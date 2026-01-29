/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a cavern. The walls are much smoother here than " +
	     "in most of this cavern, and a huge lever is sticking out " +
	     "of the south wall.\n");
    
    add_exit(TURNB,"north","@@if_open");
    
    DARK;

    add_item("lever",
	     "It's a long lever protruding from the wall, and it looks " +
	     "inviting. You almost get the urge to pull it.\n");
    add_cmd_item("lever", "pull", "@@fall_down");
}


int
if_open()
{
    if ((TURNB)->query_exit_direction() == "south")
      return 0;
    write("You find that it is impossible to leave the room as the door ends in a brick wall!\n");
    return 1;
}

string
fall_down()
{
    object para;
    write("You pull the lever and just as soon as you have done so, you are sure " +
	  "it was a mistake!\n");
    SAYBB(" pulls the lever.");
    seteuid(getuid(TO));
    set_alarm(3.0,0.0,"fall_down2", TP);
    return "";
}

void
fall_down2(object who)
{
    if (E(who) != TO)
      return;
    who->catch_msg("The floor opens beneath you and you faaaaaaaaaall..........\n");
    tell_room(TO,"A hole in the floor opens.\n",who);
    who->command("scream");
    who->move_living("falling down the hole in the floor", THEIWAR + "r0", 1, 1);
    tell_room(E(who),({ METNAMEI(who) + " arrives falling down from above.",
			CTNONMET(who) + " arrives falling down from above.",
			"" }), who);
    set_alarm(3.0,0.0,"fall_down3", who);
}

void
fall_down3(object who)
{
    who->move_living("falling further down", THEIWAR + "r1", 1, 0);
    tell_room(E(who),({ METNAMEI(who) + " arrives falling down from above.",
			CTNONMET(who) + " arrives falling down from above.",
			"" }), who);
    tell_room(TO, "The hole closes again silently.\n");
    who->catch_msg("With a THUD! you land on the hard stone floor. Ouch!\n");
    TP->heal_hp(-100);
    tell_room(E(who)," hits the hard stone floor with a loud THUD!", who);
}
