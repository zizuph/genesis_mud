/*
 * Creator: Shadowlynx
 * Date   : Oct/99
 * File   : /d/Genesis/start/human/sparkle/defs.h
 * Purpose: To be inherited in all Sparkle rooms
 * 
 * Modification log: 2000-03-22 by Jakob
 *                   - Added some defines
 8                   - And changed someothers..
*/

#define DOMAIN                  "Genesis"

// Definitions for directories.

#define GENESIS_DIR "/d/Genesis/"
#define HUMAN       GENESIS_DIR + "start/human/"
#define SPARKLE     HUMAN + "sparkle/"
#define ARMOUR      SPARKLE + "armour/"
#define WEAPON      SPARKLE + "weapon/"
#define BEACH       SPARKLE + "beach/"
#define CAVERNS     SPARKLE + "caverns/"
#define CHURCH      SPARKLE + "church/"
#define DOCKS       SPARKLE + "docks/"
#define ISLAND      SPARKLE + "island/"
#define TRAIN       SPARKLE + "train/"
#define TOWN        SPARKLE + "town/"
#define FOUNTAIN    SPARKLE + "fountain/"
#define GOLD        SPARKLE + "tower_gold/"
#define SILVER      SPARKLE + "tower_silver/"

#define SPARKLE_ROOM  SPARKLE + "room"
#define GENESIS_LOG_DIR 

#define SPARKLE_NPC         SPARKLE + "npc/"
#define SPARKLE_OBJ         SPARKLE + "obj/"
#define SPARKLE_FOOD        OBJ + "food/"
#define SPARKLE_PICS        OBJ + "pics/"

#define TP      this_player()
#define TO      this_object()
#define TI      this_interactive()

#define ENV(x)     environment(x)
#define CAP(x)     capitalize(x)
#define LOW(x)     lower_case(x)
#define NFN(x)     notify_fail((x) + "\n")
#define NF(str)    notify_fail(str)
#define WRITE(x)   this_player()->catch_tell(x)



// Hehe this is Gender discrimination!!! Use HE_SHE instead!
#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()
#define HIM(x)  (x)->query_objective()









