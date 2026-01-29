/*
 * A path in Oranea by Ckrik, July 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_oranea_path.c";

void
create_oranea_path()
{
    add_long("To the north the path suddenly ends in a cliff. " +
      "Beyond the cliff you see a small cove. You can " +
      "see some boats despite the blue mist. There is " +
      "a trail leading down the cliff to the shore. " +
      "The path continues to " +
      "south.\n");
    add_item("bushes", "The bushes seem a bit thinner here, and "+
      "through the leaves you see an entrance to a cave.\n");
    add_exit("/d/Earthsea/ships/oranea_line/oranea_pier", "down");
    add_exit("/d/Earthsea/oranea/rooms/oranea_path02", "south");
    add_exit("/d/Earthsea/oranea/bridge/cave", "enter", 0,0, 1);
}
