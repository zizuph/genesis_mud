/* File         : /d/Khalakhor/se_speir/rannoch/npc/ceard.c
 * Creator      : Darragh@Genesis
 * Date         : 00-11-06      
 * Purpose      : Npc in the Loch Rannoch area.
 * Related Files: 
 * Comments     : Based on Gruoch
 * Modifications: 
 */

#pragma strict_type

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"

inherit STDHUMAN;
inherit "/d/Khalakhor/lib/clan_support";
inherit "/d/Khalakhor/lib/weapon_repairs";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";

mapping remembered;
int has_armed;

public int
my_communicate(string str)
{
    string temp;

    if (temp = TO->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	write(stringp(temp) ? temp : "You are gagged and cannot " +
	  "speak.\n");
    }

    tell_room(environment(), QCTNAME(TO) + " " + VBFC_ME("race_sound") +
      ": " + str + "\n");
}
public void
arm_me()
{
    if (has_armed)
        return;

    seteuid(getuid());

    clone_object("/d/Khalakhor/common/arm/vest_hard_leather")->move(TO);
    clone_object("/d/Khalakhor/common/arm/belt")->move(TO);
    clone_object("/d/Khalakhor/common/wep/smiths_hammer")->move(TO);
    command("wield all");
    command("wear all");
    command("lace vest");
    has_armed = 1;
}  
public void
create_khalakhor_human()
{
    set_name("ceard");
    set_living_name("ceard");
    add_name("smith");
    add_name("blacksmith");
    add_name("man");
    set_adj("black-haired");
    add_adj("sweaty");
    cs_set_sept("Beaton");
    cs_set_clan("MacFaolain");
    cs_set_title("Blacksmith of Abhainn Ruith");
    set_long("This large man looks as if he seldom leaves "
           + "his forge, due to his pale complexion and weary "
           + "face.\n"
           + "He has scars on his left arm and forehead.\n"
           + "His hair is short, black, and really greasy.\n"
           + "He has tired brown eyes.\n");

    default_config_npc(60);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 35);
    set_skill(SS_WEP_CLUB, 60);

    set_alignment(300);
    set_exp_factor(50);
    set_act_time(15);
    add_act("ponder");
 
    set_repair_base_cost(10);
    set_repair_incr_cost(2);

    set_size_descs("short", "lean");
    set_alarm(0.5, 0.0, arm_me);

    set_default_answer("I won't discuss that with you.");
    add_ask(({"smith","smithy","forge"}),
              "say All you see here I built with my own hands. As "
            + "you see, I am a master of many crafts. They "
            + "ask about my past, but I will tell very little.",1);
    add_ask(({"past","history"}),
              "say I don't ask about your past, and you'd do well not "
            + "to ask about mine. Use my services here, provided "
            + "you have the money, but bother me not about other "
            + "matters.",1);
    add_ask(({"weapon","weapons","weaponry"}),
              "say If you did not already know about weapons, you would "
            + "not be here, would you?",1);
    add_ask(({"ring"}),
              "say Leave me be.",1);
}
public int
hook_return_intro(string str)
{
    if (!remembered[str])
    {
        command("nod " + str);
        command("say " +capitalize(query_name()) + " "
          + query_title() + ", what can I help you with?");
        remembered[str] = "nice";
        present(str, environment(TO))->add_introduced(query_real_name());
    }
    else if (remembered[str] == "bad")
    {
        command("emote glares at you for a while.");
        command("say I do not want you here, leave.");
    }
    else
    {
        command("smirk");
        command("say I wouldn't forget you that easily, would I," 
          + capitalize(str) + "?");
    }
    return 1;
}
public void
init_living()
{
    ::init_living();
    init_smith_repairs();
}
public void
attacked_by(object who)
{
    ::attacked_by(who);

    respond_to_attack(who);
}    
