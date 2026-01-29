inherit "/std/room";

#include "/d/Emerald/defs.h"

int fired = 0;

void start_room_move();
void room_move(mixed args);

void
create_room()
{
    object door;

    set_short("Tower ground floor");
    set_long("   A light airy room greets you as you look around, with tiny "+
      "slits for windows. There are some stairs winding upwards, around "+
      "a thick central pillar which must be at least four or five feet "+
      "in diameter. There is a door in the south wall.\n\n");

    add_item( ({ "stair", "stairs" }), "They look like they might hold you.\n");
    add_item("pillar","@@pillar_desc@@");

    add_exit(VILLAGE_DIR + "stairs1", "up", 0);

    door=clone_object(VILLAGE_DIR + "doors/door_a");
    door->move(this_object());
}

string
pillar_desc()
{
    if(!fired)
	return "The pillar is stone, and when you knock your knuckles on it, "+
	"you certainly feel that it is solid.\n";
    else
	return "For some reason, a portion of the floor has fallen away "+
	"revealing a room down below, and there is some rubble on the "+
	"floor beneath your feet which has come from the pillar. Beneath "+
	"a few inches of stone, you can see a copper pillar.\n";
}

void
init()
{
    ::init();
    add_action("do_fire","fire");
    add_action("do_fire","light");
}

int
do_fire(string str)
{
    object ob;

    notify_fail("What are you intending to set fire to?\n");
    if(!strlen(str))
	return 0;

    if(!parse_command(str, environment(this_player()), 
	" %o [at] 'pillar' / 'base' ", ob))
    {
	notify_fail("You want to do what?\n");
	return 0;
    }

    if(member_array(ob, all_inventory(TP)) < 0)
    {
	notify_fail("You do not have the "+ob->query_name()+" on you! What "+
	  "are you expecting to make the fire with, stone?\n");
	return 0;
    }

    if(fired)
	"/d/Emerald/room/village/wood"->start_false_fire();
    else 
	"/d/Emerald/room/village/wood"->start_fire_true();
    fired = 1;
    ob->move(ENV(TP), 1);
    return 1;
}

void
start_room_move()
{
    /* For some reason, if fired isn't declared, then it must be an error	*/
    /* because it needs to be true for the wood to burn, give them a 	*/
    /* notify_fail.							*/
    notify_fail("Something is wrong here, an error has been found.\n");
    if(!fired)
	return 0;

    set_alarm(1.0, 0.0, "room_move", ({ TP, 1 }) );
}

void
room_move(mixed args)
{
    object ob;
    int time;

    if(sizeof(args) != 2)
	return;

    ob = args[0];
    time = args[1];

    switch(time)
    {
    case 1:
	tell_room(TO, "You hear a rumble as something in the tower moves.\n");
	break;

    case 2:
	tell_room(TO, "A thunderous creaking echoes around the room, and the "+
	  "tower seems to shudder slightly. As you look around you notice "+
	  "that the tower seems to dip to the north more and more.\n");
	break;

    case 3:
	tell_room(TO, "You notice that a major portion of the floor is "+
	  "slipping down the copper column, revealing another room below "+
	  "where you are standing.\n");
	break;

    default:
	tell_room(TO, "The grinding stops and the room comes to a halt.\n");
	break;
    }
    set_alarm(10.0, 0.0, "room_move", ({ ob, time + 1 }) );
}





