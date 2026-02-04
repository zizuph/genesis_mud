inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>

#define TO this_object()
#define TP this_player()

/* NOTE this weapon is only wieldable by the Ettin and it is
   a massive tree-trunk spear */
create_weapon(){
   set_name("spear");
   set_adj(({ "massive", "iron-tipped" } ));
   set_long("A massive spear, some twenty feet long. It is tipped with a crude point of iron.\n");
   set_hit(120);
   set_pen(60);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_WEIGHT, 340000);
   add_prop(OBJ_I_VOLUME, 440000);
   add_prop(OBJ_I_VALUE, 10);
   set_wf(TO);
}


wield(){
   if(!TP->query_race_name("ettin")) return "Only a monster could wield such a thing!\n";
   
   return 1;
}

