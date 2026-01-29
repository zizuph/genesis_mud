/* Vladimir 23-06-94 */
inherit "/std/room.c";

void
create_room()
{
set_name("Entrance");
set_long(
"There is a small landslide here with a few large boulders lying around.  "+
 "Engraved in the mountainside is a small cave entrance about fifteen "+
 "feet high "+
"and stands five feet off the ground. Nothing other than darkness can be seen "+
"within the cave itself. The path continues east and west from here.\n");
add_exit("/d/Immortal/vladimir/caves/cv1.c", "enter");
add_item(({"boulder", "boulders", "rock", "rocks"}),
break_string("These boulders are medium sized, with jagged cracks running "+
"throughout. They look as if they have recently fallen.\n", 70));
add_item(({"cave", "entrance"}),
break_string("The entrance emits an aura of evil. The cave looks dank and wet "+
"from this viewpoint.\n", 70));
}
