#define NOB_IMPLEMENTATION
#include "nob.h"

#define CFLAGS "-Wall", "-Wextra", "-pedantic", "-O2"
#define CFLAGS_DEBUG "-Wall", "-Wextra", "-ggdb", "-pedantic", "-O2"

int main(int argc, char **argv)
{
	NOB_GO_REBUILD_URSELF(argc, argv);

	if(argc > 1){ //nob day01 d
		const char *nob_exec = nob_shift_args(&argc, &argv);
		const char *program = nob_shift_args(&argc, &argv);
		Nob_Cmd cmd = {0};
		nob_cmd_append(&cmd, "cc");
		if(argc > 0){
			const char *debug = nob_shift_args(&argc, &argv);
			if(strcmp(debug, "d") == 0){
				nob_cmd_append(&cmd, CFLAGS_DEBUG);
			} else {
				nob_log(NOB_ERROR, "You wanted to debug? Use 'd'");
				return 1;
			}
		} else {
			nob_cmd_append(&cmd, CFLAGS);
		}
		const char *filename = strcat(strdup(program), ".c");
		nob_cmd_append(&cmd, filename);
		if(!nob_cmd_run_sync(cmd)) return 1; //compile
		
		cmd.count = 0;
		
		nob_cmd_append(&cmd, "./a.out");
		if(!nob_cmd_run_sync(cmd)) return 1; //run
	} else {
		nob_log(NOB_ERROR, "Missing arguments...");
	}
	return 0;
}
