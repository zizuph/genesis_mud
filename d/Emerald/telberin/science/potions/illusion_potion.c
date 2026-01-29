/*
 *  /d/Emerald/telberin/science/potions/illusion_potion.c
 *
 *  A illusion-resistance potion sold in the apothecarium of Telberin.
 *
 *  Store location:  /d/Emerald/telberin/science/apothecarium.c
 *  Vending code  :  /d/Emerald/telberin/science/npc/trainer.c
 *
 *  Created March 2014, by Cooper Sherry (Gorboth)
 */

inherit "/d/Emerald/telberin/science/potions/resistance_potion_base";



/* Prototypes */
public void          create_resistance_potion();



/*
 * Function name:        create_resistance_potion
 * Description  :        dummy routine to be masked in inheriting files
 */
public void
create_resistance_potion()
{
    set_res_type("illusion");
    set_alarm(0.0, 0.0, setup_resistance_potion);
} /* create_resistance_potion */
