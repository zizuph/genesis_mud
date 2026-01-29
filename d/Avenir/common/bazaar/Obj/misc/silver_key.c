
// file name: silver_key.c
// creator(s): Ilyian, April 1995 (code borrowed from Grace)
// last update:
// purpose: key to the gate between green/s_shore and green/green17
// note:
// bug(s):
// to-do:

inherit "/std/key";
#include "../../bazaar.h"
#include "/sys/stdproperties.h"

create_key() {
    ::create_key();

    set_name("key");
    set_adj(({"silver", "intricate"}));
    set_pshort("large keyrings");
    set_short("silvery key");
    set_long("This is a silvery key, or rather, the stub of one. "+
        "It must have broken off in a lock somewhere.\n");

    set_key("_not_the_gate_key_");

    add_prop(OBJ_I_WEIGHT, 20);    
    add_prop(OBJ_I_VOLUME, 30);  
    add_prop(OBJ_M_NO_STEAL, "You can't quite seem to liberate it.\n"); 
    add_prop(OBJ_I_VALUE, 20);   // its silver
}

