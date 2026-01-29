/* created by Aridor, 09/10/94 */

#include "../local.h"

inherit CITIZEN;

#include <money.h>

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "cblouse")->move(TO);
    clone_object(OBJ + "sskirt")->move(TO);
    clone_object(OBJ + "shoes")->move(TO);
    command("wear all");
    MONEY_MAKE_SC(random(5))->move(TO);
}

void
create_citizen()
{
    set_name("marjam");
    add_name("woman");
    set_race_name("human");
    set_introduce("Calimar");
    set_gender(1);
    set_adj("shy");
    add_adj("gentle");
    set_long("@@my_long@@She appears to be out shopping, or perhaps visiting " +
	     "some friends.\n");
    default_config_npc(random(10) + 40);
    add_prop("_live_m_attack_thief","call_guards");
    set_act_time(50);
    add_act("smile shyly");
    set_random_move(60);
    set_restrain_path(TDIR);
}

string
my_long()
{
    string str = query_art_name(TP);
    if (str == query_name())
      return str + ".\n";
    else
      return "She is " + str + ".\n";
}

void
call_guards(object thief, object victim, object what)
{
    command("say Help! Thieves! Robbers!");
    command("panic");
    call_the_guards(thief->query_real_name(),"xxx");
}
