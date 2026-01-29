/*
 * Necromancer of Underdark
 * Abaddon, June, 2020
 */
//#define do_die
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <options.h>
#include <money.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";

void arm_me();

void create_monster()
{
    int x, y, i;
    string *type, *phys;

    seteuid(getuid());

    type = ({"evil", "angry", "withdrawn", "suspicious", "watchful", "demonic", "powerful" });
    phys = ({"grey-skinned", "decrepit", "skinny", "raven-haired", "bald", "hunchbacked"});

    x = random(sizeof(type));
    y = random(sizeof(phys));

    npc_name = "necromancer";

    add_adj(type[x]);
    add_adj(phys[y]);
    add_prop(LIVE_I_NEVERKNOWN, 1);
     add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_O_SPELL_ATTACK, 1);

    set_race_name("necromancer");
    add_name("necromancer");
    add_name(npc_name);

    set_short(type[x] + " " + phys[y] + " necromancer");
    set_pshort(type[x] + " " + phys[y] + " necromancer");
    set_long("This is a necromancer found in the Underdark. It's bones appear w" +
        "weak, as if they would crumble under enough force. The malevolent g" +
        "low in its eye suggests it has been raised by some occult ritual.\n");

    add_prop(NPC_I_NO_FEAR, 1);     /* all undead defend each other */
    add_prop(CONT_I_WEIGHT,6128);  /* 27.5 Kg */
    add_prop(CONT_I_HEIGHT,63);     /* 63 cm */
    add_prop(LIVE_I_SEE_DARK,10);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 110 + random(25));
    set_base_stat(5, 70);

    set_alignment(0);
    add_prop(LIVE_I_SEE_DARK,10);

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);

   /* Actions */
    set_act_time(50);
    add_act("blanch ominous");
    add_act("stare");
    add_act("wring");
    add_act("stagger .");
    add_act("pace clum");
    add_act("grit teeth");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    arm_me();

//    set_random_move(8);
//    set_restrain_path(ROOM_DIR);

    set_pick_up_team(({"skeleton"}));
}


int
query_magic_res(string prop)
{
    if (prop == MAGIC_I_RES_EARTH ||
        prop == MAGIC_I_RES_FIRE  ||
        prop == MAGIC_I_RES_AIR   || 
        prop == MAGIC_I_RES_WATER ||
        prop == MAGIC_I_RES_ILLUSION )
        return 50;
    else
        return 25;
}
/*
//I would like to make these Skeletons
//immune to impaling damage, resistant
//to slashing damage, but very weak to
// bludgeoning damage.
*/

void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    arm = clone_object(ARM_DIR + "nec_robe");
    arm -> move(TO);
    arm = clone_object(ARM_DIR + "sv_shield");
    arm -> move(TO);
    wep = clone_object(WEP_DIR + "sv_axe");
    wep -> move(TO);

    command("wear all");
    command("wield all");

}
void
init_living()
{
    ::init_living();
    init_team_pickup();
}
void
do_die(object killer)
{
    object soul;
//    seteuid(getuid(this_object()));

    soul = clone_object("/d/Faerun/underdark/dark_dom2/obj/quest_soul");
    soul->move(this_object());

	MONEY_MAKE_SC(random(10) + 2)->move(this_object(), 1);
	MONEY_MAKE_GC(random(5) + 2)->move(this_object(), 1);
	MONEY_MAKE_PC(random(5) + 2)->move(this_object(), 1);

    ::do_die(killer);
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = this_object();
    /* We don't want the tiger to attack this way each round */
    if (random(10))
        return 0;                         /* Continue with the attack. */
    hitresult = enemy->hit_me(20 + random(30), W_IMPALE, me, -1);
    how = " without effect";
    if (hitresult[0] > 0)                 /* hitresult[0] yields the % hurt. */
        how == "";
    if (hitresult[0] > 10)
        how = " hard";
    if (hitresult[0] > 20)
        how = " very hard";
    me->catch_msg("You leap into your opponent's throut!\n" +
                  capitalize(enemy->query_pronoun()) + " is hit" +
                  how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " leaps into your throut!\n" +
                     "You are hit" + how + ".\n");
    tell_watcher(QCTNAME(me) + " leaps into " + QTNAME(enemy) + "!\n" +
                 capitalize(enemy->query_pronoun()) + " is hit" +
                 how + ".\n", enemy);
    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
    return 1; /*  Important! Returning 1 means this round was a special
	       *  attack round, don't use normal attacks too. */
}