// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/add/r9.c
// creator(s):       Casca, 11/29/99
// revisions:        Manat, 01/16/01  Made the move to l2/add actually work
// purpose:          
// note:             
// bug(s):           
// to-do:          Tell room r8.c when person climbs down from here.
//                 Add to the long description a description of the livings 
//                   in the cavern below. like the hill in the bazaar.


inherit "/d/Avenir/common/dark/darkl2_base.c";

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
        "ledge high up on its eastern wall. "+
        "The cavern itself is huge, with a ceiling hidden in the "+
        "darkness above. "+
        "Against its northern wall and above this one, you can "+
        "see another ledge nearly as large as this one. "+
        "The ledge you are on shows paw-prints in the dust and dirt "+
        "as well as scratches in the rock itself. "+
        "Tufts of golden brown fur drift about in the wind. "+
        "A small cave goes into the wall here.\n");
                                

    add_exit("r9b","east","@@do_pass@@");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"cave","small cave","entrance"}),"A small cave goes "+
        "into the wall here. "+
        "It doesn't appear to go very far back.\n"+
        "You can smell a distinct animal odor here.\n");
    add_item(({"ledge","this ledge","east ledge"}),"This ledge "+
        "protrudes from the eastern wall of the large cavern.\n");
    add_item(({"northern ledge","north ledge","other ledge"}),
        "There is another ledge on the northern wall of the cavern "+
        "its higher up then this on.\n");
    add_item(({"floor","ground"}),"The surface of the ledge is "+
        "covered with dirt and dust. Hundreds of paw prints are "+
        "evident in the dirt and dust. You can also see faint "+
        "scratch marks in the rock.\n");
    add_item(({"ceiling","roof","above"}),"The upper reaches of the "+
        "caverns are lost in the darkness and shadows far above.\n");
    add_item(({"prints","paw prints","tracks"}),"There are many prints "+
        "in the dirt and dust of the floor. Most are obscured by time "+
        "and overlapping tracks, but the whole prints you can see "+
        "appear to be that of a large wolf or dog.\n");
    add_item(({"fur","tufts"}),"Balls of golden fur swirl about the "+
        "floor in the gently wind.\n");
    add_item("cavern","You are in the midst of a huge cavern "+
        "its ceiling is lost in the darkness above, and the floor "+
        "is far below the ledge on which you stand.\n");

    add_tell("From the edge of vision you see a flash of "+
        "irridescent rainbow-hued light in the darkness above.\n");
    add_tell("A tuft of fur, caught in an eddy of wind, swirls about "+
        "the floor.\n");
    add_tell("A low ghostly howl whispers through the cavern.\n");



    reset_tunnel_room();

}

int 
climbledge(string str)
{

    if (!str)
    {
        write ("Climb what?\n");
        return 1;
    }

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
            " descends the eastern wall.\n", this_player());
                return 1;
        }
}


int 
do_pass()
{

    if (TP->query_wiz_level())
    {
        write("The winged wolf attempts to block you from going east.\n");
        return 0; 
    }

    if ( (present("_winged_wolf", TO)) && (CAN_SEE(TO, TP)) )
    {
        write("The winged wolf blocks your attempt to go east.\n");
        return 1;  
    }
    return 0;
}

