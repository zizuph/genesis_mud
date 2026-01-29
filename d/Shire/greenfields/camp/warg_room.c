/* THis is just a room for the cloning and random
distribution of the warg-riding team
of gorgun
*/

#include "/d/Shire/sys/defs.h"
#include ORC_FILE

inherit SHIRE_ROOM;

#define NUM_TEAMMATES   2

// Prototypes
void move_out();

// Global Vars
static object Gorgun;

void
create_shire_room()
{
    set_short("warg room");
    set_long("This room handles the cloning and distribution of the "+
      "warg rider in the orc camp.\n");
    add_exit(GREEN_DIR + "camp/camp05", "5");
    add_exit(GREEN_DIR + "camp/camp06", "6");
    add_exit(GREEN_DIR + "camp/camp07", "7");
    add_exit(GREEN_DIR + "camp/camp09", "9");
    add_exit(GREEN_DIR + "camp/camp12", "12");
    add_exit(GREEN_DIR + "camp/camp13", "13");
    add_exit(GREEN_DIR + "camp/camp14", "14");
    add_exit(GREEN_DIR + "camp/camp15", "15");
    reset_shire_room();
}

void
reset_shire_room()
{
    object orc;
    int i;

    if (!objectp(Gorgun))
    {
    setuid(); seteuid(getuid());
    Gorgun = clone_object(GREEN_DIR + "npc/gorgun");
    Gorgun->move(TO);
    i = -1;
    while(++i < NUM_TEAMMATES)
    {
        orc = clone_object(ORCMAKER);
        orc->set_type(WARRIOR);
        orc->set_power(125 + random(51));
        orc->move(TO);
        Gorgun->team_join(orc);
    }
    set_alarm(120.0,0.0,move_out);
    }
}

void
move_out()
{
    Gorgun->command(ONE_OF(query_exit_cmds()));
}
