/*
 * A zombie, found in the crypts
 *
 * 950421 by Rastlin
 *
 * 2004-12-11 - Cotillion
 * - Rewritten so the elf and dwarf zombies inherit this one.
 *
 */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h";
#include "/d/Krynn/pax/local.h";
inherit M_FILE
inherit "/d/Krynn/std/equip";
inherit "/std/act/action";

void first_move();

void
create_zombie()
{
    set_race_name("human");
    set_adj(({ "tall", "undead" }));

    equip(({ PWEAPON + "longsword",
             PARMOUR + "leather_arm" }));
}
               

void
create_krynn_monster()
{
    set_name("zombie");
    set_pname("zombies");    
    add_name(({"undead","warrior"}));    
    set_adj(({ "undead" }));
    
    set_long("He is one of the former guards of Kith-Kanan. In the " +
        "centuries since, however, an evil perversion has corrupted " +
        "the bodyguard, turning them into mindless zombies " +
        "commanded to perform only one task: kill all intruders.\n");
    set_gender(G_MALE);
    
    set_stats(({ 90, 90, 90, 90, 90, 100, }), 20);

    set_skill(SS_DEFENCE,      50);
    set_skill(SS_PARRY,        50);
    set_skill(SS_WEP_SWORD,    90);
    set_skill(SS_AWARENESS,    200);
    add_prop(LIVE_I_QUICKNESS, 10);
    add_prop(LIVE_I_SEE_DARK,  100);
    add_prop(LIVE_I_SEE_INVIS, 5);
    add_prop(NPC_I_NO_RUN_AWAY,  1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_UNDEAD, 30);
    add_prop(NPC_I_NO_FEAR, 1);
    
    set_aggressive(1);

    set_alignment(-120);
    set_knight_prestige(230);
    set_all_hitloc_unarmed(45);

    set_random_move(3);
    set_follow_time(0.3);
    set_restrain_path(({
        PSLA + "tomb", PSLA + "crypt"
    }));
    

    /* Config Hook */
    create_zombie();

    /* Make it do one move */
    set_alarm(rnd() * 3.0, 0.0, &first_move());
}

void
first_move()
{
    string *exits;

    exits = environment()->query_exit_cmds();
    if (sizeof(exits))
        command(exits[random(sizeof(exits))]);
}


mixed
oke_to_move(string exit)
{
    if (this_object()->query_follow())
        return 0;
    return ::oke_to_move();
}

public void
init_attack()
{
    if (!interactive(this_player()))
        return;
    
    ::init_attack();

    if (!query_follow() ||
        environment(query_follow()) != environment(this_object()))
    {
        set_follow(this_player());
    }
}
