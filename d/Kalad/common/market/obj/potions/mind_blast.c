#include "/d/Kalad/defs.h"
#include <herb.h>
inherit "/std/potion.c";

/*
 * /d/Kalad/common/market/obj/potions/mind_blast.c
 * Purpose    : It adds dex.
 * Located    : 
 * Created By : Sarr 24.Apr.97
 * Modified By: 
 */


void
create_potion()
{
    set_name("potion");
    set_adj(({"fiery","red"}));
    set_short("fiery red potion");

    set_id_long("The liquid in this flask bubbles and foams madly. "+
    "The liquid is a deep, red color, swirled with lighter tones "+
    "of orange, giving it a lava-like look to it. Oddly, it is rather "+
    "cold feeling. It must be the mind-blast potion, used to restore "+
    "mana.\n");
    set_unid_long("The liquid in this flask bubbles and foams madly. "+
    "The liquid is a deep, red color, swirled with lighter tones "+
     "of orange, givint it a lava-like look to it.\n");
    set_unid_smell("It smells like fruits.\n");
    set_id_smell("It smells like fruits.\n");
    set_unid_taste("It tastes sweet and earthy.\n");
    set_id_taste("It tastes sweet and earthy.\n");
    set_potion_name("mind-blast");
    set_potion_value(3000);
    set_id_diff(15);
    set_effect(HERB_HEALING,"mana",50);
}
