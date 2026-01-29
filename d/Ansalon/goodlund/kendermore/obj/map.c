/* Piece of metal from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("map");
    add_name("junk");
    add_name("parchment");
    set_adj("old");
    add_adj("tattered");
    set_short("old tattered map");
    set_pshort("old tattered maps");
    set_long("This old tattered map looks like it dates from the Cataclysm!\n");
    add_cmd_item("map", "read", "@@read_map");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 30);
}

string
read_map()
{
    write("You try to decipher the ancient map, but can't make a bit of " + 
        "sense from it. You imagine that only the maker knows what each " + 
        "of the symbols stands for.\n");
    return "";
}

