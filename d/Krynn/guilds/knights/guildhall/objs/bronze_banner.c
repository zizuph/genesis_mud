/*
 * Dragon banners for the Knights
 * by Teth and Jeremiah
 */

inherit "/d/Krynn/solamn/hctower/spur/obj/patban_base";

void
create_banner()
{
    set_extra_short("bronze dragon");
    set_long_descr("This is a magnificent banner presenting " +
      "a reckless bronze dragon flying against a background of " +
      "electric-blue. The dragon is exhaling a bolt of lightning " +
      "from its mouth. This is the banner of the Pax Tharkas patrol, " +
      "that investigates the doings of evil south of Newports. " +
      "It is supported by a pole made of Lemish silver maple. To use " +
      "the banner in the most effective way, try 'help banner'.\n");
    set_dcolor("bronze");
    set_patrol("Pax Tharkas");
    set_color("electric-blue");
}
