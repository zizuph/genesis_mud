/*  Broom used by Thespian Guild Apprentices
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/12/95  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("broom");
    set_adj("straw");
    set_short("straw broom");
    set_long(
       "It's just a simple broom made of a long piece of smooth wood "+
       "with a crude straw brush on the end.\n");
    set_hit(5);
 
    set_hands(W_BOTH);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
 
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 800);
}
 
int sweep() {
   object Tp=this_player();
   object Tr=environment(Tp);
   write("You sweep the ground with the broom. How domestic of you!\n");
   tell_room(Tr,QCTNAME(Tp)+" sweeps the ground with a straw broom.\n",Tp);
   return 1;
}
 
void init() {
   ::init();
   add_action("sweep","sweep");
}
