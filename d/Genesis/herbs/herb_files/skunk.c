inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include "defs.h"

int EFFECT, CC;
void
create_herb() 
{
    set_name(({"herb","handful","handful of small purple berries"}));
    set_short("handful of small purple berries");
    set_pshort("handfuls of small purple berries"); 
    set_adj(({"purple", "small"}));
    set_herb_name("skunk berries");
    add_name("berries");
    set_pname(({"handfuls of skunk berries", "herbs"}));
    set_unid_long("A handful of small purple berries.\n"); 
    set_id_long(break_string("Skunk berries, or "+
	"Flatulentia maxima. The small purple berries of "+
	"this plant have medicinal value, but have unfortunate "+
	"side effects in susceptible individuals.\n",70));
    EFFECT = 25;
    CC = (4 * EFFECT) + (EFFECT * EFFECT)/5;

    set_ingest_verb("eat");
    set_find_diff(3);
    set_id_diff(30);
    set_effect(HERB_SPECIAL, "", EFFECT);
    set_herb_value(CC);
    set_decay_time(5000);
}

string
query_recover()
{ 
    return MASTER + ":" + query_herb_recover();
}
void
init_recover(string arg)
{ 
    init_herb_recover(arg); 
}

void
special_effect()
{
    object tp = this_player();
    object to = this_object();
    object poison;

    tp->catch_msg("As you eat the purple berries, "+
      "a terrible bitter taste fills your mouth.\n");
    tp->command("gag");
    setuid();
    seteuid(getuid(to));
    poison = clone_object(SKUNK_POISON);
    poison->move(tp);
}
