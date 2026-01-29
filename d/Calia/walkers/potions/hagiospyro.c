
/*
 * /d/Calia/walkers/potions/hagiospyro.c
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
    set_potion_name("hagiospyro");
    set_short("green-flecked dark grey potion");
    set_pshort("green-flecked dark grey potions");
    set_adj("green-flecked");
    add_adj("dark");
    add_adj("grey");

    /* Set the long description if identified. */
    set_id_long("This dark grey potion has bits of green leaves floating "+
      "in a mixture of strong alcohol and ash.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This dark grey potion has bits of green leaves "+
      "floating in it.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion has a strong alcohol taste mixed with ash, "+
      "some type of green leaf and some type of sea alga.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes of a strong alcohol with "+
      "some type of green leaf.\n");

    /* Set the smell if identified. */
    set_id_smell("This potion smells of a strong alcohol mixed with ash.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of alcohol and soot.\n");

    /* How hard is it to identify? */
    set_id_diff(60);

    /* What is the amount of liquid in mL? */
    set_soft_amount(70);

    /* How much alcohol in the potion? */
    set_alco_amount(50);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(1125);

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
    object hagiospyroeffect;
    if (present("_hagiospyro_potion_object_",this_player()))
    {
	write("You feel no effect.\n");
	return;
    }
    seteuid(getuid());
    hagiospyroeffect = clone_object(HAGIOSPYRO_POTION_OBJECT);
    hagiospyroeffect->set_remove_time(HAGIOSPYRO_TIME);
    hagiospyroeffect->move(this_player());
}

