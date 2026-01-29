inherit "/std/herb";

#include <herb.h>
#include <macros.h>

int CC, EFFECT;

void
create_herb()
{
    set_name(({"leaf"}));
    add_name(({"herb", "clover"})); 
    set_adj(({"clover","trifoliate","small", "three-leaf" }));
    set_herb_name("three-leaf clover");
    set_pname("three-leaf clovers");
    add_pname("leaves");
    set_short("small trifoliate leaf");
    set_pshort("small trifoliate leaves");
    set_unid_long("A small trifoliate, green leaf, divided in "+
      "three parts.\n");
    set_id_long(break_string("A leaf of the genus Trifolium, "+
	"or clover. It is a favorite among grazing animals, and the "+
	"purple flowers of this plant attract honey bees.\n", 70));
    set_id_diff(10);
    set_find_diff(2);
    EFFECT = 10;
    CC = (4 * EFFECT) + (EFFECT * EFFECT) / 5;

    set_effect(HERB_HEALING, "hp", EFFECT);

    set_ingest_verb("eat");
    set_herb_value(CC);
    set_decay_time(3000);
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
