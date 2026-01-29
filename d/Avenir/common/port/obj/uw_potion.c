 // "Potion"        (/d/Avenir/common/port/obj/potion.c)
 // creator(s):   Glinda june -95
 // last update:
 // purpose:      One of the treasures one might find if one kill the
 //               octopus in the shipwreck.
/*
 * Revisions:
 * 	Lucius, Sep 2017: Re-coded to fix runtime errors.
 */
#pragma strict_types
inherit "/std/potion";

#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <stdproperties.h>

public int no_poison;


public void
create_potion(void)
{
    reset_euid();

    set_short("clear blue potion");
    set_adj("clear");
    add_adj(({ "blue" }));
    set_potion_name("mana potion");
    set_unid_long("This potion seems very old, judging from the vial it is " +
             "contained in. It is pale blue of color. You feel reluctant " +
             "about quaffing it since it must obviously be very old, and " +
             "could have decayed into something dangerous.\n");
    set_id_long("This potion seems very old, judging from the bottle it is " +
             "contained in. It seems to be a mana potion, but you think it " +
             "might have been poisoned by the long time in sea.\n");
    set_id_diff(10);

    set_soft_amount(30);
    set_alco_amount(0);
    set_potion_value(1111);

    set_id_smell("The potions smells fresh, yet slightly bitter.\n");
    set_id_taste("The potion tastes fresh, yet slightly bitter.\n");
    set_unid_smell("The potion smells much like murky water.\n");
    set_unid_taste("The potion tastes like murky water.\n");
    set_effect(HERB_SPECIAL,"hp",400);

    set_magic_res(50);   /* This potion is a little resistive to dispelling */

    add_prop(OBJ_I_WEIGHT, 171);
    add_prop(OBJ_I_VOLUME, 122);
    add_prop(OBJ_S_WIZINFO, "This potion heals a considerable amount of " +
             "mana while at the same time taking a large amount of hp and " +
             "fatigue from the player.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 10, "poison" })); /* This is magical poison */
    add_prop(MAGIC_AM_ID_INFO, ({
        "It looks rather tempting.\n", 10,
        "The potion somehow tickles your mind. You sense something bad about " +
        "it too, though.\n", 30,
        "The potion seems to be a mana healing potion.\n", 50 ,
        "It has been polluted by the long decay time tho.\n", 70}) );
}

public void
special_effect(void)
{
    if (no_poison)
	return;

    object poison = clone_object("/d/Avenir/common/port/obj/uw_poison");
    if (poison)
    {
        poison->move(this_player());
        poison->start_poison();
    }
}

public int
cure_poison(string *cure_type, int success)
{
    if (success > 50)
        no_poison = 1; /* Poison was removed from the potion */

    return no_poison;
}
