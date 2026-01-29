inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <money.h>
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("vurgrom");
    add_name("fat brawling giant of a man");
    add_name("fat brawling man");
    add_name("fat man");
    add_name("brawling man");
    add_name("giant man");
    add_name("man");
    add_name("captain");
    set_race_name("human");
    set_adj("fat");
    set_short("fat brawling giant of a man");
    set_long("This immensely huge man has an enormous bulging waist that "+
      "hangs before him like a pregnant mother's swollen abdomen. Although large "+
      "and a wee bit on the heavy side, the man's rugged face and piercing "+
      "black eyes give you cause for concern.\n");
    set_stats(({90,80,100,75,75,95}));
    set_alignment(-500);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_DEFENCE,75);
    set_skill(SS_PARRY,75);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_BLIND_COMBAT,50);
    set_act_time(3);
    add_act("emote belches so loudly, it feels as if the entire ship is shaking.");
    add_act("say I am Vurgrom, the Mighty!!!");
    add_act("emote attempts to impress you by flexing his muscles, and fails.");
    add_act("emote 's beer belly bounces up and down.");
    add_act("say I am the mightiest ship captain in all of Kalad!");
    add_act("say With the Holy Order behind me, all of Kalad shall feel my wrath.");
    set_cact_time(3);
    add_cact("emote belches angrily!");
    add_cact("say I'll kill you and hang you from my main mast!");
    add_cact("say Noone can defeat me in battle!");
    add_cact("snarl all");
    add_cact("kick all");
    add_speak("I am Vurgrom, the mightiest follower of Thanar!\n");
    set_knight_prestige(500);
    set_title("the Mighty, Captain of the Seahawk");
    set_default_answer("The fat human snorts at you for asking such a "+
      "stupid question.\n");
    add_ask(({"holy order","order","thanar"}),"The fat human says: They "+
      "are the true masters of Kalad! Our forces grow daily and soon we "+
      "shall rise from concealment and sweep away all our foes!\n");
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object wep,arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/port/arm/captain_armour");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/port/arm/captain_boots");
    arm -> move(TO);
    command("wear all");
    wep = clone_object("/d/Kalad/common/port/wep/captain_sword");
    wep -> move(TO);
    command("wield all");
    command("say Hey! Whatter ya doin in my cabin?");
    MONEY_MAKE_GC(random(5))->move(TO,1);
}
