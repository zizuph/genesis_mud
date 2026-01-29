/* MCLUB - the key to the Bell Tower of the Shrine */
inherit "/std/key";
#include "/sys/stdproperties.h"
#include <macros.h>
#include "defs.h"
create_key() {
  set_adj("small");
  add_adj("copper");
  add_name(MCLUB_BTKEY);
  set_long("It is a small copper key with an arcane design. It looks "+
           "like it could easily be bent.\n");
  set_key(BELLTOWER_KEY_NUM);
  add_prop(OBJ_I_WEIGHT,20);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_I_VALUE,0);
}
 
/* The key can be bent so it is useless */
int bend(string Parm) {
   object TO=this_object();
   object TP=this_player();
   object TR=environment(TP);
 
   if (Parm=="key") {
      write("You bend the copper key and discard it.\n");
      tell_room(TR,QCNAME(TP)+" bends a small copper key and "+
                "discards it.\n",TP);
      TO->remove_object();
      return 1;
   }
   return 0;
}
 
void init() {
   ::init();
   add_action("bend","bend");
}
