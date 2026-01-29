/*   
 *   The Rangers base training hall - modified by Elessar, from:
 *   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *   This file is to be inherited by the train halls of all three 
 *   Ranger companies.
 *   Modified by Olorin, 30-Oct-1993
 *
 *   Added "estimate all", cleanup -- Gnadnar 21 August 1998
 *   Moved and modified for the recode. -- Gwyneth 13 August 2002
 *   
 */
inherit "/d/Gondor/std/room.c";
inherit "/lib/guild_support.c";
inherit "/lib/skill_raise.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <state_desc.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "rangers.h"

/* A few definitions */
#define NUM                    sizeof(query_money_types())
#define RANGER_I_TRAIN_CHANGE  "_ranger_i_train_change"


/* Prototypes */
public nomask void create_gondor();
public void        set_company_num(int i);
public void        create_trainhall();
public string      exa_poster();
public int         cmax(int sk);
public int         pupil_max(int sk);
public void        set_up_skills();
public void        gs_hook_already_meditate();
public void        gs_hook_start_meditate();
public void        gs_hook_rise();
public void        sk_hook_write_header(int steps);
public void        sk_hook_skillisting();
public int         sk_cost(int snum, int fr, int to);
//public varargs int sk_query_max(int sknum, int silent);
public int         sk_improve(string str);
public int         can_train_this_skill(object who, string skill, int step);
public int         train(string choice);
public void        lower_secondary(int skill, object who);
public int         query_secondary(object who);
public int         query_primary_factor(object who);
public int         query_primary(object who);
public void        init();

/* Global variables */
int     gCompany = 1;

/*
 * Function name: create_gondor
 * Description  : set up the training hall
 */
public void 
create_gondor() 
{ 
    create_trainhall();

    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_I_INSIDE, 1);

    create_guild_support();
    create_skill_raise();
    set_up_skills();

    add_item( ({"poster", "skill list", "skill-list", "list"}),
    exa_poster());
    add_cmd_item( ({"poster", "skill list", "skill-list", "list"}),
        "read", exa_poster());
}

public void
set_company_num(int i)
{
    gCompany = i;
}

/*
 * Function name: create_trainhall
 * Description  : configure your hall here
 */
public void 
create_trainhall()
{
    set_short("Ranger Training Hall");
    set_long("This is a training hall of the Rangers.\n");
}


/*
 * Function name: exa_poster
 * Description  : general text for the poster - displays the skills for
 *                the given company
 * Returns      : string - the description
 */
public string 
exa_poster()
{
    int i, size, snum, smax, *guild_sk = sk_query_train();
    string list;

    list = "These are the skills you can train here if you are a " +
        "member of " + COMPANIES[gCompany - 1] + ":\n\n";

    guild_sk = sort_array(guild_sk);
    for (i = 0, size = sizeof(guild_sk); i < size; i++)
    {
        snum = guild_sk[i];
        smax = ::sk_query_max(snum, 0);
        if (smax)
        {
            list += sprintf("  %-25s  %-25s\n", sk_trains[snum][0],
                sk_rank(smax));
        }
    }

    return list + "\n";
}

/*
 * Function name: cmax
 * Description  : determine max level this company will train
 *                a particular skill
 * Arguments    : int sk - the skill
 * Returns      : int - the max level
 */
public int 
cmax(int sk)
{
    int a = member_array(sk, SKILLS);

    if (a >= 0 && gCompany > 0 &&
      gCompany <= ITHILIEN_LEVEL) 
        return COMPANY_SKILLS[gCompany - 1][a];
    else
        return 0;
}


/*
 * Function name: pupil_max
 * Description  : determine max level of a skill for pupils 
 * Arguments    : int sk - the skill
 * Returns      : int - the max level
 */
public int 
pupil_max(int sk)
{
    int a = member_array(sk, SKILLS);
    if (a >= 0) 
        return APPRENTICE_SKILLS[a];
    else
        return 0;
}

public int get_max_virtue_value(object who, int skill)
{
    if (!who->query_ranger_has_virtues())
    {
        return 0;
    }
    object trainer = who->query_guild_trainer_occ();
    return trainer->sk_query_max(skill);
}


/*
 * Function name: set_up_skills
 * Description  : add all the ranger skills
 */
public void 
set_up_skills()
{
    string me;

    /* Combat skills */
    me = "use a sword effectively";
    sk_add_train(SS_WEP_SWORD,({ me, me }), "sword", 0,
        cmax(SS_WEP_SWORD), SS_OCCUP, 100);

    me = "use polearms effectively";
    sk_add_train(SS_WEP_POLEARM,({ me, me }), "polearm", 0,
        cmax(SS_WEP_POLEARM), SS_OCCUP, 100);

    me = "use axes effectively";
    sk_add_train(SS_WEP_AXE,({ me, me }), "axe", 0,
        cmax(SS_WEP_AXE), SS_OCCUP, 30);

    me = "shoot arrows and other missiles effectively";
    sk_add_train(SS_WEP_MISSILE, ({ me, me }), "bow", 0,
        cmax(SS_WEP_MISSILE), SS_OCCUP, 100);

    me = "defend in combat";
    sk_add_train(SS_DEFENCE,({ me, me }),"defence", 0,
        cmax(SS_DEFENCE), SS_OCCUP, 100);

    me = "parry blows with a weapon";
    sk_add_train(SS_PARRY, ({ me, me }), "parry", 0,
        cmax(SS_PARRY), SS_OCCUP, 100);

    me = "use two weapons in combat";
    sk_add_train(SS_2H_COMBAT, ({ me, me }), "two handed combat", 0,
        0, SS_OCCUP, 100);

    /* Magical skills */
    me = "recognize and handle herbs and plants";
    sk_add_train(SS_HERBALISM, ({ me, me }), "herbalism", 0,
        cmax(SS_HERBALISM), SS_OCCUP, 100);

    me = "mix potions from herbs and liquids";
    sk_add_train(SS_ALCHEMY, ({ me, me }), "alchemy", 0,
        cmax(SS_ALCHEMY), SS_OCCUP, 100);

    me = "understand magic";
    sk_add_train(SS_SPELLCRAFT, ({ me, me }), "spellcraft", 0,
        cmax(SS_SPELLCRAFT), SS_OCCUP, 100);

    me = "cast healing spells";
    sk_add_train(SS_ELEMENT_LIFE, ({ me, me }), "life spells", 0,
        cmax(SS_ELEMENT_LIFE), SS_OCCUP, 100);

    me = "summon energy from magical sources";
    sk_add_train(SS_FORM_CONJURATION,({ me, me }), "conjuration spells", 0,
        cmax(SS_FORM_CONJURATION), SS_OCCUP, 100);

    me = "cast abjuration spells";
    sk_add_train(SS_FORM_ABJURATION,({ me, me }), "abjuration spells", 0,
        cmax(SS_FORM_ABJURATION), SS_OCCUP, 100);

    /* Thief skills */
    me = "sneak and move stealthily about";
    sk_add_train(SS_SNEAK, ({ me, me }), "sneak", 0,
        cmax(SS_SNEAK), SS_OCCUP, 100);

    me = "hide and conceal";
    sk_add_train(SS_HIDE, ({ me, me }), "hide", 0,
        cmax(SS_HIDE), SS_OCCUP, 100);

    me = "find and remove traps";
    sk_add_train(SS_FR_TRAP, ({ me, me }), "traps", 0,
        cmax(SS_FR_TRAP), SS_OCCUP, 100);

    /* General skills */
    me = "hunt wild animals";
    sk_add_train(SS_HUNTING, ({ me, me }), "hunting", 0,
        cmax(SS_HUNTING), SS_OCCUP, 100);

    me = "be aware of the surroundings";
    sk_add_train(SS_AWARENESS, ({ me, me }), "awareness", 0,
        cmax(SS_AWARENESS), SS_OCCUP, 100);

    me = "find and follow tracks";
    sk_add_train(SS_TRACKING, ({ me, me }), "tracking", 0,
        cmax(SS_TRACKING), SS_OCCUP, 100);

    me = "navigate and sense the directions";
    sk_add_train(SS_LOC_SENSE, ({ me, me }), "location sense", 0,
        cmax(SS_LOC_SENSE), SS_OCCUP, 100);
    me = "befriend and handle animals";
    sk_add_train(SS_ANI_HANDL, ({ me, me }), "animal handling", 0,
        cmax(SS_ANI_HANDL), SS_OCCUP, 100);

    me = "ride horses";
    sk_add_train(SS_RIDING, ({ me, me }), "riding", 0,
        cmax(SS_RIDING), SS_OCCUP, 30);

    /* Special Ranger-skills */
    me = "hear living beings nearby";
    sk_add_train(SS_HEARING, ({ me, me }), "hearing", 20,
        cmax(SS_HEARING), SS_OCCUP, 100);
    me = "use dirty tricks in combat";
    sk_add_train(SS_BRAWLING, ({ me, me }), "brawling", 50,
        cmax(SS_BRAWLING), SS_OCCUP, 100);
    me = "ambush an opponent";
    sk_add_train(SS_AMBUSH, ({ me, me }), "ambush", 50,
        cmax(SS_AMBUSH), SS_OCCUP, 100);
}

/*
 * Function name: gs_hook_already_meditate
 * Description  : write a already-meditating msg
 */
public void
gs_hook_already_meditate()
{
    write("You are already in the pool. If you wish to finish " +
        "your meditating bath you can do so by typing 'rise'.\n");
}


/*
 * Function name: gs_hook_start_meditate
 * Description  : write a start-meditating msg
 */
public void
gs_hook_start_meditate()
{ 
    write("Slowly you sit down in the hot herb-bath, and " +
        "close your eyes. As the trance-inducing herb-smoke reaches into " +
        "your mind, a feeling of great ease and self control falls upon " +
        "you. You block off your senses and concentrate solely upon your " +
        "own mind. Just <rise> when you are done bathing.\n");
}

/*
 * Function name: gs_hook_rise
 * Description  : write a end-meditating msg
 */
public void
gs_hook_rise() 
{
    write("As if ascending from a great depth, you rise to the surface " +
        "of your consciousness. You exhale and feel very relaxed as " +
        "you get up and walk out of the herb bath.\n");
}

/*
 * Function name: sk_hook_write_header
 * Description  : Write the header to the improve or learn list
 * Arguments    : int steps - How many steps we are talking about
 */
public void
sk_hook_write_header(int steps)
{
    if (!steps)
        steps = 1;

    write("These are the skills you are able to " + query_verb() + " " +
        LANG_WNUM(steps) + (steps == 1 ? " step" : " steps") + " here.\n");
    write("  Skill:                  Cost:    " +
          "Next level:            Max level:\n" +
          "--------------------------------------" +
          "--------------------------------------\n");
}

/*
 * Function name: sk_hook_skillisting
 * Description  : Write the header to the list of skills
 */
public void
sk_hook_skillisting()
{
    write("Here follows all skills we teach, and your next level in " +
        "those skills:\n");
    write("  Skill:                  Cost:    " +
          "Next level:           Max level:\n" +
          "--------------------------------------" +
          "--------------------------------------\n");
}

public int
sk_cost(int snum, int fr, int to)
{
    int chosen = query_primary(this_player()),
        factor = query_primary_factor(this_player());

    // increase skill cost for the chosen weapon according to the
    // cost factor for this player. cost * (100 / factor) / 100
    if (snum == chosen)
        return ::sk_cost(snum, fr, to) * ( 100 + (10 * factor) ) / 100;
    else
        return ::sk_cost(snum, fr, to);
}

/*
 * Function name: sk_query_max
 * Description  : give the max we will teach for a particular skill
 * Arguments    : int sknum -- the skill
 *                int silent -- no msgs to player if set
 * Returns      : int -- the max
 */
public varargs int
sk_query_max(int sknum, int silent)
{
    object pl = this_player();
    if (pl->query_ranger_has_virtues())
    {
        return get_max_virtue_value(pl, sknum);
    }

    int ranger_stat, rlevel, skill_sum, current_max, wisint, orig_max, i, n;
    
    wisint = (pl->query_base_stat(SS_INT) + pl->query_base_stat(SS_WIS)) / 6;
    ranger_stat = pl->query_ranger_rank() * 3;

    if (member_array(sknum, SUBTERFUGE_SKILLS) >= 0 )
    {
        i = 0;
        skill_sum = 0;
        while (i < sizeof(SUBTERFUGE_SKILLS)) 
        {
            if ((n = pl->query_base_skill(SUBTERFUGE_SKILLS[i])) >= 0) 
                skill_sum +=n;

            i++;
        }

        current_max = (LEARN_FACTOR * ranger_stat) + wisint - skill_sum;
    }
    else if (member_array(sknum, NATURE_SKILLS) >= 0)
    {
        i = 0;
        skill_sum = 0;
        while (i < sizeof(NATURE_SKILLS))
        {
            if ((n = pl->query_base_skill(NATURE_SKILLS[i])) >= 0) 
                skill_sum += n;
            i++;
        }

        current_max = (LEARN_FACTOR * ranger_stat) + wisint - skill_sum;
    }
    else if (member_array(sknum, COMBAT_SKILLS) >= 0)
    {
        i = 0;
        skill_sum = 0;
        while (i < sizeof(COMBAT_SKILLS))
        {
            if ((n = pl->query_base_skill(COMBAT_SKILLS[i])) >= 0) 
                skill_sum += n;

            i++;
        }

        current_max = (LEARN_FACTOR * ranger_stat) + wisint - skill_sum;
    }
    else 
    {
        current_max = 100;
    }

    rlevel = pl->query_ranger_level();

    if ((rlevel <= APPROVED_APP_LEVEL && gCompany != 1) ||
      (rlevel > APPROVED_APP_LEVEL && rlevel != gCompany))
        orig_max = pupil_max(sknum);
    else 
        orig_max = ::sk_query_max(sknum, silent);

    current_max += pl->query_base_skill(sknum);

    if (current_max < 0) 
        return 0;

    if (current_max <= orig_max) 
        return current_max;

    return orig_max;
}

public int 
sk_do_train(int skillnum, object pl, int to_lev)
{
    if (pl->query_ranger_has_virtues())
    {
        int orig_max = get_max_virtue_value(pl, skillnum);
        if (to_lev > orig_max || orig_max < 0)
        {
            return 0;
        }

        pl->set_skill(skillnum, to_lev);
        return 1;
    }
    return sk_do_train(skillnum, pl, to_lev);
}



/*
 * Function name: sk_improve
 * Description  : player did "improve" -- write suitable mgs before 
 *                calling parent to do the work.
 * Arguments    : string str -- whatever they typed
 * Returns      : 1 on success, 0 on failure
 */
public int
sk_improve(string str)
{
    object tp = TP;
    int rlevel = tp->query_ranger_level();

    if (TP->query_wiz_level())
        return ::sk_improve(str);

    if (!rlevel)
    {
        write("\nThe Master Ranger says: Since you are not a Ranger, " +
          "you are not allowed to train here.\n");

        if (!str)
              write("The Master Ranger says: But you are welcome to have " + 
                  "a look at what we offer.\n");
        else
            return 1;
    }

    if (rlevel <= APPROVED_APP_LEVEL && gCompany != 1)
    {
        write("\nThe Master Ranger says: Since you are not a member of " +
            "this company, you are not allowed to train here.\n");
        return 1;
    }
    if (rlevel != gCompany && rlevel > APPROVED_APP_LEVEL) 
    {
        write("\nThe Master Ranger says: Since you are not a member of " +
            "this company, you are not allowed to train here.\n");
        return 1;
    }
/*
    if ((rlevel <= APPROVED_APP_LEVEL && gCompany != 1) ||
      (rlevel > APPROVED_APP_LEVEL && rlevel != gCompany))
    {
        write("\nThe Master Ranger says: You are welcome to train here, " +
            "but we cannot offer you more than apprentice training as " +
            "you are not a member of " + COMPANIES[gCompany - 1] + ".\n");
    }
*/
    return ::sk_improve(str);
}

public int
can_train_this_skill(object who, string skill, int step)
{
    int allow, pri, sec, s = sk_find_skill(skill);
    string name = who->query_real_name(), company = who->query_company();

    if(step < 0)
        return 1;

    if (who->query_base_skills(s) + step <= get_max_virtue_value(who, s))
        return 1;
    if (who->query_ranger_has_virtues(s))
        return 0;

    if(s == SS_WEP_SWORD &&
      (company == "north" || company == "ithilien"))
    {
        /* AG level */
        if(who->query_base_skill(s) + step <= 30)
            return 1;
                
        if((who->query_skill(SS_RANGER_PRI_WEP)%2) == 1)
            return 1;

        notify_fail("You have not chosen sword as your primary weapon! " +
            "You cannot train any higher at the moment!\n");
        return 0;
    }

    if((s == SS_WEP_POLEARM && company == "ithilien") ||
      (s == SS_WEP_MISSILE && company == "north"))
    {
        /* AG level */
        if(who->query_base_skill(s) + step <= 30)
            return 1;

        if((who->query_skill(SS_RANGER_PRI_WEP)%2) == 0)
            return 1;

        notify_fail("You have chosen sword as your primary weapon! " +
            "You cannot train any higher at the moment.\n");
        return 0;
    }

    return 1;
}

public int
train(string choice)
{
    int level = 0, skill_lay = 0, skill_race = 0, alt_skill, prop, pri;
    object trainer, who = this_player();
    string alt;

    /* Don't let non-rangers even get a notify_fail */
    if (!RANGERS_MEMBER(who))
        return 0;

    if (!strlen(choice))
    {
        notify_fail("Train which weapon?\n");
        return 0;
    }

    switch(choice)
    {
    case "sword":
        if (who->query_company() == "ithilien")
        {
            alt = "polearm";
            alt_skill = SS_WEP_POLEARM;
        }
        else if (who->query_company() == "north")
        {
            alt = "bow";
            alt_skill = SS_WEP_MISSILE;
        }
        else
        {
            notify_fail("You cannot choose a primary weapon " +
                "as you are not a member of the Rangers of the " +
                "North or the Rangers of Ithilien.\n");
            return 0;
        }

        prop = 1;
        pri = SS_WEP_SWORD;
        break;
    case "polearm":
        if (who->query_company() != "ithilien")
        {
            notify_fail("You cannot switch your primary weapon " +
                "to polearm.\n");
            return 0;
        }

        alt = "sword";
        alt_skill = SS_WEP_SWORD;
        prop = 2;
        pri = SS_WEP_POLEARM;
        break;
    case "bow":
        if (who->query_company() != "north")
        {
            notify_fail("You cannot switch your primary weapon " +
                "to bow.\n");
            return 0;
        }

        alt = "sword";
        alt_skill = SS_WEP_SWORD;
        prop = 2;
        pri = SS_WEP_MISSILE;
        break;
    default:
        notify_fail("Train sword or " + alt + "?\n");
        return 0;
    }

    if ((who->query_skill(SS_RANGER_PRI_WEP)%2) == prop)
    {
        notify_fail("You've already chosen " + choice + " as your " +
            "primary weapon. You can improve it or choose " + alt + ".\n");
        return 0;
    }

    if (!who->query_prop(RANGER_I_TRAIN_CHANGE))
    {
        who->add_prop(RANGER_I_TRAIN_CHANGE, 1);
        write("Are you sure you want to change your weapon to " +
            choice + "? You will have your " + alt + " skill lowered. " +
            "Please try again to confirm your weapon change to " +
            choice + ".\n");
        return 1;
    }
    else
        who->remove_prop(RANGER_I_TRAIN_CHANGE);

    /* We keep track of the primary weapon skill and how many
       times a player has changed it. Each time it's changed,
       the price goes up. This discourages changing often. */
    who->set_skill(SS_RANGER_PRI_WEP,
        who->query_skill(SS_RANGER_PRI_WEP) + 1);

    /* Lower the old choice skill */
    lower_secondary(alt_skill, who);
    write("You change weapon skill choice to " + choice + ".\n");
    return 1;
}

public void
lower_secondary(int skill, object who)
{
    mixed trainer;
    int skill_lay = 0, skill_race = 0, level, i, size;

    /* See if any of their other guilds train sword */
    trainer = who->query_guild_trainer_lay();
    if (pointerp(trainer))
    {
        for (i = 0, size = sizeof(trainer); i < size; i++)
        {
            catch(skill_lay = trainer[i]->sk_query_max(skill, 1));
            if (skill_lay > 0)
                break;
        }
    }
    else if (objectp(trainer) || stringp(trainer))
    {
        catch(skill_lay = trainer->sk_query_max(skill, 1));
    }

    trainer = who->query_guild_trainer_race();
    if (pointerp(trainer))
    {
        for (i = 0, size = sizeof(trainer); i < size; i++)
        {
            catch(skill_race = trainer[i]->sk_query_max(skill, 1));
            if (skill_race > 0)
                break;
        }
    }
    else if (objectp(trainer) || stringp(trainer))
    {
        catch(skill_race = trainer->sk_query_max(skill, 1));
    }

    level = max(skill_lay, skill_race);

    /* Take the higher of AG or other guilds. */
    level = max(level, 30);

    /* Take the lower of current level and allowable training. */
    level = min(level, who->query_skill(skill));

    /* Lower old choice weapon skill */
    who->set_skill(skill, level);
}

public int
query_primary_factor(object who)
{
    return ((this_player()->query_skill(SS_RANGER_PRI_WEP)) / 2);
}

public int
query_secondary(object who)
{
    int pri = query_primary(who);
    if (pri == SS_WEP_MISSILE || pri == SS_WEP_POLEARM)
        return SS_WEP_SWORD;

    if (NORTH_MEMBER(who))
        return SS_WEP_MISSILE;
    else if (ITHILIEN_MEMBER(who))
        return SS_WEP_POLEARM;
    else return -1;
}

public int
query_primary(object who)
{
    if ((this_player()->query_skill(SS_RANGER_PRI_WEP)%2) == 1)
        return SS_WEP_SWORD;
    else if (this_player()->query_company() == "north")
        return SS_WEP_MISSILE;
    else if (this_player()->query_company() == "ithilien")
        return SS_WEP_POLEARM;
    else
        return -1;
}

/*
 * Function name: init
 * Description  : add verbs
 */
public void 
init() 
{
    ::init();

    add_action(gs_meditate, "meditate");
    add_action(gs_meditate, "enter");
    add_action(gs_list    , "list");
    //add_action(train      , "train");

    init_skill_raise();
}

