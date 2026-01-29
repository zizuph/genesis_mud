 /*****************************************************************************
* /d/Kalad/common/guilds/fishing/rooms/s_pier2.c
*
* Pier Entrance
*
* Map of Pier
*
*        #0#
*        #|#         G - Fishing Guild
*        #0#         # - Water
*    ## # | # ##
*    #0-0-0-0-0#
*    ## # | # ##
*         G
*		 
*		 
* Created June 2018, Greneth
 *****************************************************************************/

 /*****************************************************************************
*   Includes
 *****************************************************************************/
#include "/d/Kalad/common/guilds/fishing/defs.h"

 /*****************************************************************************
*   Inherits
 *****************************************************************************/
inherit F_SPIER;

 /*****************************************************************************
*   Prototypes
 *****************************************************************************/
public void create_std_southpier();

 /*****************************************************************************
* Function name: create_std_southpier
*
* Description  : Constructor for the room, modify this to change room.
 *****************************************************************************/
public void
create_std_southpier()
{
   set_short("A long pier in the southern port area.");
   set_long("You are on a large pier in the southern port area. It was made "
	+"wide enough to accommodate a few people walking up and down it at the "
	+"same time and is supported by giant Kalad Redwood pilings. To the south "
	+"the pier extends further out into the sea, while to the north it leads "
	+"back to the Port area.\n");

	add_exit(F_ROOM + "s_pier4.c", "west");
 
    /*************************************************************************
   *  Sets the no exit message for unlisted directions
    *************************************************************************/
   set_no_exit_msg(get_all_no_exits(({"n","s"})),
   "You would fall off the pier in that direction.\n");
 
   reset_room();
}