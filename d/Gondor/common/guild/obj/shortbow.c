inherit "/std/bow";

#include <formulas.h>

public void
create_bow()
{
    set_short("sturdy shortbow");
    set_name("shortbow");
    add_name(({"bow", "hailstorm"}));
    set_adj("sturdy");
    set_long("The bow is fairly short and sturdy, well suited for " +
	     "long journeys. It is about four feet tall and made " +
	     "out of yew. The handle is made of a thin hemp-rope " +
	     "tied tightly around the wood for a good grip.\n" +
	     "There is a small note attached to the bow.\n");
    add_item("note", "On a small patch of leather someone has written:\n\n" +
	     "Instructions on Safe and Proper use of Ranger Bow Hailstorm\n\n"+
	     "aim target [in location]    - Aims bow at target, hit\n" +
	     "                              location is optional.\n\n" +
	     "fire                        - Fires arrow at aimed target.\n\n" +
	     "shoot target [in location]  - Aims and fires at target.\n\n" +
	     "unload                      - Unloads the arrow and relaxes\n" +
	     "                              aim at a target.\n\n" +
	     "secondary [command]         - Specifies the command to\n" +
	     "                              perform if you should run\n" +
	     "                              out of arrows.\n\n" +
	     "string bow                  - Puts a new string on a bow.\n\n" +
	     "unstring bow                - Removes the bowstring from\n" +
	     "                              a bow.\n\n" +
	     "If You experience any unexpected malfunctions do contact\n" +
	     "us at Rohim's Armour and Weapon Shoppe for personal service.\n" +
	     "\n\nFor optimal performance use Snowspike Arrows from\n" +
	     "Rohim's Armour and Weapon Shoppe.\n");
    add_prop(OBJ_I_WEIGHT, 2100);
    add_prop(OBJ_I_VOLUME, 3250);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(38, 35));
    set_hit(38);
    set_pen(35);
}


