/* Definitions for the Gondor domain
 */

#define OSG_DIR "/d/Gondor/anorien/osgiliath/"
#define MINAS_DIR "/d/Gondor/minas/"
#define MORGUL_DIR "/d/Gondor/morgul/"
#define RANGER_DIR "/d/Gondor/common/guild/"
#define RANGER_LOG "/d/Gondor/log/guild"
#define RANGER_ITH_DIR   RANGER_DIR + "ithilien/"
#define RANGER_NORTH_DIR RANGER_DIR + "north/"
#define RANGER_HELP_DIR  RANGER_DIR+"txt/"
#define MAGES_DIR "/d/Gondor/common/guild2/"
#define SHADES_DIR MINAS_DIR+"shades/"
#define EDORAS_DIR "/d/Gondor/rohan/edoras/"
#define ISEN_DIR "/d/Gondor/rohan/isengard/"
#define ORTHANC_DIR ISEN_DIR+"orthanc/"
#define ORTHANC_LVL1 ORTHANC_DIR+"1/"
#define ORTHANC_LVL2 ORTHANC_DIR+"2/"
#define ORTHANC_LVLG ORTHANC_DIR+"g/"
#define NPC_DIR "/d/Gondor/common/npc/"
#define HERB_DIR "/d/Gondor/common/herbs/"
#define SHIRE_HERB_DIR "/d/Shire/common/herbs/"
#define WEP_DIR "/d/Gondor/common/wep/"
#define OBJ_DIR "/d/Gondor/common/obj/"
#define ARM_DIR "/d/Gondor/common/arm/"
#define ITH_DIR "/d/Gondor/ithilien/"
#define MORDOR_DIR "/d/Gondor/mordor/"
#define UNGOL_DIR MORDOR_DIR + "ungol/"
#define LAIR_DIR UNGOL_DIR + "lair/"
#define ROH_DIR "/d/Gondor/rohan/"
#define DUN_DIR "/d/Gondor/dunland/"
#define ANO_DIR "/d/Gondor/anorien/"
#define WT_DIR "/d/Gondor/minas/citadel/tower/"
#define PEL_DIR ANO_DIR+"pelennor/"
#define LEB_DIR "/d/Gondor/lebennin/"
#define QUEST_LOG "/d/Gondor/log/quest"
#define LOG_DIR "/d/Gondor/log/"
#define SOUL_FILE RANGER_DIR+"ranger_soul"
#define RANGER_GUILD "/d/Gondor/common/guild/recruithall"
#define FARM_DIR ROH_DIR + "farm/"
/* ALL boards are kept in the RANGER_DIR! */
#define BOARD_DIR RANGER_DIR + "boards/"

/* Macros */

#define TP this_player()
#define TI this_interactive()
#define TO this_object()
#define BS(xxx) break_string(xxx, 75)
#define BSN(xxx) BS(xxx) + "\n"
#define NF(xxx) notify_fail(xxx)
#define ENV(xx) environment(xx)
#define CAP(xx) capitalize(xx)
#define LOW(xx) lower_case(xx)

#define POSSESSIVE(x) x->query_possessive()
#define OBJECTIVE(x)  x->query_objective()
#define PRONOUN(x)    x->query_pronoun()

#define SET_MAX_HP; set_hp(query_max_hp());

#define QRACE(x) x->query_race_name()

#include "/d/Gondor/met_defs.h"

/* props */

#define BEACH     add_prop(ROOM_I_TYPE,ROOM_BEACH)
