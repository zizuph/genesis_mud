inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A narrow passage");
   set_long("A narrow passageway.\n"+
      "Stone darker than seems naturally possible lies in abundance around "+
      "you, as if beckoning you into an embrace filled with promises of death "+
      "and unending cold. The immense weight of rock that hands from above "+
      "seems to crush your vitality, leaving you dazed and weakened, vulnerable to "+
      "whatever may stumble upon you here in this realm so far beneath the light "+
      "of the sun. The passage you are in has narrowed a bit here, though "+
      "not enough to cause discomfort. It continues to the west and southeast.\n");
   add_item(({"narrow passage","narrow passageway","passage","passageway"}),
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
      "It is composed of rock and stone, as is the rest of the passage.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_exit(CPASS(uc/u16),"west",0,2,1);
   add_exit(CPASS(uc/u22),"southeast",0,2,1);
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
   TP->move_living("into the wall","/d/Kalad/common/wild/pass/mind/m14");
   TP->catch_msg("You emerge onto the other side!\n");
   return;
}
