/* Domain defs */

#include <stdproperties.h>

#ifndef KRYNN_DEF
#define KRYNN_DEF

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
#define BSN(x) break_string(x,70) + "\n"

#define POSSESSIVE(x) x->query_possessive()
#define OBJECTIVE(x)  x->query_objective()
#define PRONOUN(x)    x->query_pronoun()

#define SET_MAX_HP; set_hp(query_max_hp());

#define QRACE(x) x->query_race_name()

#define METNAMEI(x) x->query_name()
#define NONMET(x) x->query_nonmet_name()
#define TNONMET(x) "the " + NONMET(x)
#define CTNONMET(x) "The " + NONMET(x)

#define SAY(x) say(({BSN(METNAMEI(TP) + x), \
    BSN(CTNONMET(TP) + x), \
    BSN("Someone" + x)}))
#define SAYBB(x) say(({BSN(METNAMEI(TP) + x), \
    BSN(CTNONMET(TP) + x)}))

#define LSAY(x, y) say(({BSN(x + METNAMEI(TP) + y), \
    BSN(x + TNONMET(TP) + y), \
    BSN(x + "someone" + y)}))
#define LSAYBB(x, y) say(({BSN(x + METNAMEI(TP) + y), \
    BSN(x + TNONMET(TP) + y)}))

#define CATCH_MSG(o, x) catch_msg(({BSN(METNAMEI(o) + x), \
    BSN(CTNONMET(o) + x), \
    BSN("Someone" + x)}))
#define CATCH_MSGBB(o, x) catch_msg(({BSN(METNAMEI(o) + x), \
    BSN(CTNONMET(o) + x)}))

#define LCATCH_MSG(o, x, y) catch_msg(({BSN(x + METNAMEI(o) + y), \
    BSN(x + TNONMET(o) + y), \
    BSN(x + "someone" + y)}))
#define LCATCH_MSGBB(o, x, y) catch_msg(({BSN(x + METNAMEI(o) + y), \
    BSN(x + TNONMET(o) + y)}))

#define TELL_ROOM(r, o, x, n) tell_room(r, ({BSN(METNAMEI(o) + x), \
    BSN(CTNONMET(o) + x), \
    BSN("Someone" + x)}), n)
#define TELL_ROOMBB(r, o, x, n) tell_room(r, ({BSN(METNAMEI(o) + x), \
    BSN(CTNONMET(o) + x)}), n)

#define LTELL_ROOM(r, o, x, y, n) tell_room(r, ({BSN(x + METNAMEI(o) + y), \
    BSN(x + TNONMET(o) + y), \
    BSN(x + "someone" + y)}), n)
#define LTELL_ROOMBB(r, o, x, y, n) tell_room(r, ({BSN(x + METNAMEI(o) + y), \
    BSN(x + TNONMET(o) + y)}), n)


#define M_FILE     "/d/Krynn/open/monster/monster.c";
#define C_FILE     "/d/Krynn/open/monster/creature.c";
#define OPEN	   "/d/Krynn/open/"

#define STAND_DIR  "/d/Krynn/"
#define SOL_DIR    "/d/Krynn/solace"
#define RAST_DIR   "/d/Krynn/rastlin"
#define NICK_DIR   "/d/Krynn/nick"
#define DOR_DIR    "/d/Krynn/dorak"
#define XAK_DIR	   "/d/Krynn/xak/"

#define QUESTH     "/d/Krynn/solace/village/monster/quest_m.h"

#define TELLDOMAIN(xxx) "/d/Krynn/private"->my_shout(xxx);
#define MESSAGE(xxx)    "/d/Krynn/private"->message(xxx);

#define GUILD           "/d/Krynn/solamn/vkeep/startroom"
#define VOID           "/d/Krynn/common/void"

#define RND_MEET       "/d/Krynn/common/random_meet.h"

#define INSIDE  add_prop(ROOM_I_INSIDE, 1);
#define OUTSIDE add_prop(ROOM_I_INSIDE, 0);
#define DARK    add_prop(ROOM_I_LIGHT,0);
#define LIGHT   add_prop(ROOM_I_LIGHT,1);

#define NEVERKNOWN add_prop(LIVE_I_NEVERKNOWN, 1)
#define ALWAYSKNOWN add_prop(LIVE_I_ALWAYSKNOWN, 1)

#define OBJ_I_COLORABLE  "_obj_i_colorable"
#define OBJ_I_COLOURABLE "_obj_i_colorable"

#endif
