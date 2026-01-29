inherit "/std/monster.c";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

#define DOWN_ROOM (CAPE + "guild/cellar")

void
create_monster()
{
    set_name("guard");
    set_race_name("human");
    set_long("This massive guard doesnt want just anybody\n"
        + " climbing the stairs.\n");
    set_short("guard");
    add_adj("massive");

    default_config_npc(135);
    
    NEVERKNOWN;

    set_hp(10000);

    set_skill(SS_DEFENCE, 95);
    set_skill(SS_WEP_POLEARM, 95);
    set_skill(SS_PARRY, 95);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);

    add_act("emote studies you.");
    add_act("emote stares at you.");
    add_act("emote smiles charmingly.");
    

    set_act_time(20);
    set_chat_time(50);
    


    ::create_monster();

    if (IS_CLONE)
        call_out("arm_me", 1);
}

void
arm_me()
{
    reset_euid();

    clone_object(KARGS + "obj/karg_platemail")->move(TO); 
    clone_object(KARGS + "obj/karg_ghelm")->move(TO);
    clone_object(CAPE + "obj/halberd")->move(TO);
    clone_object(KARGS + "obj/karg_greaves")->move(TO); 
    clone_object(KARGS + "obj/karg_bracers")->move(TO); 

    command("wear all");
    command("wield all");
}

public int
special_attack(object victim)
{
   int pen = F_PENMOD(30 + (100 - victim->query_encumberance_weight()),
      80 - victim->query_skill(SS_ACROBAT));
   if (random(10))
      return 0;
   COMMAND_SOUL->target(" gives you a hard shove.", victim);
   COMMAND_SOUL->all2act("gives", victim, " a hard shove.");
   victim->move_living("tumbling down the stairs", DOWN_ROOM, 1, 0);
   victim->hit_me(pen, W_BLUDGEON, this_object(), -1);
   if (victim->query_hp() <= 0)
   {
      victim->catch_msg("It feels like you broke your neck.\n");
      victim->do_die(this_object());
   }
   victim->catch_msg("You pick your bruised body up from the ground.\n");
   return 1;
}

