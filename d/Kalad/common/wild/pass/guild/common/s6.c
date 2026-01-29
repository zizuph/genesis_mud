inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/guild/defs.h" 

void
create_room()
{
set_short("Path to the schools.");
set_long("You have entered a large courtyard that interupts the path "
	+"to the guild. There is a huge pillar here, covered in "
	+"announcements. There is a north path, leading to a spider-"
	+"shaped building, as well as a paths both east and west, "
	+"leading to the other two buildings, the towered and pyramid. "
	+"The ebony stone floor reflects a distorted image of all above "
	+"it, and the ceiling high above you is visible, lit by the "
	+"mystical flame known as faerie fire. There are many wandering "
	+"students here, most are rushing to get to lesson, though, or "
	+"the punishments of a High Priestess will be implemented. "
	+"The back of the cavern is barely visible from here, the "
	+"huge school devoted to the priests of Lloth dominating the "
	+"whole north half of the cavern.\n");
add_item(({"pillar"}),"The pillar looks huge and also might be used to "
	+"place announcements and notes on.\n");
add_item(({"buildings"}),"There are three buildings, a pyramid, a "
	+"spider-shaped, and a towered one.\n");
add_item(({"pyramid building"}),"It is shaped like a pyramid, and "
	+"is probably the home of the fighters of the Drow.\n");
add_item(({"spider-shaped building"}),"This is the home of the "
	+"priestesses of Lloth, the Spider Queen. Only women may enter.\n");
add_item(({"towered building"}),"This is the home of the wizards of "
	+"Menzoberanzan. They train there magic within the enchanted "
	+"walls of their towers.\n");
add_item(({"student","students"}),"They seem to be students at the school "
        +"and don't want to be bothered.\n");
add_item(({"wall","walls"}),"The walls are carved from black marble "
        +"and are highly polished and carved with spider webs.\n");
add_item(({"floor"}),"The floor is made of a highly polished black "
        +"marble which is highly reflective.\n");
add_item(({"cavern"}),"The cavern is carved out of a stone resembling "
        +"black marble, and is incredibly large. It contains the whole "
        +"Drow Academy and its students.\n");
add_item(({"flame","fire","faerie fire"}),"This is the strange blue "
        +"flame that covers most of the city in an eerie glow. The "
        +"flames are blue, and seem to be alive.\n");
add_exit(DGUILD + "common/s5", "south", 0, 2);
add_exit(DGUILD + "common/s7", "north", 0, 1);
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
add_prop(ROOM_I_LIGHT,0);
add_prop(ROOM_M_NO_TELEPORT,1);
clone_object(CVAN(shop/kabal_board))->move(TO);
}

