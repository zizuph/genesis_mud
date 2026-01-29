/* 
 * Mortis 10.2014
 *
 * Standard base for all skeletons in the crypt underneath the
 * Tower of Arms. They take 1/4 damage from pierce, 1/2 damage from slash,
 * and full damage from bludgeon. Player gets messages about those while
 * fighting.
 *
 */

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include "../../../local.h"

inherit M_FILE
inherit AUTO_TEAM
inherit "/d/Krynn/std/act/actions";

/*prototype*/
void adjects();
void rattled_by(int rby);
int can_see_you(object obj);
string my_short();
string my_race();

string adjstr1, adjstr2;

public void
create_utoa_skeleton()
{
}

void
create_krynn_monster()
{
    set_name("skeleton");
    add_name(({"undead"}));

    adjects();
    
    set_short("@@my_short");
    set_long("Darkness blazes from the hollows in the eye sockets of this "
    + "dusty skeleton's skull. It's jaw gapes hungrily, and it moves with "
    + "a jagged, uneven gait.\n");
    set_race_name("@@my_race");
    
    set_skill(SS_DEFENCE,      60);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_AWARENESS,    20);
    set_skill(SS_BLIND_COMBAT, 20);

    set_stats((({140, 140, 140, 140, 140, 140})), 7);
    set_all_attack_unarmed(28, 18);
    set_all_hitloc_unarmed(20);

    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 31);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    add_prop(LIVE_M_NO_STUN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    /* Removed for balance
    add_prop(OBJ_I_RES_ELECTRICITY, 25); // No flesh to fry.
    add_prop(OBJ_I_RES_DEATH, 75); // They're already undead. */
    add_prop(OBJ_I_RES_MAGIC, 30); // Added for balance

    set_aggressive(1, 100);

    set_alignment(-200);
    set_knight_prestige(100);

    set_pick_up_team("skeleton");
    set_max_team_size_auto_join(5);

    set_act_time(120);
    add_act("emote clacks around aimlessly.");
    add_act("emote walks idly into a wall.");

    set_cact_time(60);
    add_cact("emote clacks its jaw hungrily at you.");
    add_cact("emote reaches for you with its clawed finger bones.");

    set_default_answer("@@def_answer");

    create_utoa_skeleton();
}

void
adjects()
{
    adjstr1 = one_of_list(({"darkness-eyed", "skull-cracked", "half-skulled",
        "dusty"}));

    adjstr2 = one_of_list(({"hunched", "frenzied"}));
}

string
my_short()
{
    return adjstr1 + " " + adjstr2 + " skeleton";
}

string
my_race()
{
    return one_of_list(({"human", "elf"}));
}

string
def_answer()
{
    command("moan confus");
    return "";
}

/* Returns 1 if the skeleton can see obj, 0 if not. Used in the skeleton's
 * room to only block exits when the skeleton can see the player. */
int
can_see_you(object obj)
{
    if ( !CAN_SEE(TO, obj))
    {
        return 0;
    }

    return 1;
}

/*
 * (varargs public mixed) hit_me(int wcpen, int dt, object attacker,
 * int attack_id, int target_hitloc = -1)
 *
 * Function name:   hit_me
 * Description:     Called to make damage on this object. The actually
 *                  made damage is returned and will be used to change
 *                  the score of the aggressor.
 * Arguments:       wcpen         - The wc-penetration
 *                  dt            - damagetype, use MAGIC_DT if ac will not
 *                                  help against this attack.
 *                  attacker      - Object hurting us
 *                  attack_id     - Special id saying what attack hit us. If 
 *                                  you have made a special attack, let the 
 *                                  id be -1
 *                  target_hitloc - Optional argument specifying a hitloc
 *                                  to damage.  If not specified or an
 *                                  invalid hitloc is given, a random
 *                                  one will be used.
 * Returns:         The hitresult as given by the external combat object.
 *                  For details, see 'sman cb_hit_me'.
 */
varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc)
{
    // Bludgeon does full damage, slash half, and impale a quarter.
    if (dt == W_IMPALE)
    {
        if (random(4) == 1)
        { 
            set_alarm(0.01, 0.0, &rattled_by(1));
        }
        wcpen = wcpen / 4; 
    }
    if (dt == W_SLASH)
    {
        if (random(4) == 1)
        { 
            set_alarm(0.01, 0.0, &rattled_by(2));
        }
        wcpen = wcpen / 2;
    }

    if (random(6) == 0 && dt == W_BLUDGEON)
    { 
        set_alarm(0.01, 0.0, &rattled_by(3));
    }

    return ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
}

void
rattled_by(int rby)
{
    if (rby == 1)
    {
        command("emote seems unaffected by the piercing blow.");
    }
    else if (rby == 2)
    {
        command("emote is only a little affected by the slashing blow.");
    }
    else
    {
        command("emote is rattled by the blow.");
    }
}


int
special_attack(object enemy)
{
    int pen;
    string attack, how, how2;
    mixed hitres;

    attack = "rend";

    if (random(6) == 1)
    {
        pen = 25 + random(100);
        hitres = enemy->hit_me(pen, W_SLASH, TO, -1);

        if (hitres[0] <= 0)
        {
            how = "but misses";
            how2 = how;
        }
        if(hitres[0] > 0)
        {
            how = "barely landing";
            how2 = how;
        }
        if(hitres[0] > 10)
        {
            how = "tearing some of your flesh";
            how2 = "tearing some of " + HIS(enemy) + " flesh";
        }
        if(hitres[0] > 20)
        {
            how = "tearing your flesh";
            how2 = "tearing " + HIS(enemy) + " flesh";
        }
        if (hitres[0] > 40)
        {
            how = "tearing deep through flesh";
            how2 = how;
        }
        if (hitres[0] > 60)
        {
            how = "sending chunks of flesh flying";
            how2 = how;
        }

        enemy->catch_msg(QCTNAME(TO) + " attempts to " + attack + " you with "
        + "its clawed hand " + how + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " attempts to " + attack + " "
        + QTNAME(enemy) + " with its clawed hand " + how2 + ".\n",
            ({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }

        return 1;
    }

    return 0;
}
