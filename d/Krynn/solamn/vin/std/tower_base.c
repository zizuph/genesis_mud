/* tower base by Aridor, 09/94, used in the 4 towers of vingaard keep */
/* modifed for New VK, by Teth, 12/96 */
/* Modified so the ladder will repair itself -
/* Damaris@Genesis with help from Cotillion 3/2005
*/
#include "../knight/guild.h"
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;

int ladder = 1;
object guard, guard2;

/*prototype*/
void break_ladder();


/* loads the tower guard */
void
reset_vin_room()
{
    if (!guard)
    {
	guard = clone_object(VSTD + "vin_knight_base");
	guard->move(TO);
	guard->set_block_dir("out");
    }
    if (!guard2)
    {
	guard2 = clone_object(VSTD + "vin_knight_base");
	guard2->move(TO);
	guard2->set_block_dir("out");
    }
}

void
create_tower()
{
}

void
create_vin_room()
{
    object door;

    set_short("Inside a tower");
    set_long("You are standing inside a tower. There is no door out. A " +
      "spiral stairway should lead up to the battlements above.\n");

    add_item(({"keep", "castle", "stronghold"}), "@@keep");
    add_item(({"door", "iron door", "tower door"}), "@@door");
    add_item("ladder", "@@ladder");

    create_tower();
}

/* Allows the player to say the password */
void
init()
{
    ::init();
    ADA("say");
    ADA("kdeclare");
    ADA("coath");
}

void
wave_up(object who)
{
    if ((!guard && !guard2) || (E(guard) != TO && E(guard2) != TO))
	return;
    if (!MEMBER(who))
    {
	who->catch_msg("The guard refuses to let you pass, saying: Only "+
	  "Knights are allowed atop the battlements!\n");
	tell_room(TO, "The guard stops "+QTNAME(who)+" as "+PRONOUN(who)+
	  " tries to pass, saying: Only Knights are allowed atop the "+
	  "battlements!\n", who);
	return;
    }
    if (!ladder)
    {
	who->catch_msg("The ladder here is broken.\n");
	return;
    }
    if (E(who) != TO)
	return;
    who->catch_msg("The guard grins at you and waves you up the ladder.\n"
      + "You climb quickly up the ladder.\n");
    tell_room(TO, QCTNAME(who) + " climbs up the ladder.\n", who);
    who->move_living("M", MASTER + "up", 1);
    tell_room(E(who), QCTNAME(who) + " arrives climbing up the ladder.\n", 
      who);
}

int
coath(string str)
{
    set_alarm(1.0,0.0,"wave_up",TP);
    return 1;
}

int
kdeclare(string str)
{
    if (find_player(TP->query_real_name()))
	set_alarm(1.0,0.0,"wave_up",TP);
    return 1;
}

/* add_action 'say' */
int
say(string str)
{
    string dummy;
    if (!str)
	return 0;

    if (!guard || E(guard) != TO)
	return 0;
    if (!ladder)
    {
	write("The ladder here is broken.\n");
	return 0;
    }
    if (sscanf(L(str),"%sest sularus oth mithas%s", dummy, dummy) == 2 ||
      sscanf(L(str),"%shonour is my life%s", dummy, dummy) == 2 ||
      sscanf(L(str),"%shonor is my life%s", dummy, dummy) == 2)
    {
	set_alarm(1.0,0.0,"wave_up",TP);
	return 1;
    }
    return 0;
}

/* up condition */
int
up()
{
    if (!ladder)
    {
	write("The ladder is broken and you cannot climb up.\n");
	return 1;
    }
    if (!guard || E(guard) != TO)
    {
	if (TP->query_alignment() < 0 && random(2))
	{
	    break_ladder();
	    return 1;
	}
	return 0;
    }
    guard->command("say If you want to pass you must answer this:");
    guard->command("say What is the foundation of my life?");
    return 1;
}


/* add_item descriptions */
string
keep()
{
    write("The keep is very ancient and has withstood the test of time"
      + " just as much as it has withstood numerous battles. The keep is"
      + " the stronghold of the Solamnian Knighthood, a powerful "
      + " organization of warriors devoted to the cause of good.\n");
    return "";
}

string
door()
{
    write("The door is made of iron and looks very solid.\n");
    return "";
}

string
ladder()
{
    if (!ladder)
	return "It looks like it used to be a simple iron ladder, but now " +
	"it is broken through the middle. The top half is just too high " +
	"reach by any means and the bottom half is all useless with all the " +
	"rungs broken and the metal twisted.\n";
    else
	return "It's a simple iron ladder leading up.\n";
}

void
repair_ladder()
{
    ladder = 1;

    tell_room(TO, "A squire arrives carrying a new ladder.\n" + 
        "He quickly replaces the old broken one.\n");
}

void
break_ladder()
{
    ladder = 0;
    tell_room(TO, QCTNAME(TP) + " breaks the ladder leading upwards! " +
      "The lower part of the ladder topples down to the ground " +
      "and the light metal bends and breaks under the weight.\n", TP);
    write("You break the ladder, falling down to the floor. OUCH!\n");
    TP->heal_hp(-50);

    set_alarm(3600.0 + 3600.0 * rnd(), 0.0, &repair_ladder());
}

void
ladder_breaks()
{
    ladder = 0;
    tell_room(TO, "Suddenly, the lower part of the ladder in the room " +
      "topples down to the ground and is all torn and twisted.\n");
}
