inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/guild/defs.h"

void
create_room()
{
set_short("Stairs");
set_long("The stairs have resumed their lengthy trip upwards. Below "
	+"you flicker the flames of the spell faerie fire, which "
	+"blankets the whole city in a dim light. Further to your "
	+"north lies the entrance to Tier Breche, the cavern that "
	+"houses the famed Drow Academy. The floor and walls are "
	+"highly polished and reflective, allowing you to almost "
	+"see your reflection in them. Only the sheer blackness of "
	+"the stone prevents you from doing that.\n");
add_item(({"wall","walls"}),"The walls are carved from black marble "
        +"and are highly polished and carved with spider webs.\n");
add_item(({"floor"}),"The floor is made of a highly polished black "
        +"marble which is highly reflective.\n");
add_item(({"cavern"}),"The cavern is carved out of a stone resembling "
        +"black marble.\n");
add_item(({"flame","fire","faerie fire"}),"This is the strange blue "
        +"flame that covers most of the city in an eerie glow. The "
        +"flames are blue, and seem to be alive.\n");
add_item(({"entrance"}),"The entrance of the Tier Breche lies to "
        +"your north.\n");
add_item(({"stairs","stair","step","steps"}),"They are carved from the "
        +"same black marble as the rest of the cavern and are broad "
        +"enough for many people to walk down.\n");
add_exit(DGUILD +"common/s4", "north", 0, 2);
add_exit(DGUILD +"common/s2", "south", 0, 2);
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
add_prop(ROOM_I_LIGHT,0);
add_prop(ROOM_M_NO_TELEPORT,1);
}
