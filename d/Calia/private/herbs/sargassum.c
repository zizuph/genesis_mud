/* Sargassum by Teth, March 2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("alga");
    set_adj(({"red-brown", "delicate"}));
    set_herb_name("sargassum");
    set_short("delicate red-brown alga");
    set_pshort("delicate red-brown algae");
    set_pname(({"algae", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is an delicate red-brown alga. It was probably " +
        "found floating in the ocean."));
    set_id_long(BSN("This is a delicate red-brown alga, an herb found " +
        "floating in the water column of the ocean. Sargassum " +
        "(Sargassum spp.) is famous for the extensive floating mats it " +
        "creates. It has numerous gas-filled bladders which help it to " +
        "float. This alga is eaten by those who have lost their mental " +
        "prowess."));
/*
    set_herb_value(1698);
*/
    set_herb_value(544);
/* We'll boost it again when there are more sea herbs */
    set_id_diff(44);
    set_find_diff(9);
/*
    set_effect(HERB_HEALING,"mana",70);
*/
    set_effect(HERB_HEALING,"mana",30);
    set_decay_time(2000);
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
