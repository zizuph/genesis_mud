 /*****************************************************************************
*  /d/Kalad/common/isles/rooms/beast_beach/beast_beach_7.c
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
inherit BEAST_BEACH_STD; 

 /*****************************************************************************
*  Variables
 *****************************************************************************/
object ob1;

 /*****************************************************************************
*  Function name: create_std_beach
*  Description  : Constructor for the room, modify this to change room.
 *****************************************************************************/
create_std_beach()
{   
   set_short("" + B_SE + "");
   set_long("You are standing within a cove on a medium sized beach that "
   + "has fine black sand scattered all about. With a hazy mist gently "
   + "floating about this gives the beach an unnatural sense of gloom. The "
   + "slow ebb and flow of the ocean waves come in from the south. While "
   + "to both your east and west rises a staggered outcrop of rock. And at "
   + "the north end you can see what appears to be a densely packed tree "
	+ "line.\n");
    
   add_exit(BEAST_BEACH + "beast_beach_9","north");
   add_exit(BEAST_BEACH + "beast_beach_8","east");
   add_exit(BEAST_BEACH + "beast_beach_6","west");
   add_exit(BEAST_BEACH + "beast_beach_10","northwest");
	
	 /*************************************************************************
   *  Sets the no exit message for unlisted directions
    *************************************************************************/
   set_no_exit_msg(get_all_no_exits(({"n","e","w","nw"})),
   "The spiraling outcrop blocks your way.\n");
	
   reset_room();
}

 /*****************************************************************************
*  Function name: reset_room
*  Description  : Resets the room
 *****************************************************************************/
reset_room()
{
   object ob1;
   if(!ob1)
   {
      ob1 = clone_object(LIV + "largecrab.c");
      ob1 -> move_living("M",TO);
      tell_room(TO,"A large crab shuffles into view.\n");
   }
}