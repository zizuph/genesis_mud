
/* local.h directory for KENDERMORE: 05/14/99 */

#ifndef KENDERMORE_DEF
#define KENDERMORE_DEF

#define KPATH      "/d/Ansalon/goodlund/kendermore"
#define KROOM      KPATH + "/room/"
#define KLOG       KPATH + "/log/"
#define KOBJ       KPATH + "/obj/"
#define KNPC       KPATH + "/living/"
#define FFROOM     "/d/Ansalon/balifor/flotsam_forest/room/"

#define STDDOOR "/d/Ansalon/std/door"

#define NORMAL_BOARD   KLOG + "boards/normal"

#define KENDERMORE_OUT KPATH + "/std/o_room_base"
#define KENDERMORE_IN  KPATH + "/std/i_room_base.c"
#define STREET_DESC    KPATH + "/std/look_out_base.c"
#define QEXITS         KPATH + "/std/qexits.c"
#define KMASTER        "/d/Ansalon/guild/society/room/vote_room"

/* Key defines */
#define BOX_KEY 7118768
#define FOO_BAR 7110091
#endif KENDERMORE_DEF

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif
