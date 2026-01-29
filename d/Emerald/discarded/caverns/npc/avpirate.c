inherit "/std/monster.c";

#include <wa_types.h>
#include "defs.h"
#define WEP CAVERNS_DIR+"arm/rapier"
#define ARM CAVERNS_DIR+"arm/grey_cloak"

void
create_monster()
{
   set_name("bloggo");
   set_race_name("pirate");
   set_adj("swarthy");
   set_adj("dimwitted");
   set_long("This pirate failed grammar school and enrolled in piracy.\n");
   set_stats(({ 80, 80, 80, 20, 20, 100}));
   set_hp(5000);
   set_skill(SS_DEFENCE, 70);
   set_skill(SS_PARRY, 60);
   set_skill(SS_WEP_SWORD, 70);
   set_skill(SS_AWARENESS, 60);
   set_skill(SS_UNARM_COMBAT, 60);
   
   set_chat_time(8);
   add_chat("Whoah! Somebody stop the room from spinning!");
   add_chat("Erg...I have to take a leak!");
   set_cchat_time(6);
   add_cchat("You pickin on me too?");
   add_cchat("That does it!");
   add_act("out");
   add_act("pout");
   add_act("sulk");
   seq_new("do_things");
   seq_addfirst("do_things", ({"@@arm_me", "enter cave"}));
}
arm_me()
{
   object wep, arm;
   seteuid(getuid(this_object()));
   wep = clone_object(WEP);
   wep->move(this_object());
   command("wield rapier");
   arm = clone_object(ARM);
   arm->move(this_object());
   command("wear cloak");
}
