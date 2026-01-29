#ifndef _KHALAKHOR_QUEST_DEFS_
#define _KHALAKHOR_QUEST_DEFS_

#define QUEST_MASTER      "/d/Khalakhor/sys/global/quest_master"

/*  The following 3 defines are shortcuts to the actual functions for
 *  the quest master and are to be used in quest code. If you need a
 *  more detailed description of what these functions do then check
 *  the function headers in the source code.
 */
#define CHECK_QUEST(player, quest_name) \
          QUEST_MASTER->check_quest(player, quest_name)
#define REWARD_QUEST(player, quest_name) \
          QUEST_MASTER->reward_quest(player, quest_name)
#define VARIABLE_REWARD_QUEST(player, quest_name, exp) \
          QUEST_MASTER->reward_quest(player, quest_name, exp)

/* These defines are used to administer quests with the
 * quest master. (Ideally used with exec so you don't have to use Call)
 * If you are not liege or Steward of Khalakhor these defines are
 * useless to you.
 */
#define ADD_QUEST(short_name, group, bit, exp, long_name) \
          (int)QUEST_MASTER->add_quest(short_name,group,bit,exp,long_name)
#define CLOSE_QUEST(short_name)  (int)QUEST_MASTER->close_quest(short_name)
#define LIST_QUESTS              (int)QUEST_MASTER->list("quests")
#define LIST_BITS                (int)QUEST_MASTER->list("bits") 
#define OPEN_QUEST(short_name)   (int)QUEST_MASTER->open_quest(short_name)
#define REMOVE_QUEST(short_name) (int)QUEST_MASTER->remove_quest(short_name)

// No more defines after this line
#endif
