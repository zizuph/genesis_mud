/*  - Ghastly Keep --
 *
 *
 *  Created by Znagsnuf.
 *
 *  Relase date: 28/04-17
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  26/04-17				   Altered DROP_CHANCE to 5%  			   Znagsnuf
 *  26/04-17				   Changed GKEEP_KILL to 20  			   Znagsnuf
 *  05/05-17                   Altered DROP_CHANCE to 3%               Znagsnuf
 *  03/11-17                   Altered DROP_CHANCE to 2%               Znagsnuf
 *  03/11-17                   Changed the killes needed               Znagsnuf
 */

int RND_APPERANCE = 30 + random(20); 

#define GKEEP_ADJ1 ({"dreadful", "frightening", "horrible", "shockingly",\
                     "intensely", "unpleasant", "gruesome", "hideous",\
                     "horrendous", "horrid", "macabre", "nightmarish",\
                     "ghastly", "grim", "horrific", "eerie",})

#define GKEEP_ADJ2 ({"shadowy", "translucent", "transparent", "shimmering",\
                     "gaunt", "flowing", "pearly-white", "glistening",\
                     "silvery", "wispy"})

// Must kill this many to be able to enter level 2.
#define GKEEP_KILL                25 

// Define drop change.
#define RND_DROP                 100

// 2% chance of dropping a stone.
#define DROP_CHANCE			      2