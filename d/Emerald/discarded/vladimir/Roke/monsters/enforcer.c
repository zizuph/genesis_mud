inherit "/std/monster.c";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"


void
create_monster()
{
   
   set_name("officer");
   set_race_name("human");
   set_long("This is one of Cove's law enforcers, they are new "+
      "here, but they seem to keep things in order.\n");
   set_short("law enforcement officer");
   add_adj("guard");
   
   default_config_npc(75);
   
   NEVERKNOWN;
   
   
   
   set_hp(10000);
   
   set_skill(SS_DEFENCE, 60);
   set_skill(SS_WEP_SWORD, 65);
   set_skill(SS_PARRY, 55);
   
   add_act("emote buffs his boots to a blinding shine.");
   add_act("emote watches you suspiciously.");
   
   set_act_time(10);
   
   set_alignment(300);
   
   ::create_monster();
   
   if (IS_CLONE)
      call_out("arm_me", 1);
   
}


void
arm_me()
{
   seteuid(geteuid(this_object()));
   
   clone_object("/d/Roke/vladimir/obj/armour/chainmail")->move(TO);
   clone_object("/d/Roke/vladimir/obj/weapons/esword")->move(TO);
   clone_object("/d/Roke/vladimir/obj/armour/lhelmet")->move(TO);
   clone_object("/d/Roke/vladimir/obj/armour/shield")->move(TO);
   
   
   command("wear all");
   command("wield all");
   seteuid(getuid(TO));
   
}
