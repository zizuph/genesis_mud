/* This is Korfgowl, the trainer who hangs out in the Grunts guild.  */
/* He is also a tough opponent. I may get several complaints from    */
/* mortals, but they can bugger off to Roke if they want easy kills. */
/* Skill training code based on the Gladiators trainer by Shiva.     */
/* Coded 14/12/95 by Tulix III.                                      */
/*								     */
/* Skills modified by Karath 18/02/97 to reflect changes             */
/* Skills modified by Tulix 15/12/99 to reflect latest policies      */

inherit "/std/monster";
inherit "/lib/skill_raise";

/* This line is put in to keep Mercade happy */
#pragma strict_types

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Emerald/tulix/t_defs.h"
#include "/d/Emerald/common/guild/grunts/grunts_defs.h"

public void set_up_skills();
public int  not_now(string dummy);

public void arm_me();

public void greet_member(object grunt);
public void init_soul(object living);
public void introduce_trainer(string name);
public int  is_grunt(mixed who);
public void reset_monster();
public string quest_info();
public string train_info();

/*
 * Function name: create_monster
 * Description:   define the all basics like race, stats, skills, etc. 
 */
public void 
create_monster()
{
    set_name("korfgowl");
    add_name(({ "trainer", "teacher", "grunt" }));
    set_title("the infamously noxious Grunt trainer");
    set_living_name("korfgowl");
    
    set_race_name("goblin");
    set_adj(({ "large", "battle-hardened" }));
    
    set_long("This battle-hardened goblin looks rather experienced in the " +
        "ways of the combat. If you ask nicely he may be able to teach you " +
        "some skills - but although skilled himself he is probably not " +
        "the greatest teacher, so don't expect too much.\n");
    
    add_prop(LIVE_I_QUICKNESS, 250);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(OBJ_S_WIZINFO, "This is the Grunts trainer.\n" +
        "Please note that any race can train here, and no skill is " +
        "taught here above what is available in adventurers guilds. " +
        "This is for tax reasons.\n");

    set_gender(0); /* Male */
 
    /* Stats -   STR  DEX  CON  INT  WIS  DIS  */
    set_stats(({ 240, 215, 230, 100, 100, 120 }));     /* Tough */
    set_alignment(-200);  /* He kills, and isn't fussy who it is.... */

    refresh_mobile();
 
    /* Set unarmed armour class and attacks. */
    set_all_hitloc_unarmed(60);       /* Quite a tough hide */
    set_all_attack_unarmed(90, 90);   /* Good attacks to match */

    /* Set the all important skills. */
    set_skill(SS_UNARM_COMBAT, 150);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE, 150);
    set_skill(SS_PARRY, 100);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_CLUB, 100);
    
    set_skill(SS_AWARENESS, 100);
 
    set_chat_time(5);                 /* Set speaking interval            */
    add_chat("mE cOod maYbe tEach yoo iV yoo cun pAy.");
    add_chat("dEez cAves iz verY cOld doWn Ere.");
    add_chat("Da gwUnts bArr iz a bIt rOwdY sumtImz.");
    add_chat("dOze lOuzee nOmes aZ tAyken oOvur Da bAnk.");
    add_chat("Da voOd en Da bArr iz gwIte unoOzal.");

    set_cchat_time(2);                /* Set combat speaking interval     */
    add_cchat("Me goNa smaAsh yoo in toO da gwOund.");
    add_cchat("Jus Oo dUuz yoo finK yoo iz dEelin wiV?");
    add_cchat("Yoo not lYke mee cOs mee bE a gObllyn?");
    add_cchat("mE rEely iz goNa tEach yoo a lEzon, yoo scUm.");
    
    set_act_time(6);                  /* Set action interval              */
    add_act("emote practices a few skillful moves with his weapon.");
    add_act("grunt happily");         /* Guess which guild he belongs to  */
    add_act("munch");
    add_act("pick nose");
    add_act("flick");
    add_act("flob");
    add_act("stink");
    add_act("knuckles");
    add_act("butt");
    add_act("leak");
    add_act("ears");

    add_ask(({ "quest", "quests" }), VBFC_ME("quest_info") );
    
    add_ask(({"skill", "skills", "train", "nicely", "improve", "learn"}), 
        VBFC_ME("train_info") );

    set_default_answer("The trainer thinks for a while.\n" +
        "The trainer shrugs his shoulders.\n");
    
    setuid();
    seteuid(getuid());

    set_alarm( 2.0, 0.0, init_soul ); /* Add the grunts command soul */
    
    set_up_skills();
}


/* ***********************************************************************
 * Skill training related functions
 */

/*
 * Function name: set_up_skills
 * Description:   This function defines which skills we want him to teach
 */
public void 
set_up_skills()
{
    create_skill_raise();
    
    /* Weapon skills */
    sk_add_train(SS_WEP_CLUB,     "thwap elves with clubs",      "club",0, 30);
    sk_add_train(SS_WEP_POLEARM,  "thrust polearms",          "polearm",0, 30);
    sk_add_train(SS_UNARM_COMBAT, "pummel with fists", "unarmed combat",0, 30);
    sk_add_train(SS_DEFENCE,      "dodge wimpy blows",        "defence",0, 20);
    sk_add_train(SS_BLIND_COMBAT, "smash inna dark",    "blindfighting",0, 20);
    
    /* General skills */
    sk_add_train(SS_AWARENESS,   "spot sneaky elves",    "awareness",  0, 30);
    sk_add_train(SS_APPR_MON,    "size up enemies",  "appraise enemy", 0, 30);
    sk_add_train(SS_CLIMB,       "keep from falling",    "climb",      0, 30);
    sk_add_train(SS_SWIM,        "avoid drowning",       "swim",       0, 30);

    /* This lot adds up to a total of 250 (maximum allowed is 400).     */
}

/*
 * Function name:   not_now
 * Description:     stop trainer from teaching skills while he is fighting
 * Arguments:       dummy: the skill the player wishes to improve
 */
public int
not_now(string dummy)
{
    write("The trainer is too busy teaching someone a harsh lesson.\n");
    return 1;
}

/*
 * Function name:   init_living
 * Description:     called when a player enters our environment
 */
public void
init_living()
{
    ::init_living();
    
    /* Check to see if we are busy fighting someone */
    if (TO->query_attack())
    {    
        /* Do not allow anyone to train if the trainer is in a fight */
        add_action(not_now, "improve");
        add_action(not_now, "learn");
        
        return;
    }
        
    /* Greet fellow grunts, as we are not too busy fighting. */
    if (is_grunt(TP))
        set_alarm( 4.00, 0.0, &greet_member(TP) );
    
    init_skill_raise();   /* We only get this far when not fighting */
}


/* ***********************************************************************
 * Combat related functions
 */

/*
 * Function name:   arm_me
 * Description:     give the trainer his weapons and armour (and booze!)
 */
public void
arm_me()
{
/*
    object weapon, armour, booze;

    weapon = clone_object( CAVE_DIR + "wep/longsword.c");
    weapon -> move(TO);

    armour = clone_object( CAVE_DIR + "arm/fake_collar.c");
    armour -> move(TO);

    armour = clone_object( CAVE_DIR + "arm/banded_mail.c");
    armour -> move(TO);

    armour = clone_object( CAVE_DIR + "arm/visored_helm.c");
    armour -> move(TO);
    
    armour = clone_object( CAVE_DIR + "arm/brig_leggings.c");
    armour -> move(TO);

    booze = clone_object( CAVE_DIR + "obj/stout.c");
    booze -> set_heap_size(30);
    booze -> move(TO);

    command("wield all");
    command("wear all");
*/
}

/*
 * Function name: attack_object
 * Description:   This function is called when we attack another object
 * Arguments:     enemy - The object we are about to attack
 */
public void
attack_object(object enemy)
{
    ::attack_object(enemy);

    /* Always best to get a few drinks down you during a fight */
    command("drink stouts");

    return;
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     enemy - The attacker
 */
public void
attacked_by(object enemy)
{
    ::attacked_by(enemy);

    /* Always best to get a few drinks down you during a fight */
    command("drink stouts");

    return;
}

/*
 * Function name:   special_attack
 * Description:     called when it is his turn to attack 
 * Arguments:       enemy: the player we are currently fighting
 * Returns:         1 if he makes a special attack, 0 if he doesn't
 */
public int
special_attack(object enemy)
{
    object me;
    int num;

    me = TO;
    
    num = random(10);
    
    if (!num)
    {
        /* No special attack this time. Just has a quick pint, instead. */
        command("drink stout");
    }
    
    /* Carry out normal attack if no special attacks were executed. */
    return 0;
}


/* ***********************************************************************
 * Other functions
 */

/*
 * Function name:   greet_member
 * Description:     make trainer greet members of the grunts guild
 * Arguments:       grunt: the player we wish to greet
 */
public void
greet_member(object grunt)
{
    int num;
    string *action;

    action = ({ "grunt happily", "ears", "greet", "wink" });

    num = random(sizeof(action));

    command(action[num] + " " + lower_case(TP->query_real_name()));
}

/*
 * Function name:   init_soul
 * Description:     add the grunts command soul to the trainer
 * Arguments:       living: the living we wish to add the soul to
 */
public void
init_soul(object living)
{
    add_cmdsoul(GUILD_SOUL);
    update_hooks();
}

/*
 * Function name:   is_grunt
 * Description:     find out if player is a grunt
 * Arguments:       who: the object/name we wish to check
 * Returns:         1 if player is a grunt, 0 otherwise.
 */
public int
is_grunt(mixed who)
{
    object ob;
   
    if (!who)
        return 0;

    if (stringp(who))
        ob = find_player(lower_case(who));
    else
    {   
        if (objectp(who))
            ob = who;
        else
            return 0;
    }
   
    if (!ob || !interactive(ob))
        return 0;

    if ((ob->query_guild_name_race()) == GUILD_NAME)
        return 1; /* query_guild_name_race() is defined by the guild shadow */
   
    return 0;
}

/*
 * Function name:   reset_monster
 * Description:     get some more beers from the bar
 */
public void 
reset_monster()
{
    object booze, me;
    
    me = TO;

    command("drink stouts");  /* Looks like its time to get another round */
    
    booze = present("stout", TO);
    if (!booze)
    {
        booze = clone_object(CAVE_DIR + "obj/stout");
        booze -> move(TO);
    }

    booze -> set_heap_size(30);
    
    tell_room(environment(me), QCTNAME(me) + " quickly nips off to the " +
        "Grunts bar to get some more drink.\nHe is back before you " +
        "realise he has left.\n", me);

}

/*
 * Function name: add_introduced
 * Description  : Called when a player is introduced
 * Arguments    : string name - the introduced persons [lower case] name
 */
public void
add_introduced(string name)
{
    set_alarm( 2.0, 0.0, &introduce_trainer(name) );
}

/*
 * Function name: introduce_trainer
 * Description  : Introduce trainer, to be polite
 * Arguments    : string name - the person we want to be introduced to 
 */
public void
introduce_trainer(string name)
{
    command("introduce me");
    command("grshake " + name);
}
    
/*
 * Function name:   train_info
 * Description:     tell players if we have any quests for them or not.
 * Returns:         empty string
 */
public string
quest_info()
{
    command("say I dOnt hAv nO qUests fOr yOo yeT.");

    return "";
}

/*
 * Function name:   train_info
 * Description:     give players instructions on how to train skills
 * Returns:         empty string
 */
public string
train_info()
{
    command("say I mAy bEe aYbul tO tEech yoo. Use <learn> and <improve>.");

    return "";
}

