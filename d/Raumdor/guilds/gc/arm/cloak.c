/*********************************************************************
 * - cloak.c                                                       - *
 * - A random coloured cloak for the shops in the Gentleman's club - *
 * - Created by Damaris 10/2001                                    - *
 * - Modified by Mercade 1/5/2001 (Thanks for the help)            - *
 * - Remodified by Damaris 1/6/2001                                - *
 *********************************************************************/
#pragma strict_types

inherit "/std/armour";

#include "/d/Raumdor/defs.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define COLOURS ({ "black", "brown", "grey" })
#define CLASP  ({ "gold", "silver", "sterling silver", "mithril" })

string clasp = one_of_list(CLASP);
string colour = one_of_list(COLOURS);

void
set_up_cloak()
{
    set_short("satin lined " + colour + " cloak");
    add_name(({""+ colour + " cloak", "satin cloak"}));
    set_adj(colour);
    set_long("This is a " + short() + ". This cloak is long "+
      "flowing and fastens at the collar with a small " + clasp + " clasp. "+
      "It is quite the style, no gentleman would be without "+
      "such a fine cloak. \n");
    add_item(({""+ clasp + "clasp", "clasp", "fastener"}),
      "This is a " + clasp + " clasp. It fastens at the collar.\n");
}

void
create_armour()
{
    set_name("cloak");
    set_ac(10 + random(2) ? random(6) : -random(6));
    set_at(A_ROBE);
    set_am( ({-1,3,-2 }) );
    
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()) + 100);
    
    add_item(({"lining"}),
      "This cloak has satin lining that smoothly caresses the body and "+
      "adds to the flowing appearance.\n");

    set_up_cloak();
}

mixed
wear()
{
    /* This is what wearer see's when wearinging. */
    write("You slip the "+ short() +" around your shoulders "+
      "allowing the satin lining to flow along your body as you "+
      "fasten the "+ CLASP + " clasp.\n");

    /* This what others in room see upon wearing. */
    say(QCTNAME(TP)+" slips the "+short()+" "+
        "around "+ HIS(TP) +" shoulders and fastens the "+ CLASP + " clasp.\n");
    return 1;
}

void
query_recover()
{
    return MASTER + ":" + colour + "," + clasp;
}

void
init_recover(string arg)
{
    string *args = explode(arg, ",");

    /* Verify arguments. */
    if (sizeof(args) < 2)
    {
        return;
    }

    /* Verify and set the colour. */
    if (member_array(args[0], COLOURS))
    {
        remove_adj(colour);
        colour = args[0];
    }
    /* Verify and set the clasp. */
    if (member_array(args[1], CLASP))
    {
        clasp = args[1];
    }
    /* Set up the dynamic descritpions. */
    set_up_cloak();
}
