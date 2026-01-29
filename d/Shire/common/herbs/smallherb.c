inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <ss_types.h>

create_herb()
{
    set_name("flower");
    set_short("beutiful white flower");
    set_pshort("beautiful white flowers");
    set_adj(({"beautiful", "white"}));
    set_herb_name("tar-tanak");
    set_id_long("This beautiful white flower tar-tanak, and is " +
        "special in many ways. It grows on the graves of dead " +
        "lovers, and some say inhaling its fragrance heals their soul.\n");
    set_unid_long("This is a beautiful white flower.\n");
    set_ingest_verb("inhale");
    set_id_diff(12);
    set_find_diff(1);
    set_effect(HERB_SPECIAL);
    set_decay_time(4000);
    set_herb_value(3130);
    add_prop("_effect_ai_element", ({ SS_ELEMENT_LIFE, 10 }));
}

string
query_recover()
{ 
    return MASTER+":"+query_herb_recover(); 
}

void
init_recover(string arg)
{ 
    init_herb_recover(arg); 
}

