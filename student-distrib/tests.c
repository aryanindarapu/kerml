#include "tests.h"
#include "x86_desc.h"
#include "lib.h"

#define PASS 1
#define FAIL 0
#define TEST_VECTOR 14 // Set to IDT vector number OR to 256 for keyboard tests

/* format these macros as you see fit */
#define TEST_HEADER 	\
	printf("[TEST %s] Running %s at %s:%d\n", __FUNCTION__, __FUNCTION__, __FILE__, __LINE__)
#define TEST_OUTPUT(name, result)	\
	printf("[TEST %s] Result = %s\n", name, (result) ? "PASS" : "FAIL");

static inline void assertion_failure(){
	/* Use exception #15 for assertions, otherwise
	   reserved by Intel */
	asm volatile("int $15");
}


/* Checkpoint 1 tests */

/* IDT Test - Example
 * 
 * Asserts that first 10 IDT entries are not NULL
 * Inputs: None
 * Outputs: PASS/FAIL
 * Side Effects: None
 * Coverage: Load IDT, IDT definition
 * Files: x86_desc.h/S
 */
int idt_test(){
	TEST_HEADER;

	int i;
	int result = PASS;
	for (i = 0; i < 10; ++i){
		if ((idt[i].offset_15_00 == NULL) && 
			(idt[i].offset_31_16 == NULL)){
			assertion_failure();
			result = FAIL;
		}
	}

	return result;
}

/*
 *   test_divide_error
 *   DESCRIPTION: Test to see if we probably get a divide by 0 error
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: Will purposely divide by 0 (invalid operation) to see if it triggers interupt
 */ 
int test_divide_error() {
	int a, b, c;
	a = 10;
	b = 0;
	c = a / b;
	return 0;
}

/*
 *   test_page_fault
 *   DESCRIPTION: Testing to see if we page fault when we access an invalid page
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: Will print out error message and interupt should occur
 */ 
int test_page_fault() {
    //Used to test dereference locations.
	uint8_t a;
    uint8_t* p = (uint8_t *) 0x800000; // point to kernel memory
    a = *p;

	printf("pointing to kernel memory");

    //p = (int *) 0x2; 
	//a = *p;
	return PASS;
}

// TODO: add more tests for each interrupt

// add more tests here

/* Checkpoint 2 tests */
/* Checkpoint 3 tests */
/* Checkpoint 4 tests */
/* Checkpoint 5 tests */


/*
 *   launch_tests
 *   DESCRIPTION: begin of tests
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: performs test indicated by TEST_VECTOR
 */ 
void launch_tests() {
	// TEST_OUTPUT("idt_test", idt_test());
	// launch your tests here
	clear();
	switch (TEST_VECTOR) {
		case 0:
			test_divide_error();
			break;
		case 14:
			test_page_fault();
			break;
		case 33:
			asm volatile("int $33");
			break;
		case 40:
			asm volatile("int $40");
			break;
		case 128:
			asm volatile("int $128");
			break;
		default:
			// This just takes it to the keyboard interrupt
			break;
	}
}
