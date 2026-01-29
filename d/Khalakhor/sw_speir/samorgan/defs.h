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

#define SM_TOWER_BASE      (ROOM + "base-tower")
#define SM_ROOM_BASE       (ROOM + "base-room")
#define SM_SHOP_BASE       (ROOM + "base-shop")
#define SM_HOUSE_BASE      (ROOM + "base-house")
#define SM_STREET_BASE     (ROOM + "base-street")
#define SM_GIRL_HOUSE_BASE (ROOM + "base-girl-house")
#define SM_BOY_HOUSE_BASE  (ROOM + "base-boy-house")

#define SM_PUB             (ROOM + "pub")

#define SAMORGAN_NPC  (NPC + "base-npc")

#define SM_ELF        (NPC + "base-elf")

#define SM_GIRL       (NPC + "base-girl")
#define SM_DRESS_GIRL (NPC + "lynet")
#define SM_GIRLS      ({ SM_DRESS_GIRL, NPC + "amena", NPC + "ceri", NPC + "senga" })

#define SM_BOY        (NPC + "base-boy")
#define SM_EQUIP_BOY  (NPC + "fearghal")
#define SM_BOYS       ({ SM_EQUIP_BOY, NPC + "beineon", NPC + "mael", NPC + "yann"})

#define SM_COURIER_LEVEL     1
#define SM_GUARD_LEVEL       2
#define SM_SERGEANT_LEVEL    3
#define SM_LIEUTENANT_LEVEL  4

#define SM_WARRIOR    (NPC + "base-warrior")
#define SM_GUARD      (NPC + "guard")
#define SM_COURIER    (NPC + "courier")
#define SM_SERGEANT   (NPC + "sergeant")
#define SM_LIEUTENANT (NPC + "lieutenant")

#define SM_ARMOUR      (ARM + "base-armour")
#define SM_CHAINMAIL   (ARM + "mail")
#define SM_LEGGINGS    (ARM + "leggings")
#define SM_HELMET      (ARM + "helm")
#define SM_COIF        (ARM + "coif")
#define SM_SHIELD      (ARM + "shield")
#define SM_DRESS_CLOTH (ARM + "dress-shop-cloth")

#define SM_WEAPON     (WEP + "base-weapon")
#define SM_SWORD      (WEP + "rapier")
#define SM_DAGGER     (WEP + "dagger")
#define SM_SPEAR      (WEP + "spear")
#define SM_POLEARM    (WEP + "partisan")
#define SM_AXE        (WEP + "axe")
#define SM_HAMMER     (WEP + "hammer")

#define PIER_ROOM     (SAMORGAN + "pier/pier_room")
#define UTILS         (SAMORGAN + "utils")

#define SHOP_BUYS_NONE 0
#define SHOP_BUYS_ALL  1
#define SHOP_BUYS_ARM  2
#define SHOP_BUYS_WEP  3

#endif KHALAKHOR_SAMORGAN_DEFS
