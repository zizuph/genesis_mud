/* ARGOS - Metro - A small glass vial
**
** Purchased empty for 3cc in rooms/glasswrk
** Can be filled with olive oil in  rooms/press if player has vial
**     and olives.
** When full, can be used as fuel for a brass lamp
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
int full=0;
 
/* called in rooms/press when pressing olives into oil into vial */
void fill_vial() {
   full=1;
   add_name(({"oil",ARGOS_FULL_VIAL}));
   remove_name(ARGOS_EMPTY_VIAL);
   remove_adj("empty");
   add_adj("olive");
   set_short("vial of olive oil");
   set_pshort("vials of olive oil");
   set_long("It is a small glass vial of olive oil. It can be used as "+
            "fuel for a lamp by pouring it in the lamp.\n");
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 50);
   add_prop(OBJ_I_VALUE, 20);
}
 
/* called when full vial poured into a lamp */
void empty_vial() {
   full=0;
   remove_name(({"oil",ARGOS_FULL_VIAL}));
   add_name(ARGOS_EMPTY_VIAL);
   remove_adj("olive");
   add_adj("empty");
   set_short("empty glass vial");
   set_pshort("empty glass vials");
   set_long(
      "It is a small glass vial normally used to keep a quantity of olive "+
      "oil. It is empty.\n");
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 50);
   add_prop(OBJ_I_VALUE, 3);
}
 
void create_object() {
   set_name("vial");
   add_name(ARGOS_EMPTY_VIAL);
   set_adj(({"empty","glass"}));
   set_short("empty glass vial");
   set_pshort("empty glass vials");
   set_long(
      "It is a small glass vial normally used to keep a quantity of olive "+
      "oil. It is empty.\n");
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 50);
   add_prop(OBJ_I_VALUE, 3);
}
 
int pour(string Parms) {
   object Tp=this_player();
   object To=this_object();
   object Tr=environment(Tp);
   object Lamp=present(ARGOS_BRASS_LAMP,Tp);
   string *Parm;
 
   if (!(Parms)) return 0;
   Parm=explode(Parms," ");
   if (!((member_array("oil",Parm) > -1) && (member_array("lamp",Parm) > -1)))
      return 0;
 
   if (!(full)) return 0;
 
   if (!(Lamp)) {
      write("You do not have a brass lamp this oil is used in.\n");
      return 1;
   }
 
   if (Lamp->query_time() > 0) {
      write("There is already some oil in the lamp.\n");
      return 1;
   }
 
   write("You pour a vial of oil into the brass lamp.\n");
   tell_room(Tr,QCTNAME(Tp)+" pours a vial of oil into a brass lamp.\n",Tp);
   Lamp->set_time(600); /* one vial fuels for 10 minutes */
   To->empty_vial();
   return 1;
}
 
void init() {
   ::init();
   add_action("pour","pour");
}
