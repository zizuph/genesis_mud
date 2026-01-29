/*
*
* Even more modified by Vencar for the use in palanthas.
*
* Modified from /d/Krynn/common/potions/quenta.c
* By Arman 16/10/97
 *
 * modified from Olorin's ipotion.c, by Teth Jan 1997
 */
#pragma strict_types

inherit "/std/potion.c";

#include "potion_defs.h"
#include <herb.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_potion()
{
    set_potion_name("ithusak potion");
    add_name("potion");
    set_short("bright tasty potion");
    set_adj("bright");
    add_adj("tasty");
    set_pshort("bright tasty potion");
    /* The potion's true name, used when mixing the potion. */
    set_id_long("A gnomish mixup of whatever was nearby, " +
      "atleast thats how it looks like at first glance, " +
      "giving it a bright and surprisingly tasty smell. " +
      "The ingredients seems to be some weird chemicals, " +
      "shaken hard together until it goes from a purple, " +
      "to a green substance and finally gets a tasty " +
      "bright clear colour. The chemicals are probably " +
      "manufactured on a gnomish device.\n" +
      "This potion will mostly harden the skin of the " +
      "one quaffing it, and sometimes have some weird " +
      "sideeffects.\n");

    /* Set the long description if identified. */
    set_unid_long("A gnomish mixup of whatever was nearby, " +
      "atleast thats how it looks like at first glance, " +
      "giving it a bright and surprisingly tasty smell.\n");
    /* Set the long description if unidentified. */
    set_id_taste("Aaaaahhh this tastes great! " +
      "You think you can taste some chemicals mixed together " +
      "giving a real great taste.\n");
    /* Set the taste if identified. */
    set_unid_taste("Aaaaahhh this tastes great!\n");
    /* Set the taste if unidentified. */
    set_id_smell("This potion smells of some mild alcohol " +
       "mixed together with chemicals.\n");
    /* Set the smell if identified. */
    set_unid_smell("Yep, this potion smells as good as it " +
       "taste.\n");
    /* Set the smell for those who can't identify it. */
    set_id_diff(29);
    /* How hard is it to identify? */
    set_soft_amount(50);
    /* What is the amount of liquid in mL? */
    set_alco_amount(40);
    /* How much alcohol in the potion? Alcohol is needed for */
    /* potions to go ;-)  */
    set_potion_value(STONE_POTION_COST);

    add_prop(OBJ_I_VALUE, STONE_POTION_COST);
    /* approx 50 plats should make it worth it! */

    set_effect(HERB_SPECIAL, "armour", 1);
    /* Set the effect */

    add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This potion has been brewed "+
             "with the use of gnome magic. Quafing it will harden the skin.\n",15}));

}

public void
special_effect()
{
    object ob;

    if(P("_stoneskin_armour",TP) ||
       P("_steelskin_armour",TP))
    {
    write("Ah it tasted good, but apart from that you " +
          "feel no effect.\n");
    return ;
    }
    seteuid(getuid());

    log_file(POTION_EFFECT_LOG, ctime(time()) + " " +
    this_player()->query_name() + " got extra " +
    STONE_POTION_AC + " AC by stone_potion.\n");

    ob = clone_object(STONE_OBJ);
    ob->set_duration(STONE_POTION_TIME);
    if (ob->move(TP))
    ob->move(TP, 1);
    TP->wear_arm(ob);
}
