inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Sarr */

void
create_room()
{
    set_short("In a shadowy room");
    set_long("You are now in a study room of some sort. There is a "+
    "single large table here, with a candle lit on it. Chairs "+ 
    "surround the table. The candle "+
    "flickers around, and shadows dance around the walls. The "+
    "darkness in here is great, and you feel an air of evilness. "+
    "Three other doorways lead out from here other than the one "+
    "back to the main room.\n");
    add_item("table","The table is large and wooden. You see "+
    "nothing on it, but old dark stains.\n");
    add_item("chairs","Many chairs surround the table.\n");
    add_item("candle","The candle burns strangely. It gives little "+
    "light, and a lot of room for shadows.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    add_exit(SHDIR(board),"northeast",0,-1,1);
    add_exit(SHDIR(train),"northwest",0,-1,1);
    add_exit(SHDIR(sto),"east",0,-1,1);
    add_exit(SHDIR(t10),"south",0,-1,1);
    clone_object(SHDIR(shadow_walkers_board))->move(TO);
}
