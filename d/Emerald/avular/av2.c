/*
 * AV2.c
 * Bridge on a road in Avular
 * - Alaron JAN 2000
 */

#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit AVULAR_ROOM;

int check_bridge();

void
create_avular_room()
{
    set_short("A serpentine bridge");
    set_em_long("The street here is at a strange intersection. A north-south section of "+
            "street runs beneath the bridge here. The scene, however, is dominated "+
            "completely by the bridge itself. The dark stone winds to the left, then right, "+
            "then back again, all the while arching up and down then up and down again. Simply "+
            "trying to follow the course of the bridge with your eyes is dizzying. At "+
            "the east end, the bridge starts narrow, gradually widening until at the west "+
            "end, the stone bridge expands into the giant shape of a snake's head, its fangs "+
            "plunged deep within the earth. A myriad of thousands of "+
            "individually carved scales adorned the serpentine sculpture's back.\n");

    add_item( ({"bridge", "winding bridge", "snake bridge", "snake", "stone bridge", "serpent"}),
             "The bridge is frightening, disturbing, and a marvel of architecture "+
             "and design all at the same time. The bridge winds from left "+
             "to right and back again, all the while arching upward and then "+
             "back down. At the east end, it is narrow, with thousands of small, curved "+
             "ridges carved into it. At the far west, it widens into the form of an "+
             "enormous snake head, its dark stone fangs sinking deep into the cobblestone "+
             "road beyond. Surveying the awesome site again, you notice that the thousands "+
             "of intricate, unique ridges carved into the stone bridge are actually scales "+
             "carved into the back of this massive, cold stone serpent.\n");

    add_item( "fangs",
             "The fangs of the stone snake disappear in carefully carved holes in the "+
             "cobblestone road on the west end of the bridge, adding more to the "+
             "illusion that the snake uncoiled across the gap and latched itself into "+
             "place on the west side.\n");

    add_item( "scales",
             "The scales carved into the surface of the bridge, which doubles as the back "+
             "of the serpent, are all carved with unimaginable precision, yet each and every "+
             "one has a unique, almost random shape. This attention to detail in the carving "+
             "of the scales adds to the already eerily lifelike quality of the stone snake.\n");

    add_item( ({"road", "street", "stone street", "stone road", "cobblestone road"}),
             "The precisely placed and carved cobblestone road runs east-west here. A "+
             "huge, twisting, arching stone sculpture of a snake forms a bridge leading "+
             "west over another street further below.\n");

    add_item( ({"another street", "other street", "below", "street below", "under bridge"}),
             "The snake-bridge arches up and over a street which runs north-south here. You "+
             "attempt to peer further up and down this street, but see nothing but a wall "+
             "of darkness that always seems to be pushing in toward you.\n");

    add_cmd_item( ({"snake", "bridge", "serpent", "scales"}),
                  ({"touch", "poke", "prod", "kick", "feel"}),
                  "Even though you can clearly tell that the snake sculpture is made "+
                  "of stone, the slick, dark, finely-chiseled scales almost feel like "+
                  "that of a real snake. The effect is quite frightening and "+
                  "disturbing.\n");

    add_exit(AVMAIN+"av42", "west", check_bridge);
    add_exit(AVMAIN+"av1", "east");
}

int
check_bridge()
{
    if (this_player()->query_base_stat(SS_DEX) < 70)
    {
        if ( random(5)  == 0)
        {
            write("You become dizzy, and are forced to crawl across the bridge "+
                "the rest of the room.\n");
            say(QCTNAME(this_player()) + " becomes dizzy and decides to crawl "+
                "across the bridge the rest of the way.\n");
            return 0;
        }
        else
        {
            write("You lose your balance trying to get across the winding, "+
                "serpentine bridge and slip and stumble back to the snake's "+
                "tail.\n");
            say(QCTNAME(this_player()) + " loses " + this_player()->query_possessive() +
                " balance trying to get across the winding, serpentine bridge and "+
                "slips and stumbles back to the snake's tail.\n");
            return 1;
        }
    }
    else
    {
        write("You carefully manage to get across the bridge, feeling slightly unbalanced, "+
            "but otherwise unbothered.\n");
        say(QCTNAME(this_player()) + " manages to get across the bridge, appearing fairly "+
            "unaffected by the twisting, arching curves of the snake.\n");
        return 0;
    }
}
