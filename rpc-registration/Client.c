#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define strrcvprog ((u_long)150000)
#define version ((u_long)1)
#define strrcvproc ((u_long)1)

struct input
{
    int SerialNumber;
    char *registration_number;
    char *StudentsName;
};

bool_t xdr_input(XDR *xdrs, struct input *objp)
{
    // XDR function for serializing input struct
}

struct output
{
    int status;
};

bool_t xdr_output(XDR *xdrs, struct output *objp)
{
    // XDR function for serializing output struct
}

int main(int argc, char *argv[])
{
    // Main function for the RPC client

    struct input instrs;
    struct output outstrs;
    int error;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s hostname\n", argv[0]);
        exit(-1);
    }

    // Allocate memory for the strings in the input struct
    instrs.registration_number = (char *)malloc(512);
    instrs.StudentsName = (char *)malloc(512);

    // Get input from the user
    printf("Enter serial number: ");
    scanf("%d", &instrs.SerialNumber);
    printf("Enter registration number: ");
    scanf("%s", instrs.registration_number);
    printf("Enter Students Name: ");
    getchar();
    fgets(instrs.StudentsName, 512, stdin);
    instrs.StudentsName[strcspn(instrs.StudentsName, "\n")] = 0;

    /* Send the number and strings to the server. The server should
     * return the status. */
    error = callrpc(argv[1], strrcvprog, version, strrcvproc,
                    (xdrproc_t)xdr_input, (char *)&instrs,
                    (xdrproc_t)xdr_output, (char *)&outstrs);
    if (error != 0)
    {
        fprintf(stderr, "error: call rpc failed: %d \n", error);
        fprintf(stderr, "strcprog: %d version: %d strcvproc: %d",
                strrcvprog, version, strrcvproc);
        exit(1);
    }

    // Check the status received from the server and display appropriate message
    if (outstrs.status == 0)
    {
        printf("☑️ Student details added successfully\n");
    }
    else
    {
        printf("⚠️ Error adding student. Serial number or registration number already exists.\n");
    }

    // Free the allocated memory
    free(instrs.registration_number);
    free(instrs.StudentsName);

    exit(0);
}
