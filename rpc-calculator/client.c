#include <stdio.h>
#include <tirpc/rpc/rpc.h>
#include <sys/socket.h>

#define intrcvprog ((u_long)150000)
#define version ((u_long)1)
#define intrcvproc ((u_long)1)

typedef struct {
    int num1;
    int num2;
    int operation;
} input_data;

int xdr_input_data(
    XDR *xdrs, input_data *data, ...)
{
    if (!xdr_int(xdrs, &data->num1))
    {
        return FALSE;
    }
    if (!xdr_int(xdrs, &data->num2))
    {
        return FALSE;
    }
    if (!xdr_int(xdrs, &data->operation))
    {
        return FALSE;
    }
    return TRUE;
}

int main(int argc, char *argv[])
{
    int num1, num2;
    int operation;
    int error;
    float result;

    char *operation_name;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s hostname\n", argv[0]);
        exit(-1);
    }

    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);

    printf("\nPlease choose an operation:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    scanf("%d", &operation);

    input_data indata = {num1, num2, operation};

    error = callrpc(argv[1], intrcvprog, version, intrcvproc, (xdrproc_t)xdr_input_data, &indata, (xdrproc_t)xdr_float, &result);
    if (error != 0)
    {
        fprintf(stderr, "error: callrpc failed: %d \n", error);
        fprintf(stderr, "intrcprog: %lu version: %lu intrcvproc: %lu", intrcvprog, version, intrcvproc);
        exit(1);
    }

    switch (operation){
    case 1:
        operation_name = "Addition";
        break;
    case 2:
        operation_name = "Subtraction";
        break;
    case 3:
        operation_name = "Multiplication";
        break;
    case 4:
        operation_name = "Division";
        break;
    default:
        operation_name = "Unknown";
        break;
    }

    printf("The result of %s on %d and %d is: %f\n", operation_name, num1, num2, result);
    exit(0);
}
