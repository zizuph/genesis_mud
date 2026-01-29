#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    set_name("hahmal");
    add_name("guard captain");
    add_name("captain");
    set_race_name("human");
    set_adj("courageous");
    add_adj("kabal");
    set_short("guard captain of Kabal");
    set_long("This formidable looking man can only be the captain of the "+
      "city guard here in the Caravan District. He looks extremely confident "+
      "with his sword, making you think twice about any aggresive actions "+
      "against him.\n");
    set_stats(({140, 130, 140, 80, 80, 100}));
    set_alignment(500);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS, 60);
    add_speak("I fear the worst for Kabal, raiders frequent the city more and more.\n");
    set_title("the Captain of the Guard");
    set_knight_prestige(-5);
    set_act_time(3);
    add_act("frown");
    add_act("say What are you doing in here?");
    set_cact_time(3);
    add_cact("say Where are those damn guards when I need them?");
    add_cact("say Know that you fight a master swordsman!");
    set_default_answer("The captain says: What are you speaking of?\n");
    add_ask(({"raiders", "raider"}), "The captain says: I believe the "+
      "raiding parties that are attacking are in fact, advance scouts for "+
      "Canthyr's army.\n");
    add_ask(({"canthyr"}), "The captain says: It is a land rumoured to "+
      "lie past the Great Kalad Waste, in the east.\n");
    add_ask(({"army"}), "The captain says: I fear they are planning to "+
      "invade at any moment!\n");
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(this_object()));
    arm = clone_object(ARM + "cplate");
    arm->move(this_object());
    arm = clone_object(ARM + "chelm");
    arm->move(this_object());
    arm = clone_object(ARM + "cshield");
    arm->move(this_object());
    command("wear all");
    wep = clone_object(WEP + "csword");
    wep->move(this_object());
    command("wield all");
    MONEY_MAKE_PC(random(4))->move(TO, 1);
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;

    me = this_object();
    if (random(5))
	return 0;
    hitresult = enemy->hit_me(450 + random(250), W_BLUDGEON, me, -1);
    how = " without effect";
    if (hitresult[0] > 0)
	how == "";
    if (hitresult[0] > 10)
	how = " roughly";
    if (hitresult[0] > 20)
	how = " powerfully";
    if (hitresult[0] > 30)
	how = " smashingly";
    me->catch_msg("You hit your opponent with your large steel shield!\n" +
      capitalize(enemy->query_pronoun()) + " is hit by the large steel shield" +
      how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " hits you with his large steel shield!\n" +
      "You are hit" + how + ".\n");
    tell_watcher(QCTNAME(me) + " shieldslams " + QTNAME(enemy) + "!\n" +
      capitalize(enemy->query_pronoun()) + " is shieldslammed" +
      how + ".\n", enemy);
    if (enemy->query_hp() <= 0)
	enemy->do_die(me);
    return 1;
}
