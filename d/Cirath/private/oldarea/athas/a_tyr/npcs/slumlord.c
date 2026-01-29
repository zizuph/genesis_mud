/* slumlord: Evil master of Tyr's slums... */
 
#pragma strict_types
 
inherit "/d/Cirath/std/monster.c";
#include "defs.h"

void create_monster()
{
    ::create_monster();
    set_name("akabarl");
    set_adj("greasy");
    add_adj("slum");
    set_title("the Lord and Master of the Slums");
    set_race_name("half-elf");
    set_long("Like many of his mixed heritage, this half-elf has never fit "+
             "into either society. But here among the rabble of Tyr his "+
             "combination of determination, toughness, and speed has given "+
             "him control of the entire slum. For all that it's worth.\n");
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_stats(({50, 80, 90, 30, 10, 90}));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 40);
    set_skill(SS_WEP_AXE, 60);
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_2H_COMBAT, 60);

    set_alignment(-200);
 
    set_speak("You have nothing I need. Get out of my sight.");
 
    add_act("emote slaps a slum dweller around, demanding money.");
    add_act("emote sharpens his weapons.");
    add_act("emote looks around at his domain, and isn't impressed.");
    add_act("emote eyes a relatively comely homeless girl.");
    add_act("emote gazes at you threateningly.");
    add_act("say This is my turf, watch your step.");
    add_act("say I'll show all those so called pures who's better!");
    add_act("say I am better then anyone, human or elf.");
    add_cact("emote spins his weapons in a fancy combat move.");
    add_cact("emote chuckles quietly to himself.");
    add_cact("emote charges forward abruptly.");

    set_act_time(6);
    set_cact_time(3);
}

void arm_me()
{
    clone_object(ATH_WEAPON+"knife_sd.c")->move(TO);
    clone_object(ATH_WEAPON+"axe_ston.c")->move(TO);
    clone_object(ATH_ARMOUR+"robe_pnc.c")->move(TO);
    clone_object(ATH_ARMOUR+"head_hid.c")->move(TO);
    clone_object(ATH_ARMOUR+"body_pad.c")->move(TO);
    command("wield all");
    command("wear all");
}
