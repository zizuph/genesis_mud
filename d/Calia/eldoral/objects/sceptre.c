/*
 * sceptre.c
 * 
 * This object is the 'key' for getting into the caverns beneath
 * Castle Chimera that lead to the north ravine.
 *
 * Khail, Feb 5/97
 */
#pragma strict_types

#include "defs.h"

inherit "/std/object";

public int
is_eldoral_chimera_sceptre()
{
    return 1;
}

public void
remove_sceptre(object ob)
{
    tell_room(environment(ob), "The silver sceptre suddenly " +
        "vanishes in a flash of blue light.\n");
    remove_object();
}

public void
create_object()
{
    set_name("sceptre");
    set_adj("long");
    add_adj("silver");
    set_long("This long, silver sceptre is relatively plain, " +
        "about half a meter long, with no markings at all " +
        "along the handle. At the head of the sceptre is a " +
        "small silver sculpture of a chimera.\n");

    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_S_WIZINFO,
        "This sceptre is a 'key' to opening a passage into the " +
        "caverns beneath Eldoral. It must be inserted into a " +
        "slot in the floor in /d/Calia/eldoral/ruins/catacomb_6, " +
        "and will open the doorway into the caverns.\n");
    add_prop(MAGIC_AM_MAGIC, ({20, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
        ({"An image forms in your mind of the sceptre " +
          "transforming into a chimera.\n", 10,
          "You see the chimera facing a massive wall.\n", 30,
          "As the chimera charges the wall, it smashes through " +
          "and passes beyond into darkness.\n", 50}));
    add_prop(OBJ_M_NO_BUY, 1);
}
