/*
 *   /d/Gondor/morgul/obj/hooded_scalemail.c
 */

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>  

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name(({"scalemail", "scalemail armour", "armour", "armor", "scale"}));
    set_short("enormous hooded scalemail");
    set_pshort("enormous hooded scalemails");
    set_long("This hooded scalemail is enormous and dirty! It seems too large "
      + "for anyone less than eight feet tall to wear. Still, it looks as " 
      + "though it would provide good protection to its wearer.\n");
    set_adj(({"hooded", "enormous", "dirty", "troll"}));

    set_default_armour(40, A_BODY | A_ARMS | A_LEGS | A_HEAD | A_NECK,({0,0,0}), 0);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(28) + random(300));
    add_prop(OBJ_I_WEIGHT, 40000 + random(3000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    set_af(TO);

}

public int
wear(object arm)
{
    if (TP->query_race_name() == "troll")
    {
        write("The " + short() + " fits you well as you slip into it!\n");
        say(QCTNAME(TP) + " slips into "
            + TP->query_possessive() + " " + short() + ".\n"); 
        return 1;
    }

    if (TP->query_race_name() == "minotaur")
    {
        write("The " + short() + " fits you a little loosely as "
            + "struggle into it.\n");
        say(QCTNAME(TP) + " slips awkwardly into "
            + TP->query_possessive() + " " + short() + ".\n"); 

        return 1;
    }

    else
    {
        write("The " + short() + " is much too big for you!\n");
        say(QCTNAME(TP) + " flounders around awkwardly while trying to wear "
            + "an " + short() + ", but only manages to get tangled up "
            + "and look foolish.\n"); 
    }
        return -1;

}