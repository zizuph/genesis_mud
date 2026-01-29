#pragma strict_types

#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/weather.h"
#include "/d/Khalakhor/sys/terrain.h"
#include "local.h"
#include <stdproperties.h>

inherit CLACHDUN;

// Prototypes
void set_up_cords();

string generate_long_desc();
string street_desc();
string stone_desc();
string mount_desc();
string wall_desc();
string tower_desc();

public int Buildings = 0;


void create_street() {}

nomask void
create_clachdun()
{
    set_up_cords();
    set_short("on a cobblestone street within Clach Dun");
    set_long(generate_long_desc);
    set_terrain(TERRAIN_STREET);
    add_prop(ROOM_I_LIGHT, 1);

    add_item(({"street","stone street","cobblestone street",
	"stone cobbled street"}), street_desc);
    add_item(({"stone", "stones", "cobblestone", "cobblestones"}),
      stone_desc);
    add_item(({"mountains", "mountain", "cliff", "cliffs"}), mount_desc);
    add_item(({"wall", "walls"}), wall_desc);
    add_item(({"tower", "bell tower", "lookout tower"}), tower_desc);

    create_street();
}

void
set_up_cords()
{
    sscanf(file_name(this_object()),
      ROOM_DIR + "street_%d_%d", gX, gY);
}


string
generate_long_desc()
{
    return "Need to finish this part.\n";
}

string 
street_desc() 
{
    return "";
}

string 
stone_desc() 
{
    return "";
}

string 
mount_desc() 
{
    return "";
}

string 
wall_desc() 
{
    return "";
}

string 
tower_desc() 
{
    return "";
}

int
kick(string str)
{
    if (str == "stone" || str == "loose stone")
    {
	write("You kick a loose cobblestone down the street.\n");
	say(QCTNAME(TP) + " kicks a cobblestone down the street.\n");
	return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(kick, "kick");
}
