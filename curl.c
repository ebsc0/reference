#include <curl/curl.h>
#include "common.h"


int main(int argc, char** argv)
{
    CURL *curl; /* instantiate cURL handler */
    CURLcode res; /* result code */

    curl_global_init(CURL_GLOBAL_DEFAULT); /* init global */
    curl = curl_easy_init(); /* init easy */
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://curl.se/libcurl/"); /* set url */
        res = curl_easy_perform(curl); /* perform request */

        if(res != CURLE_OK) /* check request was successful */
        {
            perror("curl_easy_perform failed");
            return -1;
        }
        curl_easy_cleanup(curl); /* cleanup easy */
    } else {
        perror("curl_easy_init failed"); /* check init easy was successful */
        return -1;
    }

    curl_global_cleanup(); /* cleanup global */
 
    return 0;
}