#pragma save_binary
#pragma strict_types

#include "/d/Shire/herald/herald.h"
#include "local.h"

inherit EAST_ROAD;

#define UT_DIR "/d/Shire/eastroad/village/ut/"

int do_enter(string str);

void
create_er_room()
{
    area = "not far";
    areaname = "Undertowers";
    land = "Eriador";
    areatype = 10;
    areadesc = "hamlet";
    grass = "green";

    extraline = "The tiny hamlet of Undertowers lies scattered "+
    "about the Great East Road. Several hobbit-holes "+
    "or smials are cut into the hills here, mostly small "+
    "ones. To the north stretch endless rolling hills, "+
    "that go on to the horizon. The Great East Road is "+
    "south, and some fields are to the east and west.";

    add_item(({"hamlet","undertowers"}),
      "This hamlet, named Undertowers for the elven towers "+
      "to the west, is quite small indeed. It consists of only "+
      "a few burrows.\n");

    add_item(({"hobbit holes","holes","hobbit-holes","smials","burrows"}),
      "The burrows are cut into the western hillside, all except one "+
      "guarded by a big round door. The nearest burrow's door is open, "+
      "you could probably enter the burrow.\n");

    add_item(({"rolling hills","dales","hills","scene"}),
      "The rolling hills to the south are covered with grass, and look "+
      "very comfortable for relaxing. The pastoral scene of hill and dale "+
      "makes you sleepy, in fact. To your north the hills become more " +
      "steep, however you think you could navigate your way through them " +
      "in that direction.\n");

    add_item(({"towers","elven towers"}),"The three elven towers are visible "+
      "to your west, and to get a closer view, you should head that " +
      "direction - or perhaps head north into the rolling hills to find " +
      "a higher vantage point.\n");

    add_item(({"door","big round door","round door"}),
      "All of the holes in this area seem to be closed off by large "+
      "round doors, designed in the hobbit fashion.  One reason they "+
      "might be so big is for the hobbits to get their bellies through "+
      "the door.\n");

    add_exit(HERALD_DIR + "path1","north",0,2,1);
    add_exit(EAST_R_DIR + "er3","south");
    add_exit(EAST_R_DIR + "er2n","west",0,1,1);
    add_exit(EAST_R_DIR + "er4n","east","@@enter_shire@@",1,1);
}

void
init()
{
    ::init();
    add_action("do_enter","enter");
}

int
do_enter(string str)
{

    if (!str)
	return 0;
    if ((str == "burrow") || (str == "smial") || (str == "hobbit hole"))
    {
	write("You enter the open burrow.\n");
	say(QCTNAME(TP)+ " leaves into the open burrow.\n");
	TP->move_living("M",UT_DIR + "5",1);
	return 1;
    }

    write("Enter what ? A "+str+" ? You must be kidding!\n");
    return 1;
}

void enter_shire()
{
    write("You cross the West Farthing border and enter the Shire.\n");
}