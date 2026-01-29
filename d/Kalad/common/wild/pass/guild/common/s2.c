inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/guild/defs.h"

void
create_room()
{
::create_room();
set_short("Platform");
set_long("You have reached a small platform in the middle of the "
	+"stairs. There is a cistern here, as well as a bench. "
	+"Around you lies the entryway to Tier Breche, where the "
	+"Drow Academy is housed. There are rumours of poweful "
	+"magical constructs guarding the school, so care should "
	+"be taken, lest an unkind fate befalls you. The stairs do "
	+"not reach much higher, and even from here the view of "
	+"Menzoberanzan is incredible, flickering blue flames cover "
	+"everything, giving off a strange light.\n");
add_item(({"cistern"}),"It is a cistern shaped from midnight black "
	+"marble, and resembling a spider. There's a hole in its "
	+"back where there is water that looks drinkable.\n");
add_item(({"bench"}),"A finely crafted adamantite bench. There are "
	+"pads on it that make the metal easier to rest upon.\n");
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
add_cmd_item("from cistern", "drink", "@@drink_cist");
add_cmd_item("on bench", "sit", "@@sit_bench");
add_cmd_item("up", "stand", "@@stand_up");
add_exit(DGUILD + "common/s3", "north", 0, 2);
add_exit(DGUILD + "common/s1", "south", 0, 2);
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
add_prop(ROOM_I_LIGHT,0);
add_prop(ROOM_M_NO_TELEPORT,1);
}
drink_cist()
{
   write("You drink from the cistern and feel very refreshed.\n");
   say(QCTNAME(TP) + " drinks from the cistern.\n");
   return 1;
}
sit_bench()
{
   write("You sit on the bech and feel relaxed.\n");
   say(QCTNAME(TP) + " sits on the bench.\n");
   return 1;
}
stand_up()
{
   write("You stand up from the bench.\n");
   say(QCTNAME(TP) + " stands up from the bench.\n");
   return 1;
}
