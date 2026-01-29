/* File         : /d/Khalakhor/se_speir/rannoch/village/village_base.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-22         
 * Purpose      : Base village file for the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Major overhaul (Darragh 2003-07-24)
 *                Changed to coord system (Darragh 2003-07-25)
 *                Merged with east village basefile (Daragh 03-07-28)
 */

#pragma strict_types

#include "room.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";

float busy_level;

int G_x,
    G_y;

int climb_wall();
int enter_river();
int side_check;

string room_check;
          
public void
setup_local_coords()
{
    sscanf(file_name(TO),
        "/d/Khalakhor/se_speir/rannoch/village/room/road_%d_%d", G_x, G_y);
    room_check = G_x + "," + G_y;

    if(member_array(room_check, MARKETPLACE_COORDS) != -1 || 
       member_array(room_check, MAIN_ROAD_COORDS) != -1 ||
       room_check == "4,8")
        busy_level = 110.0;
    else if(member_array(room_check, OTHER_BUSY_COORDS) != -1)
        busy_level = 130.0;
    else if(member_array(room_check, WALL_COORDS) != -1)
        busy_level = 180.0;
    else
        busy_level = 150.0;

    if(G_x <= 7)
        side_check = 1; /* West half */
    else
        side_check = 2; /* East half */
}

public int *
query_local_coords()
{
    return ({G_x, G_y});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public int
is_abhainn_ruith_road()
{
    return 1;
}

int
climb_wall()
{
   write("You climb up to the top of the wall with much effort, " +
         "but the sharpened ends of the poles prevents you from " +
         "crossing the wall.\n");

    say(QCTNAME(this_player())+ " tries in vain to climb "
                              + "over the wall.\n");
    return 1;
}

int
enter_river()
{
    if(member_array(room_check, RIVERBANK_COORDS) != -1 || 
                    room_check == "7,6") 
    {    
    write("You decide against doing that, it looks too cold, "
        + "deep and rapid. Getting back up would also be a problem, "
        + "a low but sheer stone wall flanks this side of the river.\n");
    say(QCTNAME(this_player())+ " watches the river briefly, as if "
                              + "considering something.\n");
    return 1;
    }
    else if(member_array(room_check, WALKWAY_WEST_COORDS) != -1)
    {
    write("You decide against doing that, it looks too cold and "
        + "deep. Getting back up seems impossible at this "
        + "point, the poles that the walkway rests upon look "
        + "slippery and slimy.\n");
    say(QCTNAME(this_player()) + " watches the water briefly, as if "
                               + "considering something.\n");
    return 1;
    }
    else if(member_array(room_check, WALKWAY_EAST_COORDS) != -1 ||
            room_check == "10,9")
    {
    write("You decide against that, it is too far down.\n");
    say(QCTNAME(this_player())+ " looks down on the water below.\n");
    return 1;
    }
}   

public void
create_khalakhor_room()
{
    string temp;

    this_object()->create_road();
    setup_local_coords();

    add_item(({"lake","the lake", "loch","loch rannoch","lake rannoch","rannoch"}),
               "The narrow highland lake is surrounded by mountains "
             + "on its east and south side. The north and west sides"
             + "consists of hilly terrain covered in forest. The lake "
             + "is fed by a river that flows in from the north. Its "
             + "outlet is far to the south, another river that meanders "
             + "away from sight between the mountains.\n");
    add_item(({"mountain","mountains","range","mountain range","spine",
               "peaks","peak"}),
               "The mountains rises up from the carpet of forest "
             + "like a great spine on the eastern shoreline of the "
             + "lake, and continuing on its southern end. There it "
             + "diminishes into craggy rock formations and finally "
             + "evens out into the western hills. The northern end "
             + "can not be seen from here, as it continues far "
             + "away northeast.\n");
    add_item(({"village"}),
               "The village is built on both sides of the "
             + "river that comes rushing down from the north, and "
             + "is protected by a high wooden wall. The western "
             + "half lies on flat ground just a little higher than "
             + "the lake, and the eastern half is situated on a "
             + "hillside, allowing a view of the lake and the "
             + "surroundings as well as the rest of the village.\n");
    add_item(({"wall","walls","village wall","village walls","high wall",
               "high wooden wall","wooden wall","defences",
               "village defences"}),
               "To protect the village against intruders, a "
             + "high wooden wall has been built where natural defenses "
             + "are not existant. Such is the case around all the western "
             + "half of the village, along with the northeastern part of "
             + "the eastern half.\n");
    add_item(({"hills","hill"}),
               "All the way west from the lake, the hills continue "
             + "on, as far as you can see. The nearest hilltop looks "
             + "as if it is completely devoid of any vegetation.\n");
    add_item(({"river","stream","flow","inlet"}),
               "The river is what provides the lake with water, "
             + "coming in from the north. Tracing its route north "
             + "you lose sight of it as it between the northern"
             + "forest and hills.\n");
    add_item(({"woods","forest","trees","woodlands","carpet","vegetation"}),
               "The forest grows everywhere possible, on the mountain "
             + "slopes as well as the hillsides of the west all the "
             + "way down to the shoreline.\n");
    add_item(({"shoreline"}),
               "You will need to specify which shoreline you mean.\n");
    add_item(({"west shoreline","western shoreline","strip",
               "narrow strip","western shore","western shore"}),
               "The west shoreline of the lake is lined with a narrow "
             + "strip of bare land, before the forest takes over "
             + "and continues on westward up on the hills.\n");
    add_item(({"north shoreline","northern shoreline",
               "north shore","northern shore"}),
               "The shape of the lake does not allow much of a "
             + "northern shoreline.\n");
    add_item(({"east shoreline","eastern shoreline","wall of rock",
               "rock wall","east shore","eastern shore"}),
               "With the mountains drawing themselves up high "
             + "above the lake casting their reflection onto it, "
             + "the only shoreline there is just a merciless "
             + "wall of rock.\n");
    add_item(({"south shoreline","southern shoreline",
               "south shore","southern shore"}),
               "The shape of the lake does not allow much of a "
             + "southern shoreline, and the distance makes it hard "
             + "to discern any details. The lake should have its outlet "
             + "there, in the form of another river.\n");
    add_item(({"reflection","reflections","images","image"}),
               "The mountains on the east side of the lake casts "
             + "their reflection onto the surface of the lake, "
             + "creating an illusion of even greater height.\n");
    add_item(({"cliff","cliffs","cliffside","cliffsides","rocks"}),
               "From the eastern bank of the river the land rises "
             + "steeply into hills, joining up with the mountains "
             + "further east. This makes the northern shoreline "
             + "into high cliffsides, a perilous place "
             + "to venture with risk of falling down on the "
             + "sharp rocks far below.\n");
    add_item(({"hilltop","top of the hill","summit","hill summit",
               "nearest hilltop"}),
               "You see no details from this distance, although "
             + "there is something there at the top of the hill.\n");
    add_item(({"roof","roofs","thatch"}),
               "Made of thick reeds and straw along with bark and "
             + "grass the thatch looks strong enough to keep rain out "
             + "and warmth in.\n");

    if(side_check == 1)
    {
    add_item(({"view","surroundings"}),
               "You take a quick look at your surroundings. "
             + "catching a glimpse of the woodlands north "
             + "and west of the village. To the south of the village "
             + "lies a lake, with high cliffs running along "
             + "its eastern shoreline forming a natural wall "
             + "at the east side of the village. This part of "
             + "the village is built on the western river bank, "
             + "on much lower ground than the eastern half, which "
             + "lies on a slope on the opposite side of river.\n");
    add_item(({"ground","floor","path","paths","road","roads"}),
               "The frequent showers of rain along with heavy use "
             + "and poor maintenance has created the soft, mushy "
             + "ground you walk on. At some places the ground is "
             + "so broken up that planks have been used to make "
             + "passage possible.\n");
    add_item(({"tower","stone tower","watch tower","watchtower",
               "sentinel"}),
               "Where the eastern half of the village ends at the "
             + "top of the steep cliffs that lines the hill and "
             + "toward the lake, you see a stone tower. You can not "
             + "make out any details from your current position.\n");
    add_item(({"plank","planks","wide plank","wide planks",
               "wooden plank","wooden planks"}),
               "The ground has been so broken up in by some places "
             + "by rain and heavy use that wide planks have been "
             + "used to be able to move around in the village.\n");
    add_item(({"house","houses","buildings","building","warehouse",
               "warehouses","fishing shed","fishing shed","boat-house",
               "boat house","boat-houses","boat houses","shed","sheds",
               "barn","barns"}),
               "The different buildings here are all made of grey wood "
             + "with thatched roofs and no windows. The nature of these "
             + "buildings suggests that they do not house "
             + "people, but things like grain, cattle, boats, "
             + "fishing equipment, and hay.\n");
    }
    else
    {
    add_item(({"view","surroundings"}),
               "You take a quick look at your surroundings. "
             + "catching a glimpse of the woodlands north "
             + "and west of the village. To the south of the village "
             + "lies a lake, with high cliffs running along "
             + "its eastern shoreline and forming a natural wall "
             + "at the east side of the village. This part of "
             + "the village was built on a steep hillside, at the "
             + "eastern bank of a river, flowing out into the "
             + "lake. On the opposite side of river lies the other "
             + "half of the village.\n"); 
    add_item(({"ground","floor","path","paths","road","roads",
               "substance","mud"}),
               "The narrow paths winding between the houses have "
             + "through years of constant use been packed into a "
             + "hard, durable substance. This part of the village "
             + "is situated on a steep hillside, which explains "
             + "why the roads are not a soggy mess, as "
             + "the rain will pour downhill and into the river.\n");
    add_item(({"tower","stone tower","watch tower","watchtower",
               "sentinel"}),
               "The stone tower has been built into the cliffside "
             + "that runs along the east side of the village. "
             + "It reaches up above the cliffs, the upper parts "
             + "in ruins. The base of tower is situated where the "
             + "main road of the village ends, and you can not see "
             + "any windows from your position. By its poor shape "
             + "it looks as if the villagers see no reason to maintain "
             + "it. Due to its elevated position high on the cliffs, "
             + "the view from the top must be breathtaking.\n");
    add_item(({"western village","western half",
               "western half of village",
               "lower village", "lower half",
               "lower half of village"}),
               "From this position, the western half of the village "
             + "seems to consist of a number of grey houses, built "
             + "closely to each other. The center of it is devoid of "
             + "any houses, creating a village square.\n");
    add_item(({"house","houses","buildings","building"}),
               "The different buildings here are all made of "
             + "grey wood, with thatched roofs, low doors and "
             + "small windows with shutters. Most of them seems " 
             + "to be in good shape, to better withstand the "
             + "harsh weather. They are built very close to each "
             + "other, at some places blocking old paths completely, "
             + "or forming narrow alleys.\n");
    add_item(({"door","doors","entrance","entrances"}),
               "The doors to the different houses are as grey and "
             + "dull as the rest of the buildings, with no lock "
             + "visible from the outside.\n");
    add_item(({"shutter","shutters","window","windows","closed shutter",
               "closed shutters"}),
               "Some of the windows are protected by shutters in "
             + "various shapes. Most of them are closed.\n");
    add_item(({"alley","alleway","alleys","narrow alley"}),
               "More a short tight path between buildings, "
             + "the alleys here usually end quickly with nothing "
             + "in them except another house wall.\n");
    
    if(member_array(room_check, WALKWAY_EAST_COORDS) != -1)
    {
    add_item(({"plank","planks","walkway","road","path"}),
               "The walkway is about six feet wide, made of "
             + "thick, strong planks, and supported underneath "
             + "by heavy poles. To prevent people from falling "
             + "down to a certain death below, a long wooden "
             + "railing has been built along the whole walkway.\n");
    add_item(({"pole","poles","heavy pole","heavy poles","support"}),
               "You lean out and look underneath the walkway. "
             + "You see long poles, almost whole tree trunks, "
             + "wedged firmly between the cliff face and the "
             + "walkway. They look well-maintained, and you do "
             + "not doubt the stability of the walkway.\n");
    add_item(({"railing","wooden railing","rail"}),
               "The wooden railing rims the entire walkway, its "
             + "purpose to make the walkway a relatively safe "
             + "place to walk, and it looks enough kept after "
             + "and well constructed to accomplish it.\n");
    add_item(({"alley","alleway","alleys","narrow alley"}),
               "You see no alleys from down here, only the front "
             + "sides of the houses on top of the cliffs.\n");
    add_item(({"house","houses","buildings","building"}),
               "The different buildings here are all made of "
             + "grey wood, with thatched roofs, low doors and "
             + "small windows with shutters. Most of them seems " 
             + "to be in good shape, to better withstand the "
             + "harsh weather.\n");
    }
    }
    if(member_array(room_check, WALL_COORDS) != -1)
    {
    add_item(({"wall","wooden wall","pole","poles","layer","layers",
               "village wall","village walls","high wall",
               "high wooden wall","wooden wall","defences",
               "village defences"}),
               "The wall is made of two layers of wooden poles, "
             + "driven deep into the ground, and reinforced with mud "
             + "and ropes. It looks sturdy enough to keep unwanted "
             + "people out. The top of the poles have been sharpened, "
             + "to prevent anyone from climbing over it.\n");

    add_cmd_item("wall","climb",climb_wall);
    }

    if(member_array(room_check, WALKWAY_WEST_COORDS) != -1)
    {
    add_item(({"plank","planks","wide plank","wide planks",
               "wooden plank","wooden planks","ground",
               "floor","path","paths","road","roads",
               "walkway","walkways"}),
               "You are on a wooden walkway that runs along the "
             + "whole shoreline of the western half of the village, "
             + "about three feet above the water. "
             + "The planks themselves are old and worn, and some "
             + "of them seems to have been replaced recently.\n");
    add_item(({"plank","planks","old plank","old planks",
               "new plank","new planks","replaced plank","replaced planks",
               "board","boards","old board","old boards",
               "new board","new boards","replaced board","replaced boards",
               "wooden plank","wooden planks","wooden board","wooden boards"}),
               "There is little special about the wooden planks you stand on. "
             + "They are in good shape though, it looks as if the villagers "
             + "frequently maintains the walkway.\n");
    }
    if(member_array(room_check, RIVERBANK_COORDS) != -1 ||
                    room_check == "7,6")
    add_cmd_item(({"water","river","stream","current",}),
                 ({"jump","jump into","jump into the",
                   "dive","dive into","dive into the",
                   "enter","plunge","plunge into","plunge into the"}),
                   enter_river);
    else if(member_array(room_check, WALKWAY_EAST_COORDS) != -1 ||
            member_array(room_check, WALKWAY_WEST_COORDS) != -1 ||
                         room_check == "10,9")
    add_cmd_item(({"water","lake","loch","rannoch","loch rannoch"}),
                 ({"jump","jump into","jump into the",
                   "dive","dive into","dive into the",
                   "enter","plunge","plunge into","plunge into the"}),
                   enter_river);

    if(member_array(room_check, MARKETPLACE_COORDS) != -1)
    add_item(({"marketplace","square"}),
               "Something about the market.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        (ROAD_MESSAGES)->start_messages(G_x, G_y, busy_level);
}