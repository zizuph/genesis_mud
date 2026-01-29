
#include "../local.h";

inherit SOLACE_ROOM_BASE;

void
create_solace_room() 
{
    set_short("Lakeside Road");
    set_long("You are walking on a dirt road that turns towards the " +
	     "mountains in the northwest. Soon, you settle into a " +
	     "comfortable jaunt, caused by the peaceful woods around you, " +
	     "leaving all bad memories behind.\n");
    add_item("mountains",
	     "The mountains look quite peaceful and serene.\n");
    add_item(({"road", "dirt"}),
	     "It's more a trail than a road, and it doesn't appear " +
	     "specifically prepared. There's just dirt here now, where " +
	     "people walked along.\n");
    add_item(({"woods","forest","trees"}),
	     "There is forest all around you, not the dark and gloomy " +
	     "type, but rather light and friendly trees.\n");
    add_exit(ROOM + "lake8","northwest",0);
    add_exit(ROOM + "lake6","south",0);
}
