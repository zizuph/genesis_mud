/* M A V I A      Q U E S T S */

/* Inherit file for quests, has reward_quest() function. */
#define QUEST "/d/Avenir/inherit/quest" 

#define QUEST_LOG   "/d/Avenir/log/quest/maivia"

/* Log to weekly statserv */
#include "/d/Avenir/smis/sys/statserv.h"
 
/* Quest prop for mavia's quests */
#define MAIVIA_I_QUEST "_mavia_i_quest"

/* Some quest items should be opened, some shouldn't */
#define Q_OB_OPENED    "_av_quest_obj_opened"
#define M_W_O          "_maivia_wangle_ob"
#define M_O_O          "_maivia_ogre_ob"
#define M_N_O          "_maivia_nochipa_ob"

#define M_GROUP 1

/* Mavia Letter to Nochipa in the infidel hideout */
#define MBIT_NOCHIPA     8
#define MEXP_NOCHIPA     1500
#define MEXP_NOCHIPA_ALT 500
#define QUEST_MAV3       "Mavia Letter 2"

/* Ogre Package Delivery */
#define MBIT_OGRE        7
#define MEXP_OGRE        1000
#define M_EXP_OGRE_ALT   500
#define QUEST_MAV2       "Mavia Ogre Package"

/* Mavia Letter to Wangle at the Fort */
#define MBIT_WANGLE      6
#define MEXP_WANGLE      500
#define QUEST_MAV1       "Mavia Letter 1"

#define CHECK_QUEST_8(x) \
(x)->test_bit("Avenir", M_GROUP, MBIT_NOCHIPA)

#define CHECK_QUEST_7(x) \
(x)->test_bit("Avenir", M_GROUP, MBIT_OGRE)

#define CHECK_QUEST_6(x) \
(x)->test_bit("Avenir", M_GROUP, MBIT_WANGLE)
