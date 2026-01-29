/*
    example2.c

    Example of an outside room.
    Based on the port district room s26.c

    Outside rooms hear the Kabal bell, and have a line
    with the street description in the long desc.

    Fysix@Genesis, March 1998
 */

#include "default.h"

inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Narrow Street");
    set_long("You are travelling along a narrow street " +
      "somewhere within the Port District. " +
      "The cobblestones underfoot are moist and covered " +
      "with a greenish grime. " +
      "The road here bends, and travels northward towards " +
      "the base of a huge cliff and eastward into the distance. " +
      "A large wooden building lies to your west and " +
      "south, while another similar structure is to " +
      "the northeast.\n" +
      "@@query_street_desc@@");

    // Room is outside so we hear the bell, see /d/Kalad/DOC/CLOCK.README
    set_hear_bell(1);

    add_item(({"narrow street", "street", "road"}),
      "A small cobblestoned roadway winding its way " +
      "among the buildings of the district.\n");
    // Ground item is always present outside
    add_item(({"ground", "pavement", "cobblestones", "cobblestone"}),
      "The pavement is worn and cracked, " +
      "and seems to be covered in a thin film of moisture.\n");
    add_item(({"greenish grime", "grime"}),
      "Rootless plants, such as moss and lichen cover " +
      "he pavement, apparently sustained by the constant " +
      "amount of water present.\n");
    add_item(({"base", "huge cliff", "cliff"}),
      "A towering sheer-faced " +
      "cliff that rises further to the north.\n");
    add_item(({"large wooden building", "large building",
	"wooden building", "building"}),
      "A rather large structure made out of hardwood planks. " +
      "It is most likely some sort of warehouse. " +
      "Immediately to the south is a large " +
      "sign hanging in front of it.\n");
    add_item(({"similar structure", "structure"}),
      "It appears to be a smaller " +
      "version of the large wooden building.\n");

    // Add sky to outside rooms, might return some real weather
    // thingies soon.
    add_sky();

    add_sign(({"large sign", "sign"}), "read",
      "\n" +
      "                   %%%%%%%%%%%%%%%%%%%%%%%%\n" +
      "                   %         THE          %\n" +
      "                   %       HALFLING       %\n" +
      "                   %     B R E W E R Y    %\n" +
      "                   %     -------------    %\n" +
      "                   % The finest, tastiest %\n" +
      "                   %      beer ever!      %\n" +
      "                   %      ----------      %\n" +
      "                   % Est. 1304            %\n" +
      "                   %%%%%%%%%%%%%%%%%%%%%%%%\n");

    add_exit(PORT + "s10", "north");
    add_exit(PORT + "s27", "east");
    add_exit(PORT + "s39", "south");
}

