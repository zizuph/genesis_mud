inherit "/std/room";

#include "default.h"

inherit CASTLE_ROOM;

int open;

void
create_room()
{
   set_short("Passageway");
   set_long("@@my_long");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   
   add_item(({"bas-relief","relief"}),"@@bas_desc@@");
   add_item(({"walls","blocks","marble"}),"The walls are made from huge "+
      "marble blocks, all carefully fitted\ntogether by ancient master "+
      "stonesmiths.\n");
   add_item("eagle","The lord of the skies is rampant above the griffon "+
      "and the unicorn.\n");
   add_item("griffon","The griffon is opposite the unicorn on the "+
      "bas-relief.\n");
   add_item("unicorn","The unicorn is one of the legendary beasts "+
	"runoured to exist on the\nother side of the world.\n");
   add_item(({"sword","swords","crossed swords"}),"The swords are ancient "+
      "dueling swords.\n");
   
   add_exit(CASTLE_DIR + "3k8","west",0);
   add_exit(CASTLE_DIR + "3k10","north",0);
   
   open = 0;
}

string
my_long()
{
   string op_st;
   
   if(open)
      op_st = " There is an opening to the southeast.";
   else
      op_st = "";
   return break_string("This passageway is lavishly decorated with "+
      "a bas-relief set in the wall. The walls are superbly hewn from "+
      "giant marble blocks and the passage extends to the north and to "+
      "the west." + op_st + "\n", 76);
}


string
bas_desc()
{
   string bas_st;
   
   if(open)
      bas_st = " The eagle has been pushed to one side.";
   else
      bas_st = "";
   return break_string("The bas-relief is quite large, maybe a foot "+
      "across, and show an eagle rampant on a pair of crossed "+
      "swords with a unicorn and a griffon to either side." + 
      bas_st + "\n", 76);
}

void
init()
{
   ::init();
   add_action("do_push","push",0);
}

int
do_push(string str)
{
   NF("Push what?\n");
   if(!strlen(str))
      return 0;
   
   NF("You push the bas-relief but nothing seems to happen.\n");
   if((str == "bas-relief") || (str == "relief"))
      return 0;
   
   NF("There is already an opening.\n");
   if(open)
      return 0; 
   
   if((!open) && (str == "eagle"))
      {
      write("You press the eagle, and an opening appears in the wall.\n");
      tell_room(TO, "A dry cool wind blows from the opening in the "+
         "wall.\n");
      open = 1;
      TO->add_exit(CASTLE_DIR + "3k12","southeast",0);
      return 1;
   }
}

