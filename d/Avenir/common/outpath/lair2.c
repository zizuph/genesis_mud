// file name:    lair2.c
// creator(s):   Cirion, April 1996
// last update:
// purpose:      Lair where there are maggot eggs & the mommy grub
// note:         
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/room";
#include "outpath.h"
  
object    mommy;

void reset_room()
{
  int   i;

  if(!present(mommy))
  {
     mommy = clone_object(MON+"mommy");
     mommy->move(TO);
     tell_room(TO, CAP(LANG_ADDART(QSHORT(mommy)))+" crawls into "
         +"the cavern.\n");
  }

  if(present("egg", TO))
    return;

  mommy->command("emote quickly ejects a bunch of slimy white eggs.");
  for(i=0;i<random(8) + 2;i++)
    clone_object(OBJ+"egg")->move(TO, 1);
}

void create_room()
{
  set_short("slimy cavern");
  set_long("This is the north end of a very low, nasty "
    +"cavern. The air carries a disgusting stench of "
    +"filth and decay, and foul water drips down from the "
    +"walls and ceiling. The floor is everywhere covered "
    +"in a thick white film.\n");

  ACI(({"","air","here"}),({"smell","sniff"}),"The air smells "
    +"terrible, like the decay of some ancient beast.\n");

  add_item(({"wall","walls","cave","cavern"}),"The walls of the "
    +"cavern are smooth and wet.\n");
  add_item(({"floor","ground"}),"It is slippery and wet, covered "
    +"in a sticky white slime.\n");
  add_item(({"ceiling","roof"}),"It is very low and smooth.\n");
  add_item(({"film","slime"}),"It seems to cover everything, "
    +"befouling all it touches.\n");

  IN;
  IN_IN;
  remove_prop(ROOM_I_LIGHT);

  add_exit(OUTPATH+"lair1", "south");

  reset_room();
}
