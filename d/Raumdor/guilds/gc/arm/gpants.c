/*********************************************************************
 * - pants.c                                                       - *
 * - A random coloured pair of pants for the shops in the          - *
 * - Gentleman's club                                              - *
 * - Created by Damaris 10/2001                                    - *
 * - Modified by Mercade 1/5/2001 (Thanks for the help)            - *
 * - Remodified by Damaris 1/6/2001                                - *
 *********************************************************************/

#pragma strict_types

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define COLOURS ({ "black", "brown", "grey" })

/*********************************************************************
 * - Global variable, contains the colour of the pants.            - *
 *********************************************************************/
string colour = one_of_list(COLOURS);

/*********************************************************************
 * - Function name: set_up_pants                                   - *
 * - Description  : Sets up the dynamic part of the pants,         - *
 * -                including the colour description.              - *
 *********************************************************************/
void
set_up_pants()
{
    set_short("pair of " + colour + " pants");
    set_pshort("pairs of " + colour + " pants");
    set_long("This is a high quality " + short() +". It has been made "+
      "with pliable fabric to allow the wearer freedom of movement. "+
      "In fact they are so supple they give the wearer the "+
      "kind of flexibility that is needed in riding steeds or carousing, "+
      "but elegant enough to go courting in.\n");
    set_adj(colour);
}

void
create_armour()
{
    set_up_pants();

    set_name("pants");
    /* People should also be able to refer to this as the pair, etc. */
    add_name("pair");
    set_pname("pairs");
    set_adj( ({ "pair", "of" }) );

    set_ac(10 + random(5));
    set_at(A_LEGS);
    set_am( ({-1,3,-2 }) );

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()) + 100);
    
}

/*********************************************************************
 * - Function name: query_recover                                  - *
 * - Description  : Returns the recovery string, including the     - *
 * -                colour of the pants.                           - *
 * - Returns      : string - the recovery string.                  - *
 *********************************************************************/
string
query_recover()
{
    return MASTER + ":" + colour;
}

/*********************************************************************
 * - Function name: init_recover                                   _ *
 * - Description  : Sets up the colour of the pants after recovery.- *
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
        set_up_pants();
    }
}
