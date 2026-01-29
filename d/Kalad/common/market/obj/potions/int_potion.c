#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <herb.h>
inherit "/std/potion.c";

/*
 * /d/Kalad/common/market/obj/potions/int_potion.c
 * Purpose    : It adds int.
 * Located    : 
 * Created By : Sarr 24.Apr.97
 * Modified By: 
 */


void
create_potion()
{
    set_name("potion");
    set_adj("clear");
    set_short("clear potion");
    set_id_long("This flask is filled with clear liquid, probably "+
    "a mind-lore potion.\n");
    set_unid_long("This flask is filled with clear liquid.\n");
    set_unid_smell("It smells like nothing.\n");
    set_id_smell("It smells like nothing.\n");
    set_unid_taste("It tastes like nothing.\n");
    set_id_taste("It tastes like nothing.\n");
    set_potion_name("mind-lore");
    set_potion_value(3100);
    set_id_diff(20);
    set_effect(HERB_ENHANCING,"int",16);
}
