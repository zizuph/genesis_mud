/* aurak.c
 *
 * 15.03.2003: Modified by Blizzard for quest purposes.
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>
#include "../local.h"

inherit "/d/Krynn/std/aurak";

// Quest props.
#define ELF_CAMP_QUEST            "_elf_camp_quest"
#define SARIST_KILLED             "_sarist_killed"
#define QUALTHAS_KILLED           "_qualthas_killed"
#define SPOKEN_WITH_DWARF         "_spoken_with_dwarf"
#define ELF_QUESTIONED            "_elf_questioned"
#define I_RELEASED_ELF            "_i_released_elf"
#define CAMP_VISITED              "_camp_visited"
#define CELL_ROOM                 "/d/Krynn/pax/tharkas/ground_level/cell"

public string ask_help();
public string ask_deorl();
public string ask_sarist();
public string ask_qualthas();
public string ask_reward();
public string ask_camp();
public void   do_answer(string what, object who);
int           report_me(string str);
void          reward_me(object who);

int           speech = 0;

create_aurak()
{
    set_color("red");
    
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({ "help", "quest", "task", "job" }), VBFC_ME("ask_help"), 1);
    add_ask(({ "elves", "camp", "location", "elf" }), VBFC_ME("ask_camp"), 1);
    add_ask(({ "deorl", "Deorl", "about deorl", "about Deorl" }),
        VBFC_ME("ask_deorl"), 1);
    add_ask(({ "sarist", "Sarist", "about Sarist", "about sarist" }),
        VBFC_ME("ask_sarist"), 1);
    add_ask(({ "qualthas", "Qualthas", "about qualthas", "about Qualthas" }),
        VBFC_ME("ask_qualthas"), 1);
    add_ask(({ "reward", "about reward" }), VBFC_ME("ask_reward"), 1);
        
}

public string
default_answer()
{
    if ( random(2) )
    {
        command("say What? Speak up or leave!");
    }
    else
    {    
        command("say What do you want?!");
        command("peer");
    }

    return "";
}

public void
init_living()
{
    ADD(report_me, "report");
    ADD(report_me, "speak");
    ::init_living();
}

int
report_me(string str)
{
    object who = TP;
    
    if ( !strlen(str) || !parse_command(str, ({ }),
        "'to' / 'with' [the] [evilfaced] 'aurak' / 'draconian'") )
    {
        notify_fail("What are you trying to do? Report to the aurak?\n", 0);
        return 0;
    }
    
    who->catch_msg("You speak with " + QTNAME(TO) + " for a while.\n");
    say(QCTNAME(who) + " speaks with " + QTNAME(TO) + " for a while" +
        ".\n", who);

    if ( who->query_prop(I_RELEASED_ELF) || 
        who->query_prop(ELF_QUESTIONED) || who->query_prop(CAMP_VISITED) )
    {
        set_alarm(3.0, 0.0, &do_answer("camp", who));
        return 1;
    }

  // Player has nothing interesting for us to report        
    command("say What?! Get lost!");
    return 1;

}

/* Function name  : ask_help
 * Description    : asnwer to question about help
 */
public string
ask_help()
{
    set_alarm(1.0, 0.0, &do_answer("help", TP));
    return "";
}

/* Function name  : ask_camp
 * Description    : asnwer to question about camp
 */
public string
ask_camp()
{
    set_alarm(1.0, 0.0, &do_answer("camp", TP));
    return "";
}

/* Function name  : ask_reward
 * Description    : asnwer to question about reward
 */
public string
ask_reward()
{
    set_alarm(1.0, 0.0, &do_answer("reward", TP));
    return "";
}

/* Function name  : ask_sarist
 * Description    : asnwer to question about sarist
 */
public string
ask_sarist()
{
    set_alarm(1.0, 0.0, &do_answer("sarist", TP));
    return "";
}

/* Function name  : ask_qualthas
 * Description    : asnwer to question about qualthas
 */
public string
ask_qualthas()
{
    set_alarm(1.0, 0.0, &do_answer("qualthas", TP));
    return "";
}

/* Function name  : ask_deorl
 * Description    : asnwer to question about deorl
 */
public string
ask_deorl()
{
    set_alarm(1.0, 0.0, &do_answer("deorl", TP));
    return "";
}

/* Function name   : do_answer
 * Description     : answers to the questions
 * Arguments       : string what  - topic
 *                   object who   - the player who asked
 */
public void
do_answer(string what, object who)
{
    object out_room = E(TO);
    
    if ( !objectp(who) || E(who) != E(TO))
    {
        speech = 0;
        return;   /* We wont speak if the player is gone */
    }
    
    switch (what)
    {
    case "help":
        command("say What? You wanna help?");
 // Load the cell room.
        if ( !(E(TO))->query_cell_loaded() )
        {  
            (E(TO))->set_cell_loaded();
        }
 // Check if Sarist in the cell.
        if ( !(find_object(CELL_ROOM)->query_prisoner()) )
        {
            command("say Get lost then!");
            command("emote laughs.");
            return;
        } 
 // Player is evil enough to belive he is able to do this task      
        if ( (who->query_alignment() < 0) &&
            !(who->query_prop(ELF_CAMP_QUEST)) )
        {   
            command("laugh");
            set_alarm(3.0, 0.0, &do_answer("help1", who));
        }
 // We will not trust non-evil players 
        else if ( who->query_alignment() > 0 )
        {
            command("laugh");
            set_alarm(3.0, 0.0, &do_answer("help0", who));
        }
    break;
    case "help0":
        command("emote stops laughing.");
        command("say Who even let you in? Get lost!");
    break;
    case "help1":
        say(QCTNAME(TO) + " stops laughing and peers at " + QTNAME(who) +
            " slowly.\n", who);
        who->catch_msg(QCTNAME(TO) + " stops laughing and peers at you " +
            "slowly.\n");
        say(QCTNAME(TO) + " says to " + QTNAME(who) + ": Maybe... " +
            "Maybe I could use you, indeed.\n", who);
        who->catch_msg(QCTNAME(TO) + " says to you: Maybe... " +
            "Maybe I could use you, indeed.\n");
        set_alarm(4.0, 0.0, &do_answer("help2", who));
    break;
    case "help2":
        who->catch_msg(QCTNAME(TO) + " says to you: You see, we " +
            "captured an elf two days ago and now he is rotting in " +
            "the cell.\n"); 
        say(QCTNAME(TO) + " speaks with " + QTNAME(who) + " for a " +
            "moment.\n", who);
        command("emote points at the wooden door.");
            
        set_alarm(4.0, 0.0, &do_answer("help3", who));
    break;
    case "help3":
        who->catch_msg(QCTNAME(TO) + " hisses to you: You probably " +
            "wonder why we haven't jusst killed him? Ha! I could do " +
            "it in many wayss, quickly... or sslowly.\n");
        command("grin evil");
            
        set_alarm(3.0, 0.0, &do_answer("help4", who));
    break;
    case "help4":
        who->catch_msg(QCTNAME(TO) + " continues: This " +
            "would be too easy... and he is possessing informations " +
            "we could us. But.. those elvess have so strong " +
            "hatred towards uss ..and this one is not willing to " +
            "cooperate.\n");
        who->catch_msg(QCTNAME(TO) + " smirks.\n");
           
        set_alarm(4.0, 0.0, &do_answer("help5", who));
    break;
    case "help5":
        who->catch_msg(QCTNAME(TO) + " hisses: Ssstupid elf!\n");

        set_alarm(2.0, 0.0, &do_answer("help6", who));
    break;
    case "help6":
        who->catch_msg(QCTNAME(TO) + " says to you: Anyway... you " +
            "wanna help, right? Then go there and make him speak! " +
            "We have to know the location of their camp!\n");
        say(QCTNAME(TO) + " hisses something to " + QTNAME(who) + ".\n", who);
         
        set_alarm(4.0, 0.0, &do_answer("help7", who));
    break;
    case "help7":
        who->catch_msg(QCTNAME(TO) + " calms down and says: I do not " +
            "care how you do it, but it would be better if he stays " +
            "alive for now. Lord Verminaard might want to present " +
            "that elf to the dragon.\n");
         
           set_alarm(3.0, 0.0, &do_answer("help8", who));
    break;
    case "help8":
        who->catch_msg(QCTNAME(TO) + " says: And his pet prefers " +
            "the fresh meat.\n");
        say(QCTNAME(TO) + " says something to " + QTNAME(who) + ".\n", who);
        command("cackle");
        
        set_alarm(3.0, 0.0, &do_answer("help9", who));
    break;
    case "help9":
        command("say Go then! And report to me when you are done!");
        who->add_prop(ELF_CAMP_QUEST, 1);
    break;
    case "deorl":
  // Player questioned the prisoner 
        if ( who->query_prop(ELF_QUESTIONED) )
        {
            command("say Ahh, probably he is the one that fled into the " +
                "forest. But he got poisoned and I belive he died. ");
        }
  // Player has not questioned the prisoner
        else
        {
            command("say What are you talking about? Get lost!");
        }
    break;
    case "sarist":
        if ( who->query_prop(ELF_QUESTIONED) )
        {
            command("say Sarist is his name? I have no use of this!");
            command("say What about the camp?");
        }
  // Other cases v
        else
            command("say What? Who is that?"); 
    break;        
    case "camp":
        if ( who->query_prop(ELF_CAMP_QUEST) && 
            who->query_prop(I_RELEASED_ELF) && 
            !(who->query_prop(CAMP_VISITED)) )
        {
            command("say You set the prisoner free! I should use you " +
                "as replacement for him! But I will give you one more " +
                "chance!");
            command("fume");
            
            set_alarm(3.0, 0.0, &do_answer("help__3", TP));
        }
  // After interrogating the prisoner
        if ( who->query_prop(ELF_QUESTIONED) && 
            !(who->query_prop(I_RELEASED_ELF)) && 
            !(who->query_prop(CAMP_VISITED)) )
        {
            command("say Stupid elf! He thinks he can put us off with such " +
                "informations!?");
            command("emote fumes.");
            set_alarm(3.0, 0.0, &do_answer("help__1", TP));
        }
 // The player found the camp and killed at least one elf
        else if ( who->query_prop(CAMP_VISITED) )
        {   
            if ( speech == 0 )
            {
                who->catch_msg(QCTNAME(TO) + " scowls at you.\n");
                say(QCTNAME(TO) + " scowls at " + QTNAME(who) + ".\n");
                command("say You found the camp then?");
                speech = 1;
                set_alarm(2.0, 0.0, &do_answer("final_speech", who));
            }
            else
                return;
        }
 // Other cases
        else
            command("say The elves are attacking our troops lately. They " +
                "must have a camp set somewhere close to the edge of " +
                "the forest!");
    break;
    case "help__1":
        if ( !who->query_prop(SARIST_KILLED) )
            command("say He will regret that!");
        
        set_alarm(1.0, 0.0, &do_answer("help__2", who));
    break;
    case "help__2":
        say(QCTNAME(TO) + " says something to " + QTNAME(who) + ".\n", who);

        who->catch_msg(QCTNAME(TO) + " peers at you and says: As about you. " +
            "You could do better.. but I give you a chance to fix that.\n"); 
        set_alarm(2.0, 0.0, &do_answer("help__3", who));
    break;
    case "help__3":
        who->catch_msg(QCTNAME(TO) + " says to you: I want you to find that " +
            "camp. I want to see your weapon stained by elven blood.\n");
        TO->command("close door");
        set_alarm(2.0, 0.0, &do_answer("help__4", who));
    break;
    case "help__4":
        command("say Come back when you are done and maybe I will reward " +
            "you!");
        command("grin");
    break;
    case "qualthas":
        if ( who->query_prop(ELF_QUESTIONED) )
        {
            command("say Qualthas? So he is their leader? Hmmm.");
            who->catch_msg(QCTNAME(TO) + " says to you: I bet his death " +
                "would weaken those elves...\n");
        }
        else
            command("say Qualthas you say? Who is that?"); 
    break;    
    case "final_speech":
        who->catch_msg(QCTNAME(TO) + " hisses to you: I feel a smell of " +
            "elven blood from you. Good. It seems you are not lieing " +
            "to me.\n");
        say(QCTNAME(TO) + " speaks with " + QTNAME(who) + " for a moment " +
            ".\n", who);
        set_alarm(3.0, 0.0, &do_answer("speech1", who));
    break;
    case "speech1":
        who->catch_msg(QCTNAME(TO) + " says to you: Now, when we know " +
            "where the camp is, we may prepare an attack.\n");
        command("emote goes hmm.");

        set_alarm(2.0, 0.0, &do_answer("speech2", who));
    break;
    case "speech2":        
 // The player is not told about the path leading to Qualinost, because
 // the prisoner was killed and aurak could not interrogate him 
        if (who->query_prop(SARIST_KILLED) || who->query_prop(I_RELEASED_ELF))
        {
            who->catch_msg(QCTNAME(TO) + " says: It's a pity the prisoner " +
                "had not survived the confrontation with you. We did not " +
                "have a chance to chat with him again.\n");
            command("say By revealing the location of that camp you " +
                "did better than before and our Queen shall reward you.");
        }
        else
 // Tell the player about the path leading to Qualinost       
        {
            who->catch_msg(QCTNAME(TO) + " says: I had a chat with the " +
                "prisoner while you were out. There is a path leading " +
                "to Qualinost south of their camp. Maybe you would like " +
                "to use it some day.\n");
            command("say By revealing the location of that camp you did " +
                "us a good turn. Our Queen shall reward you for that.");
        }
        speech == 0;
        TO->command("close door"); 
        set_alarm(2.0, 0.0, &reward_me(who));
        
    break;
    case "reward":
        if ( who->query_prop(ELF_QUESTIONED) || who->query_prop(CAMP_VISITED) )
            set_alarm(1.0, 0.0, &do_answer("camp", who));
        else
            command("say Get lost!");
    break;
    default:
        command("say What are you talking about?!");
    break;
    
    }
    
}

/* 
 *  XP calculation function 
 */ 
void
calculate_experience(object who)
{
    int xp_base = 19000;

    if (who->test_bit("krynn", 1, 19))
    {
        who->catch_msg("There is no experience second time you " +
            "solve this quest.\n");
        return;
    }

    xp_base -= (who->query_prop(SARIST_KILLED)     ? 2000 : 0);
    xp_base -= (who->query_prop(I_RELEASED_ELF)    ? 2000 : 0);
    xp_base -= (who->query_prop(ELF_QUESTIONED)    ? 0 : 2000);
    xp_base -= (who->query_prop(SPOKEN_WITH_DWARF) ? 0 : 2000);

    who->catch_msg("You feel more experienced.\n");
    tell_room(E(who), QCTNAME(who) + " looks more experienced.\n", who);

    who->add_exp_quest(xp_base);                         
 // set bit 
    who->set_bit(1, 19);

    K_QUEST_LOG("quest", "Lost scouts - evil", who, xp_base);
}


void
remove_quest_props(object who)
{
    if (who->query_prop(ELF_CAMP_QUEST))
        who->remove_prop(ELF_CAMP_QUEST);

    if (who->query_prop(SPOKEN_WITH_DWARF))
        who->remove_PROP(SPOKEN_WITH_DWARF);
        
    if (who->query_prop(SARIST_KILLED))
        who->remove_prop(SARIST_KILLED);

    if (who->query_prop(QUALTHAS_KILLED))
        who->remove_prop(QUALTHAS_KILLED);

    if (who->query_prop(CAMP_VISITED))
        who->remove_prop(CAMP_VISITED);

    if (who->query_prop(ELF_QUESTIONED))
        who->remove_prop(ELF_QUESTIONED);

    if (who->query_prop(I_RELEASED_ELF))
        who->remove_prop(I_RELEASED_ELF);

}


void
reward_me(object who)
{
    calculate_experience(who);
    remove_quest_props(who);

}

