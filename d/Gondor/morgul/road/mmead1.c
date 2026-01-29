#pragma strict_types

inherit "/d/Gondor/morgul/road/mroad";

#include "/d/Gondor/defs.h"

public string  do_smell();

static object  Snake;

public string
short_desc()
{
    return "on a meadow by the white bridge in the Morgul Vale";
}

public string
long_desc()
{
    return BSN(
        "You are standing just north of the white bridge, by the side " 
      + "of the road on a shadowy meadow on the bank of the Morgulduin. " 
      + "The road is to the northeast. The vapour rising from the water " 
      + "in the river below is deadly cold and seems to grope for you.");
}

public void
create_area_room()
{
    add_item(({"vale","imlad morgul","morgul vale"}), BSN(
        "The Imlad Morgul, or Vale of Black Sorcery, continues further "
      + "east, narrowing to a dark cleft in the mountain-range. A foul-smelling "
      + "stream runs in the middle of the valley, and the walls of Minas Morgul "
      + "stand upon a hill on the further side. "));
    add_item(({"gate","walls","mouth"}), BSN(
        "The gate is dark in the glowing walls of the city; a black "
      + "mouth opening in the outer circle of the northward walls. "));
    add_item(({"city","tower","glow"}), BSN(
        "The pulsating glow of the city is almost enchanting to "
      + "look upon, and the luminous Tower of the Moon fills you with a desire "
      + "to run up the gleaming road to the dark gate. "));
    add_item("bridge","The white bridge gleams pale above the dark stream.\n");
    add_item(({"water", "stream","river","morgulduin"}), BSN(
        "The dark fuming water of the stream radiates a foul smell almost "
      + "unbearable to breathe in."));
    add_item(({"wall","rock wall"}), BSN(
        "North of the road, a rock wall is running alongside the road, " 
      + "probably to prevent rocks sliding down the steep slopes of the " 
      + "mountains north of the road from tumbling onto the road."));
    add_item(({"road"}), BSN(
        "The road continues north of the Morgulduin to the west, leading " 
      + "out of the valley. To the south, it crosses the river and runs " 
      + "up towards the gates of Minas Morgul."));
    add_item(({"bank", "flat", "ground", "meadow"}), BSN(
        "On wide flats on either bank are shadowy meadows. In some " 
      + "places they are filled with pale white flowers that give " 
      + "forth a faintly sickening smell that mingles with the vapour " 
      + "rising from the Morgulduin."));

    add_cmd_item(({"water", "fume", "fumes", "smell", }), "smell", do_smell);

    add_exit(MORGUL_DIR +"road/mrd3","northeast", stop_escape);

    set_up_herbs( ({ HERB_DIR + "morgurth", HERB_DIR + "angurth" }), 
		  ({"bank", "flat", "ground", "meadow"}), 3);

    reset_room();
    enable_reset(200);
}

public void
reset_room()
{
    ::reset_room();

    if (!objectp(Snake))
    {
        Snake = clone_npc(Snake, NPC_DIR + "snake");
        Snake->set_restrain_path(MORGUL_DIR +"road");
        Snake->set_random_move(4);
        Snake->set_whimpy(80);
        Snake->set_poison_frequency(20);
    }
}

public string
do_smell()
{
    TP->command("puke");
    return "The fumes make you feel sick.\n";
}
