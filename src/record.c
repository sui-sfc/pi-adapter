#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pulse/error.h>  /* pulseaudio */
#include <pulse/simple.h> /* pulseaudio */

#define APP_NAME "pulseaudio_sample"
#define STREAM_NAME "rec"
#define DATA_SIZE 1024

int main() {
    int pa_errno, pa_result, written_bytes;

    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16LE;
    ss.rate = 48000;
    ss.channels = 1;

    pa_simple *pa = pa_simple_new(NULL, APP_NAME, PA_STREAM_RECORD, NULL, STREAM_NAME, &ss, NULL, NULL, &pa_errno);
    if (pa == NULL) {
        fprintf(stderr, "ERROR: Failed to connect pulseaudio server: %s\n", pa_strerror(pa_errno));
        return 1;
    }

    char data[DATA_SIZE];
    while (1) {
        pa_result = pa_simple_read(pa, data, DATA_SIZE, &pa_errno);
        if (pa_result < 0) {
            fprintf(stderr, "ERROR: Failed to read data from pulseaudio: %s\n", pa_strerror(pa_errno));
            return 1;
        }
        written_bytes = write(STDOUT_FILENO, data, DATA_SIZE);
        if (written_bytes < DATA_SIZE) {
            fprintf(stderr, "ERROR: Failed to write data to stdout: %s\n", strerror(errno));
            return 1;
        }
    }

    pa_simple_free(pa);
    return 0;
}
