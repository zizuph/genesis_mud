#include "../local.h"

inherit VILLAGE;

int do_enter(string str);

void
create_village_room()
{
   areaname = "Greenholm";
   land = "the Shire";
   areatype = 2;
   areadesc = "path";
 
   extraline = "The outskirts of the village Greenholm are not very "+
     "different from the center of the village.  A single "+
       "burrow has been carved from the hillside.  East is "+
	 "a shiny new building made of freshly painted wood, "+
	   "and a shiny new sign hangs from the eave.  "+
	     "Southwest will return you to the center of the village.";
   
   add_item(({"shiny new building","building","shop","east building"}),
	    "This relatively large building is made of stone and wood.  The "+
	    "wood has been weathered to a grey-black, nearly matching "+
	    "the dark stone.\n");
   
   add_item(({"wood","freshly painted wood","painted wood","eave"}),
	    "The wood is black pine and has been heavily covered in red paint.  "+
	    "As a result the shop stands out against the green hills of its environs. "+
	    "The eave has a shiny new sign attached to it.\n");
   
   add_item(({"sign","new sign","shiny new sign"}),
	    "The sign shows a large bag of money held by a tall and powerful "+
	    "hobbit.  There is writing above it.\n");
   
   add_item("writing","It is quite legible.\n");
   
   add_cmd_item("sign","read","The sign reads: The Greenholm Trader.\n");
   add_cmd_item("writing","read","The sign reads: The Greenholm Trader.\n");
   
   add_item(({"village","greenholm"}),
	    "This village, named Greenholm "+
	    "is quite small indeed. It consists of only "+
	    "a few burrows and the local trading post.\n");
   
   add_item(({"hobbit holes","holes","hobbit-holes","smials","burrows"}),
	    "The burrows are cut into the eastern hillside, all except one "+
	    "guarded by a big round door.  The nearest burrow's door is open, "+
	    "you could probably enter the burrow.\n");
   
   add_item(({"rolling hills","dales","hills","scene"}),
	    "The rolling hills to the south are covered with grass, and look "+
	    "very comfortable for relaxing.  The pastoral scene of hill and dale "+
	    "makes you sleepy, in fact.\n");
   
   add_item(({"door","big round door","round door"}),
	    "All of the holes in this area seem to be closed off by large "+
	    "round doors, designed in the hobbit fashion.  One reason they "+
	    "might be so big is for the hobbits to get their bellies through "+
	    "the door.\n");
   
   add_exit(GREENHOLM_DIR + "shop","east");
   add_exit(GREENHOLM_DIR + "viln1","southwest");
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
   notify_fail("Enter what ?\n");

   if(!str) return 0;

   if ((str == "burrow") || (str == "smial") || (str == "hobbit hole"))
   {
     write("You enter the open burrow.\n");
     say(QCTNAME(TP)+ " leaves into the open burrow.\n");
     TP->move_living("M",GREENHOLM_DIR + "7",1);
     say(QCTNAME(TP)+ " arrives.\n");
     return 1;
    }

   notify_fail("Enter what ? A "+str+" ? You must be kidding!\n");
   return 0;
}

