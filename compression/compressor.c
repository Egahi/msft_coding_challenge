/**
 * compressor.c
 *
 * this program compresses a file via run length encoding
 * i.e reoccuring consecutive characters are represented
 * with a single charcater and the frequency of ocurrence
 *
 * solution to microsoft coding challenge (compression)
 * https://msft3c.com/preview/1/learn
 *
 * input file format
 * each string is on a separate line
 * the total number of strings is written on the first
 * line in the file
 *
 * @s_egahi
 *
 * this is compressor
 */

#include <stdio.h>
#include <stdlib.h>

#define LENGTH 46

int strlength(char word[]);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./compressor file.txt\n");
    }

    // open file for reading
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // open file for writing
    FILE *outfile = fopen("output.txt", "a");
    if (outfile == NULL)
    {
        printf("Could not open output.txt");
        return 2;
    }

    // Read first character in file
    // represents the number of strings in the file
    int lines = 0;
    fscanf(infile, "%i", &lines);

    // print number of strings to output
    fprintf(outfile, "%i", lines);

    char word[LENGTH];
    int frequency = 1;
    int length;

    for (int i = 0; i < lines; i++)
    {
        // read a word from the infile
        fscanf(infile, "%s", word);

        // length of string
        length = strlength(word);

        // add a new line to outfile
        fputc('\n', outfile);

        // iterate over individual characters
        for (int j = 0; j < length; j++)
        {
            // reoccuring characters
            if (word[j] == word[j + 1])
            {
                // keep track of number of reoccurrence
                frequency++;
            }

            // different character found
            else
            {
                // previous character did not reoccur
                if (frequency == 1)
                {
                     // append character to outfile
                     fputc(word[j], outfile);
                }

                // previous character reoccurred
                else
                {
                     // append number of reoccurernce to outfile
                     fprintf(outfile, "%i", frequency);

                     // append character to outfile
                     fputc(word[j], outfile);

                     // refresh counter
                     frequency = 1;
                }
            }
        }
    }

    // success
    return 0;
}

/**
 * calculates and returns the length of a string
 */
int strlength(char word[])
{
    int length = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        length++;
    }

    return length;
}