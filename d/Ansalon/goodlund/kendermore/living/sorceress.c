/* Witch outside the forests of Kendermore, Gwyneth June 11, 1999 */
/* Modified by Vitwitch 10/2021 to be a quest giver */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

#define ROBEOFWOVENWORMS "_zeboim_robe_of_woven_worms"
#define SATEELA_INTROD "_sateela_m_introd"

#define QUEST_DOMAIN "Ansalon"
#define QUEST_GROUP 1
#define QUEST_BIT 2
#define QUEST_XP 3200
#define QUEST_ALIGN_DELTA -100
#define QUEST_NAME "Robe of the Darkling Sea (Quest)"
#define ALLOW_QUEST_REWARD 1

inherit "/std/act/action.c";
inherit AM_FILE

create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("sateela");
    add_name("sorceress");
    set_living_name("sateela");
    set_race_name("human");
    set_adj("willowy");
    add_adj("cold-hearted");
    set_gender(G_FEMALE);
    set_title("of Thenwyg, Servant of the Five-Headed Dragon");
    set_introduce(1);
    set_short("willowy cold-hearted sorceress");
    set_long("This woman looks back at you with a fire in her hard eyes. " + 
        "You can detect an air of magic about her. Perhaps it's best to " + 
        "leave this servant of Takhisis alone.\n");

    // increase in stats 100->150 (Vitwitch 2021)
    set_stats(({150,150,150,150,150,150}));
    set_hp(query_max_hp());

    // increase in skill 50->100 (Vitwitch 2021)
    set_skill(SS_AWARENESS, 100);
    // increase in skill 80->100 (Vitwitch 2021)
    set_skill(SS_UNARM_COMBAT, 100);

    set_alignment(-500);
    set_knight_prestige(200);
    set_act_time(10);
    add_act("scowl");
    add_act("emote mixes a handful of flowers into her pot.");
    add_act("emote brushes a lock of fire red hair from her face.");
    add_act("smile wickedly");
    set_alarm(0.0,0.0, "arm_me");

    add_prop(LIVE_M_NO_ACCEPT_GIVE, " only wants the Robe of Woven "+
       "Worms. If you have it, you should ask for your reward.\n");

    set_default_answer("The sorceress looks at you sharply -- her "+
                       "flashing eyes warn against further discussion "+
                       "of that matter.\n");

    add_ask(({"help","quest","task"}), "@@ask_something|help@@");
    add_ask(({"reward","my reward","for my reward"}),
              "@@ask_something|reward@@");

    add_ask(({"robe","robe of worms","robe of woven worms"}),
              "@@ask_something|robe@@");
    add_ask(({"darkling sea","ship","wreck"}),"@@ask_something|ship@@");
    add_ask(({"shore","rocky shore","jetty","reefcutters jetty"}),
              "@@ask_something|jetty@@");
    add_ask(({"skill","fish","fishing"}),
              "@@ask_something|fishing@@");
    add_ask(({"bait","particular bait"}),
              "@@ask_something|bait@@");
}


public void
add_introduced(string who)
{
    if (!query_attack())
        react_introduce(who);
}


public varargs void
react_introduce(mixed who = 0)
{
    object ob;
    who = lower_case(who);

    if (!(ob = find_player(who)))
        return;

    ob->add_prop(SATEELA_INTROD,1);

    if (!objectp(ob))
    {
        command("introduce me");
        return;
    }
    
    if (environment(ob) != environment() ||
        !CAN_SEE(this_object(), ob))
        return;
    
    command("introduce me to " + OB_NAME(ob));
}


int
is_known( object who )
{
    if ( !(who->query_prop(SATEELA_INTROD)) )
        return 0;
    return 1;
}


void
reward_outcome( object who )
{
    if ( !ALLOW_QUEST_REWARD ) return;

    who->catch_msg("You reflect upon Sateela's betrayal of her Queen's "+
                   "wishes.\n\nYou feel more experienced.\n\n");

    tell_room(E(who), QCTNAME(who) + " looks more experienced.\n", who);

    who->adjust_alignment(QUEST_ALIGN_DELTA);
    who->add_exp_quest(QUEST_XP);
    who->set_bit(QUEST_GROUP, QUEST_BIT);
    A_QUEST_LOG("quest", QUEST_NAME, who, QUEST_XP);

    tell_room( E(who), "The roiling darkness and the sorceress abruptly "+
               "vanish. The anguished scream of " 
               + QTNAME(TO) + " fades slowly.\n\n");

    remove_object();

    return;
}


void
reward_seq2( object who )
{
    who->catch_msg("\n\nThe hissing in your mind reverberates, you hear, "+
                   "'SSSATEELA... YOUR SSSILK ROBE WASSS A GIFT... "+
                   "FAITHLESS SSSERVANT... YOU MUSSST SSSUFFER'\n\n");

    tell_room( E(who), "The darkness surrounding " + QTNAME(TO) + 
               " and " + QTNAME(who) + " roils violently.\n", who);

    set_alarm( 3.0, 0.0, &reward_outcome(who) );

    return;
}


void
reward_seq1( object who )
{
    this_object()->set_appearance_offset(50);

    who->catch_msg("\nWith " + QTPNAME(TO) + " silk robe completely "+
                   "shredded in the violence of the "+
                   "struggle, you find yourself battling a hideous "+
                   "creature... just before a dark cloud engulfs you "+
                   "and " + QCTNAME(TO) + " both.\n\n"); 

    tell_room( E(who), QCTNAME(TO) + " and " + QTNAME(who) 
                 + " are both engulfed in sudden darkness.\n", who);
    command("shout NO... MY QUEEN... LET ME BE MADE OVER!");
    command("say Did I not serve you best when I was a beauty?"); 

    who->catch_msg("\n\nYour mind fills with an immense hissing that drives "+
                   "out rational thought... a maelstrom of draconic heads "+
                   "surrounds you and " + QTNAME(TO) + ", with gouts of "+
                   "white-hot flame.\n\n");

    set_alarm( 3.0, 0.0, &reward_seq2(who) );

    return;
}


void
reward_seq0( object who )
{
    who->catch_msg("\n\nYou try and give the disgusting Robe of " +
        "Worms to " + QTNAME(TO)+ " but it clings wetly to you!\n");

    who->catch_msg( QCTNAME(TO) + " looks upon you in fury.\n\n");
    tell_room( E(who), QCTNAME(TO) + " looks at " + QTNAME(who) 
          + " in fury.\n", who);
    command("shout GIVE ME THE ROBE NOW!"); 

    who->catch_msg("You futilely try to give the Robe of Worms " +
        "to " +QTNAME(TO)+ " to no avail!\n\n" + 
        QCTNAME(TO) + " claws wildly at the Robe "+
        "of Worms like a savage animal... in the fevered struggle "+
        "her own clinging silk robe begins to rend and tear. "+
        "With every new rent in the robe, her features are "+
        "rendered more grotesque.\n");
    tell_room( E(who), QCTNAME(TO) + " claws at " + QTNAME(who) 
         + ".\n", who);

    set_alarm( 3.0, 0.0, &reward_seq1(who) );

    return;
}


public void
do_answer(string what, object who)
{
    if ( !objectp(who) || E(who) != E(TO))
        return;   /* We wont speak if the player is gone */

    if(!CAN_SEE(TO, who))
    {
        who->catch_msg("\n" + QCTNAME(TO) + " peers about keenly... "+
           "seeing nothing before returning to her arcana.\n");
        return;
    }

    if (query_attack()) 
    {
        who->catch_msg("\n" + QCTNAME(TO) + " glares at you.\n");
        who->catch_msg(QCTNAME(TO) + " sneers at you: Forces are in play "+
              "here... blood and steel and magicks... "+
              "no time for chatter...\n");
        say(QCTNAME(TO) + " dismisses " + QTNAME(who) + ".\n", who);
    } 

    if ( !is_known(who) )
    {
        who->catch_msg(QCTNAME(TO) + 
          " shifts a fiery lock from before her eyes revealing a scowl.\n");
        who->catch_msg("\n" + QCTNAME(TO) + " peers at you suspiciously.\n");
        who->catch_msg(QCTNAME(TO) + " says to you: And who are you "+
          "to address me unnamed? Speak your true name if you dare.\n");
        say(QCTNAME(TO) + " queries " + QTNAME(who) + 
           " imperiously.\n", who);
        return;
    }

    switch ( what )
    {
    case "robe":
        say(QCTNAME(TO) + " stares at " + QTNAME(who) + ".\n", who);
        who->catch_msg("\n" + QCTNAME(TO) + " stares at you with light "+
                      "in her eyes. Whispered words cross your mind:\n");
        who->catch_msg("'The Robe of Worms, of Woven Worms, is the sometime "+
                  "raiment of Zeboim, daughter of my Queen. That faithless "+
                  "child has cast it aside. The wise know it to be the "+
                  "font of Her beauty in Her watery realm. I would have "+
                  "it here... so that I might return it to Takhisis, the "+
                  "Queen of Darkness, the many splendoured Dragon of Five "+
                  "Heads. You must bring the robe to me in secret so that "+
                  "my return of it comes as a surprise gift. The robe is "+
                  "to be found in the Darkling Sea. If you have it with you, "+
                  "ask me about your reward.'\n\n");
        return;

    case "ship":
        say(QCTNAME(TO) + " stares at " + QTNAME(who) + ".\n", who);
        who->catch_msg("\n" + QCTNAME(TO) + " stares at you with light "+
                      "in her eyes. Whispered words cross your mind:\n");
        who->catch_msg("'The Darkling Sea is a ship -- cravenly named after "+
                  "the daughter of my Queen. The men aboard sought Her "+
                  "favour and forgiveness for sailing upon Her seas. "+
                  "Not long out of the port of Palanthas, in sight of "+
                  "a safe jetty on a rocky shore in a storm, She summoned "+
                  "this packet of "+
                  "fools to Her deeps so they might attend Her forever. "+
                  "She is eternally capricious. She soon tired of them "+
                  "and moved on. But She lost Her robe in the broken vessel, "+
                  "and has not returned for it since.'\n\n");
        return;

    case "fishing":
        say(QCTNAME(TO) + " stares at " + QTNAME(who) + ".\n", who);
        who->catch_msg("\n" + QCTNAME(TO) + " stares at you with light "+
                      "in her eyes. Whispered words cross your mind:\n");
        who->catch_msg("'Many a tiresome kender sings of fishing learned "+
                  "on the docks of Palanthas as they slip past upon "+
                  "the road to the south. You can learn the skill to "+
                  "fish in that hateful city. Heed me well -- you will "+
                  "need a particular creature as bait.'\n\n");
        return;

    case "bait":
        say(QCTNAME(TO) + " stares at " + QTNAME(who) + ".\n", who);
        who->catch_msg("\n" + QCTNAME(TO) + " stares at you with light "+
                      "in her eyes. Whispered words cross your mind:\n");
        who->catch_msg("'I have divined the particular creatures which "+
                  "will entice the robe from the deeps. "+
                  "Seek the larvae of the ooze to the west "+
                  "of the ruins of Xak Tsaroth.'\n\n");
        return;

    case "jetty":
        say(QCTNAME(TO) + " stares at " + QTNAME(who) + ".\n", who);
        who->catch_msg("\n" + QCTNAME(TO) + " stares at you with light "+
                      "in her eyes. Whispered words cross your mind:\n");
        who->catch_msg("'The jetty where the Darkling Sea lies nearby is "+
                  "known among seafarers as Reefcutters Jetty. It is a "+
                  "place of refuge from storm and surge, if not from "+
                  "blades and throats cut. The ship foundered "+
                  "offshore from the jetty in deep water. "+
                  "One such as you should be able to fish up the robe "+
                  "from its broken deck -- with patience and skill.'\n\n");
        return;

    case "task":
    case "quest":
    case "help":
        say(QCTNAME(TO) + " stares at " + QTNAME(who) + ".\n", who);
        who->catch_msg("\n" + QCTNAME(TO) + " stares at you with light "+
                      "in her eyes. Whispered words cross your mind:\n");

        if ( who->test_bit(QUEST_DOMAIN,QUEST_GROUP,QUEST_BIT) )
        {
            who->catch_msg("'I learned a lesson in loyalty from my Queen -- "+
                  "a slow and painful lesson such as you could not imagine. "+
                  "All because of your stupidity when last in my service. "+
                  "Trouble me not again with your help.'\n\n");
        }
        else
        {
            who->catch_msg("'One such as you may have the will and the wit "+
                  "to be of service to me. I require a particular robe -- "+
                  "for to be made-over. It is known by the wise as the "+
                  "Robe of Worms... late of the Darkling Sea. Fetch it "+
                  "in secret for me and I will reward you well. If you "+
                  "have it with you ask me for your reward.'\n\n");
        }

        return;

    case "reward":
        say(QCTNAME(TO) + " stares at " + QTNAME(who) + ".\n", who);
        who->catch_msg("\n" + QCTNAME(TO) + " stares at you with light "+
                      "in her eyes. Whispered words cross your mind:\n");

        if ( who->test_bit(QUEST_DOMAIN,QUEST_GROUP,QUEST_BIT) ) 
        {
            who->catch_msg("'I learned a lesson in loyalty from my Queen -- "+
                  "a slow and painful lesson such as you could not imagine. "+
                  "All because of your stupidity when last in my service. "+
                  "There is no reward owed to you beyond long torment.'\n\n");
        }
        else
        {
            if ( !present( ROBEOFWOVENWORMS, who ) ) 
            {
                who->catch_msg("'You do not have the robe in your "+
                  "possession! What trickery is this?!'\n\n");
            }
            else
            {
                who->catch_msg("'You have the robe! Give it to "+
                                "me at once!'\n\n");
                set_alarm( 2.0, 0.0, &reward_seq0(who) );
            }
        }
        return;

    default:
        return;
    }
}


public string
ask_something( string question )
{
    set_alarm(1.0, 0.0, &do_answer(question, TP));
    return "";
}


/* Function name : Arm me
 * Description : Clones, and wears armours
 * Returns : Null
*/
 
void
arm_me()
{
    setuid();
    seteuid(getuid(TO));
    clone_object(KOBJ + "wrobe")->move(TO);
    clone_object(KOBJ + "wcirclet")->move(TO);
    clone_object(KOBJ + "wshoes")->move(TO);
    command("wear all");
}

public void
do_die(object killer)
{
    command("remove robe");
    ::do_die(killer);
}
