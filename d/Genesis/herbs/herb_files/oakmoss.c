inherit "/std/herb";

#include <herb.h>
#include <macros.h>

int CC, EFFECT;

void
create_herb()
{
    set_name(({"lichen", "moss", "herb"}));
    set_adj(({"brown", "oak"}));
    add_name("oakmoss");
    set_herb_name("oakmoss");
    set_pname(({"pieces of lichen", "mosses", "herbs"}));
    set_short("piece of brown lichen");
    set_pshort("pieces of brown lichen");
    add_name(({"pieces", "pieces of brown lichen"}));
    set_unid_long("A piece of brown lichen.\n");
    set_id_long(break_string("A piece of brown lichen that "+
	"grows on the bark of oak trees, commonly known as "+
	"oakmoss. It is used to make perfumes and has "+
	"some small medicinal value.\n",70));
    EFFECT = 35;
    CC = (4 * EFFECT) + (EFFECT * EFFECT) / 5;

    set_id_diff(25);
    set_effect(HERB_HEALING, "mana", EFFECT);
    set_ingest_verb("eat");
    set_herb_value(CC);
    set_find_diff(4);
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
