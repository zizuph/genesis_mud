/*
 * Dragon banners for the Knights
 * by Teth and Jeremiah
 */

inherit "/d/Krynn/solamn/hctower/spur/obj/patban_base";

void
create_banner()
{
    set_extra_short("brass dragon");
    set_long_descr("This is a magnificent banner presenting " +
      "a talkative brass dragon flying against a background of " +
      "snow-white. The dragon is exhaling a mist of sleep gas " +
      "from its mouth. This is the banner of the Solace patrol, " +
      "that investigates the doings of evil in and around Solace. " +
      "It is supported by a pole made of black walnut. To use " +
      "the banner in the most effective way, try 'help banner'.\n");
    set_dcolor("brass");
    set_patrol("Solace");
    set_color("snow-white");
}
