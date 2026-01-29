// file name: 3g_key
// creator(s): 
// last update:
// purpose:      key to the Third Gate
//               cloned by gatekeeper3.c
// note:
// bug(s):
// to-do:

inherit "/std/key";
#include "../../bazaar.h"
#include "/sys/stdproperties.h"

void
create_key() 
{
    ::create_key();

    set_name("key");
    set_adj(({"sturdy", "little"}));
    set_short("sturdy little key");
    set_long("This sturdy little key opens the lock to the "+
        "Third Gate of Sybarus.\n");

    set_key("_avenir_third_gate_key_");

    add_prop(OBJ_I_WEIGHT, 10000);    
    add_prop(OBJ_I_VOLUME, 10000);  
    add_prop(OBJ_M_NO_STEAL, "You can't quite seem to liberate it.\n"); 
    add_prop(OBJ_I_VALUE, 1000);   // its an important key
}

