/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "hob.h"

public void
create_room(void)
{
    set_short("crumbling vestibule");
    set_long("This shadowed room carries a stench of rotting "+
	"death and decrepit inhabitation. The stone walls and floor "+
	"are covered over in black soot and dark patches of sludge. "+
	"Rusted iron poles have been rammed into various floor joints "+
	"and have little black pots atop them belching both light and "+
	"smoke, giving the room an ashen haze and obscuring the "+
	"ceiling.\n");

    add_item("ceiling", "The ceiling is not visible through the layers "+
	"of ash and soot in the air and on the stones themselves.\n");
    add_item(({"wall","walls","stone","stones","floor"}),
	"The walls and floor (and presumably the ceiling) are made from "+
	"an undertermined type of stone. They are closely fitted together "+
	"but that is all you can determine as they are covered in filth, "+
	"soot and sludge.\n");
    add_item(({"filth","soot","sludge","slime","ash"}),
	"Black soot and ash cover nearly everything, while black and grey "+
	"flecks of ash also hang in the air. Glossy patches of sludge "+
	"also line the walls and floor, evidence of decomposition.\n");
    add_item(({"joint","floor join","joints","floor joints"}),
	"The joints of the stones are close and artfully fitted. "+
	"The careful work was been broken at various points on the "+
	"floor however to make room for rusted iron poles.\n");
    add_item(({"pole","poles","iron pole","iron poles",
	"rusted pole","rusted poles"}), "Some rusted iron poles with "+
	"black pots top them have been rammed into the floor with no "+
	"apparent pattern to them.\n");
    add_item(({"pot","pots","black pot","black pots","little pot",
	"little pots"}), "Little black pots are welded atop rusted "+
	"iron poles thrust into the floor. They belch light and smoke "+
	"in seemingly equal measure.\n");

    IN; LIGHT;
    /* For the magic map. */
    add_prop(ROOM_S_MAP_FILE, "utterdark_hobs.txt");

    add_exit(AREA1 + "hall1",  "northwest");
    add_exit(AREA1 + "hall18", "northeast");

    add_npc(MON + "lizard", 1);
    add_npc(MON + "hobgoblin", 6);

    add_object(HOB + "door2", 1);
}
