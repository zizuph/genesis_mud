/* Black disk used at sacrifical altar to Nuitari - Arman 2017     */


inherit "/std/object";
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

public void
create_object()
{
    set_name("disk");
    add_name("_WoHS_black_sacrificial_disk");
    set_short("midnight black disk");
    set_adj(({"midnight","black"}));
    set_long("A small circular disk of pure black onyx. It seems unusually " +
        "cold in your hand.\n");

    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 502);
    add_prop(OBJ_I_VALUE, 455);

    add_prop(MAGIC_AM_ID_INFO, ({ "This black disk has been enchanted by " +
                                  "dwarven dark savants of the Theiwar " +
                                  "clan, to be used as an offering to " +
                                  "the god known as the Devouring Dark, " +
                                  "the Nightreaver, the Ungod - Nuitari, " +
                                  "God of Black Magic.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

}
