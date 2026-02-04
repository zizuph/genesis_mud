/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define TO     this_object()
#define TP     this_player()

void
create_armour()
{
   set_name("hooded-cowl");
   set_adj("white");
   add_name("cowl");
   add_name("mystic_cowl");
   add_name("hood");
   set_long("A simple white cowl, to be worn with a robe.\n");
   set_ac(5);
   add_prop("mystic_armour", 1);
   set_at(A_HEAD);
   set_am(({0, 0, 0}));
   add_prop(OBJ_I_WEIGHT, 300);
   add_prop(OBJ_I_VOLUME, 300);
   set_af(TO);
}

wear(object obj){
   
   object robe;
   
   robe = present(MYSTIC_ROBE, TP);
   
   
   if(TP->query_skill(MYSTIC_RANK)<1){
      TP->catch_msg("You feel you have violated some order.\n");
   }
   if(!robe) return "It cannot be worn without the robe.\n";
   if(!robe->query_worn()) return "You must wear the robe in order to wear the cowl.\n";
}


