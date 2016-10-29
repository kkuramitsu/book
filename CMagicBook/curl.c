#include "mymagic.h"
//#include <unistd.h>
#include <curl/curl.h>
 
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}

int main(int argc, char *argv[])
{
	if(argc < 2) {
		printf("Usage: %s <URL>\n", argv[0]);
		return EXIT_FAILURE;
	}
 	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl_handle = curl_easy_init();
	/* set URL to get here */ 
	curl_easy_setopt(curl_handle, CURLOPT_URL, argv[1]);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, stdout);
	curl_easy_perform(curl_handle);
	fflush(stdout);
	curl_easy_cleanup(curl_handle);
	return 0;
}
