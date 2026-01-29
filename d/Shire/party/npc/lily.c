#include <ss_types.h>
#include "../defs.h"
#include HOBBIT_FILE

inherit HOBBITMAKER;

void
create_hobbit()
{
    set_type(MAIDEN);
    set_power(85);
    set_name("lily");
    add_name("_breezy_inn_cook_");
    set_family_name("sandheaver");
    set_title("Cook of the Breezy Field Inn");
    set_adj(({"sandy-haired","round-faced"}));

    add_chat("Enjoy yourself at the party.");
}

void
arm_hobbit()
{
    setuid(); seteuid(getuid());
    clone_object(PARTY_WEP+"cook_spoon")->move(TO);
    command("wield all");
    clone_object(PARTY_ARM+"cook_apron")->move(TO);
    command("wear all");
}

void
introduce_hobbit(string player)
{
    object tp;

    if (tp = present(player,ENV(TO)))
    {
	switch(random(3))
	{
	case 0:
	    command("say Hullo there "+CAP(player)+", have you tried my "+
	      "roast mutton?");
	    break;
	case 1:
	    command("say Greetings "+tp->query_met_name()+", please make yourself "+
	      "at home.");
	    break;
	case 2:
	    command("say Nice to meet you "+CAP(player)+".");
	    break;
	}
    }
}
