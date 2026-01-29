inherit "/std/monster.c";
#include "defs.h"
#include "/sys/filter_funs.h"
#include <money.h>
void
create_monster()
{
   set_name("rockjaw");
   set_race_name("dwarf");
   set_adj("effeminate");
   add_adj("cooking");
   set_long("This is the Minthor's personal cook. He can cook up "
	+"anything you can imagine, just not for anyone but the Minthor "
	+"family. Don't bother him, or he might filet you.\n");
   set_stats(({70,50,85,65,65,60}));
   set_act_time(5);
   add_act("whistle happily");
   add_act("emote filets some small creature.");
   add_act("emote burns himself on the stove.");
   add_act("sing");
   set_cact_time(7);
   add_cact("gasp");
   add_cact("emote swings his cleaver menacingly.");
   set_chat_time(5);
   add_chat("Can i help you?\n");
   add_chat("I love the taste of thri-kreen giblets.\n");
   add_chat("This pot cost me 8 liters of water!\n");
   set_cchat_time(3);
   add_cchat("Now you asked for it.\n");
   add_cchat("You better not get blood on my food!\n");
   add_cchat("They don't call me the asshole fileter for nothing!\n");
   add_prop(LIVE_I_NEVERKNOWN, 1);
}
void
arm_me()
{
  clone_object(TZ_MINTHOR + "wep/cleaver.c")->move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(10))->move(this_object(),1);
}
