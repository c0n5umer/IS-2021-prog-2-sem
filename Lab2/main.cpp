#include <unistd.h>
#include <iostream>
#include <vector>

#include <nlohmann/json.hpp>

#include "currency.h"
#include "request.h"

using json = nlohmann::json;

int main() {
    std::vector<Currency> values;

    json req = json::parse(getRequest());

    for (json::iterator it = req["Valute"].begin(); it != req["Valute"].end(); ++it) {
        Currency temp(it.value()["CharCode"], it.value()["Name"], it.value()["Value"], it.value()["Nominal"]);

        values.push_back(temp);
    }

    printValues(values);

    while (true) {
        sleep(5);
        std::cout << std::endl;
        updateValues(values);
        printValues(values);
    }

    return 0;
}