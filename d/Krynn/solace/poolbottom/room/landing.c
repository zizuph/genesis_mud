#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit POOLBOTTOM_IN;
object mirror;

void
reset_poolbottom_room()
{
       if(!objectp(mirror))
       {
        mirror = clone_object(EOBJ + "mirror");
        mirror->move(this_object());
       }
	return;
}

create_poolbottom_room()
{
    set_short("second storey landing above the great hall of the school of High Magic");
    set_long("You stand at the top of a landing overlooking the great hall within the school of High " +
       "Magic. A grand double staircase leads down from here to the great hall, while the landing " +
       "continues west to the observatory and east to the alchemy labs.\n");

    add_item(({"second storey","labs","alchemy labs","observatory","landing"}),
       "You stand on a landing on the second storey of the school, where you can access the " +
       "alchemy labs and observatory.\n");        

    add_item(({"school","Poolbottom","school of high magic"}),
       "You stand within the walls of the school of High Magic that resides " +
       "outside the hamlet of Solace. Here aspirants wanting to learn the " +
       "art of sorcery come to learn and train.\n");

    add_item(({"hall","great hall"}),"You look down on the massive great hall of " +
       "Poolbottom, the school of High Magic. Sandstone walls, lined with torches, rise high up to " +
       "the lofty ceiling. " +
       "Long tables also line the walls, providing students a place to study or eat.\n");

    add_item(({"walls","sandstone walls","grey sandstone walls","high sandstone walls",
               "blocks","sandstone blocks","grey sandstone blocks"}),
       "The school has been build from grey sandstone blocks mined from quarries " +
       "far to the south near Pax Tharkas. The workmanship of the walls is seamless, " +
       "most likely done by a master dwarven mason.\n");

    add_item(({"ceiling","lofty ceiling","high ceiling","roof"}),
        "@@exa_ceiling");

    add_item(({"torches","torch"}),"@@exa_torches");
    add_item("extinguished torches","@@exa_extinguished_torches");
    add_item("lit torches","@@exa_lit_torches");

    add_exit(ROOM + "observatory","west",0);
    add_exit(ROOM + "alchemy_lab","east",0);
    add_exit(ROOM + "ng_hall","stairs","@@walk_stairs");
    add_invis_exit(ROOM + "ng_hall","down","@@walk_stairs");

    reset_poolbottom_room();
}

int
walk_stairs()
{

    write("You walk down the great double staircase to the great hall.\n");
    TP->move_living("walks down the great double staircase to the great hall", 
        ROOM + "ng_hall",1,0);
    return 1;
}

string
exa_extinguished_torches()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "Looking along the walls of the great hall, you notice no torch is lit.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "Unlit torches line the walls of the great hall, ready to be lit with the " +
            "darkness that comes with nightfall.\n";
	    break;
    }
    return str;
}

string
exa_lit_torches()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "The walls of the great hall are lined with lit torches that dance brightly, " +
            "casting the shadows of night up high to the ceiling, cloaking it in darkness.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "Looking along the wall, you notice no torch is lit.\n";
	    break;
    }
    return str;
}

string
exa_torches()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "The walls of the great hall are lined with lit torches that dance brightly, " +
            "casting the shadows of night up high to the ceiling, cloaking it in darkness.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "Unlit torches line the walls of the great hall, ready to be lit when " +
            "darkness comes with nightfall.\n";
	    break;
    }
    return str;
}

string
exa_ceiling()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "You can make out little detail of the ceiling " +
            "above you, it being cloaked with nighttime shadows.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "High above you is the ceiling of the great hall.\n";
	    break;
    }
    return str;
}