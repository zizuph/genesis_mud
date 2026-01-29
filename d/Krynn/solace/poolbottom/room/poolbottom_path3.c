#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/common/clock/clock.h"

inherit POOLBOTTOM_OUT;

void
reset_poolbottom_room()
{
	return;
}

create_poolbottom_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"large stone building","stone building","building",
         "structure","main structure","large building","outline",
         "school","school of high magic",
         "two storey stone building","east wing", "west wing"}),
       "@@far_building");

   add_item("poolbottom","Poolbottom, the name of the private school of High Magic " +
        "just outside of Solace.\n"); 

   add_item(({"second storey"}),"@@second_storey");

    add_item(({"entry","double doors","wooden doors"}),
         "Long steps of grey sandstone lead to the entry of the school of High Magic " +
         "to your north. Tall double doors of thick oak, strengthened with iron bands, " +
         "stand closed before you. On the left door, a copper plaque has been " +
         "fastened with iron studs.\n"); 

    add_item(({"copper plaque","plaque"}),
         "Fastened to one of the double doors is a copper plaque. There is " +
         "writing on it in the common tongue that you could probably read.\n");

    add_item(({"long steps","steps","grey sandstone steps","sandstone steps"}),
         "Long steps of grey sandstone lead to the entry of the school of High Magic " +
         "to your north.\n");

    add_item(({"windows","window","lights"}),
       "@@windows");

    add_item(({"walls","sandstone","stone walls","sandstone walls"}),
       "@@add_item_near_walls");

    add_cmd_item(({"wall","walls","up to window","up","to window"}),"climb",
      "@@climb_wall");

    add_cmd_item(({"doors","door","tall doors","double doors","wooden doors",
           "on door","on doors","on double doors","on tall double doors"}),
           "knock","@@knock_door");
  
    add_cmd_item(({"plaque","copper plaque","writing"}),"read","@@read_plaque");

    add_exit("/d/Krynn/guilds/sohm/room/joinroom","north","@@school_closed");
    add_exit(ROOM + "poolbottom_path2","south",0);

    reset_poolbottom_room();
}

int
school_closed()
{
    write("You push the twin doors open and make your way in to the " +
          "large stone building.\n\n"); 
/*
    write("The School of High Magic is closed while Master Theobald "+
          "is in conclave at the Tower of Wayreth. It will open on his "+
          "return.\n");
*/
    return 0;
}

string
short_descr()
{
    return close_school_desc();
}

string
long_descr()
{
    return long_close_desc()+"\n";
}

string
far_building()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "Before you, rising against the darkness of night like a menacing shadow, " +
              "is Poolbottom, the school of High Magic. The walls of the school are " +
              "dimly illuminated by lights high up in a number of second storey windows, " +
              "while the entrance stands to your north.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "Before you rises a large two storey stone building known as Poolbottom, " +
                  "the school of High Magic. Before you to the north is the entrance, while " +
                  "two wings extending to the east and west of the main structure.\n";
	    break;
    }
    return str;
}

string
second_storey()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "The walls of the school are " +
              "dimly illuminated by lights high up in a number of second storey windows, " +
              "while the entrance stands to your north.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "The walls of the school rise two storeys, with a number of windows " +
              "up high overlooking the path to Solace.\n";
	    break;
    }
    return str;
}

string
windows()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "A number of windows twinkle above you like beacons in the night " +
               "from the second storey of the building.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "A number of windows can be made out high up on the second storey of the " +
               "large building.\n";
	    break;
    }
    return str;
}

string
add_item_near_walls()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "The darkness of night hides most of the details of the walls of the school " +
             "from you.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "The walls of the school of High Magic are of a dark grey sandstone, mined " +
                  "from quarries near Pax Tharkas.\n";
	    break;
    }
    return str;
}

string
knock_door()
{

	write("You knock loudly on the double doors of thick oak, but only a deep echo responds.\n");
	say(QCTNAME(this_player()) + " knocks loudly on the double doors of think oak, but gets no " +
           "response.\n");
	return "";

}

string
climb_wall()
{

	write("You search in vain for possible handholds to make use of to scale the wall. " +
           "The builder who engineered the construction of this school was likely a " +
           "master dwarven mason, and there are no gaps for you to use.\n");
	say(QCTNAME(this_player()) + " attempts to climb the walls of the school, but can find " +
           "no handholds to make use of.\n");
	return "";

}

string
read_plaque()
{
    if(this_player()->query_skill(SS_LANGUAGE) < 10)
    {
	write("Your language skills are too poor to read writing even in the " +
          "common tongue!\n");
	return "";
    }
    write("You read the writing on the copper plaque:\n\n" +
          "       A mage's soul is forged in the crucible of magic.\n"+ 
          "       You choose to go voluntarily into the fire. \n"+
          "       The blaze might well destroy you.\n"+ 
          "       But if you survive, every blow of the hammer will \n"+
          "       serve to shape your being.\n"+ 
          "       Every drop of water wrung from you will temper \n"+
          "       and strengthen your soul. ~ Antimodes\n"+
          "\n");

    return "";
}