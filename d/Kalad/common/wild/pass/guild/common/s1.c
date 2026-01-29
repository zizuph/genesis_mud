inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/guild/defs.h"

void
create_room()
{
set_short("Stairs");
set_long("You have left the entrance of the Drow Academy and now "
	+"stand on the stairs leading up to Tier Breche, the immense "
	+"cavern which houses the Academy. Lining the walls and floor "
	+"is the eerie blue flame called faerie fire. The steps "
	+"themselves are broad, easily allowing 6 people to walk "
	+"side-by-side without being crowded, and they are made of "
	+"a black marble which reflects all light that happens to "
	+"touch it. The stairs reach far up into the darkness, hiding "
	+"strange secrets of Lloth and the drow.\n");
add_item(({"wall","walls"}),"The walls are carved from black marble "
	+"and are highly polished and carved with spider webs.\n");
add_item(({"floor"}),"The floor is made of a highly polished black "
	+"marble which is highly reflective.\n");
add_item(({"cavern"}),"The cavern is carved out of a stone resembling "
	+"black marble.\n");
add_item(({"flame","fire","faerie fire"}),"This is the strange blue "
	+"flame that covers most of the city in an eerie glow. The "
	+"flames are blue, and seem to be alive.\n");
add_item(({"entrance"}),"The entrance of the drow academy lies to "
	+"your south.\n");
add_item(({"stairs","stair","step","steps"}),"They are carved from the "
	+"same black marble as the rest of the cavern and are broad "
	+"enough for many people to walk down.\n");
add_exit(DGUILD + "common/s2", "north", 0, 2);
add_exit(DGUILD + "common/joinroom", "south", 0, 2);
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
add_prop(ROOM_I_LIGHT,0);
}
