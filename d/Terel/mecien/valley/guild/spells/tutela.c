/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define TP this_player()
#define ENV environment


#define CAST_LIMIT    200   /* The limit for this to become a success */

nomask mixed
tutela()
{
   object who, ob;
   int mana_limit, sum;
   
   who = TP;
   
   if (NPMAGIC(who)) /* See if it is possible to cast a magic spell on obj. */
      return "Something prevents you from cast this spell.\n";
   
   if(present("divine_watcher", TP)) return "A watcher is already with you!\n";
   
   mana_limit = 200;
   
   if(!present(MYSTIC_AMULET, TP)) return "You will need the amulet.\n";
   if(!present("holy_alb", TP)) return "You will need the alb.\n";
   if (this_player()->query_mana() < mana_limit)
      return "You do not have the strength.\n";
   
   if (random(this_player()->query_skill(SS_FORM_CONJURATION) +
            this_player()->query_skill(SS_ELEMENT_LIFE)) < random(CAST_LIMIT))
   {
      write("Your call is not heard.\n");
      this_player()->add_mana(-mana_limit / 7);
      return 1;
   }
   
   this_player()->add_mana(-mana_limit);
   write("You call upon the Twelve for their divine protection to overshadow you.\n");
   say(QCTNAME(TP) + " kneels to the ground, raises a hand and cries out to the heavens with a song of terrifying glory.\n");
   
   TP->add_mana(-200);
   set_alarm(4.0, -1.0, "fear", who);
   set_alarm(8.0, -1.0, "arrive", who);
   return 1;
}

fear(object who){
   tell_room(ENV(who), QCTNAME(who) + " turns white and tears form in " +
      who->query_possessive() + " eyes, as if in regret to what " +
      who->query_pronoun() + " has done.\n", who);
   who->catch_msg("You begin to fear the coming of the divine powers.\n");
}


arrive(object who){
   object ob;
   seteuid(getuid(this_object()));
   ob = clone_object(SPELL_DIR + "watcher_obj");
   ob->set_duration(random(this_player()->query_stat(SS_WIS) / 3) +
      random(this_player()->query_skill(SS_SPELLCRAFT) / 2) + 50);
   ob->move(who);
}
