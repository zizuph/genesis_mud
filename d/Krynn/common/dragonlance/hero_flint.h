#ifndef _HERO_FLINT_H_
#define _HERO_FLINT_H_

#include "heroes.h"

#define SOLACE_FOREST ({ \
	({ "emote collapses on the boulder.", \
	   FLINT_NAME, \
	   7.0 }), \
	({ "emote grumbles: I should never have left.", \
	   FLINT_NAME, \
	   3.0 }), \
	({ "say And I'll be damned if I'm ever leaving " + \
	   "again!", FLINT_NAME, \
	   25.0 }), \
	({ "emote pulls a block of wood and a gleaming " + \
	   "dagger from his pack. He starts slicing at " + \
	   "the wood.", FLINT_NAME, \
	   15.0 }), \
	({ "say Silliest thing I ever did. After one " + \
	   "hundred and forty-eight years, I ought " + \
	   "to have learned!", FLINT_NAME, \
	   3.0 }), \
	({ "You hear a distant voice saying: You'll " + \
	   "never learn, dwarf! Not if you live to be " + \
	   "two hundred and forty-eight!", FLINT_NAME, \
	   5.0, 1 }), \
	({ "say Tanis?", \
	   FLINT_NAME, \
	   3.0 }), \
	({ &flint_interrupt("tanis", "Enter Solace forest"), \
	   TANIS_NAME, \
	   5.0 }), \
	({ "smile tanis", \
	   FLINT_NAME, \
	   5.0 }), \
	({ "say Did you find what you sought?", \
	   TANIS_NAME, \
	   5.0 }), \
	({ "emote growls: Well, I assume one would go with the other.", \
	   FLINT_NAME, \
	   4.0 }), \
	({ "say Are we going to stand here all night, smelling the " + \
	   "cooking fires? Or are we going to go into town and get " + \
	   "some dinner?", \
	   TANIS_NAME, \
	   5.0 }), \
	({ "southwest", \
	   TANIS_NAME, \
	   0.5 }), \
	({ "say So you found nothing?", \
	   TANIS_NAME, \
	   3.0 }), \
	({ "say Not true. The clerics vanished three hundred years ago " + \
	   "during the Cataclysm. So says the elders.", \
	   TANIS_NAME, \
	   4.0 }), \
        ({ "emote whispers: What?", \
	   TANIS_NAME, \
	   5.0 }), \
	({ "emote peers toward the trees.", \
	   FLINT_NAME, \
	   4.0 }), \
	({ "emote whispers: I don't see anything.", \
	   TANIS_NAME, \
	   5.0 }), \
	({ "emote screams in furious rage.", \
	   FLINT_NAME, \
	   4.0 }), \
	({ "emote groans: Wouldn't you know it? Tasslehoff Burrfoot.", \
	   FLINT_NAME, \
	   6.0 }), \
	({ &flint_interrupt("tasslehoff", "Enter Solace forest"), \
	   TAS_NAME, \
	   4.0 }), \
                      })

#endif _HERO_FLINT_H_
