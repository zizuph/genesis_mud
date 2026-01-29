/* This npc is cloned by /d/Emerald/caverns/*jail.c
*/
inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"

void
create_monster()
{
   set_name("guard");
   set_short("cocky alert guard");
   set_adj("alert");
   add_adj("cocky");
   add_name("pirate");
   set_long("This guy is on his toes!\n");
   set_pshort("guards");
   set_stats(({60,50,50,41,56,62}));
   set_hp(TO->query_max_hp());
   set_skill(SS_WEP_AXE, 60);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_PARRY, 40);
   set_chat_time(5);
   add_chat("With my trusty axe at my side, there "+
      "won't be any escapes around here!");
   add_chat("Those prisoners don't stand a chance against "+
      "me!");
   add_chat("I can't wait for one of those land lovers to "+
      "try and make a run for it!");
   MONEY_MAKE_SC(10+random(3))->move(TO);
   MONEY_MAKE_GC(1+random(2))->move(TO);
   seteuid(getuid(this_object()));
   set_alarm(1.0,0.0,"arm");
}


void
arm()
{
   object axe, platemail, key;
   seteuid(geteuid());
   axe = clone_object(THIS_DIR+"arm/axe");
   seteuid(geteuid());
   platemail = clone_object(THIS_DIR+"arm/gplatemail");
   axe ->move(TO);
   platemail ->move(TO);
   key = clone_object(THIS_DIR+"obj/g_key2");
   key ->move(TO);
   command("wield all");
   command("wear all");
}




