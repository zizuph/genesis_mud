 /*****************************************************************************
*  /d/Kalad/common/isles/std/beast_beach_path_std.c
*
*  STD File: Beach Path area for the Isle of the Beast
*
*  Created June 2019, Greneth
*
*  Info:
*
*  Map of Beach - This is the beach area of the Isle of Beasts
*  where all players will start their adventure after crashing.
*  The beach area offers one quest from Nigel.          
*                                                        
*           0-0-0-0-N         
*          /| | | | |\       
*         0-0-0-0-0-0-0       0-0             
*         | | | | | | |\     /| |\                   
*         0-0-0-S-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0 
*                                 | | | | | | | | | |\
*                                 P-P-P-P-P-P-P-P-P-P-P
*                                      \| | | | | | |/ 
*      S - Starting Point               P-P-P-P-P-P-P
*      N - Nigel (Antiques) - Quest             
*      P - Tide Pool             
*
 *****************************************************************************/

 /*****************************************************************************
*  Pragma
 *****************************************************************************/
#pragma strict_types

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "../local.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/std/room";

 /*****************************************************************************
*  Prototypes
 *****************************************************************************/
public nomask void  create_room();
public void         create_std_beach_path();
public void         add_beach_path_items();

 /*****************************************************************************
*  Strings
 *****************************************************************************/
string smell_air(string str);

 /*****************************************************************************
*  Function name: create_room
*  Description  : Creates the room
 *****************************************************************************/
public nomask void
create_room()
{
   add_prop(ROOM_I_LIGHT, 0);
   add_prop(ROOM_I_INSIDE, 0);
   create_std_beach_path();
   add_beach_path_items();
}

 /*****************************************************************************
*  Function name: create_std_beach_path
*  Description  : Dummy function for inheriting rooms to mask
 *****************************************************************************/
public void
create_std_beach_path()
{
   set_short("a set_short is needed here");
   set_long("A set_long is needed here.\n");
}

 /*****************************************************************************
*  Function name: add_beach_path_items
*  Description  : Adds the standard  exa items for the beach path
 *****************************************************************************/
public void
add_beach_path_items()
{	
   add_item(({"sand", "black sand", "fine sand", "fine black sand"}), 
	"The sand is black, very fine and scattered about the beach.\n");
	
   add_item(({"crevice"}), 
	"Testing\n");
	
	add_item(({"beach"}),
	"A very dim and strange beach covered in black sand and surrounded by "
	+ "a hazy mist.\n");
	
	add_item(({"outcrop", "outcrop of rock", "outcrops", "rock", "rocks"}),
	"Black, volcanic rock is staggered in a swirling, rising pattern "
	+ "that has created almost a full cavern around you.\n");
	
	add_item(({"sky", "misty sky"}),
	"Looking up you realize that the sky cannot be seen due to the thick "
	+ "mist.\n");
	
	add_item(({"mist", "thick mist", "haze", "air", "hazy mist"}),
	"The misty haze in the air is still, thick and stagnant, very little "
	+ "light can be seen causing everyting to look more dull.\n");
}

 /*****************************************************************************
*  Function name: get_all_no_exits
*  Description  : Returns an array of strings with exits for use with 
*                 set_no_exit_msg()
*  Argument     : Array of exits to exclude, for simplicity you can use nw 
*                 instead of northwest, etc.
 *****************************************************************************/
string *
get_all_no_exits(string *exits)
{
   string *r_exits = m_values(NORMAL_EXITS);
   foreach (string exit: exits) {
      foreach (string ind, string val: NORMAL_EXITS) {
         if (exit == ind || exit == val) {
            r_exits -= ({ val });            
         }
      }
   }
   return r_exits;
}

 /*****************************************************************************
*  Function name: init
*  Description  : Adds the smell action
 *****************************************************************************/
public void
init()
{
    ::init();
    add_action(smell_air, "smell");
}

 /*****************************************************************************
*  Function name: smell_air
*  Description  : Describes the smell action
 *****************************************************************************/
int
smell_air(string str)
{
    notify_fail("Smell what?\n");
    if (str != "air" && str != "the air" && str != "area" 
    && str != "the area" && str != "beach")
    return 0;
    
    else
    say(QCTNAME(this_player()) +
    " takes a deep breath, of the air around them and twitches their nose.\n");
    write("You take a deep breath of the air around you, the mist tickles "
	 + "your nose.\n");
    return 1;
}