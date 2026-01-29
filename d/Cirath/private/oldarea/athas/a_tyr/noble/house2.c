/* house2.c: Rich house 2: Serpine, 04-07-95. */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("noble", ATH_PERSON+"rich_hmn.c", 1, 1);
    bring_room_mob("slave", ATH_PERSON+"slav_hmn.c", 2);
}

void
create_room()
{
    set_short("spherical villa");
    set_long("Apparently either designed or commissioned by one with a "+
             "love of curves, everything in this house appears somewhat "+
             "round. The portraits, the furniture, and even "+
             "the doorway are spheres or ovals of some sort. The whole "+
             "effect serves to make one feel disoriented, as if a "+
             "different world entirely has been entered.\n");

    add_item("furniture", "Other then its unique shape, and a decent "+
             "amount of wood and metal mixed in with the stone, it is "+
             "all pretty unremarkable.\n");

    add_item(({"portraits", "portrait"}), "They appear to be family "+
             "members, dating back many generations. However most "+
             "seem recently crafted, even those of people long "+
             "passed from this world.\n");

    add_item("doorway", "Its round, save for the flat hinged side.\n");

    add_item(({"spheres", "sphere", "ovals", "oval", "circles", "circle"}),
             "They are everywhere! Be more specific.\n");

    INSIDE

    add_exit(TZ_NOBLE+"rd_hr_03.c", "south", 0, 1);
    reset_room();
}
