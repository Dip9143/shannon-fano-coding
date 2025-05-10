#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#define MAX_BIT 16

void sel_sort_dec(float* probs, int size);
int equaiprob_2(float* probs, int start_index, int end_index);
void add_bits(int start_index, int end_index, char probs_bit[][MAX_BIT], char* bit_str) ;
void shannon_fano(float* probs, int start_index, int end_index, char probs_bit[][MAX_BIT]);
void codeword(float* probs, char probs_bit[][MAX_BIT], int size);
float entropy(float* probs, int size);
float efficiency(float* probs, char probs_bit[][MAX_BIT], float entropy, int size);

int main() {
    // Taking the size of the array as number of elemnts
    int size;
    printf("Enter the number of symbols: ");
    scanf("%d" , &size);

    // Array size of n that contains probabilties
    float probs[size];

    // Taking the input of the elements in the array
    printf("Enter the probabilties for each symboles(in real number): ");
    for (int i = 0; i < size; i++)
    {
        scanf("%f", &probs[i]);
    }

    // Array which stores bit_string
    char probs_bit[size][MAX_BIT];

    // Initializing each element to be a empty string
    for (int i = 0; i < size; i++)
    {
        strcpy(probs_bit[i], "");  // sets first char to '\0'
    }

    // Sorting the array in decreasing order
    sel_sort_dec(probs, size);

    // Applying Shannon Fanno
    shannon_fano(probs, 0, size - 1, probs_bit);

    // Printing the codewords
    codeword(probs, probs_bit, size);

    // Printing entropy
    float entropy_val = entropy(probs, size);
    printf("Entropy: %6.4f\n", entropy_val);

    // Printing efficiency
    float efficiency_val = efficiency(probs, probs_bit, entropy_val, size);
    printf("Efficiency: %5.2f%%", efficiency_val*100);


    return 0;

}


void sel_sort_dec(float* probs, int size) 
{ // Using simple selection sorting algorithm in decresing order
    int max_index;
    for (int i = 0; i < size - 1; i++)
    {
        max_index = i;
        for (int c = i + 1; c < size; c++)
        {
            if (probs[max_index] < probs[c])
            {
                max_index = c;
            }
        }

        float temp = probs[i];
        probs[i] = probs[max_index];
        probs[max_index] = temp;
    }
}

int equaiprob_2(float* probs, int start_index, int end_index)
{
    // Returns the index which divides the array into most equaiprobable set
    float total_prob = 0.0;
    for (int i = start_index; i <= end_index; i++)
    {
        total_prob += probs[i];
    }

    float target = total_prob/2;

    float current_sum = 0.0;
    for (int i = start_index; i <= end_index; i++)
    {
        current_sum += probs[i];
        if (current_sum >= target) return i;
    }

    return end_index;
}

void add_bits(int start_index, int end_index, char probs_bit[][MAX_BIT], char* bit_str) {


    for (int i = start_index; i <= end_index; i++) {

        // Append bit ('0' or '1') to the corresponding bit string
        strcat(probs_bit[i], bit_str);
    }

}

void shannon_fano(float* probs, int start_index, int end_index, char probs_bit[][MAX_BIT]) 
{
    if (start_index != end_index)
    {
        // Calculate the index which divides the array into two most equaiprobable set
        int divide_index = equaiprob_2(probs, start_index, end_index);

        // Adding bits 0 or 1
        add_bits(start_index, divide_index, probs_bit, "0");
        add_bits(divide_index + 1, end_index, probs_bit, "1");

        // Recursive call
        shannon_fano(probs, start_index, divide_index, probs_bit);
        shannon_fano(probs, divide_index + 1, end_index, probs_bit);


    

    }
}

void codeword(float* probs, char probs_bit[][MAX_BIT], int size)
{
    printf("\n-------------------------------------CODEWORDS-------------------------------------------\n");
    for (int i = 0; i < size; i++)
    {
        printf("Codeword of the symbol with the probabilty %0.4f: %s, lenght: %d\n", probs[i], probs_bit[i], strlen(probs_bit[i]));
    }

     printf("-----------------------------------------------------------------------------------------\n");
    
}

float entropy(float* probs, int size)
{// Calculating entropy 
    float entropy_val = 0.0;
    for (int i = 0; i < size; i++)
    {
        entropy_val += probs[i]*(log2(1/probs[i]));
    }

    return entropy_val;
}

float efficiency(float* probs, char probs_bit[][MAX_BIT], float entropy, int size)
{
    float max_entropy = 0.0;
    for (int i = 0; i < size; i++)
    {
        max_entropy += probs[i]*(strlen(probs_bit[i]));
    }

    return (entropy/max_entropy);
}