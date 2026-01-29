/* created by Aridor, 09/10/94 */

#include "../local.h"

inherit CITIZEN;

#include <money.h>

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(POBJ + "lshirt")->move(TO);
    clone_object(POBJ + "pants")->move(TO);
    command("wear all");
    MONEY_MAKE_CC(random(20))->move(TO);
}

void
create_citizen()
{
    set_name("willy");
    add_name("farmer");
    set_race_name("human");
    set_introduce("the farmer");
    set_gender(0);
    set_adj("black-skinned");
    add_adj("sun-burned");
    set_long("@@my_long@@He looks like he has had a hard life and has " +
	"to work a lot to make a living.\n");
    set_extra_long("He is working in the fields.\n");
    default_config_npc(random(10) + 85);
    add_prop("_live_m_attack_thief",1);
    set_act_time(10);
    add_act("smile sadly");
    add_act("say I should be off to the market!");
    add_act(({"say I just hope I can sell all my stuff today.",
	      "say Well, or don't have enough money to feed me, that's what.",
	      "ponder",
	      "say Ah yes, life goes on...",
	      "say Nothing much I can do about it except make the best of it."}));
    add_act("say Hello there, how goes?");

    remove_ask("cutter");
    remove_ask("peat cutter");
    remove_ask("peat");
    remove_ask("inn");
    remove_ask("palace");
    remove_ask("temple");
    remove_ask("post");
    remove_ask("post office");
    add_ask(({"cutter","peat","peat cutter"}),
	    "say The peat cutter? He lives closeby, just a few more steps.",1);
    add_ask("inn","say Yes, a fine inn! It's beyond the post office, I go there often.",1);
    add_ask("palace",
	    "say Hmm, everyone knows it, what a waste of money! It's pretty " +
	    "nice I have to admit, though.",1);
    add_ask("temple","say Yes, there was one in the city, but it's all rubble now.",1);
    add_ask(({"post","post office"}),
	    "say The post office? That's easy. Just turn right as you enter the city.\n",1);

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
