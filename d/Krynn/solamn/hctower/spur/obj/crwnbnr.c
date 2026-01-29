/*
 * Dragon banners for the Knights
 * by Teth and Jeremiah
 */

inherit "/d/Krynn/solamn/hctower/spur/obj/ordban_base";

void
create_banner()
{
    set_extra_short("crown");
    set_long_descr("This is a magnificent banner presenting " +
      "a deep-blue kingfisher wearing a golden crown on a field " +
      "of white and deep-blue, the symbol the Knights of Solamnia " +     
      "use when representing Habbakuk. This is the banner of the Order " +
      "of the Crown. It is supported by a pole made of elm. To use " +
      "the banner in the most effective way, try 'help banner'.\n");
    set_deity("Habbakuk");
    set_patrol("Crown");
    set_color("deep-blue and white");
}
