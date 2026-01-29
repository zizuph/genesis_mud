/* This is a poison gas - it is created by one of Enzalcaspins spells.    */
/* It takes a total of 1500hp over a period of 3 mins 20 seconds.         */
/* Coded 11/11/95 by Tulix III.                                           */

inherit "/std/poison_effect";
#include <poison_types.h>

public void
create_poison_effect()
{
    set_interval(10);
    set_time(200);
    set_damage( ({ POISON_FATIGUE, 40, POISON_HP, 75 }) );
    set_strength(60);
    set_poison_type("gas");
}

/*
 * Function name: tell_damage_player
 * Description  : The player has been hurt; tell him how.  A string
 *                is passed, which must sound reasonable in the 
 *                sentences "You feel xxxx." and "You feel much xxxx."
 * Arguments    : phit - the damage level
 *                str  - the string to tell the player.
 */
public void
tell_damage_player(int phit, string str)
{
    if (silent > 1)
    {
        return;
    }

    if (phit > 90)
    {
        tell_object(poisonee, "The poisonous gas you breathed in is still " +
            "burning the inside of your lungs.\nYou feel so much " + str + 
            ", you wish you were dead.\n");
        return;
    }

    if (phit > 75)
    {
        tell_object(poisonee, "The poisonous gas you breathed in is still " +
            "causing internal damage.\nYou feel much " + str + ".\n");
        return;
    }

    tell_object(poisonee, "The poisonous gas you breathed in causes " +
        "a sharp pain in your lungs.\nYou feel " + str + ".\n");
    return;
}


