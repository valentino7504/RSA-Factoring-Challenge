#include "rsa.h"
/**
 * main - the factoring file
 * @argc: the number of command line arguments
 * @argv: the command line arguments
 * Return: 0
 */
int main(int argc, char *argv[])
{
	FILE *file = fopen(argv[1], "r");
	char line[100];
	mpz_t number, small_factor, large_factor, half;
	mpz_inits(number, small_factor, large_factor, half, NULL);

	while (fgets(line, sizeof(line), file) != NULL)
	{
		if (strcmp(line, "\n") == 0)
			break;
		line[strlen(line) - 1] = '\0';
		mpz_set_str(number, line, 10);
		mpz_set_str(large_factor, line, 10);
		mpz_set_str(small_factor, "2", 10);
		mpz_tdiv_q_ui(half, number, 2);
		while ((mpz_cmp(small_factor, half) <= 0))
		{
			if (mpz_divisible_p(number, small_factor))
				break;
			if (!mpz_cmp(small_factor, half))
			{
				mpz_set_str(small_factor, "1", 10);
				break;
			}
			mpz_add_ui(small_factor, small_factor, 1);
		}
		mpz_tdiv_q(large_factor, number, small_factor);
		mpz_out_str(stdout, 10, number);
		printf("=");
		mpz_out_str(stdout, 10, large_factor);
		printf("*");
		mpz_out_str(stdout, 10, small_factor);
		printf("\n");
	}
	mpz_clears(number, small_factor, large_factor, NULL);
	fclose(file);
	return (0);
}
