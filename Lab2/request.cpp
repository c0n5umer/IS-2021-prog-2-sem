//
// Created by Aleksandr Orlov on 18.03.2022.
//

#include "request.h"

using json = nlohmann::json;

void cleanup(CURL *curl, curl_slist *headers) {
    if (curl)
        curl_easy_cleanup(curl);
    if (headers)
        curl_slist_free_all(headers);
    curl_global_cleanup();
}

size_t curl_callback(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

std::string getRequest()
{
    const std::string url = "https://www.cbr-xml-daily.ru/daily_json.js";
    struct curl_slist *headers = NULL;

    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    std::string response_string;

    if (!curl) {
        std::cout << "ERROR : Curl initialization\n" << std::endl;
        cleanup(curl, headers);
        return NULL;
    }

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode status = curl_easy_perform(curl);
    if (status != 0) {
        std::cout << "Error: Request failed on URL : " << url << std::endl;
        std::cout << "Error Code: " << status << " Error Detail : " << curl_easy_strerror(status) << std::endl;
        cleanup(curl, headers);
        return NULL;
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    curl_global_cleanup();

    return response_string;
}

void updateValues(std::vector<Currency> &values) {
    json req = json::parse(getRequest());

    for (int i = 0; i < values.size(); i++) {
        try {
            values[i].updateValue((double)req["Valute"][values[i].getCharcode()]["Value"] /
                                  (int)req["Valute"][values[i].getCharcode()]["Nominal"]);
        }
        catch(const std::exception& ex) {
            std::cout << "Error: error when update" << std::endl;
        }
    }
}

void printValues(std::vector<Currency> &values) {
    for (int i = 0; i < values.size(); i++)
        std::cout << values[i].getCharcode() << ": " << values[i].getName() << "; " << values[i].getValue() << "; average: "
                  << values[i].getAverage() << "; median: " << values[i].getMedian() << std::endl;
}