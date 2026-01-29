#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <herb.h>
inherit "/std/potion.c";

/*
 * /d/Kalad/common/market/obj/potions/acid_potion.c
 * Purpose    : It adds dex.
 * Located    : 
 * Created By : Sarr 24.Apr.97
 * Modified By: 
 */


void
create_potion()
{
    set_name("potion");
    set_adj(({"sulfurous","black"}));
    set_short("black sulfurous potion");
    set_id_long("This is potion is pure black and reeks of sulfur. "+
    "You see odd shapes floating around in the liquid, and it appears "+
    "to be some kind of dragon-scum.\n");
    set_unid_long("It is a strange potion of pure black. It smells "+
    "horrible.\n");
    set_unid_smell("It smells like sulfur.\n");
    set_id_smell("It smells like sulfur.\n");
    set_unid_taste("It tastes very sour and nasty.\n");
    set_id_taste("It tastes very sour and nasty.\n");
    set_potion_name("dragon-scum");
    set_potion_value(3000);
    set_id_diff(22);
    set_effect(HERB_ENHANCING,"acid",10);
}
