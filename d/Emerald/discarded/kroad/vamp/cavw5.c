/*	This room was created by Jaypeg : 02/08/97
        Added exit slide 02/19/98 - Jaypeg
*/


inherit "/d/Emerald/kroad/vamp/cave_base";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


void create_cave_room()
{

    set_noshow_obvious(1);

    set_short( "In a lightless, unnatural tunnel" );
    set_long( "   An eerie disquiet falls over you in this tunnel, "+ 
      "your skin crawls in warning. You sense an unnatural "+ 
      "darkness around you, a hungry thirst for the life that "+ 
      "beats within you.\n   The walls "+ 
      "around you are seeping some dark ichor, you think "+ 
      "the better of investigating further. Light seems to be "+ 
      "sucked into the darkness here, and you find yourself "+
      "unable to see any escape, nor tell what direction you "+
      "are heading. You do notice a large smooth hole in the north "+
      "wall, but see nothing inside it but darkness.\n\n" );


    add_prop( ROOM_I_LIGHT, -2 );
    add_prop(ROOM_I_INSIDE,1);


    add_item( ({"tunnel", "passage", "floor"}),
      "This narrow tunnel of unnatural silence and "+ 
      "darkness presses in apon you leaving you "+ 
      "feeling clammy and disoriented. The walls "+ 
      "drip some unspeakable ichor, and the floor "+ 
      "you cannot even see by lowering your light "+ 
      "source to it.\n" );
    add_item( ({"disquiet", "feeling"}),
      "There is a feeling of terror brewing within "+ 
      "you, the aura of unlife and chaos unspeakable "+ 
      "here makes you feel nauseous and panicky.\n" );
    add_item( ({"ichor", "moisture", "walls"}),
      "An undiscribable ichor seeps from the walls, "+ 
      "its moist surface being one of the few things "+ 
      "you can make out here in this tunnel amongst "+ 
      "the unnatural darkness.\n" );
    add_item( ({"hole", "smooth hole", "large hole"}),
      "Low down on the north wall gapes a large hole, "+
      "not quite perfectly round in shape, and easily "+
      "large enough for you to enter. The surface is "+
      "slippery and seems to go down into darkness.\n");


    add_exit( VAMP_KR_DIR + "cavw3.c", "south", 0 );

}

void init()
{
    ::init();
    add_action("enterhole", "enter");
}

int enterhole(string hole)
{
    notify_fail("enter what?\n");

    if (hole!="hole") return 0;
    write("You swing your legs into the whole and find your"+
    "self sliding quickly into darkness.\n\n\nSuddenly the "+
    "slide is gone and you feel yourself falling...\n\n\n");
    say(QCTNAME(TP)+" dissapears into the dark whole.\n");

    TP->move_living("down the hole into darkness", VAMP_KR_DIR 
      + "fallroom");

    return 1;

}