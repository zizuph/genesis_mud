#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("human");
    add_name("council member");
    set_race_name("human");
    set_adj("council");
    set_short("council member");
    set_long("This man is dressed in fine courtly attire and walks "+
      "around with a slight strut, as if he owns everything in the world. "+
      "He seems to be rather upset about something.\n");
    set_stats(({75, 80, 75, 85, 85, 75}));
    set_alignment(0);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_TRADING, 100);
    set_act_time(6);
    add_act("frown");
    add_act("swear");
    add_act("say We must not let the non-humans into Kabal!");
    add_act(({"scowl elf", "scowl dwarf", "scowl gnome", "scowl hobbit", "scowl goblin", "say Get out of here you scum."}));
    add_act("ponder");
    set_cact_time(3);
    add_cact("say The guards will kill you for this!");
    add_cact("say You filthy peasant!");
    add_speak("Only council members are allowed in here.\n");
    set_knight_prestige(0);
    MONEY_MAKE_SC(random(10))->move(TO, 1);
    set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    object arm;
    seteuid(getuid(TO));
    arm = clone_object(ARM + "tccmrobe");
    arm->move(TO);
    command("wear all");
    command("emote looks rather flustered.");
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("ack");
	command("shout Kill the peasants!");
	command("kill " + OB_NAME(ob));
    }
}
