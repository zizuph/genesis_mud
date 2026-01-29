/*
 * General include file for North spier
 * TAPAKAH, 04/2005
 */

#ifndef _N_SPEIR_INCLUDE
#define _N_SPEIR_INCLUDE

#define NSPEIRPATH "/w/tapakah/goblinvillage/src/"

#define INSIDE_VILLAGE "_inside_goblin_village"
#define INSIDE_CAMP    "_inside_goblin_camp"
#define INSIDE_GUILD   "_inside_hammerhand_guild"

#define PIERPATH    NSPEIRPATH + "pier/"
#define VILLAGEPATH NSPEIRPATH + "village/"
#define CAMPPATH    NSPEIRPATH + "camp/"
#define ROADPATH    NSPEIRPATH + "road/"
#define HHPATH      NSPEIRPATH + "hhands/"

#define VILLAGEDEFS VILLAGEPATH + "village.h"
#define CAMPDEFS    CAMPPATH    + "camp.h"
#define PIERDEFS    PIERPATH    + "pier.h"
#define ROADDEFS    ROADPATH    + "road.h"
#define HHDEFS      HHPATH      + "hhands.h"

#define RESIST_LEVEL 100

#define COLD_MANA  30
#define COLD_DAMAGE_BASE 60
#define COLD_DAMAGE_EXTRA 60

#define CONFUSION_MANA 60
#define CONFUSION_DAMAGE 400
#define CONFUSION_LANGUAGE 50
#define CONFUSION_INTELLIGENCE 120
#define CONFUSION_WISDOM_MIN 120
#define CONFUSION_WISDOM_RANDOM 30
#define CONFUSION_COST 300


#define SUFFALIGN -400

#define BS(str) break_string(str,75,0)
#define BSN(str) BS(str) + "\n"

#endif
