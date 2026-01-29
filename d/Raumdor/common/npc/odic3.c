/* Odic (part 3), Sarr */
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file */
#include "defs.h"
#include <poison_types.h>
inherit STD_UNDEAD;
inherit "/std/combat/unarmed";


create_monster() 
{
   ::create_monster();
   set_name("odic");
   add_name("vine-plant");
   set_race_name("vine-plant");
   set_adj("glowing");
   set_short("glowing vine-plant");
   set_long("A living plant that glows with a purple and black aura!\n");
   set_skill(SS_DEFENCE,100);
   set_skill(SS_UNARM_COMBAT,100);
   add_prop(LIVE_I_NO_CORPSE,1);
   add_prop(LIVE_I_UNDEAD,55);
   set_act_time(3);
   set_cact_time(3);
   add_cact("emote blazes even brighter for a moment.");
   set_attack_unarmed(0, 40, 40, W_SLASH, 25, "lower left vine");
   set_attack_unarmed(1, 40, 40, W_SLASH, 25, "lower right vine");
   set_attack_unarmed(2, 40, 40, W_SLASH, 25, "upper left vine");
   set_attack_unarmed(3, 40, 40, W_SLASH, 25, "upper right vine");
   set_hitloc_unarmed(0,40,40,"lower body");
   set_hitloc_unarmed(1,40,10,"upper vines");
   set_hitloc_unarmed(2,40,10,"lower vines");
   set_hitloc_unarmed(3,40,40,"upper body");
}

string
query_combat_file()
{ 
    return "/d/Raumdor/common/std/chumanoid.c";
}


void
do_die(object killer)
{
    command("emote slumps to the ground with a thud, as a purple "+
    "mist flows out and vanishes!\n");
    ::do_die(killer);
}

int
special_attack(object enemy)
{
    object poison;
    if(random(10))
        return 0;
    tell_watcher(QCTNAME(TO)+" slashes "+ 
    QCTNAME(enemy) + " with a slime coated vine!\n",enemy);
    enemy -> catch_msg(QCTNAME(TO)+" slashes you"+
    " with a slime coated vine!\n");
    poison = clone_object("/std/poison_effect.c");
    poison->move(enemy);
    poison->set_time(20);
    poison->set_interval(5);
    poison->set_strength(40);
    poison->set_damage(({POISON_HP,100}));  
    poison->start_poison();
    return 1;
}
