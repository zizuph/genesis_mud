inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
#include <macros.h>
int recently_searched;
void
create_room() {
   set_short("Mute's special place!\n");
   set_long("This is the north end of a very long room.  It is " +
      "cluttered with dust, rags, bones, and a couple of rotted " +
      "corpses.  The atrocious odour of decay present here is so " +
      "strong that you feel on the verge of urling your guts out.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item("rags","These are strips of clothing, pieces of clothing, " +
      "and just in general:  pieces of filth.\n");
   add_item("bones","These are old bones devoid of all flesh.  " +
      "You're not sure what creature they're from, but it's obvious " +
      "they've been here a long time.\n");
   add_item("corpses","There are a few of these rotted bodies " +
      "laying about, but one in particular catches your eye... \n" +
      "...the body of a human male robed in brown, laying on his " +
      "face, and clutching something beneath him.\n");
   clone_object("/d/Rhovanion/common/dungeon1/living/zombie.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell17","south");
}
void
init()
{
   ::init();
   add_action("part_corpse","search");
}
int
part_corpse(string str)
{
   if(!str || str != "corpse")
      return 0;
   if(recently_searched)
      {
      write("There is nothing left on this stripped corpse.\n");
      return 1;
   }
   write("You begin to go through the corpse's belongings...\n");
   say(QCTNAME(TP) + " bends down and starts going through the " +
      "corpse's belongings...\n");
   call_out("part_find",5);
   return 1;
}
string
part_find() {
   recently_searched = 1;
   write("You find a closed pouch on the corpse.\n");
   say(QCTNAME(TP) + " finds a closed pouch on the corpse.\n");
   room_add_object("/d/Rhovanion/common/dungeon1/gear/pouch.c",1,
      "It feels heavy like it may contain something.\n");
   return "";
}
