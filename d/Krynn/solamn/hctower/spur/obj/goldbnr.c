/*
* Dragon banners for the Knights
* by Teth and Jeremiah
*/

inherit "/d/Krynn/solamn/hctower/spur/obj/patban_base";

void
create_banner()
{
    add_name("gold_banner");
    set_extra_short("gold dragon");
    set_long_descr("This is a magnificent banner presenting " +
        "a spectacular gold dragon flying against a background of " +
        "midnight-black. The dragon is exhaling plumes of flame " +
        "from its mouth. This is the banner of the Solamnian patrol, " +
        "that investigates the doings of evil near Vingaard Keep and " +
        "Palanthas. It is supported by a pole made of oak. To use " +
        "the banner in the most effective way, try 'help banner'.\n");
    set_dcolor("gold");
    set_patrol("Solamnia");
    set_color("midnight-black");
}
