
/*
 * /d/Calia/walkers/potions/anthisto.c
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
    set_potion_name("anthisto");
    set_short("smelly orange potion");
    set_pshort("smelly orange potions");
    set_adj("smelly");
    add_adj("orange");

    /* Set the long description if identified. */
    set_id_long("This smelly potion has a cloudy orange colour.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This smelly potion has a cloudy orange colour.\n");

    /* Set the taste if identified. */
    set_id_taste("The potion has a slimy taste, like some sort of "+
        "sea alga mixed with water.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes like sea water.\n");

    /* Set the smell if identified. */
    set_id_smell("The potion smells of sulphur.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of rotten eggs.\n");

    /* How hard is it to identify? */
    set_id_diff(40);

    /* What is the amount of liquid in mL? */
    set_soft_amount(30);

    /* How much alcohol in the potion? */
    set_alco_amount(0);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(777);

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
    object anthistoeffect;
    if (present("_anthisto_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    anthistoeffect = clone_object(ANTHISTO_POTION_OBJECT);
    anthistoeffect->set_remove_time(ANTHISTO_TIME);
    anthistoeffect->move(this_player());
}

