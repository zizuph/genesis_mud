#pragma strict_types

inherit "/d/Cirath/std/monster.c";
#include "defs.h"


#define RNDRACE ({"human", "human", "elf", "half-elf", "dwarf"})
#define RNDADJ ({"mean", "sarcastic", "growling", "dirty", "menacing"})
#define RNDADJ2 ({"red-eyed","shadowy","slight","hulking","dangerous"})

void
create_monster()
{
    ::create_monster();
     set_adj(RNDADJ2[random(5)]);
    add_adj(RNDADJ[random(5)]);
    set_race_name(RNDRACE[random(5)]);
    set_name("thug");
     set_gender(0);
    set_long("The people in this bar are all fairly interchangeable. "
	+"All of them look wary of your appearance, and none too pleased "
	+"to see you.  Its probably a good idea to leave them alone.\n");
    add_prop (LIVE_I_NEVERKNOWN, 1);

    set_act_time(7);
    add_act("emote eyes you up and down.");
    add_act("emote picks his teeth with a bone.");
    add_act("emote slides his dagger from its sheath.");
    add_act("say You look like a pretty piece of meat.");
    add_act("grin wickedly");
    add_act("say You aren't wanted here, why don't you leave?");
    add_act("say You just steer clear of me and there won't be any trouble.");
    set_cact_time(5);
    add_cact("shout Go for the money!!");
    add_cact("emote lunges at you with a deft maneuver.");
    add_cact("emote tries to sweep your feet from under you.");
    add_cact("say Don't let 'em get away!");
    add_cact("say Now you die.");

    set_alignment(random(0)-400);
    set_assist_cry("Now you die!");
    set_stats(({75, 100, 75, 60, 65, 65}));

    set_skill(SS_WEP_KNIFE,60);
    set_skill(SS_DEFENCE,  50);
    set_skill(SS_PARRY, 50);
}

void
arm_me()
{
    clone_object(TYR_WEP+"bone_dagger")->move(TO);
    clone_object(TYR_ARM+"body_lth")->move(TO);
    make_cash((random(5)+5), "copper");
    command("wield all");
    command("wear all");
}


