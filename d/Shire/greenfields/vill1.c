inherit "/d/Shire/eastroad/std/vill_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 GREEN_DIR + "path1","southwest",0,1
#define EXIT2 GREEN_DIR + "vill2","north",0,1
#define EXIT3 EVENDIM_DIR + "ev7","east",0,1


int do_enter(string str);

void
create_village_room()
{
   areaname = "Greenfields";
   land = "the Shire";
   areatype = 2;
   areadesc = "path";
 
   extraline = "This field, dotted with small green bushes and covered "+
   "in tall grass, is a calm tranquil spot.  The rolling hills wrap you in "+
   "a veil of comfort and peace.  A hobbit burrow is dug into the side of "+
   "a round hill here.  North lies the hamlet of Greenfields, and southwest "+
   "a path leads into a steeper set of hills.";

   add_item(({"bushes","bush"}),
   "The bushes are small and lithe, and very green.  An ordinary bush.\n");

   add_item(({"grass","tall grass","spot"}),
   "Calm and tranquil, it may be, but the tall grass is definitely not for "+
    "sitting- it would give you a rash!\n");

   add_item(({"rolling hills"}),
   "The rolling hills here are quite flat and not very tall.  Perfect for building "+
   "a burrow in.\n");

   add_item(({"steeper hills","set of hills","steeper set of hills"}),
   "The steeper hills are sharp and jagged looking, very uninviting.\n");

   add_item(({"path"}),"The gravel and dirt path leads into those steep hills to "+
   "the southwest.\n");

   add_item(({"twisty path"}),
   "The twisty path is dirt only and leads north into the hamlet "+
   "of Greenfields.\n");


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
     TP->move_living("M",GREEN_DIR + "burrow/1",1);
     return 1;
    }

   NF("Enter what ? A "+str+" ? You must be kidding!\n");
   return 0;
}
