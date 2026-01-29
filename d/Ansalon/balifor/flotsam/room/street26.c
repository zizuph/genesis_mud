#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object merc;

void
reset_flotsam_room()
{
   if(!objectp(merc))
      {
      merc = clone_object(KNPC + "mercenary");
      merc->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Crowded street in the town of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"street","cobbled street"}),"A filthy, well-used " +
      "cobbled street. \n");
   add_item(({"brazier","iron brazier","tall iron brazier"}),"A " +
      "tall iron brazier, its light casting dark shadows on the " +
      "walls of the surrounding buildings. \n");
   add_item("clouds","Overhead loom gloomy clouds that seem to hover over " +
      "Flotsam every minute of the day. \n");
   add_item("house","A tall merchants house that has fallen into " +
      "disrepair. It seems deserted... but wait! You think you saw " +
      "a glimmer of light come from one of the upper windows. \n");
   add_item(({"window","upper window"}),"Hmm... you thought you saw a light " +
      "coming from this window, but now its gone. Must be your " +
      "imagination. \n");
   add_item(({"soldiers","mercenaries"}),"Drunken soldiers "+
      "of the Blue Dragonarmy along side newly recruited mercenaries " +
      "stumble through the street. It would be best to keep out of their " +
      "way if you don't want trouble.\n");
   add_item("patrols","Heavily armed patrols wander the streets, " +
      "stopping newcomers to Flotsam, interrogating them, and occasionally " +
      "arresting them. You wonder what they are looking for?\n");
   
   add_exit(FROOM + "street25","east",0);
   add_exit(FROOM + "street27","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a crowded " +
   "cobbled street in the town of Flotsam. Off-duty soldiers and " +
   "newly recruited mercenaries roaming from tavern to tavern in " +
   "search of cheap ale fill the streets, alongside heavily armed " +
   "patrols that seem to be looking for something... or someone. " +
   "To your south stands a tall house that may have been " +
   "the home of some rich merchant, but is now deserted. " +
   "The street continues to your east and west. " +
   "A tall iron brazier stands off on a sidewalk, relieving " +
   "little of the gloom brought on by the clouds overhead. " +
   season_descr() + "\n";
}
