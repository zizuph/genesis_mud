#pragma strict_types

inherit "/d/Gondor/morgul/road/mroad";

#include "/d/Gondor/defs.h"

public string
short_desc()
{
    return "A winding road leading to Minas Morgul";
}

public string
long_desc()
{
    return BSN(
    "The road, gleaming faintly, winds deviously up towards "+
    "the city's gate: a black mouth opening in the outer circle of the "+
    "northward walls. The road passes over a white bridge across the foul "+
    "stream to the north. Wide flats lie on either bank of the stream, "+
    "shadowy meads filled with pale white flowers.");
}

public void
create_area_room()
{
  add_item("flowers","The flowers are luminous too, beautiful and yet horrible\n"+
    "of shape, like the demented forms in an uneasy dream, and they give\n"+
    "forth a faint sickening charnel-smell; an odour of rotten-ness fills\n"+
    "the air.\n");
  add_item("bridge","The white bridge glows faintly with a pale light. It\n"+
    "allows the road to pass across the foul stream.\n");
  add_item(({"stream","river","water","morgulduin"}), BS(
    "The Morgulduin is silent, and steaming, but the vapour "+
    "that is rising from it, curling and twisting about the bridge, is "+
    "deadly cold, and smells abominable."));
  add_item("gate","The black gate of Minas Morgul is at the end of the winding\n"+
    "road to the south. The pale glow from the walls around it makes\n"+
    "the gate seem even darker.\n");
  add_item("city","The city lies to the south, its walls and tower glowing with\n"+
    "a pale, luminous light, beckoning for you to come closer....closer...\n");
  add_item("road","The road gleams faintly as it winds deviously up towards the\n"+
    "black gate of the city to the south. North the road passes over the\n"+
    "white bridge across the Morgulduin.\n");
  add_exit(MORGUL_DIR+"road/mbridge",  "northeast", stop_escape, 3);
  add_exit(MORGUL_DIR+"road/mmead4",   "east",      block_npc,   1);
  add_exit(MORGUL_DIR+"city/o_ngate",  "southeast", check_allow, 4);
  add_exit(MORGUL_DIR+"road/mmead3",   "west",      block_npc,   1);

  set_up_herbs( ({ HERB_DIR + "morgurth", HERB_DIR + "angurth" }), 
      ({"bank", "flat", "ground", "meadow"}), 3);

  reset_room();
  enable_reset(200);
  
}

