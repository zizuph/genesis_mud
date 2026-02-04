#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"
#include <macros.h>

#define TP this_player()
#define EN environment

canis(){
   object hound;


  if(TP->query_mana() < 100) return "You do not have the strength.\n";

   write("You call to ancient world, reciting an mysterious prayer to the spirits of nature.\n");
   say(QCTNAME(TP) + " calls out in a loud voice, reciting some ancient prayer.\n");
   set_alarm(5.0, -1.0, "arrive_hound", TP);

  TP->add_mana(-100);
    return 1;

}

arrive_hound(object caster){
  object hound;

  hound = clone_object("/d/Terel/mecien/valley/guild/spells/hound");
  hound->set_master(caster);
  hound->move_living("M", EN(caster));
   tell_room(EN(hound), QCTNAME(hound) + " appears from a misty cloud.\n");
    
}


