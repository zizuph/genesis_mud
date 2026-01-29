/*
* Dragon banners for the Knights
* by Teth and Jeremiah
*/

inherit "/d/Krynn/solamn/hctower/spur/obj/patban_base";

void
create_banner()
{
    set_extra_short("copper dragon");
    set_long_descr("This is a magnificent banner presenting " +
      "an impressive copper dragon flying against a background of " +
      "dark crimson. A stream of acid is being spewed from the maw "+
      "of the dragon. This is the banner of the Flotsam patrol, " +
      "which keeps silent watch over the occupied port city. " +
      "It is supported by a pole made of diamond willow. To use " +
      "the banner in the most effective way, try 'help banner'.\n");
    set_dcolor("copper");
    set_patrol("Flotsam");
    set_color("dark crimson");
}

