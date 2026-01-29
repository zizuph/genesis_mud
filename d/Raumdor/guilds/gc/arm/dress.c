/*********************************************************************
 * - dress.c                                                       - *
 * - A black dress for the shops in the                            - *
 * - Gentleman's club                                              - *
 * - Created by Damaris 10/2001                                    - *
 *********************************************************************/
#pragma strict_types

inherit "/std/armour";

#include "/d/Raumdor/defs.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

void create_armour()
{
	set_short("black silk dress");
	set_name("dress");
	set_adj( ({"black", "sleeveless", "silk"}) );
	set_long("This is a medium length, black, sleeveless silk dress. "+
       "The neckline plunges deeply exposing the supple cleavage of the "+
       "one who wears it. The back also plunges downward to expose "+
       "and show off the delicate curves of the back. It smoothly "+
       "hugs the hips and thighs in a most provocative manner and ends "+
       "right above the knee.\n");

    set_ac(10 + random(5));
    set_at(A_BODY);
    set_am( ({-1,3,-2 }) );

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()) + 100);
}
public string
query_recover()
{
return MASTER;
}

mixed wear()
{

	/* This is what wearer see's when wearinging. */
	write("You slowly slip into the "+ short() +" and stifle a soft "+
	"moan as the soft silk caresses your skin sensually.\n");

    /* This what others in room see upon wearing. */
    say(QCTNAME(TP)+" slowly slips into "+
       "the "+short()+" with a definate look of pleasure "+
       "upon "+ HIS(TP) +" face as the silky material caresses "+
       "against "+ HIS(TP) +" skin.\n");
  return 1;
}

mixed remove()
{
	/* This is what wearer see's when removing. */
    write("You slowly slip off the "+ short() +", the material "+
       "gliding against your flesh in a most sensuous exotic way.\n");

    /* This is what others in room see when removing. */
    say(QCTNAME(TP)+" slowly slips out "+
       "of "+HIS(TP)+" "+ short() +", "+ HIS(TP) +" face "+
       "looking a bit flushed as "+ HE(TP) +" does so.\n");

    return 1;
}
