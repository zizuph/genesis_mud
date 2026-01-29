/* 
 *	This is /d/Gondor/common/npc/bee.c
 *	Olorin, December 1995
 *
 *	Idea and most code copied from /d/Gondor/common/npc/mosquito.c
 *	by Mercade
 */
#pragma strict_types

inherit "/d/Gondor/common/npc/mosquito.c";
inherit "/std/act/action.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define RADJ ({ ({"tiny yellow-brown"}), ({"tiny brown"}), ({"little beige"}), \
                ({"little striped"}), ({"little brown"}), ({"little yellow-brown"}) })
#define RLONG ({ \
  "This is the tiniest of bees. Still, it can be a nuisance, flying around your head.\n",\
  "This tiny bee is swarming all around you, especially in front of your eyes and through your hair.\n",\
  "This little bee keeps creeping through your face and hair.\n",\
  "This is a curious green bee which keeps tickling your face.\n",\
  "This brown bee is particularly bothersome, swarming around you, tickling you "\
  + "in the eyes, in the nose, in the neck, everywhere.\n",\
  "This one is rather big for a bee, but no less troublesome than the smaller ones.\n"})

#define RWEIGHT ({ 10, 10, 20, 20, 20, 50 })    /* from 10 to 50 grams */

                  /* str dex con int wis dis */
#define RSTAT ({ \
                   ({  2, 20, 1, 1, 1, 5 }), \
                   ({  2, 24, 2, 1, 1, 5 }), \
                   ({  3, 28, 3, 1, 1, 5 }), \
                   ({  3, 32, 4, 1, 1, 5 }), \
                   ({  4, 36, 5, 1, 1, 5 }), \
                   ({  4, 40, 6, 1, 1, 5 }) })

public void
create_mosquito() 
{
   int     ran = random(6);

   set_name("bee");
   add_name(({"_random_bee_"}));
   set_pname("bees");
   set_pshort(implode(RADJ[ran], ", ") + " bees");
   set_race_name("bee"); 
   set_adj(RADJ[ran]);
   set_long(BS(RLONG[ran]));

   add_prop(CONT_I_WEIGHT,RWEIGHT[ran]);
   add_prop(CONT_I_HEIGHT,RWEIGHT[ran]);
   add_prop(CONT_I_VOLUME,RWEIGHT[ran]);
   add_prop(LIVE_I_NEVERKNOWN,1);

   set_stats(RSTAT[ran]);

   set_act_time(2);        /* Set some random actions */    
   add_act("emote swarms around your head.");
   add_act("emote flies around through the grass.");
   add_act("emote buzzes around angrily.");

   set_poison_file(POISON_DIR + "bee_sting");
}

