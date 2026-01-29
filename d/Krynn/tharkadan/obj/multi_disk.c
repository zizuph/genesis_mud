/* Multi disk used at sacrifical altar to Nuitari - Arman 2017     */


inherit "/std/object";
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

public void
create_object()
{
    set_name("disk");
    add_name("_WoHS_multi_sacrificial_disk");
    set_short("multi-hued disk");
    set_adj(({"multi-hued","multi-hued"}));
    set_long("This is a small disk carved from a unique agate of three " +
        "hues. Examining it you get the disturbing impression that you " +
        "are holding a large white eye with a red iris and black " +
        "pupil.\n");

    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 502);
    add_prop(OBJ_I_VALUE, 3455);

    add_prop(MAGIC_AM_ID_INFO, ({"This rare multi-hued disk has been " +
                                 "carefully carved by dark dwarf " +
                                 "gemcutters to create a representation " +
                                 "of the Night of the Eye - an event " +
                                 "where all three moons of magic " +
                                 "come into conjunction. This disk is " +
                                 "usually used as an offering by dark " +
                                 "savants to the god known as the " +
                                 "Devouring Dark, the Nightreaver, the " +
                                 "Ungod - Nuitari, God of Black " +
                                 "Magic.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

}
