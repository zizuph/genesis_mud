#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define TP this_player()
#define TO this_object()
#define EN environment

torris(){
   object ob1, me;
   object lamp, ember;

    lamp = present(MYSTIC_LAMP, TP);
   ember = present("mystic_ember", lamp);
   
   
  if(!lamp) return "You will need the lamp.\n";
   if(!ember) return "The sacred fire is not with you.\n";
   if(TP->query_mana() < 100) return "You do not have the strength.\n";
   if(TP->query_skill(SS_ELEMENT_FIRE) + TP->query_skill(SS_FORM_CONJURATION) <
         random(150)) return "You fail to summon the ancient fire.\n";
   if(!TP->query_prop("blessed")) return "You must be blessed!\n";
   ob1 = present("ancient_branch", TP);
   if(!ob1) return "The fire finds no home.\n";
   
   TP->catch_msg("You hold aloft the ancient branch and summon the spirits of the ancient fires!\n");
   tell_room(EN(TP), QCTNAME(TP) + " holds aloft an ancient branch and intones a sacred chant.\n", TP);
   me = TP;
   set_alarmv(2.0, -1.0, "burst", ({ me, ob1 }));
   TP->add_mana(-100);
    if(random(100) > 92){
   TP->catch_msg("Your lamp grows cold.\n");
   lamp->remove_ember();
   }

   return 1;
}


burst(object me, object ob1){
   object fb;
  tell_room(EN(me), "The ancient branch held aloft by " +
      QCTNAME(me) + " explodes into a fiery blaze!\n", me);
   me->catch_msg("The sacred spirits of fire enter into the ancient branch!\n");
   ob1->remove_object();
   fb = clone_object("/d/Terel/mecien/valley/guild/spells/fire_brand");
   set_alarm(210.0, -1.0, "consumed", fb);
   fb->move(TP);
}

consumed(object fb){
   tell_room(EN(fb), "The " + fb->query_short() + " turns into ash.\n");
   fb->remove_object();
}


