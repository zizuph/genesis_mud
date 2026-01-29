/*
 *    /d/Emerald/blackwall/delrimmon/npc/blackwall_orc.c
 *
 *    This is the standard file for orcs in the Blackwall Mountains.
 *    Some functions copied from /d/Gondor/morgul/npc/ithil_monster.c
 *
 *    Copyright (c) October 1998, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/orc";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
static int     Attack_Id;
static int     Wimpy_Run;
static string  OrigQuestion;

/* prototypes */
public void    create_blackwall_orc();
public void    create_orc();
public void    say_enemy(string str1, string str2);
public void    emote_enemy(string str);
public void    loot_corpse();
public void    set_restrain_path_with_delay();
public void    do_attack(object victim);
public void    check_attack(object pl);
public void    call_for_friends(object ob);
public void    attacked_by(object ob);
public void    help_friend(object ob, object friend);
public void    notify_ob_attacked_me(object friend, object attacker);
public void    init_attack();
public void    add_blackwall_emotes();
public void    add_blackwall_asks();
public void    react_intro(object tp);
public void    catch_question(string question);
public int     not_here_func();
public string  default_answer();
public string  name_answer();
public void    add_introduced(string name);
public string  orders_answer();
public string  keepers_answer();
public string  horse_answer();
public string  telberin_answer();
public string  women_n_children_answer();
public string  captain_answer();
public string  lowlands_answer();
public string  emerald_answer();
public string  blackwall_answer();
public string  darkling_answer();
public string  army_answer();
public string  val_shoreil_answer();
public string  job_answer();
public void    give_gems();


public void    set_wimpy_run(int i) { Wimpy_Run = i; }
public int     query_wimpy_run() { return Wimpy_Run; }

/*
 * Function name:        create_blackwall_orc
 * Description  :        dummy routine to be redefined in inheriting files
 */
public void
create_blackwall_orc()
{
} /* create_blackwall_orc */

/*
 * Function name:        create_orc
 * Description  :        set up the npc with domain presets
 */
nomask void
create_orc()
{
    int rnd     = random(11);

    seteuid(getuid(TO));

    set_name("soldier");
    add_name("_blackwall_orc");

    set_skill(SS_AWARENESS,    55+rnd);
    set_skill(SS_CLIMB,        25+rnd);
    set_skill(SS_BLIND_COMBAT, 80+rnd);

    set_skill(SS_WEP_SWORD,   30);
    set_skill(SS_WEP_POLEARM, 30);
    set_skill(SS_WEP_AXE,     30);
    set_skill(SS_WEP_KNIFE,   30);
    set_skill(SS_WEP_CLUB,    30);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_whimpy(0);
    set_wimpy_run(20);
    set_alignment(-200 - random(100) );

    set_learn_pref( ({ 1, 1, 1, 0, 0, 1, }) );
    config_orc(65 + (random(10) * 2));

    add_blackwall_emotes();

    /* respond nicely to questions */
    set_dont_answer_unseen(1);
    set_default_answer(VBFC_ME("default_answer"));
    set_not_here_func("not_here_func");
    add_ask( ({ "what's your name", "what is your name", "name" }),
        VBFC_ME("name_answer") );

    add_blackwall_asks();
    set_not_here_func("not_here_func");

    create_blackwall_orc();
    give_gems();
} /* create_orc */

/* 
 * Function name:        say_enemy
 * Description  :        we let the npc taunt his enemy
 *
 */
public void
say_enemy(string str1, string str2)
{
    object enemy = query_attack();

    if (!objectp(enemy))
    {
        return;
    }

    if (!present(enemy,ENV(TO)))
    {
        return;
    }

    command("say " + str1 + enemy->query_race_name() + str2);
} /* say_enemy */

/*
 * Function name:        emote_enemy
 * Description  :        we let the npc do an emote towards the enemy
 */
public void
emote_enemy(string str)
{
    object  enemy = query_attack();

    if (!objectp(enemy))
    {
        return;
    }

    if (!present(enemy, ENV(TO)))
    {
        return;
    }

    command(str + " " + enemy->query_real_name());
} /* emote_enemy */

/*
 * Function name:        loot_corpse
 * Description  :        the npcs can loot corpses
 */
public void
loot_corpse()
{
    command("get all from corpse");
} /* loot_corpse */

/*
 * Function name: set_restrain_path_with_delay
 * Description  : if there is not already one set, we set a restrain path
 *                for the npc based on its current location
 */
public void
set_restrain_path_with_delay()
{
    if (!sizeof(query_restrain_path()))
    {
        set_restrain_path(implode(explode(
          file_name(ENV(TO)), "/")[0..3], "/"));
    }
} /* set_restrain_path_with_delay */

/*
 * Function name:        do_attack
 * Description  :        checks to see if we can see the victim, then
 *                       attack
 */
public void
do_attack(object victim)
{
    remove_alarm(Attack_Id);
    Attack_Id = 0;

    if (objectp(query_attack()) || victim->query_npc())
    {
        return;
    }

    if (!objectp(victim) || !present(victim,ENV(TO)) || 
        !CAN_SEE(TO, victim) || !CAN_SEE_IN_ROOM(TO))
    {
        if (random(25) == 0)
        {
            command("say What was that noise?");
            return;
        }

        return;
    }

    command("kill "+victim->query_real_name());
} /* do_attack */

/*
 * Function name:        check_attack
 * Description  :        set up an attack if this is a goodaligned player,
 *                       or if this player has attacked other isengard
 *                       npcs
 */
public void
check_attack(object pl)
{
    if (objectp(query_attack()) || (Attack_Id && sizeof(get_alarm(Attack_Id))))
    {
        return;
    }

    if (pl->query_prop(BW_I_ENEMY) ||
        pl->query_alignment() > ENEMY_ALIGNMENT)
    {
        if (!objectp(pl) || !present(pl,ENV(TO)) || 
            !CAN_SEE(TO, pl) || !CAN_SEE_IN_ROOM(TO))
        {
            if (random(25) == 0)
            {
                command("say What's that noise?!");
            }

            return;
        }

        switch(random(12))
        {
            case 0:
                command("shout Enemies!");
                break;
            case 1:
                command("say Ha ha! Now you will die, maggot!");
                break;
            case 2:
                command("say There's the " + pl->query_race_name()
                    + "! Kill " + pl->query_objective() + "!");
                break;
            case 3:
                command("shout Death to the Army's enemies!");
                break;
            case 4:
                command("say That's " + pl->query_objective()
                    + "! Attack!!");
                break;
            default:
                break;
        }

        Attack_Id = set_alarm(3.0, 0.0, &do_attack(pl));
    }
} /* check_attack */

/*
 * Function name:        call_for_friends
 * Description  :        cause other isengard npcs to assist us
 */
public void
call_for_friends(object ob)
{
    int i;
    object  room = ENV(TO),
           *arr;

    filter(all_inventory(room), &->id("_blackwall_orc"))
           ->notify_ob_attacked_me(TO, ob);
} /* call_for_friends */

/*
 * Function name:        attacked_by
 * Description  :        set up the call for assistance, passing
 *                       our attacker to the next routine
 */
public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    if (interactive(ob))
    {
        /* we only remember attacks from evil players */
        if (ob->query_alignment() < 0)
        {
            ob->add_prop(BW_I_ENEMY,
                     ob->query_prop(BW_I_ENEMY) + 1);
        }
    }

    call_for_friends(ob);
} /* attacked_by */

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     ob - The person who attacked my friend
 *                friend - my friend who was attacked
 */
public void
help_friend(object ob, object friend)
{
    if (objectp(ob) && !query_attack() && present(ob, ENV(TO))
        && !(Attack_Id && sizeof(get_alarm(Attack_Id)))
        && CAN_SEE(TO, ob) && CAN_SEE_IN_ROOM(TO))
    {
        /* cut down on some spam, here... */
        if (!random(4))
        {
            command("shout Die, maggot of "
              + LANG_ADDART(ob->query_race_name()) + "!");
        }

        Attack_Id = set_alarm(3.0, 0.0, &do_attack(ob));
    }
} /* help_friend */

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate who was attacked
 *                attacker - The attacker
 */
public void
notify_ob_attacked_me(object friend, object attacker)
{
    if (objectp(query_attack()) || friend == TO)
    {
        return;
    }
   
    if (random(10))
    {
        set_alarm(2.0 + 5.0 * rnd(), 0.0, &help_friend(attacker, friend));
    }
} /* notify_ob_attacked_me */

/*
 * Function name:        init_attack
 * Description  :        set up the fight
 */
public void
init_attack()
{
    if (query_attack())
    {
        return;
    }
   
    set_alarm(0.0, 0.0, &check_attack(TP));
} /* init_attack */

/*
 * Function name:        add_blackwall_emotes
 * Description  :        these are the standard emotes for the blackwall
 *                       orcs. to change them in inheriting files,
 *                       simply redefine this function there.
 */
public void
add_blackwall_emotes()
{
    set_chat_time(15 + random(15));
    add_chat("Heh... I can't wait till we get orders to march!");
    add_chat("The Keepers don't scare me! I'll cut them down"
           + " to size!");
    add_chat("I say we burn Telberin first... its got the most"
           + " elves!");
    add_chat("Once we've taken that damned Elf Captain, then"
           + " we can do as we please in the lowlands!");

    set_cchat_time(5 + random(10));
    add_cchat("Taste my black blade, pathetic fool!");
    add_cchat("If there's one thing I can't stand, it's you!");
    add_cchat("Now you've angered me. Soon you'll be dead!");
    add_cchat("The Master told us we'd have practice soon. Too bad"
            + " it isn't more of a challenge!");

    set_act_time(15 + random(15));
    add_act("frown");
    add_act("emote tests the weight of his weapon.");
    add_act("scratch");

    set_cact_time(2 + random(2));
    add_cact("emote crouches, swinging wildly at you with his weapon!");
    add_cact("shout You won't take me, sniveling fool!");
    add_cact("emote spits on you in disgust!");
    add_cact("scream");
} /* add_blackwall_emotes */

/*
 * Function name:        add_blackwall_asks
 * Description  :        these are the standard asks defined for the
 *                       blackwall orcs. they can be redefined in
 *                       inheriting npcs for more specific responses
 */
public void
add_blackwall_asks()
{
    add_ask( ({"march", "orders", "orders to march", "marching orders",
               "marching", "promises"}),
        VBFC_ME("orders_answer"));
    add_ask( ({"keeper", "keepers", "keepers of telberin", "enemy",
               "enemies", "elf", "elves"}),
        VBFC_ME("keepers_answer"));
    add_ask( ({"horse", "horses"}),
        VBFC_ME("horse_answer"));
    add_ask( ({"telberin", "city", "elf city"}), 
        VBFC_ME("telberin_answer"));
    add_ask( ({"women", "children", "women and children"}),
        VBFC_ME("women_n_children_answer"));
    add_ask( ({"elf captain", "captain of the keepers",
               "captain of the keepers of telberin",
               "curan", "curan attai", "attai" }),
        VBFC_ME("captain_answer"));
    add_ask( ({"lowlands", "lowlands of emerald"}),
        VBFC_ME("lowlands_answer"));
    add_ask( ({"emerald"}),
        VBFC_ME("emerald_answer"));
    add_ask( ({"blackwall", "mountains", "blackwall mountains",
               "home", "blackwall fortress", "fortress"}),
        VBFC_ME("blackwall_answer"));
    add_ask( ({"darkling", "leader", "real leader", "darklings",
               "master"}),
        VBFC_ME("darkling_answer"));
    add_ask( ({"chieftain", "orcs", "chieftains", "orc",
               "train", "trained", "training", "army",
               "army of darkness", "the army", "soldier",
               "soldiers"}),
        VBFC_ME("army_answer"));
    add_ask( ({"val shoreil", "val-shoreil"}),
        VBFC_ME("val_shoreil_answer"));
    add_ask( ({"job", "work", "duty"}),
        VBFC_ME("job_answer"));
} /* add_blackwall_asks */

/*
 * Function name:        react_intro
 * Description  :        respond to introduction
 * Arguments    :        object tp -- the person who intro'd
 */
public void
react_intro(object tp)
{
    if (ENV(tp) != ENV())
    {
        command("sneer");
        return;
    }

    switch(random(6))
    {
    case 0:
        command("sneer amused "+tp->query_real_name());
        break;
    case 1:
        command("say Heh... so, "+tp->query_pronoun()+" wants to know"
              + " my name. Not a chance.");
        break;
    case 2:
        command("say You call that a name?");
        break;
    case 3:
        command("say Ha! We'll have to remember that one!");
        break;
    case 4: 
        command("bow sarcast");
        break;
    case 5:
        command("say Do you expect me to applaud?");
        break;
    }
} /* react_intro */


/***** ask routines below here *****/


/*
 * Function name:       catch_question
 * Description  :       intercept /std/act/asking.c's catch_question() to:
 *                      1) strip leading "for", "about" and trailing "?"
 *                      2) remember the original question
 * Arguments:           string question -- whatever the player asked
 */
public void
catch_question(string question)
{
    string      *tmp_arr,                       /* preps/verbs of interest */
                stuff1, stuff2, stuff3;         /* tmp strings */

    if (objectp(query_attack()))
    {
        return; /* no answers if fighting */
    }

    OrigQuestion = question;
    if (strlen(question))
    {
        /* strip off leading "for", "about" and trailing " ?" */
        tmp_arr = ({ "for", "about" });
        if (parse_command(question, ({}), "%p %s", tmp_arr, stuff1))
        {
            question = stuff1;
        }
        if (sscanf(question, "%s ?", stuff1) ||
            sscanf(question, "%s?", stuff1))
        {
            question = stuff1;
        }
    }
    ::catch_question(question);
} /* catch_question */

/*
 * Function name:       not_here_func
 * Description  :       called when player asks question & leaves
 * Returns      :       0 -> don't answer the question
 */
public int
not_here_func()
{
     command("curse angrily");
     command("shout I wouldn't have told you, anyway!");
     return 0;
} /* not_here_func */

/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    string      question = query_question();

    if (strlen(question))
    {
        DEBUG_LOG(TP->query_real_name()+" questions: '"+
            ((question != OrigQuestion) ? OrigQuestion+"' -> '" : "")+
                question+"'\n");
    }
    command("sneer . "+TP->query_real_name());
    command("say I'm sick of talking to you!");
    return "";
} /* default_answer */

/* 
 * Function name:       name_answer
 * Description  :       respond to questions about name
 *
 */
public string
name_answer()
{
    object      tp = TP;

    /* probably unnecessary, since we set not_here_func, but ... */
    if (!objectp(tp))
    {
        return "";
    }

        command("sneer");
        command("say You're as stupid as you look, "+
            TP->query_race_name()+".");
        command("say You'll not have my name!");

    return "";
} /* name_answer */

/*
 * Function name:       add_introduced
 * Description  :       Add the name of a living who has introduced to us
 * Arguments    :       string name -- name of the introduced living
 */
public void
add_introduced(string name)
{
    /* wizards always know the npc name, so query_met() is true.
     * however, assume that if a wiz intro'd, we should respond
     */
    if (interactive(TP) &&
        CAN_SEE_IN_ROOM(TO) &&
        CAN_SEE(TO, TP) &&
        (!TP->query_met(query_name()) ||
         TP->query_wiz_level()))
    {
        set_alarm(1.0 + (2.0 * rnd()), 0.0, &react_intro(TP));
    }
} /* add_introduced */

/*
 * Function name:       orders_answer
 * Description  :       respond to questions about orders, marching
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"march", "orders", "orders to march", "marching orders",
 *             "marching", "promises"}),
 */
public string
orders_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Always promises that we will march soon... but"
              + " do we? No!");
        break;
    case 1:
        command("say Our orders are our business!");
        break;
    case 2:
        command("say When we do march, it will be glorious!");
        break;
    }
    return "";
} /* orders_answer */

/*
 * Function name:       keepers_answer
 * Description  :       respond to questions about the KoT
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"riders", "rohirrim", "riders of rohan", "enemy",
 *             "enemies", "horse lovers"}),
 */
public string
keepers_answer()
{
    switch (random(3))
    {
    case 0:
        command("say When we march, the Keepers will regret it!");
        break;
    case 1:
        command("say Those damned Elves! I'll enjoy cutting"
              + " their worthless horses into meat!");
        break;
    case 2:
        command("say I hate them ... their horses, their pathetic"
          + " elf captain, their city. All will burn!");
        break;
    }
    return "";
} /* keepers_answer */

/*
 * Function name:       horse_answer
 * Description  :       respond to questions about the horses of Telberin
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"horse", "horses", "steed", "steeds", "steeds of rohan",
 *             "mearas"}),
 */
public string
horse_answer()
{
    switch (random(3))
    {
    case 0:
        command("say The Keepers think their horses will help them"
              + " defeat us. What a laugh!");
        break;
    case 1:
        command("say The only thing good about horses is the way"
              + " they taste.");
        break;
    case 2:
        command("say When we burn Telberin, we'll sell those horses..."
              + " at least the ones we don't eat.");
        break;
    }
    return "";
} /* horse_answer */

/*
 * Function name:       telberin_answer
 * Description  :       respond to questions about Telberin
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"edoras", "city of rohan"}), 
 */
public string
telberin_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Telberin won't stand long once we march!");
        break;
    case 1:
        command("say Telberin is pathetic! I've seen better defenses"
              + " on a toolshed.");
        break;
    case 2:
        command("say I've heard that there are lots of women and"
              + " children in Telberin. Won't that be fun?");
        break;
    }
    return "";
} /* telberin_answer */

/*
 * Function name:       women_n_children_answer
 * Description  :       respond to questions about women & children
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"women", "children", "women and children"}), 
 */
public string
women_n_children_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Women and children first, I always say!");
        break;
    case 1:
        command("emote grins, nodding cruelly.");
        break;
    case 2:
        command("say I can hear their screams already! Ha Ha!");
        break;
    }
    return "";
} /* women_n_children_answer */

/*
 * Function name:       captain_answer
 * Description  :       respond to questions about the Captain
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"captain", "rider captain", "captain of the riders",
 *             "captain of the riders of rohan", "rohirrim captain",
 *             "eomer"}),
 */
public string
captain_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Curan, they call him... but we call him target"
              + " practice!");
        break;
    case 1:
        command("say Sooner or later he'll make a mistake, and then"
              + " we'll have the lowlands to ourselves!");
        break;
    case 2:
        command("say They said we'd march when he is dead. Well,"
              + " it is taking too long!");
        break;
    }
    return "";
} /* captain_answer */

/*
 * Function name:       lowlands_answer
 * Description  :       respond to questions about the plains of rohan
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"plains", "plains of rohan"}),
 */
public string
lowlands_answer()
{
    switch (random(3))
    {
    case 0:
        command("say We'd have the lowlands all to ourselves if it"
              + " weren't for those damned Elves!");
        break;
    case 1:
        command("say Once in a while we find a horse in the lowlands,"
              + " and get a little extra food for supper.");
        break;
    case 2:
        command("say The plains belong to Blackwall Fortress, and the"
              + " Keepers will soon learn that!");
        break;
    }
    return "";
} /* lowlands_answer */

/*
 * Function name:       emerald_answer
 * Description  :       respond to questions about the rohan
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"rohan"}),
 */
public string
emerald_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Emerald! That is just another name for the land"
              + " that belong to us!");
        break;
    case 1:
        command("say Emerald won't last long... not now that the"
              + " Darklings have trained the Army of Darkness.");
        break;
    case 2:
        command("say We'll see how much Emerald changes in the years"
              + " to come. I predict a lot of wildfires!");
        break;
    }
    return "";
} /* emerald_answer */

/*
 * Function name:       blackwall_answer
 * Description  :       respond to questions about isengard
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"isengard", "home"}),
 */
public string
blackwall_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Blackwall Fortress isn't bad. There is plenty to"
              + " eat and drink there!");
        break;
    case 1:
        command("say Blackwall Fortress will soon be a great capital!");
        break;
    case 2:
        command("say Compared to Telberin, Blackwall Fortress is a"
              + " paradise!");
        break;
    }
    return "";
} /* blackwall_answer */

/*
 * Function name:       darkling_answer
 * Description  :       respond to questions about the darklings
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"saruman", "leader", "real leader", "sharkey"}),
 */
public string
darkling_answer()
{
    switch (random(3))
    {
    case 0:
        command("say The Darklings know how to treat good soldiers!");
        break;
    case 1:
        command("say Ever since we joined with them, they've given us"
              + " plenty of good food and drink!");
        break;
    case 2:
        command("say The Master is a smart one! He'll show those"
              + " Keepers who owns Emerald!");
        break;
    }
    return "";
} /* darklings_answer */

/*
 * Function name:       army_answer
 * Description  :       respond to questions about the uruk-hai
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"uruk", "uruk-hai", "uruks", "orc",
 *             "train", "trained", "training"}),
 */
public string
army_answer()
{
    switch (random(3))
    {
    case 0:
        command("say The Army of Darkness is the most fearsome"
              + " group of warriors in Emerald!");
        break;
    case 1:
        command("say Mess with the Army, and you've got yourself"
              + " a reason to run very fast.");
        break;
    case 2:
        command("say The Army fears no one! They will soon show"
              + " the Elves how to bleed.");
        break;
    }
    return "";
} /* army_answer */

/*
 * Function name:       val_shoreil_answer
 * Description  :       respond to questions about Val-Shoreil
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"sauron", "dark lord"}),
 */
public string
val_shoreil_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Shhh... keep your voice down! We don't talk"
              + " about that!");
        break;
    case 1:
        command("say He is almighty, and he shall win Emerald back!");
        break;
    case 2:
        command("say Don't use that name around here!");
        break;
    }
    return "";
} /* val_shoreil_answer */

/*
 * Function name:       job_answer
 * Description  :       respond to questions about work
 * Returns      :       null string ... response is gen'd via command()
 *
 *  add_ask( ({"job", "work", "duty"}),
 */
public string
job_answer()
{
    switch (random(3))
    {
    case 0:
        command("say I kill the Elves of Telberin. What do you do?");
        break;
    case 1:
        command("say It is my job to kill people who ask too many"
              + " questions...");
        break;
    case 2:
        command("say I do what the Darklings say!"
              + " Now get out of here!");
        break;
    }
    return "";
} /* job_answer */


/*
 * Function name:        give_gems
 * Description  :        These orcs enjoy black gems. There is a chance
 *                       that they will load with some.
 */
public void
give_gems()
{
    object  gem;

    if (random(2))
    {
        return; /* only 1/3 will have gems */
    }

    if (!random(5))
    {
        gem = clone_object("/d/Genesis/gems/obj/pearl_black");
    }
    else
    {
        gem = clone_object("/d/Genesis/gems/obj/onyx");
    }

    gem->move(this_object());
} /* give_gems */
