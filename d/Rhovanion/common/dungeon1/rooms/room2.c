inherit "/std/room.c";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
#include <ss_types.h>
#define I_AM_STUCK "_i_am_stuck"
static int counter;
static int cracked;
object victim;
void
create_room() {
   set_short("room\n");
   set_long("This is a room rectangular in shape made of large, " +
      "stone blocks.  It is approximately thirty feet north by " +
      "twenty feet east in size.  A stone arch leads out of the " +
      "room north down a tunnel, and there is a door on the east " +
      "wall.  The air here is particularly dry.\n");
   add_item(({ "block", "blocks" }), "These are large, dark blocks of " +
      "stone approximately one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("arch","This smoothly carved dark stoned arch leads " +
      "out of the room north to a dark tunnel.\n");
   add_cmd_item("cracks","pry","@@pry_cracks");
   add_cmd_item("latch","jiggle","@@jiggle_latch");
   clone_object("/d/Rhovanion/common/dungeon1/misc/door1.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun1","north",
      "@@do_trap");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun7","south",
      "@@do_trap");
}
void
init()
{
   ::init();
   add_action("enter_door","enter");
}
do_trap() {
   if(TP->query_prop(I_AM_STUCK))
      {
      write("You struggle to free your foot, but to no avail. " +
         "It is trapped within the mesh of iron bars in the pit.\n");
      TP->command("despair");
      return 1;
   }
   else
      {
      return 0;
   }
}
int
enter_door(string str) {
   victim = TP;
   notify_fail("Enter what?\n");
   if (!str)
      return 0;
   if (str != "door")
      return 0;
   if (counter==0)
      {
      TP->add_prop(I_AM_STUCK,1);
      counter++;
      write("You begin to walk towards the door when...\n");
      say(QCTNAME(TP) + " begins to walk towards the door when...\n");
      set_alarm(2.0,0.0,"enter_door2");
      return 1;
   }
   else
      {
      if (TP->query_prop(I_AM_STUCK,1))
         {
         write("You try to leave, but your foot is stuck " +
            "in the pit.\n");
         say(QCTNAME(TP) + " moans sadly as he struggles " +
            "futilely to pull " + QCTNAME(TP) + "'s foot from " +
            "the lockjaw grip of the iron bars holding it in place.\n");
         return 1;
      }
      else
         {
         TP->command("clumsily");
         return 1;
      }
   }
}
enter_door2() {
   write("...a small section of the floor gives way and your " +
      "foot plunges in.\n" +
      "It feels stuck!\n");
   say(QCTNAME(TP) + " watches helplessly as a small " +
      "section of the floor gives way and " + QCTNAME(TP) +
      "'s foot plunges in.\n");
   add_item("trap","At first glance the trap appears " +
      "to consist of a square pit about a foot across and " +
      "nearly a foot and a half deep.  One inch iron bars " +
      "extend from all sides of the stone pit creating a " +
      "barrier from removing a stuck limb.\n");
   add_item(({"bar","bars"}),"These are strong, inch " +
      "thick iron bars extending from the sides of the pit. " +
      "Upon closer examination of the stone the bars extend " +
      "from you notice small stress cracks.\n");
   add_item("cracks","These are tiny cracks around " +
      "the bars in the old, dark stone of the pit.  The " +
      "stone is old and brittle.  If one were strong enough " +
      "one might be able to pry at them until they're larger.\n");
   return 1;
}
int
pry_cracks(string str) {
   if (cracked==1)
      {
      write("They've already been pried as much as they'll " +
         "ever be.\n");
      TP->command("sigh");
      return 1;
   }
   else
      {
      if (TP->query_stat(SS_STR > 30))
         {
         write("You strain and pry and manage to enlarge the " +
            "cracks somewhat.  From where the cracks have opened " +
            "can be glimpsed an odd looking latch hooked on to " +
            "one of the iron bars.\n");
         say(QCTNAME(TP) + " strains and pries and manages to " +
            "enlarge the cracks somewhat.\n");
         add_item("latch","This small iron latch seems to be " +
            "serving some task in this trap.  If you could somehow " +
            "unlatch it, poke it, jiggle it you might be able to escape this trap.\n");
         cracked=1;
         return 1;
      }
      else
         {
         write("You strain and pry but find you lack the " +
            "strength to damage the cracks.\n");
         say(QCTNAME(TP) + "'s face turns red to no avail as " +
            QCTNAME(TP) + " can not pry open the cracks.\n");
         return 1;
      }
   }
}
int
jiggle_latch(string str) {
   write("You toggle the latch a bit and it snaps out of " +
      "place.  The iron bars of the trap slowly grind back " +
      "into the stone they burst from.\n");
   say(QCTNAME(TP) + " sticks his hand into the pit, and " +
      "the iron bars of the trap slowly grind back into the " +
      "stone from which they burst.\n");
   victim->remove_prop(I_AM_STUCK,1);
   counter--;
   set_alarm(1.0,0.0,"jiggle_latch2");
   return 1;
}
int
jiggle_latch2() {
   write("You fall through the door.\n");
   say(QCTNAME(victim) + " falls east through the door.\n");
   victim->command("clumsily");
   return 1;
}
