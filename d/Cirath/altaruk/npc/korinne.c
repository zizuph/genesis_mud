inherit "/std/monster";
#include "/d/Cirath/common/defs.h"
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Cirath/common/introfnc.h"

create_monster()
{
    set_name("korinne");
    add_name("bartender");
    add_name("innkeeper");
    set_title("Giantslayer");
    set_race_name("elf");
    set_adj("scarred");
    add_adj("agile");
    set_gender(1);
    set_long("She is the innkeeper and bartender here at the dead kank." +
        " Tribal tattoos cover her bare arms. She looks like she can" +
   	" handle herself in a fight.\n");
    set_alignment(250);
    set_stats(({100,110,100,75,75,100}));
    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,50);
    set_act_time(12);
    add_act("say Drink up guys. Thers more where it came from.");
    add_act("emote mumbles I wish my friend would move out soon. It makes" +
        " me edgy having him here.");
    add_act("say Watch it! If you spill that I'l wipe it with your" +
        " face.");
    add_act("emote grins amusedly.");
    add_act("wistle");
    set_cact_time(6);
    add_cact("say Ahh! You wont live to tell about this Fool!");
    add_cact("say Your shoes untied!");
    add_cact("say So you think you can handle a giantslayer ehh?");
    add_cact("emote grunts as she flings her blades at you.");
    add_ask("friend", "So you want to be my friend ehh? " +
        " Sure your my friend. everyones my friend. hehe.\n");
    add_ask("room", "You want to rent a room? well..ehh.." +
        " let me check. Nope, no empty rooms right now. Maybe" +
        " there will be one soon. Sorry love. But. I hear there" +
        " might be a room if you ask around up at clothier street.\n");
    add_ask(({"favor","help","task"}),"You wanna wash dishes to" +
        " pay your tab ehh? No can do. Either you pay with coins" +
        " or you pay with your blood. Up to you love.\n");

   add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE,1);
 
}
void
arm_me()
{
   clone_object(ALT_WEP + "kblade")->move(this_object());
   clone_object(ALT_WEP + "kblade")->move(this_object());
   command("wield all");
   clone_object(ALT_ARM + "kvest")->move(this_object());
   clone_object(ALT_ARM + "kpants")->move(this_object());
   command("wear all");
   MONEY_MAKE_SC(random(50))->move(this_object(),1);
}

