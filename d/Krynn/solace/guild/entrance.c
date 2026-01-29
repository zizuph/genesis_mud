/* Entrance to guild hall */
/* Modified by Mucalytic May the 20th '96. */

#include "guild.h"
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit INSIDE_BASE;

void create_solace_room()
{
    set_short("The entrance to the old Solamnian Knight's Guild");
    set_long("You are standing at the entrance of the old Solamnian guild "+
        "hall. This is simply a small hall with an archway leading south to "+
        "another room. These were the secret halls from where the Solamnian "+
        "Knights planned and fought their war against evil. Due to the "+
        "advancing dragon-armies this Hall of Paladine was long ago "+
        "evacuated and all Knights relocated to the safety of Vingaard Keep "+
        "inside the borders of Solamnia.\n");
   
    add_exit(TDIR + "hall1", "south", 0, 1);
    add_exit(PARENT + "road/clearing", "north", 0, 1);

    add_item("archway", "An archway in the south wall, leading to another "+
        "part of the old guild halls.\n");
}
