#pragma strict_types
#pragma no_clone

#include <stdproperties.h>
inherit "/std/room";

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("On the stairway");
    set_long("You are climbing about halfway"+
        " up on a narrow stairway cut straight out of"+
        " the granite cliff. Some distance above your"+
        " head you see the edge of the cliff, and"+
        " the stone tower on top of it rising high"+
        " up towards the sky. Northwards you have"+
        " an excellent view over the city of Gont"+
        " Port, and beyond that the open farmland."+
        " In the distance, far to the north is"+
        " a snow-capped mountain visible between"+
        " the clouds. The only ways to continue"+
        " are either climbing on towards the top or"+
        " descend the stairway to the street again.\n");
    add_item("stairway","You are climbing about"+
        " halfways up on a narrow stairway, leading"+
        " up a steep cliff. The steps are cut straight"+
        " out from the granite rock, and are rough and"+
        " uneven.\n");
    add_item("tower","Above your head a stone"+
        " tower rises high up towards the sky. You"+
        " might get to it if you manage to climb"+
        " the stairs.\n");
    add_item("cliff","You are climbing one"+
        " of the famous Armed Cliffs, guarding the"+
        " entrance to Gont Port. The granite cliff"+
        " is very steep, and you have an excellent"+
        " view over your surroundings from it.\n");
    add_item("city","Northwards the city of"+
        " Gont Port spreads out, with high towers,"+
        " large stone building and a very busy harbour"+
        " with hundreds of ships anchored in it.\n");
    add_item("view","The view from this elevated"+
        " position is excellent. You can see the whole"+
        " city below and beyond the rolling green"+
        " farmland disappearing in the distance in"+
        " a range of high hills. Far away is a"+
        " snow-capped mountain barely visible through"+
        " the clouds and fog surrounding it.\n");
    add_item("mountain","This must be Gont Mountain,"+
        " a volcano still erupting once in a while. The"+
        " high peak is covered with snow and enshrouded"+
        " in swirling clouds and mist.\n");
    add_item("hills","The hills in the distance"+
        " are clad with lush green forest, and look"+
        " very inviting. You think you can catch a"+
        " glimpse of a stream, winding its way through"+
        " the forest with the sunlight reflecting on"+
        " the water.\n");
    add_item("farmland","Just north of the city"+
        " is rolling farmland, with acre after acre"+
        " with fields. You can see a few small villages"+
        " as well in the distance.\n");
    add_item("forest","Green forest climb the"+
        " sides of the high hills. Looking at the"+
        " colour you think it might be pine, here and"+
        " there mixed up with the darker green shade"+
        " of spruce trees.\n");
    add_item("harbour","The busy harbour of Gont"+
        " Port is just below, with hundreds of ships"+
        " anchored by the three piers stretching out"+
        " far into the bay from the east, west and"+
        " north.\n");
    add_exit("e_cliff1", "up");
    add_exit("city_street/city_road23", "down");
}
