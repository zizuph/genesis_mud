#pragma save_binary

#include "local.h"

inherit EAST_ROAD;

int do_enter(string str);

void
create_er_room()
{
   area = "not far";
   areaname = "Undertowers";
   land = "Eriador";
   areatype = 10;
   areadesc = "tiny hamlet";
   grass = "green";

   extraline = "The tiny hamlet of Undertowers lies scattered "+
                     "about the Great East Road.  Several hobbit-holes "+
                     "or smials are cut into the hills here, some large "+
                     "and a few small.  Farther south, you see great "+
                     "rolling hills and dales, a scene that continues "+
                     "in all directions except north, where the East "+
          "Road runs from Grey Havens to Bree.";

   add_item(({"hamlet","undertowers"}),
   "This hamlet, named Undertowers for the elven towers "+
   "to the west, is quite small indeed. It consists of only "+
   "a few burrows.\n");

   add_item(({"hobbit holes","holes","hobbit-holes","smials","burrows"}),
   "The burrows are cut into the western hillside, all except one "+
   "guarded by a big round door.  The nearest burrow's door is open, "+
   "you could probably enter the burrow.\n");

   add_item(({"door","big round door","round door"}),
   "All of the holes in this area seem to be closed off by large "+
   "round doors, designed in the hobbit fashion.  One reason they "+
   "might be so big is for the hobbits to get their barrels of beer through "+
   "the door.\n");

   add_item(({"rolling hills","dales","hills","scene"}),
   "The rolling hills to the south are covered with grass, and look "+
   "very comfortable for relaxing.  The pastoral scene of hill and dale "+
   "makes you sleepy, in fact.\n");

   add_item(({"towers","elven towers"}),"The three elven towers are visible "+
   "to your west, and to get a closer view, you should head that direction.\n");
   add_exit(EAST_R_DIR + "er3","north");
   add_exit(EAST_R_DIR + "er2s","west",0,1,1);
   add_exit(EAST_R_DIR + "er4s","east","@@enter_shire@@",1,1);
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

   if ((str == "burrow") || (str == "smial") || (str == "hobbit hole"))
   {
     write("You enter the open burrow.\n");
     say(QCTNAME(TP)+ " leaves into the open burrow.\n");
     TP->move_living("M",VILLAGE_DIR + "ut/ut1a",1);
     return 1;
    }

   write("Enter what ? You must be kidding!\n");
   return 1;
}

void enter_shire()
{
    write("You cross the West Farthing border and enter the Shire.\n");
}