inherit "/d/Gondor/morgul/road/mroad";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public string
short_desc()
{
    return "upon the white bridge crossing the Morgulduin";
}

public string
long_desc()
{
    return BSN( 
    "You are standing on the pale glowing bridge over the "+
    "Morgulduin stream. The road passes across the bridge, leading south "+
    "towards the black gate of Minas Morgul, while it turns west leading "+
    "out of the vale on the north side of the bridge. An unbearable foul "+
    "smell is rising from the stream, causing you to gag and feel nauseated "+
    "and a certain urge to get away from the bridge. At the head of the "+
    "bridge stand some stone figures.");
}

public void
create_area_room()
{
    add_item("bridge", BSN("The bridge is made of white stone, but there "
      + "is a strange pale light in it, as if sorcery is at work. "
      + "Wide banks lie on either bank, shadowy meads filled with pale "
      + "white flowers. From mead to mead the bridge springs, and stone "
      + "figures stand at its head."));
    add_item("figures", BSN("Stone figures stand at the head of the bridge, " +
	     "carven with cunning in forms human and bestial, but all " +
	     "corrupt and loathsome.")); 
    add_item("road", BSN("The cobblestone road leads south towards the city, and "+
    "turns west to the north of here, tall stone walls on both sides of it."));
    add_item("walls","There are tall stone walls on both sides of the road to "+
	     "the north.\n");
    add_item(({"stream","river","water"}), BSN(
        "An unbearable foul smell is rising from the Morgulduin. The water flowing " +
        "beneath the bridge is silent, and it is steaming, but the vapour that is " +
	"rising from it, curling and twisting about the bridge, is deadly cold."));
    add_exit(MORGUL_DIR +"road/mrd3","north",     stop_escape);
    add_exit(MORGUL_DIR +"road/mrd4","southwest", check_allow);
}
