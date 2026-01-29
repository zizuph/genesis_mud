/*
 * party.h
 *
 * This file is included in all party_*.c files and contains necessary
 * definitions.
 */

#define PARTY_DIR	"/d/Shire/open/party/"
#define PARTY_ROOM	(PARTY_DIR + "party_room")
#define PARTY_TOOL	(PARTY_DIR + "party_tool")
#define PARTY_CAKE	(PARTY_DIR + "party_cake")
#define PARTY_ROCKET	(PARTY_DIR + "party_rocket")
#define PARTY_CRACKER	(PARTY_DIR + "party_cracker")
#define PARTY_CHAMPAGNE	(PARTY_DIR + "party_champagne")

#define PARTY_HAT_ID	"party_hat"     /* ID of party hat object */
#define PARTY_TOOL_ID	"_partytool_"   /* ID of partytool */

#define PARTY_LOG	"party"
#define PARTY_LOG_PATH	("/d/Shire/log/" + PARTY_LOG)

#define HOURS_BETWEEN_PARTIES	3	/* Interval between parties */

#define DECISION_TIME 5    /* # of mins you have to type 'party' */
