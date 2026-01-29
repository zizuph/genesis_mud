inherit "/std/room.c";

create_room()
{
  set_short("Test room");
  set_long(break_string("@@long_description:/d/Dville/deinonychus/tmp/descriptions.c",77));
}
