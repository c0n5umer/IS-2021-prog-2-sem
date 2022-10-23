//
// Created by Aleksandr Orlov on 18.03.2022.
//

#ifndef LAB2_REQUEST_H
#define LAB2_REQUEST_H

#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <memory>
#include <vector>

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "currency.h"

void cleanup(CURL *curl, curl_slist *headers);
size_t curl_callback(void *ptr, size_t size, size_t nmemb, std::string* data);
std::string getRequest();
void updateValues(std::vector<Currency> &values);
void printValues(std::vector<Currency> &values);


#endif //LAB2_REQUEST_H
