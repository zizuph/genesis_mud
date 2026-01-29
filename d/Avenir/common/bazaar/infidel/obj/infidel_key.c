// file name: infidel_key.c
// creator(s): Ilyian, Oct 1995
// last update:
// purpose: key to the infidel hideout
// note:
// bug(s):
// to-do:

inherit "/std/key";
inherit "/lib/keep";

#include "../infidel.h"
#include "/sys/stdproperties.h"

create_key() {
    ::create_key();

    set_keep(1);
    set_name("key");
    set_adj(({"brass"}));
    set_pshort("brass keys");
    set_short("brass key");
    set_long("This is a small brass key, with vague "
            +"intricate etchings along the shaft.\n");

    set_key("_infidel_hideout_key_");
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 100);
}

