#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"
inherit "/d/Roke/common/monster";

int has_introduced=0;
int wood;
void
create_monster()
{
   set_name("faylan");
   set_living_name("faylan");
   
   set_title(" the High Lord Traveller");
   set_race_name("human");
   add_name("traveller");
   add_adj("large");
   add_adj("burly");
   set_long("This is a big burly man that smiles at you with\n"
    + "all four of his teeth.\n");
   
   default_config_npc(100);
   
   set_random_move(20);
   set_restrain_path(ATUAN);
   
   set_hp(10000);
   
   set_alignment(100);
   
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_PARRY, 75);
   set_skill(SS_WEP_AXE,95);
   
   add_act("emote growls satanically at you");
   add_act("emote rubs his beer belly.");
   add_act("emote sharpens his axe.");
   add_act("say I have travelled these lands for years.");
   add_act("say Travelling is my life.");
   add_act("emote looks wistfully into the distance.");
   add_cchat("RaaaaaarrrrggghH!");
   
   
   set_act_time(2);
   set_cact_time(1);
   set_chat_time(1);
   
   set_default_answer("I dont really have much to say.\n");
   
   
   
   ::create_monster();
   
   if (IS_CLONE)
      call_out("arm_me", 1);
   
   trig_new("%w 'introduces' %s","react_introduce");
   
}

void
arm_me()
{
   seteuid(geteuid(this_object()));
   
   clone_object("/d/Roke/vladimir/obj/weapons/faxe")->move(TO);
   clone_object("/d/Roke/vladimir/obj/armour/fcloak")->move(TO);
   clone_object("/d/Roke/vladimir/obj/armour/fboots")->move(TO);
   
   command("wield all");
   command("wear all");
   seteuid(getuid(TO));
   
}

void
react_introduce(string person,string who)
{
   if (!has_introduced)
      {
      call_out("introduce_me",6);
      has_introduced=1;
      call_out("remove_int",30);
   }
}

void
introduce_me()
{
   command("introduce myself");
}

void
remove_int()
{
   has_introduced=0;
}

