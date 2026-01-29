inherit "/std/herb";

/*
*   coded by Amelia  4/17/97
*  the oils from roots and leaves of monks hood
*  are very poisonous if ingested, but healing
*  when applied externally
*/
#include <herb.h>
#include <macros.h>
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define MONKSHOOD_POISON HERBS+"poisons/monkshood_poison.c"

int CC, EFFECT;

void
create_herb()
{
    set_name(({"root"}));
    add_name(({"monkshood", "friar's cap"}));
    add_pname(({"herbs", "roots", "friar's caps"}));
    add_adj(({"small", "tuberous"}));
    set_herb_name("monkshood");
    add_adj("monkshood");
    set_short("small tuberous root");
    set_pshort("small tuberous roots");
    set_unid_long(break_string("A tuberous root, from a "+
	"plant which has blue-purple, hooded flowers.\n", 70));
    set_id_long(break_string("A tuberous root from the "+
	"monkshood plant, or Aconitum napellus, "+
	"commonly known as friar's cap. "+
	"The leaves and root of this plant are "+
	"extremely poisonous if eaten, but have "+
	"a very healing effect if applied "+
	"externally, such as by rubbing on the skin.\n",70));
    set_id_diff(25);
    EFFECT = 50;
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;

    set_ingest_verb("eat");
    set_herb_value(CC);
    set_find_diff(4);
    set_decay_time(5000);
    set_effect(HERB_SPECIAL, "", EFFECT);
}

int
rub_root(string str)
{
    object tp = this_player();
    object to = this_object();
    int i;
    string herb, dummy;


    if (!str)
	return 0;
    if (i = parse_command(str, environment(to),
	"%w [on] %w", herb, dummy))
    {

	if (id(herb))
	{
	    EFFECT = 50;
	    tp->heal_hp(EFFECT);
	    tp->catch_msg("As you rub the herb against "+
	      "your skin, it stings but you feel the healing "+
	      "effect.\n");
	    to->remove_object();
	    return 1;
	}
	notify_fail("Rub what on where?\n");
	return 0;
    }
    notify_fail("Rub what on where?\n");
    return 0;
}

void
special_effect()
{

    object tp = this_player();
    object to = this_object();
    object poison;

    tp->catch_msg("You eat the root. You realize "+
      "suddenly it was a big mistake!\n");
    seteuid(getuid(to));
    poison = clone_object(MONKSHOOD_POISON);
    poison->move(tp);
    poison->start_poison();
}

void
init()
{
    ::init();
    add_action(&rub_root(), "rub");
}
