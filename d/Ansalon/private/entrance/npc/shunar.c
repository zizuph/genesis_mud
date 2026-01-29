/* Shunar, the evil mage for the kender quest, Gwyneth, August 1999 */

#include <money.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/kendermore/local.h"
#include <wa_types.h>

inherit "/std/act/action.c";
inherit AM_FILE

int seen_kender = 0;

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;
    set_name("shunar");
    set_adj("disfigured");
    add_adj("one-eyed");
    set_living_name("shunar");
    set_long("You wouldn't want to mess with this man. He looks like he " +
        "could destroy you with a wave of his little finger. His one eye " + 
        "wanders aimlessly, as if he can't see very well.\n");
    set_gender(G_MALE);
    set_race_name("human");
    set_title("De Winter, Renegade Mage");
    set_introduce(1);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " scowls at your offer, and warns you " + 
        "to leave now!\n");

    set_stats(({140,180,140,180,180,100}));

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 70);

    set_alignment(-1000);
    set_knight_prestige(500);

    set_act_time(25);
    add_act("say Where did I put that key? Maybe I dropped it somewhere.", 1);
    add_act("say That dragon better not be planning to escape again!", 1);
    add_act("say Blasted kender, always finding a way into my sanctuary.", 1);
    add_act("emote mumbles: Nobody will get into my workroom with my " + 
        "disk... Hey, where'd I put it?\nHe pats his pockets.", 1);
    add_act("say Nobody could find my secret passage, even if they did " + 
        "find their way in.", 1);

    set_random_move(5);

    set_default_answer("He shouts at you to begone, or else!\n");
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
    clone_object("/d/Ansalon/private/entrance/obj/srobe")->move(TO);
    command("wear all");

    seteuid(getuid(TO));
    MONEY_MAKE_GC(random(5)+5)->move(TO); 
}

int
special_attack(object enemy)
{
    int attacktype,
    pen,
    wloc;

    mixed hitres;

    string *hitloc,
    how, how2;

    attacktype = 1;

    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    if (attacktype == 1)
    {
        pen = 1000 + random(200);
        hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1);

        wloc = random(5);

        if (hitres[0] <= 0)
            how = "You feel no effect from the spell aimed at you";
            how2 = "The spell misses";
        if (hitres[0] > 0)
            how = "You feel a wash of pain go through you";
            how2 = "The spell hits";
        if (hitres[0] > 20)
            how = "You feel slightly burnt as sparks hit you";
            how2 = "The spell flings sparks at";
        if (hitres[0] > 40)
            how = "You feel a stab of pain as a bolt of magic hits you";
            how2 = "The spell strikes";
        if (hitres[0] > 60)
            how = "You yell out in pain as a fireball hits you";
            how2 = "A fireball hits";
        if (hitres[0] > 80)
            how = "You scream in pain as a bolt of lightning hits you";
            how2 = "A bolt of lightning hits";

        enemy->catch_msg(QCTNAME(TO) + " closes his eyes and chants a " +
            "few words that you can't hear. He raises his hand and points " + 
            "at you. " + how + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " closes his eyes and chants a " + 
            "few words that you can't hear. He raises his hand and points " + 
            "at " + 
            QCTNAME(enemy) + ". " + how2 + " " + HIM(enemy) + ".\n",
            ({ enemy, TO }));

        if (enemy->query_hp() <= 0)
            enemy->do_die(TO);

        return 1;
        }
    return 0;
}

