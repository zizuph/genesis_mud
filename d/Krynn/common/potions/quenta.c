/*
 * /d/Krynn/common/potions/quenta.c
 *
 * modified from Olorin's ipotion.c, by Teth Jan 1997
 */
#pragma strict_types

inherit "/std/potion.c";

#include <herb.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_potion()
{
    set_potion_name("quenta");
    set_short("clear potion");
    set_adj("clear");
    set_pshort("clear potions");
    /* The potion's true name, used when mixing the potion. */
    set_id_long("Sparkling and effervescent, this clear " +
      "potion looks like enchanted water. The only " +
      "flaw in the crystal perfection of the potion are " +
      "some remnant pieces of a twisted gnarly root.\n");
    /* Set the long description if identified. */
    set_unid_long("Sparkling and effervescent, this clear potion " +
      "looks like enchanted water. The only flaw in the " +
      "crystal perfection of the potion are some remnant " +
      "plant parts.\n");
    /* Set the long description if unidentified. */
    set_id_taste("The potion tastes of brackish water.\n");
    /* Set the taste if identified. */
    set_unid_taste("Despite the colour, the potion tastes of " +
      "poisoned or brackish water!\n");
    /* Set the taste if unidentified. */
    set_id_smell("The potion smells of swamps and dark forests.\n");
    /* Set the smell if identified. */
    set_unid_smell("The potion smells disgusting!\n");
    /* Set the smell for those who can't identify it. */
    set_id_diff(19);
    /* How hard is it to identify? */
    set_soft_amount(50);
    /* What is the amount of liquid in mL? */
    set_alco_amount(0);
    /* How much alcohol in the potion? Alcohol is needed for */
    /* potions to go ;-)  */
    set_potion_value(144);
    /* 1 gold coin, for the value. */

    set_effect(HERB_SPECIAL, "invisibility", 1);
    /* Set the effect */
}

public void
special_effect()
{
    object ob;

    if(TP->query_invis())
    {
        write("Quaffing the potion did nothing for you.\n");
        return ;
    }
    seteuid(getuid());
    ob = clone_object(KRPOTION + "quenta_object");
    ob->set_duration(20 + (random(220)));
    if (ob->move(TP))
        ob->move(TP, 1);
}
