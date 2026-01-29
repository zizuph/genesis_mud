/* 
 * This is /d/Gondor/common/npc/midge.c, copied from
 *  /d/Gondor/common/npc/midge.c by Justus.
 * Olorin, Sep 1993
 * Changed to inherit /d/Gondor/common/npc/mosquito.c for the more
 * realistic and annoying features of Mercade's hard-to-kill insects.
 * Elessar, Dec 1998
 */

inherit "/d/Gondor/common/npc/mosquito";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/trigaction";
inherit "/std/act/domove";
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define RADJ ({ ({"tiny black"}), ({"tiny brown"}), ({"little beige"}),\
    ({"little green"}), ({"little brown"}), ({"little black"}) })
#define RLONG ({\
    "This is the tiniest of midges. Still, it can be a nuisance, flying around "\
	+ "your head.\n",\
    "This tiny midge is swarming all around you, especially in front of "\
	+ "your eyes and through your hair.\n",\
    "This little midge keeps creeping through your face and hair.\n",\
    "This is a curious green midge which keeps tickling your face.\n",\
    "This brown midge is particularly bothersome, swarming around you, "\
	+ "tickling you in the eyes, in the nose, in the neck, everywhere.\n",\
    "This one is rather big for a midge, but no less troublesome than the "\
	+ "smaller ones.\n"})


string nibbleplayer;

void
create_mosquito() 
{
    int ran;

    if (!IS_CLONE) return;

    ran = random(sizeof(RADJ));
    set_name("midge");
    set_race_name("midge");
    add_name(({"_random_midge_"}));
    set_pname("midges");
    set_pshort(implode(RADJ[ran], ", ") + " midges");
    set_race_name("midge"); 
    set_adj(RADJ[ran]);
    set_long(BS(RLONG[ran]));
    set_gender(G_NEUTER);
    add_prop(LIVE_I_NEVERKNOWN,1);

    refresh_living();

    /* Hard to hit though because it's hopping around all the time! */

    set_act_time(2);        /* Set some random actions */    
    add_act("emote creeps through your hair.");
    add_act("emote swarms around your head.");
    add_act("emote flies into your face.");
    add_act("emote flies into your ears.");
    add_act("emote flies into your eyes.");
    add_act("emote scrambles over your neck.");
    add_act("emote scrambles into your nose.");
    add_act("emote flies around through the grass.");
    add_act("emote buzzes around aimlessly.");
}

void
try_sting(object victim)
{
    if (present("_Midge_Repellant_", victim))
    {
        victim->catch_msg("The midges seem to stay away from you.\n");
        return;
    }
    ::try_sting(victim);
}

/* For the solamnic Knights */
query_knight_prestige() { return(0); }

