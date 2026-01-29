#pragma save_binary
#pragma strict_types

#include "local.h"
#include <stdproperties.h>

inherit GREY_HAVENS;

object archer;

// Function Prototypes
void add_archer();

void
create_gh_room()
{
    area = "not far from";
    areaname = "the City of Mithlond";
    land = "Eriador";
    areatype = 8;
    areadesc = "grassy area";
    grass = "dark green";

    extraline = "Down the gently sloping road to the southwest is " +
	"the harbour area. " +
        "White towers rise above the city walls of Grey Havens to " +
	"the northeast. Waves crash upon the shore in the west. " +
	"Off to the the east is a dense forest.\n";

    add_exit(GH_HARBOUR_DIR +  "harbour1.c", "southwest");
    add_exit(GH_HARBOUR_DIR +  "harbour11.c", "west");
    add_exit(GH_HARBOUR_DIR +  "harbour5.c", "east", 0, 1, 1);
    add_exit(GH_HARBOUR_DIR +  "harbour3.c", "north");
    add_archer();
    add_prop(ROOM_I_LIGHT, 1);
}

void
reset_shire_room()
{
    ::reset_shire_room();
    if(present(archer, TO))
        return;
    add_archer();
}

void
add_archer()
{
    archer = clone_object(GH_DIR + "npc/guard");
    archer->move_living("xxx", TO);
}