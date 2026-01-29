#include <ss_types.h>
#include "../defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"

inherit HOBBITMAKER;

void
create_hobbit()
{
    set_type(SHIRRIFFE);
    set_power(120);
    set_name("lotho");
    set_family_name("took");
    set_title("Shirriffe of West Farthing");
    set_adj(({"proud","unwavering"}));

    disable_all_noise();
    set_chat_time(random(6)+5);
    add_chat("Enjoy yourself at the party.");
    add_chat("Welcome to "+PARTY_MASTER->query_hosts()+"'s party.");
    add_chat("Make sure you behave yourself at "+
      "this party. Bad behavior will not be tolerated.");
    add_chat("I can't wait till the fireworks start. Nothing can beat "+
      "Mr. Gandalf's wonderful work!");
    add_chat("I hope Podo comes and relieves me soon, so I may "+
      "visit the kitchen here.");
}

void
arm_hobbit()
{
    setuid(); seteuid(getuid());
    clone_object(PARTY_WEP+"shir_spear")->move(TO);
    command("wield all");
    clone_object(PARTY_ARM+"shir_hat")->move(TO);
    clone_object(PARTY_ARM+"shir_tunic")->move(TO);
    command("wear all");
}

void
introduce_hobbit(string player)
{
    object tp;

    if (tp = present(player,ENV(TO)))
    {
	command("say Pleased to meet you kind "+tp->query_race_name()+".");
    }
}
