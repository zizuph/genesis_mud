inherit "/d/Shire/std/clone_handler";
 
#include "/d/Shire/sys/defs.h"
//#include "defs.h"

#define ANNUMINAS_DIR   "/d/Shire/annuminas/"
#define ANPC_DIR        (ANNUMINAS_DIR) + "monsters/"

 
void
create_clone_handler()
{
    set_default_area(ANNUMINAS_DIR);
    add_clone(ANPC_DIR + "g_orc", 1, 25);
    add_clone(ANPC_DIR + "w_orc", 2, 10);
    add_clone(ANPC_DIR + "uruk",  3, 5);

//    add_clone(ANPC_DIR + "yagluk", 3, 1);

    set_clone_handler_id("Annuminas Clone Handler");
} 
