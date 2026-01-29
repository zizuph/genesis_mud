/*
 *  /d/Sparkle/area/city/obj/gnome/lever.c
 *
 *  This is a shaft connecting mechanical parts together for gnomish
 *  machinery.
 *
 *  Created October 2008, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/obj/gnome/gnome_machinery2";

#include "../../defs.h"

/* Global Variables */
public string      Lever_Position = "middle";

/* Prototypes */
public void        create_machine();
public string      get_the_desc();


/*
 * Function name:        create_machine
 * Description  :        set up the construct
 */
public void
create_machine()
{
    add_name("shaft");
    set_adj( ({ "flat", "steel" }) );
    set_short(get_the_desc() + "shaft");
    set_desc("This " + get_the_desc() + "shaft looks a bit like an"
      + " unbelievably long snow ski.");

    set_f_delay(1.5);
    set_b_delay(1.5);

    set_forward("turning");
    set_f_forward("fixed in place, its flat edge parallel to the ground");
    set_backward("turning");
    set_f_backward("fixed in place, its flat edge parallel to the ground");
} /* create_machine */


/*
 * Function name:        get_the_desc
 * Description  :        Make use of any externally set adjectives in
 *                       the description of the gear.
 */
public string
get_the_desc()
{
    switch (sizeof(query_adj(1)))
    {
        case 0:
            return "";
            break;
        case 1:
            return query_adj() + " ";
            break;
        default:
            return query_adj(1)[0] + " " + query_adj(1)[1] + " ";
    }
} /* get_the_desc */