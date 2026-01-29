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
    set_name("teldar");
    add_name("first mate");
    add_name("mate");
    set_race_name("human");
    set_adj("clean-shaven");
    add_adj("wrinkled");
    set_short("first mate");
    set_long("This middle-aged man is slim of body and gives you the "+
      "distinct impression that anyone who crosses him, is himself crossed "+
      "back, right across the throat. His shock of dark brown hair has a "+
      "distinct grey streak in it, making him appear older than he actually "+
      "is.\n");
    set_stats(({75,85,75,70,70,80}));
    set_alignment(-200);
    set_skill(SS_WEP_SWORD,70);
    set_skill(SS_WEP_KNIFE,80);
    set_skill(SS_DEFENCE,60);
    set_skill(SS_PARRY,60);
    set_skill(SS_AWARENESS,80);
    set_skill(SS_UNARM_COMBAT,30);
    set_skill(SS_BLIND_COMBAT,50);
    set_skill(SS_2H_COMBAT,60);
    set_act_time(3);
    add_act("grin myst");
    add_act("ponder");
    add_act("emote moves about the room.");
    add_act("emote sneers.");
    set_cact_time(3);
    add_cact("emote shows you no mercy.");
    add_cact("say I'll see your rotting corpse, fool!");
    add_cact("say I'll be rid of you in no time!");
    add_cact("spit");
    add_speak("The Seahawk shall soon sail again...\n");
    set_knight_prestige(400);
    set_title("the First Mate of the Seahawk");
    set_default_answer("The first mate says: What are you speaking of?\n");
    add_ask(({"seahawk"}),"The first mate says: Why its this grand old "+
      "ship you are standing in!\n");
    add_ask(({"quest"}),"The first mate says: Do I look like I am going "+
      "to tell you of quests???\n");
    add_ask(({"task"}),"The first mate says: Go drown yourself!\n");
    add_ask(({"help"}),"The first mate says: Does it look like _I_ want "+
      "your help?\n");
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object wep,arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/port/arm/1stmate_armour");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/port/arm/1stmate_cloak");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/port/arm/1stmate_boots");
    arm -> move(TO);
    command("wear all");
    wep = clone_object("/d/Kalad/common/port/wep/1stmate_sword");
    wep -> move(TO);
    wep = clone_object("/d/Kalad/common/port/wep/1stmate_dagger");
    wep -> move(TO);
    command("wield all");
    command("say How'd you get in here?");
}
