/* created by Arman 22 June 2018
 */

#include <ss_types.h>

#define CLUB                 ("/d/Krynn/clubs/warfare/")

#define CLUB_SOUL            (CLUB + "warfare_club_soul")
#define WAR_OBJ              (CLUB + "warfare_club_obj")
#define WAR_JOINROOM         (CLUB + "warfare_join");
#define LOG                  (CLUB + "log/")
#define CLUBDATA             (CLUB + "data/")
#define CLUBLOG              (LOG + "warfare_log_")
#define LEAVELOG             (LOG + "warfare_log_")

// Master Objects
#define CLUB_MANAGER         (CLUB + "warfare_club_manager")
#define WAR_ARMYMASTER       ("/d/Krynn/common/warfare/armymaster")

#define IS_CLUB_MEMBER(x)    CLUB_MANAGER->query_is_member(x)

#define ARMY_IN_AREA(x)           (WAR_ARMYMASTER->army_in_area(x))
#define CHECK_ARMY_IN_AREA(x, y)  (ARMY_IN_AREA(x) == y)

#define CLUB_DEBUG(x)  find_player("arman")->catch_msg("[Club] " + x + "\n")

#ifndef WARFARE_AREAS
#define WARFARE_AREAS      ({ "Newports Area", \
                              "Solace Area", \
                              "Central Abanasinian Plains", \
                              "North Abanasinian Plains", \
                              "Nightlund Plains", \
                              "Guardlund Plains", \
                              "Western Solamnian Plains", \
                              "Estwilde Plains", \
                              "Throtyl Pass", \
                              "Icewall Plains" })
/* Trelgorn forest isn't conquerable at the moment.
                              "Trelgorn Forest" }) 
*/
#endif

#ifndef WARFARE_ARMIES
#define WARFARE_ARMIES      ({ "Knights", \
                               "Neidar Clan", \
                               "Free People", \
                               "Red Dragon Army", \
                               "Blue Dragon Army", \
                               "Black Dragon Army", \
                               "Green Dragon Army", \
                               "White Dragon Army" })
#endif
