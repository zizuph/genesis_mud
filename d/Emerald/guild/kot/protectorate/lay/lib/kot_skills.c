#pragma save_binary

#include "../guild.h"

inherit "/d/Emerald/lib/train";

#include <ss_types.h>
#include "/d/Emerald/sys/skills.h"

void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_TRADING, "make deals", 0, 0, 40);
    sk_add_train(SS_AWARENESS, "perceive", 0, 0, 60);
    sk_add_train(SS_LANGUAGE, "speak foreign and archaic languages",
	0, 0, 60);
    sk_add_train(SS_DEFENSE, "dodge attacks", 0, 0, 40);
    sk_add_train(SS_APPR_MON, "appraise enemies", 0, 0, 50);
    sk_add_train(SS_PARRY, "parry attacks", 0, 0, 40);
    sk_add_train(SS_WEP_SWORD, "use a sword", 0, 0, 40);
    sk_add_train(SS_ELEMENT_LIFE, "use and understand life magic", 0, 0, 30);

#ifdef SS_PROT_CLARITY
    sk_add_train(SS_PROT_CLARITY, "attain clarity of mind", "clarity",
        110, 50);
#endif

#ifdef SS_PROT_2H_SWORD
    sk_add_train(SS_PROT_2H_SWORD, "fight with a two-handed sword",
        "two-handed sword", ftoi((itof(SS_SKILL_DESC[SS_WEP_SWORD][1]) * 
        TWOH_SWORD_WEIGHT)), 50);
#endif
}

int sk_no_train(object who)
{
    if (!LAY_PROT_MEMBER(who) && !EMRLD_WIZ(who))
    {
        write("Only layman Protectorate members may train here.\n");
        return 1;
    }

/*
    if (CHECK_PUNISHMENT(BAR, TP->query_real_name()))
    {
    	command("say Sorry " + TP->query_name() + ", but you are " +
	    "considered unworthy to train here.");
    	return 1;
    }
*/

  return 0;
}

void
init_kot_skills()
{
    init_skill_raise();
}
