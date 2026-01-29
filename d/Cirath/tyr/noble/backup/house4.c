/* house4.c: Rich house 4: Serpine, 04-22-95 */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("noble", TYR_NPC+"rich_hmn.c", 2, 1);
    bring_room_mob("slave", TYR_NPC+"slav_hmn.c", 1);
}

void
create_room()
{
    set_short("fallen estate");
    set_long("For every noble in the lap of luxury there are two just "+
             "barely clinging to the lifestyle they are accustomed to. Bad "+
             "investments, poor betting, or just plain laziness has "+
             "brought down the owners of this once proud house. Empty "+
             "walls and dust are all that's left now. That and their "+
             "foolish conviction that it is just a temporary setback.\n");

    add_item(({"wall", "walls", "empty wall", "empty walls"}), 
               "They are as empty as hopes for a better tommorow.\n");
              
    add_item("dust", "It's dust. And there is a lot of it.\n");

    INSIDE

    add_exit(TYR_NOBLE+"rd_hr_05.c", "east", 0, 1);
    reset_room();
}
