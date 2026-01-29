/*
 * Base file for the Clorhir area
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";

void create_clorhir_room() {}


/*
 * cavern vars and routines
 */
int alarm_id;



//string what_time;

// We use 'create_Room' instead of 'create_shire_room' because
// this is an indoors room
public void create_clorhir_room()
{
    set_short("");

    add_item("ceiling",
        "The ceiling is rough looking. It is made from stone blocks " +
        "that are now cracked. Some roots hang from the ceiling " +
        "and have cracked the stone blocks leaving a rough looking " +
        "surface.\n");

    set_room_tell_time(60+random(120));
    add_room_tell("Water drips in the distance.");

    create_clorhir_room();

    /* Let's hope this prevents the cloning problems. */
    setuid();
    seteuid(getuid());
}


string psg_desc1()
{
    return "You stand at the end of an ornate hallway. Statues line " +
        "the walls. A large mosaic sits in the middle of the floor, " +
        "partially obscured by a pile of rubble from the collapsed " +
        "ceiling. You smell the unmistakable odor of five leaf being smoked. ";
}

string psg_desc2()
{
    return "This is beneath the Downs inside a dark tunnel. The " +
        "passage smells dusty and of death and the " +
        "walls are made of crumbly stone. Roots grow from cracks " +
        "in the ceiling in this cold and gloomy place. ";
}

string psg_desc3()
{
    return "Somewhere inside a dark tunnel beneath the Downs " +
        "east of the Great Forest. Roots grow from the ceiling, " +
        "pushing stones aside. The tunnel is dark and dank, an " +
        "evil and haunted place, some say. ";
}

string psg_desc4()
{
    return "You stand in a dark tunnel. The walls are made of " +
        "stones that are cracked and weathered from countless " +
        "ages. The passage is moist from dripping water and very " +
        "cold. ";
}

string psg_desc10()
{
    return "You stand under the barrows in a dark passage. This " +
        "looks like one of the oldest part of barrow as there are " +
        "few stones on the walls and roots hang everywhere from " +
        "the walls and roof.  ";
}

string psg_desc11()
{
    return "This is a dank, dark passage. The walls have collapsed " +
        "leaving little room to move about. The passage smells " +
        "really bad like an old grave. ";
}

string psg_desc12()
{
    return "The passageway ends here. It is fallen in on itself, " +
        "making movement difficult. There is barely enough room " +
        "to turn around and walk out of here. ";
}


public string long_desc()
{
    string desc;

    desc = CAP(query_short()) + ". ";

    if (strlen(extraline))
	    desc +=extraline;

    if (functionp(vbfc_extra))
	    desc +=vbfc_extra();

    return (desc);
}