#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit POOLBOTTOM_IN;
object cabinet, cupboard, armour, weapon, wand, staff, misc;

void
reset_poolbottom_room()
{
    if(!objectp(misc))
    {
	misc = clone_object(EOBJ + "misc_rack");
	misc->move(TO);
    }
    if(!objectp(cabinet))
    {
	cabinet = clone_object(EOBJ + "leftover_cabinet");
	cabinet->move(TO);
    }
    if(!objectp(cupboard))
    {
	cupboard = clone_object(EOBJ + "herb_cupboard");
	cupboard->move(TO);
    }
    if(!objectp(armour))
    {
	armour = clone_object(EOBJ + "armour_rack");
	armour->move(TO);
    }
    if(!objectp(weapon))
    {
	weapon = clone_object(EOBJ + "weapon_rack");
	weapon->move(TO);
    }
    if(!objectp(wand))
    {
	wand = clone_object(EOBJ + "wand_shelf");
	wand->move(TO);
    }
    if(!objectp(staff))
    {
	staff = clone_object(EOBJ + "staff_rack");
	staff->move(TO);
    }
}

create_poolbottom_room()
{
    set_short("storage chamber of the school of High Magic");
    set_long("You stand in a large chamber within the eastern wing of the school of " +
       "High Magic. Here you find a range of racks, cupboards, chests, cabinets and " +
       "shelves where weird and wonderful items are stored.\n");

    add_item(({"walls","sandstone walls","grey sandstone walls","high sandstone walls",
               "blocks","sandstone blocks","grey sandstone blocks"}),
       "The school has been build from grey sandstone blocks mined from quarries " +
       "far to the south near Pax Tharkas. The workmanship of the walls is seamless, " +
       "most likely done by a master dwarven mason.\n");

    add_exit(ROOM + "room","north",0);

    reset_poolbottom_room();
}