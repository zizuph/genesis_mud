/* Bur Reed by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"ribbon-like", "linear"}));
    set_herb_name("bur reed");
    set_short("ribbon-like linear leaf");
    set_pshort("ribbon-like linear leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a ribbon-like linear leaf. It was probably " +
        "picked off a juicy herb near or in a pond."));
    set_id_long(BSN("This is the leaf of bur reed, an herb found " +
        "near or in temperate ponds. Bur reed (Sparganium spp.) " +
        "grows to about 70 cm high. The herb has ball-like clusters of " +
        "flowers, the pistillate flowers eventually forming a cluster of " +
        "wedge-shaped nutlets. There are no known uses of this herb."));  
    set_herb_value(12);
    set_id_diff(14);
    set_find_diff(7);
    set_decay_time(6000);
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
