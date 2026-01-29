#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <money.h>

#define RICHPURSE RICHCLUB+"richpurse"
#define RICHLOG "/d/Immortal/rclub/new.log" /*  JOIN-LOG  */
#define RICHROOM RICHCLUB+"richclub"
#define RICH_OBJ RICHCLUB+"richclub"
#define SET_EMOTE "_live_s_soulextra"
#define ACCOUNTS "/d/Genesis/obj/accounts"

void
create_room()
{
    set_short("master room of the RMC");
    set_long(break_string(
        "This is the master room of the Rich Men's Club. It's placed "+
        "in the attic of the RMC tower and here are many matters of the "+
        "club handled. It is a very cozy room with dark red curtains, "+
        "making the light very damp. Pictures hangs on the wall, showing "+
        "the founders of the club."+
        "\n",60));
    INSIDE;
}