// directory macros:
#define  __DIR                       ("/d/Gondor/common/mordor/")

// include this file in your area defs.h, then
// '#undef DIR' and '#define DIR <area_dir>' to
// make the room macros useful/relocatable.
#define  DIR                         (__DIR)

#define  ROOM                        (DIR + "room/")
#define  OBJ                         (DIR + "obj/")
#define  WEAP                        (DIR + "weapon/")
#define  ARM                         (DIR + "armour/")
#define  NPC                         (DIR + "npc/")
#define  LOG                         (DIR + "log/")

// these directory macros exist for when you've
// redefined DIR
#define  MORDOR_SYS                  (__DIR + "sys/")
#define  MORDOR_STD                  (__DIR + "std/")
#define  MORDOR_LIB                  (__DIR + "lib/")
#define  MORDOR_OBJ                  (__DIR + "obj/")
#define  MORDOR_WEAP                 (__DIR + "weapon/")
#define  MORDOR_ARM                  (__DIR + "armour/")
#define  MORDOR_NPC                  (__DIR + "npc/")
#define  MORDOR_LOG                  (__DIR + "log/")
#define  MORDOR_COMMON               (__DIR + "common/")

// geography directory macros:
#define  GORGOROTH                   (MORDOR_COMMON + "gorgoroth/")
#define  NURN                        (MORDOR_COMMON + "nurn/")
#define  RHUN                        (MORDOR_COMMON + "rhun/")
#define  KHAND                       (MORDOR_COMMON + "khand/")

// utility macros:
#define  SAFE_LOAD(x)                (!catch((x)->load_me()))

// commonly used function macros (for brevity)
#define  TP                          (this_player())
#define  TO                          (this_object())
#define  ENV(x)                      (environment(x))
#define  HIS(x)                      (x->query_possessive())
#define  HIM(x)                      (x->query_objective())
#define  HE(x)                       (x->query_pronoun())
#define  NF(x)                       (notify_fail(x))

// standard properties
#define  ROOM_M_NO_SUN               ("_room_i_no_me_sun")
#define  MORDOR_M_NO_SELL            ("_mordor_m_no_sell")
