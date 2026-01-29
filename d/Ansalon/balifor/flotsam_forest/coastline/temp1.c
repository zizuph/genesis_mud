#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>

inherit FOREST_OUT;
object guard;
int guardian = random(3);

void
reset_flotsam_room()
{
    if(!objectp(guard))
    {
	if(guardian == 0)
	{
	    guard = clone_object("/d/Ansalon/private/guardian2");
	    guard->move(TO);
	}
	if(guardian == 1)
	{
	    guard = clone_object("/d/Ansalon/private/guardian3");
	    guard->move(TO);
	}
	if(guardian == 2)
	{
	    guard = clone_object("/d/Ansalon/private/guardian1");
	    guard->move(TO);
	}
    }
}

create_flotsam_room()
{
    set_short("Outside the entrance to a lost temple");
    set_long("@@long_descr");

    add_item(({"entrance","archway"}),
      "This doorless arched entrance is the beginning of a " +
      "vaulted passage that leads into the temple.\n");
    add_item(({"temple","lost temple","grand temple","structure",
	"noble structure"}),
      "This grand and ancient temple has been built with four " +
      "wings projecting from its center, so that from above " +
      "the temple must like like a four-leafed clover.\n");
    add_item("wing","Projecting from the center of the " +
      "temple are four wings.\n");
    add_item(({"marble","greying marble"}),
      "The high marble walls of the temple seem to have greyed " +
      "over time. Or perhaps this greying is just an effect " +
      "of contrast against the white mist that swirls around " +
      "the temple.\n");
    add_item(({"sea of mist","mist","swirling white mist",
	"white mist"}),
      "White mist swirls around the temple, making the structure " +
      "look like it is sitting in the clouds. An ancient stone " +
      "path leads into to the mist to the west.\n");
    add_item(({"ancient stone path","stone path","path"}),
      "This stone path was obviously crafted with great care, " +
      "as each stone fits perfectly into place. The path " +
      "leads east into the temple and west into the mist.\n");
    add_item(({"dome","rose-coloured dome"}),
      "The dome that graces the top of the temple would have " +
      "been an awe inspiring piece of artwork in its time. " +
      "Now cracked and faded, it only inspires a sense of loss " +
      "to the world.\n");

    add_exit(CROOM + "mist13","west",0);
    add_exit(CROOM + "temp2","east","@@no_go");

    reset_flotsam_room();
}

string
long_descr()
{
    return "Before you stands the open archway entrance to " +
    "a grand temple of greying marble. Looking older than " +
    "the mountains themselves, it stands with quiet dignity " +
    "in a sea of mist, as if supported by the clouds. Indeed, " +
    "it looks like a house of the gods, yet the hand of " +
    "time has still affected this noble structure. Its " +
    "elaborate rose-coloured dome is badly cracked, with " +
    "sections of the dome having disappeared completely. " +
    "An ancient stone path leads east into the temple, and " +
    "west into the swirling white mist.\n";
}

int
no_go()
{
    write("The stone guardian stops you from entering the " +
      "temple.\n");
    say("The stone guardian stops " +QTNAME(TP)+ " from " +
      "entering the temple.\n");
    return 1;
}
