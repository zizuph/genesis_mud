/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include "spells.h"
#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define EN environment

#ifndef TP
#define TP this_player()
#endif
   
nomask mixed
arbor()
{
   
  object who, grapes;

  if(!present(MYSTIC_MANTLE, TP)) return "You will need the mantle.\n";
  if(!present(MYSTIC_SATCHEL, TP)) return "You will need the satchel.\n";
   grapes = present(MYSTIC_GRAPES, TP);
  if(!grapes) return "You will need some grapes from the vinyard.\n";
   if(TP->query_mana() < 150)
      return "You do not have the strength.\n";
  if(EN(TP)->query_prop(ROOM_I_INSIDE)) return "Such powers cannot be summoned here.\n";
   if(!EN(TP)->query_prop("mystic_presence")) return "The ancient powers must be present.\n";
   
   if (random(TP->query_skill(SS_ELEMENT_LIFE) +
            TP->query_skill(SS_FORM_CONJURATION))
      < random(150))
   {
      TP->add_mana(-10);
      write("Your prayer is not heard.\n");
      return 1;
   }
   
   TP->add_mana(-150);
   
  write("You call upon the spirits of life and intone the sacred chant in honour of the holy tree.\n");
   say(QCTNAME(TP) + " kneels upon the ground and intones a sacred chant.\n");
  grapes->remove_object();
   
  who = TP;
  set_alarm(4.0, -1.0, "glow", who);
   set_alarm(6.0, -1.0, "form", who);
  set_alarm(8.0, -1.0, "bright", who);
   set_alarm(10.0, -1.0, "plant", who);
   return 1;
}

glow(object who){
  tell_room(EN(who), "A silvery-white glow shines down upon the ground.\n");
  who->catch_msg("You sense the power of the spirit world opening.\n");
}

form(object who){
   tell_room(EN(who), "A mysterious shape begins to form from the glowing light, growing " +
  "up from the ground.\n");
}

bright(object who){
tell_room(EN(who), "There is a flash of bright light and the mysterious " +
  "form heaves upward in a state of expanding growth!\n");
  who->catch_msg("The forces of life have opened the spirit world!\n");
}


plant(object who){
   
   object ob;
   object room;
   
   
   seteuid(getuid(this_object()));
   
  tell_room(EN(who), "The glowing form suddenly solidifies and appears as a " +
"massive silvery-white tree!\n");
   ob = clone_object(SPELL_DIR + "tree");
   ob->set_duration(DURATION(who->query_stat(SS_WIS),
         who->query_skill(SS_SPELLCRAFT), 200));
   ob->move(EN(who));
   
   room = clone_object(SPELL_DIR + "tree_room");
   room->add_exit(file_name(environment(who)), "down", 0);
   who->add_prop("_tree_last_room", file_name(environment(who)));    
   
   
   ob->set_tree_room(room);
   return 1;
}
