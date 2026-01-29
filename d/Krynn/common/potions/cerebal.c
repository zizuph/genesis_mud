/*
 * /d/Krynn/common/potions/cerebal.c
 *
 * modified from Olorin's ipotion.c, by Teth Jan 1997
 */
#pragma strict_types

inherit "/std/potion.c";
/* Should always inherit the standard potion */

#include <herb.h>
#include <macros.h>
/* Include /sys/herb.h, as we use some defines from it below. */

#include "/d/Krynn/common/defs.h"
/* Standard include for all Krynn files. */

public void
create_potion()
{
    set_potion_name("cerebal");
    set_short("olive potion");
    set_pshort("olive potions");
    set_adj("olive");
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
    set_soft_amount(50);
    /* What is the amount of liquid in mL? */
    set_alco_amount(25);
    /* How much alcohol in the potion? Alcohol is needed for */
    /* potions to go ;-)  */
    set_potion_value(1286);
    //* 9 gold coins! But the mana effect should be worth it. */

    set_effect(HERB_HEALING, "mana", 90);
    /* Set the effect. HERB_HEALING is defined in /sys/herb.h */
    //* NB: This is high for a potion, but it requires two */
    /*     mana-healing herbs. */
}
