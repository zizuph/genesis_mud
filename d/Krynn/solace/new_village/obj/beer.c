/* A Small Beer From The Inn of the Last Home*/

/*
* Last Updated By:
* Leia
* June 05, 2005
*/

inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(4);
    /* Name _beer_for_dirtying is a part of the fountain quest. Do not change. */
    set_name("_beer_for_dirtying");
    add_name("beer");
    set_adj("small");
    set_short("small beer");
    set_pshort("small beers");
    set_long("This is a very small beer indeed! The glass holding it is no bigger than two shots worth. The head of foam is nearly half the glass as well, however, it is promised to be VERY refreshing.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
