/*
 *    /d/Gondor/ithilien/poros/npcs/corsair.c
 *
 *    This is a standard corsair crewman.
 *    Original by Talisan,  February 1996
 *
 *    Revision history:
 *        5/13/99 modified for use in pelargir lighthouse quest by Tyr
 *        6/28/99 incorporated Gnadnar's suggested improvements by Tyr
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/npcs/corsair_master";

#include <stdproperties.h>
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

/* prototypes */
public void	create_corsair();
public string	*random_adj();
public int	query_knight_prestige();


/*
 * Function name:	create_corsair
 * Description	:	set up the corsair. appearance varies.
 */
public void
create_corsair()
{
    FIX_EUID;

    add_adj(random_adj());

    set_chat_time(6 +random(3));
    add_chat("You shouldn't be here.");
    add_chat("I'd rather be out raiding aboard the ship!");
    add_chat("We should move our hideout again.");
    add_chat("I don't think it's safe here anymore.");
    add_chat("Looting's much easier when the lighthouse at Pelargir is busted.");
    add_chat("The last merchantman we took was a real prize. Full of booty!");
    add_chat("We should plunder Pelargir next.");
    add_chat("I think Umbar and Minas Morgul should join against Gondor.");

    set_cchat_time(4 +random(2));
    add_cchat("Die, you stinking dog!");
    add_cchat("I'll soon have your head on a pike!");
    add_cchat("Looks like we're about to have another slave!");
    add_cchat("For Umbar!");
    add_cchat("Long live the Corsairs!");

    set_act_time(6 +random(6));
    add_act("laugh evil");
    add_act("grin");
    add_act("spit");
    add_act("grumble");

#if 0
    set_equipment( ({ (POROS_DIR + "armours/chainmail"),
                      (POROS_DIR + "armours/helmet"),
                      (POROS_DIR + "weapons/broadsword") }) );
#endif

}   /* end create corsair */


/*
 * Function name:	random_adj
 * Description	:	return random pair of adjectives
 * Returns	:	string * -- an array of two adjectives
 */
public string *
random_adj()
{
    switch (random(11))
    {
    case 0:
      return ({ "fierce", "corsair" });
      break;
    case 1:
      return ({ "savage", "corsair" });
      break;
    case 2:
      return ({ "tall", "corsair" });
      break;
    case 3:
      return ({ "sinister", "corsair" });
      break;
    case 4:
      return ({ "furtive", "corsair" });
      break;
    case 5:
      return ({ "haughty", "corsair" });
      break;
    case 6:
      return ({ "dark-eyed", "corsair" });
      break;
    case 7:
      return ({ "strong", "corsair" });
      break;
    case 8:
      return ({ "powerful", "corsair" });
      break;
    case 9:
      return ({ "evil-looking", "corsair" });
      break;
    case 10:
      return ({ "shifty-eyed", "corsair" });
      break;
    }
} /* random_adj */

public int	query_knight_prestige()	{ return 50; }
