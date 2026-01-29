#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    set_name("gerhann");
    set_race_name("human");
    set_adj("fierce");
    set_long("This man is carefully looking up at the sky with a fierce "+
      "expression on his face. You notice his eyes slowly scanning the "+
      "surrounding environment, taking in its every detail.\n");
    set_stats(({80, 100, 80, 75, 75, 90}));
    set_alignment(250);
    set_act_time(6);
    add_act("emote slowly scans the horizon.");
    add_act("think how much he loves falcons.");
    add_act("put all coins in backpack");
    set_cact_time(3);
    add_cact("say You animal!");
    set_title("the Falconmaster");
    add_speak("I love falcons, they mean the world to me!\n");
    set_knight_prestige(-3);
    set_skill(SS_WEP_KNIFE, 70);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_ANI_HANDL, 90);
    set_default_answer("The falconmaster says: I know not what you speak of.\n");
    add_ask(({"falcon", "falcons"}), "The falconmaster says: They are my "+
      "sole purpose for living. You see, I train falcons for Lord Entreri.\n");
    add_ask(({"lord entreri", "entreri"}), "The falconmaster says: He is "+
      "the head of the Trading Company.\n");

    equip(({
                ARM + "tcfgloves",
                    OBJ + "backpack",
                    WEP + "tcfknife",
                    }));
    MONEY_MAKE_GC(random(10))->move(TO, 1);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say How dare you attack my falcon!");
	command("kill " + OB_NAME(ob));
    }
}
