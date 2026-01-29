/*
 * Filename:       warfare.h
 * Description:    Should hold definitions for the warfare module
 *
 * Added to warfare module by Boron, Oct 25 1999
 *
 */
#ifndef WARFARE_DEFINES
#define WARFARE_DEFINES

#define WARFARE_ENABLED    1
#define WAR_PATH    "/d/Shire/moria/warfare/"

#define ARMY_PATH   (WAR_PATH + "armies/")
#define AREA_PATH   (WAR_PATH + "areas/")
#define REWARDS_PATH (WAR_PATH + "rewards/")

/* Army master */
#ifndef ARMYMASTER
#define ARMYMASTER  (WAR_PATH + "armymaster")
#endif

#define ARMY_BASE   (WAR_PATH + "army")
#define AREA_BASE   (WAR_PATH + "area")
#define AUTO_RECRUIT (WAR_PATH + "auto_recruit")

#define RECRUITBASE (WAR_PATH + "recruit_base")
#define WARSHOP     (WAR_PATH + "std/warshop")

/* Warfare areas */
#define WAR_AREA_NEWPORT      "Newports Area"
#define WAR_AREA_WESTSOL      "Western Solamnian Plains"
#define WAR_AREA_ESTWILDE     "Estwilde Plains"
#define WAR_AREA_SOLACE       "Solace Area"
#define WAR_AREA_CENTRAL_ABANASINIA    "Central Abanasinian Plains"
#define WAR_AREA_NORTH_ABANASINIA      "North Abanasinian Plains"
#define WAR_AREA_NIGHLUND     "Nightlund Plains"
#define WAR_AREA_GUARDLUND    "Guardlund Plains"
#define WAR_AREA_THROTYL      "Throtyl Pass"
#define WAR_AREA_ICEWALL       "Icewall Plains"
#define WAR_AREA_TRELGORN     "Trelgorn Forest"
/* Old warfare area names (should not be used) */
#define WAR_AREA_ABANASINIAN  "Abanasinian Plains"
#define WAR_AREA_EASTSOL      "Eastern Solamnian Plains"


/* Army names */
#define FREE_ARMY   "Free People"

#define KNIGHT_ARMY "Knights"
#define NEIDAR_ARMY "Neidar Clan"

#define RED_ARMY    "Red Dragon Army"
#define BLUE_ARMY   "Blue Dragon Army"
#define BLACK_ARMY  "Black Dragon Army"
#define GREEN_ARMY  "Green Dragon Army"
#define WHITE_ARMY  "White Dragon Army"


/* Guild names */
#define NEIDAR_GUILD      "Dwarven Warriors of the Neidar Clan"
#define SOLAMNIAN_KNIGHTS "Solamnian Knights"

/* Peace year (no war in or before this year) */
#define PEACE_YEAR  353

/*
 * Default recruit amount and tax amount
 */
#define DEFAULT_TAX_BASE      1010
#define DEFAULT_RECRUIT_BASE  6

/* The price of the unit is calculated with this
 * price - the base unit price
 * units - number of units in the area
 */
#define UNIT_PRICE(price, units)  ((price) * pow((units) + 1.0, 1.4) / \
                                   ((units) + 1.0))

/*
 * The recruit rate drops as the number of recruits increase, this gives
 * an absolute max of 400 but the real one is probably around 200. 
 */
#define RECRUIT_RATE(base, recruits) ((base) * pow((recruits), \
                                                   -((recruits) / 400.0)))

#define W_LOG           (WAR_PATH + "war.log")
#define C_LOG           (WAR_PATH + "war_conq.log")
//#define DEBUG(x)	find_player("cotillion")->catch_tell(x)
#define WAR_LOG(x)      write_file(W_LOG, ctime(time()) + ": " + (x) + "\n")
#define CONQ_LOG(x)     write_file(C_LOG, ctime(time()) + ": " + (x) +"\n")


#endif

