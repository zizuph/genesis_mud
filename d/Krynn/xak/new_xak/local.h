#ifndef _XAK_TSAROTH_H_
#define _XAK_TSAROTH_H_

#include "/d/Krynn/common/defs.h"

#define TDIR                "/d/Krynn/new_xak/"     /* XAK_DIR */
#define STD                 TDIR + "std/"
#define NPC                 TDIR + "npc/"
#define ROOM                TDIR + "room/"
#define OBJ                 TDIR + "obj/"
#define TEMPLE              ROOM + "temple/"
#define CITY                ROOM + "city/"
#define HALL                ROOM + "hall/"
#define MIDDLE              ROOM + "middle/"
#define LOWER               ROOM + "lower/"

#define OUTROOM             STD + "outside_base"
#define INROOM              STD + "inside_base"
#define TABLE_HA            STD + "rndhall_ancestors"
#define TABLE_LOWER         STD + "rndlower"
#define TABLE_MIDDLE        STD + "rndmiddle"

#define STDDOOR             "/d/Krynn/std/door"
#define CHAPEL              "/d/Krynn/solamn/guild/spells/chapel_base"
#define XAK_MASTER          (OBJ + "master")

#define DOOR(x)             (x->query_open() ? "open" : "closed")
#define ADOOR(x)            (x->query_open() ? "an open" : "a closed")
#define MOVE(x,y)           if (!x) { x = clone_object(y); x->move(TO); }
#define GET_NPC_HA          (XAK_MASTER->query_npc_file(TABLE_HA))
#define GET_NPC_MIDDLE      (XAK_MASTER->query_npc_file(TABLE_MIDDLE))
#define GET_NPC_LOWER       (XAK_MASTER->query_npc_file(TABLE_LOWER))

#define K_TEMPLE            "XAK4325"

#define BUPU_PACK(x)        (XAK_MASTER->query_bupu_pack(x))

#endif _XAK_TSAROTH_H_
