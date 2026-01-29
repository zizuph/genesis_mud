/* A giant goblin guard - Tulix III, recoded 18/04/96                    */
/* This is one of Tulix's close personal friends.                        */
/* He was hired to keep undesirables out of the Grunts guild rooms, and  */
/* apart from occassional lapses, he seems to do his job pretty well.    */
/* Originally coded 1/3/1993 by Tulix I                                  */
/* Cloned by cave: /d/Emerald/cave/levelb/cave10b.c                      */

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"
#include "/d/Emerald/common/guild/grunts/grunts_defs.h"

/* This line is put in to keep Mercade happy */
#pragma strict_types

/* Prototype functions */
public void   init_soul();
public void   arm_me();
public void   greet_member(object grunt);
public void   introduce_monster(string name);
public void   spit_at_lichen();
public int    is_grunt(mixed who);
public string quest_info();
public string grunts_info();


public void
create_monster()
{
    set_name("grifnarl");
    set_title("the Giant Guard of the Grunts Guild");
    add_name("giant");
    add_name("guard");
    set_race_name("goblin");
    set_short("giant goblin");
    set_adj("giant");
    set_long(
        "You take a good look at the gigiantic figure that looms over you. " +
        "This is one big, mean looking Goblin. He is a replacement for " +
        "the old guard, who unfortunately, was just not up to the job " +
        "of keeping all the 'undesirables' out of the Grunts guild below. "+
        "He is much better at his job than the last guard.\nYou can tell " + 
        "that simply by the way he handles those axes.....\n" +
        "Perhaps fighting is not the best "+
        "way to get past this guy.\n");
   
    add_prop(OBJ_I_WEIGHT, 80000);
    add_prop(CONT_I_HEIGHT, 300);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_QUICKNESS, 300);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
   
    set_gender(0);
    
    /*           str, dex, con, int, wis, dis */
    set_stats(({ 165, 155, 180, 100, 100, 120}));
    refresh_mobile();
    set_alignment(-300);
   
    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(20,50);
   
    set_aggressive(0);
   
    add_ask(({ "quest", "quests" }), VBFC_ME("quest_info") );
    
    add_ask(({ "grunts", "guild", "Grunts" }), VBFC_ME("grunts_info") );

    set_default_answer("The giant goblin grunts stupidly.\n");

    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
   
    set_skill(SS_AWARENESS, 100);

    set_alarm( 1.0, 0.0, init_soul);

    set_act_time(4);

    /* Nearly the full repertoire of Grunt emotes. */
    add_act("flob");
    add_act("ears");
    add_act("fist");
    add_act("roar");
    add_act("grunt");
    add_act("munch");
    add_act("pick nose");
    add_act("crap");
    add_act("tongue");
    add_act("stink all");
    add_act("knuckles");
    add_act("butt");
    add_act("flick");
    add_act("spit at lichen");
}

public void
arm_me()
{
    object right_axe, left_axe, leggings, plate, collar;

    right_axe = clone_object( CAVE_DIR + "wep/right_giant_axe");
    right_axe -> move( TO );
    
    left_axe = clone_object( CAVE_DIR + "wep/left_giant_axe");
    left_axe -> move( TO );
    
    leggings = clone_object( CAVE_DIR + "arm/stout_leggings");
    leggings -> move( TO );
    
    plate = clone_object( CAVE_DIR + "arm/giant_plate");
    plate -> move( TO );

    collar = clone_object( CAVE_DIR + "arm/fake_collar");
    collar -> move( TO );

    command("wield all");
    command("wear all");

    return;
}

/*
 * Function name:   init_living
 * Description:     called when a player enters our environment
 */
public void
init_living()
{
    ::init_living();

    set_alarm( 2.0, 0.0, spit_at_lichen);
    
    /* Check to see if we are busy fighting someone */
    if (TO->query_attack())
        return;
    
    /* Greet fellow grunts, as we are not too busy fighting. */
    if (is_grunt(TP))
        set_alarm( 4.00, 0.0, &greet_member(TP) );
}

/*
 * Function name:   greet_member
 * Description:     make guard greet members of the grunts guild
 * Arguments:       grunt: the player we wish to greet
 */
public void
greet_member(object grunt)
{
    int a_num, g_num;
    string *action, *greeting;

    /* The player may have left the room. */
    if ( ENV(TO) != ENV(grunt) )
        return;

    action = ({ "grunt happily", "ears", "greet", "nod", "hug" });
    a_num = random(sizeof(action));
    
    greeting = ({ "fellOw GrUnt", "mY friEnd", "oLd bUddy", "wOrthy membEr"});
    g_num = random(sizeof(greeting));

    command("say GreEtingz tO yoo, " + greeting[g_num] + " " +
        capitalize(TP->query_real_name()) + "!");
    command(action[a_num] + " " + lower_case(TP->query_real_name()));
}

public void
spit_at_lichen()
{
    command("spit at lichen");
}

/*
 * Function name:   init_soul
 * Description:     add the grunts command soul to the guard
 */
public void
init_soul()
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
 * Function name: add_introduced
 * Description  : Called when a player is introduced
 * Arguments    : string name - the introduced persons [lower case] name
 */
public void
add_introduced(string name)
{
    set_alarm( 2.0, 0.0, &introduce_monster(name) );
}

/*
 * Function name: introduce_monster
 * Description  : Introduce monster, to be polite
 * Arguments    : string name - the person we want to be introduced to 
 */
public void
introduce_monster(string name)
{
    command("introduce me");
    command("grshake " + name);
}
    
/*
 * Function name:   quest_info
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
 * Function name:   grunts_info
 * Description:     give interested players some info about the guild.
 * Returns:         empty string
 */
public string
grunts_info()
{
    command("say Da grUnts guIld iz dA bEst in dA hOle wUrld!");
    command("say Itz a rAce guIld - sO I onlee allOw gOblyns dOwn thEre.");
    command("grunt happily");

    return "";
}

