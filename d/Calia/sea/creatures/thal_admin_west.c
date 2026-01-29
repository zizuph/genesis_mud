
 /*    An administrator for Thalassia

    coder(s):    Jaacar  July 2003

 */

inherit "/d/Calia/std/sea_creature";
inherit "/std/act/action";
inherit "/std/act/asking";

#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include "defs.h"
#include GLYKDEF
#include MAP_HEADER
#include SEA_QUESTS

public string
ask_help()
{
    object who;
    string name;

    if (TP->test_bit(THAL_W_ADMIN_DOMAIN, THAL_W_ADMIN_GROUP, THAL_W_ADMIN_BIT))
    {
         TP->catch_msg("You have already solved this quest!\n");
         return "";
    }

    who = TP;
    name = lower_case(who->query_real_name());
    command("whisper " + name + " Help? Well you can't help me, "+
        "but I may be able to help you.");
    command("smile");
    TP->add_prop(THAL_W_ADMIN_PROP,1);
    command("whisper " + name + " If you can find the medical "+
        "facilities of the city, come back and ask me for a "+
        "reward.");
    return "";
}

public string
ask_reward()
{
    object who;
    string name;

    if (TP->test_bit(THAL_W_ADMIN_DOMAIN, THAL_W_ADMIN_GROUP, THAL_W_ADMIN_BIT))
    {
         TP->catch_msg("You have already solved this quest!\n");
         return "";
    }

    who = TP;
    name = lower_case(who->query_real_name());

    if (!TP->query_prop(THAL_W_ADMIN_PROP))
    {
        command("whisper "+name+" You want a reward for what?");
        return "";
    }
    if (TP->query_prop(THAL_W_ADMIN_PROP) != 2)
    {
        command("whisper "+name+" You have not completed the task I "+
            "gave you!");
        return "";
    }

    TP->set_bit(THAL_W_ADMIN_GROUP, THAL_W_ADMIN_BIT);
    TP->add_exp(THAL_W_ADMIN_EXP);
    TP->catch_msg("You feel more experienced!\n");
    TP->command("save");
    log_file("thal_admin_west", TP->query_real_name() +
            " " + ctime(time())+".\n");
    command("whisper to "+name+" Congratulations. I am glad "+
          "I could help you out.");
    if (TP->query_scar())
    {
        command("whisper to "+name+" Perhaps you should have "+
            "used the services offered there to get rid of "+
            "those scars.");
        command("wink suggestively");
    }
    TP->remove_prop(THAL_W_ADMIN_PROP); 
    return "";
}

void
create_creature()
{
    object gem;

    set_name("eeeeeek");
    add_name("mermaid");
    set_short("hard-working administrative mermaid");
    set_adj("hard-working");
    add_adj("administrative");
    set_race_name("mermaid");
    add_name("administrator");
    add_name("officer");
    set_long("She is one of the most beautiful creatures you have "+
        "ever laid eyes upon in your life.  She has long "+
        "flowing golden hair and deep sea-green eyes.  She "+
        "is human in appearance above the waist, but has a "+
        "large fish-like tail instead of legs.  Her bare breasts "+
        "are fully exposed as she swims through the water.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_prop(OBJ_M_NO_ATTACK, "You do not dare attack the administrator.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "You do not dare attack the administrator.\n");
    set_alignment(300);
    set_gender(1);
    set_stats(({(random(80)+40),(random(60)+40),(random(60)+40),
        70,70,(random(40)+20)}));

	set_skill(SS_SWIM, 100);
	
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"quest","help"}), VBFC_ME("ask_help"));
    add_ask("reward", VBFC_ME("ask_reward"));
    add_ask("job","say My job? I am an administrator of the city of Thalassia.",1);
    add_ask(({"thalassia","Thalassia","city"}),
        "say Thalassia is my home.",1);
}

public string
default_answer()
{
    command("say I do not know of what you speak.");
    return "";
}


