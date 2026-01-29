inherit "/d/Gondor/common/room";

create_room()
{
  set_short("A temporary room for the boat on the river");
  set_long("A temporary room for the boat on the river.\n");
  add_exit("/d/Gondor/anorien/osgiliath/boatroom","west");
  add_exit("/d/Gondor/ithilien/osgiliath/boatroom","east");
}
