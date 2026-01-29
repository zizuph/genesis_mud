#ifndef QUEST_HANDLER_DEFS

#define QUEST_HANDLER_DEFS

/* The directory where the quest_handler files are kept */
#define QH_HANDLER_DIR      "/d/Earthsea/quest_handler/"

/* Path to the quest_handler itself */
#define QH_HANDLER_FILENAME (QH_HANDLER_DIR + "quest_handler")

/* Path to the quest_handler save file */
#define QH_SAVE_FILENAME    QH_HANDLER_FILENAME

/* Directory where the quest logs are saved */
#define QH_LOG_DIR          "/d/Earthsea/log/quests/"

/* Path to the master log file */
#define QH_MASTER_LOG (QH_LOG_DIR + "quest.log")

/* Maximum size of the master log */
#undef QH_MASTER_SIZE 45000

/* Macro that converts a quest name into the path to the
 * quest's data file
 */
#define QH_DATA_FILE(quest) (QH_LOG_DIR + quest + ".o")

/* Macro that restores the data for the given quest */
#define QH_RESTORE_DATA_FILE(quest) \
    (restore_map(QH_LOG_DIR + quest))

/* Macro that saves the data for the given quest */
#define QH_SAVE_DATA_FILE(quest, data) \
    (save_map(data, QH_LOG_DIR + quest))

/* Macro that converts a quest name into the path to the
 * quest's log file
 */
#define QH_LOG_FILE(quest)  (QH_LOG_DIR + quest + ".log")

/* Use this when a player has completed a quest to set bits,
 * add experience, log, etc. (see quest_completed() in the
 * quest_handler)
 */
#define QH_QUEST_COMPLETED(player, quest) \
    QH_HANDLER_FILENAME->quest_completed(player, quest)

/* Use this to find out if a player has completed a particular
 * quest. (see query_quest_completed() in the quest_handler)
 */
#define QH_QUERY_QUEST_COMPLETED(player, quest) \
    QH_HANDLER_FILENAME->query_quest_completed(player, quest)

#endif
