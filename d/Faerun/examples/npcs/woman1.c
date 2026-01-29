/*
 * Halfling Wife
 * by Finwe, December 2015
 */

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";


// needed for a default answer when player asks something the npc
// doesn't understand or has an answer for.
public string default_answer();

void pause(int num);
void pause_stop();

void create_monster()
{
    int i;

    seteuid(getuid());
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    add_adj("middle-aged");
    add_adj("cheerful");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    add_name(npc_name);
    add_name("woman");
    set_short("middle-aged cheerful female woman");
    set_long("This is a " + query_short() + ". She face is freckled and her " +
        "brown hair curly. She is round and plump looking with a happy smile.\n");

    set_gender(G_FEMALE);
    add_prop(CONT_I_WEIGHT,85000);
    add_prop(CONT_I_HEIGHT,190);
    add_prop(NPC_I_NO_LOOKS, 900); /*sets visual looks */

    default_config_npc(30 + random(10));
    set_base_stat(SS_DEX, (40 + random(25)));

    set_alignment(110 + random(50));

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_2H_COMBAT, 50);

   /* Actions */
    set_act_time(5);
    set_cact_time(5);

    add_act("emote smiles happily.");
    add_act("emote sighs deeply.");
    add_act("emote scratches her nose.");

    add_chat("You can ask me about the weather or faerun.");
    
    set_cchat_time(5);
    add_cchat("What are you fighting me for?");
    add_cchat("You will die for this crime!");
    add_cchat("Take that, and that, and that!");
    add_cchat("I can't believe you are doing this!");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_pick_up_team(({npc_name}));

    add_ask("weather", "The weather is quite nice here.\n");
    add_ask("faerun", "Faerun is the best domain ever!!!\n");
// the default answer
    set_default_answer(VBFC_ME("default_answer"));

// You can also do it this way
//    set_default_answer("I don't know what you're talking about.\n");

}

void
init_living()
{
    ::init_living();
}


/*
 * Function name:	default_answer
 * Description	:	answer to questions we don't understand
 * Returns	:	"" (answer is written before return)
 */
public string
default_answer()
{
    command("say I don't know what you are talking about!");
    pause(10);
    command("say You really should think your questions out before asking them.");
    return "";
}

void 
pause(int delay)
{
    if(delay == 0)
    {
        delay = 3;
    }
write("\n\ndelay: " + delay + "\n\n\n");
    set_alarm(itof(delay),0.0,&pause_stop());
}

void 
pause_stop()
{
    return;
}
