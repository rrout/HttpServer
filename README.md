# HttpServer
Sample HTTP Server built with boost

# httpserver

## Overview
HttpServer is a C++ application that uses the Boost library to Create REST API.

## Features
- Native Support of JSON
- SSL cert support
- MVC model

## Folder Structure
HttpServer/ ├── inc/ │ └── your_headers.h └── src/ └── your_sources.cpp


## Requirements
- CMake 3.10 or higher
- Boost libraries
- A C++17 compatible compiler

## Setup and Installation
1. **Clone the repository**:
   ```sh
   git clone https://github.com/rrout/HttpServer
   cd HttpServer

## Build The Project
   ```sh
   mkdir build
    cd build
    cmake ..
    make

## Usage
Describe here how to run and use your project. Provide examples if necessary:

    ```sh
    ./httpserver

## Examples
Provide some example commands and their expected output.
```sh
curl http://localhost:8080/apiv1/GetVnet
curl http://localhost:8080/apiv1/GetVnet?vnetId=abcd
curl http://localhost:8080/apiv1/GetMapping
curl http://localhost:8080/apiv1/GetMapping?vnetId=abcd
curl -X POST -H "Content-Type: application/json" -d '{"vnetId":"01234567-89ab-cdef-0123-456789abcdef","cAddr":"1.1.1.1", "cMac":"1.1.1.1", "pAddr":"1.1.1.1", "pMac":"1.1.1.1"}' http://localhost:8080/apiv1/PutMapping
curl -X POST -H "Content-Type: application/json" -d '{"vnetId":"01234567-89ab-cdef-0123-456789abcdef"}' http:  //localhost:8080/apiv1/PutVnet


## Contributing
Fork the repository

Create a new branch (git checkout -b feature-branch)

Commit your changes (git commit -am 'Add new feature')

Push to the branch (git push origin feature-branch)

Create a new Pull Request

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Contact
If you have any questions, feel free to reach out:

Name: Rashmi Ranjan Rout

Email: rashmiranjan_rout@outlook.com

