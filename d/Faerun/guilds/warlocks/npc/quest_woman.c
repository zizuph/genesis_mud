/*
 * Quest woman
 * by Finwe, August, 2006
 * Used and slightly modified by Nerull 2018
 */

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";


/*
 * Function name: reward_task()
 * Description  : Determines the reward for various tasks
 */
int
give_remains(string str)
{
    object remains;
    
    if (str == "remains to woman" || str == "bundle to woman")
    {
        if (objectp(remains = present("_quest_infant_remains", 
        this_player())))
        {
            // If the player has done this quest.
            if(this_player()->test_bit(DOMAIN, INFANT_QUEST_GROUP, 
            INFANT_QUEST_BIT))
            {
                write("You give the sad remains to the young "
                +"desperate woman.\n");
                
                command("emote cries: What is this? No..no..no, it "
                +"can't be! I refuse to believe it! It must be "
                +"someone else's poor girl!\n");
                
                command("emote wails desperately!\n");
                
                command("emote throws away the sad remains!\n");
                    
                remains->remove_object();
                
                return 1;
            }
            
            write("You give the sad remains to the young desperate woman.\n");
                
            command("emote cries: What is this? No..no..no, it can't be! I "
            +"refuse to believe it! It must be someone else's poor girl!\n");
                
            command("emote wails desperately!\n");
                
            command("emote throws away the sad remains!\n");
                
            this_player()->catch_msg("\nYou feel little more experienced for "
            +"trying to satisfy the young desperate woman, even if she "
            +"is in complete denial!\n");
            
            remains->remove_object();
            
            this_player()->set_bit(INFANT_QUEST_GROUP, INFANT_QUEST_BIT);
            this_player()->add_exp_quest(INFANT_QUEST_EXP);
            
            QUEST_LOG_FILE(INFANT_QUEST_LNG, INFANT_QUEST_EXP);
            
            return 1;
        }
         
        return 0;
    } 
    
    return 0;
}


void create_monster()
{
    int i;

    seteuid(getuid());
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    npc_name = "_crazed_quest_human";

    add_adj("young");
    add_adj("desperate");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    add_name(npc_name);
    add_name("woman");
    set_short("young desperate woman");
    set_long("This is a " + query_short() + ". Her long, "
    +"black hair is braided into one long braid. Her eyes dart "
    +"around in utter desperation looking for help while crying in "
    +"desperation for something. You get an urgent feeling that "
    +"something dreadful happened to this woman, so maybe you "
    +"should ask her for help?\n");
        
    set_gender(G_FEMALE);
    add_prop(CONT_I_WEIGHT,85000);
    add_prop(CONT_I_HEIGHT,190);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 80 + random(25));
    set_base_stat(5, 80);

    set_alignment(110 + random(50));

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,30);

   /* Actions */
    set_act_time(5);
    set_cact_time(5);
    add_act("cry");
    add_act("wail");
    add_act("sob");
    add_act("emote looks desperately for someone to help her.");
    add_act("emote raises her arms in fustration.");
    add_act("emote yells for help!");

    add_chat("Traveller, can you help me finding my child?");
    add_chat("The hag took my child and ran into the mere!");
    add_chat("Gods! Someone help me finding my child!");
       
    set_cchat_time(5);
    add_cchat("I will fight to the death! Life means nothing no more!");
    add_cchat("I want you to help me, not to kill me!");
    add_cchat("You are worse than the beasts in the mere!");
    add_cchat("I will beat you silly!");
    
    add_ask( ({ "quest", "task", "help" }),
    "say Please help me! An old gruesome hag ambushed me and "
    +"outright stole my child! She laughed and ran into the mere "
    +"west of here!", 1);
    
    add_ask( ({ "child", "baby", "infant", "samara" }),
    "say She is my daugther. Samara is just a few months "
    +"old! Search for a tiny black-haired infant in a small "
    +"blue dress! Hurry up please...I can't be without her!", 1);
    
    add_ask( ({ "hag", "old hag", "witch", "old gruesome hag" }),
    "say She came from the mere, and ambushed me and stole "
    +"Samara! She looked like an old crone in brown smelly "
    +"robes and a covered face. Her arms was like trunks and "
    +"way too strong for me to handle! Please, find my "
    +"child and kill that witch! Hurry please!!", 1);

    add_prop(LIVE_I_NEVERKNOWN, 1);
}


void
init_living()
{
    ::init_living();
    add_action(give_remains, "give");
}
