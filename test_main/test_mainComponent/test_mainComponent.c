#include "legato.h"
//#include "string.h"
#include <curl/curl.h>
#include "le_data_interface.h"
#include "le_mdc_interface.h"
//#include "le_dcs_interface.h"
//#include "le_data_common.h"
//#include "le_mdc_common.h"

//--------------------------------------------------------------------------------------------------
/**
 * Set the network configuration.
 *
 */
//--------------------------------------------------------------------------------------------------
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

COMPONENT_INIT
{
	le_mdc_ConnectService();
	le_mdc_ProfileRef_t defaultModemProfile = le_mdc_GetProfile(LE_MDC_DEFAULT_PROFILE);
	le_mdc_SetAPN(defaultModemProfile, "internet.sierrawireless.com");
	le_mdc_SetPDP(defaultModemProfile, LE_MDC_PDP_IPV4);
	le_mdc_ConState_t state;
	le_mdc_GetSessionState(defaultModemProfile, &state);
	le_mdc_StartSession(defaultModemProfile);

	SetNetworkConfiguration(defaultModemProfile);















//  CURLcode ret;
//	CURL *hnd;
//
//	hnd = curl_easy_init();
//	curl_easy_setopt(hnd, CURLOPT_URL, "http://droptips.com");
//	curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
//	curl_easy_setopt(hnd, CURLOPT_NOBODY, 1L);
//	curl_easy_setopt(hnd, CURLOPT_HEADER, 1L);
//	curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.54.0");
//	curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
//	curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
//	curl_easy_setopt(hnd, CURLOPT_FILETIME, 1L);
//	curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
//
//
//	ret = curl_easy_perform(hnd);
//
//	curl_easy_cleanup(hnd);
//	hnd = NULL;











	CURLcode ret;
	  CURL *hnd;
	  struct curl_slist *slist1;

	  slist1 = NULL;
	  slist1 = curl_slist_append(slist1, "Content-Type: application/json");
	  slist1 = curl_slist_append(slist1, "Host: al0em0v1fq7j2-ats.iot.us-east-1.amazonaws.com");

	  hnd = curl_easy_init();
	  curl_easy_setopt(hnd, CURLOPT_URL, "https://al0em0v1fq7j2-ats.iot.us-east-1.amazonaws.com:8443/topics/iot/mangoh");
	  curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
	  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{ \"deviceName\": \"MangOH Red\", \"PM2_5\": 213.37, \"PM10\": 420.66, \"latitude\": 11.052006, \"longitude\": 52.940984, \"datetime\": \"2019-11-25T21:37:00.000Z\"}");
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












	le_mdc_StopSession(defaultModemProfile);
	while(1) {
		printf("CURL_TEST: %d\n", (int)ret);
		sleep(1);
	}
}
