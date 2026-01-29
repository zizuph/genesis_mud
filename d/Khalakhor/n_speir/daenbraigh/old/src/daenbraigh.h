/*
 * General include file for Daenbraigh
 * TAPAKAH, 04/2005
 */

#ifndef _DAENBRAIGH_INCLUDE
#define _DAENBRAIGH_INCLUDE

#define DAENBRAIGHPATH ("/d/Khalakhor/n_speir/daenbraigh/src/")

#define INSIDE_VILLAGE ("_inside_goblin_village")
#define INSIDE_CAMP    ("_inside_goblin_camp")
#define INSIDE_GUILD   ("_inside_hammerhand_guild")
#define INSIDE_FOREST  ("_inside_foraois")
#define GV_ENEMY       ("_goblin_village_enemy")

#define PIERPATH    (DAENBRAIGHPATH + "pier/")
#define VILLAGEPATH (DAENBRAIGHPATH + "village/")
#define CAMPPATH    (DAENBRAIGHPATH + "camp/")
#define HHANDSPATH  (DAENBRAIGHPATH + "hhands/")
#define FORESTPATH  (DAENBRAIGHPATH + "foraois/")

#define DAENBRAIGH_BASE (DAENBRAIGHPATH + "daenbraigh")
#define DAENBRAIGH_NPC  (DAENBRAIGHPATH + "daenbraigh_npc")
#define FACTION         (DAENBRAIGHPATH + "faction")

#define NF0(text) {notify_fail(text); return 0;}
				 
#endif
