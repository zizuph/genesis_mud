/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h";
#define TP this_player()
#define EN environment

unstun(object who){
who->catch_msg("You feel calm again.\n");
who->remove_stun(10);
}

scared(object who){
  who->add_stun(10);
   who->catch_msg("The terrifying sound petrifies you!\n");
   set_alarm(5.0, -1.0, "unstun", who);
}

frighten(object who){
   
   if(living(who)){
      if(who->query_alignment() < 10){
         who->add_panic(50);
         if(who->query_stat(SS_DIS) < random(200)) set_alarm(2.0, -1.0, "scared", who);
         return 1;
      }
      if(who->query_prop("blessed")){
         who->catch_msg("The sounds of the storm excite and enliven you!\n");
         return 1;
      }
      who->catch_msg("The tremendous thunder frightens you!\n");
   who->add_panic(15);
      
   }
}

tonitrus(){
   
   object cloud;
   
   
   if(TP->query_skill(SS_FORM_CONJURATION) + TP->query_skill(SS_SPELLCRAFT) <
   random(70)) return "You fail to master the storms powers!\n";
   if(TP->query_mana() < 25) return "You do not have the strength.\n";
   if(!present(MYSTIC_STAFF, TP)) return "You will need the staff.\n";
   cloud = present("mystic_cloud", EN(TP));
   if(!cloud)
      return "No storm is present.\n";
   
   write("You raise your staff to the heavens, calling upon the might of the storm.\n");
   tell_room(environment(TP), QCTNAME(TP) + " raises " + TP->query_possessive() +
      " staff to the heavens!\n", this_player());
   set_alarm(6.0, -1.0, "thunder", cloud);
   TP->add_mana(-25);
   set_alarm(3.0, -1.0, "dark", cloud);
   return 1;
}

dark(object cloud){
   tell_room(EN(cloud), "It becomes suddenly very dark!\n");
}

thunder(object cloud){
   tell_room(environment(cloud), "A explosion of thunder shakes the ground, sending "
      + "pulses of energy through the sky!\n");
   map(all_inventory(EN(cloud)), frighten);
   
   return 1;
}
