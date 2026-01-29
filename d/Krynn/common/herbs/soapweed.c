/* Soapweed by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"stiff", "narrow"}));
    set_herb_name("soapweed");
    set_short("stiff narrow leaf");
    set_pshort("stiff narrow leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("smear");
    set_unid_long(BSN("This is a stiff narrow leaf. It was probably " +
        "picked from a plant on a dry slope on a prairie."));
    set_id_long(BSN("This is a leaf from the plant called soapweed, an " +
        "herb found on temperate sunny slopes on prairies. Soapweed is " +
        "also called yucca (Yucca glauca). It is a coarse plant with " +
        "short woody stems, that has stiff narrow leaves with sharp tips. " +
        "The flowers are a creamy white. It is said that if this herb is " +
        "smeared on the skin, it will neutralize acid."));
    set_herb_value(794);
    set_id_diff(36);
    set_find_diff(9);
    set_effect(HERB_ENHANCING,"acid",35);
    set_decay_time(6100);
    set_dryable();
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
