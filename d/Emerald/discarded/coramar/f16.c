#include "dirheader.h"
#include "coramar.h"

#include <stdproperties.h>

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");

    set_long("   The forest is so overgrown here that no light can get "+
             "through. The young trees bend so low over the path that you "+
             "have to duck slightly to maneuver through it. Massive jumbles "+
             "of hanging vines and thick bushes making maneuvering through "+
             "the dark tunnel of trees very difficult.\n\n");

    add_prop(ROOM_I_LIGHT,-1);

    add_prop(ROOM_S_DARK_LONG,"There is not enough light in here to see "+
             "anything.\n");

    add_prop(ROOM_S_DARK_MSG,"It is too dark in the tunnel of trees to");

    add_fexit(CORAMAR+"f17", "northeast", 0);
    add_fexit(CORAMAR+"f15", "southeast", 0);
}
