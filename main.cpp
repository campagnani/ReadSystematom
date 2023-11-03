#include <iostream>
#include <cstring>
#include <cstdlib>
#include <libserialport.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <serial_port_name>" << std::endl;
        return 1;
    }

    const char* portname = argv[1];

    // Create a serial port handle
    struct sp_port* port;
    sp_return result = sp_get_port_by_name(portname, &port);
    if (result != SP_OK) {
        std::cerr << "Error: Unable to open the serial port" << std::endl;
        return 1;
    }

    // Open the serial port
    result = sp_open(port, SP_MODE_READ);
    if (result != SP_OK) {
        std::cerr << "Error: Unable to open the serial port" << std::endl;
        sp_free_port(port);
        return 1;
    }

    // Set the baud rate, data bits, stop bits, and parity
    sp_set_baudrate(port, 9600);
    sp_set_bits(port, 8);
    sp_set_stopbits(port, 1);
    sp_set_parity(port, SP_PARITY_NONE);

    // Read data from the serial port with a timeout
    char header[2];
    char data[41];
    char crc[2];

    const int readTimeoutMillis = 100; // Set your desired timeout in milliseconds

    // Read header
    result = sp_blocking_read(port, header, sizeof(header), readTimeoutMillis);
    if (result != 2) {
        std::cerr << "Error: Failed to read header" << std::endl;
    } else {
        // Read data
        result = sp_blocking_read(port, data, sizeof(data), readTimeoutMillis);
        if (result != 41) {
            std::cerr << "Error: Failed to read data" << std::endl;
        } else {
            // Read CRC
            result = sp_blocking_read(port, crc, sizeof(crc), readTimeoutMillis);
            if (result != 2) {
                std::cerr << "Error: Failed to read CRC" << std::endl;
            } else {
                // Check CRC and process the received data here
                // You'll need to implement CRC checking based on your CRC algorithm
                // and further processing of the data as needed.

                std::cout << "Received header: " << header << std::endl;
                std::cout << "Received data: " << data << std::endl;
                std::cout << "Received CRC: " << crc << std::endl;
            }
        }
    }

    // Close the serial port
    sp_close(port);
    sp_free_port(port);

    return 0;
}
