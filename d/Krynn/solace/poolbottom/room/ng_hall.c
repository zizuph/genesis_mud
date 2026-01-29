#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit POOLBOTTOM_IN;
object door, servant;

void
reset_poolbottom_room()
{
      if(!door->query_locked())
      {
        tell_room(environment(this_object()), "An ethereal servant suddenly appears " +
         "and begins tidying the room.\n");
        setuid();
        seteuid(getuid());
        servant = clone_object(LIVING + "ethereal_servant");
        servant->arm_me();
        servant->move(this_object());
        servant->command("close door");
        servant->command("lock door with key");
        servant->remove_object();
        tell_room(environment(this_object()), "The ethereal servant vanishes, off to clean " +
         "other parts of the school.\n");
       }

	return;
}

create_poolbottom_room()
{
    set_short("Within the great hall of the school of High Magic");
    set_long("You stand at the northern end of the great hall within the school of High " +
       "Magic. To your north in the middle of the high sandstone wall stands an ornate door, " +
       "the entrance to the private residence of the Master of the school. To your west a " +
       "passageway leads to the libraries of the school, while to your east a passageway " +
       "leads to the student's residential area. A grand double staircase rises here to the " +
       "second storey of the school where the observatory and the alchemy labs can be " +
       "accessed.\n");

    add_item(({"ornate door","door","entrance"}),
       "To your north is an ornate door, the entrance to the private residence of Master " +
       "Theobald.\n");

    add_item(({"passageway","passageways","east","west","eastern passageway","western passageway",
       "west passageway","east passageway"}),
       "Passageways leave the great hall to your west to the school's libraries, and to your " +
       "east to the residential area for students.\n");

    add_item(({"library","libraries"}),"Down the passageway to your west are the libraries of " +
       "the school where students study about spellcraft, the forms of magic, and the elements.\n");

    add_item(({"residential area","residential","residentials"}),"Down the passageway to your " +
       "east you will find the residential areas of the students.\n");

    add_item(({"grand double staircase","double staircase","staircase","stairs"}),
       "On either side of the ornate door to your north are the entries to a grand double staircase that " +
       "rises up to the second storey of the school.\n");

    add_item(({"second storey","labs","alchemy labs","observatory"}),
       "By taking the stairs up to the second storey you will be able to access the alchemy " +
       "labs and observatory of the school.\n");        

    add_item(({"school","Poolbottom","school of high magic"}),
       "You stand within the walls of the school of High Magic that resides " +
       "outside the hamlet of Solace. Here aspirants wanting to learn the " +
       "art of sorcery come to learn and train.\n");

    add_item(({"hall","great hall"}),"You stand within the massive great hall of " +
       "Poolbottom, the school of High Magic. Sandstone walls, lined with torches, rise high up to " +
       "the lofty ceiling. " +
       "Long tables also line the walls, providing students a place to study or eat.\n");

    add_item(({"walls","sandstone walls","grey sandstone walls","high sandstone walls",
               "blocks","sandstone blocks","grey sandstone blocks"}),
       "The school has been build from grey sandstone blocks mined from quarries " +
       "far to the south near Pax Tharkas. The workmanship of the walls is seamless, " +
       "most likely done by a master dwarven mason.\n");

    add_item(({"tables","long tables"}),
       "A number of long tables line the walls of the great hall, providing students " +
       "a place where they can study or eat.\n");

    add_item(({"ceiling","lofty ceiling","high ceiling","roof"}),
        "@@exa_ceiling");

    add_item(({"torches","torch"}),"@@exa_torches");
    add_item("extinguished torches","@@exa_extinguished_torches");
    add_item("lit torches","@@exa_lit_torches");

    add_exit(ROOM + "library","west",0);
    add_exit(ROOM + "room","east",0);
    add_exit("/d/Krynn/guilds/sohm/room/joinroom","south",0);
    add_exit(ROOM + "landing","stairs","@@walk_stairs");
    add_invis_exit(ROOM + "landing","up","@@walk_stairs");

    door = clone_object(EOBJ + "theobald_doora");
    door->move(this_object());

    reset_poolbottom_room();
}

int
walk_stairs()
{

    write("You walk up the great double staircase to the second storey.\n");
    TP->move_living("walks up the great double staircase to the second storey", 
        ROOM + "landing",1,0);
    return 1;
}

string
torch_desc()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "lit torches that drive the nighttime shadows up to the lofty ceiling above. ";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "extinguished torches. ";
	    break;
    }
    return str;
}

string
exa_extinguished_torches()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "Looking along the wall, you notice no torch is lit.\n";
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