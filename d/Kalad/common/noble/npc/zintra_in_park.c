/*
    zintra_in_park.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/special";

#include "default.h"

object wep;

void
create_kalad_monster()
{
    set_name("figure");
    set_adj("shadowy");
    add_adj("dark");
    set_short("dark shadowy figure");
    set_long("You gaze upon what seems to be a dark-cloaked hooded "+
        "humanoid. It is counched over slightly, looking at you from within "+
        "its shadowy dark hood. A feeling of great evil seems to eminate from "+
        "it.\n"+
        "It has a black rose hanging from its belt.\n");

    set_gender(2);
    set_stats(({120,120,90,120,130,100}));
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_AWARENESS,150);
    set_skill(SS_2H_COMBAT,100);
    set_skill(SS_SNEAK,100);
    set_skill(SS_HIDE,100);
    set_alignment(-1000);
    set_knight_prestige(500);
    set_act_time(5);
    add_prop(NPC_I_NO_LOOKS,1);

    add_act("emote ponders slicing your neck.");

    set_cact_time(3);
    add_cact("emote hisses.");
    add_cact("emote glares at you with dark hatred.");

    add_prop(LIVE_I_NEVERKNOWN,1);

    add_equipment(({
        GUILDS + "shadow_walkers/thief_cloak",
        GUILDS + "shadow_walkers/thief_pants",
        GUILDS + "shadow_walkers/thief_vest",
        GUILDS + "shadow_walkers/thief_boots",
        NOBLE + "wep/knife_hooks",
        NOBLE + "wep/knife_hooks",
        }));

    // Configure our special attack
    set_default_special(25, W_SLASH, 85, 300, -1);
}

// Execute a special attack only if we have a weapon
int special_attack(object enemy)
{
    // This special requires having a weapon
    if (!(wep = query_weapon(W_RIGHT)))
       if (!(wep = query_weapon(W_LEFT)))
            return 0;

    return ::special_attack(enemy);
}

// Special has random weapon penetration
int
query_special_wcpen()
{
    return 300 + random(200);
}

// Give messages
void
special_did_hit(object enemy, string hdesc, int hitloc_id, int phurt,
   int damage_type, int damage)
{
    string msg;

    msg = "narrowly misses";
    switch (phurt)
    {
       case 0..9 :
        msg = "slightly scratches";
        break;
       case 10..19 :
        msg = "neatly stings";
        break;
       case 20..29 :
        msg = "neatly slices";
        break;
       case 30..39 :
        msg = "slashes hard against";
        break;
       case 40..49 :
        msg = "impales deeply into";
        break;
       case 50..59 :
        msg = "digs brutally into";
        break;
       case 60..69 :
        msg = "tears a bloody rip into";
        break;
       case 70..79 :
        msg = "shreds chunks of flesh from";
        break;
       case 80..89 :
        msg = "shreds blood and gore from";
        break;
       case 90..100 :
        msg = "nearly rips off";
        break;
    }

    enemy->catch_msg(QCTNAME(TO) + " lunges at you with its " + 
        wep->short() + " and " + msg +" your " + hdesc + ".\n");
    tell_room(ENV(TO), QCTNAME(TO) + " lunges at " + QTNAME(enemy)
        + " with its " + wep->short() + " and " + msg +
        " " + HIS(enemy) + " " + hdesc + ".\n", enemy);
}
