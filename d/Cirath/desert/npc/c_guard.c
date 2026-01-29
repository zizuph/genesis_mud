inherit "/std/monster";
#include "/d/Cirath/common/defs.h"
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Cirath/common/teamfnc.h"

#define RNDRACE ({"human","elf","half-elf","dwarf","mul","human"})
#define RNDADJ ({"tall", "strong", "muscular", "brutish"})
#define RNDADJ2 ({"wary","serious","nervous","sharp-eyed"})
#define RNDWEP ({"g_spear1","g_club1","g_axe1","g_sword1"})[random(4)]

mixed attackers;

create_monster()
{
    set_race_name(RNDRACE[random(6)]);
   set_adj(RNDADJ2[random(4)]);
   add_adj(RNDADJ[random(4)]);
    set_long("This looks to be one of the many guardsmen "
	+"used to patrol the outskirts of Tyr.  The guardsmen "
    +"come in all chapes and sizes, only sharing one thing.  "
	+"Their desire to please Kalak and stay alive.\n");
   set_alignment(-400);
   default_config_npc(125);
   set_skill(SS_WEP_SWORD,70);
   set_skill(SS_WEP_CLUB,70);
   set_skill(SS_WEP_POLEARM,70);
   set_skill(SS_WEP_AXE,70);
   set_skill(SS_PARRY,20);
   set_skill(SS_AWARENESS,30);
   set_skill(SS_DEFENCE,60);
   set_act_time(9);
   add_act("say Be careful out here, there have been braxat sightings.");
   add_act("say Stay close if you want to be safe.");
   add_act("emote stretches his weary back.");
   add_act("say The braxat can breath acid, be careful when messing with "
   	+"them.");
   add_act("smile tired");
   set_cact_time(9);
   add_cact("say Filthy traitor, to the dogs with ye!");
   add_cact("emote lunges forward, almost scoring a hit upon you.");
   add_cact("growl.");
   add_prop(LIVE_I_NEVERKNOWN,1);
}

void
arm_me()
{
  clone_object(DES_WEP+ RNDWEP)->move(TO);
   command("wield all");
    clone_object(DES_ARM + "g_body1")->move(TO);
    clone_object(DES_ARM + "g_helm1")->move(TO);
    clone_object(DES_ARM + "g_shield")->move(TO);
   command("wear all");
}

