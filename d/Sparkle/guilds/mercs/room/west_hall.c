/*
 * /d/Genesis/guilds/merc/west_hall, by Morrigan 11/2001
 *
 */
inherit "/std/room";

#include "../merc.h"
#include "room.h"

object guard1;

void
reset_room()
{
    /* They have all left. (Gorboth)
    if (!guard1)
	(guard1 = clone_object(MNPC + "merc_base"))->move(this_object());
    */
}

public string
read_poster()
{
    return "NOTICE:\n\n"+
	"This room is unused, if you can think of a good idea for "+
	"it, let me know.\n";
}

public string
read_door()
{
    return "The plaque reads simply: Mercenary Lords and their "+
	"followers ONLY!\n";
}

int enter_hall()
{
    write(GREAT_HALL_ENTER);
}

int check_allowed()
{
    object me = this_player();
    string lord;

    if (MCREST->query_crest_lord(me->query_name()))
        lord = me->query_name();
    else if (MCREST->query_members_lord(me->query_name()) != "none")
        lord = MCREST->query_members_lord(me->query_name());
    else if (me->id("_mercenary_guild_guard_"))
        return 0;
    else if (me->query_wiz_level())
	return 0;
    else if (me->query_merc_dog())
	return 0;
    else
    {
        write("You knock on the door. A guard sticks his head "+
	   "out briefly to tell you that you are not "+
	   "allowed to enter that part of the hall.\n");
	say(QCTNAME(me)+" knocks on the door. A guard sticks his "+
	   "head out briefly, but refuses to let "+OBJECTIVE(me)+
	   " through.\n");
        return 1;
    }

    if (MCREST->query_lord_status(lord) < MERC_STATUS_ASPIRING)
    {
        write("You knock on the door. A guard sticks his head "+
	   "out briefly to tell you that you are not "+
	   "allowed to enter that part of the hall.\n");
	say(QCTNAME(me)+" knocks on the door. A guard sticks his "+
	   "head out briefly, but refuses to let "+OBJECTIVE(me)+
	   " through.\n");
        return 1;
    }

    write("You knock on the door. It opens from the other side, "+
	"and a guard lets you enter.\n");
    say(QCTNAME(me)+" knocks on the door. It swings open and "+
	PRONOUN(me)+" is allowed to enter.\n");
    return 0;
}
    
int enter_crest_room()
{
    write("You step into a room bustling with activity.\n");
    return 0;
}

public void
create_room()
{
    set_short("An empty hallway");
    set_long(BUILDING_DESC+
        "This is an empty hallway that leads back east to the "+
        "Great Hall, and south into a room from which the sounds of "+
        "busy feet can be heard. There is a small poster on the wall "+
        "here, and a door in the north wall, beside which a small plaque "+
          "has been fastened.\n");


    add_item("door", "The door is in the north wall, upon it is "+
	"a small plaque.\n");
    add_cmd_item("door", "open", "The door is locked.\n");
    add_cmd_item(({"door", "lock"}), "pick", "You start to try to "+
	"pick the lock, but stop at the glance of several unhappy "+
	"guards.\n");
    add_item(({"poster", "sign"}), &read_poster());
    add_cmd_item(({"poster", "sign"}), "read", 
        &read_poster());
    add_item(({"plaque"}), &read_door());
    add_cmd_item(({"plaque"}), "read", &read_door());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1); 
    add_exit(MROOM + "lord_entrance.c", "north", "@@check_allowed", 1, 0);
    add_exit(MROOM + "crest_room.c", "south", "@@enter_crest_room", 1, 0);
    add_exit(MROOM + "great_hall.c", "east", "@@enter_hall", 1, 0);
    reset_room();
}
