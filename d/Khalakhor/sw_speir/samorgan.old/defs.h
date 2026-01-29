#ifndef KHALAKHOR_SAMORGAN_DEFS
#define KHALAKHOR_SAMORGAN_DEFS

#include "/d/Khalakhor/sw_speir/defs.h"

/* Global coords for SaMorgan. */
#define SAMORGAN_COORDS ({0, 0});

/* A few path shortcuts. */
#define ARM           (SAMORGAN + "arm/")
#define FISH          (SAMORGAN + "fishing/")
#define MON           (SAMORGAN + "mon/")
#define NPC           (SAMORGAN + "npc/")
#define ROOM          (SAMORGAN + "room/")
#define SCROLLS       (SAMORGAN + "scrolls/")
#define SMLIB         (SAMORGAN + "lib/")
#define SMLOG         (SAMORGAN + "log/")
#define SMOBJ         (SAMORGAN + "obj/")
#define WEP           (SAMORGAN + "wep/")

#define SAMORGAN_BASE (SAMORGAN + "samorgan")

#define BEACH_BASE    (ROOM + "beach_base")
#define BEACHBASE     (ROOM + "beachbase")
#define VILLAGE_ROOM  (ROOM + "village_room")

#define SAMORGAN_NPC  (NPC + "base_npc")
#define SM_WARRIOR    (NPC + "base_warrior")
#define SM_GUARD      (NPC + "guard")
#define SM_COURIER    (NPC + "courier")
#define SM_SERGEANT   (NPC + "sergeant")
#define SM_LIEUTENANT (NPC + "lieutenant")

#define SM_CHAINMAIL  (ARM + "chainmail")
#define SM_LEGGINGS   (ARM + "leggings")
#define SM_HELMET     (ARM + "helmet")
#define SM_SHIELD     (ARM + "shield")
    

#define SM_SWORD      (WEP + "sword")
#define SM_DAGGER     (WEP + "dagger")
#define SM_SPEAR      (WEP + "spear")
#define SM_HALBERD    (WEP + "halberd")

#define PIER_ROOM     (SAMORGAN + "pier/pier_room")
#define UTILS         (SAMORGAN + "utils")

#endif KHALAKHOR_SAMORGAN_DEFS
