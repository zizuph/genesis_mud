/* created by Aridor 06/21/93
 *
 * This room contains a donation column (/d/Genesis/obj/donation/column)
 */

#include "../local.h"

inherit STREET_BASE

#include <macros.h>
#include "fountain_drink.h"

object cler;
object column = 0;

string
query_to_jail()
{
  return "north";
}

void
reset_palan_room()
{
    if (!column)
    {
	column = clone_object("/d/Genesis/obj/donation/column");
	column->move(TO);
    }

/*
    if (cler)
      return;
    cler = clone_object(LIV + "cleric");
    cler->move(TO);
*/
}

void
create_palan_room()
{
    set_short("The Central Plaza");
    set_long("@@my_long");

    add_cmd_item(({"line","in"}),({"stand","wait"}),"@@wait_forever");

    add_exit(ROOM + "street17","northwest",0,1);
    add_exit(ROOM + "street20","west",0,1);
    add_exit(ROOM + "street10","southwest",0,1);
    add_exit(ROOM + "street3","south",0,1);
    add_exit(ROOM + "street4","southeast",0,1);
    add_exit(ROOM + "street6","east",0,1);
    add_exit(ROOM + "street12","northeast",0,1);
    add_exit(PALACE + "palace1","north","@@palace_closed",0);

    add_item(({"palace","tower"}),
	     "It's truly a magnificent palace which is topped by the white " +
	     "tower. The palace makes up the entire north side of the " +
	     "plaza, its front is also painted white and many windows " +
	     "look out onto the plaza.\n");
    add_item(({"window","windows","front"}),
	     "The windows on the palace front are painted in different but " +
	     "still decent colors, giving the building a friendly and " +
	     "peaceful appearance.\n");
    add_item(({"fountain","statue","man"}),
	     "You see that the fountain is really a statue, a man with his " +
	     "hands above his head, and water pouring from his hands. The " +
	     "statue is plated with gold, and it sparkles brightly in the " +
	     "sunlight.\n");
    add_item(({"water","hand","hands","head"}),
	     "You cannot see anything special.\n");
    add_item(({"plaza"}),
	     "It's a large plaza on which you are standing. Crowds of " +
	     "people are all around you, pushing and shoving you. In the " +
	     "middle of the plaza is a fountain.\n");
    add_item(({"people","crowd","crowds"}),
	     "All these people here! There is a very long line of people, " +
	     "but also everywhere else on the plaza you can see people " +
	     "strolling around, minding their business.\n");
    add_item(({"line"}),
	     "It is a very long line of people, winding itself across the " +
	     "plaza. The line seems to lead inside the palace.\n");

    add_cmd_item( ({ "water", "from fountain", "water from fountain" }), 
        "drink", drink_water);
        
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    
    reset_room();
}


int
palace_closed()
{
    if ((present("iletter", TP)) || (TP->query_wiz_level()))
      {   
	  write("The palace guard steps out of his cabin and says: " +
		"\"It is a great honour to have you here.\"The guard " +
		"bows deeply before you and beckons you to enter.\n");
	  return 0;
      }
    write("A palace guard steps out of his cabin to say: \"The Lord " +
	  "of Palanthas has auditions today, so please wait in line " +
	  "until it is your turn!\n\n");
    return 1;
}


string
my_long()
{
    string desc = "Wow, this Plaza is truly impressive. It is unmistakably " +
      "the center of the city, there are crowds of people pushing and " +
      "shoving you. You just hope all your money is safe. Actually you " +
      "wonder about these people since there is nothing on the plaza " +
      "except a fountain, water sparkling golden in the sun. Towering the " +
      "plaza to the north is the Palace with its magnificent white tower " +
      "glistening in the sun and radiating warmth.\n";
    return desc;
}

int
wait_forever()
{
    write("You stand in line. It seems this might take a while.\n");
    say(QCTNAME(TP) + " stands in line.\n");
    TP->move_living(0,ROOM + "line");
    return 1;
}


