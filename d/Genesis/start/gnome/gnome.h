/*
 * Path names :
 * (inherit must have absolute path)
 */

#define BASE_DIR "/d/Genesis/start/gnome/"

#define ROOM_DIR  (BASE_DIR + "room/")
#define OBJ_DIR   (BASE_DIR + "obj/")
#define STUFF_DIR (BASE_DIR + "stuff/")

#define LIB      "/d/Genesis/start/gnome/stuff/lib.c"
#define TRANSACT "/d/Genesis/start/gnome/stuff/transact.c"
#define CITIZEN  "/d/Genesis/start/gnome/stuff/citizen.c"
#define MERCHANT "/d/Genesis/start/gnome/stuff/merchant.c"

#define GUARD_POOL      (STUFF_DIR + "guard_pool")
#define GUARD_OBJECT    (STUFF_DIR + "guard")

#define STORY_FILE      (STUFF_DIR + "gnomestory")
#define GUARD_NAME_FILE (STUFF_DIR + "guardnames")

/*
 * Some horrible thingies.
 */

#define BS(x)       break_string(x, 70)
#define SHAKE(a, v) (a + random(2 * v + 1) - v)

#define M_Emote(x)  write(BS(M_Keeper + " " + x));
#define M_Tell(x)   M_Emote("tells you: " + x)
#define M_Keeper    short()

#define DEFAULT_GUARD_SETTINGS ({ 14, ({ OBJ_DIR + "chainmail",\
                                         OBJ_DIR + "axe" }),\
                                      ({ "wear chainmail", "wield axe" }),\
                                  this_object() })

#define QG_STATUE 3
#define QB_STATUE 0

#define GUARD_VARIANCE 10

#define GNOME_DELAY 6
