/* 
 * /d/Kalad/common/wild/pass/giantpass/rooms/swhut.c
 * Purpose    : Giant's home
 * Located    : North of the Caravan Route
 * Created By : Antharanos 
 * Modified By: Meton 2020
 */ 

#include "../local.h"
inherit STDIR + "giantroom_std.c";

/* by Antharanos */
void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   add_prop(OBJ_I_HAS_FIRE,1);
   set_short("Hut");
   set_long("The inside of this hut is filled with smoke from a fire "
      + "burning in the center of the room. Several giant logs are "
      + "stacked on the side, fuel for the fire. Discarded bones litter "
      + "the floor.\n");
   add_item(({"smoke"}),"It fills this hut, making your eyes water.\n");
   add_item(({"fire"}),"A large and intensely hot fire, the cause of all "
      + "the smoke here.\n");
   add_item(({"giant logs","logs","log"}),"The dead trunks of several "
      + "redwood trees.\n");
   add_item(({"bones","bone"}),"The skeletal remains of several "
      + "unfortunate animals.\n");
   add_exit(RDIR + "w31", "out");
   add_exit(RDIR + "w31","northeast", 0, 1, 1);
   add_npc(LIV + "hgiant.c", 2);
}

void
init()
{
   ::init();
   add_action("do_smell", "smell");
   add_action("do_smell", "sniff");
   add_action("do_smell", "exa");
}
int
do_smell(string str)
{
   if(!str || str != "smoke")
      {
      notify_fail("You can't smell '" + str + "'.\n");
      return 0;
   }
   write("As you inhale the smoke in...\n");
   say(QCTNAME(TP) + " smells the smoke from the fire.\n");
   set_alarm(2.0,0.0,"do_cough");
   return 1;
}
void
do_cough()
{
   TP->command("cough");
   TP->command("choke");
   TP->command("puke");
   return;
}