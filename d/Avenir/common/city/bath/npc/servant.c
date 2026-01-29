#pragma strict_types
/*
 * ~/servant.c
 *
 * NPC for the bath house
 * Based upon cleaning woman /d/Avenir/common/mon/cleaner.c
 *
 * Revisions:
 *   Lilith, Feb 2002: Created.
 *   Lucius, Jul 2017: Code Cleanups.
 *
 */
inherit "/d/Avenir/inherit/monster";

#include "../bath.h"

#include <stdproperties.h>               /* properties */
#include <macros.h>                      /* macros like VBFC and QNAME */
#include <wa_types.h>                    /* weapon and armour defs */
#include <ss_types.h>                    /* skill and stat defs */

public int alarm_id;
public string *randadj = ({
    "little", "dark-eyed", "tall", "buxom", "greying",
    "slender", "delicate", "voluptuous", "willowy",
    "concerned", "secretive", "smiling", "wide-eyed",
    "innocent", "sweet", "pleasant", "exquisite",
    "gentle", "lovely",
});
public string *randes = ({
    " scrubbing the floor", " mopping up water",
    " sitting on her heels", " on her knees",
});

public string my_long(void);


public void
create_monster(void)
{
    set_long(my_long);
    set_name("servant");
    add_name(({"woman", "slave"}));
    set_race_name("human");
    set_adj(({ one_of_list(randadj), "bathhouse", "female" }));
    set_gender(G_FEMALE);
    set_stats(({60,60,60,40,40,50}));
 
    set_alignment(0);
    set_pick_up(1);
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(20, 11);

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_UNARM_COMBAT, 20);

    add_prop(CONT_I_HEIGHT, 180); 
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_S_EXTRA_SHORT, one_of_list(randes));

    set_act_time(30);
    add_act("emote carefully slops some water onto the floor and "+
         "scrubs it with her brush.");
    add_act("emote wipes her forehead with the back of her hand.");
    add_act("emote blows a wisp of hair from her eyes.");
    add_act("emote watches you with calm disinterest.");
    add_act("emote shifts to a more comfortable position.");
    add_act("emote breathes deeply of the scented air.");
    add_act("emote hums tonelessly to herself.");

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"help","task","job","errand","quest","assignment"}), 
        VBFC_ME("give_job"), 1);
    add_ask(({"instruct", "instructions"}), "say My boss will give me "+
        "instructions when he has something for me to do.", 1);
    add_ask(({"food", "drink", "kahve", "towel", "towels", "soap",
        "soaps","tray", "trays"}), "say The bath attendants can "+
        "supply you with those, or you can get some off the "+
        "shelves in the corridor you passed as you came in.", 1);
}

public string
my_long(void)
{
    string str;

    switch(random(6))
    {
        case 0:
            str = "seems to be waiting for instructions";
            break;
        case 1:
            str = "scrubs with slow, measured movements, as though she "+
                  "is pacing herself";
            break;
        case 2:
            str = "wears a simple white tunic that leaves her arms "+
                  "bare and her legs exposed below the knee";
            break;
        case 3:
            str = "has a small, enigmatic smile on her face";
            break; 
        case 4:
            str = "has a large bottom that sways as she scrubs";
            break;
       case 5:
            str = "has broad shoulders and muscular forearms that ripple "+
                  "under her pale skin";
            break;                 
    }
    return "A "+ query_adj() +" servant of the bathhouse.\n"+
           "She "+ str +".\n"+        
           "She is demure and obedient, a typical "+
           "sybarite servant shrouded in a quiet dignity.\n"+
           "She appears to be well-fed and healthy despite her hard "+
           "labour.\n";
}

public string
what_me(void)
{
    switch(random(7))
    {
        case 0:
            command("say I am not permitted to answer that question.");
            break;
        case 1:
            command("say I scrub floors and clean messes. That is all I know.");
            break;
        case 2:
            command("emote struggles to answer, but does not seem able "+
                "to get the words out.");
            break;
        case 3:
            command("say Would that I could, but I cannot say.");
            break;
        case 4:
            command("emote looks fearfully around.");
            command("say Would you see me punished?");
            break;
        case 5:
            command("say I am not worthy of your attention.");
            break;
        case 6:
            command("emote shrugs and goes back to her work.");
            break;
    }
    return "";    
}

public string
give_job(void)
{
    command("smile " + this_player()->query_real_name());
    command("say You're very kind, but I must do this myself, "+
        "or face the consequences.");
    return "";
}

public void 
return_to_normal(void)
{
    if (query_attack())
    {
        command("say I beg you please, kill me quickly. I've "+
            "not the courage for suffering.");
        return;
    }
    remove_alarm(alarm_id);
    alarm_id = 0;
    add_prop(LIVE_S_EXTRA_SHORT, " on her knees");
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    if (query_prop(LIVE_S_EXTRA_SHORT))
        remove_prop(LIVE_S_EXTRA_SHORT);

    if (!alarm_id)
	alarm_id = set_alarm(20.0, 60.0, return_to_normal);
}

