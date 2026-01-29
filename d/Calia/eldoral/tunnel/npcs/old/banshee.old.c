
/*
 * banshee.c
 *
 * An undead Banshee for the Undead Tunnels near
 * Eldoral
 *
 * Copyright (C): Jaacar (Mike Phipps), October 8th, 2003
 *
 * - Removed obsolete tell_watcher function (Petros)
 */


inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <formulas.h>
#include <composite.h>
#include "defs.h"

#define A_LEFT_HAND  0
#define A_RIGHT_HAND 1

#define H_HEAD 0
#define H_BODY 1

void
create_creature()
{
    object gloves;

    set_name("banshee");
    set_short("old grey-haired banshee");
    set_adj(({"old","grey-haired"}));
    set_race_name("banshee");
    set_long("This creature is the spirit of an evil female elf. "+
        "She is now merely a floating, luminous phantom of her former "+
        "self. She is old and withered and her hair is wild and unkempt. "+
        "She is wearing tattered rags and her face is a mask of pain and "+
        "anguish, but hatred and ire burn brightly in her eyes.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alignment(-600);
    set_gender(G_FEMALE);
    MONEY_MAKE_GC(random(2)+2)->move(this_object());
    add_prop(OBJ_I_VOLUME, 12000);
    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(MAGIC_I_RES_COLD,100);
    add_prop(MAGIC_I_RES_ELECTRICITY,100);
    add_prop(MAGIC_I_RES_MAGIC,50);
    add_prop(LIVE_I_UNDEAD,50);
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_aggressive(1);

    gloves = clone_object(TUN_ARMOURS+"snake_gloves");
    gloves->move(TO);
    TO->command("wear gloves");

    set_act_time(30);
	add_act("emote lets out a loud wail.");
	add_act("emote cries out in pain.");

    set_cact_time(15);
    add_cact("emote lets out a loud wail.");
    add_cact("emote slashes at you with her hand.");
    add_cact("emote touches your shoulder. You feel slightly drained.");

    set_stats(({(120+random(20)),(110+random(20)),
        (115+random(20)),(115+random(20)),
        (115+random(20)),(115+random(20))}));

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_DEFENCE, 100);

    set_attack_unarmed(A_LEFT_HAND, 40,40,W_SLASH,50,"left hand");
    set_attack_unarmed(A_RIGHT_HAND,40,40,W_SLASH,50,"right hand");

    set_hitloc_unarmed(H_BODY, ({40,40,40,40}), 80, "body");
    set_hitloc_unarmed(H_HEAD, ({15,15,15,15}), 20, "head");
}

/*
 * Function name: special_attack
 * Description  : Controls the dragonsaurus' special attacks in
 *                combat. Decides which to use, if any.
 * Arguments    : enemy - Object pointer to the living to attack.
 * Returns      : 1 - Made attack, no further attacks this round.
 *                0 - No special attack, continue normal combat round.
 */
public int
special_attack(object enemy)
{
    int player_dis, banshee_dis, difference;

    if (random(100))
        return 0;      /* 1 in 100 chance of special attack. */

    player_dis = enemy->query_stat(SS_DIS);
    banshee_dis = TO->query_stat(SS_DIS);

    difference = (banshee_dis + random(50)) - (player_dis + random(100));

    switch (difference)
    {
        case -250..0:
            tell_object(enemy, "The banshee lets out a loud wail directed "+
                "at you. You cover your ears and wait for her to finish.\n");
            enemy->tell_watcher("The banshee lets out a loud wail directed "+
                "at " + QTNAME(enemy) + ". "+capitalize(enemy->query_pronoun())+
                " covers "+enemy->query_possessive()+" ears and waits for her "+
                "to finish.\n",enemy);
            break;
        case 1..49:
            tell_object(enemy, "The banshee lets out a loud wail directed "+
                "at you. You begin to feel panicky and cover your ears, waiting "+
                "for her to finish.\n");
            enemy->tell_watcher("The banshee lets out a loud wail directed "+
                "at " + QTNAME(enemy) + ". "+capitalize(enemy->query_pronoun())+
                " looks very panicky and covers "+enemy->query_possessive()+
                " ears and waits for her to finish.\n",enemy);
            enemy->add_panic(500);
            return 1;
            break;
        default:
            tell_object(enemy, "The banshee lets out a loud wail directed "+
                "at you. You begin to feel extremely panicky and cover your "+
                "ears, waiting for her to finish.\n");
            enemy->tell_watcher("The banshee lets out a loud wail directed "+
                "at " + QTNAME(enemy) + ". "+capitalize(enemy->query_pronoun())+
                " looks extremely panicky and covers "+enemy->query_possessive()+
                " ears and waits for her to finish.\n",enemy);
            enemy->add_panic(1000);
            return 1;
            break;
    }
}

public void
do_die(object killer)
{
    write("The banshee lets out a loud wailing noise. There is a blinding "+
        "flash of light, causing you to avert your eyes for a moment. When "+
        "you look back, the banshee is gone.\n");
    ::do_die(killer);

}
