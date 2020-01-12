#include "legato.h"
#include "interfaces.h"
#include "le_tty.h"
#include <curl/curl.h>
#include "le_data_interface.h"
#include "le_mdc_interface.h"

static void SetNetworkConfiguration
(
    le_mdc_ProfileRef_t profileRef
)
{
    char ipAddr[100] = {0};
    char gatewayAddr[100] = {0};
    char dns1Addr[100] = {0};
    char dns2Addr[100] = {0};
    char systemCmd[200] = {0};
    FILE* resolvFilePtr;
    le_mdc_ConState_t state = LE_MDC_DISCONNECTED;
    mode_t oldMask;

    // Check the state
    LE_ASSERT( le_mdc_GetSessionState(profileRef, &state) == LE_OK );
    LE_ASSERT( state == LE_MDC_CONNECTED );

    // Get IP, gateway and DNS addresses for IPv4 or IPv6 connectivity
    if ( le_mdc_IsIPv4(profileRef) )
    {
        LE_ASSERT(le_mdc_GetIPv4Address(profileRef, ipAddr, sizeof(ipAddr)) == LE_OK);
//        LE_PRINT_VALUE("%s", ipAddr);

        LE_ASSERT(le_mdc_GetIPv4GatewayAddress(profileRef, gatewayAddr, sizeof(gatewayAddr))
                                                                                          == LE_OK);
//        LE_PRINT_VALUE("%s", gatewayAddr);

        LE_ASSERT(le_mdc_GetIPv4DNSAddresses( profileRef,
                                              dns1Addr, sizeof(dns1Addr),
                                              dns2Addr, sizeof(dns2Addr)) == LE_OK );
//        LE_PRINT_VALUE("%s", dns1Addr);
//        LE_PRINT_VALUE("%s", dns2Addr);

        snprintf(systemCmd, sizeof(systemCmd), "/sbin/route add default gw %s", gatewayAddr);
    }
    else if ( le_mdc_IsIPv6(profileRef) )
    {
        LE_ASSERT(le_mdc_GetIPv6Address(profileRef, ipAddr, sizeof(ipAddr)) == LE_OK);
//        LE_PRINT_VALUE("%s", ipAddr);

        LE_ASSERT(le_mdc_GetIPv6GatewayAddress(profileRef, gatewayAddr, sizeof(gatewayAddr))
                                                                                          == LE_OK);
//        LE_PRINT_VALUE("%s", gatewayAddr);

        LE_ASSERT(le_mdc_GetIPv6DNSAddresses( profileRef,
                                              dns1Addr, sizeof(dns1Addr),
                                              dns2Addr, sizeof(dns2Addr)) == LE_OK );
//        LE_PRINT_VALUE("%s", dns1Addr);
//        LE_PRINT_VALUE("%s", dns2Addr);

        snprintf(systemCmd, sizeof(systemCmd), "/sbin/route -A inet6 add default gw %s",
                                                gatewayAddr);
    }

    sleep(5);

    LE_DEBUG("%s", systemCmd);
    LE_ASSERT( system(systemCmd) == 0 );

    // allow fopen to create file with mode=644
    oldMask = umask(022);

    // open the resolver configuration
    resolvFilePtr = fopen("/etc/resolv.conf", "w+");

    if (resolvFilePtr == NULL)
    {
        LE_ERROR("Unable to open resolv.conf: %m");
    }
    LE_ASSERT( resolvFilePtr != NULL );

    LE_ASSERT( fprintf(resolvFilePtr, "nameserver %s\n", dns1Addr) > 0 );

    if (dns2Addr[0] != '\0')
    {
        LE_ASSERT( fprintf(resolvFilePtr, "nameserver %s\n", dns2Addr) > 0 );
    }

    LE_ASSERT( fclose(resolvFilePtr) == 0 );

    // restore old mask
    umask(oldMask);
}

le_result_t get_coordinates(int32_t * latitude, int32_t * longitude, int32_t * hAccuracy) {
	le_result_t res;

	res = le_pos_Get2DLocation(latitude, longitude, hAccuracy);

	if (res == LE_OK)
	{
		LE_INFO("Location: latitude=%.6f, longitude=%.6f, hAccuracy=%.6f", *latitude/10e5, *longitude/10e5, *hAccuracy/10e5);
	}
	else if (res == LE_FAULT)
	{
		LE_INFO("Failed to get the 2D location's data");
	}
	else if (res == LE_OUT_OF_RANGE)
	{
		LE_INFO("One of the retrieved parameter is invalid (set to INT32_MAX)");
	}
	else
	{
		LE_INFO("unknown location error (%d)", res);
	}

	return res;
}

COMPONENT_INIT
{
	/**
	 * GPS part
	 */
	LE_INFO("Fetching 2D location \n");

	le_posCtrl_ActivationRef_t posCtrlRef = le_posCtrl_Request();
	if (!posCtrlRef)
	{
		LE_ERROR("Can't activate the Positioning service");
	}

	le_result_t res;
	int32_t latitude = 0;
	int32_t longitude = 0;
	int32_t hAccuracy = 0;

	//debug
	float latitude_f;
	float longitude_f;

	/**
	 * Sensor part
	 */
	int fd = le_tty_Open("/dev/ttyHS0", O_RDWR | O_NOCTTY | O_NDELAY);
	le_tty_SetBaudRate(fd, LE_TTY_SPEED_9600);

    char * byte;
    char * lastbyte;

    byte = malloc( sizeof(char) );
    lastbyte = malloc( sizeof(char) );

    * byte = 0x00;

    char * buffer;
    buffer = malloc( 6 * sizeof(char) );

    int pm_25;
    int pm_100;

	/**
	 * Time part
	 */
	char buffer_time[30];

	time_t rawTime;
	struct tm * timeinfo;

	/**
	 * Curl part
	 */
	// String
	char buffer_json[500];

	le_mdc_ConnectService();
	le_mdc_ProfileRef_t defaultModemProfile = le_mdc_GetProfile(LE_MDC_DEFAULT_PROFILE);
	le_mdc_SetAPN(defaultModemProfile, "internet.sierrawireless.com");
	le_mdc_SetPDP(defaultModemProfile, LE_MDC_PDP_IPV4);
	le_mdc_ConState_t state;
	le_mdc_GetSessionState(defaultModemProfile, &state);
	le_mdc_StartSession(defaultModemProfile);

	SetNetworkConfiguration(defaultModemProfile);

	CURLcode ret;
	CURL *hnd;
	struct curl_slist *slist1;


	int iter;
	/**
	 * Sending value
	 */
	while(1) {
		// GPS
		get_coordinates(&latitude, &longitude, &hAccuracy);
		latitude_f = latitude / 10e5;
		longitude_f = longitude / 10e5;
		printf("Coords: %f, %f\n", latitude_f, longitude_f);

		// Sensor
		for(iter = 0; iter < 8; ++iter) {
			* lastbyte = * byte;
			read( fd, byte, 1 );

			if( * lastbyte == 0xaa && * byte == 0xc0 ) {
				read( fd, buffer, 6 );
				pm_25 = buffer[0] + 256 * buffer[1];
				pm_100 = buffer[2] + 256 * buffer[3];

				printf("PM2.5: %.1f, PM10: %.1f\n", (double)pm_25 / 10.0, (double)pm_100 / 10.0);
			}
		}



//		read(fd, buffer, 100);
		printf("PM2.5: %f, PM10: %f\n", (buffer[3])/10.0, (buffer[2])/10.0); // Note: not correct, check which bytes to use

		// Time
		time(&rawTime);
		timeinfo = localtime(&rawTime);

		timeinfo->tm_hour = timeinfo->tm_hour -1;
//		printf("THERE%d\n\n\n\n",timeinfo->tm_hour);


		strftime(buffer_time, 30, "%Y-%m-%dT%H:%M:%S.000Z", timeinfo);
		printf("%s\n", buffer_time);

		// Curl
		// String
//		sprintf(buffer_json, "{ \"deviceName\": \"MangOH Der\", \"PM2_5\": %f, \"PM10\": %f, \"latitude\": %f, \"longitude\": %f, \"datetime\": \"%s\"}", (buffer[3])/10.0, (buffer[2])/10.0, latitude_f, longitude_f, buffer_time);
		sprintf(buffer_json, "{ \"deviceName\": \"TEST mangOH\", \"PM2_5\": %.2f, \"PM10\": %.2f, \"latitude\": %f, \"longitude\": %f, \"datetime\": \"%s\"}", (double)pm_25 / 10.0, (double)pm_100 / 10.0, latitude_f, longitude_f, buffer_time);




		slist1 = NULL;
		slist1 = curl_slist_append(slist1, "Content-Type: application/json");
		slist1 = curl_slist_append(slist1, "Host: al0em0v1fq7j2-ats.iot.us-east-1.amazonaws.com");

		hnd = curl_easy_init();
		curl_easy_setopt(hnd, CURLOPT_URL, "https://al0em0v1fq7j2-ats.iot.us-east-1.amazonaws.com:8443/topics/iot/mangoh");
		curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, buffer_json);
		curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)150);
		curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.54.0");
		curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
		curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
		curl_easy_setopt(hnd, CURLOPT_CAINFO, "/home/root/aws-ula/AmazonRootCA1.pem");
		curl_easy_setopt(hnd, CURLOPT_SSLCERT, "/home/root/aws-ula/fd9b2692c5-certificate.pem.crt");
		curl_easy_setopt(hnd, CURLOPT_SSLKEY, "/home/root/aws-ula/fd9b2692c5-private.pem.key");
		curl_easy_setopt(hnd, CURLOPT_SSLVERSION, (long)CURL_SSLVERSION_TLSv1_2);
		curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

		ret = curl_easy_perform(hnd);

		curl_easy_cleanup(hnd);
		hnd = NULL;
		curl_slist_free_all(slist1);
		slist1 = NULL;


		printf("RRREEETTT: %d\n", ret);

		printf("%s\n", buffer_json);


		sleep(1);
	}
	printf("%d\n", res);


	printf("%d\n", ret);


}
