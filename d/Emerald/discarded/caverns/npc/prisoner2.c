inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"

void
create_monster()
{
   set_name("prisoner");
   add_name("runt");
   set_race_name("gnome");
   set_adj("squeeky");
   add_adj("little");
   set_short("squeeky little prisoner");
   set_long(
      "This annoying little runt looks like he knows a "+
      "lot about prison life, especially what he can get "+
      "away with.\n");
   set_stats(({73,69,70,58,62,74}));
   set_hp(TO->query_max_hp());
   set_skill(SS_WEP_KNIFE, 70);
   set_skill(SS_DEFENCE, 65);
   set_skill(SS_PARRY, 60);
   set_skill(SS_BLIND_COMBAT, 50);
   set_chat_time(5);
   add_chat("Got any smokes?");
   seteuid(getuid(this_object()));
}


void
attacked_by(object ob)
{
   object shiv;
   ::attacked_by(ob);
   if(present("shiv",TO))
      return;
   tell_room(ENV(TO),break_string(
         "The prisoner gets something from a creavace in "+
         "the wall.\n",74),TO);
   shiv = clone_object(CAVERNS_DIR+"arm/shiv");
   shiv ->move(TO);
   TO->command("wield all");
}


