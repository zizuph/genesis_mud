/*  /d/Faerun/neverwinter/rooms/1o.c
*
*   By Thessius, 2020
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_NEWERW_OUTDOOR;


void
create_neverw_outdoor()
{
    extraline = "You are in a southern part of the easter alleys. The "
	+"alley opens back up to a main street to the northwest. Many people "
	+"dash back and forth as quickly as they can past the opening to the "
	+"alley, fearing for that they might have something of value stolen "
	+"from them. A few ruffians and rapscallions lean upon the walls of "
	+"the buildings lining the populated street, licking their lips "
	+"and flipping their daggers, eyes darting back and forth, intent on "
	+"finding their next victim.";
    
    set_short("Somewhere in the eastern alleys of Protector's Enclave");
    
    //If we want herbs here.
    //add_std_herbs("mere");
        
    add_item(({"ruffians", "rapscallions"}),
       "The various ne'erdowells lick their lips as they eye you, "
       +"looking you up and down. They gauge the weight of the coin "
       +"you possess, drawing their daggers as you get closer to "
       +"them.\n");
	   
    add_item(({"alley"}),
       "The alley is clearly worn down and treated as a place where "
       +"several ne'erdowells and hooligans conspire as to who might "
       +"be robbed come nightfall. Most merchants and nobles avoid the "
       +"alleys like the plague, hugging their coin purse close to "
       +"their bodies.\n");
	   
    add_item(({"street"}),
       "The street, although not the main street of Protector's Enclave, "
	   +"is bustling with activity.");

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "n6.c", "northwest");
    add_exit(ROOM_DIR + "nae2.c", "south");
}


void
reset_faerun_room()
{
    set_searched(0);
}