#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#define SIZE 5
/*
    Data Structure for Data of Birth

    Project Name: Kernel Module (Data Structure)
    Group Members:
	     Muhammad Hamza 2016-UET-NML-CS-28
	      Umer Farooq 2016-UET-NML-CS-17
	       Ammar Farooq Khan 2016-UET-NML-CS-20

         This is our operating system module project in which we write a simple
Linux kernel module. In which we use Linux kernel data structure and build a
small Queue. That queue can store a complete record of a person/employee in Kernel space.
This record will store in kernel space.

*/

struct BirthDay {
    int Day;
    int Month;
    int Year;
    struct list_head list;
};

static LIST_HEAD(BirthDay_list);

int Days[SIZE]={02,15,30,22,11};
int Months[SIZE]={02,06,03,10,12};
int Years[SIZE]={1998,2000,1997,1992,2002};

/* This function is called when the module is loaded. */
int KernelDataStructure_init(void){
    printk(KERN_INFO "Storing My friends Date of Birth in List\n");
    //struct BirthDay *MyFriends;
    int i;
    //struct BirthDay *MyFriends;
    for(i=0; i<SIZE; i++){

        struct BirthDay *MyFriends;
        // gfp_t flags the type of memory to allocate.
        // GFP_KERNEL - Allocate normal kernel ram. May sleep.
        MyFriends = kmalloc(sizeof(*MyFriends),GFP_KERNEL);

        MyFriends->Day = Days[i];
        MyFriends->Month =Months[i];
        MyFriends->Year = Years[i];

        list_add_tail(&MyFriends->list, &BirthDay_list);
        //printk(KERN_INFO "BIRTHDAY: Month: %d Day: %d Year: %d\n",MyFriends->Month,MyFriends->Day,MyFriends->Year);
    }

    /* Traversing the list */
	printk(KERN_INFO "Traversing birthday list\n");
    struct BirthDay *ptr, *next;
    list_for_each_entry_safe(ptr, next, &BirthDay_list, list) {
        printk(KERN_INFO "BIRTHDAY: Month: %d Day: %d Year: %d\n",ptr->Month,ptr->Day,ptr->Year);
	}

    printk(KERN_INFO "Muhammad Hamza\n");
    return 0;
}

/* This function is called when the module is removed. */
void KernelDataStructure_exit(void){
    struct BirthDay *ptr, *next;
    printk(KERN_INFO "Delete the DataStructure\n");
    list_for_each_entry_safe(ptr, next, &BirthDay_list, list) {
    //printk(KERN_INFO "BIRTHDAY: Month: %d Day: %d Year: %d\n",ptr->Month,ptr->Day,ptr->Year);
        // delete structs and return memory
    list_del(&ptr->list);
    kfree(ptr);
    }
}


/* Macros for registering module entry and exit points. */
module_init(KernelDataStructure_init);
module_exit(KernelDataStructure_exit);
MODULE_LICENSE("MIT");
MODULE_DESCRIPTION("KernelDataStructure Module");
MODULE_AUTHOR("Muhammad Hamza");
