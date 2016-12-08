#include <stdio.h>
#include <string.h>

#include "ml_mfile.h"

#define MAX_BLOCK_SIZE  262144

int main(int argc, char **argv)
{
	MFILE *mfp_body = ml_mopen(MAX_BLOCK_SIZE, NULL, NULL);	
	if (mfp_body == NULL) {
		printf("mopen for body fail\n");
		return 1;
	}

	printf("Input >>>>>>>>>>>>>\n");
	char buf[1024*5] = {0};
	while (fgets(buf, sizeof(buf), stdin)) {
		int wr = ml_mwrite(mfp_body, buf, strlen(buf));
		if (wr != 1) {
			ml_mclose(mfp_body);
			printf("mwrite fail for body\n");

			break;
		}
	}

	int body_len = ml_msize(mfp_body);
	printf("\nbody len:%d\n", body_len);
	printf("Output >>>>>>>>>>>>>\n");

	ml_mseek(mfp_body);
	while (1) {
		memset(buf, 0, sizeof(buf));
		int nr = ml_mread_line(mfp_body, buf, sizeof(buf));
		if (nr == 0) {
			break;
		}

		printf("%s", buf);
	}

	ml_mclose(mfp_body);
	mfp_body = NULL;

	return 0;
}
