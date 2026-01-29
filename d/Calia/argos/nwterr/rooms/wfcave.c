/* Cave behind the waterfall - no purpose now, just here to pique curiosity
**
** History
** Date        Coder       Action
** --------  ------------  ---------------------------------------------
** 2/22/97   Zima          Created
** 7/12/17   Jaacar        Added Elemental Clerics Racial guild routines
*/

/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define GUILD_MANAGER "/d/Calia/guilds/elementalists/lib/guild_manager"
#define RACIAL_JOINROOM "/d/Calia/guilds/elementalists/specials/racial_joinroom"

public string altar_desc();

/* room definition */
void create_room() {
   set_short("Inside a mysterious cave");
   set_long(
      "Veins of glowing gemstone criss cross the walls of this mysterious "+
      "cave, lighting it with their strange light. Columns have been "+
      "sculpted out of the gray stone all around the circular chamber, "+
      "while a simple stone altar stands in the center of the cave.\n");
 
   add_item(({"veins","gemstone","gemstones"}),
      "Veins of a strange gemstone run through the walls of the cave, "+
      "criss crossing in an erratic woven pattern. They glow a dark "+
      "purplish colour, illuminating the chamber with an eerie light.\n");
   add_item(({"cave","chamber"}),
      "It is a dome-shaped cavern set deep in the mountain. Though "+
      "the shape of the chamber is fairly symmetrical, it has a strange "+
      "sense of naturality to it.\n");
   add_item("columns",
      "They are simple flat, rectangular columns which have been sculpted "+
      "from the walls of the cave. They encircle the dome-shaped chamber.\n");
   add_item("altar","@@altar_desc@@");
 
   /* exits */
   add_exit("wfall1","east",0);
}

public string
altar_desc()
{
    string altar_description = "It is a simple stone altar with a round top, hewn "+
        "of the stone of the mountain. ";
    
    if (GUILD_MANAGER->query_is_full_master(TP))
    {
        altar_description += "You feel a strange, yet at the same time familiar "+
            "energy radiating from it. You feel compelled to touch it. ";
    }
    else
    {
        altar_description += "It looks like it hasn't been used in ages. ";
    }
    
    altar_description += "\n";
    
    return altar_description;
}

public int
do_touch(string str)
{
	int occupied;
	
    if (!GUILD_MANAGER->query_is_full_master(TP))
        return 0;
        
    if (!parse_command(str, TP, " [the] [simple] [stone] 'altar' "))
    {
        notify_fail("Touch what?\n");
        return 0;
    }
    
    occupied = RACIAL_JOINROOM->query_occupied();
    
    if (!occupied)
    {
    	write("You reach out and touch the top of the altar. The energy flows "+
	        "through your body. It becomes so intense that you have to close "+
	        "your eyes. The intensity subsides and when you open your eyes, "+
	        "you realize you are somewhere else.\n\n");
	    say(QCTNAME(TP)+" reaches out and touches the top of the altar. You "+
	        "see "+TP->query_objective()+" close "+TP->query_possessive()+
	        " eyes.\n");
	    TP->move_living("X",RACIAL_JOINROOM,1,0);
	    RACIAL_JOINROOM->set_occupied(1);
	    return 1;
	}

	write("You reach out and touch the top of the altar. The energy flows "+
        "through your body. A voice echos in your mind saying, 'Another "+
        "is already undergoing Symviosi. Please try again in a few minutes.'\n");
    say(QCTNAME(TP)+" reaches out and touches the top of the altar.\n");
        
    return 1;
}

void
init()
{
    ::init();
    add_action(do_touch,"touch");
}
