#ifndef _HERO_TANIS_H_
#define _HERO_TANIS_H_

#include "heroes.h"

#define SOLACE_FOREST ({ \
	({ "say The same.", \
	   TANIS_NAME, \
	   2.0 }), \
        ({ "hug flint warmly", \
           FLINT_NAME, \
	   2.0 }), \
        ({ "say Some sign of the ancient, true gods? Or peace of mind? " + \
	   "I went seeking both. Which did you mean?", \
	   FLINT_NAME, \
	   5.0 }), \
	({ "say Go.", \
	   FLINT_NAME, \
	   3.0 }), \
	({ "southwest", \
	   FLINT_NAME, \
	   3.0 }), \
	({ "say Nothing.", \
	   TANIS_NAME, \
	   5.0 }), \
        ({ "say What about the dwarven clerics? The stories we heard?", \
	   FLINT_NAME, \
	   4.0 }), \
	({ "say Much like the elves.", \
	   TANIS_NAME, \
	   5.0 }), \
	({ "emote gestures and makes a hushing sound.", \
	   FLINT_NAME, \
	   4.0 }), \
	({ "emote whispers: Over by those trees.", \
	   TANIS_NAME, \
	   2.0 }), \
	({ "emote points into the forest.", \
	   FLINT_NAME, \
	   5.0 }), \
	({ "emote whispers: I did.", \
	   TANIS_NAME, \
	   6.0 }), \
        ({ "emote calls: Who goes there?", \
	   TANIS_NAME, \
	   6.0 }), \
	({ "As an answer comes an eerie sound that lasts for a long time, " + \
	   "one that makes you hair rise on your neck. It is a hallow, " + \
	   "whiring sound that starts out low and grows higher and " + \
	   "higher.", \
	   TANIS_NAME, \
	   10.0, 1 }), \
        ({ "Eventually the sound attains a high-pitched, screaming whine. " + \
	   "Soaring with it, comes a voice.", \
	   TANIS_NAME, \
	   4.0, 1 }), \
	({ "The spirit voice whines: Elven wanderer, turn from your " + \
	   "course and leave the dwarf behind. We are the spirits of " + \
	   "those poor souls Flint Fireforge left on the barroom floor. " + \
	   "Did we die in combat?", \
	   TANIS_NAME, \
	   7.0, 1 }), \
	({ "The spirit voice whines: NOO! We died of shame, cursed by the " + \
	   "ghost of the grape for not being able to outdrink a hill " + \
	   "dwarf.", \
	   TANIS_NAME, \
	   8.0, 1 }), \
        ({ "laugh", \
	   FLINT_NAME, \
	   1.0 }), \
                      })
	
#endif _HERO_TANIS_H_
