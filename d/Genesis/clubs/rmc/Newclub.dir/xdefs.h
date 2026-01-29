/*
 *      RICH CLUB DEFINE FILE
 *   Created by Conan Aug 29, 1995
 */

#include "/d/Immortal/std/domain.h"

/* Rooms and Object paths */
#define RICHCLUB          "/d/Immortal/rclub/Newclub.dir/"
#define RICH_OBJ          RICHCLUB+"richclub"
#define RICHPURSE         RICHCLUB+"richpurse"
#define RICH_OBJ          RICHCLUB+"richclub"
#define IMMISLAND         "/d/Immortal/island/"
#define RICH_ROOM         RICHCLUB+"richclub"
#define RICHROOM          RICHCLUB+"newrich"
#define ACCOUNTS          "/d/Genesis/obj/accounts"
#define COAT_OBJ          RICHCLUB+"coat"
#define RICHSOUL          RICHCLUB+"richsoul"
#define RMC_TREASURE_ROOM RICHCLUB+"rmaster"
#define RMC_PURGE_LOG     RICHCLUB+"dested.backup"

/* Data Defines */
#define RMC_PAID(xxx)     rdata[xxx][0]
#define RMC_JOINED(xxx)   rdata[xxx][1]
#define RMC_ACCOUNT(xxx)  rdata[xxx][2]
#define RMC_NOTE(xxx)     rdata[xxx][3]
#define RMC_HUMBLE(xxx)   rdata[xxx][4]
#define RMC_NEWS(xxx)     rdata[xxx][5]
#define RMC_VISIBLE(xxx)  rdata[xxx][6]
#define RMC_SUSPEND(xxx)  rdata[xxx][7]
#define RMC_PURCHASE(xxx) rdata[xxx][8]
#define RICH_NOTIFY_MSG ({"You feel a minor shift in the market",\
        "You feel a small shift in the market",\
        "You feel a shift in the market",\
        "You feel a big shift in the market",\
        "You feel a great shift in the market",\
        "You feel a tremendous shift in the market",\
        "You feel a gigantic shift in the market",\
        "You feel a divine shift in the market",\
        "You feel an uproar in the market",})
#define RMC_TITLE ({"Poor Member", "Average Member", "Wealthy Member", \
        "Extremely Wealthy Member", "Obscenely Wealthy Member", \
        "Filthily Rich Member", "Big Shot", "Vice-President", \
        "President", "Disgustingly Rich Member", "Divine Member", \
        "Co-Wizard", "Founder and Club Wizard"})

/* Properties */
#define RMC_I_GOLD_COATED "_rmc_i_gold_coated"
    
/* Portals */
#define PORTAL1 "/d/Calia/gelan/rooms/fountain_statue_w"
#define PORTAL2 "/d/Kalad/common/caravan/company/s1"
#define PORTAL3 "/d/Krynn/neraka/dragon/landing1.c"

/* Some useful defines */
#define HIS_HER(xxx)     xxx->query_possessive()
#define HIM_HER(xxx)     xxx->query_objective()
#define HE_SHE(xxx)      xxx->query_pronoun()
#define CAP              capitalize
#define ENV              environment
#define CQRLNAME(xxx)    capitalize(xxx->query_real_name())
#define SET_EMOTE        "_live_s_soulextra"
#define RICH_ACCESS(xxx) xnf="No such RMC command.\n";if(level<xxx) return 0
#define RNAMETAB         if ((strlen(RMC_MEMBER(i)) > 7 && v > 1) || \
                         (strlen(RMC_MEMBER(i)) > 5 && v == 1)) str += "\t"; \
                         else str += "\t\t"
#define NOTHUMBLE        if ((RICHROOM)->query_humble(TP)) {\
                         write("It isn't humble to do that!\n");\
                         return 1;}
#define XNOTHUMBLE       xnf = "It isn't humble to do that!\n";if (r_humb) {\
                          return 0;}
#define NUM              sizeof(MONEY_TYPES)

/* Log Paths */
#define PORTAL_LOG  RICHCLUB+"portal.log"
#define RICHLOG     RICHCLUB+"rich.log"
#define COAT_LOG    RICHCLUB+"coat.log"
