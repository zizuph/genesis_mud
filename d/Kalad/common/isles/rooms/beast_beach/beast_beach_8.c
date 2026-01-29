 /*****************************************************************************
*  /d/Kalad/common/isles/rooms/beast_beach/beast_beach_8.c
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
    
   add_exit(BEAST_BEACH + "beast_beach_9","northwest");
   add_exit(BEAST_BEACH + "beast_beach_7","west");
   
    /*************************************************************************
   *  Sets the no exit message for unlisted directions
    *************************************************************************/
   set_no_exit_msg(get_all_no_exits(({"nw","w"})),
   "The spiraling outcrop blocks your way.\n");
	
   reset_room();
}

 /*****************************************************************************
*  Function name: do_climb
*  Description  : Lets the player climb to the upper beach
 *****************************************************************************/
int
do_climb(string str)
{
   notify_fail("What?\n");
   if (!strlen(str))
   {
      return 0;
   }
    
   if (!parse_command(str, TP, " [the] [black] 'rock' / 'rocks' / 'outcrop' "))
   {
      return 0;
   }

   if (TP->query_skill(SS_CLIMB) < 30)
   {
      write("You attempt to scale the rocks, but find that you are not "
      + "skilled enough in climbing to make it to the top.\n");
		
      return 1;
   }

    set_dircmd(str);    
    write("You nimbly scale the rocks and make it to the top.\n");
    tell_room(environment(TP), QCTNAME(TP)+" scales "+
        "the rocks and makes it to the top.\n",TP);
    TP->move_living("M", BEAST_BEACH+"beast_beach_path_1.c");
    tell_room(environment(TP), QCTNAME(TP) + " arrives, climbing up from "
        + "the rocks below.\n",TP);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_climb,"climb");
}