// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/add/r10.c
// creator(s):       Casca, 11/28/99
// revisions:        Manat, 01/16/01  Made the move to l2/add actually work
// purpose:          
// note:             
// bug(s):           
// to-do:          

inherit "/d/Avenir/common/dark/darkl2_base";

#include "/d/Avenir/common/dark/dark.h"

void
init()
{
    ::init();
    add_action("climbledge","climb");
}

void
create_tunnel_room()
{
    set_short("Ledge");
    set_long("You are within a huge cavern, standing on a large "+
      "ledge high up on its northern wall. "+
      "The cavern itself is huge, with a ceiling hidden in the "+
      "darkness above. "+
      "Below you on the eastern wall is another somewhat larger "+
      "ledge. "+
      "A small cave goes into the wall here.\n");

    add_exit("r10b","north","@@do_pass");

    /*
     * Put additional add_items below. 
     */

    add_cavern();

    add_item(({"cave","small cave","entrance"}),"A small cave goes "+
      "into the wall here. "+
      "It doesn't appear to go very far back.\n");
    add_item(({"ledge","this ledge","north ledge"}),"This ledge "+
      "protrudes from the north wall of the large cavern.\n");
    add_item(({"eastern ledge","east ledge","other ledge"}),
      "There is another ledge on the eastern wall of the cavern "+
      "its lower then this one.\n");
    add_item(({"ceiling","roof","above"}),"The upper reaches of the "+
      "caverns are lost in the darkness and shadows far above.\n");
    add_item("cavern","You are in the midst of a huge cavern "+
      "its ceiling is lost in the darkness above, and the floor "+
      "is far below the ledge on which you stand.\n");
    add_tell("From the edge of vision you see a flash of "+
      "irridescent rainbow-hued light in the darkness above.\n");
    add_tell("A low ghostly howl whispers through the cavern.\n");

    reset_tunnel_room();

}

int
climbledge(string str)
{
    if ((str=="down")||(str=="out")||(str=="to cavern"))
    {
	write("You lever yourself over the edge of the "+
	  "ledge and work your way back down to the "+
	  "floor of the cavern below.\n");
	say(QCTNAME(this_player())+ " climbs over the edge "+
	  "of the ledge and disappears from sight.\n");
	set_dircmd("down");
	TP->move_living("M", L2 +"add/r8");
	tell_room(environment(this_player()), QCTNAME(this_player()) +
	  " descends the northern wall.\n", this_player());
	return 1;
    }

    notify_fail ("Climb what?\n");
    return 0;
}

int 
do_pass()
{

    if (TP->query_wiz_level())
    {
	write("The winged wolf attempts to block you from going north.\n");
	return 0; 
    }

    if ( (present("_winged_wolf", TO)) && (CAN_SEE(TO, TP)) )
    {
	write("The winged wolf blocks your attempt to go north.\n");
	return 1;  
    }
    return 0;
}

