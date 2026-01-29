/* Based on aurak_leader by Aridor */
// Updated May 2003, Boron- Added Fael_ring.c to armours
// 6.10.2003, Blizzard - Magic missile causes double damage to 
//                       other Dragonarmy members

// June 11th 2006, By Navarre: Fixed check for blind, so it doesn't blind twice.
// Removed double damage for other dragonarmy members, dont like cheats like that.
// 2020-01-02 - Cotillion
// - Increased clone_unique chances as they were very low.

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/kurinost/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"f
#include <ss_types.h>
#include <macros.h>
#include "../local.h"

inherit "/d/Ansalon/guild/dragonarmy/npc/da_monster";
inherit AUTO_TEAM
inherit "/lib/unique";

public void
remove_horn()
{
    object horn = present("warhorn", this_object());

    if (objectp(horn))
        horn->remove_object();

}

void
create_da_monster()
{
    set_name("fael-thas");
  add_name("_big_bad_fael_");
    set_living_name("fael-thas");
    set_adj(({"evil", "shadowy"}));
    set_race_name("elf");
    set_long("This elf seems lithe and cunning. Exiled from the " +
       "fabled Silvanesti for the use of evil magics, he has " +
       "struck many bargains, and backstabbed many backs to " +
       "reach his current position of command in the White " +
       "Dragonarmy. A powerful magic user, and a skilled fighter, " +
       "Fael-theas trusts noone. Not even his army, or his " +
       "white dragon, Sleet.\n");

    set_color("white");
    set_dragonarmy_rank(4, 1);
    add_prop(LIVE_I_SEE_DARK, 2);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_PARRY, 95);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_2H_COMBAT, 90);
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 185);

    set_alignment(-1200);
    set_stats(({165, 225, 200, 205, 165, 185}));
    set_hp(query_max_hp());
    set_exp_factor(150);
    set_aggressive(1);

    set_act_time(3);
    add_act("emote sneers and mutters: Human are such morons...");
    add_act("emote barks: Who are you? State your name and rank!");
    add_act("emote smiles deviously: What have we here? More spies?" +
        " You'll end up like the icefolk.");
    add_act("emote boggles: How did you pass my guards? How did you " +
        "enter my castle?!");

    set_cact_time(10);
    add_cact("emote yells: Fool! You skills are nothing compared to my " +
      "magic!");
    add_cact("emote laughs: You look pretty enough to take to my bed!");
    add_cact("emote looks for an opening to take advantage of.");

    set_alarm(2.0, 0.0, "remove_horn");
    arm_me();
}

arm_me()
{
    object ob;

    setuid();
    seteuid(getuid());



    if(random(2))
    {
        ob = clone_object("/d/Krynn/icewall/castle2/obj/weapons/wknife");
        ob->move(TO, 1);

        ob = clone_unique("/d/Krynn/icewall/castle2/obj/weapons/fael_sword", 10,
            "/d/Krynn/icewall/castle2/obj/weapons/fael_crap_sword");
        ob->move(TO, 1);
    }
    else
    {
        ob = clone_unique("/d/Krynn/icewall/castle2/obj/weapons/wclaymore", 10,
            "/d/Ansalon/balifor/port_balifor/obj/claymore");
        ob->move(TO, 1);
    }

    if(random(5))
    {
        ob = clone_object("/d/Krynn/icewall/castle2/obj/armours/wplatemail");
    }
    else
    {
        ob = clone_object("/d/Krynn/icewall/castle2/obj/armours/wdragonarm");
    }
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/icewall/castle2/obj/armours/wdragonhelm");
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/icewall/castle2/obj/armours/wshinguard");
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/icewall/castle2/obj/armours/wheavyboots");
    ob->move(TO, 1);

    ob = clone_unique("/d/Krynn/icewall/castle2/obj/armours/fael_ring", 7);
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/common/scrolls/dominate_scroll");
    ob->move(TO, 1);

    command("wear all");
    command("wield all");
    present("warhorn")->remove_object();
}

void
return_intro(object ob)
{
    if(!present(ob, E(TO)))
    {
    return;
    }
    command("introduce me to "+ob->query_real_name());
}

void
add_introduced(string str)
{
    object ob = find_player(lower_case(str));
    if(ob && !ob->query_met(TO))
    {
    set_alarm(3.0, 0.0, &return_intro(ob));
    }
}

int
special_attack(object enemy)
{
        int     attacktype,
        pen,
        att,
        wloc;

        mixed hitres;

        string *hitloc,
        *attack,
        how,
        weapon;

        attacktype = random(6);

        if (!random(5))
        {
            command("emote eats a little white herb");
            TO->heal_hp(TO->query_hp()/2);
            command("cackle evil");
        }

        hitloc = ({"left arm","right arm","body","left leg","right leg"});

// ------------------------ CAST MAGIC MISSILE!

        if (attacktype == 1)
        {
            pen = 600 + random(450);

            pen -= pen * enemy->query_prop(MAGIC_I_RES_FIRE) /100;
            hitres = enemy->hit_me(pen, 40, TO, -1);

            wloc = random(5);
            att  = random(2);

            if (hitres[0] <= 0)
                how = "missing";
            if(hitres[0] > 0)
                how = "burning";

            enemy->catch_msg(QCTNAME(TO) +
              " utters the words: Kalith Karan, Tobanis-kar!"+
              " and points at you. Four missiles of magic leap from his "+
              "fingers, " +how+ " your " + hitloc[wloc] + ".\n");

            tell_room(E(TO), QCTNAME(TO) + " utters the words: " +
              " Kalith Karan, Tobanis-kar!" +
              " and points at " + QTNAME(enemy) + ". Four missiles " +
              "of magic leap from his "+
              "fingers, " +how+ " " + QTNAME(enemy) +
              "'s " + hitloc[wloc] + ".\n",({enemy, TO}));

            if (enemy->query_hp() <= 0)
            {
                enemy->do_die(TO);
                command("spit corpse");
            }
            return 1;
        }

// ------------------------ CAST BLINDNESS!

        if (attacktype == 2)
        {
            if(!P("blind_obj", enemy))
            {
              enemy->catch_msg(QCTNAME(TO) +
                " utters the words: Dulak!"+
                " and points at you.\n");
              enemy->catch_msg("You have been blinded!\n");

              tell_room(E(TO), QCTNAME(TO) + " utters the words: Dulak!"+
                " and points at " + QTNAME(enemy) +".\n",({enemy, TO}));
               clone_object(OBJK + "fael_blind")->move(enemy);
               return 1;
            }
            command("slash");
            return 1;
        }

//------------------------- HOLD PERSON!

    if(attacktype == 3)
    {
    enemy->catch_msg(QCTNAME(TO) + " whispers in the spidery " +
            "language of the magi!\n\nInvisible bonds reach out to " +
            "hold you!\n");

    tell_room(E(TO), QCTNAME(TO) + " whispers in the spidery " +
            "language of the magi!\n\n" + QCTNAME(enemy) + " suddenly " +
            "freezes in midstep!\n", ({ enemy, TO}));

    if(!P("fael_stun",enemy))

            {
        clone_object(OBJK + "fael_stun")->move(enemy);
            return 1;
            }

        command("slash");
    return 1;
    }


//------------------------SLASH!
            if (attacktype == 4)
{
       command("slash");
       return 1;
}


    return 0;
}

void
init_living()
{
    ::init_living();
}
