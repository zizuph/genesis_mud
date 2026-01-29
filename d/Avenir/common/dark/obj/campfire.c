// -*-C++-*- 
// campfire            /d/Avenir/common/dark/obj/campfire.c       
// creator(s ):       Casca, 01/25/00
// purpose:           Campfire which can be extinguished or light.
//                         This ones for the Albi.
// last update:      Lilith 05/19/00
// note:            
// bug(s):
// to-do:


#pragma strict_types

inherit "/std/torch";

#include "/d/Avenir/common/dark/dark.h";

#define BTU         (4)  /* How bright the fire burns.   */

/* Function name: reset_placed_functions
 * Description:   This function is called from the placer module to 
 *                reset the object. Can be used to fill the object with 
 *                contents. 
 *
 *    For when it is called see:
 *    /d/Avenir/smis/std/placer_mod.c
 *
 *    If it returns 1, the placer will do nothing, but if it returns 0,
 *    the placer will clone a new object.
 *
 */
public int
reset_placed_functions()
{
    reset_torch();
    return 1;
}

/*
 * Function name: reset_torch
 * Description  : Since you may not mask reset_object() in torches, you have
 *                to redefine this function.
 */
public void
reset_torch()
{
    set_strength(BTU);
    set_time(1800); 
}

void
create_torch()
{
    set_name("campfire");
    add_name(({"fire", "avenir_dark_camp_fire"}));

    set_long("This is a small campfire, built with collected "+
        "driftwood and small chunks of a flammable stone."+
        "@@burning_desc@@");

//Dont want them to burn themselves.
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

//Lets not show it in the room exept in the long.
    set_no_show_composite(1); 

//Lets set the brightness and the timer
    reset_placed_functions();
}

/*
 * Function name: burning_desc
 * Description:     adds to long desc depending on the state of the fire.
 * Returns:           string - description
 */
public string 
burning_desc()
{
    if(!query_time())
        return " These ashes are long beyond the hope of re-kindling into a fire.\n";
    else if (!query_prop(OBJ_I_HAS_FIRE))
        return " It seems ready to be set alight.\n";
    else
        return " Trembling, uncertain flames lick at the wood and "+
                  "stone, sending plumes of stink and smoke into the air.\n";
}

public varargs string
short(object for_obj)
{
    // double ::'s to get rid of the (lit) message
    return ::short(for_obj);
}

/*
 * Function name: flame_tells
 * Description:     called when the campfire is lighted; gives nifty messages.
 */
public void 
flame_tells()
{
    string  str;

    if(!query_lit(0))
        return;

    switch(random(5))
    {
        case 0:
            str = "The fire pops and sizzles as fat from the roasting meat "+
                    "falls into the flames.";
            break;
        case 1:
            str = "The fire crackles and pops, throwing a beautiful cascade of "+
                   "sparks arcing through the air.";
            break;
        case 2:
            str = "A knot explodes, scattering sparks in the air.";
            break;
        case 3:
            str = "The flames scatter and flare, casting odd shadows.";
            break;
        default:
             str = "The fire burns dimly, casting only the faintest light.";
    }

    tell_room(environment(this_object()), str + "\n");
    set_alarm(itof(random(200) + 20), 0.0, flame_tells);
}

/*
 * Function name: light_me_after_delay
 * Description:     called when the torch is lighted; masking this function from
 *                        std/torch.c  to provide an additional msg when lighted.
 * Returns:          1 - torch successfully lit     
 */
public int 
light_me_after_delay()
{
    ::light_me_after_delay();
    tell_room(environment(this_object()), "The campfire sputters back to life.\n");
    set_alarm(itof(random(200) + 20), 0.0, flame_tells);
    return 1;
}

/*
 * Function name: query_light_fail
 * Description  : This function indicate whether the torch may be lit or not;
 *                      Masking this function from std/torch.c to add another
 *                      check -- player should not be able to light it if in combat.
 * Returns:        string - fail 
 *                     int 0 - no fail   
 */
public mixed
query_light_fail()
{
    if (this_player()->query_attack())
        return "You don't have the time to start a campfire. You're in combat!\n";

    ::query_light_fail(); 
}

/*
 * Function name: query_torch_may_decay
 * Description  : This function will indicate whether the torch may decay or not
 *                after it burns out. By default it returns 1, but if you do not
 *                want to have it decay, you must redefine this function to make
 *                it return 0. This is especially true for oil lamps.
 * Returns     In this case 0 - never..
 */
public int
query_torch_may_decay()
{
    return 0;
}

