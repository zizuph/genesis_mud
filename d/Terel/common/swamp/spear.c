inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"

create_weapon() {
   int n;
   
   set_name("spear"); add_name("spear");
set_short("wooden spear");
set_pshort("wooden spears");
  set_adj("wooden");
   set_hit(10);
set_pen(10);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   set_hands(W_NONE);
   
   
   set_long("You see nothing special about the "+ query_name() +".\n");
   /*  set_long("Name: "+ query_name() +
      "\nAdj: "+ arr[n] +
      "\nVal: "+ query_prop(OBJ_I_VALUE) +",  "+ wep_value +
      "\nPen: "+ arr[n+1] +"  n: "+ n +"\n");
   */
   
}

