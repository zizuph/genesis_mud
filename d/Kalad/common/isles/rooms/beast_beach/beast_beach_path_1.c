 /*****************************************************************************
*  /d/Kalad/common/isles/rooms/beast_beach/beast_beach_path_1.c
*
*  Room File: Beach area for the Isle of the Beast
*
*  Created June 2019, Greneth
*
 *****************************************************************************/

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "../local.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit BEAST_BEACH_PATH_STD; 

 /*****************************************************************************
*  Function name: create_std_beach_path
*  Description  : Constructor for the room, modify this to change room.
 *****************************************************************************/
create_std_beach_path()
{   
   set_short("" + B_P + "");
   set_long("You are on a small path hidden inside the rising outcrop of "
   + "rocks. The mist drops down from the small crevice above partially "
   + "obstructing your view. Heading down will lead back to the beach "
   + "while that path continues to the east.\n");
    
   add_exit(BEAST_BEACH + "beast_beach_path_2","east");
   add_exit(BEAST_BEACH + "beast_beach_8","down");
	
	/*************************************************************************
   *  Sets the no exit message for unlisted directions
    *************************************************************************/
   set_no_exit_msg(get_all_no_exits(({"e","d"})),
   "You bump against the rock with your body but go nowhere.\n");
	
   reset_room();
}