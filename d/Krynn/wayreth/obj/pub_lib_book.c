/*
 * A standard book used in the library of Solamnian Knights
 * Made by Nick
 *
 * Copied by Jeremiah 95/06/30, for the use in the libraries
 * in the Tower of Hight Sorcery in Wayreth forest.
 */

inherit "/std/scroll";
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/wayreth/tower/pub_lib.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

string file;

void
create_scroll()
{
    set_name("book");
    add_name("lib_book");

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 500);
}
