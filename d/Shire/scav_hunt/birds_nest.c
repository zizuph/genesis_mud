/* 
 * Bird's nest
 * -- Finwe, September 2003
 */
  
inherit "/std/object";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    seteuid(getuid());
    set_name("nest");
    add_name("_shire_birds_nest_");
    set_adj("birds");
    set_adj("old");
    set_short("old birds nest");
    set_long("This is "+short()+". It was made of small twigs and " +
        "round shaped. The inside is lined with mosses and soft bird " +
        "feathers. The nest looks like it was made last season and " +
        "fell from a nearby tree. It is battered and many of the " +
        "twigs broken. The nest looks like it is ready to fall apart.\n");
    add_item(({"feathers", "bird feathers", "soft bird feathers", 
            "soft feathers"}),
        "The feathers are dirty but white colored. They are small and " +
        "line the inside of the nest. The appear to have been plucked " +
        "from the breast of birds as they look soft and downy.\n");
    add_item(({"twigs", "broken twigs"}),
        "The twigs are small and woven into a round nest. Many of " +
        "them are broken and moss-covered. Some of the twigs hang " +
        "from the nest as if they are ready to fall off the nest.\n");
    add_item(({"mosses", "moss"}),
        "They are light green, and line the inside of the nest. Most " +
        "of the moss has fallen out of the nest, but it still remains " +
        "in the nest in patches. Gray mosses grow on some of the " +
        "twigs. It looks ugly and unassuming.\n");

	add_prop(OBJ_I_WEIGHT, 50);
//check volumes
	add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);
}
