/*
 * Dragon banners for the Knights
 * by Teth and Jeremiah
 */

inherit "/d/Krynn/solamn/hctower/spur/obj/ordban_base";

void
create_banner()
{
    set_extra_short("sword");
    set_long_descr("This is a magnificent banner presenting " +
      "a deep-blue kingfisher clutching a silver sword in its claws " +
      "on a field of white and earth brown, the symbol the Knights of " +
      "Solamnia use when representing Kiri-Jolith. This is the banner " + 
      "of the Order of the Sword. It is supported by a pole made of " +  
      "ash. To use the banner in the most effective way, try " +
      "'help banner'.\n");
    set_deity("Kiri-Jolith");
    set_patrol("Sword");
    set_color("earth-brown and white");
}
