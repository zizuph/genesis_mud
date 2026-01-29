/*********************************************************************
 * - gloves.c                                                      - *
 * - A random coloured pair of gloves for the shops in the         - *
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

#define COLOURS ({"brown", "grey", "white", "silver", "black", "cream", })

/*********************************************************************
 * - Global variable, contains the colour of the gloves.           - *
 *********************************************************************/
string colour = one_of_list(COLOURS);

/*********************************************************************
 * - Function name: set_up_gloves                                  - *
 * - Description  : Sets up the dynamic part of the gloves,        - *
 * -                including the colour description.              - *
 *********************************************************************/
void
set_up_gloves()
{
    set_short("pair of " + colour + " gloves");
    set_pshort("pairs of " + colour + " gloves");
    set_long("A " + short() +" meant to be worn on the hands. These "+
      "gloves compliment any gentleman's attire making it complete. "+
      "The leather is soft and supple giving freedom of movement. "+
      "They also denote elegance and refinement to those who are "+
      "smart enough to add them to their wardrobe.\n");
    set_adj(colour);
}

void
create_armour()
{
    set_up_gloves();

    set_name("gloves");
    /* People should also be able to refer to this as the pair, etc. */
    add_name("pair");
    set_pname("pairs");
    set_adj( ({ "pair", "of" }) );

    set_ac(10 + random(5));
    set_at(A_HANDS);
    set_am( ({-1,3,-2 }) );

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()) + 100);
    
}

/*********************************************************************
 * - Function name: query_recover                                  - *
 * - Description  : Returns the recovery string, including the     - *
 * -                colour of the gloves.                          - *
 * - Returns      : string - the recovery string.                  - *
 *********************************************************************/
string
query_recover()
{
    return MASTER + ":" + colour;
}

/**********************************************************************
 * - Function name: init_recover                                    _ *
 * - Description  : Sets up the colour of the gloves after recovery.- *
 * - Arguments    : string arg - the recovery argument.             - *
 **********************************************************************/
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
        set_up_gloves();
    }
}
