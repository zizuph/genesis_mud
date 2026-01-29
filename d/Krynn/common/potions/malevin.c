/*
 * /d/Krynn/common/potions/cerebal.c
 *
 * modified from Olorin's ipotion.c, by Teth Jan 1997
 */
#pragma strict_types

inherit "/std/potion";

#include <herb.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_potion()
{
    set_potion_name("cerebal");
    /* The potion's true name, used when mixing the potion. */
    set_id_long("Brown and green, this potion is a mixture of " +
        "forest herbs. Parts of mushrooms and ferns can be seen " +
        "inside the potion, chopped finely. This potion would " +
        "undoubtedly be good for your mental faculties.\n");
    /* Set the long description if identified. */
    set_unid_long("Brown and green, this potion is a mixture of " +
        "forest herbs. Parts of plants and fungi can be seen " +
        "within.\n");
    /* Set the long description if unidentified. */
    set_id_taste("The potion tastes of ferns and mushrooms, " +
        "mixed together, resulting in a earthy plant taste.\n");
    /* Set the taste if identified. */
    set_unid_taste("The potion tastes earthy and chlorophyllic.\n");
    /* Set the taste if unidentified. */
    set_id_smell("The potion smells of ferns and chantrelles.\n");
    /* We give them a hint at what needs to be done to mix it here, */
    /* although we could've done it anywhere. Set the smell if */
    /* identified. */
    set_unid_smell("The potion smells of ferns and amanita.\n");
    /* Heh, let's confuse someone who can't identify it. Maybe */
    /* we should make a poison potion with amanita and fiddlehead! */
    /* Set the smell for those who can't identify it. */
    set_id_diff(25);
    /* How hard is it to identify? */
    set_soft_amount(200);
    /* What is the amount of liquid in mL? */
    set_alco_amount(50);
    /* How much alcohol in the potion? Alcohol is needed for */
    /* potions to go ;-)  */
    set_potion_value(1440);
    /* 10 gold coins! But the mana effect should be worth it. */

    set_effect(HERB_POISONING, "potion", 75);
    add_effect(HERB_HEALING, "hp", -2500);
    set_poison_file(KRPOTION + "malevinp");
    /* Set the effect. HERB_HEALING is defined in /sys/herb.h */
    /* NB: This is high for a potion, but it requires three */
    /*     mana-healing herbs. */
}
