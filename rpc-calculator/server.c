#ifndef MVS
#define MVS
#endif

#include <tirpc/rpc/rpc.h>
#include <stdio.h>

#define intrcvprog ((u_long)150000)
#define fltrcvprog ((u_long)150102)
#define intvers ((u_long)1)
#define intrcvproc ((u_long)1)
#define fltrcvproc ((u_long)1)
#define fltvers ((u_long)1)

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

int main()
{
    char *intrcv(input_data *in);

    registerrpc(intrcvprog, intvers, intrcvproc, (char *(*)(char *))intrcv, (xdrproc_t)xdr_input_data, (xdrproc_t)xdr_int);
    printf("Intrcv Registration with Port Mapper completed\n");

    svc_run();
    printf("Error:svc_run returned!\n");
    exit(1);
}

char *intrcv(input_data *in)
{
    static float result;
    // print the values received
    printf("First number: %d\n", in->num1);
    printf("Second number: %d\n", in->num2);
    printf("The operation number: %d\n", in->operation);

    switch (in->operation)
    {
    case 1:
        result = in->num1 + in->num2;
        break;
    case 2:
        result = in->num1 - in->num2;
        break;
    case 3:
        result = in->num1 * in->num2;
        break;
    case 4:
        result = (float)in->num1 / in->num2;
        break;
    default:
        fprintf(stderr, "Oops!!Invalid operation\n");
        exit(1);
        break;
    }

    return (char *)&result;
}