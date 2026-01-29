/* created by Aridor 06/06/94 */

#include "../local.h"

inherit ROOM_BASE

/*prototype*/
void make_light();

int gate_closed;

void
reset_ld_room()
{
    enable_reset(0);
}

nomask void
reset_thief_room()
{
    reset_ld_room();
}

void
create_ld_room() { }

nomask void
create_thief_room()
{
    create_ld_room();
    
    DARK;
    
    restore_object(DOORROOM);
    if (!gate_closed)
      make_light();
}


void
make_light()
{
    LIGHT;
    tell_room(TO,"Suddenly, light floods the cavern!\n");
}

void
make_dark()
{
    DARK;
    tell_room(TO,"Suddenly, the cavern in cast into darkness!\n");
}
