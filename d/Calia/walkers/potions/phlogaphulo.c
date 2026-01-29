
/*
 * /d/Calia/walkers/potions/phlogaphulo.c
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
    set_potion_name("phlogaphulo");
    set_short("gritty black potion");
    set_pshort("gritty black potions");
    set_adj("gritty");
    add_adj("black");

    /* Set the long description if identified. */
    set_id_long("This gritty black potion has small purple flecks floating "+
        "in it.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This gritty black potion has small purple flecks floating "+
        "in it.\n");

    /* Set the taste if identified. */
    set_id_taste("The potion has a slimy, gritty and salty taste to it.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes salty and gritty.\n");

    /* Set the smell if identified. */
    set_id_smell("The potion smells salty.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells salty.\n");

    /* How hard is it to identify? */
    set_id_diff(60);

    /* What is the amount of liquid in mL? */
    set_soft_amount(30);

    /* How much alcohol in the potion? */
    set_alco_amount(0);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(1124);

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
    object phlogaphuloeffect;
    if (present("_phlogaphulo_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    phlogaphuloeffect = clone_object(PHLOGAPHULO_POTION_OBJECT);
    phlogaphuloeffect->set_remove_time(PHLOGAPHULO_TIME);
    phlogaphuloeffect->move(this_player());
}

