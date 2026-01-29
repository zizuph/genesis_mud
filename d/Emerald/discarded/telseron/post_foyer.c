inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#define POST_OFFICE     TOWNSHIP_DIR + "post"
 
void reset_room();
 
void
create_room()
{
    reset_room();
    set_short("The foyer of the post office");
    set_long("   The foyer of the post office is large and " +
        "spacious. The walls are elegantly panelled with fine " +
        "mahogany, give the room a rich and comfortable feeling. "+
        "Couches and easy chairs are placed around the room, " +
        "offering weary travellers a place to sit, chat, and " +
        "relax. From the ceiling hangs an elegant chandelier, " +
        "bathing the room in a soft glow. Travellers wander " +
        "in and out of here as they check their mail. You " +
        "notice an a plaque fastened to a wall.\n\n");
 
    add_item("plaque",
        "It is polished to a bright sheen. Some instructions " +
        "have been engraved on its surface.\n");
    add_cmd_item("plaque", "read", "@@read_sign@@");
    add_item(({"wall", "walls"}),
        "The walls are polished to a deep luster. The walls " +
        "softly reflect the glow of the chandelier.\n");
    add_item(({"panel", "panels"}),
        "The panels are of the finest mahogany you can imagine " +
        "and are evenly grained. When you run your hand across " +
        "them, you are unable to feel the seams of the panels. " +
        "You don't see the seams either.\n");
    add_item("chandelier",
        "The chandelier is made of the finest crystals you've " +
        "seen. The crystals refract the light of the candles " +
        "into a million rainbows which dance across the room. " +
        "behind the crystals, bright candles burn, emitting " +
        "filling the room with light.\n");
    add_item(({"floor", "ground"}),
        "The ground is a hardwood floor. It is polished where " +
        "throw rugs don't cover it.\n");
    add_item(({"throw rug", "throw rugs", "carpet", "carpets", 
            "rug", "rugs"}),
        "The throw rugs are plush and comfortable looking. They " +
        "are a deep burgandy colour with gold designs in them. " +
        "You sigh contently as you wiggle your toes in the " +
        "fibers of the rug.\n");
    
    add_cmd_item("upstairs", "check", "@@people_desc@@");
    add_prop(ROOM_M_NO_ATTACK, 1);
   add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TOWNSHIP_DIR + "post", "up", "@@upstairs@@");
    add_exit(TOWNSHIP_DIR + "rd17", "out");
}                    
 
void
reset_room()
{
}
 
string
read_sign()
{
    return "          \n"+
      "             ______________________________________________  \n"+
      "            |\\____________________________________________/|\n"+
      "            | |                                          | | \n"+
      "            | | Here in the foyer, you may chat with     | | \n"+
      "            | | whoever is present. To see who is in the | | \n"+
      "            | | post office, you may <check upstairs>.   | | \n"+
      "            | |__________________________________________| | \n"+
      "            |/____________________________________________\\|\n"+
      "\n\n";
}
 
 
string
people_desc()
{
    object other_room;
    mixed opeople;
 
    if (!LOAD_ERR(POST_OFFICE))
        other_room = find_object(POST_OFFICE);
    else
        return "The office seems hazy and fuzzy. Perhaps there is "+
            "something wrong with it? Perhaps a wizard could help?\n";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        return "The post office is deserted and quiet.\n";
    else
        return "From here, you can see "+COMPOSITE_LIVE(opeople)+
            " upstairs in the post office.\n";
}

int upstairs()
{
    write ("You ascend the stairs to the post office.\n");
 
    say(QCTNAME(TP) + " ascends the stairs to the post office.\n");
}
