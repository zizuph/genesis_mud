/*                                    */
/*     This is the room where the     */
/*     ladder leading up to the       */
/*     treetop village of Kaldoro     */
/*     is located.                    */
/*                                    */
/*          By: Antharanos            */
/*          Modified by Rico 08.01.95 */
/*                                    */

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

public void
create_room()
{
   ::create_room();

   add_prop(ROOM_NO_TIME_DESC,1);
   add_prop(OBJ_S_SEARCH_FUN, "search_here");

   set_short("Valley");
   set_long("You are within a wide and open valley.\n"+
      "Giant redwood trees surround you, enfolding you in "+
      "their vibrant, full of life depths. On the sides of "+
      "the valley, the Hespyre mountains tower above the "+
      "landscape. Their slopes are more gentle here, and "+
      "as such the forest creeps higher up the mountains here than "+
      "in other areas of the range.\n");

   add_item(({ "forest", "redwood trees", "trees", "giant trees" }),
      "The smallest ones are almost fifteen feet wide at "+
      "the base, with most of the others being as wide as "+
      "twenty feet. All of them tower hundreds of feet "+
      "into the sky, casting dark shadows upon the "+
      "ground around you. Almost unseen in the shadows, "+
      "you notice what appears to be an old, rope ladder "+
      "trailing down from the thick foliage above.\n");
   add_item(({"hespyre mountains","mountains","range","mountain"}),
      "Massive formations of rock, so great is their "+
      "size that everything within the landscape is dwarfed in "+
      "comparison, even the mighty redwoods.\n");
   add_item(({ "slopes", "slope" }), "The relatively "+
      "gentle slopes of the trees.\n");
   add_item(({ "rope", "ladder", "rope ladder", "old ladder" }),
      "This old, rope ladder appears to be unable to hold "+
      "a normal sized person, but as you give it a test by pulling "+
      "on it sharply you realize that it must be very "+
      "sturdy indeed! You try to see where it ends up "+
      "above you, but you can't make it out because the "+
      "ladder disappears into some very dark shadows. "+
      "You are tempted to climb up and investigate "+
      "further.\n");

   add_exit("/d/Kalad/common/wild/pass/w32", "southwest",0,2);
   add_exit("/d/Kalad/common/wild/pass/w34", "north",0,2);
}

public string
search_here(object me, string arg)
{
   if (arg != "here")
      return "";
   clone_object("/d/Kalad/common/wild/pass/herbs/parsley")->move(TP);
   return "You search carefully and find an herb!\n";
}

void
init()
{
   ::init();

   add_action("climb", "climb");
   return;
}

int
climb(string str)
{
   if((str=="rope ladder")||(str=="up ladder")||(str=="ladder"))
   {
      if(((this_player()->query_skill(SS_CLIMB))<=30))
      {
         write("/n"+
            "You get yourself all tangled up in the "+
            "rope ladder. It takes you a while to extricate "+
            "yourself, but you finally manage to do it. You "+
            "are obviously unskilled enough to successfully "+
            "make this climb.\n");

         say(QCTNAME(this_player()) + " tried to climb up the "+
            "ladder but got all tangled up in it instead. It's "+
            "hysterical sight to behold!\n");

         this_player()->heal_hp(-20);
         return 1;
      }
      say(QCTNAME(this_player()) + " deftly clambers up the old "+
         "rope ladder.\n", 50);
      this_player()->move_living("climbing up the ladder",
         KALDORO(rooms/kv01));
      command("look");
      return 1;
   }
   write("Climb what?");
   return 1;
}
