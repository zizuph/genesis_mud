#define FD_WEP ( DAENBRAIGHPATH  + "foraois/weps/")
#define FD_ARM ( DAENBRAIGHPATH + "foraois/arms/")
#define FD_NPC ( DAENBRAIGHPATH + "foraois/npcs/")
#define FD_OBJ ( DAENBRAIGHPATH + "foraois/objs/")

// material type of weapon, bronze, iron, steel, tempered steel

// levels of tropps
#define FD_KING	   3
#define	FD_LEADER  2
#define FD_WARRIOR 1
#define FD_SOLDIER 0

// human section of defs 

#define FD_H_STR 100
#define FD_H_DEX 95
#define FD_H_CON 100
#define FD_H_INT 60
#define FD_H_WIS 55
#define FD_H_DIS 90

// skills per level
// king = 90/90/80 + max. 5
// leader = 86/80/70 + max. 5
// warrior = 73/70/60 + max. 5
// soldier = 60/60/50 + max. 5
 
#define FD_H_LEVEL_SWORD(x)  (60 + (30 * (x)/3) + random(6))
#define FD_H_LEVEL_DEF(x)    (60 + (30 * (x)/3) + random(6))
#define FD_H_LEVEL_PARRY(x)  (50 + (30 * (x)/3) + random(6))
#define FD_H_LEVEL_AWARE(x)  (40 + (15 * (x)/3) + random(4))

// elves section of defs 

#define FD_E_STR 100
#define FD_E_DEX 95
#define FD_E_CON 100
#define FD_E_INT 60
#define FD_E_WIS 55
#define FD_E_DIS 90

// skills per level
// king = 90/90/80 + max. 5
// leader = 86/80/70 + max. 5
// warrior = 73/70/60 + max. 5
// soldier = 60/60/50 + max. 5
 
#define FD_E_LEVEL_SWORD(x)  (60 + (30 * (x)/3) + random(6))
#define FD_E_LEVEL_DEF(x)    (60 + (30 * (x)/3) + random(6))
#define FD_E_LEVEL_PARRY(x)  (50 + (30 * (x)/3) + random(6))
#define FD_E_LEVEL_AWARE(x)  (70 + (20 * (x)/3) + random(4))

