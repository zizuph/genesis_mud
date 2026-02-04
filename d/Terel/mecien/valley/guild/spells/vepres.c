#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define TO this_object()
#define EN environment
#define TP this_player()
#define PATH "/d/Terel/mecien/valley/guild/spells/"



vepres(){
   
   object here;
   
  object rose;

  rose = present("mystic_rose", TP);
   here = EN(TP);
   if(TP->query_mana() < 120) return "You do not have the strength.\n";
    if(TP->query_skill(SS_FORM_CONJURATION) + TP->query_skill(SS_ELEMENT_DEATH) +
   random(100) < 150) return "You fail to symmon the nether world.\n";
  if(!rose) return "You will need a rose.\n";
   tell_room(EN(TP), QCTNAME(TP) + " stretches forth a hand, looking gnarled and worn, " +
      "raises it up and incants some dark words.\n", TP);
   
  if(present("nether_thorns", here)) return "Nether thorns are already present here.\n";
   TP->catch_msg("You call upon the realm of shadows to issue forth its tendrils.\n");
   
   set_alarm(5.0, -1.0, "begin_thorns", here);
  rose->remove_object();
   TP->catch_msg("Your rose dries out and crumbles into nothingness.\n");
   return 1;
   
}

begin_thorns(object here){
   object thorns;
   seteuid(getuid(TO));
   tell_room(here, "The ground begins to tremble as a mass of "
      + "shadowy black thorns weave their way upwards, filling this place.\n");
   thorns = clone_object(PATH + "thorns");
   thorns->move(here);
   set_alarm(200.0, -1.0, "remove_thorns", thorns);
  TP->add_mana(-120);
   return 1;
   
}

remove_thorns(object thorns){
   
   tell_room(EN(thorns), "The mass of shadowy black thorns fade away like a spectre from an unknown world.\n");
   thorns ->remove_object();
}


