/**********************************************************************
 * - house2floor.c                                                  - *
 * -                                                                - *
 * - updated by Damaris@Genesis 11/2004                             - *
 * - Added reset_room function                                      - *
 **********************************************************************/
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object man;
public void
reset_room()
{
    if (!man)
    {
	man = clone_object("/d/Kalad/common/trade/cliffside/xzintra");
	man->move(this_object(), 1);        
    }

}


void
create_room()
{
   set_short("Top Floor");
   set_long("This is the top floor of the house. There is an old mattress "
      +"here, which apparently gets a lot of use. The room is very "
      +"dirty, but you've come to expect that here. Against the far "
      +"wall there is a shelf with something on it.\n");
   add_item(({"mattress"}),"This is an old dirty mattress. There is "
      +"an equally old pillow here as well, and "
      +"the bed shows signs of frequent use.\n");
   add_item(({"pillow"}),"This is an old pillow that matches the mattress perfectly.\n");
   add_item(({"shelf"}),"The long wooden shelf contains a few objects of "+
      "interest.\n");
   add_item(({"objects","object"}),"Located on the shelf are a hairbrush, a "+
      "wash bowl, a water pitcher, a knife sheath and a toothpick.\n");
   add_item(({"hairbrush"}),"It is an old hairy hairbrush.\n");
   add_item(({"wash bowl","bowl"}),"This is a wash bowl filled with dirty "
      +"water.\n");
   add_item(({"water pitcher","pitcher"}),"A pitcher filled with murky water.\n");
   add_item(({"knife sheath","sheath"}),"This is a knife sheath made of gold "
      +"and encrusted with jewels, it looks very valuable.\n");
   add_item(({"toothpick"}),"A wooden toothpick with food particles "
      +"clinging to it.\n");
   add_exit(TRADE(cliffside/house2),"down");
   hear_bell = 2;
   add_prop(ROOM_I_INSIDE,1);
   reset_room();
}
