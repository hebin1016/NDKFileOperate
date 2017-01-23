#include "com_example_ndkfileoperate_NDKFileUtils.h"

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"hank",FORMAT,__VA_ARGS__)
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"hank",FORMAT,__VA_ARGS__)

long getFileSize(const char *path) {
	FILE *file = fopen(path, "rb");
	fseek(file, 0, SEEK_END);
	return ftell(file);
}

/*
 * Class:     com_example_ndkfileoperate_NDKFileUtils
 * Method:    diff
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_example_ndkfileoperate_NDKFileUtils_diff(
		JNIEnv *env, jclass jclass, jstring path, jstring path_pattern,
		jint num) {
	const char *c_path = (*env)->GetStringUTFChars(env, path, NULL);
	const char *c_pattern_path = (*env)->GetStringUTFChars(env, path_pattern,
			NULL);

	char **filelist = malloc(sizeof(char*) * num);

	int i = 0;
	for (; i < num; i++) {
		filelist[i] = malloc(sizeof(char) * 100);
		sprintf(filelist[i], c_pattern_path, i);
		LOGI("patch path:%s", filelist[i]);
	}

	long filesize = getFileSize(c_path);

	FILE *FP = fopen(c_path, "rb");

	if (filesize % num == 0) {
		int part = filesize / num;
		i = 0;
		for (; i < num; i++) {
			FILE *fpw = fopen(filelist[i], "wb");
			int j = 0;
			for (; j < part; j++) {
				fputc(fgetc(FP), fpw);
			}
			fclose(fpw);
		}
	} else {
		int part = filesize / (num - 1);
		i = 0;
		for (; i < num - 1; i++) {
			FILE *fpw = fopen(filelist[i], "wb");
			int j = 0;
			for (; j < part; j++) {
				fputc(fgetc(FP), fpw);
			}
			fclose(fpw);
		}

		FILE *fpw = fopen(filelist[num - 1], "wb");
		i = 0;
		for (; i < filesize % (num - 1); i++) {
			fputc(fgetc(FP), fpw);
		}
		fclose(fpw);
	}

	fclose(FP);

	i = 0;
	for (; i < num; i++) {
		free(filelist[i]);
	}

	free(filelist);
	(*env)->ReleaseStringUTFChars(env, path_pattern, c_pattern_path);
	(*env)->ReleaseStringUTFChars(env, path, c_path);
}

/*
 * Class:     com_example_ndkfileoperate_NDKFileUtils
 * Method:    patch
 * Signature: (Ljava/lang/String;ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_example_ndkfileoperate_NDKFileUtils_patch(
		JNIEnv * env, jclass jclass, jstring pattern, jint num, jstring path) {
	const char *merge_path = (*env)->GetStringUTFChars(env, path, NULL);
	const char *pattern_path = (*env)->GetStringUTFChars(env, pattern, NULL);

	char **filelist = malloc(sizeof(char*) * num);
	int i = 0;
	for (; i < num; i++) {
		filelist[i] = malloc(sizeof(char) * 100);
		sprintf(filelist[i], pattern_path, i);
	}

	FILE *all_file=fopen(merge_path,"wb");

	i=0;
	for (; i < num; i++) {
		int filesize=getFileSize(filelist[i]);
		FILE *fpr=fopen(filelist[i],"rb");
		int j=0;
		for (; j < filesize; j++) {
			fputc(fgetc(fpr),all_file);
		}
		fclose(fpr);
	}
	fclose(all_file);


	i = 0;
	for (; i < num; i++) {
		free(filelist[i]);
	}

	free(filelist);

	(*env)->ReleaseStringUTFChars(env, pattern, pattern_path);
	(*env)->ReleaseStringUTFChars(env, path, merge_path);

}
