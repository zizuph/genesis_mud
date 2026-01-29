/*********************************************************************
 * - shirt.c                                                       - *
 * - A random coloured shirt for the shops in the                  - *
 * - Gentleman's club                                              - *
 * - Created by Damaris 10/2001                                    - *
 * - Remodified by Damaris 1/6/2001                                - *
 *********************************************************************/
#pragma strict_types

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define COLOURS ({ "burgundy", "black", "cream", "crimson", "blue" })

/*********************************************************************
 * - Global variable, contains the colour of the shirt.            - *
 *********************************************************************/
string colour = one_of_list(COLOURS);

/*********************************************************************
 * - Function name: set_up_shirt                                   - *
 * - Description  : Sets up the dynamic part of the shirt,         - *
 * -                including the colour description.              - *
 *********************************************************************/
void
set_up_shirt()
{
    set_short("" + colour + " coloured satin shirt");
    set_long("This is a " + colour + " coloured satin shirt. This is special "+
      "attire for gentleman. The satin is used to show "+
      "off nobility and style.\n");
    
    set_adj(colour);
}

void
create_armour()
{
    set_up_shirt();
    
    set_name("shirt");
    add_name("satin shirt");
   
    set_ac(10 + random(5));
    set_at(A_TORSO);
    set_am( ({-1,3,-2 }) );

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()) + 100);
}

/*********************************************************************
 * - Function name: query_recover                                  - *
 * - Description  : Returns the recovery string, including the     - *
 * -                colour of the shirt.                           - *
 * - Returns      : string - the recovery string.                  - *
 *********************************************************************/
string
query_recover()
{
    return MASTER + ":" + colour;
}

/*********************************************************************
 * - Function name: init_recover                                   _ *
 * - Description  : Sets up the colour of the shirt after recovery.- *
 * - Arguments    : string arg - the recovery argument.            - *
 *********************************************************************/
void
init_recover(string arg)
{
    /* Only set the colour if we recognise it. */
    if (member_array(arg, COLOURS) >= 0)
    {
        /* First remove the old randomised adjective. */
        remove_adj(colour);

        /* Set up the old colour and re-initialise the desciptions. */
        colour = arg;
        set_up_shirt();
    }
}
