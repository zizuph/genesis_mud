#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
inherit "/d/Shire/std/room/room_tell";
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "nw";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_er_room()
{
    set_area("outside the Forsaken Inn between the Chetwood "+
      "and the Midgewater Marshes on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("open field");
    set_grass("wet long");
    set_treetype("oak");

    set_extraline("The dense oak forest swallows up the road to your "+
      "northwest, where in all other directions the view is pretty clear, "+
      "except to the far east where you can make out the pall hanging "+
      "over the Midgewater Marshes. Standing glumly on the south side of "+
      "the road is the Forsaken Inn, a ruined shadow of its former glory "+
      "of hundreds of years ago. The road continues to the northwest "+
      "and east from here.");

    add_item(({"inn","forsaken inn"}),
      "Lurking over the Great East Road here is the famous Forsaken "+
      "Inn. Hundreds of years ago it was a favourite drinking hole "+
      "for the many folk of Arnor travelling from one place to "+
      "another, but since the destruction of Fornost the Inn has "+
      "fallen into ruin.\nIts once healthy and strong timber is now "+
      "cracked and grey, and most of the roof shingles have crumbled "+
      "and cracked, allowing free flow of rain to run through to the "+
      "ground floor and wreak a slow havoc there. The front door of "+
      "the Inn is locked and barred, but you can make out a hole in "+
      "the west wall from where you can enter the Inn.\n");
    add_item(({"hole","wall","west wall"}),
      "An apparent weakness in the west wall of the Inn has allowed "+
      "further decay, now leaving a fairly large hole. Seeing that "+
      "the front door is locked and barred, you can use the hole to "+
      "enter the Inn.\n");
    add_item(({"forest","chetwood","oak forest"}),
      "The ancient oaks of the Chetwood swallow up the Great East road "+
      "with the heavy tree cover almost plunging the forest into "+
      "darkness.\n");
    add_item(({"pall","marshes","midgewater marshes"}),
      "All that is visible of the Midgewater Marshes from this distance "+
      "is the haze hanging over the horizon, and the occasional whiff "+
      "of the foul smell of rotten gasses.\n");

    set_room_tell_time(30);
    add_room_tell("A gust of cool wind blows by, and the timbers of the "+
      "Forsaken Inn emit an eerie groan.\n");
    add_room_tell("One of the window shutters slams against the wall, "+
      "startling you.\n");
    add_room_tell("You feel a thud as something crashes nearby.\n");
    add_room_tell("A faint rumbling like singing reaches your ears.\n");
    add_room_tell("You hear a deep-throated roar that must have come "+
      "from inside the Inn.\n");
    add_room_tell("From inside the Inn you hear a loud splash.\n");

    add_exit(ER_DIR + "erb5",  "northwest", 0, 1);
    add_exit(ER_DIR + "erb7",  "east", 0, 1);
    /*  add_exit(ER_DIR + "erb5s", "west", 0, 2, 1);
	add_exit(ER_DIR + "erb6n", "north", 0, 2, 1);
	add_exit(ER_DIR + "erb6s", "south", 0, 2, 1); */

}

public void
enter_inv(object ob, object from)
{
	string *names;
	::enter_inv(ob, from);
	names = ob->query_names();
	if(ob->id(npc_name))
	{
		if (!move_alarm || !sizeof(get_alarm(move_alarm)))
		{
			move_alarm = set_alarm(50.0 + rnd() * 20.0, 0.0, &move_patrol(ob));
		}
	return;
	}
}

void init()
{
    ::init();
    add_action("enterinn", "enter");
}

int enterinn(string inn)
{
    notify_fail("Enter what?\n");

    if (inn!="inn") return 0;
    write("You slip through the hole in the west wall and enter "+
      "the Forsaken Inn.\n");
    say(QCTNAME(TP)+" enters the Inn through a hole in the west wall.\n");

    TP->move_living("into the Inn", "/d/Shire/eastroad/eastern/inn1");

    return 1;

}
