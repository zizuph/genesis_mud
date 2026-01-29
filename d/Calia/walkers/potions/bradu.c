
/*
 * /d/Calia/walkers/potions/bradu.c
 *
 * modified from Karath's cerebal.c potion, by Jaacar November 1997
 */

#pragma strict_types

inherit "/std/potion.c";

#include <herb.h>
#include <macros.h>
#include "defs.h"

public void
create_potion()
{
    set_potion_name("bradu");
    set_short("watery green-brown potion");
    set_pshort("watery green-brown potions");
    set_adj("watery");
    add_adj("green-brown");

    /* Set the long description if identified. */
    set_id_long("A watery green-brown potion, this is a mixture of water "+
        "and elkhorn kelp.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This watery green-brown potion appears to have long "+
        "blades of green alga floating in it.\n");

    /* Set the taste if identified. */
    set_id_taste("The potion has the unmistakenable taste of salt "+
        "water.  Judging by the blades of alga you would guess it "+
        "is a mixture of water and elkhorn kelp.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes bitter, like salt water.\n");

    /* Set the smell if identified. */
    set_id_smell("The potion smells of salt water.  Judging by the "+
        "blades of alga you would say it is a mixture of elkhorn kelp "+
        "and water.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of salt water.\n");

    /* How hard is it to identify? */
    set_id_diff(25);

    /* What is the amount of liquid in mL? */
    set_soft_amount(30);

    /* How much alcohol in the potion? */
    set_alco_amount(0);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(700);

    /* Set the effect. */
    set_effect(HERB_SPECIAL, "", 0);
}

string
query_recover()
{
    return MASTER;
}

void
special_effect()
{
    object bradueffect;
    if (present("_bradu_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    bradueffect = clone_object(BRADU_POTION_OBJECT);
    bradueffect->set_remove_time(BRADU_TIME);
    bradueffect->move(this_player());
}

