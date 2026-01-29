/* Domain defs */

#include <stdproperties.h>
#include "/d/Krynn/common/warfare/warfare.h"

#ifndef KRYNN_DEF
#define KRYNN_DEF

/* Props */
#define LIVE_I_NO_DRAGONFEAR   ("_live_i_no_dragonfear")
#define LIVE_O_KRYNN_DRAGON    ("_live_o_krynn_dragon")
#define ROOM_I_NO_TIME         ("_room_i_no_time")
#define ROOM_I_SUNLIGHT        ("_room_i_sunlight")
#define OBJ_I_COLORABLE        ("_obj_i_colorable")
#define OBJ_I_COLOURABLE       ("_obj_i_colorable")

/* Krynn general defines */
#define TP           this_player()
#define TI           this_interactive()
#define TO           this_object()
#define ADD(xxx,yyy) add_action(xxx, yyy);
#define ADA(xxx)     add_action(xxx, xxx);
#define NF(xxx)      notify_fail(xxx);
#define BS(xxx,nn)   break_string(xxx + "\n", nn)
#define C(xxx)       capitalize(xxx)
#define P(str, ob)   present(str, ob)
#define E(ob)        environment(ob)
#define L(str)       lower_case(str)
#define BSN(x)       BS(x,75)

#define POSSESSIVE(x) ((x)->query_possessive())
#define HIS(x)        ((x)->query_possessive())
#define OBJECTIVE(x)  ((x)->query_objective())
#define HIM(x)        ((x)->query_objective())
#define HIMSELF(x)    ((x)->query_objective() + "self")
#define PRONOUN(x)    ((x)->query_pronoun())
#define HE(x)         ((x)->query_pronoun())
#define REALAGE(x)    ((x)->query_age() * 2)
#define QRACE(x)      (x)->query_race_name()
#define QREALRACE(x)  (x)->query_race()

#define ONE_OF(x)     ((x)[random(sizeof(x))])


#define UNIQUE(filen,num,alternatefile) ((!((filen)->load_file()) && \
                        sizeof(filter(object_clones(find_object(filen)), \
                        (&operator(==)(0) @ &->query_prop("_obj_i_broken")))) \
            < num) ? filen : alternatefile)

/* Special output possibilities for dark rooms and invisible livings.
 * This SHOULD be used everywhere instead of the normal functions. These
 * definitions have been developed by /Mercade and were taken from his
 * met_defs.h file.
 */
#define METNAMEI(x)        ((x)->query_name())
#define NONMET(x)          ((x)->query_nonmet_name())
#define TNONMET(x)         ("the " + NONMET(x))
#define CTNONMET(x)        ("The " + NONMET(x))

#define SAY(x) say(({BSN(METNAMEI(TP) + x), \
    BSN(CTNONMET(TP) + x), \
    BSN("Someone" + x)}))
#define SAYBB(x) say(({BSN(METNAMEI(TP) + x), \
    BSN(CTNONMET(TP) + x), ""}))

#define LSAY(x, y) say(({BSN(x + METNAMEI(TP) + y), \
    BSN(x + TNONMET(TP) + y), \
    BSN(x + "someone" + y)}))
#define LSAYBB(x, y) say(({BSN(x + METNAMEI(TP) + y), \
    BSN(x + TNONMET(TP) + y), ""}))

#define CATCH_MSG(o, x) catch_msg(({BSN(METNAMEI(o) + x), \
    BSN(CTNONMET(o) + x), \
    BSN("Someone" + x)}))
#define CATCH_MSGBB(o, x) catch_msg(({BSN(METNAMEI(o) + x), \
    BSN(CTNONMET(o) + x), ""}))

#define LCATCH_MSG(o, x, y) catch_msg(({BSN(x + METNAMEI(o) + y), \
    BSN(x + TNONMET(o) + y), \
    BSN(x + "someone" + y)}))
#define LCATCH_MSGBB(o, x, y) catch_msg(({BSN(x + METNAMEI(o) + y), \
    BSN(x + TNONMET(o) + y), ""}))

#define TELL_ROOM(r, o, x, n) tell_room(r, ({BSN(METNAMEI(o) + x), \
    BSN(CTNONMET(o) + x), \
    BSN("Someone" + x)}), n)
#define TELL_ROOMBB(r, o, x, n) tell_room(r, ({BSN(METNAMEI(o) + x), \
    BSN(CTNONMET(o) + x), ""}), n)

#define LTELL_ROOM(r, o, x, y, n) tell_room(r, ({BSN(x + METNAMEI(o) + y), \
    BSN(x + TNONMET(o) + y), \
    BSN(x + "someone" + y)}), n)
#define LTELL_ROOMBB(r, o, x, y, n) tell_room(r, ({BSN(x + METNAMEI(o) + y), \
    BSN(x + TNONMET(o) + y), ""}), n)

/*
Planed usage:
In create_krynn_monster()  you do:
add_emote_hook("nod", 2.0, do_nod);
add_emote_hook("smile", 1.5, do_smile);
add_emote_hook("grin", 3.0, do_smile);
add_emote_adverb_hook("kindly", 2.0, do_smile);
add_emote_adverb_hook("shyly", 2.0, do_smile);

And then somewhere outside you do:
EMOTE_HOOK

The functions that gets called should look like this:
public void
do_smile(object actor, string adverb)
{
....
}

Nothing more and nothing less...
*/

#define EMOTE_HOOK \
public void \
emote_hook(string emote, object actor, string adverb) \
{ \
    mixed t; \
    function f; \
    if (pointerp((t = gNpc_emotes[emote]))) \
    { \
    f = t[1]; \
    set_alarm(t[0], 0.0, &f(actor, adverb)); \
    } \
    else \
    if (pointerp((t = gNpc_adverbs[adverb]))) \
    { \
        f = t[1]; \
        set_alarm(t[0], 0.0, &f(actor, emote)); \
    } \
}


/* Krynn directories */
#define STAND_DIR  "/d/Krynn/"
#define KRYNN_DIR  "/d/Krynn/"
#define OPEN_DIR   (KRYNN_DIR + "open/")
#define COMMON_DIR (KRYNN_DIR + "common/")
#define SOLACE_DIR (KRYNN_DIR + "solace/")
#define XAK_DIR    (KRYNN_DIR + "xak/")
#define SOLAMN_DIR (KRYNN_DIR + "solamn/")
#define NERAKA_DIR (KRYNN_DIR + "neraka/")
#define CLUB_DIR   (KRYNN_DIR + "clubs/")
#define GUILDOBJ   (SOLAMN_DIR + "guild/obj/")

/* Krynn special rooms (might only work with complete pathnames) */
#define VOID       (COMMON_DIR + "void")

/* These require a bit special care */
#ifndef ARMYMASTER/* For usage with warfare.h */
#define ARMYMASTER (COMMON_DIR + "warfare/armymaster")
#endif
#ifndef CLOCK
#define CLOCK      (COMMON_DIR + "clock/clock")
#endif

/* Other objects */
#define KRLINK     (KRYNN_DIR + "domain_link")

/* include files  (must have complete pathname!) */
#define QUESTH     "/d/Krynn/solace/new_village/npc/quest_m.h"
#define RND_MEET   "/d/Krynn/common/random_meet.h"
#define HERBSEARCH "/d/Krynn/common/herbsearch.h"
/* HERBSEARCH is kept for backwards compatibility. Inheriting
    HERBSEARCHNEW should be done instead now - Teth */
#define TIME_FLOW  "/d/Krynn/common/time_master.h"


#define CLOCKH     "/d/Krynn/common/clock/clock.h"
#define DONE_QUEST(x)  "/d/Krynn/common/quest_master"->set_quest_solved(x)
#define QUERY_QUEST(x) "/d/Krynn/common/quest_master"->query_quest_solved(x)

/* Log defines */
#define K_KILL_LOG(f, who, whom) (log_file(f, sprintf("%s %-45s (%3d)\n", \
                          extract(ctime(time()), 4), \
                          who + " was killed by " + \
                          C(whom->query_real_name()), \
                          whom->query_average_stat()), \
                          500000))
#define STD_KILL_LOG(who, whom)  K_KILL_LOG("kills", who, whom)

#define K_QUEST_LOG(f, q, w, x)  (log_file(f, sprintf("%s %-25s " + \
                                   "%15s (%3d) %6d\n", \
                               extract(ctime(time()), 4), \
                               q, C(w->query_real_name()), \
                               w->query_average_stat(), x), \
                       1000000))
#define STD_QUEST_LOG(q, w, x)   K_QUEST_LOG("quest",q,w,x)

/* special include file (must have complete pathname!) */
#define DELIVERY   "/d/Genesis/delivery/delivery.h"

/* inherit files  (must have complete pathname!) */
#define M_FILE      "/d/Krynn/std/monster";
#define C_FILE      "/d/Krynn/std/creature";
#define R_FILE      "/d/Krynn/std/room";
#define OR_FILE     "/d/Krynn/std/outside_room";
#define ROOM_TELLS  "/d/Krynn/open/room_tell";
#define AUTO_TEAM   "/d/Krynn/open/auto_teaming";
#define QUEST_LOGGER ("/d/Krynn/common/questlogger/quest_logger")
#define HERBSEARCHNEW "/d/Krynn/std/herbsearch";
#define DRAGONBASE  "/d/Krynn/std/dragon_base";
#define CONQUER_BASE "/d/Krynn/common/warfare/conquer_base";
#define RECRUIT_BASE "/d/Krynn/common/warfare/recruit_base";


/* Krynn defines for Rooms */
#define INSIDE       add_prop(ROOM_I_INSIDE, 1);
#define OUTSIDE      add_prop(ROOM_I_INSIDE, 0);
#define DARK         add_prop(ROOM_I_LIGHT, 0);
#define LIGHT        add_prop(ROOM_I_LIGHT, 1);
#define NO_TIME      add_prop(ROOM_I_NO_TIME, 1)
#define MAX_SUNLIGHT 30

/* Krynn defines for NPCS */
#define SET_MAX_HP       set_hp(query_max_hp())
#define LEFTOVER(x)      add_leftover("/std/leftover", (x), 1, "", 0, 0)
#define CUTLEFTOVER(x)   add_leftover("/std/leftover", (x), 1, "", 0, 1)
#define NEVERKNOWN       add_prop(LIVE_I_NEVERKNOWN, 1)
#define ALWAYSKNOWN      add_prop(LIVE_I_ALWAYSKNOWN, 1)


/* Krynn defines for herb paths */
#define KRHERB      "/d/Krynn/common/herbs/"
#define AVHERB      "/d/Avenir/common/herbs/"
#define GOHERB      "/d/Gondor/common/herbs/"
#define KHHERB      "/d/Khalakhor/common/herbs/"
#define SHHERB      "/d/Shire/common/herbs/"
#define EAHERB      "/d/Earthsea/herbs/herb_files/"
#define RAHERB      "/d/Kalad/common/herbs/"
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

/* Krynn defines for common objects */
#define KCOMMERCE  (COMMON_DIR + "commerce/")
#define KRARMOUR   (COMMON_DIR + "armours/")
#define KRDRINK    (COMMON_DIR + "drinks/")
#define KRFOOD     (COMMON_DIR + "foods/")
#define KRNPC      (COMMON_DIR + "npcs/")
#define KROBJECT   (COMMON_DIR + "objects/")
#define KRWEAPON   (COMMON_DIR + "weapons/")
#define KRSCROLL   (COMMON_DIR + "scrolls/")
#define KRPOISON   (COMMON_DIR + "poisons/")
#define KRPOTION   (COMMON_DIR + "potions/")

#endif



