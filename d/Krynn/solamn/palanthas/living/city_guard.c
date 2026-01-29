/* 
 * Mortis 02.2006
 *
 * Standard city guards found in the guard towers
 * in each district of Palanthas.
 *
 * If players can become Constable, these will change
 * to match their guild, but this is the default guard.
 *
 * Mortis 09.2014
 * Reduced propensity to spam when attacked/attacking.
 *
 */

#include "../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

#define MY_CLOTHING      NOBLE + "arms/parmour"
#define MY_ARMOUR        MERCH + "arms/larmour"
#define MY_GENERAL       MERCH + "obj/lgeneral"

inherit M_FILE
inherit AUTO_TEAM
inherit "/d/Krynn/std/act/actions";

/*prototype*/
void adjects();
void arm_me();
void arm_me2();

int gender;
string adjstr1, adjstr2;

void
create_krynn_monster()
{
    seteuid(getuid(TO));

    set_name("guard");
    add_name(({"guardsman"}));

    adjects();
    
    set_short("@@my_short");
    set_long("A young guardsman of the city of Palanthas sworn to uphold "
    + "the laws and treat the citizenry with respect.  The guard's open "
    + "white tunic bears " + "@@constable_symbol@@" + " above its left "
    + "breast.\n");
    set_race_name("human");
    
/*    set_size_descs("tall", "of normal width");
    set_appearance(6);*/
    
    set_skill(SS_DEFENCE,      50);
    set_skill(SS_PARRY,        20);
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_AWARENESS,    25);
    set_skill(SS_WEP_SWORD,    50);
    set_skill(SS_WEP_CLUB,     50);
    set_skill(SS_WEP_POLEARM,  45);
    set_skill(SS_BLIND_COMBAT, 20);

    set_stats((({75, 45, 55, 35, 35, 55})), 7);
    set_all_attack_unarmed(12, 8);
    set_all_hitloc_unarmed(5);

    set_alignment(400);
    set_knight_prestige(-75);

    set_pick_up_team("guard");
    set_max_team_size_auto_join(5);

    set_act_time(50);
    add_act("emote polishes a heap of armour.");
    add_act("emote polishes a rack of weapons.");
    add_act("emote straightens an open white tunic.");
    add_act("time");
    add_act("smell");
    add_act("emote ponders visiting the Plaisir district when the shift "
    + "ends.");
    add_act("emote contemplates doing some reading in the Great Library "
    + "when the shift ends.");
    add_act("say Any of you want to peruse the shops of the Arms district "
    + "when the shift ends?");
    add_act("say Who's up for a drinking contest at the Green Twitch Inn "
    + "after the shift ends?");
    add_act("say I heard Chief Constable Hagen jailed another thief.  He's "
    + "relentless.");
    add_act("say Miscreants in the marble city do not prosper, not with "
    + "Hagen around.");

    set_cact_time(16);
    add_cact("shout Violent offender!  Prepare the shackles!");
    add_cact("emote blocks the exit decrying:  It's jail or Lars for you, "
    + "miscreant.");
    add_cact("emote pulls a pair of iron shackles from his belt.");
    add_cact("emote attempts to shackle you with a pair of iron shackles.");

    add_ask(({"hagen", "chief", "constable"}), "say Hagen is the Chief "
    + "Constable of Palanthas.  He's unstoppable, and will throw any "
    + "miscreants in jail without a moment's hesitation.  They either "
    + "<surrender> or die, and that's always been the case.", 1);
    add_ask("jail", "say The jail is still in the Palace, but they're "
    + "building a newer, larger jail off the Palatial plaza.  I don't "
    + "think Lord Amothus appreciates using the palace as a jail.", 1);
    add_ask(({"city", "palanthas"}), "say Palanthas' majesty is unrivaled!  "
    + "The marble city is the best place to live in all the realms, and we "
    + "keep it completely safe.  The city has never been compromised.", 1);
    add_ask(({"guard", "guards", "guardsman"}), "say The city guard is well-"
    + "trained, competent, and motivated to keep Palanthas completely safe.  "
    + "That I promise.", 1);

    set_default_answer("@@def_answer");

    set_alarm(1.0, 0.0, "arm_me");
    set_alarm(2.0, 0.0, "arm_me2");
}

void
adjects()
{
    adjstr1 = one_of_list(({"young", "cleanly", "smooth-chinned",
    "watchful-eyed", "youthful", "thin"}));

    adjstr2 = one_of_list(({"blond-haired", "black-haired", "buzz-cut",
    "brown-haired", "side-burned", "moustachioed", "short-haired"}));
    
    set_gender(G_MALE);
}

string
my_short()
{
    string gend = "male";

    if (TO->query_gender() == G_FEMALE)
    { gend = "female"; }

    return adjstr1 + " " + adjstr2 + " " + gend + " guard";
}

string
def_answer()
{
    command("say You should ask my commander, citizen.");
    return "";
}

void
arm_me()
{
    string whichbody, whichwep;
    object gpants, gwep;

    if (random(4) == 1)
        whichbody = "shirt";
    else
        whichbody = one_of_list(({"coat", "vest"}));

    // Guard's standard weapon.
    whichwep = one_of_list(({"gwep_sword", "gwep_polearm", "gwep_club"}));
    gwep = clone_object(OBJ + whichwep);
    gwep->move(TO);

    if (whichwep != "gwep_polearm")
        clone_object(OBJ + "garmour_shield")->move(TO);

    // Guard's custom legwear.
    gpants = clone_object(MY_CLOTHING);
    gpants->set_armour_data("the city guard" + "&&"
                            + "loose" + "&&"
                            + "white" + "&&"
                            + "linen" + "&&"
                            + "pants");
    gpants->move(TO);

    // Guard's standard issue boots.
    clone_object(OBJ + "garmour_boots")->move(TO);

    // Guard's custom body armour.
    clone_object(OBJ + "garmour_" + whichbody)->move(TO);

    command("wield all");
    command("wear all");
}

void
arm_me2()
{
    command("wield all");
    command("wear all");
}

string
constable_symbol()
{
    return "a symbol of an upturned sword over the white palatial tower";
}

void
attack_func(object enemy)
{
    if (!CAN_SEE(TO, enemy))
    { return; }
    
    if (random(5) != 1)
    {
        command("shout Miscreant! Employ force!");
    }
    action_attack(enemy);
}

void
init_living()
{
    init_team_pickup();
    ::init_living();

    if (TP->query_prop(LIVE_I_ATTACKED_PALANTHAS) == 1)
    {
        set_alarm(0.5, 0.0, &attack_func(TP));
        return;
    }

}

void
attacked_by(object ob)
{
    ob->add_prop(LIVE_I_ATTACKED_PALANTHAS, 1);

    ::attacked_by(ob);
}

int
special_attack(object enemy)
{
    int pen, att, wloc, weptype, damtype;
    string hitloc, attack, how, how2, weapon;
    mixed hitres;
    object *wep = query_weapon(-1);

    if (!sizeof(wep))
    return 0;

    weapon = wep[0]->query_short();
    weptype = wep[0]->query_wt();

    switch (weptype)
    {
        case W_POLEARM:
            attack = "catch";
            damtype = W_IMPALE;
            hitloc = "body";
            wloc = A_TORSO;
            break;
        case W_SWORD:
            attack = "pierce";
            damtype = W_IMPALE;
            hitloc = "body";
            wloc = A_TORSO;
            break;
        case W_CLUB:
            attack = "clobber";
            damtype = W_BLUDGEON;
            hitloc = "head";
            wloc = A_HEAD;
            break;
        default:
            attack = "strike";
            damtype = W_SLASH;
            hitloc = "legs";
            wloc = A_LEGS;
            break;
    }

    if (random(6) == 1)
    {
        pen = 25 + random(100);
        hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

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
            how = "incapacitating you slightly";
            how2 = "incapacitating " + HIM(enemy) + " slightly";
        }
        if(hitres[0] > 20)
        {
            how = "incapacitating you greatly";
            how2 = "incapacitating " + HIM(enemy) + " greatly";
        }
        if (hitres[0] > 40)
        {
            how = "with well-trained power";
            how2 = how;
        }
        if (hitres[0] > 60)
        {
            how = "with deadening force";
            how2 = how;
        }

        enemy->catch_msg(QCTNAME(TO) + " attempts to " + attack + " your "
        + hitloc + " with " + HIS(TO) + " " + weapon + " " + how + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " attempts to " + attack + " "
        + QTNAME(enemy) + "'s " + hitloc + " with " + HIS(TO) + " " + weapon
        + " " + how2 + ".\n", ({enemy, TO}));

        if (enemy->query_hp() <= 0)
            enemy->do_die(TO);

        return 1;
    }

    return 0;
}
