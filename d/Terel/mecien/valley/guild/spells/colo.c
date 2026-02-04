#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define EN environment
#define TO this_object()
#define TP this_player()

string *herb_list;

colo(string str){
   object herb;
   string herb_file;
   
   
   if(!str) return "The spirits remain still.\n";
   herb = present(str, TP);
   if(!herb) return "You have no such thing.\n";
   if(!herb->query_herb_name()) return "The spirits await a proper offering.\n";
   if(!herb->query_prop("blessed")){
      TP->catch_msg("Something seems wrong as the " + herb->short() +
         " rots away.\n");
      herb->remove_object();
      return 1;
   }
   TP->catch_msg("You pronounce the sacred prayer over the " + herb->short() + " and it begins to glow.\n");
   tell_room(EN(TP), QCTNAME(TP) + " intones a sacred prayer while holding something.\n", TP);
   TP->catch_msg("You hold up the " + herb->short() + ", it bursts into a cloud of particles, which is suddenly caught up in a wind that carries it away.\n");
   tell_room(EN(TP), QCTNAME(TP) + " holds up a glowing " + herb->short() + ", it bursts into a cloud of particles, which is suddenly carried away by a gust of wind.\n", TP);
   seteuid(getuid(TO));
   restore_object(HERBS);
   herb_file = MASTER_OB(herb);
   if(member_array(herb_file, herb_list) > -1){
      TP->catch_msg("The spirits seem to tell you that such things already grow somewhere in their keeping.\n");
      herb->remove_object();
      TP->add_mana(-50);
      return 1;
   }
   herb_list = herb_list + ({ herb_file });
   save_object(HERBS);
   
   TP->add_mana(-200);
   herb->remove_object();
   return 1;
}

