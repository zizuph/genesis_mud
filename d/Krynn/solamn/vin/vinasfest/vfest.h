#ifndef VFEST_DEFS
#define VFEST_DEFS

#define VFEST ("/d/Raumdor/open/special/vfest/")

#define WATCH  (VFEST + "melee")
#define MELEE  (VFEST + "melee")
#define STANDS (VFEST + "stands")

#define SHADOW (VFEST + "shadow")
#define STONE1 (VFEST + "stone1")
#define STONE2 (VFEST + "stone2")

#define VFEST_START (VFEST + "lawn")
#define LIVE_O_ROOM_BEFORE_VFEST  "_live_o_room_before_vfest"

#define INVITATION  (VFEST+ "invite")
#define GARLAND_PATH  (VFEST + "garland")
#define GARLAND_LIMIT ({ 2, 150, "You have taken enough garland, leave "+ \
	"some for others.\n", "Sorry, the basket is empty at this "+ \
	"time.\n" })
#define CAP(x)     capitalize(x)
#define ENV(x)     environment(x)
#define HIMM(x)    x->query_objective()

#endif VFEST_DEFS