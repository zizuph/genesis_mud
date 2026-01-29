#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object drac1;
object merc;

void
reset_flotsam_room()
{
   if(!objectp(drac1))
      {
      drac1 = clone_object(KNPC + "baaz");
      drac1->move(TO);
   }
   if(!objectp(merc))
      {
      merc = clone_object(KNPC + "mercenary");
      merc->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Outside a Tavern in the southern parts of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"filthy street","street"}),"A filthy street " +
      "that runs east and west. To the south stands a " +
      "taproom. \n");
   add_item("tavern","As taverns go, you would not put this " +
      "on a list of drinking holes to remember, but for Flotsam, " +
      "this is about as good as you will get. The sign board over " +
      "the door depicts a bird-of-prey in flight. Underneath the " +
      "picture is the words 'Hawkstones Taproom'.\n");
   
   add_exit(FROOM + "street33","east",0);
   add_exit(FROOM + "tavern01","south","@@tav_enter",0);
   add_exit(FROOM + "street35","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a filthy " +
   "street in the southern parts of the town of Flotsam. To your " +
   "south, the sound of drunken laughter, and every now and then the " +
   "sound of something breaking, filters out of a busy tavern. " + season_descr() + "\n";
}

int
tav_enter(){
   write("You enter 'Hawkstones Taproom'...\n");
   return 0;
}
