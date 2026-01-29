/*
* Grass lawn in the park.
*
* Coded by Porta 971018.
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/d/Earthsea/herbs/specials/hs";
inherit "/d/Earthsea/lib/room_tell";

#include "/d/Earthsea/herbs/herb_sets/park_herbs.h"
#include <stdproperties.h>
#include <macros.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Wide grass lawn");
    set_long("A wide grass lawn, well-tended and green"+
        ", is planted here just below the high city wall to"+
        " the west. In the middle of the lawn is a fountain"+
        " in shape of a bronze figure holding a staff. The"+
        " water cascades out from the top of the staff, landing"+
        " in the surrounding pond with a splashing sound."+
        " Flowerbeds surround the fountain, with many beautiful"+
        " flowers planted in intricate patterns. Around the lawn"+
        " are groves of trees, and three gravel paths meeting"+
        " by the fountain lead away from this green area.\n");
    add_item("grass","The grass is very green and looks"+
        " well-tended, growing thick on the rich earth.\n");
    add_item("groves","There are several groves of trees"+
        " surrounding this open part of the park. To the"+
        " north and northwest are birches, and to the northeast"+
        " is a grove of very old oak trees.\n");
    add_item("lawn","This open area of the park is planted"+
        " with green grass.\n");
    add_item("wall","The city wall towers up above your head"+
        " to the west, built by cut black stone set closely"+
        " together. Green moss grows in the narrow gaps between the"+
        " rocks.\n");
    add_item("fountain","The fountain looks fairly old,"+
        " with a bronze figure standing on a rock in the middle"+
        " of the pond surrounding it. Water cascades out from"+
        " the top of the staff the figure is holding, landing"+
        " in the pond with a splash.\n");
    add_item("pond","The pond is filled with clear water,"+
        " and you can see pads of water lily, and here and"+
        " there a large white flower.\n");
    add_item(({"flowerbeds","flowers"}),"Flowerbeds are"+
        " bordering the small pond, thriving in the wet earth"+
        " and the water from the fountain. Beautiful blue and"+
        " white flowers are planted in intricate patterns.\n");
    add_item("figure","The bronze figure is shaped as a"+
        " humanoid, but the features of its face is long ago"+
        " eroded leaving you wondering who this could be."+
        " The figure is holding a staff, which cascades water"+
        " high up in the air.\n");
    add_item("staff","The figure holds a staff, also of"+
        " bronze, with water cascading out from the top of"+
        " it.\n");
    add_item("paths","Three gravel paths meet by the"+
        " fountain, and leads to the northeast, northwest and"+
        " west into groves of trees.\n");
    set_up_herbs(select_herb_files(PARK_HERBS), PARK_LOCATIONS, 3);
    add_tell("Water droplets cascade from the fountain, sparkling "+
        "in the sun.\n");
    add_tell("A small fish leaps up in the pond.\n");
    add_tell("Overhead a flock of brightly coloured birds "+
        "flies to the grove of birch trees.\n");
    add_tell("The water makes a musical noise, splashing in the pool.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_exit("park_1", "northeast");
    add_exit("park_3", "north");
    add_exit("park_4", "northwest");
    reset_room();
}

public int
drink_it(string str)
{
    object tp = this_player();

    if(!str || (str != "from fountain" && !parse_command(str, this_object(),
        "'water' [from] [the] [fountain]")))
        return 0;

    if(tp->drink_soft(tp->drink_max()/16, 0))
    {
        write("You cup your hands and take a big drink of water from " +
            "the fountain. You feel refreshed.\n");
        say(QCTNAME(tp) + " kneels down and gets a drink from the " +
            "fountain.\n");
        return 1;
    }

    write("You aren't thirsty at the moment.\n");

    return 1;
}

public void
init()    
{
    ::init();
    add_action(drink_it,  "drink");
}
