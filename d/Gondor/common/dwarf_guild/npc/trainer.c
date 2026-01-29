/*
 * /d/Gondor/common/dwarf_guild/npc/trainer.c
 *
 * Copyright (C) Stas van der Schaaf - November 3 1993
 *               Mercade @ Genesis
 *
 * This is the master dwarf that teaches you in the trainhall of the
 * dwarven race guild.
 */

inherit "/d/Gondor/common/dwarf_guild/npc/remember";
inherit "/lib/skill_raise";

#include "/d/Gondor/defs.h"
#include "../dwarf.h"
#include <const.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define SAVE_FILE              (DWARVEN_RACE_GUILD_NPCS + "trainer_save")
#define MY_NAME                "thorin"
#define SK_MAX_SS_WEP_AXE      30
#define SK_MAX_SS_WEP_CLUB     30
#define SK_MAX_SS_BLIND_COMBAT 20
#define BASE                   80
#define COMPUTE_STAT           (((BASE * 3) / 4) + random(BASE / 2) + 1)
#define COMPUTE_SKILL          max(COMPUTE_STAT, 100)
#define CLONE_OBJECT(s)        clone_object(s)->move(this_object(), 1)
#define TRAINEE                player_name(this_player())
#define TIME_NO_SAY            10

#define SKILL_MAXIMA                            \
    ([ SS_WEP_AXE      : SK_MAX_SS_WEP_AXE,     \
       SS_WEP_CLUB     : SK_MAX_SS_WEP_CLUB,    \
       SS_BLIND_COMBAT : SK_MAX_SS_BLIND_COMBAT ])

/*
 * Global variable (will not be saved)
 */
static int last_time_said = 0;

/*
 * Prototypes
 */
void set_up_skills();

void
create_monster()
{
    set_name(MY_NAME);
    add_name( ({ "master", "trainer", "artist" }) );
    set_living_name(MY_NAME);
    set_race_name("dwarf");

    set_adj("agile");
    add_adj("dark-bearded");

    set_long(BSN("This dark-bearded dwarf is the master trainer of the " +
        DWARVEN_RACE_GUILD_NAME + ". If you pay him, he will teach you " +
        "all he knows and he knows many skills."));

    set_title("son of Dwoin, master artist with axes");
    set_gender(G_MALE);

    set_base_stat(SS_STR, BASE);
    set_base_stat(SS_DEX, COMPUTE_STAT);
    set_base_stat(SS_CON, BASE);
    set_base_stat(SS_WIS, COMPUTE_STAT);
    set_base_stat(SS_INT, COMPUTE_STAT);
    set_base_stat(SS_DIS, COMPUTE_STAT);

    REFRESH;  /* hp, mana, fatigue  */
    FIX_EUID; /* set the euid right */

    set_alignment(500);

    set_skill(SS_BLIND_COMBAT, 100);    /* He is a dwarf              */
    set_skill(SS_WEP_AXE,      100);    /* What else? He is a guru... */
    set_skill(SS_PARRY,        COMPUTE_SKILL);
    set_skill(SS_DEFENCE,      COMPUTE_SKILL);
    set_skill(SS_AWARENESS,    COMPUTE_SKILL);
    set_skill(SS_UNARM_COMBAT, COMPUTE_SKILL);
    set_skill(SS_2H_COMBAT,    COMPUTE_SKILL);

    set_mm_in(" arrives.");
    set_mm_out(" walks away.");

    set_npc_save_file(SAVE_FILE);

    create_skill_raise(); /* for the skills          */
    set_up_skills();      /* for the skills          */
    create_remember();    /* for remembering players */
}

void
do_die(object killer)
{
    if (!objectp(killer))
    {
        killer = previous_object();
    }

    FIX_EUID;
    write_file("/d/Gondor/common/dwarf_guild/npc/trainer_death",
        ctime(time()) + sprintf(" %-12s (%-3d)\n",
        capitalize(killer->query_real_name()), killer->query_average_stat()));

    ::do_die();
}

void
arm_trainer()
{
    object ob;

    fix_souls();

    CLONE_OBJECT(DWARVEN_RACE_GUILD_WEAPONS + "t_axe");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_WEAPONS + "t_axe"); /* He has 2! */
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "t_mail");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "t_greaves");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "t_helmet");

    ob = clone_object(DWARVEN_RACE_GUILD_ARMOURS + "npc_belt");
    ob->move(this_object(), 1);
    ob->set_owner_name(MY_NAME);

    command("wield all");
    command("wear all");

    ob = clone_object(DWARVEN_RACE_GUILD_OBJECTS + "wallet");
    ob->move(this_object(), 1);

    MONEY_MAKE_GC(random(10))->move(ob, 1);
    MONEY_MAKE_SC(random(20))->move(ob, 1);
    MONEY_MAKE_CC(random(30))->move(ob, 1);
}

void
init_living()
{
    ::init_living();

    init_skill_raise();
}

/*
 * Function name: set_up_skills
 * Description  : This function initializes the skills to be trained by
 *                Thorin.
 */
void
set_up_skills()
{
    string me;

    me = "use an axe";
    sk_add_train(SS_WEP_AXE,      ({ me, me }), me, 0, 50, -1, 0);
    me = "use a club";
    sk_add_train(SS_WEP_CLUB,     ({ me, me }), me, 0, 50, -1, 0);
    me = "fight in the dark";
    sk_add_train(SS_BLIND_COMBAT, ({ me, me }), me, 0, 20, -1, 0);
    me = "climb with hand and feet";
    sk_add_train(SS_CLIMB,        ({ me, me }), me, 0, 30, -1, 0);
    me = "navigate and be aware in unknown places";
    sk_add_train(SS_LOC_SENSE,    ({ me, me }), me, 0, 30, -1, 0);
    me = "appraise an opponent";
    sk_add_train(SS_APPR_MON,     ({ me, me }), me, 0, 30, -1, 0);
    me = "appraise value";
    sk_add_train(SS_APPR_VAL,     ({ me, me }), me, 0, 30, -1, 0);
    me = "appraise objects";
    sk_add_train(SS_APPR_OBJ,     ({ me, me }), me, 0, 30, -1, 0);
    me = "trade with profit";
    sk_add_train(SS_TRADING,      ({ me, me }), me, 0, 30, -1, 0);
    me = "handle animals";
    sk_add_train(SS_ANI_HANDL,    ({ me, me }), me, 0, 30, -1, 0);
}

/*
 * Function name: belt_ok
 * Description  : This function checks whether a member wears his/her belt.
 *                If the member does not wear a proper belt, he/she is not
 *                confirmed as a member.
 * Arguments    : int silent - the call may not print anything.
 * Returns      : int - success/failure.
 */
int
belt_ok(int silent)
{
    object arm;

    if (!objectp(arm = (object)TP->query_armour(A_WAIST)))
    {
        if (((time() - last_time_said) > TIME_NO_SAY) &&
            !silent)
        {
            last_time_said = time();

            npc_say("You are not wearing your belt, " + TRAINEE +
                ", so you do not qualify as a Rockfriend. Ergo, I might not " +
                "be able to train you all I know now.");
        }

        return 0;
    }

    if (!(arm->id(DWARVEN_RACE_GUILD_BELT_ID)))
    {
        if (((time() - last_time_said) > TIME_NO_SAY) &&
            !silent)
        {
            last_time_said = time();

            npc_say("The " + arm->short() + " you are wearing, " + TRAINEE +
                " is not the official belt of the " +
                DWARVEN_RACE_GUILD_NAME +
                ", so you do not qualify as a member now. Ergo, I might not " +
                "be able to train you all I know now.");
        }

        return 0;
    }

    if (arm->query_owner_name() != TP->query_real_name())
    {
        if (((time() - last_time_said) > TIME_NO_SAY) &&
            !silent)
        {
            last_time_said = time();

            npc_say("Your belt does not carry a brand of your name. See " +
                "Borin, the smith, and get him to brand your name on your " +
                "belt, " + TRAINEE + ". Now you do not qualify as a member. " +
                "Ergo, I might not be able to teach you all I know.");
        }

        return 0;
    }

    return 1;
}

/*
 * Function name: limited_max
 * Description  : Return the maximum non-members can train in this guild.
 * Arguments    : int skill - the skill to check.
 * Returns      : int - the maximum trainable.
 */
int
limited_max(int skill)
{
    if (member_array(skill, m_indices(SKILL_MAXIMA)) >= 0)
    {
        return SKILL_MAXIMA[skill];
    }

    return ::sk_query_max(skill);
}

/*
 * Function name: sk_query_max
 * Description  : This function is used to determine the maximum a player
 *                can train in a certain skill. I redefined it to allow
 *                members to train SS_WEP_AXE to 50, but other players only
 *                to the normal value as with an open (adventurers) guild.
 * Arguments    : skill  - the skill the player wants to train
 *                silent - if true, don't give a message.
 * Returns      : int    - the maximum (s)he can train in it.
 */
int
sk_query_max(int skill, int silent)
{
    if (IS_MEMBER(TP))
    {
        if (belt_ok(silent))
        {
            return ::sk_query_max(skill);
        }
    }
    else 
    {
        if (((time() - last_time_said) > TIME_NO_SAY) &&
            !silent)
        {
            last_time_said = time();

            npc_say("You are a friend of the Rockfriend Guild, " + TRAINEE +
                ", but I can only train you to some limits.");
        }
    }

    return limited_max(skill);
}

/*
 * Function name: query_skill_decay_max
 * Description  : This function is called from the train-room when the
 *                skill decay function wants to know whether the players
 *                skills may decay or not.
 * Arguments    : int skill - the skill to query.
 * Returns      : int - the maximum to train here from Thorin.
 */
int
query_skill_decay_max(int skill)
{
    return ::sk_query_max(skill);
}

int
sk_hook_unknown_skill(string skill, string verb)
{
    command("confused");
    npc_say("I can not teach you how to " + skill + ", " + TRAINEE +
        ", for I do not know a skill by that name.");
    return 1;
}

int
sk_hook_cant_train(string skill, int to_lev)
{
    command("hmph");
    npc_say("You are a greenhorn, " + TRAINEE + "! Grow up if you want to " +
        "become " + sk_rank(to_lev) + " in how to " + skill + ".");
    return 1;
}

int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    command("curse at " + CAP(TP->query_real_name()));
    npc_say("What trick are you trying to pull off, " + TRAINEE +
        "? You don't have enough money on you to pay for my service. " +
        "If you want to become " + sk_rank(to_lev) + " in how to " +
        sk_tdesc[sk_find_skill(skill)][0] + ", earn more money!");
    return 1;
}

void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    write("You improve your ability to " + sk_tdesc[snum][0] + ".\n");
    write("You achieve the rank of " + rank + ".\n");
    say(QCTNAME(this_player()) + " improves " + POSSESSIVE(TP) +
        " ability to " + sk_tdesc[snum][1] + " and receives the rank of " +
        rank + ".\n");
}

void
sk_hook_write_header(int steps)
{
    if (!steps)
        steps = 1;
    npc_say("These are the skills you are able to " + query_verb() +
        " " + LANG_WNUM(steps) + (steps == 1 ? " step" : " steps") + ", " +
        TRAINEE + ", together with the level you will reach then, " +
        "the maximum level I am able to teach you and what I will charge " +
        "you to reach the acquired level.");
    write("Skill:                 Cost:          Next level:          Maximum level:\n"+
          "---------------------------------------------------------------------------\n");
}

void
sk_hook_skillisting()
{
    npc_say("These are all skills I can teach you, " + TRAINEE +
        ", together with the next level you will reach, the maximum level " +
        "to which I am able to teach you and what I will charge you to " +
        "reach that next level.");
    write("Skill:                 Cost:          Next level:          Maximum level:\n"+
          "---------------------------------------------------------------------------\n");
}

int
sk_hook_no_list_learn()
{
    npc_say("There are no new skills I can teach you, " + TRAINEE +
        ". You might find others who can teach you new things though.");
    return 1;
}

int
sk_hook_no_list_improve()
{
    npc_say("I can not help you to improve any skills now, " + TRAINEE +
        ". Maybe there are new skills I can teach or you might find others " +
        "who can teach you more than I can.");
    command("frown");
    return 1;
}

int
sk_hook_improved_max(string skill)
{
    npc_say("I taught you all I know about how to " + skill + ", " +
        TRAINEE + ". Maybe someone else might be able to teach you " +
        "more.");
    return 1;
}

/*
 * We are friendly to other domains, Solamnian Knights may not kill him!
 */
int
query_knight_prestige()
{
    return -6;
}
