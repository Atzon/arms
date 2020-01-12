#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

#include "legato.h"

COMPONENT_INIT
{

    LE_INFO("Hello, world.");
    CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl) {
//		url_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	  curl_easy_setopt(curl, CURLOPT_URL, "https://al0em0v1fq7j2-ats.iot.us-east-1.amazonaws.com:8443/topics/iot/mangoh");
	  curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
	  curl_easy_setopt(curl, CURLOPT_CAINFO, "./AmazonRootCA1.pem");
	  curl_easy_setopt(curl, CURLOPT_SSLCERT, "./fd9b2692c5-certificate.pem.crt");
	  curl_easy_setopt(curl, CURLOPT_SSLKEY, "./fd9b2692c5-private.pem.key");
	  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"PM2_5\": 30.28,\"latitude\": 50.062006,\"longitude\": 19.940984,\"PM10\": 100.66,\"datetime\": \"2020-05-30T23:00:00.000Z\"}");
	  res = curl_easy_perform(curl);
	  curl_easy_cleanup(curl);
	}

	printf("DUPA_8: %d\n", res);
}
