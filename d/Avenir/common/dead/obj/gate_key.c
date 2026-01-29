// file name: gate_key.c
// creator(s): Ilyian, Oct 15, 1995
// last update:
// purpose: Key to the gate of Cahor. Players should never
//          be able to get a hold of it. Cloned bo Mixcotoc.
// note:
// bug(s):
// to-do:

inherit "/std/key";
#include "../dead.h"
#include "/sys/stdproperties.h"

create_key() {
    ::create_key();

    set_name("key");
    set_adj(({"heavy", "iron"}));
    set_short("heavy iron key");
    set_long("This is a heavy iron key.\n");

    set_key("_cahor_gate_key");
    add_prop(OBJ_I_WEIGHT, 160);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 20);

}
