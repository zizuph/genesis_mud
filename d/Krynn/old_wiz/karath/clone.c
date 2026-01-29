inherit "/std/room";

void
create_room()
{
  set_long("     Piles of rock lay in crumbling heaps around an obelisk "+
  "that shimmers with electricity. Statues in the shape of humanoids and "+
  "creatures fill the area. It appears that this is some sort of magical "+
  "cloning-plant.\n");
  set_short("Karath's cloning room");
  add_exit("workroom.c", "up");
}
