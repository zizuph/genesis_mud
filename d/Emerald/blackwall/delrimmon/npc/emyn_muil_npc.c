/*
 *    /d/Emerald/blackwall/delrimmon/npc/emyn_muil_monster.c
 *
 *    This is the standard file for npcs in the Blackwall Mountains.
 *    Some functions copied from /d/Gondor/morgul/npc/ithil_monster.c
 *
 *    Gorboth, Febuary 1997
 */
// Please use this pragma always:
#pragma strict_types
inherit "/d/Gondor/std/monster.c";
inherit "/d/Gondor/common/lib/logkill";

#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

static int  Wimpy_Run;

void
set_wimpy_run(int i)
{
    Wimpy_Run = i;
}

int
query_wimpy_run()
{
    return Wimpy_Run;
}

void
create_emyn_muil_npc()
{
    set_race_name("human");
}

nomask void
create_monster()
{
    int rnd     = random(11);

    seteuid(getuid(TO));
    add_name("_emyn_muil_npc");

    set_skill(SS_AWARENESS,    55+rnd);
    set_skill(SS_CLIMB,        25+rnd);
    set_skill(SS_BLIND_COMBAT, 80+rnd);

    set_skill(SS_WEP_SWORD,   30);
    set_skill(SS_WEP_POLEARM, 30);
    set_skill(SS_WEP_AXE,     30);
    set_skill(SS_WEP_KNIFE,   30);
    set_skill(SS_WEP_CLUB,    30);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK,   2);

    set_whimpy(45);
    set_wimpy_run(20);

    set_learn_pref( ({ 1, 1, 1, 0, 0, 1, }) );

    // Why this?
    set_exp_factor(50);

    create_emyn_muil_npc();
}

public int     query_knight_prestige() {return (- query_alignment()); }

public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    if (!interactive(ob))
        return;

    // We only remember the attacks on evils
    if (query_alignment() < 0)
        ob->add_prop(EM_I_DID_ATTACK,
                     ob->query_prop(EM_I_DID_ATTACK) + 1);
}

void
say_enemy(string str1, string str2)
{
    object enemy = query_attack();

    if (!objectp(enemy))
        return;
    if (!present(enemy,ENV(TO)))
        return;
    command("say " + str1 + query_attack()->query_race_name() + str2);
}

void
emote_enemy(string str)
{
    object  enemy = query_attack();

    if (!objectp(enemy))
        return;
    if (!present(enemy,ENV(TO)))
        return;
    command(str + " " + enemy->query_real_name());
}

void
loot_corpse()
{
    command("get all from corpse");
}

static void
get_money() 
{
    MONEY_MAKE_CC( 10 + random(11))->move(TO);
    MONEY_MAKE_SC(  1 + random( 6))->move(TO);
}

// Do you need this?
// If yes, where do you call it?
public void
set_restrain_path_with_delay()
{
    if (!query_restrain_path() || !sizeof(query_restrain_path()))
        set_restrain_path(implode(explode(file_name(ENV(TO)),"/")[0..3], "/"));
}
