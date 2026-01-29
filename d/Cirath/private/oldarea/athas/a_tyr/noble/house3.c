/* house3.c: Rich house 3: Serpine, 04-08-95 */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("noble", ATH_PERSON+"rich_hmn.c", 2, 1);
    bring_room_mob("slave", ATH_PERSON+"slav_hmn.c", 3);
}

void
create_room()
{
    set_short("pristine mansion");
    set_long("This sprawling mansion is perfectly clean from top to "+
             "bottom. All the shelves are carefully sorted, all the "+
             "linen perfectly white, and the everpresent sand of Athas "+
             "seems to have gone into retreat. That such order exists "+
             "in a place people live is absolutely amazing. "+
             "You shiver when you realise why: Slaves can be killed or "+
             "tortured if they fail to do their jobs well. You start "+
             "to eye the southern exit.\n");

    add_item(({"shelves", "shelf"}), "Fine items, but all marked with "+
             "a symbol and thus not worth stealing.\n");

    add_item("linen","Definitely cleaned in water rather than sand.\n");

    add_item("sand", "Aren't you listening? There isn't any!\n");

    INSIDE

    add_exit(TZ_NOBLE+"rd_hr_04.c", "south", 0, 1);
    reset_room();
}
