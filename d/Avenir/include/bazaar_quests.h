// file name: ~Avenir/include/bazaar_quests.h
// creator(s):  Boriska, Mar 18 1995
// last update: Boriska, Mar 18 1995
// purpose:     Common definitions for quests in bazaar area
// note:
// bug(s):
// to-do:

#ifndef _BAZAAR_QUESTS_H
#define _BAZAAR_QUESTS_H

// quest bit group
#define GROUP 0

// quest bits
#define FIRST_BIT 5
#define LAST_BIT  12

// quests are counted starting from , because there's no way
// to distinguish between unset prop and prop with value 0.
#define LIBRARY_TOUR 1
#define PILLORY_TOUR 2

#define QUEST_TOKEN "/d/Avenir/boriska/baz/quest_token"
#define QUEST_TOKEN_ID "_avenir_bazaar_quest_token"

// set to number of quest solved
#define BAZAAR_QUEST_SOLVED "_avenir_i_bazaar_quest_solved"

#endif




