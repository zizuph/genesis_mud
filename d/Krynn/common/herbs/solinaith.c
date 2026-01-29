/* Solinaith by Teth, Feb.18,96 */
/* Added revelation for OotS - Arman 2017 */
/* Reduced magic resistance benefit from 28 to 4 - Arman 2018 */

#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include "/d/Krynn/guilds/OotS/defs.h"
#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"white", "dusty"}));
    set_herb_name("solinaith");
    set_short("dusty white leaf");
    set_pshort("dusty white leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a dusty white leaf. It was probably " +
        "picked from a plant in a shady forest."));
    set_id_long(BSN("This is a leaf from the plant called solinaith, an " +
        "herb found in temperate shaded forests. Solinaith means the birth " +
        "of Solinari in Silvanesti. The leaf is used by the elves to heal " +
        "simple wounds, and is rumoured to have another effect, but that " +
        "is a well-kept secret. Oddly enough, none can claim to have ever " +
        "seen this herb bloom."));
    set_herb_value(1572);
    set_id_diff(55);
    set_find_diff(9);
    set_effect(HERB_ENHANCING,"magic",4);
    add_effect(HERB_HEALING,"hp",20);
    add_effect(HERB_SPECIAL,"",20);
    set_decay_time(3000);
}

public void
special_effect()
{
    if(IS_OOTS(TP))
    {
          if(!OOTS_QUERY_REV(TP, "solinari"))
          {
            TP->catch_msg("\n\nAs the white leaf touches your tongue you " +
                "feel a divine revelation on the aspect of god of " +
                "magic, Solinari!\n\n\n");
            OOTS_ADD_REV(TP,"solinari","the aspect of solinari");  
          }
    }

}


string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
