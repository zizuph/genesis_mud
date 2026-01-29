/*
 * Dragon banners for the Knights
 * by Teth and Jeremiah
 */

inherit "/d/Krynn/solamn/hctower/spur/obj/patban_base";

void
create_banner()
{
    set_extra_short("silver dragon");
    set_long_descr("This is a magnificent banner presenting " +
      "a beautiful silver dragon flying against a background of " +
      "forest-green. The dragon is exhaling a cone of frost " +
      "from its mouth. This is the banner of the Icewall patrol, " +
      "that investigates the doings of evil south of Tarsis. " +
      "It is supported by a pole made of diamond willow. To use " +
      "the banner in the most effective way, try 'help banner'.\n");
    set_dcolor("silver");
    set_patrol("Icewall");
    set_color("forest-green");
}
