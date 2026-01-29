/*
 * modification log:
 * Stern march 2000, added OBJ_I_CONTAIN_WATER property
 */

inherit "/d/Gondor/rohan/entwash/stream";


#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define LOG_ENTER            "/d/Gondor/log/entwash"

//  Prototypes
string  crossing();
void    stream();

void
create_stream()
{
    set_extra_long("The river Entwash has split into two major"
      + " offshoots, the southermost one being due west of here. The"
      + " ground has grown very muddy here, and small streams are"
      + " running off from the main flow of the river. Directly to the"
      + " east the Entwash fragments entirely and the area known as the"
      + " Mouths of the Entwash begins. It grows very marshy in that"
      + " direction.");

    set_flow("southeast");

    add_item(({"river","rivers","streams","stream","entwash",
        "river entwash"}), BSN(
        "The river has begun to fragment here into many smaller streams"
      + " which flow off into a very marshy area to the east."));
    add_item(({"ground"}), BSN("The ground here has grown very wet and"
      + " muddy. Many streams and smaller trickles are running off"
      + " from the main waterway causing a break in the terrain."));

/*
    add_exit(ENTWASH_DIR + "str5", "northwest");
 */
    add_exit(ROH_DIR + "plains/d15", "west", crossing, 5);
    add_exit(ENTWASH_DIR + "ent1a", "east", stream, 2);
    add_prop(OBJ_I_CONTAIN_WATER,-1);
}

int
crossing()
{
    int diff = 10 + random(10),
        swim = TP->query_skill(SS_SWIM);

    if (diff > swim)
    {
        write("You attempt to swim across the Entwash, but are confounded"
          + " by the current which flows through this narrow channel.\n");
        say(QCTNAME(TP) + " enters the river to swim across, but"
          + " soon returns to shore, wet and dripping.\n");

        return 1;
    }

    write("You enter the cold water, and swiftly swim across the river.\n");
    say(QCTNAME(TP) + " enters the cold water, and swims to the"
      + " western shore.\n");

    return 0;
}

void
stream()
{
    write("You cross the shallow stream fragmenting out from the Entwash.\n");

}
