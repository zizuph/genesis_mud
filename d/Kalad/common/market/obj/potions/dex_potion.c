#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <herb.h>
inherit "/std/potion.c";

/*
 * /d/Kalad/common/market/obj/potions/dex_potion.c
 * Purpose    : It adds dex.
 * Located    : 
 * Created By : Sarr 24.Apr.97
 * Modified By: 
 */


void
create_potion()
{
    set_name("potion");
    set_adj("light-brown");
    set_short("light-brown potion");
    set_id_long("This is a strange ligh-brown potion, that may be "+
    "a dex potion.\n");
    set_unid_long("It is a strange light-brown potion.\n");
    set_unid_smell("It smells like nothing.\n");
    set_id_smell("It smells like nothing.\n");
    set_unid_taste("It tastes like nothing.\n");
    set_id_taste("It tastes like nothing.\n");
    set_potion_name("dex-elixir");
    set_potion_value(3000);
    set_id_diff(20);
    set_effect(HERB_ENHANCING,"dex",10);
}
