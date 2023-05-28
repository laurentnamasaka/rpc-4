# README

This README file provides instructions on how to compile and run the client and server code for a simple RPC (Remote Procedure Call) application. The code consists of two files: `server.c` and `client.c`. The server code handles incoming requests and performs a search or registration operation based on the received data. The client code prompts the user for input and sends it to the server for processing.

## Compilation Instructions

### Server Compilation

To compile the server code, follow these steps:

1. Open a terminal or command prompt.
2. Navigate to the directory containing the `server.c` file.
3. Execute the following command to compile the code:

   ```shell
   gcc -o server server.c -lnsl
   ```

   This command uses the GNU Compiler Collection (GCC) to compile the `server.c` file into an executable named `server`. The `-lnsl` flag is used to link the network services library (`libnsl`), which is required for RPC.

### Client Compilation

To compile the client code, follow these steps:

1. Open a terminal or command prompt.
2. Navigate to the directory containing the `client.c` file.
3. Execute the following command to compile the code:

   ```shell
   gcc -o client client.c -lnsl
   ```

   This command uses the GCC to compile the `client.c` file into an executable named `client`. The `-lnsl` flag is used to link the network services library (`libnsl`), which is required for RPC.

## Execution Instructions

### Starting the Server

Before running the client, the server needs to be started. Follow these steps to start the server:

1. Open a terminal or command prompt.
2. Navigate to the directory containing the compiled `server` executable.
3. Execute the following command to start the server:

   ```shell
   ./server
   ```

   The server will now be listening for incoming RPC requests.

### Running the Client

To run the client and interact with the server, follow these steps:

1. Open a terminal or command prompt.
2. Navigate to the directory containing the compiled `client` executable.
3. Execute the following command to run the client:

   ```shell
   ./client <server_hostname>
   ```

   Replace `<server_hostname>` with the hostname or IP address of the machine running the server. This is the machine where you started the server in the previous step.
   
4. The client will prompt you to enter the following information:

   - **Serial number**: Enter an integer value representing the serial number.
   - **Registration number**: Enter a string representing the registration number.
   - **Students Name**: Enter a string representing the name of the student.

5. After entering the required information, the client will send the data to the server using RPC.
6. The server will process the data and send a response back to the client.
7. The client will display the appropriate message based on the response received from the server.

## Additional Notes

- The server code assumes the existence of a file named `Registration.txt` in the same directory, which is used to store student records. Make sure the file exists and is writable by the server process.
- The code provided is a simplified example of RPC usage and may require modifications or enhancements for use in a real-world scenario.