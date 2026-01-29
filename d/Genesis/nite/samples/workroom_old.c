/*
 * File         : /d/Genesis/nite/workroom.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : October 7, 1998          
 * Modifications: 
 * Purpose      : This is Nite's workroom     
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

/* Inherit the basic room functionality and default configuration. */
inherit "/std/room.c";

/* Include the following files as headers to this file. Use the format
 * of <filename.h> in this case, since the location of filename is
 * already predefined. Including "/sys/filename.h" would also work, but
 * it is extremely poor form, as it will not work if ever
 * /sys/filename.h is moved. We want to include this header because of
 * some definitions below.
 */
#include <stdproperties.h>

/* Variable for the pigeon */
object pigeon;

/* Prototype. */
void reset_room();
public string activate_portal();

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    /* Give the room a short description. No need to capitalize. */
    set_short("Nite's workroom");

    /* Give the room a long description. Nothing fancy. */
    set_long("This is Nite's workroom.\nIt is dark here. Water drips " +
      "periodically from the ceiling of the cave. Perhaps it was water " +
      "which bore this room out of the cool rock. Tiny creatures peer " +
      "at you from a myriad of crevices. Something has been carved into " +
      "the west wall. A fire burns in the center of the cave. To the " +
      "north, a swirling portal has been hurriedly erected. A modest " +
      "computer sits on the floor.\n");

    /* Add items. */
    add_item(({"creatures", "tiny creatures"}),
      "They take no notice of you.\n");

    add_item(({"crevice", "crevices"}),
      "Tiny creatures dart in and out of the many corners and " +
      "crevices of the cave's rock walls.\n");

    add_item(({"something", "etching", "etchings", "carving", "carvings",
	"wall", "west wall", "rock"}),
      "Nite has carefully carved out a symbolic representation of " +
      "his proud lineage. Using an ancient dialect, he traces his " +
      "ancestry back to Xi Tpa. Tpa was a founding elder of the " +
      "House of Ghad Tuk, one of the oldest known goblin bloodlines.\n");

    add_item(({"fire", "flame"}),
      "It burns hot with a strange blue flame. Twelve small stones " +
      "are inexplicably suspended in the flame. As you stare " +
      "deeply into the flickering light, a voice deep inside your " +
      "mind says to you, \"Set me free...\"\n");

    add_item(({"stones", "small stones", "eyes", "the eyes", "eyes " +
      "of the six", "the eyes of the six"}),
      "The Eyes of The Six are twelve small spheres which, " +
      "suspended in the blue flame, seem to rhythmically dance " +
      "and careen about each other. The Eyes have been religiously " +
      "guarded for centuries by pure-blooded descendants of the " +
      "House of Ghad Tuk. Many wars have been waged over the Eyes " +
      "as they are believed to be infused with the knowledge and " +
      "powerful magic of The Six. These legendary goblin mages were " +
      "the original founding elders of The House.\n");

    add_item(({"portal", "swirling portal"}),
      "The swirling portal leans haphazardly against the rocky north " +
      "wall. A worn piece of parchment has been scotch taped to the " +
      "frame.\n");

    add_cmd_item("portal", "enter", "@@activate_portal");

    add_item("parchment",
      "On the faded parchment, the words \"Me Pride And Joy\" have " +
      "been sloppily written in purple crayon.\n");

    add_item(({"computer", "modest computer"}),
      "This is Nite's computer. You wonder what it runs on as there " +
      "is no visible power cord. This is where Nite maintains the " +
      "Genesis web site, which is currently visible on the screen.\n");

    add_item(({"screen", "computer screen", "monitor",
      "computer monitor", "home page", "web site", "site"}),
      "On the computer screen, you can see the home page of the " +
      "Genesis web site. What a lovely job Nite has done here!\n");

    add_cmd_item("parchment", "read",
      "On the faded parchment, the words \"Me Pride And Joy\" have " +
      "been sloppily written in purple crayon.\n");

    add_exit("/d/Genesis/wiz/lounge", "east");

    reset_room();
}

void
reset_room()
{
    if (!objectp(pigeon))
    {
	/* Cloning the object */
	seteuid(getuid(this_object()));
	pigeon = clone_object("/d/Genesis/nite/pigeon");
	pigeon->move(this_object(),1);
    }
}

public string
activate_portal()
{
    this_player()->move_living("X", "/d/Genesis/new/start/goblin/town/cavern_c3", 0, 0);
    return "";
}
