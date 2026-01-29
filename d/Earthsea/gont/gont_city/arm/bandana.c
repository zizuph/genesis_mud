// fixed the name, didn't change the file...

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

#define COLOURS ({ "red", "green", "purple", "red-striped", "orange", \
    "white", "yellow", "purple-polkadotted", \
})

public void
create_armour()
{
    string colour = COLOURS[random(sizeof(COLOURS))];
    set_name("bandana");
    set_adj(colour);
    set_short(colour + " bandana");
    set_long("A bright " + colour + " bandana, "+
        "typically worn around the neck by sailors.\n");
    set_at(A_NECK);
    set_ac(20);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 35);
}
