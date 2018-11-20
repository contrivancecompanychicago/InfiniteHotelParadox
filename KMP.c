#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*  int room_id;
  char name[100];
  int age;
  char key_assigned[20];
};*/

void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}


void computeLPSArray(char* pat, int M, int* lps);

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {//Checking for the aptness of the key for the hotel roonm.
            printf("Your key is correct. ");
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)

                j = lps[j - 1];
            else
                i = i + 1;
                if (i==N)
                {
                    printf("Your key doesn't match the one assigned to you\n");
                }

        }

    }
}

// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0) {
                len = lps[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}


int main()
{
  //srand(time(NULL));
  char assigned_key[100], key_entered[100];
  gen_random(assigned_key, 14);
  printf("The key assigned to you is: %s", assigned_key);
  printf("\nEnter the key for your room.\n");
  scanf("%s", key_entered);
  KMPSearch(key_entered, assigned_key);
  return 0;
}
