/* Mortis 11.2005
 * 
 * Views of people north of tr3?
 * Views of what ships are in dock?
 * Old way of using secret hole sucks here and in wall.c.
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit SHIP_BASE;

#define IN_WALL		SHIP + "wall"

int door_open = 0;

string
query_to_jail()
{
  return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Old Circle runs south along the city wall which "
	+ "towers above you to the east.  The wall ends here against a "
	+ "cliff of stone.  You are somewhat high above the piers from "
	+ "this vantage point with a full view of the Bay of Branchala.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The ageworn marble of Old Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above "
	+ "the mountains.  The air is rich with the salty smells from the bay "
	+ "borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The ageworn marble of Old Circle and its buildings "
	+ "gleams in the midday sun as people travel to and from the harbor "
	+ "and noble district filling the street with the noisy murmurings "
	+ "of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Old Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers, merchants, and seamen make their way about the street."
	+ road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Old Circle amplifying the yellow glow of the street lamps.  "
	+ "Few people make their way about here at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
	object gate;

    SHORT("On Old Circle northwest of the Scholar's Gate");
    LONG("@@get_time_desc@@");

	ITEM(({"pier", "piers"}), "Several piers extend out from the docks "
	+ "of Palanthas at which great trading vessels come and go at all "
	+ "hours.  This harbor is extremely busy with the great amount of "
	+ "trade done here.\n");
	ITEM(({"vessel", "vessels", "ship", "ships"}), "Dozens of ships are "
	+ "in port at the docks with several arriving and embarking even now.\n");
	ITEM(({"cliff", "cliffs"}), "A rocky cliff overlooks the piers below.  "
	+ "The city wall ends here where it is no longer necessary to protect "
	+ "the city.\n");
	ITEM("view", "The view of the Bay of Branchala, the docks, and the "
	+ "harbor of Palanthas is clear from this vantage point.  Your vision "
	+ "extends far across the dark blue waters.\n");
	ITEM(({"wall", "city wall", "great wall"}), "The city wall of "
	+ "Palanthas towers high above to your east.  It is faced with "
	+ "large block panels of polished, translucent marble, but atop "
	+ "its crenallated defenses you spot dark grey rock which comprises "
	+ "its core.  The wall is in good shape.\n");
	ITEM(({"facing", "panel", "panels"}), "Thin sheets of polished, "
	+ "translucent marble have been cemented over the stone of the wall "
	+ "to give it a gleaming, white appearance.  As the wall approaches "
	+ "the cliff to the north, its panels have had to be cut into odd "
	+ "shapes to fit flush against it.  The last panel at its base is "
	+ "small and thin.\n");
	ITEM(({"small thin panel", "small panel", "thin panel"}), "This custom "
	+ "cut translucent marble facing is somewhat loose.\n");
	ITEM(({"hole"}), "@@examine_the_hole");
	CMD(({"small panel","thin panel", "small thin panel"}),
		({"pry","push","press"}), "@@secret_door_opens");
	CMD(({"hole"}),({"enter"}), "@@go_into_the_wall");

	EXIT(SHIP + "w02", "south", 0, 0);

}

string
secret_door_opens()
{
    seteuid(getuid(TO));
    if (door_open)
      write("Nothing happens.\n");
    else
	{
		tell_room(IN_WALL,"One of the big stone blocks moves silently "
		+ "into the room, revealing a hole to your west.\n");
		tell_room(TO,"One of the small, thin marble panels moves silently "
		+ "inside the wall, revealing a hole.\n");
	  door_open = 1;
	  add_exit(IN_WALL,"east");
	  set_alarm(25.0,0.0,"secret_door_closes");
      }
    return "";
}

void
secret_door_closes()
{
    if (!door_open)
      return;
	tell_room(IN_WALL,"One of the big stone blocks moves silently back " +
	"into the wall, closing the hole.\n");
    tell_room(TO,"One of the small, thin marble panels moves silently out "
	+ "from inside the wall, closing the hole.\n");
	door_open = 0;
	remove_exit("east");
	(IN_WALL)->remove_exit("west");
}


string
go_into_the_wall()
{
    if (!door_open)
      {
	  write("What?\n");
	  return "";
      }
	write("You enter the hole and find yourself in a small dark room "
	+ "inside the city walls.\n");
    say(QCTNAME(TP) + " leaves into the hole in the city wall.\n");
    TP->move_living("into the hole",IN_WALL, 1, 0);
    return "";
}


string
examine_the_hole()
{
	if (door_open)
      return "It's a hole into the city wall. Inside you can't see "
	+ "anything since it's dark there. You think it's large enough that "
	+ "you can fit through.\n";
    else
      return "You find no hole.\n";
}


int
query_door_open()
{ return door_open; }

