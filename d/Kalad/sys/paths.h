/*
   paths.h
   
   Paths of all areas in Kalad.
   
   Fysix@Genesis, Oct 1997
 */
#ifndef _KALAD_PATHS_DEF
#define _KALAD_PATHS_DEF

#define DOMAIN       "Kalad"

#define DOMAIN_DIR   "/d/Kalad/"

// General domain directories
#define COMMON       DOMAIN_DIR + "common/"
#define LIB          DOMAIN_DIR + "lib/"
#define LOG          DOMAIN_DIR + "log/"
#define OPEN         DOMAIN_DIR + "open/"
#define PRIVATE      DOMAIN_DIR + "private/"
#define STD          DOMAIN_DIR + "std/"
#define SYS          DOMAIN_DIR + "sys/"
#define CLONE        DOMAIN_DIR + "clone/"

// Market district
#define MARKET    COMMON + "market/"
// Port district
#define PORT      COMMON + "port/"
// Sewers under city
#define SEWERS    COMMON + "sewers/"
// Central district
#define CENTRAL   COMMON + "central/"
// Tradesmen's district
#define TRADE     COMMON + "trade/"
// Upper class distrcit
#define NOBLE     COMMON + "noble/"
// Caravan district
#define CVAN      COMMON + "caravan/"

#define WILD      COMMON + "wild/"
// Pass northeast of city
#define CPASS     WILD + "pass/"
// Outside the city
#define FARM      WILD + "farm/"
// Empire of Canthyr
#define CANTHYR   COMMON + "canthyr/"
// farmlands area west of city
#define KALDORO   WILD + "wild/pass/kaldoro/"
// Land of Raumdor
#define RAUM      "/d/Raumdor/common/"

// Eastern City of Tyr
#define TYR       COMMON + "tyr/"
// Mountain Dividing Continent
#define RIDGE     COMMON + "ridge/"

// Guilds dir
#define GUILDS    COMMON + "guilds/"
// Zintra Guild
#define ZINTRA    COMMON + "sewers/zintra/"
// Khiraa Guild
#define KHIRAA    GUILDS + "khiraa/"

#endif
