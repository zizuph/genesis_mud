/* created by Aridor, 12/02/93 */

/*The definition file for the Knights' Club*/

#include "../local.h"    /*TDIR and ROOM should be defined in here*/
#include <std.h>

#define CLUB_LIMIT           40 /*default: max. 30 members*/
#define MIN_REQUIRE          20 /*default: 10 half hours: 5 hours playing in 21 days*/
#define TWENTY_ONE_DAYS      1814400 /*1209600 seconds in 14 days, 1814400 seconds in 21 days*/
#define SEC_PER_30_MIN       1800 /*1800 seconds in 30 minutes*/
#define CLUB                 TDIR + "club/"
#define SLEEP                CLUB + "club2"
#define LOG                  CLUB + "log/"
#define IN_CLUB              "knight_club_membership_token"
#define CLUB_SOUL            CLUB + "club_soul"
#define SCABBARD             CLUB + "club_obj"
#define CLUBMASTER           CLUB + "clubmaster"
#define CLUBLOG              LOG + "_club_log"
#define LEAVELOG             LOG + "_leave_log"
#define MEMBER_FILE          LOG + "_member_file"

#define CLUB_S_SCABBARD_LOCATION "_club_s_scabbard_location"
#define CLUB_O_SHEATHED_WEAPON   "_club_o_sheathed_weapon"
#define CLUB_M_TMP_NO_DROP       "_club_m_tmp_no_drop"  /*did the weapon have no_drop set already?*/

#define OUTSIDE_THE_CLUB     ROOM + "knight1"

#define IS_CLUB_MEMBER(pl)   present(IN_CLUB, pl)
#define SLEEP_PRICE_MEM      10
#define SLEEP_PRICE          120

