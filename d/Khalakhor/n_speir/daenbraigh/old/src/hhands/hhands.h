/*
 * Include file for hammerhands' rooms
 * TAPAKAH, 10/2005
 */

#ifndef _DAENBRAIGH_HHANDS
#define _DAENBRAIGH_HHANDS 1

#include "../daenbraigh.h"

#define HHANDS_NAME "Hammerhands"

#define HH_INSIDE   ("_hammerhands_inside")
#define HH_MEMBER   ("_hammerhands_member")
#define HH_PROPERTY ("_hammerhands_property")

#define HH_OBJS  (HHANDSPATH + "objs/")
#define HH_NPCS  (HHANDSPATH + "npcs/")
#define HH_WEPS  (HHANDSPATH + "weps/")
#define HH_ARMS  (HHANDSPATH + "arms/")
#define HH_ROOM  (HHANDSPATH + "room/")
#define HH_DATA  (HHANDSPATH + "data/")
#define HH_TEXT  (HHANDSPATH + "text/")
#define HH_GUILD (HHANDSPATH + "hhnd/")

#define HH_PUBLIC_BOARD   (HHANDSPATH + "pbbd/")
#define HH_PRIVATE_BOARD  (HHANDSPATH + "prbd/")

#define HH_PATH_BASE (HH_ROOM + "path")
#define HH_GUILDROOM (HH_ROOM + "guildroom")

#define HH_OBJID     ("_hammerhands")

#define HH_CHAINMAIL (HH_ARMS + "chainmail")
#define HH_HELMET    (HH_ARMS + "helmet")
#define HH_SHIELD    (HH_ARMS + "shield")
#define HH_CLOAK     (HH_ARMS + "cloak")

#define HH_CLUB      (HH_WEPS + "club")
#define HH_SCLUB     (HH_WEPS + "sclub")

#define HH_GUARD    (HH_NPCS + "guard")
#define HH_GM       (HH_NPCS + "gm")
#define HH_SHKPR    (HH_NPCS + "shopkeeper")
#define HH_TRAIN    (HH_NPCS + "trainer")

#define HH_PACK     (HH_OBJS + "pack")
#define HH_TORCH    (HH_OBJS + "torch")
#define HH_LAMP     ("/d/Gondor/common/obj/oil_lamp")
#define HH_FLASK    ("/d/Gondor/common/obj/oilflask")
#define HH_STONE    (HH_OBJS + "whetstone")
#define HH_RACK     (HH_OBJS + "rack")

#define HH_LISTED   (HH_GUILD + "data/listed")

#define HH_RACKMAP  (HH_DATA + "rackmap")

#define HH_ACCESS_ALL     (0)
#define HH_ACCESS_MEMBER  (1)
#define HH_ACCESS_COUNCIL (2)

#define HH_GUARD_ADJ (({"burly","confident","thick-armed","musclebound"}))

#define HH_ACLASS (30)
#define HH_WCLASS (35)

#endif
