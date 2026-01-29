/* changed add_item for ladder, added add_cmd_item, Amelia 6/9/98 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";

public void
create_room()
{
    set_short("Storage building");
    set_long("This seems to be a"+
        " building where fisherman"+
        " store their supplies and bring their boats in for repair"+
        " when needed. There is a large winch in the far end"+
        " of the room, just in front of a wooden structure"+
        " perfectly shaped to support a smaller boat. Behind"+
        " the winch is a ladder leading up through a hole in"+
        " the ceiling. On pegs"+
        " bolted into the board walls hang many fishing nets"+
        " of all sizes, and you can see a stack of empty"+
        " boxes in a corner. A smell of fish, tar and ocean"+
        " is in the air.\n");
    add_item("building","You are inside a fairly large"+
        " wooden building, built by hardwood boards nailed"+
        " to a supporting structure. It seems to be a"+
        " storage room for some of the fishermen in Gont"+
        " Port.\n");
    add_item("winch","This is a very sturdy winch, securely"+
        " bolted to the floor. It has a wooden handle, long"+
        " enough to allow several people to help out turning"+
        " it and a long strong steel wire winded up on the"+
        " drum. The end of the wire has a hook.\n");
    add_item("handle","The wooden handle is long enough"+
        " to allow several people to work at the winch"+
        " simultaneously.\n");
    add_item("drum","The drum of the winch is vertical"+
        " and made by boards. It holds a wide roll of strong"+
        " steel wire.\n");
    add_item("wire","This strong steel wire is made by"+
        " several narrow threads braided together to form"+
        " a strong pattern. Looking at the wide roll it seems"+
        " to be more than enough to haul something in from the"+
        " water.\n");
    add_item("hook","A large hook is fastened to the end of the wire.\n");
    add_item("structure","This wooden structure is located"+
        " just in front of the winch and seems to be made"+
        " to support a smaller boat so it won't tip over. It"+
        " has four loops made of steel in each corner.\n");
    add_item("walls", "The walls are made from boards, nailed"+
        " together carefully.\n");
    add_item("ladder", "A ladder leads up through a hatch"+
        " in the ceiling. You notice that the rungs on the ladder are"+
        " rotten and broken in places.\n");
    add_item("hatch", "The hatch in the ceiling appears to "+
        "be like a door. It is closed.\n");
    add_item("pegs","Several pegs are bolted into the board"+
        " walls, holding large number of nets.\n");
    add_item("nets","A large number of fishing nets of varying"+
        " sizes hang on the pegs.\n");
    add_item("boxes","The boxes are empty, but after smelling"+
        " them there is no doubt about what they once contained."+
        " Looking closer you can see traces of scales and fish blood"+
        " smeared onto the wood.\n");
    add_item("ceiling","The ceiling is made by strong boards"+
        " nailed onto a structure of supporting girders. You notice"+
        " a block fastened in one of the girders just above the"+
        " wooden structure.\n");
    add_item("block","Looking up you see a block fastened to"+
        " a girder just above the wooden structure. You wonder what"+
        " that could be for.\n");
    add_cmd_item("ladder", "climb", "You try to climb the "+
        "ladder, but your foot breaks through the rung.\n");
    add_exit("city_street/city_road18", "south");
}
