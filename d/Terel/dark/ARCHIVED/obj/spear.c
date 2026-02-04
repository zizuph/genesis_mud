inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"

create_weapon() {
   string *arr;
   int n;
   
   set_name("spear"); add_name("spear");
   
   
   arr = ({"barbed",20, "cruel",12, "vicious",15, "wicked",9, 
         "sharp",10, "long",13, "hideous",17, "large",13});
   
   n = random(sizeof(arr)/2)*2;
    set_short(arr[n] + " spear");
   set_adj(arr[n]);
   
   set_hit(20);
   set_pen(arr[n+1] + 3);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   set_hands(W_NONE);
   add_prop(OBJ_I_VALUE, arr[n+1]*arr[n+1]); 
   /*    comp_value(arr[n+1]);   */
   
   set_short(arr[n]+ " spear");
   
   set_long("You see nothing special about the "+ query_name() +".\n");
   /*  set_long("Name: "+ query_name() +
      "\nAdj: "+ arr[n] +
      "\nVal: "+ query_prop(OBJ_I_VALUE) +",  "+ wep_value +
      "\nPen: "+ arr[n+1] +"  n: "+ n +"\n");
   */
   
}

