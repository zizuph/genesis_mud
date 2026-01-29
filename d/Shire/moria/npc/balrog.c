/*

Balrog
by Palmer
January 2003

Recode of various Balrogs in ~shire/moria/npc

ChangeLog:

April 10 2004 - Palmer  - Changed alignment to -1200
March 26 2013 - Gorboth - Modifications included for April Fool's Day

*/

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/std/act/add_things";
inherit "/std/act/chat";
inherit "/d/Shire/lib/kill_logger";
inherit "/cmd/std/command_driver";
inherit "/d/Shire/common/lib/tell";

#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <const.h>
#include <time.h>
#include "defs.h"
#include "/d/Shire/common/lib/evilkill.h"
#include "/d/Shire/moria/skills/skill_types.h"
#include "/d/Shire/private/shire_admin.h"

#define A_L_WING    262144
#define A_R_WING    524288
#define W_HORNS    1048576
#define W_ALL_DT    (W_BLUDGEON | W_SLASH | W_IMPALE)

#define APRIL_FOOL_ENABLED        1
#define TELL_G(x) find_living("gorboth")->catch_msg("DEBUG: " + x + "\n")

/* Global Variables */
public string    April_Fool_Name = "mouse";
public int       Joke_Activated  = 0;
public string    Joke_Date       = "Apr 01";

/* Function Prototypes */
public void            check_april_fool();
public string          describe_short();
public string          describe_long();
public void            init_living();

public void      set_joke_date(string s) { Joke_Date = s; }
public string    query_joke_date()       { return Joke_Date; }


public string query_met_name()
{
    return "Gash";
}


public void
create_creature()
{
    int i;

    set_name("balrog");
    set_living_name("gash");
    add_name("gash");
    add_adj("evil");
    set_title("the Evil Lord in Moria, Durin's Bane, Fire Demon of Might");
    set_race_name("balrog");

    set_short(describe_short);
    set_long(describe_long);

    set_stats(({380, 347, 346, 200, 170, 288}));

    // Where is this from? /std/creature.c?
    TO->setup_skills();

    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 80);
    set_skill(SS_2H_COMBAT, 90);

    add_prop(CONT_I_WEIGHT, 11400*1000);  /* 11.4 tons */
    add_prop(CONT_I_HEIGHT, 549);
    add_prop(OBJ_I_LIGHT, 50);
    add_prop(OBJ_I_HAS_FIRE, 50);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 99);

    add_prop(LIVE_I_SEE_DARK, 100); /* Night vision. */
    add_prop(LIVE_I_SEE_INVIS, 99);/* Sees all but wizards */
    add_prop(LIVE_I_QUICKNESS, 50); /* Fast monster. */
    add_prop("_live_m_no_drain", 1);

    set_skill(SS_PUNCH, 100);
    set_skill(SS_BASH, 100);
    set_skill(SS_DIS_FOE_ARMED, 100);
    set_skill(SS_DIS_FOE_UNARMED, 100);


    // Whoa. Make sure we don't uncomment this till he's ready.
    set_monster_home("/d/Shire/moria/mines/lair/lair6");
    set_restrain_path("/d/Shire/moria/mines/lair");

    // He attacks 100% of the time.
    set_attack_chance(100);
    set_aggressive(1);

    // What's this? No looking like the image of perfection.
    add_prop(NPC_I_NO_LOOKS, 1);

    set_attack_unarmed(W_RIGHT, 100,  90, W_ALL_DT,   20, "right claw");
    set_attack_unarmed(W_LEFT, 100,  90, W_ALL_DT,   20, "left claw");
    set_attack_unarmed(W_FOOTR, 90, 130, W_BLUDGEON, 20, "right foot");
    set_attack_unarmed(W_FOOTL, 90, 130, W_BLUDGEON, 20, "left foot");
    set_attack_unarmed(W_HORNS, 100, 170, W_IMPALE,   20, "horns");

    // Give him horns as leftover.
    add_leftover("/std/leftover", "horn", 2, 0, 1, 1);

    // Remove std hit locations and define our own.
    for (i=0; i<5; i++)
        remove_hitloc(i);

    set_hitloc_unarmed(A_LEGS, 100, 20, "leg");
    set_hitloc_unarmed(A_EYES, 10,  2, "burning eyes");
    set_hitloc_unarmed(A_L_WING, 70,  9, "left wing");
    set_hitloc_unarmed(A_R_WING, 70,  9, "right wing");
    set_hitloc_unarmed(A_HEAD, 110, 10, "skull");
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
          "always commands fear. Ensconed in a changing shadow, " +
          "enshrouded in magic fire, the Balrog of Moria is typical " +
          "of the Demons of Might; but he is far more powerful " +
          "than anyone in Endor except his fellow Maiar and the " +
          "highest of the Firstborn's Lords.\n", 40,
      }));


    add_prop(NPC_I_NO_RUN_AWAY, 1); // No wimpy.

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

    set_chat_time(20);
    add_chat("Be gone!");
    add_chat("Conniving mortal!");

    set_kill_log_name("balrog");
    set_kill_log_size(-1);  // Log never gets truncated.

    TELL_ADMIN("The Balrog was cloned at " + ctime(time()));


    // 100% is 1 attack per turn. He's fast.
    set_attackuse(120);
    equip(MORIA_WEP + "calris");
    equip(MORIA_WEP + "whip");
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

public string
query_combat_file()
{
    return "/std/combat/chumanoid";
}


/*
 * Function name: cr_reset_attack
 * Description:   Set the values for a specific attack. These are called
                  from the external combat object.
 * Arguments:     aid: The attack id
 */
public void
cr_reset_attack(int aid)
{
    mixed att;

    if (!mappingp(ua_attdata))
        ua_attdata = ([]);

    att = ua_attdata[aid];

    if (sizeof(att) >= 4)
    {
        query_combat_object()->cb_add_attack(att[0], att[1], att[2], att[3],
        aid,query_skill(SS_UNARM_COMBAT));
    }
}


// He's only going to use this if disarmed (Mage breaking his weapon?)
public int
hand_hit(int aid, string hdesc, int phurt, object enemy, int dt,
  int phit, int dam)
{
    string name = ((Joke_Activated) ? "Mouse" : "Balrog");

    switch (phurt)
    {
        case -1:
        case -2:
            enemy->catch_msg("The "+name+" misses you completely.\n");

            tell_room(ENV(TO)," misses "+ QCTNAME(enemy) +
                "completely.\n", enemy);

        break;
        case 0..9:
            enemy->catch_msg("The "+name+" slashes at you with his wicked " +
                "claws, gouging your flesh and drawing blood.\n");

            tell_room(ENV(TO),"The "+name+" slashes at "+ QCTNAME(enemy) +
                " with his sharp claws, gouging " + HIM_HER(TP) +
                "and drawing blood.\n", enemy);
        break;
        case 10..19:
            enemy->catch_msg("The "+name+" roars demonically and strikes you " +
                "with his fists, knocking the breath out of you.\n");

                tell_room(ENV(TO)," roars demonically and strikes " +
                    QCTNAME(enemy) + " with his fists.\n", enemy);
        break;
        case 20..39:
            enemy->catch_msg("The "+name+" picks you up and throws you against "+
                "the wall, knocking you senseless.\n");

            tell_room(ENV(TO), "The "+name+" picks up "+ QCTNAME(enemy) +
                " and throws " + HIM_HER(enemy) +
                " against a wall, knocking " + HIM_HER(enemy) +
                " senseless.\n", enemy);
        break;
        case 40..59:
            enemy->catch_msg("The "+name+" charges you, hammering you with his "+
                "immense fists.\n");

            tell_room(ENV(TO),"The "+name+" charges "+ QCTNAME(enemy) +
                " hammering "+HIM_HER(enemy) +
                " with his immense fists.\n", enemy);
        break;
        case 60..79:
            enemy->catch_msg("The "+name+" roars with insane fury and strikes " +
                "you with terrible blows from his fists.\n");

            tell_room(ENV(TO),"The "+name+" roars with insane fury and strikes "+
                QCTNAME(enemy)+" with terrible blows from his fists.\n",enemy);
        break;
        case 80..99:
            enemy->catch_msg("The "+name+" picks you and throws you hard to " +
                "the ground. You hear a sickening sound as bones break and " +
                "blood begins to run from the wounds.\n");

            tell_room(ENV(TO),"The "+name+" picks up and throws " +
                QCTNAME(enemy) + " to the ground. " +
                "A sickening sound fills the air as bones break and " +
                "blood begins to run from the wounds.\n", enemy);
        break;
        default:
    }

    if (HP(enemy) <= 0)
    {
        enemy->command("scream");
        enemy->catch_msg("A deadly scene of fire and destruction is " +
            "your last view of the world as you are crushed by the " +
            "immense "+name+".\n\n" + "You are dead.\n");

        tell_room(ENV(TO),
            "The terrifying "+name+" demolishes " +
            QCTNAME(enemy) + " as he firmly crushes "+HIM_HER(enemy)+
            " and squashes "+HIS_HER(enemy)+" remains into the ground!!\n"+
            QCTNAME(enemy) + " dies instantly.\n", enemy);
        enemy->do_die(TO);
    }
    return 1;
}

// His main mode of unarmed combat.
public int
foot_hit(int aid, string hdesc, int phurt, object enemy, int dt,
  int phit, int dam)
{
    string name = ((Joke_Activated) ? "Mouse" : "Balrog");
    hdesc = "sharply clawed foot";

    switch (phurt)
    {
    case -1:
    case -2:
        enemy->catch_msg("The "+name+" misses you completly with his "
        + hdesc + ".\n");

        tell_room(ENV(TO),"The "+name+" misses " + QCTNAME(enemy) +
            " with his "+hdesc+".\n", enemy);
    break;

    case 0..9:
        enemy->catch_msg("The "+name+" grazes you with his "+hdesc+".\n");

        tell_room(ENV(TO),"The "+name+" grazes " + QCTNAME(enemy)+ " with his " +
            hdesc+".\n", enemy);
    break;

    case 10..19:
        enemy->catch_msg("The "+name+" kicks you with his " + hdesc +
        ", drawing blood.\n");

        tell_room(ENV(TO),"The "+name+" kicks " + QCTNAME(enemy) +
        " with his " + hdesc + ", drawing blood.\n", enemy);
    break;

    case 20..39:
        enemy->catch_msg("The "+name+" lets out a bone-chilling scream as he " +
            "hits you repeatedly with his "+hdesc+".\n");

        tell_room(ENV(TO),"The "+name+" cackles demonically as he hits " +
            QCTNAME(enemy) + " repeatedly with his "+hdesc+".\n", enemy);
    break;
    case 40..59:
        enemy->catch_msg("The "+name+" stomps on you with his " + hdesc + ".\n");

        tell_room(ENV(TO),"The "+name+" stomps on " + QCTNAME(enemy) +
            " with his " + hdesc + ".\n", enemy);
    break;
    case 60..79:
        enemy->catch_msg("The "+name+" charges you with demonic fury, gouging " +
            "you with his "+hdesc+".\n");
        tell_room(ENV(TO),"The "+name+" charges " + QCTNAME(enemy) +
            " with demonic fury, gouging " + HIM_HER(enemy) +
            " with his "+hdesc+".\n", enemy);
    break;
    case 80..99:
        enemy->catch_msg("The "+name+" vents a deafening roar as he flaps his " +
            "wings, lifting him off the ground. He kicks you into the air " +
            "and slams you against the wall!\n");

        tell_room(ENV(TO),"The "+name+" vents a deafening roar as he flaps his "+
            "wings, lifting him off the ground. He kicks " + QCTNAME(enemy) +
            " into the air and slams him against the wall!\n");
    break;
    default:
    enemy->catch_msg("You try to stand, but stagger about, reeling from " +
                     "the demonic power of the "+name+".\n");

    tell_room(ENV(TO), QCTNAME(enemy) + " trys to stand, but staggers about, "+
        "reeling from the demonic power of the "+name+".\n", enemy);
    }

    if (HP(enemy) <= 0)
    {
        enemy->catch_msg("As the Fire Spirit launches one final " +
            "terrible kick, you feel bones crush and your heart stops " +
            "beating as you land like a gory piece of meat, utterly " +
            "pummelled to death...\n");

        tell_room(ENV(TO),"The "+name+" launches a final kick, hitting "+
            QCTNAME(enemy)+ " awfully, crushing bones to a bloody mess " +
            "of gore and splintered bones, leaving behind nothing but " +
            "a corpse.\n", enemy);

        enemy->do_die(TO);
    }
    return 1;
}

horn_hit(int aid, string hdesc, int phurt, object enemy, int dt,
  int phit, int dam)
{
    string name = ((Joke_Activated) ? "Mouse" : "Balrog");
    hdesc = "fiery horns";

    switch (phurt)
    {
    case -1:
    case -2:
        enemy->catch_msg("The "+name+" misses you completly with the fiery " +
            "horns on his head.\n");

        tell_room(ENV(TO),"The "+name+" misses " + QCTNAME(enemy) +
            " completely with the fiery horns on his head.\n", enemy);
    break;

    case 0..9:
        enemy->catch_msg("The "+name+" grazes you with his "+hdesc+".\n");

        tell_room(ENV(TO),"The "+name+" grazes " + QCTNAME(enemy) + " with his "+
            hdesc + ".\n", enemy);
    break;

    case 10..19:
        enemy->catch_msg("The "+name+" lashes out at you with his " + hdesc +
            ", scraping you painfully.\n");

        tell_room(ENV(TO),"The "+name+" lashes out at " + QCTNAME(enemy) +
            " with his " + hdesc + ", scraping " + HIM_HER(enemy) +
            " painfully.\n", enemy);
    break;

    case 20..39:
        enemy->catch_msg("The "+name+" lets out a demonic roar as he slashes " +
            "you repeatedly with his "+hdesc+".\n");

        tell_room(ENV(TO),"The "+name+" lets out a demonic roar as he slashes " +
            QCTNAME(enemy) + " repeatedly with his "+hdesc+".\n", enemy);
    break;
    case 40..59:
        enemy->catch_msg("The "+name+" smashes you with his fiery horns, " +
            "throwing you to the ground.\n");

        tell_room(ENV(TO),"The "+name+" smashes " + QCTNAME(enemy) +
            " with his fiery horns, throwing " + HIM_HER(enemy) +
            " to the ground.\n", enemy);
    break;
    case 60..79:
        enemy->catch_msg("The "+name+" lowers his head and charges you with " +
            "demonic fury, penetrating your armour with his "+hdesc+".\n");

        tell_room(ENV(TO),"The "+name+" lowers his head charges " +
            QCTNAME(enemy) + " with demonic fury, penetrating " +
            "armour with his "+hdesc+".\n", enemy);
    break;
    case 80..99:
        enemy->catch_msg("The "+name+" thrashes his head from side to side, " +
            "catching you with his fiery horns and throws you high into the " +
            "air. You crash to the ground with a sickening thud.\n");

        tell_room(ENV(TO),"The "+name+" thrashes his head from side to side, " +
            "catching " + QCTNAME(enemy) + " on his fiery horns and throws " +
            HIM_HER(enemy) + " high into the " + "air. " + HE_SHE(enemy) +
            " crashes to the ground with a sickening thud.\n", enemy);
    break;
    // default: Is this needed?
    }

    if (HP(enemy) <= 0)
    {
        enemy->command("panic");
        enemy->catch_msg("Your last scene in this beloved world is " +
            "breathtaking. The "+name+" attacks you with his horns, " +
            "brutally penetrating your chest, crushing your bones and " +
            "pierces your heart.\n\n"+
            "You die a horrible death.\n");
        tell_room(ENV(TO),
            "In a breath-taking scene of brutal power and destruction, " +
            "the ferocious "+name+" pierces " +
            QTNAME(enemy)+ " in " + HIS_HER(enemy) + " chest with his " +
            "horns. You hear bones crush and blood flow as " +
            HE_SHE(enemy) + " is firmly lifted from the ground, impaled " +
            "on his horns.\n\n"+
            "The "+name+" shakes his head, casting the limp corpse " +
            "into a dark corner.\n\n"+
            QCTNAME(TP) + " is dead.\n", enemy);
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
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *          dt:     The current damagetype
 *          phit:  The %success that we made with our weapon
 *          dam:     The damamge made in hitpoints
 */
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
  int phit, int dam)
{
    if (aid == W_RIGHT || aid == W_LEFT)
        return hand_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (aid == W_FOOTR || aid == W_FOOTL)
        return foot_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (aid == W_HORNS)
        return horn_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    return 0;
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
     * Start nonplayers when attacked
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
    return 100;
}

void
attacked_by(object ob)
{
    object *arr;

    ::attacked_by(ob);
    TELL_ADMIN("The Balrog was attacked by " + ob->query_cap_name() + "("+ob->query_average_stat()+") at " + ctime(time()));
}


/*
 * Function name:        check_april_fool
 * Description  :        Check to see if it is April 1st, and if so,
 *                       switch the short description and race name
 *                       to the balrog.
 */
public void
check_april_fool()
{
    string  date = TIME2FORMAT(time(), "mmm dd");

    if (date != Joke_Date)
    {
        if (Joke_Activated)
        {          
            set_name("balrog");
            set_race_name("balrog"); 
            remove_name(capitalize(April_Fool_Name));
            set_short("Balrog");

            tell_room(environment(this_object()),
                "There is a sudden flash, and the "
              + April_Fool_Name + " seems to have changed!\n");

            TELL_G("In MORIA -- Morphing mouse back to Balrog!");

            Joke_Activated = 0;
        }

        return;
    }

    if (!Joke_Activated)
    {
        set_name("mouse");
        set_race_name(April_Fool_Name); 
        set_short(capitalize(April_Fool_Name));
        remove_name("Balrog");

            tell_room(environment(this_object()),
                "There is a sudden flash, and the Balrog"
              + " seems to have changed!\n");

            TELL_G("In MORIA -- Morphing Balrog to Mouse!");

        Joke_Activated = 1;
    }

    return;
} /* check_april_fool */


/*
 * Function name:        describe_short
 * Description  :        We want to have this function called whenever
 *                       someone gets the short desc of the creature
 *                       to see if the date has changed.
 * Returns      :        string - the short desc
 */
public string
describe_short()
{
#ifdef APRIL_FOOL_ENABLED
    check_april_fool();
#endif

    return query_name();
} /* describe_short */


/*
 * Function name:        describe_long
 * Description  :        We want to have this function called whenever
 *                       someone gets the long desc of the creature
 *                       to see if the date has changed.
 * Returns      :        string - the long desc
 */
public string
describe_long()
{
#ifdef APRIL_FOOL_ENABLED
    check_april_fool();
#endif

    return "Standing before you is one of the most feared " +
        "creatures ever, the "+short()+" of Moria. The "+short()+" is a " +
        "huge, hulking, man-like demon. Fire streams from his " +
        "mane and his nostrils breathe flames. His limbs are " +
        "huge and muscular and look strong enough to smash " +
        "anything. Giant wings extend from his back, flapping idley.  " +
        "Darkness and fear surround the "+short()+".\n";
} /* describe_long */


/*
 * Function name:        init_living
 * Description  :        We want to have this function called whenever
 *                       someone enters the room of the creature
 *                       to see if the date has changed.
 */
public void
init_living()
{
    ::init_living();

#ifdef APRIL_FOOL_ENABLED
    check_april_fool();
#endif
} /* init_living */
