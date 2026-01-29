inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A narrow, cramped passage");
   set_long("A narrow and cramped passageway.\n"+
      "Stone as black as the lightless depths of the netherworld surround "+
      "you, enfolding you in its cold embrace. The immense weight of rock that "+
      "hangs above you seems to crush your vitality, leaving you fatigued "+
      "and weary. The passage appears to end here, for the wall to the north "+
      "is complete, not a crack visible. The rest of the passage lies to the "+
      "southeast, where darkness reigns.\n");
   add_item(({"narrow passage","cramped passage","narrow passageway","cramped passageway","passage","passageway"}),
      "A narrow corridor somewhere beneath the surface of Kalad.\n");
   add_item(({"stone","rock"}),
      "As black as a fetid tar pit, it seems to suck the very life from "+
      "your bones.\n");
   add_item(({"walls"}),
      "Which wall?\n");
   add_item(({"northern wall","north wall","wall"}),
      "The wall to the north is unusually smooth for such an apparently "+
      "natural passageway. Upon closer inspection it appears to possess a "+
      "rather unusual quality. It has the consistency of water itself, yet "+
      "appears in no danger of collapsing.\n");
   add_item(({"floor","ground","ceiling"}),
      "It is composed of numerous bits of rock and stone.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_exit(CPASS(uc/u2),"southeast",0,2,1);
}
void
init()
{
   ::init();
   AA(do_enter,enter);
}
int
do_enter(string str)
{
   if(!str || str != "wall")
      {
      NF("You can't enter '" + str + "'.\n");
      return 0;
   }
   write("You slowly enter the wall, wading through the strangely "+
      "liquid-like rock.\n");
   say(QCTNAME(TP) + " slowly enters the wall, disappearing into "+
      "the very rock itself!\n");
   set_alarm(2.0,0.0,"do_move");
   return 1;
}
void
do_move()
{
   TP->move_living("into the wall","/d/Kalad/common/wild/pass/underdark/u31");
   TP->catch_msg("You emerge onto the other side!\n");
   return;
}
