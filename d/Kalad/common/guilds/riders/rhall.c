inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Mhyrkhaan */

void
create_room()
{
    ::create_room();
    set_short("Guild Hall of the Dark Alliance");
    set_long("You are in the guild hall of the Dark Alliance. The walls have torches on "+
    "them, casting light in this otherwise dark and dismal place. "+
    "To the north, you see the Rider's store, to the west you see "+
    "the training hall and to the east you see the Wartables. "+
    "This room has many tables and chairs in it for the Riders to "+
    "relax and discuss plans. To the south you see a cosy, area where "+
    "you can rest for the day.\n");
    add_item("torches","The torches are well tended and burn brightly.\n");
    add_item("tables","The tables are sturday and made of solid oak.\n");
    add_item("walls","The walls are made of smoothened stone.\n");
    INSIDE;
    add_exit(COMMON(guilds/riders/joinroom),"up",0,-1,-1);
    add_exit(COMMON(guilds/riders/rshop),"north",0,-1,-1);
    add_exit(COMMON(guilds/riders/rstable),"east",0,-1,-1);
    add_exit(COMMON(guilds/riders/train),"west",0,-1,-1);
    add_exit(COMMON(guilds/riders/start),"south",0,-1,-1);
    add_exit(COMMON(guilds/riders/dacommon),"common",0,-1,-1);
    clone_object(COMMON(guilds/riders/da_board))->move(TO,1);
}

