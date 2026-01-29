/* This file contains constants pertaining to the Tours of Argos       */
/* note: some properties used by quests are found in argos/argos.h     */
/*       where multiple areas are involved.                            */
 
/* Tour properties. Each number represents the current state on a tour
**
** When prop value = 0,      that means player is not on a quest
** When prop value > 50,     that means player just finished SOME quest
** When prop value >0 & <50, that means player is on SOME quest
*** The ON_xxx values are the tour#'s, and therefore indices into
** the arrays below.
*/
#define ARGOS_TOUR_PROP    "_argos_tour_prop"
#define ON_NO_TOUR         0
#define DONE_SOME_TOUR     50    /* any value > this val means SOME tour done*/
#define NO_TOURS_DONE      0
 
#define ON_REG_TOUR        1
#define REG_TOUR_DONE      51
 
#define ON_TOE_QUEST       2
#define TOE_QUEST_DONE     52
 
#define ON_CASSOCK_QUEST   3
#define CASSOCK_QUEST_DONE 53
 
#define ON_GRANDMA_QUEST   4
#define GRANDMA_QUEST_DONE 54
 
#define ON_WINE_QUEST      5
#define WINE_QUEST_DONE    55
 
/* array of experience added for each tour. Indices match vals of ON_X_TOURs */
#define TOUR_EXP ({0,400,800,2400,3500,3500})
 
/* array of tour identifiers listed in order. ON_XXX_TOUR above are indices */
#define TOUR_PROP \
   ({ON_NO_TOUR,ON_REG_TOUR,ON_TOE_QUEST,ON_CASSOCK_QUEST,ON_GRANDMA_QUEST, \
     ON_WINE_QUEST})
#define LAST_TOUR_NUM_TODO (sizeof(TOUR_PROP)-1)
 
/* list of tour titles. Used to log_file when players finish each tour */
#define TOUR_NAME \
        ({"none","Registry Tour","Toe Quest","Cassock Quest","Grandma Quest", \
        "Wine Quest"})
 
/* Instructions said by Alexis when a tour is asked for */
#define TOUR_SAYS ({ \
   ({"I am really sick. I must have caught a bug."}),                   \
   ({                                                                         \
     "Find the visitor's center in Argos and sign the registry.",             \
     "We like to keep a record of our visitors.",                             \
     "Then come back to me and ask for your reward."                          \
   }),                                                                        \
   ({                                                                         \
     "It is said to bring luck to rub the toes of all the statues of the "+   \
        "monarchs of Argos.",                                                 \
     "Find all the statues of our monarchs in the city and rub their toes.",  \
     "Come back to me and ask for a reward when you are done."  \
   }),                                                                        \
   ({                                                                         \
      "I heard that something was stolen from the collections of my travels.",\
      "Find Epsoros who takes care of my collection and ask him about it.",   \
      "Return the stolen object to him and come back and ask for your reward."\
   }),                                                                        \
   ({                                                                         \
      "My old friend Giagia needs some new clothes. Her old ones are so "+    \
         "stained with grapes and dirt.",                                     \
      "I promised to send her a newly made tunic and cloak.",                 \
      "Go have those two things made and take them to her.",                  \
      "Then return to me and ask for your reward."                            \
   }),                                                                        \
   ({                                                                         \
      "My friend Dramaticus works too hard.",                                 \
      "Managing the guild of our only queen is a big job.",                   \
      "He really likes newly made wine. Deliver a bottle to him and "+        \
         "come back and ask for your reward."                                 \
   })                                                                         \
})
 
/* Constants used by the Registry Tour in the City */
#define  REG_TOUR_QUILL  "_argos_reg_tour_quill"
#define  REG_TOUR_DIPPED "_argos_reg_tour_dipped"
#define  REGISTRY_FILE   TEXT_DIR+"registry"
 
/* Awareness required by player to successfully find cassock via search */
#define CASSOCK_QUEST_AWARENESS 10

/* Constants used by the Toe Quest */
#define TOE_QUEST_PROP  "_argos_toe_quest_prop"
#define TOE_QUEST_ARGOSIUS     0
#define TOE_QUEST_PAXEUS       1
#define TOE_QUEST_AGRARIUS     2
#define TOE_QUEST_BASILEUS     3
#define TOE_QUEST_SOCARTES     4
#define TOE_QUEST_COLLISIMUS   5
#define TOE_QUEST_THESPIA      6
#define TOE_QUEST_BIBLIONUS    7
#define TOE_QUEST_COSMOPOLITUS 8
 
/* 3 quest bits used to indicate sequence of up to 7 quests done in order */
/* ie: 000->no quests done, 001->first quest done, 111->seventh done, etc */
#define QUEST_DOM   "Calia"
#define QUEST_GROUP 2
#define QUEST_BIT1  3
#define QUEST_BIT2  4
#define QUEST_BIT3  5
