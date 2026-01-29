/*
 * the goat's skin
 * for the Ten Alders Goat in Roke
 * Amelia 5/3/97
*/

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("skin");
    add_name("goatskin");
    set_adj("goat");
    add_adj("long-haired");
    set_short("goatskin");
    set_pshort("goatskins");
    set_pname(({"skins", "goatskins"}));
    set_long("The skin from a long-haired goat. It " +
        "is soft and pliable and might be made into " +
        "armour, clothing or other implements.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 25);
}
