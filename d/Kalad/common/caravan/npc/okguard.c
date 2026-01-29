#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    set_name("andrew");
    add_name("guard");
    add_name("guardsman");
    set_race_name("human");
    set_adj("old");
    add_adj("kabal");
    set_short("old guardsman of Kabal");
    set_pshort("old guardsmen of Kabal");
    set_long("He is a tall, white-haired man whose job it was to insure "+
      "order in the great city of Kabal. Unfortunately, he is now too old "+
      "to do such things and has now been retired.\n");
    set_stats(({75, 60, 60, 100, 100, 60}));
    set_alignment(500);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_WEP_KNIFE, 70);
    set_skill(SS_2H_COMBAT, 70);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_act_time(3);
    add_act("peer all");
    add_act("say What are you doing in my house?");
    set_cact_time(3);
    add_cact("say Fellow guardsmen, come to my aid! Oops, forgot that I live alone now.");
    add_cact("say I'm too old to die like this!");
    add_speak("Do you mind not staying inside my house?\n");
    set_knight_prestige(-5);
    set_title("the Retired Guardsman");
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));

    arm = clone_object(ARM + "gchain");
    arm->move(TO);
    arm = clone_object(ARM + "ghelm");
    arm->move(TO);
    command("wear all");
    wep = clone_object(WEP + "gsword");
    wep->move(TO);
    wep = clone_object(WEP + "gdagger");
    wep->move(TO);
    command("wield all");
    MONEY_MAKE_SC(random(5))->move(TO, 1);
}
