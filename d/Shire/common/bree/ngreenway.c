#include "defs.h"
#include "/d/Shire/trickster/trickster.h"

inherit "/d/Shire/std/room";

void
create_shire_room()
{
   set_short("On the old North Road northwest of Bree");
   
   set_long("@@my_long@@");
   
   add_item(({"hill","bree-hill"}),
      "You see the steep slopes of Bree-hill on this side, and in "+
      "the south-east you can see a lane winding towards some holes.\n");
   add_item(({"holes","lane"}),
      "Well, as it is quite far, you see nothing special of interest.\n");
   add_item(({"road","greenway"}),
      "This is the continuation of the Greenway to the north, and you "+
      "can understand why it is called so, because grass grow on it.\n");
   add_item("grass",
      "Well, surely since grass grow here, it cannot be used so much.\n");
   add_item(({"dike","hedge"}),
      "The people in the town have obviously made some sort of protection "+
      "against the wild. They have not built walls, but dug a deep "+
      "trench or dike with a thick hedge on the inner side. The "+
      "dike surrounds the town.\n");
   
   add_exit("/d/Gondor/arnor/greenway/nr1", "north", 0);
   add_exit(STAND_DIR + "cross", "south", 0);
   add_exit(STAND_DIR + "ngate", "southeast", "@@no_enter");
}

int
no_enter()
{
   if (IS_MEMBER(TP))
      {
      write("You quickly jump into the well concealed hole and into " +
         "the safety of the Trickster's secret entrance.\n");
      TP->move_living("into a hole", TRICK_DIR + "s_enterance");
      return 1;
   }
   write("You cannot enter the small opening, because it is blocked with "+
      "sturdy gates.\n");
   return 1;
}

void
init()
{
   ::init();
   add_action("do_enter","enter");
   add_action("do_enter","jump");
}

int
do_enter(string str)
{
   if (!IS_MEMBER(TP))
      {
      NF("What?\n");
      return 0;
   }
   if (!str)
      {
      NF("Enter what?\n");
      return 0;
   }
   if (str == "opening" || str == "hole" || str == "concealed hole")
      {
      write("You quickly jump into the well concealed hole and into " +
         "the safety of the Trickster's secret entrance.\n");
      TP->move_living("into a hole", TRICK_DIR + "s_enterance");
      return 1;
   }
   write("Enter the hole maybe?\n");
   return 1;
}

string
my_long()
{
   string  str;
   
   str = "You are walking on the Old North road west of Bree-Hill. "+
   "The road leads south to the crossing of the Great East Road "+
   "and the Greenway. In the southeast you see the town of Bree "+
   "and in that direction a small road leads into a small opening in "+
   "a hedge on the other side of a dike. This dike and hedge "+
   "must serve as an attempt to protect the village with physical "+
   "obstructions.";
   
   if (IS_MEMBER(TP))
      {
      str += " Well hidden in the southeast is a well concealed hole "+
      "which is the Trickster secret entrance.  If you were not shown "+
      "the location of this hole you would have surely missed it.\n";
   }
   else
      {
      str += "\n";
   }
   return str;
}
