/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

#define TO     this_object()
#define TP     this_player()
#define GUILD  "The Ancient Mystic Order"
#define MEMBER (TP->query_guild_member(GUILD))
#define MYSTIC_RANK 130003

void
create_armour()
{
   set_name("robe");
   set_adj("white");
   add_name("mystic_robe");
   set_long("A simple white robe, a religious garment.\n");
   set_ac(10);
   add_prop("mystic_armour", 1);
   set_at(A_ROBE);
   set_am(({0, 0, 0}));
   add_prop(OBJ_I_WEIGHT, 300);
   add_prop(OBJ_I_VOLUME, 300);
   set_af(TO);
}

remove(object what){
   object cowl;
   cowl = present("mystic_cowl", TP);
   if(cowl){
      if(cowl->query_worn()){
         TP->command("remove cowl");
      }
   }
   
}

wear(object obj){
   
   
   if(TP->query_skill(MYSTIC_RANK)<1){
      TP->catch_msg("You feel you have violated some order.\n");
   }
}


