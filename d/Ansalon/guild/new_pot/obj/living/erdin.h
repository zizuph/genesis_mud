/*
 */

#ifndef POT_ERDIN_DEFS
#define POT_ERDIN_DEFS

#include "/d/Ansalon/guild/new_pot/guild.h"

#define INGREDIENTS_OBJ (GUILDDIR + "obj/ingredients/")

#define INGREDIENTS     ([ "diamond" : "diamond_dust", \
                           "silver" : "silver_powder", \
                           "heart" : "", \
                        ])
                        
    ({ "<TO> places the <OB> in a small steel bowl upon the " +     \
       "workbench. He reaches for a small phial and unplugs it.\n", \
                                                                    \
       "Leaning as far from the bowl as possible, <TO> tips the " + \
       "phial over the bowl and a thick black liquid drips down " + \
       "while he mumbles a prayer to the Dark Queen.\n",            \
                                                                    \
       "There is a slow cracking noise and then a large bang. " +   \
       "A cloud of black smoke rises from the bowl.",               \
                                                                    \
       "<TO> waves away the smoke and then empties the bowl " +     \
       "into <TP> outstretched hands.\n" }),                        \
                                                                    \
    "silver" : "silver_powder",                                     \
    ({ "
