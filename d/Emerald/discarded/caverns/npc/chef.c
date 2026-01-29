inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"

void
create_monster()
{
   set_name("chef");
   set_short("bumbling chef");
   set_adj("bumbling");
   set_long(
      "This chef looks so uncoordinated that you begin to "+
      "wonder if he can actually cook.\n");
   set_stats(({60,55,55,43,48,57}));
   set_hp(TO->query_max_hp());
   set_skill(SS_WEP_KNIFE, 40);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_PARRY, 35);
   set_chat_time(9);
   add_chat("What are you doing in my kitchen!?!?");
   add_chat("Get out of here! Can't you see I'm working?");
   seteuid(getuid(this_object()));
   set_alarm(1.0,0.0,"arm_me");
}

void
arm_me()
{
   object apron, peeler;
   apron = clone_object(CAVERNS_DIR+"/arm/dirty_apron");
   apron ->move(TO);
   peeler = clone_object(CAVERNS_DIR+"/arm/peeler");
   peeler ->move(TO);
   TO->command("wear all");
   TO->command("wield all");
   return;
}


