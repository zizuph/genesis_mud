/*
 * 2004-12-20 - Cotillion
 * - 10% chance to clone either of the weapons, higher max amount.
 *   Should work better with long uptmies.
 *
 * 2004-12-30 - Cotillion
 * - Increased chances to 20% and 30% for axe, maul
 */

/* Navarre 25th June 2006: Added a space in the attack description
 * was fingerat instead of finger at.
 */

/* Navarre July 3rd 2006, fixed typo, wounds begin to heal, instead of begins */

/* Added minor vulnerability to fire and acid.
 * Reduced xp bonus by 5% to account for that.
 * - Arman, July 2016
 */

#pragma save_binary
#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <composite.h>

inherit AM_FILE
inherit "/lib/unique";
inherit "/d/Krynn/open/auto_teaming";

object weapon;
object ring;

void
create_krynn_monster()
{
    set_name("thorr-kan");
    add_name("thorrkan");
    set_race_name("troll");
    set_living_name("thorr-kan");
    set_title("Rocksmasher, the High Shaman of the Fifth Talisman"); 
    set_adj(({"wise","arrogant"}));
    set_short("wise arrogant forest troll");
    set_gender(0);
    set_long("The " + short() + " is a large humanoid creature, covered " +
        "in thick fur. Long, yellow fangs reach out of his cruel mouth, " +
        "and a foul smell surrounds him. His green-grey skin makes him "+
        "blend in with the forest, making him very hard to see. These "+
        "trolls might appear stupid, but as you look into their dark eyes "+
        "you sense a form of intelligence.\n"+
        "A sphere of force surrounds his body.\n"+
        "He is a shaman of the fifth talisman.\n"+
        "He has a tattoo on his forehead that looks like a five-pointed star.\n"+
        "He has long black hair.\n"+
        "He is wearing a feather-covered amulet around his neck.\n");
    set_knight_prestige(800);

    set_stats(({250,210,270,170,140,220}));
    set_introduce(1);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_BLIND_COMBAT, 80);
    set_alignment(-900);
    set_all_hitloc_unarmed(45);
    set_pick_up_team(({"troll"}));
    add_prop(LIVE_I_SEE_DARK, 3);

    // some vulnerability to fire
    add_prop(OBJ_I_RES_FIRE, -10);

    // some vulnerability to acid
    add_prop(OBJ_I_RES_ACID, -10);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_hp(query_max_hp());
    set_exp_factor(195);


    if (random(2))
    {
        weapon = clone_unique(MWEP + "crystalAxe", 3, MWEP + "tree",0, 20);
        weapon->move(TO, 1);
    }
    else
    {
        weapon = clone_unique(MWEP + "war_maul", 4, MWEP + "tree",0, 30);
        weapon->move(TO, 1);
    }

    if (random(3))
    {
        ring = clone_object(MOBJ + "ring");
        ring->move(TO,1);
    }

    command("wear all");
    command("wield all");
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc,
    hps;

    mixed hitres;

    string *hitloc,
    *attack,
    how,
    weapon;

    attacktype = random(8);

    hitloc = ({"left arm","right arm","body","left leg","right leg","head"});

    if((attacktype == 1) && (TO->query_hp() < 1500))
    {
        TO->heal_hp(1500);
        tell_room(E(TO), QCTNAME(TO) + "'s wounds begin to heal!\n",({TO, TO}));
        return 1;
    }

    if (attacktype == 1)
    {
        pen = 600;
        hitres = enemy->hit_me(pen, 40, TO, -1);

        wloc = random(6);
        att  = random(2);

        if (hitres[0] <= 0)
            how = "missing";
        if(hitres[0] > 0)
            how = "slightly burning";
        if(hitres[0] > 10)
            how = "burning";
        if(hitres[0] > 20)
            how = "igniting";
        if (hitres[0] > 40)
            how = "surrounding";
        if (hitres[0] > 60)
            how = "engulfing";

        enemy->catch_msg(QCTNAME(TO) + 
          " mumbles strange words while pointing a finger"
          + " towards you. A bolt of fire leaps from the "+
            "palm of his hand, " +how+ " your " + hitloc[wloc] + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " points a finger " +
          "at " + QTNAME(enemy) + ". A bolt of fire " +
          "leaps from the palm of his hand, " + how + " " + QTNAME(enemy) +
          "'s " + hitloc[wloc] + ".\n",({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }
        return 1;
    }
    return 0;
}
