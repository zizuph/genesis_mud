
/*    
 *   The hermit for the mermaid quest
 *
 *   coded by Amelia  1/7/95
 *   Modifications by Maniac 19/8/96 
 *   Added ore giving for Thalassian Staff Quest, Sept 5/03 - Jaacar
 *   Added better hints in no_help and added "quest" to add_ask to be
 *   similar to task / Hyde 27Nov15
 */

inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <composite.h>
#include <formulas.h>
#include <cmdparse.h>
#include "defs.h"

#include SEA_QUESTS

#define LIVE_I_GOT_ORE "_live_i_got_ore"

void
create_monster()
{
    set_name("bum");
    add_adj("beach");
    add_name("hermit");
    set_race_name("human");
    set_short("beach bum");
    set_long("This man has spent much time in "+
        "the sun and salt water. His skin is tanned and "+
        "leathery in appearance, and he is very thin. His hair "+
        "is long and unkempt, and he has a long shaggy beard. "+
        "It appears he has lived away from civilization for "+
        "some time.\n");

    set_act_time(9);
    add_act("emote mumbles to himself.");
    add_act("emote stares longingly out to sea.");
    add_act("emote pauses as if to listen.");
    add_act("stare");
    add_act("scratch");
    add_act("think");
    set_chat_time(10);
    add_chat("Once I was the wealthiest man in Gelan.");
    add_chat("If only she would come back ...");
    add_act("sigh sadly");
    add_chat("What am I going to do with this ore?");
    add_chat("Her eyes are as blue-green as the Calian sea.");
    add_chat("It's a terrible thing, to be eaten alive by " +
              "a monster of the sea!");

    set_stats(({20,25,20,25,20,25}));
    set_skill(SS_DEFENCE, 15); 
    set_skill(SS_PARRY, 15); 
    set_skill(SS_UNARM_COMBAT, 15); 

    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1); 
    add_prop(CONT_I_WEIGHT, 10);

    add_ask(({"help", "task", "for task", "about task", "quest", 
              "about help", "for help", "to help"}), 
              VBFC_ME("no_help"), 1);
    add_ask(({"eaten", "eaten alive", "about monster", "monster", 
              "about monsters",  "monster of the sea", 
              "monsters of the sea"}), 
            VBFC_ME("monster"), 1); 
    add_ask(({"treasure", "wondrous treasure", "sea treasure"}), 
             VBFC_ME("treasure"),1);
    add_ask(({"day", "that day", "worst day"}), VBFC_ME("win_heart"),1);
    add_ask(({"win her heart", "win heart", "heart"}), 
            VBFC_ME("win_heart"),1);
    add_ask(({"her", "she", "mermaid"}), VBFC_ME("her"),1);
    add_ask(({"ore", "silver ore"}), VBFC_ME("ore"),1);
    add_ask(({"chance", "about chance", 
             "lost chance", "lost forever"}), 
             VBFC_ME("lost_chance"),1);
    set_default_answer("The bum whispers to you: " +
                       "I'm not interested in talking about that!\n");
}

string
no_help()
{
   object tp = TP;

   command("whisper to "+tp->query_real_name()+" There is no help " +
                "for me!");
   command("cry "+query_real_name());
   command("whisper to "+tp->query_real_name()+" My chance was " +
           "lost forever.");
   command("whisper to "+tp->query_real_name()+" Maybe someone else " +
           "will win her heart if they can defeat the monster.");
   return "";
}

string
lost_chance()
{
   object tp = TP;

   command("sigh");
   command("emote stands looking sorrowfully at you.");
   command("whisper to "+tp->query_real_name()+" I tried to convince "+
        "her to come live with me in my mansion in Gelan.");
   command("whisper to "+tp->query_real_name()+" I only wanted " +
           "to win her heart.");
   command("whisper to "+tp->query_real_name()+" That day...was " +
                "the worst day of my life!");
   return "";
}

string
her()
{
    object tp = TP;

    command("cry");
    command("whisper to "+tp->query_real_name()+" She sits upon "+
        "a rock not far out to sea.");
    command("whisper to "+tp->query_real_name()+" You will know her "+
        "on sight.  She is the most beautiful creature I have ever "+
        "seen.");
    command("sigh");
    return "";
}

string
ore()
{
    object tp = TP;
    object ore = clone_object(SEA_OBJECTS+"raw_ore");
    ore->move(TO);

    command("cry");
    command("whisper to "+tp->query_real_name()+" She doesn't want "+
        "this ore!");
    command("whisper to "+tp->query_real_name()+" What does she want?");
    command("sigh");
    if (tp->query_prop(LIVE_I_GOT_ORE))
    {
        return "";
    }
    command("whisper to "+tp->query_real_name()+" Here, you take it. I "+
        "don't need it anymore. Maybe you can give it to that alchemist "+
        "or something. Maybe he will appreciate it.");
    command("give ore to "+tp->query_real_name());
    tp->add_prop(LIVE_I_GOT_ORE,1);
    return "";
}

string
treasure()
{
    object tp = this_player();

    command("whisper to "+tp->query_real_name()+" It is the " +
                "rarest treasure in the sea!");
    command("whisper to "+tp->query_real_name()+" A black pearl.");
   
    return "";
}


string
win_heart()
{
   object tp = TP;

    command("whisper to "+tp->query_real_name()+" She refused "+
        "all my gifts of platinum and gold.  Only the rarest treasure "+
        "of the sea is worthy of her.");
    command("whisper to "+tp->query_real_name()+" That day...");
    command("whisper to "+tp->query_real_name()+" I nearly won her...");
    command("whisper to "+tp->query_real_name()+" A wondrous treasure " +
                "of the sea was nearly in my grasp.");
    command("whisper to "+tp->query_real_name()+" But I almost died "+
        "finding it! The monster eats you alive! I failed, and ever " +
        "since then..");
   command("shiver");
   command("sniff");
   return "";
}


string
monster()
{
   object tp = this_player();

   command("scream");
   command("whisper to "+tp->query_real_name()+" It is evil!  "+
        "Beware of the sea!");
   command("whisper to " + tp->query_real_name() + " If you are " +
           "foolhardy enough to search for it, you will " +
           "find it four points west and two points down " +
           "from the southernmost point of the beach."); 
   return "";
}

