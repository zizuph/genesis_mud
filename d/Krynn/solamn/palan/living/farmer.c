/* created by Aridor, 09/10/94 */

#include "../local.h"

inherit CITIZEN;

#include <money.h>

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "lshirt")->move(TO);
    clone_object(OBJ + "pants")->move(TO);
    command("wear all");
    /*clone_object(OBJ + "food1")->move(TO);
      clone_object(OBJ + "food2")->move(TO);*/
    MONEY_MAKE_CC(random(20))->move(TO);
}

void
create_citizen()
{
    set_name("bill");
    add_name("farmer");
    set_race_name("human");
    set_introduce("the farmer");
    set_gender(0);
    set_adj("black-skinned");
    add_adj("over-worked");
    set_long("@@my_long@@He looks like he has had a hard life and has " +
	"to work a lot to make a living.\n");
    set_extra_long("He is on his way to sell goods.\n");
    default_config_npc(random(10) + 90);
    add_prop("_live_m_attack_thief",1);
    set_act_time(10);
    add_act("smile sadly");
    add_act("say Off to the market I go!");
    add_act(({"say I just hope I can sell all my stuff today.",
	      "say With the money I'll go buy some new tools.",
	      "say Well, IF I have enough money left to feed me, that is.",
	      "ponder",
	      "say Ah yes, life goes on...",
	      "say Nothing much I can do about it except make the best of it."}));
    add_act("say Hello there, how goes?");
    set_random_move(80);
    set_restrain_path(TDIR);

}

string
my_long()
{
    string str = query_art_name(TP);
    if (str == query_name())
      return str + " the farmer.\n";
    else
      return "He is " + str + "\n";
}
