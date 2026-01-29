inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <chapel.h>

void
create_room()
{
    add_prop(ROOM_I_NO_CLEANUP, 1);
    set_short("Chapel garden");

    set_long("   You stand in a beautifully terraced garden outside "+
      "of the chapel. There is a smooth stone path that wanders north "+
      "from the gate to the doors of the chapel. It also branches off " +
      "and winds its way along a small creek and over a small stone bridge. "+
      "There is a small pond here, being fed by the small creek that winds its way "+
      "back to the gazebo you can see in the distance.\n\n");

    add_item(({"flower", "flowers"}), "The flowers are absolutely " +
      "breathtaking! There are hundereds of varieties all swaying " +
      "softly in the breeze which surrounds the garden. The blossoms of the  " +
      "flowers seem to beckon to you. Perhaps you could pick one?\n");
    add_item(({"tree", "trees"}), "The trees stand magestically as a  "+
      "border around the entire garden. Their dark green foliage blends " +
      "in harmony with the vibrant colours of the flowers.\n");
    add_item(({"path", "stone", "stones", "ground"}), "The path "+
      "is made of smooth polished stones. The path winds its " +
      "way along the creek and over a small stone bridge, " +
      "winding around the far garden before returning.\n");
    add_item(({"pond", "pool"}), "The pond is crystal clear "+
      "water with sunlight shimmering off of the surface. You " +
      "notice small bubbles on the surface of the water and when " +
      "you take a closer look you can see a school of brightly coloured fish "+
      "swimming and playing close to the surface of the water.\n");
    add_item(({"door", "doors"}), "The chapel doors are made of a " +
      "dark, highly polished wood. The door handles are crafted from crystal, "+
      "fragile looking, yet extremely durable.\n");
    add_item("gazebo","In the distance you see a small white gazebo surrounded by a beautiful garden, not unlike the one you are standing in.\n");
    add_item("creek","This creek is really nothing more that a trickle of water connecting the ponds in the two gardens.\n");
    add_item("bridge","This small bridge is crafted from stones and crosses the creek.\n");
    add_item("garden","As you look at the flowers and trees you can't "+
      "help but think how appropriate it's beauty is "+
      "for being outside of a wedding chapel.\n");
    add_item("gate","You notice the small gate you passed through to "+
      "enter the garden. It seems to stay perpetually ajar.\n");

    add_exit("rectory", "north", "@@check_thrown_out");
    add_exit("outside_chapel","northwest","@@b_msg@@");
}

int
check_thrown_out()
{
    if (this_player()->query_prop(THROWN_OUT) > 2) {
	write("You step up to the doors, but they didn't open. " +
	  "Seems you aren't wanted there.\n");
	say(QCTNAME(this_player()) + " tries to enter the chapel, " +
	  "but cannot open the door.\n");
	return 1;
    }
    write("As you step up to the doors, they magically open.\n");
    write("After you have passed, they silently close.\n");
    return 0;
}

int
b_msg()
{
    write("You step over the bridge toward the gazebo ... \n\n");
    say(QCTNAME(this_player())+" steps over the bridge toward the gazebo.\n");
    return 0;
}

int query_carriage_stop(object carriage) { return 1; }
