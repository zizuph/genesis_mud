inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"

create_weapon() {
   string *arr;
   int n;
   
   set_name("scimitar"); add_name("knife");
   set_pname("scimitarss");
   
   
   arr = ({"curved",10, "cruel",8, "vicious",15, "wicked",6, 
         "blood stained",11, "jagged",14, "black",12,
         "rusty",7, "long",13, "ornate",17, "large",13});
   
   n = random(sizeof(arr)/2)*2;
   set_adj(arr[n]);
   
   set_hit(25);
   set_pen(arr[n+1] + 5);
   set_wt(W_SWORD);
   set_dt(W_IMPALE | W_SLASH);
   set_hands(W_NONE);
   add_prop(OBJ_I_VALUE, arr[n+1]*arr[n+1]); 
   /*    comp_value(arr[n+1]);   */
   
   
   set_long("You see nothing special about the "+ query_name() +".\n");
   /*  set_long("Name: "+ query_name() +
      "\nAdj: "+ arr[n] +
      "\nVal: "+ query_prop(OBJ_I_VALUE) +",  "+ wep_value +
      "\nPen: "+ arr[n+1] +"  n: "+ n +"\n");
   */
   
}

