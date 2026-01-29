
/*
 * /d/Calia/walkers/potions/epikanomai.c
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
    set_potion_name("epikanomai");
    set_short("dark orange potion");
    set_pshort("dark orange potions");
    set_adj("dark");
    add_adj("orange");

    /* Set the long description if identified. */
    set_id_long("This dark orange potion appears to have some sea alga "+
        "floating around in it.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This dark orange potion seems to have some sort of "+
        "slimy mass floating in the bottom of it.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion has the distinct taste of strong alcohol "+
        "mixed with ash and sargassum and some other type of sea alga.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes of strong alcohol and soot with "+
        "some slimy, salty alga in it.\n");

    /* Set the smell if identified. */
    set_id_smell("This potions smells of strong alcohol mixed with ash.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of alcohol and soot.\n");

    /* How hard is it to identify? */
    set_id_diff(70);

    /* What is the amount of liquid in mL? */
    set_soft_amount(70);

    /* How much alcohol in the potion? */
    set_alco_amount(50);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(1400);

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
    object epikanomaieffect;
    if (present("_epikanomai_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    epikanomaieffect = clone_object(EPIKANOMAI_POTION_OBJECT);
    epikanomaieffect->set_remove_time(EPIKANOMAI_TIME);
    epikanomaieffect->move(this_player());
}

