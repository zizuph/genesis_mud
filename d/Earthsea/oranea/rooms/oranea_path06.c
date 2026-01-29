/*
 * A path in Oranea by Ckrik, July 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_oranea_path.c";

void
create_oranea_path()
{
    add_long("The path is getting really steep.\n");
    add_exit("/d/Earthsea/oranea/rooms/oranea_path05", "north");
    add_exit("/d/Earthsea/oranea/rooms/mountain_path01", "southwest",
      "@@block@@");
}

int
block()
{
    object tp = this_player();

    tp->catch_msg("It appears that a landslide here has blocked the "+
      "path to the southwest.\n");
    return 1;
}
