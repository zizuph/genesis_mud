/*
 * Anghoth definitions
 *
 *   Alto, 01 June 2002
 *
 */

#ifndef ANGHOTH_DEFS
#define ANGHOTH_DEFS

/* Basic information definitions */

#define DEBUG(x)                 (find_living("alto")->catch_msg(x))

/* Basic directory definitions */

#define ANGHOTH_DIR              "/d/Gondor/clubs/anghoth/"
#define ANGHOTH_BOARD_DIR        (ANGHOTH_DIR + "boards/")
#define ANGHOTH_HELP             (ANGHOTH_DIR + "help/")
#define ANGHOTH_ROOM             (ANGHOTH_DIR + "room/")
#define ANGHOTH_NPC              (ANGHOTH_DIR + "npc/")
#define ANGHOTH_OBJ              (ANGHOTH_DIR + "obj/")
#define ANGHOTH_SOUL_DIR         (ANGHOTH_DIR + "soul/")
#define ANGHOTH_SHADOW_DIR       (ANGHOTH_DIR + "shadow/")

/* Important file definitions */

#define MANAGER                  (ANGHOTH_DIR + "manager")
#define ANGHOTH_SHADOW           (ANGHOTH_SHADOW_DIR + "anghoth_shadow")
#define ANGHOTH_SOUL             (ANGHOTH_SOUL_DIR + "anghoth_soul")
#define ANGHOTH_TOKEN            (ANGHOTH_OBJ + "anghoth_token")
#define ANGHOTH_TOKEN_ID         "_anghoth_token_id"
#define ANGHOTH_KORRAK_TOKEN     (ANGHOTH_OBJ + "korrak_token")
#define ANGHOTH_DATH_TOKEN       (ANGHOTH_OBJ + "dath_token")
#define ANGHOTH_DURUB_TOKEN      (ANGHOTH_OBJ + "durub_token")
#define ANGHOTH_KRIECHEK_TOKEN   (ANGHOTH_OBJ + "kriechek_token")
#define ANGHOTH_ASHUK_TOKEN      (ANGHOTH_OBJ + "ashuk_token")
#define ANGHOTH_START            (ANGHOTH_ROOM + "priv_board_room")
#define MAGE_MANAGER             ("/d/Gondor/guilds/morgulmage/master/master")

/* Log file definitions */

#define ANGHOTH_LOG              (ANGHOTH_DIR + "/log/anghoth_log")
#define LOG_SIZE                 9000

/* Board directories */

#define ANGHOTH_BOARD            (ANGHOTH_BOARD_DIR + "anghoth_board")

/* Miscellaneous definitions */

#define ALIGN_MIN                -100
#define ALIGN_WARN               (ALIGN_MIN - 50)
#define ALIGN_JOIN               (ALIGN_WARN - 50)
#define BANNED_RACE              ({"hobbit", "kender", "elf"})
#define ANGHOTH_SUBLOC           "Anghoth_SubLoc"

/* Valid Anghoth test */

#define NON_ANGHOTH_LEVEL         0
#define KRIECHEK_LEVEL            1
#define KORRAK_LEVEL              2
#define DATH_LEVEL                3
#define DURUB_LEVEL               4

/* Anghoth member macros */
#define ANGHOTH_MEMBER(x)         ((x)->query_anghoth_member())
#define KRIECHEK_MEMBER(x)        (ANGHOTH_MEMBER(x) &&              \
                                        (x)->query_anghoth_level() == \
                                        KRIECHECK_LEVEL)
#define KORRAK_MEMBER(x)          (ANGHOTH_MEMBER(x) &&              \
                                        (x)->query_anghoth_level() == \
                                        KORRAK_LEVEL)
#define DATH_MEMBER(x)            (ANGHOTH_MEMBER(x) &&              \
                                        (x)->query_anghoth_level() == \
                                        DATH_LEVEL)
#define DURUB_MEMBER(x)           (ANGHOTH_MEMBER(x) &&              \
                                        (x)->query_anghoth_level() == \
                                        DURUB_LEVEL)

#endif ANGHOTH_DEFS
