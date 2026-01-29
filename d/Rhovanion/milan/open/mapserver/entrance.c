inherit "/std/room";


void
create_room()
{
  set_short("entrance");
  set_long("This in entrance to map-rooms.\n");
  add_exit("/d/Rhovanion/milan/open/mapserver/map-1-2","down");
}
