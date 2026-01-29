// Kirk of Port City - Corridor
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 5/25/97     Zima        Created
// 6/20/98     Zima        Recoded as bottom of stairwell
//
//
#include "defs.h"
#include <stdproperties.h>
#include "../../lib/zdoor.h"
#define  OTHER ROOM+"kcorr6"
inherit  SR_LIB+"zindoor";
inherit  "/d/Khalakhor/std/room";
 
object manach;
 
//
// reset_room
//
void reset_room()
{
   if (manach) return;
   seteuid(getuid());
   manach = clone_object(SR_NPC+"dorrius");
   manach->equip_me();
   manach->move(TO);
   manach->set_indoor_room(TO);
   tell_room(TO,QCNAME(manach)+" walks down the steps.\n");
   manach->secure_door();
}
 
//
// create_khalakhor_room
//
void create_khalakhor_room()
{
 
   set_short("Corridor in the abbey");
   set_long(
      "   You are at the end of a corridor which runs north and south through "+
      "the abbey of the kirk. Opaque windows line the eastern "+
      "wall of the passageway, their panes set in a lattice pattern. "+
      "Candelabrum stand along the corridor between the windows, laden "+
      "with flickering candles, dimly lighting the long stone hall. "+
      "A set of steps lead up from here, while a wrought iron gate "+
      "with panes of stained glass guards the way down the corridor "+
      "to the north.\n");
 
   INSIDE;
   add_item("corridor",
      "It is a long corridor through the abbey of the kirk, linking the "+
      "myriad of chambers used by the manachs who live here. It runs north "+
      "behind the gate and ends here.\n");
   add_item("abbey",
      "It is a building attached to the kirk where the manachs who take "+
      "care of this place live and work.\n");
   add_item("windows",
      "The windows are tall and thin, their tops rising to a pointed "+
      "arch. They line the eastern wall of the cooridor, their "+
      "opaque panes a lattice of diamond shaped panes of a cream "+
      "color.\n");
   add_item(({"candelabra","candelabrum","candelabras","candles"}),
      "The ornate candelabrum sit along the eastern wall, one "+
      "between each pair of windows. Each is made of gold and ornately "+
      "crafted with elegant twists and curves which flank out from "+
      "a tall central staff. Dozens of thick white candles flicker "+
      "in the holders of each, dimly lighting the cooridor.\n");
   add_item("steps","They lead up into the upper level of the abbey.\n");
   add_item(({"bolt","lock"}),
      "The lock on the gate is a bolt which can be used only on this "+
      "side to lock and unlock the gate.\n");
 
   add_exit("kcorr6","north");
   add_exit("ucorr7","up","@@chk_guard");
 
   setup_indoor("north", OTHER, ({"gate"}),
      "It is a wrought iron gate, its poles twisted and cast in swirling "+
      "and interlocking lines and scrolls. Panes of stained glass are "+
      "cut and set into the gate, obscuring the corridor behind it "+
      "to the north. Its beauty is deceptive of its strength. There "+
      "is a bolt action lock on it.",
      "wrought iron gate", 0, BOLTABLE, LOCKED, 200);
}
 
//
// manach_here
//
int manach_here(object ob)
{
   if (manach && present(manach,TO) && CAN_SEE(manach,ob) &&
       CAN_SEE_IN_ROOM(manach))
       return 1;
   return 0;
}
 
//
// chk_guard
//
int chk_guard()
{
   if (manach_here(TP)&&(!(TP->is_saggart()))&&
      (!(TP->query_prop(SR_BLESS_ENTER))))
      {
      manach->command("say You may not go there, "+
                     (TP->query_nonmet_name())+".");
      return 1;
      }
   return 0;
}
 
//
// init
//
void init()
{
   ::init();
   add_indoor_actions();
}
 
//
// knocked - respond to knock on door
//
void knocked(object tp)
{
   ::knocked(tp);
   if (manach_here(tp)) manach->answer_knock(tp);
}
 
//
// do_greet
//
void do_greet(object tp, object from)
{
   if (manach_here(tp) && present(tp,TO))
      manach->do_greet(tp,from,outsiderm);
}
 
//
// enter_inv
//
void enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);
   if (manach_here(ob) && living(ob) && (from != TO))
     set_alarm(2.0,0.0,&do_greet(ob,from));
}
