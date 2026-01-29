inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include  "/sys/money.h"
#include <stdproperties.h>
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("smolek");
    add_name("leader");
    set_race_name("human");
    set_adj("press");
    add_adj("gang");
    set_short("press gang leader");
    set_long("A large bear-like man whose features are muddled by the "+
      "long, concealing coat he wears about him. He walks in a deliberate "+
      "cadence of sound, making it seem as if he were several men instead of "+
      "just one.\n");
    set_stats(({80,70,80,50,50,60}));
    set_alignment(-50);
    set_skill(SS_WEP_CLUB,80);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,50);
    set_act_time(6);
    add_act("emote shifts his coat to conceal his features.");
    add_act("grin .");
    set_cact_time(3);
    add_cact("laugh evilly all");
    add_cact("grin crazily");
    add_speak("I rule these streets! So don't get in my way!\n");
    set_random_move(10);
    set_knight_prestige(50);
    set_title("the Crazed");
    set_alarm(1.0,0.0,"arm_me");
    set_default_answer("The press gang leader says: I don't answer stupid "+
      "questions!\n");
    add_ask(({"quest"}),"The press gang leader says: Find out fer yerself!\n");
    add_ask(({"help"}),"The press gang leader says: I don't help losers!\n");
    add_ask(({"task"}),"The press gang leader says: Why don't you commit "+
      "suicide?\n"+
      "The press gang leader laughs sadistically at you.\n");
}
void
arm_me()
{
    object wep,arm;
    seteuid(getuid(this_object()));
    arm = clone_object("/d/Kalad/common/port/arm/pglarm");
    arm -> move(this_object());
    arm = clone_object("/d/Kalad/common/port/arm/earring");
    arm->move(this_object());
    command("wear all");
    wep = clone_object("/d/Kalad/common/port/wep/pglclub");
    wep -> move(this_object());
    command("wield all");
    MONEY_MAKE_GC(random(3))->move(TO,1);
}
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say Prepare to die, " + ob->query_nonmet_name() + ".");
	command("kill " + lower_case(ob->query_real_name()));
    }
}
