#include <rpc/rpc.h>
#include <stdio.h>
#include <string.h>

#define strrcvprog ((u_long)150000)
#define strvers ((u_long)1)
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

struct output *strrcv(struct input *in);

int main()
{
    // Register the program, version, and procedure with the portmapper
    registerrpc(strrcvprog, strvers, strrcvproc, strrcv,
                (xdrproc_t)xdr_input, (xdrproc_t)xdr_output);
    printf("☑️ The registration of the 'strrcv' procedure with the Port Mapper has been successfully completed.\n");

    // Run the RPC service loop to handle incoming requests
    svc_run();
    printf("⚠️ The execution of 'svc_run' encountered an error and returned.\n");
    exit(1);
}

// Procedure called by the server to receive and return a string
struct output *strrcv(struct input *in)
{
    // Implementation of the server-side procedure

    static struct output out;
    FILE *fp;
    int found = 0;
    int SerialNumber;
    char registration_number[512];
    char StudentsName[512];

    // Print received input values
    printf("Serial number: %d\n", in->SerialNumber);
    printf("Registration number: %s\n", in->registration_number);
    printf("Students Name: %s\n", in->StudentsName);

    // Open the file to read student records
    fp = fopen("Registration.txt", "r");
    if (fp != NULL)
    {
        // Loop through the file to find matching records
        while (fscanf(fp, "%d %s %s\n", &SerialNumber, registration_number, StudentsName) != EOF)
        {
            if (SerialNumber == in->SerialNumber || strcmp(registration_number, in->registration_number) == 0)
            {
                found = 1;
                break;
            }
        }
        fclose(fp);
    }

    // Update the output struct based on the search result
    if (!found)
    {
        // Append the received student record to the file
        fp = fopen("Registration.txt", "a");
        fprintf(fp, "%d\t\t %s\t\t %s\t\t\n", in->SerialNumber, in->registration_number, in->StudentsName);
        fclose(fp);
        out.status = 0; // success
    }
    else
    {
        out.status = 1; // failure
    }

    // Return the output struct to the client
    return &out;
}
