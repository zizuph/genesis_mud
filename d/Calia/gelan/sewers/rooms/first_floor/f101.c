 /*****************************************************************************
*  /d/Calia/gelan/sewers/rooms/first_floor/f101.c
*
*  Description: Gelan Sewers
*
*  Created Aug 2021, Greneth
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
*  Function name: create_std_newbie
*  Description  : Constructor for the room, modify this to change room.
 *****************************************************************************/
create_std_sewers()
{
   set_short("" + S_W + "");
   set_long("You are in a tunnel that runs from the west to east. The west "
   + "is blocked off by a sturdy grate where the source of water comes from "
   + "while to the east the tunnel continues. Small holes can be seen at "
   + "the base of the walls that deposits waste into the slow moving sewage "
   + "cannal.\n");

   add_exit(FIRST_FLOOR + "f102","east");     
    
 /*****************************************************************************
*  Sets the no exit message for unlisted directions
 *****************************************************************************/
   set_no_exit_msg(get_all_no_exits(({"e","w"})),
   "Oof! You run into the wall.\n");
    
   set_alarm(1.0,0.0,"reset_room");
}