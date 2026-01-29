/* Domain defs */

#include <stdproperties.h>

#ifndef ANSALON_DEF
#define ANSALON_DEF

/* Ansalon general defines */
#define TP           this_player()
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

#define UNIQUE(filen,num,alternatefile) ((!((filen)->load_file()) && \
      sizeof(filter(object_clones(find_object(filen)), \
            (&operator(==)(0) @ &->query_prop("_obj_i_broken")))) \
      < num) ? filen : alternatefile)

#define POSSESSIVE(x) x->query_possessive()
#define OBJECTIVE(x)  x->query_objective()
#define PRONOUN(x)    x->query_pronoun()
#define HIS(x)        x->query_possessive()
#define HIM(x)        x->query_objective()
#define HE(x)         x->query_pronoun()
#define REALAGE(x)    (x->query_age() * 2)
#define QRACE(x) x->query_race_name()

/* Special output possibilities for dark rooms and invisible livings
* This SHOULD be used everywhere instead of the normal functions
*/
#define METNAMEI(x) x->query_name()
#define NONMET(x) x->query_nonmet_name()
#define TNONMET(x) "the " + NONMET(x)
#define CTNONMET(x) "The " + NONMET(x)

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
Planned usage:
In create_ansalon_monster()  (or whatever) you do:
add_emote_hook("nod",2.0,do_nod);
add_emote_hook("smile",1.5,do_smile);
add_emote_hook("grin",3.0, do_smile);
add_emote_hook("shyly",2.0, do_smile);

And then somewhere outside you do: EMOTE_HOOK

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
   if (pointerp((t = this_object()->query_emotes()[emote]))) \
      { \
      f = t[1]; \
      set_alarm(t[0], 0.0, &f(actor, adverb)); \
   } \
   else \
      if (pointerp((t = this_object()->query_emotes_adverb()[adverb]))) \
      { \
      f = t[1]; \
      set_alarm(t[0], 0.0, &f(actor, emote)); \
   } \
}

/* Ansalon directories */
#define ASTAND_DIR"/d/Ansalon/"
#define ANSALON_DIR "/d/Ansalon/"
#define ACOMMON_DIR ANSALON_DIR + "common/"

/* Ansalon special rooms */
#define AVOID ACOMMON_DIR + "void"

/* Krynn directories */
#define KRYNN_DIR  "/d/Krynn/"
#define SOLACE_DIR KRYNN_DIR + "solace/"
#define XAK_DIR   KRYNN_DIR + "xak/"
#define SOLAMN_DIR KRYNN_DIR + "solamn/"
#define NERAKA_DIR KRYNN_DIR + "neraka/"
#define GUILDOBJ   SOLAMN_DIR + "guild/obj/"

/* Krynn special rooms (might only work with complete pathnames) */
#define GUILD      "/d/Krynn/solamn/vkeep/startroom"

/* include files  (must have complete pathname!) */
#define QUESTH     "/d/Krynn/solace/village/monster/quest_m.h"
#define ARND_MEET   "/d/Ansalon/common/random_meet.h"
#define AHERBSEARCH "/d/Ansalon/common/herbsearch.h"
#define ATIME_FLOW  "/d/Ansalon/common/time_master.h"
#define DL_CLOCK    "/d/Ansalon/common/clock/clock.h"  

/* Ansalon defines for logs */

/*    (string, string, object)    */
#define A_KILL_LOG(f, who, whm) (log_file(f, sprintf("%s %-45s (%3d)\n", \
         extract(ctime(time()), 4), \
         who + " was killed by " + \
         C(whm->query_real_name()), \
         whm->query_average_stat()), \
      500000))

/*    (string, string, object, int)    */
#define A_QUEST_LOG(f, q, w, x) (log_file(f, sprintf("%s %-25s %15s " + \
         "(%3d) %6d\n", \
         extract(ctime(time()), 4), \
         q, C(w->query_real_name()), \
         w->query_average_stat(), x), \
      1000000))

/* inherit files  (must have complete pathname!) */
#define AM_FILE      "/d/Ansalon/std/monster";
#define AC_FILE      "/d/Ansalon/std/creature";
#define AR_FILE      "/d/Ansalon/std/room";
#define AOR_FILE     "/d/Ansalon/std/outside_room";
#define AROOM_TELLS  "/d/Ansalon/open/room_tell";
#define AUTO_TEAM    "/d/Krynn/open/auto_teaming";
#define CONQUER_BASE "/d/Krynn/common/warfare/conquer_base";

/* Ansalon defines for Rooms */
#define INSIDE     add_prop(ROOM_I_INSIDE, 1);
#define OUTSIDE    add_prop(ROOM_I_INSIDE, 0);
#define DARK       add_prop(ROOM_I_LIGHT,0);
#define LIGHT      add_prop(ROOM_I_LIGHT,1);

/* Ansalon defines for NPCS */
#define SET_MAX_HP       set_hp(query_max_hp())
#define LEFTOVER(x) add_leftover("/std/leftover",x,1,"",0,0)
#define CUTLEFTOVER(x) add_leftover("/std/leftover",x,1,"",0,1);
#define NEVERKNOWN       add_prop(LIVE_I_NEVERKNOWN, 1)
#define ALWAYSKNOWN      add_prop(LIVE_I_ALWAYSKNOWN, 1)
#define OBJ_I_COLORABLE  "_obj_i_colorable"
#define OBJ_I_COLOURABLE "_obj_i_colorable"
#define OBJ_I_CONVERT_HOOPAK "_obj_i_convert_hoopak"
#define OBJ_I_NO_CONVERT_HOOPAK "_obj_i_no_convert_hoopak"

#endif
