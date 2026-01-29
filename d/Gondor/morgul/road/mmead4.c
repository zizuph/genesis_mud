#pragma strict_types

inherit "/d/Gondor/morgul/road/mroad";

#include "/d/Gondor/defs.h"

public string
short_desc()
{
    return "on a meadow by the white bridge in the Morgul Vale";
}

public string
long_desc()
{
    return BSN(
    "You are standing just south of the white bridge, by the side " +
    "of the road on a shadowy meadow on the bank of the Morgulduin. " +
    "The road is to the west. The vapour rising from the water " +
    "in the river below is deadly cold and seems to grope for you.");
}

public void
create_area_room()
{
    add_item(({"vale","imlad morgul","morgul vale"}), BSN(
        "The Imlad Morgul, or Vale of Black Sorcery, continues further "+
        "east, narrowing to a dark cleft in the mountain-range. A "+
        "foul-smelling stream runs in the middle of the valley, and the "+
        "walls of Minas Morgul stand upon a hill to the south."));
    add_item(({"gate","walls","mouth"}), BSN(
        "The black gate of Minas Morgul is at the end of the winding "+
        "road. The pale glow from the walls around it makes "+
        "the gate seem even darker."));
    add_item(({"city","tower","glow"}), BSN(
        "The pulsating glow of the city is almost enchanting to "+
        "look upon, and the luminous Tower of the Moon fills you with a "+
        "desire to run up the gleaming road to the dark gate. "));
    add_item("bridge","The white bridge gleams pale above the dark stream.\n ");
    add_item(({"stream","river","water","morgulduin"}), BSN(
        "The Morgulduin is silent, and steaming, but the vapour "+
        "that is rising from it, curling and twisting about the bridge, is "+
        "deadly cold, and smells abominable."));
    add_item("road",BSN(
        "The road gleams faintly as it winds deviously up towards the "+
        "black gate of the city to the south. North the road passes "+
        "over the white bridge across the Morgulduin."));
    add_item(({"bank", "flat", "ground", "meadow"}), BSN(
        "On wide flats on either bank are shadowy meadows. In some " +
        "places they are filled with pale white flowers that give " +
        "forth a faintly sickening smell that mingles with the vapour " +
        "rising from the Morgulduin."));
    add_exit(MORGUL_DIR +"road/mrd4","west", stop_escape);

    set_up_herbs( ({ HERB_DIR + "morgurth", HERB_DIR + "angurth", HERB_DIR + "myrtle", }), 
 		  ({ "bank", "flat", "ground", "meadow"}), 3);

    enable_reset(200);
}

