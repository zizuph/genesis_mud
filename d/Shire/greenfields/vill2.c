inherit "/d/Shire/eastroad/std/vill_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 GREEN_DIR + "vill3","north",0,1
#define EXIT2 GREEN_DIR + "vill1","south",0,1
#define EXIT3 GREEN_DIR + "shop","east",0,1


int do_enter(string str);

void
create_village_room()
{
   areaname = "Greenfields";
   land = "the Shire";
   areatype = 2;
   areadesc = "twisty path";
 
   extraline = "The twisty path becomes hard, packed gravel here, as it leads "+
   "north, farther into the hamlet of Greenfields.  East is a burrow with a huge, "+
   "oak door, standing wide open.  North the twisty gravel path continues into "+
   "Greenfields, while to the south are jagged hills and a twisty dirt path.";

   add_item(({"jagged hills"}),
   "The jagged hills look dim and ominous, in any light.\n");

   add_item(({"twisty path","twisty gravel path","twisty dirt path","path"}),
   "The twisty path follows the curves of the hills to the north and to the "+
   "south.  A few feet to the south, the gravel begins to mix in with the dirt, and "+
   "to the north, the dirt starts to fade a bit.\n");

   add_item(({"dirt","gravel"}),
   "The dirt and gravel combine to separate this path from the lush green "+
   "hillsides.\n");

   add_item(({"hill","hills"}),
   "The hills here are gently rolling and grass covered.  Lush vegetation covers "+
   "them- it is a fertile place.\n");

    add_item(({"burrow","east burrow","shop"}),
   "The burrow to the east is large and tall enough for even elves to enter.  "+
   "The sound of money exchanging hands comes from within.\n");



   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
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
     TP->move_living("M",GREEN_DIR + "shop",1);
     return 1;
    }

   NF("Enter what ? A "+str+" ? You must be kidding!\n");
   return 0;
}
