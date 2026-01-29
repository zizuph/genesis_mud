/* Navarre July 3rd 2006, Fixed typo, ammount -> amount */



/*
* Modified from /d/Krynn/common/potions/quenta.c
* By Arman 16/10/97
 *
 * modified from Olorin's ipotion.c, by Teth Jan 1997
 */
#pragma strict_types

inherit "/std/potion.c";
/* Should always inherit the standard potion */

#include <herb.h>
/* Include /sys/herb.h, as we use some defines from it below. */

#include <macros.h>
/* needed to do the query_recover() */

#include "/d/Ansalon/common/defs.h"
/* Standard include for all Krynn files. */

public void
create_potion()
{
    set_potion_name("dethek brew");
    add_name("liquid");
    set_short("foul-smelling liquid");
    set_adj("foul-smelling");
    add_adj("foul");
    add_adj("smelling");
    set_pshort("foul-smelling liquids");
    /* The potion's true name, used when mixing the potion. */
    set_id_long("A dwarven concoction, the strength " +
      "of this brews foul smell makes you wonder why anyone, " +
      "including dwarves, would willingly want to drink " +
      "this liquid that would probably put a black dragon's " +
      "acid breath to shame. From the looks of it, this brew " +
      "contains a decent amount of dwarven spirits, as well as " +
      "some sort of root that is probably the cause of this " +
      "awful smell coming from this brew. Regardless of its " +
      "undesirable properties, you would say that " +
      "this potion was designed to help resist poisons.\n");
    /* Set the long description if identified. */
    set_unid_long("A dwarven concoction, the strength of " +
      "this brews foul smell makes you wonder why anyone, " +
      "including dwarves, would willingly want to drink " +
      "this liquid that would probably put a black dragon's " +
      "acid breath to shame.\n");
    /* Set the long description if unidentified. */
    set_id_taste("Eeeeyerk! This potion tastes as bad " +
      "as it smells.You think you can taste a woody-root " +
      "mixed in with a lot of dwarven spirits.\n");
    /* Set the taste if identified. */
    set_unid_taste("Eeeeyerk! This potion tastes as bad " +
      "as it smells!\n");
    /* Set the taste if unidentified. */
    set_id_smell("This brew smells strongly of dwarven " +
      "spirits, as well as some foul smell that you don't recognise.\n");
    /* Set the smell if identified. */
    set_unid_smell("Yep, this brew smells pretty bad!\n");
    /* Set the smell for those who can't identify it. */
    set_id_diff(19);
    /* How hard is it to identify? */
    set_soft_amount(100);
    /* What is the amount of liquid in mL? */
    set_alco_amount(244);
    /* How much alcohol in the potion? Alcohol is needed for */
    /* potions to go ;-)  */
    set_potion_value(144);
    /* 1 gold coin, for the value. */

    set_effect(HERB_SPECIAL, "resistance", 1);
    /* Set the effect */
}

public void
special_effect()
{
    object ob;

    TP->set_intoxicated(TP->query_prop(LIVE_I_MAX_INTOX));

    if(TP->query_race() == "elf")
    {
	write("This brew upsets your delicate elven stomach!\n");
	say(QCTNAME(TP)+ "'s face turns green, and " +HE(TP)+ " looks rather sick!\n");
	write("You spew the contents of your stomach onto the ground. Ick!\n");
	say(QCTNAME(TP)+ " spews the contents of " +HIS(TP)+ " stomach all " +
	  "over the ground! How disgusting.\n");
	TP->eat_food(-(TP->query_stuffed()), 0);
	return;
    }

    if(P("Ansalon_Resistance_Object",TP))
    {
	write("Quaffing the brew did nothing for you.\n");
	return ;
    }
    seteuid(getuid());
    ob = clone_object("/d/Ansalon/estwilde/obj/dwarf_brew_object");
    ob->set_duration(600 + (random(121)));
    if (ob->move(TP))
	ob->move(TP, 1);
}