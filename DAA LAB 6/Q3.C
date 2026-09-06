#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    double real;
    double imag;
} Complex;

/* Recursive FFT */
void FFT(Complex a[], int n, int inverse)
{
    if (n == 1)
        return;

    Complex even[n / 2], odd[n / 2];

    for (int i = 0; i < n / 2; i++) {
        even[i] = a[2 * i];
        odd[i]  = a[2 * i + 1];
    }

    FFT(even, n / 2, inverse);
    FFT(odd, n / 2, inverse);

    double angle = 2 * PI / n;

    if (!inverse)
        angle = -angle;

    Complex w = {1, 0};

    Complex wn = {
        cos(angle),
        sin(angle)
    };

    for (int i = 0; i < n / 2; i++) {

        Complex t = {
            w.real * odd[i].real - w.imag * odd[i].imag,
            w.real * odd[i].imag + w.imag * odd[i].real
        };

        a[i].real = even[i].real + t.real;
        a[i].imag = even[i].imag + t.imag;

        a[i + n / 2].real = even[i].real - t.real;
        a[i + n / 2].imag = even[i].imag - t.imag;

        Complex temp = {
            w.real * wn.real - w.imag * wn.imag,
            w.real * wn.imag + w.imag * wn.real
        };

        w = temp;
    }

    /* Scaling for inverse FFT */
    if (inverse) {
        for (int i = 0; i < n; i++) {
            a[i].real /= n;
            a[i].imag /= n;
        }
    }
}

/* Find next power of 2 */
int nextPowerOf2(int n)
{
    int p = 1;

    while (p < n)
        p *= 2;

    return p;
}

/* Convolution using FFT */
void convolution(double A[], int m, double B[], int n)
{
    int size = m + n - 1;
    int N = nextPowerOf2(size);

    Complex FA[N], FB[N];

    /* Initialize arrays */
    for (int i = 0; i < N; i++) {
        FA[i].real = 0;
        FA[i].imag = 0;
        FB[i].real = 0;
        FB[i].imag = 0;
    }

    /* Store input vectors */
    for (int i = 0; i < m; i++)
        FA[i].real = A[i];

    for (int i = 0; i < n; i++)
        FB[i].real = B[i];

    /* FFT */
    FFT(FA, N, 0);
    FFT(FB, N, 0);

    /* Point-wise multiplication */
    for (int i = 0; i < N; i++) {

        double real = FA[i].real * FB[i].real
                    - FA[i].imag * FB[i].imag;

        double imag = FA[i].real * FB[i].imag
                    + FA[i].imag * FB[i].real;

        FA[i].real = real;
        FA[i].imag = imag;
    }

    /* Inverse FFT */
    FFT(FA, N, 1);

    /* Print result */
    printf("\nConvolution: ");

    for (int i = 0; i < size; i++)
        printf("%.0f ", FA[i].real);

    printf("\n");
}

int main()
{
    int m, n;

    printf("Enter size of A: ");
    scanf("%d", &m);

    printf("Enter size of B: ");
    scanf("%d", &n);

    double A[m], B[n];

    printf("Enter elements of A: ");
    for (int i = 0; i < m; i++)
        scanf("%lf", &A[i]);

    printf("Enter elements of B: ");
    for (int i = 0; i < n; i++)
        scanf("%lf", &B[i]);

    convolution(A, m, B, n);

    return 0;
}