/*	This room was created by Jaypeg : 02/09/97
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
      "are heading.\n\n" );


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


    add_exit("cavp8", "north");
    add_exit("cavp10", "southeast");
}

