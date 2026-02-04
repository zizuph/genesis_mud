/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP       this_player()
#define TO       this_object()
#define BSN(xx)  break_string(xx+"\n", 70)

create_object()
{
    set_name("ember");
    add_name(MYSTIC_EMBER);
    set_adj("small");
    set_long(BSN(
        "It's a small ember."
    ));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 0);
}
