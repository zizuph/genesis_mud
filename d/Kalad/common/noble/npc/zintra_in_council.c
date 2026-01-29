/*
    zintral_in_council.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    set_name("figure");
    set_adj("shadowy");
    add_adj("dark");
    set_short("dark shadowy figure");
    set_long("A figure dressed all in black, you cannot make out a face "+
        "because it is wearing a hood. Shadows seem to gather around it, and "+
        "a feeling of death and evil radiates from it.\n"+
        "A black rose hangs from its belt.\n"+
        "A midnight-black sword sheath hangs from its back.\n");

    set_gender(2);
    set_stats(({120,160,140,120,130,120}));
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_WEP_SWORD,100);

    set_alignment(-1000);
    set_knight_prestige(1000);

    set_act_time(5);
    add_act("emote shifts slightly against the wall.");
    add_act("nod slight");
    add_act("emote clenches its fists.");
    add_act("emote hisses softly.");

    set_cact_time(3);
    add_cact("say Fool!");

    add_prop(LIVE_I_NEVERKNOWN,1);

    add_equipment(({
        GUILDS + "shadow_walkers/thief_cloak",
        GUILDS + "shadow_walkers/thief_pants",
        GUILDS + "shadow_walkers/thief_vest",
        GUILDS + "shadow_walkers/thief_boots",
        }));
}

void
call_to_remove_corpse(object enemy)
{
    call_other(ENV(TO), "call_to_remove_corpse", enemy);
}

void
attacked_by(object enemy)
{
    ::attacked_by(enemy);

    enemy->stop_fight(TO);
    stop_fight(enemy);

    enemy->catch_msg("You move to strike the "+short()+", but it "+
        "easily blocks your blow and grabs your arm, then spins, and "+
        "drives you against the wall, slaming your head hard!\n");
    tell_room(ENV(TO),QCTNAME(enemy)+" moves to strike the "+short()+
        ", but it easily blocks "+HIS(enemy)+" blow and grabs "+HIS(enemy)+
        " arm, then spins, and drives "+HIM(enemy)+" against the wall, "+
        "slamming "+HIS(enemy)+" head hard.\n",enemy);
    enemy->catch_msg("It then drives its knee into your gut, and you "+
        "loose your lunch.\n");
    tell_room(ENV(TO),"It then drives its knee into "+HIS(enemy)+" gut, "+
        "and "+HE(enemy)+" looses "+HIS(enemy)+" lunch.\n",enemy);
    enemy->command("puke");
    enemy->catch_msg("Then, you are flung across the room, landing "+
        "against the wall, and hitting your head hard, and you black out.\n");
    tell_room(ENV(TO),"Then, "+HE(enemy)+" is flung across the room, "+
        "landing against the wall, and hitting "+HIS(enemy)+" head hard, "+
        "and you see "+HIM(enemy)+" crumple to the ground.\n",enemy);

    seteuid(getuid());
    clone_object(NOBLE + "obj/doppar")->move(enemy, 1);
    enemy->inc_prop(LIVE_I_SEE_DARK, -10);

    set_alarm(3.0,0.0, &call_to_remove_corpse(enemy));
}

