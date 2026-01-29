/*	This room was created by Jaypeg : 02/09/97
*/


inherit "/d/Emerald/kroad/vamp/cave_base";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


void create_cave_room()
{

    set_short( "Perched inside a crack overlooking the chasm" );
    set_long( "   A sudden gust of wind hits you here, and you "+
      "realise how stifling the air has been inside the eerie, "+
      "dark caverns. The walls here are just as creepy and "+
      "unsettling here as before, even more so, with the wisps "+
      "of light seeping through from above you.\n   Looking up "+
      "you can make out the crack where the fresh air is coming "+
      "from, and what seems to be a spire coming out of the "+
      "wall.\n\n" );


    add_prop( ROOM_I_LIGHT, 0 );

    add_item( ({"spire", "crack", "above"}),
      "You deduct by the squishy feel beneath your feet, the "+
      "faint smell and the horizontal spire that this would "+
      "be a likely perching place for bats.\n" );

    add_item( ({"alchove", "floor"}),
      "This small alchove of unnatural silence and "+ 
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


    add_exit( VAMP_KR_DIR + "cavp6.c", "south", 0 );


}

