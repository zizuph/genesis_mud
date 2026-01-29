/* rd_hr_05: High road section 5: Serpine, 04-22-95. */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
    set_short("southeastern high road");
    set_long("The affluence of the Noble's Quarter begins to die out "+
             "down this lane of the High Road. Once a central part "+
             "of the area, the proximity to the slave pits and Iron Square "+
             "to the southeast has made those nobles that can, move off "+
             "to the northwest. Though not poor by any stretch of the "+
             "imagination, the mansions here are quite unimpressive "+
             "compared to those deeper in. The few plants around do "+
             "little to offset the sun's oppressive heat.\n");

    add_item(({"mansion", "mansions"}), "One particularly run-down "+
             "mansion lies to the west.\n");

    add_item(({"plant", "plants"}), "Ugly and only barely clinging to "+
             "life, they are not unlike most things in Athas.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TZ_NOBLE+"rd_hr_04.c", "northwest", 0, 1);
    add_exit(TZ_NOBLE+"house4.c", "west", 0, 1);
    add_exit(TZ_NOBLE+"rd_hr_06.c", "southeast", 0, 1);
}
