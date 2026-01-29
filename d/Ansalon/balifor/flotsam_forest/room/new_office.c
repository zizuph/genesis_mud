#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>
#include <ss_types.h>

inherit FOREST_IN;
object knight;

#define DOOR_OPEN "_room_my_door_is_open"

void
reset_flotsam_room()
{
    if(!objectp(knight))
    {
	knight = clone_object(FNPC + "darryn");
	knight->arm_me();
	knight->move(TO);
    }
}

create_flotsam_room()
{
    set_short("Office");
    set_long("@@long_descr");

    add_item(({"office","room"}),"@@long_descr");
    add_item(({"desk","mahogany desk","papers","reports"}),
      "An old mahogany desk sits in the middle of the room, covered " +
      "with reports and papers.\n");
    add_item(({"crack", "door", "doorway"}), "@@crack_desc");
    add_item(({"tapestry","back wall"}), "@@tapestry_desc");

    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_exit(FROOM + "hall","east",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in an office, used by the Knights " +
    "Circle based outside of Flotsam. A mahogany desk sits in the centre " +
    "of the room, with a tapestry of a sword surrounded by roses hangs " +
    "on the back wall.\n";
}

string
tapestry_desc()
{
    string str = "On the back wall is a " +
    "magnificent tapestry. It depicts two of the symbols of the " +
    "Knighthood, a rose curled around an elegant sword.\n";

    if (TP->query_skill(SS_AWARENESS) >= 45)
	return str + "Your sharp eyes notice a crack in the wall behind "+
	"the tapestry, and you realize the tapestry covers a hidden "+
	"doorway!\n";

    return str;
}

void init()
{
    add_action("knock_door", "knock");
    ::init();
}

int
is_knight()
{
    if (TP->query_guild_name_occ() != "Solamnian Knights")
    {
	write("You are shoved back as you try to enter the secret "+
	  "hallway by the guards on the other side of the wall.\n");
	say(QCTNAME(TP)+" is shoved back as "+PRONOUN(TP)+" tries "+
	  "to enter the secret hallway to the west.\n");
	return 1;
    }

    write("The guards salute you as you pass into the secret hallway "+
      "of this Circle of Knights.\n");
    return 0;
}

void
close_wall()
{
    remove_exit("west");
    remove_prop(DOOR_OPEN);
    tell_room(TO, "The tapestry-covered back wall closes again, and the "+
      "sound of stone grinding against stone echoes through the room.\n");
}

int
open_wall(object ob)
{
    NF("The door is already open!\n");
    if (query_prop(DOOR_OPEN))
	return 0;

    if (ob->query_guild_name_occ() != "Solamnian Knights")
    {
	ob->catch_msg("A very small peep hole opens in the wall, "+
	  "and a gruff voice shouts: You had best leave, you do "+
	  "not belong here.\n");
	tell_room(E(ob), "A very small peep hole opens in the wall, "+
	  "and a gruff voice shouts: You had best leave, you do "+
	  "not belong here.\n", ({ ob }));
	return 1;
    }

    add_prop(DOOR_OPEN, 1);
    add_exit(FROOM + "secret_hallway", "west", "@@is_knight");
    ob->catch_msg("A very small peep hole opens in the wall, then "+
      "closes again. A moment later, the wall swings open, revealing "+
      "a hidden passageway to the west.\n");
    tell_room(E(ob), "A very small peep hole opens in the wall, then "+
      "closes again. A moment later, the wall swings open, revealing "+
      "a hidden passageway to the west.\n", ({ ob }));
    set_alarm(5.0, 0.0, "close_wall");
    return 1;
}

int
knock_door(string str)
{
    NF("What ?\n");
    if (!str)
	return 0;

    NF("Knock on what?\n");
    if (str != "door" && str != "on door" && str != "back wall" &&
      str != "on back wall" && str != "tapestry" && str != "on tapestry")
	return 0;

    write("You knock on the back wall of the room, realizing it is not "+
      "as ordinary as it appears to be.\n");
    say(QCTNAME(TP)+" knocks on the tapestry-covered back wall.\n");
    set_alarm(1.0, 0.0, "open_wall", TP);
    return 1;
}

string
crack_desc()
{
    if (TP->query_skill(SS_AWARENESS) <= 45)
	return "You find no crack.\n";

    return "You notice that the wall is slightly cracked along the "+
    "edges of the tapestry, and suddenly realize that the tapestry "+
    "is covering a secret doorway.\n";
}

