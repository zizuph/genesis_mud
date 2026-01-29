/* Female mercenary hiding out in Kendermore, Gwyneth, June 15, 1999 */

#include <money.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>

inherit "/std/act/action.c";
inherit "/lib/unique";
inherit AM_FILE

object mknife; 

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;
    set_name("jaine");
    add_name("jane_merc");
    set_adj("hardened");
    add_adj("muscular");
    set_long("Before you stands an imposing woman. Her eyes are cold " +
        "and hard, the eyes of a hired killer. She seems to be hiding " + 
        "from someone, and obviously doesn't like your presence.\n"); 
    set_gender(G_FEMALE);
    set_race_name("human");
    set_title("Raka, Mercenary for Hire");
    set_introduce(1);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " looks suspiciously at your offer. She " + 
        "is obviously too much of a mercenary to accept anything at face " + 
        "value.\n");

    set_stats(({140,140,140,110,110,120}));

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 70);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_AWARENESS, 100);

    set_alignment(-200);
    set_knight_prestige(5);

    set_act_time(25);
    add_act("say They'll never find me here.");
    add_act("peer nervously");
    add_act("@@sheathe_knife@@");
    add_act("say I wish I hadn't lost my sword. This knife is only " + 
        "just acceptable.");

    set_cact_time(20);
    add_cact("emote shouts out a fierce battle cry!");
    add_cact("emote gets a cold look on her face, and her eyes blaze hotly.");
    add_cact("scowl angrily");
    add_cact("fight offensively");
    add_cact("fight normally");

    set_default_answer("She scoffs at your questions.\n");
    set_alarm(1.0,0.0,"arm_me");
    seteuid(getuid(TO));
}

/* Function name : Arm me
 * Description : Loads, wears and wields armour and weapons.
 * Returns : Nothing
*/

void
arm_me()
{

    clone_object(KOBJ + "mercbrig")->move(TO, 1);
    clone_object(KOBJ + "mercbracers")->move(TO, 1);
    clone_object(KOBJ + "mercboots")->move(TO, 1);
    clone_object(KOBJ + "mercpants")->move(TO, 1);
    clone_unique(KOBJ + "merchelm", 7, KOBJ + "fruit")->move(TO, 1);

    command("wear all");

    seteuid(getuid(TO));
    MONEY_MAKE_GC(random(5)+5)->move(TO); 
}

/* Function name : Attacked by (Not working)
 * Description : Clones the mercenary's knife and wields it when attacked.
 * Returns : Null
*/

void
attacked_by(object ob)
{
    ::attacked_by();
    if (mknife) /* Make sure it only happens once. */
        return;

    mknife=clone_object(KOBJ + "mercknife");
    mknife->move(TO);
    command("emote draws a knife from her boot.");
    command("wield all");
}    

/* Function name : Special attack
 * Description : Causes extra damage during combat.
 * Returns : 1 or 0
*/

int
special_attack(object enemy)
{
    int attacktype,
    pen,
    wloc;

    mixed hitres;

    string *hitloc,
    how,
    weapon;

    if (!sizeof(query_weapon(-1)))
        return 0;

    attacktype = random(4);

    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    weapon = query_weapon(-1)[0]->query_short();

    if (attacktype == 1)
    {
        pen = 350 + random(200);
        hitres = enemy->hit_me(pen, W_SLASH, TO, -1);

        wloc = random(5);

        if (hitres[0] <= 0)
            how = "her " + weapon + " barely missing";
        if (hitres[0] > 0)
            how = "her " + weapon + " lightly slashing";
        if (hitres[0] > 10)
            how = "her " + weapon + " slashing";
        if (hitres[0] > 20)
            how = "her " + weapon + " heavily slashing";
        if (hitres[0] > 40)
            how = "her " + weapon + " piercing";
        if (hitres[0] > 60)
            how = "her " + weapon + " deeply piercing";

        enemy->catch_msg(QCTNAME(TO) + " flashes her eyes angrily at you, " +
            how + " your " + hitloc[wloc] + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " flashes her eyes angrily at " + 
            QCTNAME(enemy) + ", " + how + " " + POSSESSIVE(enemy) + " " + 
            hitloc[wloc] + ".\n", ({ enemy, TO }));

        if (enemy->query_hp() <= 0)
            enemy->do_die(TO);

        return 1;
        }
    return 0;
}

/* Function name : Sheathe knife (Not working)
 * Description : Removes the knife from inventory randomly when not
 *     fighting.
 * Returns : Emote
*/

string
sheathe_knife()
{
    if (TO->query_attack() != 0)
        return "emote puts a hand on her empty scabbard and scowls";
    if (mknife && (E(mknife) == TO))
    {
        mknife->remove_object();
        return("emote sheathes a knife in her boot.");
    }
    return "emote puts a hand on her empty scabbard and sighs.";
}
 
