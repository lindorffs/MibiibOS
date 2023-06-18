#include <builtins/free.h>

#include <memory.h>
#include <utils.h>
#include <os.h>

extern memoryAllocationUnit memoryUnits[32];
extern u_int number_assigned;
extern d_u_int last_assigned;

void free_hook(void) {
	char assigned[5], used[5];
	itoa(number_assigned, assigned);
	itoa(last_assigned, used);
	os_print("Allocated Units: ");
	os_print(assigned);
	os_print(". Allocated Memory: ");
	os_print(used);
	os_print(" Bytes\n");
	for (u_int i = 0; i < number_assigned; i++) {
		char number[5];
		itoa(i, number);
		os_print(number);
		os_print(": ");
		os_print(memoryUnits[i].name);
		os_print("\n");
	}
}
