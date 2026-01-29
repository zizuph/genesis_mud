 /*****************************************************************************
*  /d/Kalad/common/sewers/rooms/first_floor/f101.c
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
inherit SEWERS_STD;

 /*****************************************************************************
*  Function name: create_std_beach
*  Description  : Constructor for the room, modify this to change room.
 *****************************************************************************/
create_std_sewers()
{
   set_short("" + B_SW + "");
   set_long("You are in a dirty sewer\n");
      
    
    /*************************************************************************
   *  Sets the no exit message for unlisted directions
    *************************************************************************/
   set_no_exit_msg(get_all_no_exits(({"n","ne","e"})),
   "The sewer walls block your way\n");
    
   set_alarm(1.0,0.0,"reset_room");
}