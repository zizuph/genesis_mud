// Base room for homes in the village
#include "defs.h"
inherit  "/d/Khalakhor/std/room";
inherit  ROOM+"npc";
 
string bdir, sdir, hdir;
string extra="";
 
void setup_villagers(int numnpc)
{
   int i;
   arrmsg="enters the home";
   for (i=0; i<numnpc; i++)
      name += ({"villager"});
}
 
void set_dirs(string outexit)
{
   if (outexit="north")
      { hdir="south"; bdir="east";  sdir="west"; }
   else if (outexit="south")
      { hdir="north"; bdir="east";  sdir="west"; }
   else if (outexit="east")
      { hdir="west";  bdir="north"; sdir="south";}
   else
      { hdir="east";  bdir="north"; sdir="south";}
}
 
create_home(string outexit)
{
   set_dirs(outexit);
   set_short("In a home in a quaint village");
   set_long("   This is one of the quaint little homes of the village, "+
            "neat as a pin and looking almost brand new on the inside. "+
            "There is a small clay bricked hearth along the "+hdir+
            " wall, in front of which sits a simple wooden table "+
            "surrounded by four chairs. A couple of beds are set "+
            "in the corners along the "+bdir+" wall flanking a large "+
            "wardrobe, while a modest couch and a cabinet stand along "+
            "the "+sdir+" wall. "+extra+"\n");
   add_item("hearth",
      "Made of clay brick, baked to a golden brown, the small "+
      "hearth provides heat for the home as well as a place to "+
      "cook.\n");
   add_item(({"table","chair","chairs"}),
      "A simple but waxed table and chairs sit in front of the "+
      "hearth.\n");
   add_item(({"bed","beds"}),
      "The beds have simple wood frames and mattresses stuffed "+
      "with straw and feathers.\n");
   add_item("wardrobe",
      "It is a large wardrobe standing between the beds, made of "+
      "wood and used to store clothing and other items.\n");
   add_cmd_item("wardrobe",({"open","unlock"}),
      "It is locked and can not be opened.\n");
   add_item("couch",
      "It is a modest wood frame couch with wool cushions.\n");
   add_item("cabinet",
      "It is a simple wooden cabinet with shelves, used to store "+
      "various items used by the family.\n");
   INSIDE;
}
