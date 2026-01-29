/* The graveyard
*Dorak's attempts :)
 * 'o_grave0.c'
 * If that's Eiram's bat, then royalties are due
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
#include <std.h>

inherit GRAVE_STD;

void
create_solace_room()
{
    set_short("Old Graveyard");
    set_long("There are old and new graves here.\n");

	add_item("graves", 
		"There are old and new gravesd.  Which do you look at?\n");
	add_item(({"old graves", "old grave"}),
		("Moss makes it impossible to read the old ones.\n" +
		"Perhaps the Keeper will clean them some day.\n"));
    add_item("new graves", "@@graves");
    add_item("new grave", 
        "If you want to read what's written on a new grave, try 'read' \n" +
        "'name'on gravestone.  (look at new graves for names)\n");
    add_cmd_item(({"on", "grave"}), "read", "@@grave_look");

    add_exit(TDIR + "fence0","south","@@south_msg");
    add_exit(TDIR + "o_grave1","east","@@eastd_msg");
    set_alarm(10.0,0.0,"batsay");
}

south_msg()
{
	write("Death is in the air!\n");
    return 0;
}

east_msg()
{
	write("Shhhh!, here comes one now (slurp!)!!\n");
     return 0;
}
  
query_grave_room() { return 15; }/* plus 1 each room */

void
batsay()
{
     write("A bat flapped its wings as it passed over your head.\n");
}
