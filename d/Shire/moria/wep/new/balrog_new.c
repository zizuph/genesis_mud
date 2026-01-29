/*

Balrog
by Palmer
January 2003

Recode of various Balrogs in ~shire/moria/npc

ChangeLog:

April 10 2004 - Palmer  - Changed alignment to -1200
March 26 2013 - Gorboth - Modifications included for April Fool's Day

*  Created by Znagsnuf.
*
*  Date:                      What is done:                            By whom:            
*  ----------------------------------------------------------------------------
*  01/05-17                   Started remaking it                      Znagsnuf
*  01/05-17      Keeping most of the core from previous versions       Znagsnuf
*
*/

inherit "/std/monster";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/cmd/std/command_driver";

inherit "/d/Shire/lib/kill_logger";

#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <const.h>
#include <time.h>

#include "/d/Shire/moria/defs.h"
#include "/d/Shire/common/lib/evilkill.h"
#include "/d/Shire/private/shire_admin.h"

#define A_L_WING    262144
#define A_R_WING    524288

// Has he wielded his weapons?
public int weapons = 0;

// Weapon1, and Weapon2
public object wep1, wep2, wings;   

// The different stages.
public int stage0 = 1;
public int stage1 = 0;
public int stage2 = 0;
public int stage3 = 0;

/* Function Prototypes */
public varargs void  arm_me();
public void       draw_weapons();
public void       remove_weapons();

void
create_monster()
{
    ::create_monster();
    int i;

    set_race_name("balrog");
    set_title("the Evil Lord in Moria, Durin's Bane, Fire Demon of Might");
    set_name("gash");
    add_name("_balrog_in_moria");
    set_gender(G_MALE);

    set_adj( ({"huge", "hulking", "muscular"}) );
    set_short("huge hulking balrog");
    set_long("Standing before you is one of the most feared creatures ever, "
           + "the " + short() + " of Moria. The " + short() + " is a huge, "
           + "hulking, man-like demon. Fire streams from " 
           + HIS_HER(this_object()) + " mane and " + HIS_HER(this_object()) 
           + " nostrils breathe flames. " + HIS_HER(this_object()) + "limbs "
           + "are huge and muscular and look strong enough to smash anything. "
           + "Giant wings extend from "+ HIS_HER(this_object()) + " back, "
           + "flapping idly. Darkness and fear surround the " + short() 
           + ".\n");

    set_stats( ({ 380, 347, 416, 200, 170, 288}) );

    set_skill(SS_WEP_CLUB,     100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_WEP_SWORD,    100);
    set_skill(SS_DEFENCE,      100);
    set_skill(SS_PARRY,        100);
    set_skill(SS_2H_COMBAT,    100);
    set_skill(SS_AWARENESS,    100);
    set_skill(SS_BLIND_COMBAT, 100);

    add_prop(CONT_I_WEIGHT, 11400*1000);  /* 11.4 tons */
    add_prop(CONT_I_HEIGHT,      549);
    add_prop(LIVE_I_SEE_DARK,    100);    /* Night vision. */
    add_prop(LIVE_I_SEE_INVIS,    99);    /* Sees all but wizards */
    add_prop(LIVE_I_QUICKNESS,    50);    /* Fast monster. */
    add_prop("_live_m_no_drain",   1);
    add_prop("_ranger_i_not_brawl",1);
    add_prop(NPC_I_NO_RUN_AWAY,    1); // No wimpy.
    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(NPC_I_NO_FEAR,        1);

    set_appearance_offset(50);
    set_scar(6);

    // Wear his wings.
    arm_me();

    // He attacks 100% of the time.
    set_attack_chance(100);
    set_aggressive(1);

    set_attackuse(120);

    set_attack_unarmed(W_RIGHT, 100,   90, W_SLASH,    25, "right claw");
    set_attack_unarmed(W_LEFT,  100,   90, W_SLASH,    25, "left claw");
    set_attack_unarmed(W_FOOTR,  90,  100, W_BLUDGEON, 20, "right foot");
    set_attack_unarmed(W_FOOTL,  90,  100, W_BLUDGEON, 20, "left foot");
    set_attack_unarmed(W_BOTH,  100,  100, W_IMPALE,   30, "horns");
     
    // Give him horns as leftover.
    add_leftover("/d/Shire/moria/wep/new/balrog_horn", "horn", 1, 0, 1, 1);

    // Remove std hit locations and define our own.
    for (i=0; i<10; i++)
        remove_hitloc(i);

    set_hitloc_unarmed(A_LEGS,  100, 20, "leg");
    set_hitloc_unarmed(A_L_WING, 70, 10, "left wing");
    set_hitloc_unarmed(A_R_WING, 70, 10, "right wing");
    set_hitloc_unarmed(A_HEAD,  100, 10, "skull");
    set_hitloc_unarmed(A_R_ARM, 100, 10, "left arm");
    set_hitloc_unarmed(A_L_ARM, 100, 10, "right arm");
    set_hitloc_unarmed(A_BODY,	100, 30, "body");
   
    add_prop(MAGIC_AM_ID_INFO,
      ({ "This is the Balrog of Moria, a truly fitting legacy of " +
          "Morgoth's great evil.\n", 1,
          "A fallen Maia, he is a Fire Spirit recruited into the " +
          "folds of darkness long before history began. He served " +
          "in Morgoth's armies during the wars of the First Age " +
          "and, with the fall of Thangorodrim in the Great Battle, " +
          "he was one of the few Balrogs to escape destruction.\n", 10,
          "Durin's Bane instills dread in the heart of anything " +
          "that stands before him, which was befitting a Demon " +
          "whose might exceeds that of a Dragon. His presence "+
          "always commands fear. Ensconced in a changing shadow, " +
          "enshrouded in magic fire, the Balrog of Moria is typical " +
          "of the Demons of Might; but he is far more powerful " +
          "than anyone in Endor except his fellow Maiar and the " +
          "highest of the Firstborn's Lords.\n", 40,
      }));

    set_alignment(-1200);

    set_act_time(6);
    add_act("assist troll");
    add_act("assist orc");

    // This will make attack targets randomly.
    // Why? Doesn't he auto-attack? Wouldn't add_cact be more appropriate?
    // Peace spells?
    add_act("kill elf");
    add_act("kill dwarf");
    add_act("kill human");
    add_act("kill goblin");
    add_act("kill gnome");
    add_act("kill wraith");
    add_act("kill orc");
    add_act("kill kender");
    add_act("kill ogre");
    add_act("kill presence");
    add_act("kill undead");

    set_chat_time(20);
    add_chat("Be gone!");
    add_chat("Conniving mortal!");
    set_exp_factor(200);
/*
    set_kill_log_name("balrog");
    set_kill_log_size(-1);  // Log never gets truncated.

    TELL_ADMIN("The Balrog was cloned at " + ctime(time()));
*/
}

int
query_magic_res(string prop)
{
    if (prop == MAGIC_I_RES_WATER)
        return 0;
    else if (prop == MAGIC_I_RES_POISON ||
             prop == MAGIC_I_RES_FIRE ||
             prop == MAGIC_I_RES_ACID ||
             prop == MAGIC_I_RES_DEATH)
        return 100;
    else
        return 95;
}

// Armors
void
arm_me()
{
    seteuid(getuid(this_object()));
    
    wings = clone_object(MORIA_WEP + "new/balrog_wings");
    wings->move(TO);
    command("wear wings");
}

// Weapons
void
draw_weapons()
{

    if(!weapons)
    {    
        seteuid(getuid(this_object()));

        tell_room(ENV(TO), "\n" + QCTNAME(TO)+ " roars demoniacally when "
                + "weapons are drawn.\n", TO);

        wep1 = clone_object(MORIA_WEP + "new/balrog_whip");
        wep1->move(TO);
        wep2 = clone_object(MORIA_WEP + "new/balrog_sword");
        wep2->move(TO);
        command("wield whip");
        command("wield sword");
        weapons = 1;

        // Will remove the weapons after 30min (1800sec)
        set_alarm(1800.0, 0.0, &remove_weapons());
    }
}

void
remove_weapons()
{
    if(!TO->query_attack())
    {
        if(wep1)
        {
            command("unwield whip");
            wep1->remove_object();
        }

        if(wep2)
        {
            command("unwield sword");
            wep2->remove_object();
        }

        // Resetting the fight.
        weapons = 0;
        stage0 = 1;
        stage1 = 0;
        stage2 = 0;
        stage3 = 0;

        if(wings)
                wings->do_extinguish();

        tell_room(ENV(TO), "Flames licks the surroundings one final time as " 
                               + QTNAME(TO) + " unwields " + HIS_HER(TO) 
                               + " flaming weapons.\n", TO);
    }

    // If the Balrog is in combat, check again in 30mins.
    if(weapons)
        set_alarm(1800.0, 0.0, &remove_weapons());    
}

public string
query_combat_file()
{
    return "/std/combat/chumanoid";
}

public int
hand_hit(int aid, string hdesc, int phurt, object enemy, int dt,
         int phit, int dam)
{
    string name = this_object()->query_short();

    // Double the dmg.
    if (dam > 1)
        enemy->heal_hp(-dam);

    switch (phurt)
    {
        case -1:
        case -2:
            enemy->catch_msg("The "+name+" misses you completely.\n");

            tell_watcher("The "+name+" misses "+ QTNAME(enemy) +
                              " completely.\n", enemy);

        break;
        case 0..9:
            enemy->catch_msg("The "+name+" slashes at you with his wicked " +
                "claws, gouging your flesh and drawing blood.\n");

            tell_watcher("The "+name+" slashes at "+ QTNAME(enemy) +
                        " with his sharp claws, gouging " + HIM_HER(enemy) +
                        " and drawing blood.\n", enemy);
        break;
        case 10..19:
            enemy->catch_msg("The "+name+" roars demoniacally and strikes you "
                         + "with his fists, knocking the breath out of you.\n");

                tell_watcher("The "+name+" roars demoniacally and "
                                 + "strikes " + QTNAME(enemy) + " with his "
                                 + "fists.\n", enemy);
        break;
        case 20..39:
            enemy->catch_msg("The "+name+" picks you up and throws you "
                           + "against the wall, knocking you senseless.\n");

            tell_watcher( "The "+name+" picks up "+ QTNAME(enemy) +
                " and throws " + HIM_HER(enemy) +" against a wall, knocking " 
                + HIM_HER(enemy) +" senseless.\n", enemy);
        break;
        case 40..59:
            enemy->catch_msg("The "+name+" charges you, hammering you with "
                           + "his immense fists.\n");

            tell_watcher("The "+name+" charges "+ QTNAME(enemy) 
                     + " hammering " + HIM_HER(enemy) + " with his immense "
                     + "fists.\n", enemy);
        break;
        case 60..79:
            enemy->catch_msg("The "+name+" roars with insane fury and "
                           + "strikes you with terrible blows from his "
                           + "fists.\n");

            tell_watcher("The "+name+" roars with insane fury and "
                            + "strikes "+ QTNAME(enemy) + " with terrible "
                            + "blows from his fists.\n", enemy);
        break;
        case 80..99:
            enemy->catch_msg("The "+name+" picks you and throws you hard to " +
                "the ground. You hear a sickening sound as bones break and " +
                "blood begins to run from the wounds.\n");

            tell_watcher("The "+name+" picks up and throws " +
                      QTNAME(enemy) + " to the ground. " +
                      "A sickening sound fills the air as bones break and " 
                    + "blood begins to run from the wounds.\n", enemy);
        break;
        default:
    }

    if (HP(enemy) <= 0)
    {
        enemy->command("scream");
        enemy->catch_msg("A deadly scene of fire and destruction is " +
            "your last view of the world as you are crushed by the " +
            "immense "+name+".\n\nYou are dead.\n");

        tell_watcher("The terrifying "+name+" demolishes " 
            + QTNAME(enemy) + " as he firmly crushes " + HIM_HER(enemy)
            + " and squashes " + HIS_HER(enemy) +" remains into the ground!!\n"
            + QTNAME(enemy) + " dies instantly.\n", enemy);
        enemy->do_die(TO);
    }
    return 1;
}

// His main mode of unarmed combat.
public int
foot_hit(int aid, string hdesc, int phurt, object enemy, int dt,
         int phit, int dam)
{
    string name = this_object()->query_short();
    hdesc = "sharply clawed foot";
    mixed* hitresult;
    string how;
    object me, *all;
    int hurt = 1000, i;

    me = TO;
    all = FILTER_LIVE(all_inventory(environment(me))) - ({ me });

    // 25% chance of an AoE attack.
    if (!random(4) && stage3)
    {
        for (i=0; i<sizeof(all); i++) 
        {

            hurt -= hurt * all[i]->query_magic_res(MAGIC_I_RES_FIRE) / 300;
            hitresult = all[i]->hit_me(hurt, MAGIC_DT, me, -1);

            if(all[i]->query_hp() <= 0)
                all[i]->do_die(me);
        }

        find_living("znagsnuf")->catch_tell("DEBUG: BALROG AoE damage!\n");

        tell_watcher("\n" +QCTNAME(me) + " stomps " + HIS_HER(me) + " " + hdesc 
                     + " hard down into the ground, while clashing " 
                     + HIS_HER(me) + " weapons together. The flames turns "
                     + HIS_HER(me) + " skin into a brilliant shade of blue, "
                     + "the blazing inferno burns everything mercilessly in "
                     + "its path.\n");

        return 1;
    }

    // Double the dmg.
    if (dam > 1)
        enemy->heal_hp(-dam);

    switch (phurt)
    {
    case -1:
    case -2:
        enemy->catch_msg("The "+name+" misses you completely with his "
        + hdesc + ".\n");

        tell_watcher("The "+name+" misses " + QTNAME(enemy) +
            " with his "+hdesc+".\n", enemy);
    break;

    case 0..9:
        enemy->catch_msg("The "+name+" grazes you with his "+hdesc+".\n");

        tell_watcher("The "+name+" grazes " + QTNAME(enemy) + " with "
                        + "his " + hdesc+".\n", enemy);
    break;

    case 10..19:
        enemy->catch_msg("The "+name+" kicks you with his " + hdesc +
        ", drawing blood.\n");

        tell_watcher("The "+name+" kicks " + QTNAME(enemy) +
        " with his " + hdesc + ", drawing blood.\n", enemy);
    break;

    case 20..39:
        enemy->catch_msg("The "+name+" lets out a bone-chilling scream as "
                       + "he hits you repeatedly with his "+hdesc+".\n");

        tell_watcher("The "+name+" cackles demoniacally as he hits " +
            QTNAME(enemy) + " repeatedly with his "+hdesc+".\n", enemy);
    break;
    case 40..59:
        enemy->catch_msg("The "+name+" stomps on you with his " 
                         + hdesc + ".\n");

        tell_watcher("The "+name+" stomps on " + QTNAME(enemy) +
            " with his " + hdesc + ".\n", enemy);
    break;
    case 60..79:
        enemy->catch_msg("The "+name+" charges you with demonic fury, "
                       + "gouging you with his "+hdesc+".\n");
        tell_watcher("The "+name+" charges " + QTNAME(enemy) +
                          " with demonic fury, gouging " + HIM_HER(enemy) +
                          " with his "+hdesc+".\n", enemy);
    break;
    case 80..99:
        enemy->catch_msg("The "+name+" vents a deafening roar as he flaps "
                       + "his wings, lifting him off the ground. He kicks "
                       + "you into the air and slams you against the wall!\n");

        tell_watcher("The "+name+" vents a deafening roar as he flaps "
                        + "his wings, lifting him off the ground. He kicks " 
                        + QTNAME(enemy) + " into the air and slams him "
                        + "against the wall!\n");
    break;
    default:
    enemy->catch_msg("You try to stand, but stagger about, reeling from " +
                     "the demonic power of the "+name+".\n");

    tell_watcher(QCTNAME(enemy) + " tries to stand, but staggers about, "
                 + "reeling from the demonic power of the "+name+".\n", enemy);
    }

    if (HP(enemy) <= 0)
    {
        enemy->catch_msg("As the Fire Spirit launches one final " +
            "terrible kick, you feel bones crush and your heart stops " +
            "beating as you land like a gory piece of meat, utterly " +
            "pummeled to death...\n");

        tell_watcher("The "+name+" launches a final kick, hitting "+
            QTNAME(enemy)+ " awfully, crushing bones to a bloody mess " +
            "of gore and splintered bones, leaving behind nothing but " +
            "a corpse.\n", enemy);

        enemy->do_die(TO);
    }
    return 1;
}

horn_hit(int aid, string hdesc, int phurt, object enemy, int dt,
         int phit, int dam)
{
    string name = this_object()->query_short();
    hdesc = "fiery horns";

    if (!random(2) && stage2)
    {
        int heal = (query_max_hp() / 30);
        TO->heal_hp(heal);
    }

    // Double the dmg.
    if (dam > 1)
        enemy->heal_hp(-dam);

    switch (phurt)
    {
    case -1:
    case -2:
        enemy->catch_msg("The "+name+" misses you completely with the fiery "
                       + "horns on his head.\n");

        tell_watcher("The "+name+" misses " + QTNAME(enemy) 
                  + " completely with the fiery horns on his head.\n", enemy);
    break;

    case 0..9:
        enemy->catch_msg("The "+name+" grazes you with his "+hdesc+".\n");

        tell_watcher("The "+name+" grazes " + QTNAME(enemy) + " with "
                        + "his "+ hdesc + ".\n", enemy);
    break;

    case 10..19:
        enemy->catch_msg("The "+name+" lashes out at you with his " + hdesc +
                         ", scraping you painfully.\n");

        tell_watcher("The "+name+" lashes out at " + QTNAME(enemy) +
                        " with his " + hdesc + ", scraping " + HIM_HER(enemy) +
                        " painfully.\n", enemy);
    break;

    case 20..39:
        enemy->catch_msg("The "+name+" lets out a demonic roar as he slashes " +
                         "you repeatedly with his "+hdesc+".\n");

        tell_watcher("The "+name+" lets out a demonic roar as he "
                        + "slashes " + QTNAME(enemy) + " repeatedly with "
                        + "his "+hdesc+".\n", enemy);
    break;
    case 40..59:
        enemy->catch_msg("The "+name+" smashes you with his fiery horns, " +
                         "throwing you to the ground.\n");

        tell_watcher("The "+name+" smashes " + QTNAME(enemy) +
                          " with his fiery horns, throwing " + HIM_HER(enemy) +
                          " to the ground.\n", enemy);
    break;
    case 60..79:
        enemy->catch_msg("The "+name+" lowers his head and charges you with " +
                         "demonic fury, penetrating your armour with his "
                         + hdesc + ".\n");

        tell_watcher("The "+name+" lowers his head charges " +
                  QTNAME(enemy) + " with demonic fury, penetrating armour "
                  + "with his " + hdesc + ".\n", enemy);
    break;
    case 80..99:
        enemy->catch_msg("The "+name+" thrashes his head from side to side, " +
            "catching you with his fiery horns and throws you high into the " +
            "air. You crash to the ground with a sickening thud.\n");

        tell_watcher("The "+name+" thrashes his head from side to "
                        + "side, catching " + QTNAME(enemy) + " on his "
                        + "fiery horns and throws " + HIM_HER(enemy) 
                        + " high into the " + "air. " + HE_SHE(enemy) 
                        + " crashes to the ground with a sickening "
                        + "thud.\n", enemy);
    break;

    }

    if (HP(enemy) <= 0)
    {
        enemy->command("panic");
        enemy->catch_msg("Your last scene in this beloved world is " +
            "breathtaking. The "+name+" attacks you with his horns, " +
            "brutally penetrating your chest, crushing your bones and " +
            "pierces your heart.\n\n"+
            "You die a horrible death.\n");
        tell_watcher(
            "In a breath-taking scene of brutal power and destruction, " +
            "the ferocious "+name+" pierces " +
            QTNAME(enemy)+ " in " + HIS_HER(enemy) + " chest with his " +
            "horns. You hear bones crush and blood flow as " +
            HE_SHE(enemy) + " is firmly lifted from the ground, impaled " +
            "on his horns.\n\n"+
            "The "+name+" shakes his head, casting the limp corpse " +
            "into a dark corner.\n\n"+
            QCTNAME(enemy) + " is dead.\n", enemy);
        enemy->do_die(TO);
    }
    return 1;
}

/*
 * Function name: cr_did_hit
 *
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. This is supposed to be
 *                replaced by a more intelligent routine in creature and
 *                  humanoid combat. (called from heart_beat)
 *
 * Arguments:     aid:   The attack id
 *                hdesc: The hit location description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *          dt:     The current damage type
 *          phit:  The %success that we made with our weapon
 *          dam:     The damage made in hit points
 */
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
           int phit, int dam)
{

    // 75% health, ignite wings
    int hp_75 = (TO->query_max_hp()/100)*75;
    // 50% health, draw weapons
    int hp_50 = (TO->query_max_hp()/100)*50;
    // 30% health, AoE attack 
    int hp_30 = (TO->query_max_hp()/100)*30;

    // Stage 1
    if(stage0)
    {
        if(TO->query_hp() < (hp_75))
        {
            stage1 = 1;
            stage0 = 0;
            
            // Ignite the wings.
            if(wings)
                wings->do_ignite();
            
        }

    }

    // Stage 2
    if(stage1)
    {
        if(TO->query_hp() < (hp_50))
        {
            stage2 = 1;
            stage1 = 0;

            // Draw weapons at 50% health.
            if(!weapons)
            {
                draw_weapons();
            }
        }   
    }

    // Stage 3
    if(stage2)
    {
        if(TO->query_hp() < (hp_30))
        {
            stage3 = 1;
            stage2 = 0;
        }    
    }

    if (aid == W_RIGHT || aid == W_LEFT)
        return hand_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (aid == W_FOOTR || aid == W_FOOTL)
        return foot_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (aid == W_BOTH)
        return horn_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

// Don't accept objects
public void
enter_inv(object ob, object from)
{
    if (!IS_MORIA_OBJECT(ob))
        ob->remove_object();
    else
        ::enter_inv(ob, from);
}

int
add_prop_live_i_stunned(mixed val)
{
    return 1;
}

int
add_prop_live_as_attack_fumble(mixed val)
{
    return 1;
}

int
add_prop_live_i_attack_delay(mixed val)
{
    return 1;
}

public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    mixed hres;
    int wi;

    /*
     * Start non-players when attacked
     */
    start_heart();

    if (!combat_extern)
        ::combat_reload();

    if (wcpen > 100)
        wcpen = 100;

    if (wcpen > 0 && (dt == -1 || attack_id == -1))
        wcpen /= 2;                   /* 50 % resistance against
                                         special attacks. */

    hres = (mixed)combat_extern->cb_hit_me(wcpen, dt, attacker, attack_id);

    if (!(wi = query_whimpy()))
        return hres;

    if (((100 * query_hp()) / query_max_hp()) < wi)
    {
        set_alarm(1.0, 0.0, &run_away());
    }

    return hres;
}

int
query_knight_prestige()
{
    return 5000;
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    //TELL_ADMIN("The Balrog was attacked by " + ob->query_cap_name() 
    //         + "("+ob->query_average_stat()+") at " + ctime(time()));
}

/*
* Function name: do_die()
* Description  : This is called when the npc is slain.
*/

public void
do_die(object killer)
{
    // To prevent double unwield.
    command("unwield all");

    if(wings)
        wings->do_extinguish();

    ::do_die(killer);
}