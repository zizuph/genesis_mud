/*  /d/Ravenloft/droptables/fos_drops/r_healing_potion_undead.c
 *
 *  Healing potion. The living can't quaff this one.
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

    set_potion_name("Dissolution");

    set_short("smoky black potion");

    set_pshort("smoky black potions");

    set_adj("smoky");
    add_adj("black");

    set_id_long("A smoky black potion that could only "
    +"benefit one who is not living. Unless you "
    +"wish to perish, you should not quaff this potion.\n");

    set_unid_long("This is a smoky black potion. The potion "
    + "appears black with smoky grey tails spinning about. It "
    + "releases a blackened cloud as you adjust the lid. It "
    + "doesnt look healthy.\n");

    set_id_taste("It tastes of the void. This "
    +"potion will aid only the dead.\n");

    set_unid_taste("It tastes of the void.\n");

    set_id_smell("It smells of foul and rotting "
    +"corpses.\n");

    set_unid_smell("It smells of foul and "
    +"rotting corpses.\n");

	add_prop(MAGIC_AM_MAGIC, ({ 30,"enchantment" }));

	add_prop(MAGIC_AM_ID_INFO, ({ "This potion give a small "
		+ "amount of health to the undead when quaffed.\n",20 }));

	add_prop(OBJ_S_WIZINFO, "This potion give a small "
		+ "amount of health (300) to an undead when quaffed. It "
		+ "gives a 180 seconds cooldown.\n");

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

    // This potion works only on the undead.
    if (!this_player()->query_prop(LIVE_I_UNDEAD))
    {
        this_player()->catch_msg("No, you will NOT quaff "
        +"this potion, as it reeks of Death and Decay!\n");
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

    write("You feel greatly rejuvenated!\n");
}


