A task provided to us during our self-studies day on October 30th 2025.

The assignment is about making a project as a developer in a fictitious company that provides security solutions for other companies.
"We" are hired to provide a "Smart Sensor Node" which is designed to measure temperatures, store them locally and also has the ability to send these values to a cloud server using TCP/HTTP.

The assignment also had other parts to it, other than programming, but in this file I only state the things connected to this functionality.

Here we are supposed to implement an easy C-program that:
* Uses TCP-sockets to connect to a server (for example: example.com  port:80).
* Sends a simple HTTP POST-inquiry:
POST  / HTTP/1.1
Host: example.com
{
    "device": "UUID",
    "time": "<time>",
    "temperature": "<temperature>°C"
}

It recieves the answer from the serer and writes it to the terminal.

Specifications:
* The program has to use at least one function pointer (for example: how to choose between different handling functions for incoming data.)
* At least one example of a pointer to pointer (for example: char **argv or a dynamically allocated list)
* Compiles through a Makefile with seperate .c and .h-files
* Versionalised with GIT (a minimum of three commits with clear messages.)