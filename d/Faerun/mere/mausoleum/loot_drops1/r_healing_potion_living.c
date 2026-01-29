/*  /d/Ravenloft/droptables/fos_drops/r_healing_potion_living.c
 *
 *  Healing potion. Undeads can't quaff this one.
 *
 *  Nerull, 2015
 */

inherit "/std/potion";
#include "../defs.h";
#include "/d/Ravenloft/defs/magicalitems_stats.h";
#include <stdproperties.h>
#include <herb.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>


/*
* Function name: create_potion
* Description:   This is the create-function of the potion, which you should
*                redefine and setup the herb from.
*/
public void
create_potion()
{
    seteuid(getuid(this_object()));

    string pot_name;
    string pot_addname;
    string pot_short;


    set_potion_name("testpotion");
    add_name("_r_healing_potion_living");

    set_short("shimmering blue potion");

    set_pshort("shimmering blue potions");

    set_adj("shimmering");
    add_adj("blue");

    set_id_long("Tinkering with the lid causes the liquid "
    +"to release a white vapour which reminds you of "
    +"calm seaside breeze. The more you stare into the "
    +"shimmering the more alive you feel.\n");

    set_unid_long("A calm blue potion which reminds you "
    +"of  the ocean. Many pleasant comforting ideas spring "
    +"into your thoughts as you gaze into the shimmering blue.\n");

    set_id_taste("It tastes of crystalized pure "
    +"water, a taste of life. This potion will definitely "
    +"heal the wounds of the living.\n");

    set_unid_taste("It tastes of crystalized pure "
    +"water, a taste of life.\n");

    set_id_smell("Recognizing this as manapotion, you would "
    +"use this one when in dire need for more mana.\n");

    set_unid_smell("It smells like strawberry and lemon.\n");


	add_prop(MAGIC_AM_MAGIC, ({ 30,"enchantment" }));

	add_prop(MAGIC_AM_ID_INFO, ({ "This potion give a small "
	+"amount of health to a living when quaffed.\n",20 }));

	add_prop(OBJ_S_WIZINFO, "This potion give a small "
	+"amount of health (300) to a living when quaffed. It "
	+"gives a 180 seconds cooldown.\n");

    // Identification Difficulty
    set_id_diff(R_HEAL_POTION_ID_DIFFICULTY);

    // Amount of non-alcohol liquid
    set_soft_amount(R_HEAL_POTION_SOFT_AMOUNT);

    // Amount of Alcohol
    set_alco_amount(R_HEAL_POTION_ALCO_AMOUNT);

    // The worth of the potion
    set_potion_value(R_HEAL_POTION_VALUE);

    // The immediate effect when quaffed. See <herb.h>
    // for more detail.

    set_effect(HERB_SPECIAL, "healing", 1);
    
}



/*
* Function name: special_effect
* Description  : Define this routine if you want to do some special effect
*                if a player consumes this drink. By default, it displays
*                the message set with set_drink_msg(), if any.
* Arguments    : int amount - the number of drinks consumed.
*/
special_effect()
{
    seteuid(getuid());

    // This potion works only on the living.
    if (this_player()->query_prop(LIVE_I_UNDEAD))
    {
        this_player()->catch_msg("No, you will NOT "
        +"quaff this life-reeking potion!\n");
        return 0;
    }

    
    // Potion cooldown check.
    if (present("_r_healing_potion_cooldownob", this_player()))
    {
        this_player()->catch_msg("You feel no effect.\n");
        return 0;
    }

    // Execute the heal.
    this_player()->heal_hp(R_HEAL_POTION_HEAL_AMOUNT);

    // We clone the cooldown object
    clone_object(DOMAIN_DIR
    + "droptables/fos_drops/r_healing_potion_cooldown")->move(this_player(), 1);
    
    write("You feel MUCH better.\n");
}





