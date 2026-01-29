#ifndef _AVENIR_WATER_H_
#define _AVENIR_WATER_H_

#define MBW_CHECK_ID	"ave::magic::breathe"
#define MBW_OBJECT	"/d/Avenir/common/herbs/water_res"

/* Seconds of MBW prop for eating 1 nethra herb. */
/* 5 - 10 mins duration */
#define MBW_NETHRA	(300 + random(301))
/* Seconds of MBW prop per Hizarbin blessing. */
/* 15 - 45 mins duration */
#define MBW_HIZARBIN	(900 + random(2701))

/* A couple shortcut defines. */
#define IN_WATER(x)	((x)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
#define UNDER_WATER(x)	((x)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)

#endif /* _AVENIR_WATER_H_ */
