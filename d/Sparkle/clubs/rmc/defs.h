/*
 * RMC Definitions File
 * Rich Men's Club
 * 
 * Created by Conan Aug 29, 1995
 * Modified by Lunatari Dec 14, 2005
 * (In preparation for the move to Sparkle domain)
 */
#include "/d/Sparkle/sys/defs.h"
#include "/d/Genesis/sys/deposit.h"

#include <wa_types.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <money.h>
#include <std.h>

/* Rooms and Object paths */
#define RMCDIR    "/d/Sparkle/clubs/rmc/"
#define RMCLIB    (RMCDIR+"lib/")
#define RMCVAR    (RMCDIR+"var/")
#define RMCLOG    (RMCDIR+"log/")
#define RMCOBJ    (RMCDIR+"obj/")
#define RMCNPC    (RMCDIR+"npc/")
#define RMCROOMS  (RMCDIR+"room/")
#define RMCSOUL   (RMCLIB+"rmcsoul")
#define RMCPURSE  (RMCOBJ+"player_purse")
#define RMC_CLOG  (RMCLOG+"coat.log")
#define RMC_RLOG  (RMCLOG+"rich.log")
#define RMC_PLOG  (RMCLOG+"portals.log")
#define RMC_COAT  (RMCVAR+"coating")
#define RMC_PORT  (RMCVAR+"portals")
#define RMCSHIP   (RMCDIR+"ship/")
#define RMCMASTER (RMCLIB+"master")
#define RMCSAVED  (RMCVAR+"master")
#define RMCNEWS   (RMCVAR+"news")
#define RMCSUBLOC "rich_purse"
#define PURSE_ID  "rich_club_obj"
#define TICKET_ID "rmc_golden_ticket"
#define RMC_TREASURE_ROOM (RMCLIB+"treasure")
#define PURSE_NPC_ID "rich_club_npc_obj"

/* Data Defines */
#define RMC_MEMBER(xxx)   xxx[0]
#define RMC_PAID(xxx)     xxx[1]
#define RMC_ACCOUNT(xxx)  xxx[2]
#define RMC_NOTE(xxx)     xxx[3]
#define RMC_HUMBLE(xxx)   xxx[4]
#define RMC_NEWS(xxx)     xxx[5]
#define RMC_VISIBLE(xxx)  xxx[6]
#define RMC_SUSPEND(xxx)  xxx[7]
#define RMC_PURCHASE(xxx) xxx[8]
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
        "Club Wizard", "Founder and Club Wizard"})

/* Properties */
#define RMC_I_GOLD_COATED "_rmc_i_gold_coated"
    
/* Portals */
#define PORTAL1 "/d/Calia/gelan/rooms/fountain_statue_w"
#define PORTAL2 "/d/Kalad/common/caravan/company/s1"
#define PORTAL3 "/d/Ansalon/taman_busuk/neraka/outer/black/yard.c"

/* Some useful defines */
#define HIS_HER(xxx)     xxx->query_possessive()
#define HIM_HER(xxx)     xxx->query_objective()
#define HE_SHE(xxx)      xxx->query_pronoun()
#define CAP              capitalize
#define ENV              environment
#define CQRLNAME(xxx)    capitalize(xxx->query_real_name())
#define SET_EMOTE        "_live_s_soulextra"
#define RICH_ACCESS(xxx) if (RMCMASTER->query_level(TP->query_real_name()) < xxx) return "No such RMC command.\n"

#define RNAMETAB         if ((strlen(RMC_MEMBER(i)) > 7 && v > 1) || \
                         (strlen(RMC_MEMBER(i)) > 5 && v == 1)) str += "\t"; \
                         else str += "\t\t"
#define NOTHUMBLE        if (RMCMASTER->query_humble(TP->query_real_name())) {\
                         write("It isn't humble to do that!\n");\
                         return 1;}
#define XNOTHUMBLE       if (RMCMASTER->query_humble(TP->query_real_name())) {\
                          return "It isn't humble to do that!\n";}
#define NUM              sizeof(MONEY_TYPES)

/* Log Paths */
#define PORTAL_LOG  RMCLOG+"portal.log"
#define RICHLOG     RMCLOG+"rich.log"
#define COAT_LOG    RMCLOG+"coat.log"

/*
 *  
 * Basic functional defines.
 *   
 */
#define NF(message)     notify_fail(message)
#ifndef TP
#define TP              this_player()
#endif
#define ETP             environment(this_player())
#ifndef TI
#define TI              this_interactive()
#endif
#ifndef TO
#define TO              this_object()
#endif

#define PO              previous_object()
#define ETO             environment(this_object())
#define BS(message)     break_string(message, 75)
#define FIXEUID         setuid(); seteuid(getuid())

/*
 * Attributes
 */
#define INSIDE          add_prop(ROOM_I_INSIDE, 1)
#define OUTSIDE         remove_prop(ROOM_I_INSIDE)
#define DARK            remove_prop(ROOM_I_LIGHT)
#define LIGHT           add_prop(ROOM_I_LIGHT,1)
#define BEACH           add_prop(ROOM_I_TYPE,ROOM_BEACH)
#define WATER           add_prop(ROOM_I_TYPE,ROOM_IN_WATER)
#define NEVERKNOWN      add_prop(LIVE_I_NEVERKNOWN, 1)
#define ALWAYSKNOWN     add_prop(LIVE_I_ALWAYSKNOWN, 1)
