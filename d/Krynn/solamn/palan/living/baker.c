/* created by Aridor, 09/06/94 */

#include "../local.h"

inherit CITIZEN;

#include <money.h>

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "apron")->move(TO);
    clone_object(OBJ + "shoes")->move(TO);
    clone_object(OBJ + "cshirt")->move(TO);
    clone_object(OBJ + "leggings")->move(TO);
    command("wear all");
    MONEY_MAKE_SC(random(20))->move(TO);
    MONEY_MAKE_CC(random(20))->move(TO);
}

void
create_citizen()
{
    set_name("fredluf");
    add_name("baker");
    set_race_name("human");
    set_introduce("Figge, Baker");
    set_gender(0);
    set_adj("whitish");
    add_adj("merry");
    set_long("@@my_long");
    set_extra_long("He is covered with flour.\n");
    default_config_npc(random(10) + 40);
    set_act_time(10);
    add_act("smile");
    add_act("say It's been a successful week.");
    add_act("say Oh, well.");
    add_act("chuckle");
    add_act("say Hello there, how goes?");
    add_act("say Fine, thanks.");
    add_act("hmm");
    add_act("say Considering the circumstances, it could be worse.");
    set_random_move(50);
    set_restrain_path(TDIR);
}

string
my_long()
{
    string str = query_art_name(TP);
    if (str == query_name())
      return str + " Figge, Baker.\n";
    else
      return "He is " + str + "\n";
}
