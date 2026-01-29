inherit "/std/herb";

/*
*  coded by Amelia, 5/15/97
*  
*/
#include <herb.h>
#include <macros.h>
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>

int CC, EFFECT;

void
create_herb()
{
    set_name(({"blade of grass", "blade of witch grass", 
	"grass", "herb"}));
    add_name("blade");
    add_adj(({"witch", "purple", "tangled"}));
    set_short("purple blade of grass");
    set_pshort("purple blades of grass");
    set_herb_name("witch grass");
    set_pname(({"blades of witch grass", "blades of grass"}));
    add_pname(({"herbs", "grasses"}));
    set_unid_long("A long blade of purple grass.\n");
    set_id_long(break_string("Purple long-bladed grass, or "+
	"Panicum capilare, commonly known as witch grass. "+
	"There is a superstition that this grass is "+
	"an ingredient in witches' potions.\n", 70));
    set_id_diff(25);
    EFFECT = 20;
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;

    set_herb_value(CC);
    set_find_diff(4);
    set_decay_time(5000);
    set_effect(HERB_POISONING, "herb", EFFECT);
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

