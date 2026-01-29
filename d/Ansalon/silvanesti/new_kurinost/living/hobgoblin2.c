/*
 * hobgoblin.c
 *
 * A standard hobgoblin for the draconian camp in Kurinost.
 *
 * Copyright (C): Kellon, september 2012
 *
 * Cotillion - 2020-06-16
 * - Added missing axe skill
 * 
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

// I N H E R I T E D   F I L E S
inherit M_FILE

// D E F I N I T I O N S

// G L O B A L   V A R S
int gLevel = 8;

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
public void
create_krynn_monster()
{
    string adj1 = ONE_OF(HOBGSTR);
    string adj2 = ONE_OF(HOBGADJS);

    set_name("hobgoblin", HOBGNAME);
    set_short(adj1 + " " + adj2 + " hobgoblin");
    set_race_name("hobgoblin");
    add_adj(adj1);
    add_adj(adj2);

    add_prop(CONT_I_HEIGHT, 130 + random(30));
    add_prop(CONT_I_WEIGHT, 70000 + random(20) * 1000);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_long("Dark red eyes glare at you with hatred, as this " +
        adj1 + " " + adj2 + " hobgoblin turns to watch you. The " +
        "dark leathery brown skin on his upper body bulges, " +
        "revealing powerful muscles. Though he is wearing " +
        "mismatching pieces of metal armour, with a rusty " +
        "chainshirt underneath and shiny plates of metal strapped " +
        "together on top, he still looks quite well protected. " +
        "His broad face reveals a strong lower jaw with two sharp " +
        "and long protruding fangs in his mouth and a wide bony " +
        "forehead topped with a gritty knot of black hair.\n");

    for (int ct = 0; ct < 6; ct++)
    {
        set_base_stat(ct, gLevel * 5 + random(10) + 45);
    }

    set_skill(SS_WEP_AXE, (gLevel * 4) + 65);
    set_skill(SS_WEP_CLUB, (gLevel * 4) + 65);
    set_skill(SS_DEFENCE, (gLevel * 4) + 65);
    set_skill(SS_PARRY, (gLevel * 3) + 60);

    set_alignment(-200);
    set_knight_prestige(85);

    NEVERKNOWN;

    set_act_time(24);
    add_act("say Me 'it yoo 'ard with it!");
    add_act("say Hey! Scitch yoo!");
    add_act("say Cut and burn! Cut and burn!");
    add_act("say Bahhh! Yoo no look elf! Me kill elf!");
    add_act("emote looks worriedly towards the forest.");
    add_act("emote looks directly at you with his hateful red " +
        "eyes.");

    set_cact_time(20);
    add_cact("emote carefully aims for something and swings his " +
        "weapon wildly.");
    add_cact("shout Smegg! Me kill yoo!");
    add_cact("say Me 'it yoo 'ard with it!");
    add_cact("say Yoo da stoopid!");
    add_cact("emote glares at you with bloodlust in his dark red " +
        "eyes.");
    add_cact("emotes glares at you, smacking his lips in " +
        "anticipation.");
}

void
arm_me()
{
    setuid();
    seteuid(getuid());

    clone_object(RSWEAPON + "woodaxe")->move(TO, 1);
    command("wield all");

    clone_object(RSARMOUR + "hobgchain")->move(TO, 1);
    command("wear all");
}


/*
 *  FUNCTION : special_attack
 *  Arguments: object - the enemy.
 *  Returns  : int - 1 as this is a special attack.
 * 
 *  The hobgoblins have a special attack! Whee!
 *
 */
public int
special_attack(object enemy)
{
    mixed *hitresult;
    string hit_desc = "", watcher_desc = "";
    string hitloc, hithurt;
    
    if (!random(8))
    {
        hitresult = enemy->hit_me(100 + random(30), W_SLASH, TO, -1);

        switch (random(2))
        {
            case 0:
                watcher_desc = "Dark red eyes glaring with " +
                    "bloodlust, " + QTNAME(TO) + " rushes madly " +
                    "forward, trying to hit " + QTNAME(enemy) +
                    " with a wild swing of his felling axe. ";
                hit_desc = "Dark red eyes glaring with bloodlust, " +
                    QTNAME(TO) + " rushes madly forward, trying " +
                    "to hit you with a wild swing of his felling axe. ";
                break;

            case 1:
                watcher_desc = "With a scream of rage, " +
                    QTNAME(TO) + " rushes madly forward, trying " +
                    "to hit " + QTNAME(enemy) + " with a wild " +
                    "swing of his felling axe. ";
                hit_desc = "Screaming with rage, " + QTNAME(TO) +
                    " rushes madly forward, trying to hit you " +
                    "with a wild swing of his felling axe. ";
        }

        hitloc = hitresult[1];

        if (hitresult[0] > 20)
        {
            hithurt = ONE_OF(({ "crushing", "deadly", "mighty",
                "bloody" }));
            watcher_desc = watcher_desc + "THUMP! " +
                QCTNAME(enemy) + " staggers backwards trying to " +
                "recover, as " + QTNAME(TO) + " hits " + HIM(enemy) +
                " over the " + hitloc + " with a " + hithurt +
                " blow!\n";
            hit_desc = hit_desc + "THUMP! You stagger backwards " +
                "trying to recover, as you are hit over the " +
                hitloc + " with a " + hithurt + " blow!\n";
        }
        else
        if (hitresult[0] > 10)
        {
            hithurt = ONE_OF(({ "heavy", "wild", "strong",
                "ugly" }));
            watcher_desc = watcher_desc + "THUMP! Just as " +
                QTNAME(enemy) + " is about to make an easy " +
                "counterblow, " + QTNAME(TO) + " turns sharply " +
                "and makes a " + hithurt + " blow over the " +
                hitloc + " of " + QTNAME(enemy) + "!\n";
            hit_desc = hit_desc + "THUMP! Just as you are about " +
                "to make an easy counterblow, " + QTNAME(TO) +
                " turns sharply and makes a " + hithurt + " blow " +
                "to your " + hitloc + "!\n";
        }
        else
        if (hitresult[0] > 0)
        {
            hithurt = ONE_OF(({ "glancing", "feeble", "light",
                "faint" }));
            watcher_desc = watcher_desc + "THUMP! Swinging wildly " +
                "with his felling axe, he barely " +
                "manages a " + hithurt + " blow, connecting with " +
                QTNAME(enemy) + "'s " + hitloc + "!\n";
            hit_desc = hit_desc + "THUMP! Swinging wildly with " +
                "his felling axe, " + QTNAME(TO) +
                " barely manages a " + hithurt + " blow, " +
                "connecting with your " + hitloc + "!\n";
        }
        else
        if (hitresult[0] < 1)
        {            
            watcher_desc = watcher_desc + "SWOOSH! " + QCTNAME(TO) +
                " fumbles his attack completely and barely " +
                "manages to stay on his feet, trying to recover " +
                "from his wild swing!\n";
            hit_desc = hit_desc + "SWOOSH! " + QCTNAME(TO) +
                " fumbles his attack completely and barely " +
                "manages to stay on his feet, trying to recover " +
                "from his wild swing!\n";
        }

        enemy->catch_msg(hit_desc);
        tell_watcher(watcher_desc, enemy);

        if (enemy->query_hp() < 1)
        {
            enemy->do_die(TO);
        }
    }
    else
    {
        if (!random(5))
        {
            watcher_desc = ONE_OF(({
                QCTNAME(TO) + " screams in anger as he misses an " +
                    "opportunity for real bloodshed!\n",
                QCTNAME(TO) + " stumbles forward, looking quite " +
                    "foolish as he tries to recover his " +
                    "balance!\n",
                QCTNAME(TO) + " swings his felling axe " +
                    "wildly around, determined to hit anything!\n",
                QCTNAME(TO) + " growls with hated, switching his " +
                    "grip on the felling axe!\n" }));

            tell_watcher(watcher_desc);
        }
    }

    return 1;
}
