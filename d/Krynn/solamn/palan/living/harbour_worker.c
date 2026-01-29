/* created by Aridor, 09/06/94 */

#include "../local.h"

inherit CITIZEN;
inherit "/d/Krynn/std/intro";

#include <money.h>

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "overall")->move(TO);
    MONEY_MAKE_GC(3)->move(TO);
    command("wear all");
}

void
create_citizen()
{
    set_name("wokkn");
    add_name("worker");
    set_race_name("human");
    set_introduce("the harbour worker");
    set_gender(0);
    set_adj("muscular");
    add_adj("tanned");
    set_long("@@my_long");
    set_extra_long("He is dirty and oily.\n");
    default_config_npc(random(10) + 70);
    set_act_time(10);
    add_act("say Here comes the weekend.");
    add_act("say Just picked up my salary.");
    add_act("say You're not looking for a fight are you?");
    add_act("say I'm off to the pub.");
    add_act("say Gotta get rid of them coins again before they get stolen.");

}

string
my_long()
{
    string str = query_art_name(TP);
    if (str == query_name())
      return str + " the harbour worker.\n";
    else
      return "He is " + str + "\n";
}

