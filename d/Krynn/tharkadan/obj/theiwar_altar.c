/* Sacrifical altar to Nuitari - Arman 2017     */


inherit "/std/object";
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

public void
create_object()
{
    set_name("altar");
    add_name("_theiwar_altar");
    set_short("spherical black altar");
    set_adj(({"spherical","black"}));
    set_long("Before you squats a spherical black altar that seems to " +
             "devour the light and radiate intense darkness. It " +
             "reminds you strongly of a small black moon in a starless " +
             "night sky.\n");

    add_prop(OBJ_I_VOLUME, 40000);
    add_prop(OBJ_I_WEIGHT, 50200);
    add_prop(OBJ_I_VALUE, 45500);
    add_prop(OBJ_M_NO_GET, "The altar is far too big to pick up and " +
         "carry.\n");
    add_prop(OBJ_M_NO_STEAL, 1);

    add_prop(MAGIC_AM_ID_INFO, ({ "This is an altar of the dark dwarves " +
                                  "dedicated to the Devouring Dark, the " +
                                  "Nightreaver, the Ungod - Nuitari, God " +
                                  "of Black Magic.\n", 10, "Those who " +
                                  "sacrifice certain objects to Nuitari " +
                                  "may be favoured with a reward.\n", 25, 
                                  "Nuitari desires such items as " +
                                  "enchanted dark disks crafted in the " +
                                  "image of his moon, multi-hued disks " +
                                  "crafted in the image of the Night " +
                                  "of the Eye, fallen pieces of his " +
                                  "celestial body, and the braids of " +
                                  "stone giants.\n", 45 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

}
