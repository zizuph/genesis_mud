/*
 * Dragon banners for the Knights
 * by Teth and Jeremiah
 */

inherit "/d/Krynn/solamn/hctower/spur/obj/ordban_base";

void
create_banner()
{
    set_extra_short("rose");
    set_long_descr("This is a magnificent banner presenting " +
      "a deep-blue kingfisher grasping a red rose in its beak on a field " +
      "of white and silver, the symbol the Knights of Solamnia " +     
      "use when representing Paladine. This is the banner of the Order " +
      "of the Rose. It is supported by a pole made of yew. To use " +
      "the banner in the most effective way, try 'help banner'.\n");
    set_deity("Paladine");
    set_patrol("Rose");
    set_color("silver and white");
}
