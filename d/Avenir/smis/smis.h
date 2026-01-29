// file name:        /d/Avenir/smis/smis.h
// creator(s):       Denis May'96
// purpose:          SMIS basic definitions.
/*
 * Revisions:
 *     Lucius, Jul 2017: Cleanups. Moved modules.h contents here.
 */
#ifndef SMIS_HEADER
#define SMIS_HEADER

#define SMIS_VERSION			"1.21"

/* Localized
 */
#define SMIS_DIR			"/d/Avenir/smis/"
#define SMIS_QUEST_LOG		        "/d/Avenir/log/quest/quests"

/* SMIS object files.
 */
#define SMIS				(SMIS_DIR + "smis")
#define SMIS_MANAGER			(SMIS_DIR + "smis_mgr")
#define SMIS_CMDSOUL			(SMIS_DIR + "smiscmd")
#define SMIS_MODULE			(SMIS_DIR + "module")
#define SMIS_MANIP			(SMIS_DIR + "manip")
#define SMIS_ROOM			(SMIS_DIR + "smis_room")

/* Placer definitions.
 */
#define SMIS_MODULE_PLACER		(SMIS_DIR + "std/placer_mod")
#define SMIS_MODULE_QUEST		(SMIS_DIR + "std/quest_mod")

#endif
