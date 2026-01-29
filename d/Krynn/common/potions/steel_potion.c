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
    set_potion_name("sikhan potion");
    add_name("potion");
    set_short("yellow acidic potion");
    set_adj("yellow");
    add_adj("acidic");
    set_pshort("yellow acidic potion");
    /* The potion's true name, used when mixing the potion. */
    set_id_long("A stinking yellow potion, created from " +
      "some ingredients mingled together by gnomes. " +
      "It is certain that the ingredients aren't natural, " +
      "nothing in the realm would be able to make such an " +
      "unnatural yellow color. The effect of the potion is " +
      "quite hard to figure, but it must be beneficial in " +
      "some ways that only a gnome would have thought up.\n");

    /* Set the long description if identified. */
    set_unid_long("A stinking yellow potion, created from " +
      "some ingredients mingled together by gnomes.\n");
    /* Set the long description if unidentified. */
    set_id_taste("Aaargh the acid burns your tongue! " +
      "You think you can taste some chemicals mixed together " +
      "in a mild alcohol.\n");
    /* Set the taste if identified. */
    set_unid_taste("Aaargh the acid burns your tongue! \n");
    /* Set the taste if unidentified. */
    set_id_smell("This potion smells of some mild alcohol " +
       "mixed together with chemicals.\n");
    /* Set the smell if identified. */
    set_unid_smell("The yellow liquid reeks of acid.\n");
    /* Set the smell for those who can't identify it. */
    set_id_diff(39);
    /* How hard is it to identify? */
    set_soft_amount(80);
    /* What is the amount of liquid in mL? */
    set_alco_amount(70);
    /* How much alcohol in the potion? Alcohol is needed for */
    /* potions to go ;-)  */
    set_potion_value(STEEL_POTION_COST);
    add_prop(OBJ_I_VALUE, STEEL_POTION_COST);
    /* approx 90 plats should make it worth it! */

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
    write("You feel no effect other than the acid burning " +
          "your tongue.\n");
    return ;
    }
    seteuid(getuid());

    log_file(POTION_EFFECT_LOG, ctime(time()) + " " +
    this_player()->query_name() + " got extra " +
    STEEL_POTION_AC + " AC by steel_potion.\n");

    ob = clone_object(STEEL_OBJ);
    ob->set_duration(STEEL_POTION_TIME);
    if (ob->move(TP))
    ob->move(TP, 1);
    TP->wear_arm(ob);
}
