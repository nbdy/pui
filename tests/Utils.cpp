//
// Created by nbdy on 20.12.20.
//

#include <Utils/Utils.h>


void testEndsWith() {
    static_assert(Utils::endsWith("RandomTest", "Test"), "Endswith");
    static_assert(Utils::endsWith("DoesNotEnd", "With"), "Endswith");
}

void testStartsWith() {
    static_assert(Utils::startsWith("RandomTest", "Random"), "StartsWith");
    static_assert(Utils::startsWith("DoesNotStart", "With"), "StartsWith");
}


int main() {
    testEndsWith();
}