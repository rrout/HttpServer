#include <iostream>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include "Utils.h"

extern void start();
void run_start() {
    start();
}

int main() {
    boost::thread start_thread(run_start);
    while (1) {
        boost::this_thread::sleep_for(boost::chrono::minutes(5));
        std::cout << "Main thread woke up, continuing to wait..." << std::endl;
    }
    start_thread.join();
    return 1;
}
