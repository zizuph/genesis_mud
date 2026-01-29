inherit "/d/Roke/Athas/room/roads/MOUNTAIN_PASS.c";

#include "/d/Roke/defs.h"

void
create_mountain_pass()  {
        add_exit(ROAD_D+"pass2","east",0,2);
        add_exit(ROAD_D+"ent_pass","west",0,2);
}
