#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

inherit OUTER_OUT;

void
create_neraka_room()
{
    set_short("backyard of a pawnshop in Neraka");

    set_extra_long("You are standing in the backyard of a pawnshop. " +
		"All sorts of crates are stacked by the wall providing " +
		"some shelter from the weather and unwanted " +
		"attention.");


    set_quarter(RED);

    add_exit(NOUTER+"red/r18","northwest",0,0,0);

    add_item(({"backyard", "area", "sheltered area"}) , "It is a small " +
        "area at the back of the " +
        "pawnshop. Litter and some crates are stacked next to the "+
        "wall.\n");

    add_item(({"litter", "trash"}), "Scraps of paper, rotting " +
        "fruit, a large brown button and many more discarded things " +
        "that someone left here.\n");

    add_item(({"scraps", "scraps of paper"}), "Little pieces of paper "+
        "that probably were brought here by the wind or have fallen from " +
        "crates.\n");

    add_item(({"fruit", "rotting fruit"}), "Decay made its point " +
        "here and the fruit is now nothing more but slime.\n");

    add_item(({"button", "large button", "brown button",
        "large brown button"}), "Nothing better then to loose "+
        "a button from the pants. Someone must have been in a hurry " +
        "and forgot to pick it up.\n");

    add_item(({"shop", "pawnshop", "building"}),
	"It is a fairly large building with solid, stone walls. "+ 
	"In fact there might not be many buildings in Neraka that "+
	"would have been made so sturdy. Crates are stacked near the wall to " +
        "provide some shelter.\n");

    add_item(({"wall", "walls"}), "In front of you, to the north, you see "+
	"the back wall of a pawnshop. It is made of large stones, "+
	"probably transported here from nearby mountains. In the middle of "+
	"the wall there is a set of doors with no lock or even a door-knob. "+
	"It seems that someone has to open them for you from the inside. "+
	"Also, dozens of crates are placed next to the wall forming some sort of "+
	"a sheltered area. Shelter from the weather or something " +
        "else?\n");

    add_item("stones", "Fairly large chunks of rock, probably brought here "+
	"from the mountains. Someone made a lot of effort to form "+
	"quite a solid walls out of them.\n");

    add_item("mountains", "All around the valley you see the peaks of the " +
	"Taman Busuk mountain range. In the far distance, a pass weaves its"+
	" way through them.\n");

    add_item(({"doors", "door"}), "In the wall, someone placed a " +
        "set of doors that would "+
	"allow anyone to bring goods inside the shop without too "+
	"much of unwanted attention. There is no doorknob or lock on "+
	"the doors.\n");

   add_item("crates", "All sorts of wooden crates are stacked up " +
        "next to the wall. " +
        "Almost indecipherable notes are places " +
        "on some of them.\n");

   add_item("notes", "Most of them are covered with dirt and not "+
       "much can be read out. When you look through them " +
       "the word \"Flotsam\" catches your attention.\n");

}

int
open_door(string str)
{
     NF("Open what?\n");

     if(!str)
      return 0;

     if (str == "door" || str == "doors")
     {
	write("Since there is no doorknob, you try to push the doors " +
	      "inward but without much success. They must " +
              "be bolted from the inside.\n");

	return 1;
     }

     return 0;
}

int
knock_door(string str)
{

    NF("Knock on what?\n");

    if (!str)
     return 0;

    if (str == "on door" || str == "on doors")
    {
       write("You knock on the doors but no one answers your call.\n");
       return 1;
    }

    return 0;
}

void
init()
{
    ::init();

    add_action("open_door", "open");
    add_action("knock_door", "knock");

}

