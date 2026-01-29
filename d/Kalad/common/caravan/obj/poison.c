#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <herb.h>
inherit "/std/potion.c";

/* A poison potion, can be bought in Caravan lot in shop */
/* Sarr 19.Mar.97 */


void
create_potion()
{
    set_name("potion");
    set_adj("white");
    set_short("white potion");

    set_id_long("This potion looks to be made out of spider venom, "+
      "mixed in with other things to disguise its power. It would be "+
      "wise not to drink it.\n");

    set_unid_long("It is a strange, white potion. You wonder what it"+
      " does.\n");

    set_unid_smell("It smells like sugar and spices.\n");
    set_id_smell("It smells like sugar and spices.\n");
    set_unid_taste("It tastes good.\n");
    set_id_taste("It tastes good.\n");
    set_potion_name("poison");
    //set_potion_value(500);
    add_prop(OBJ_I_VALUE, 500);
    set_effect(HERB_POISONING,"spider",60);
}
