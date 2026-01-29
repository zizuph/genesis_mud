/*	This room was created by Jaypeg : 02/18/97
*/


inherit "/d/Emerald/kroad/vamp/cave_base";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"
#include "/d/Emerald/common/guild/vamp/guild.h"

string
entchimney()
{

    if (!IS_MEMBER(TP) && !IS_WIZ(TP))
    {
	write( "You jump up high, but only manage to get some of your arm "+
	  "up into the rock chimney. You fall down and land ungracefully.\n" );
	say( QCTNAME(TP)+" jumps up and tries to fit up and into the narrow "+
	  "chimney, but only manages to get an arm up into it before falling "+
	  "down and landing very ungracefully.\n" );
	return "";
    }
    else
	write( "You close your eyes and focus your subconscious, leaving "+
	  "your physical form to disperse into mist, and quickly glide "+
	  "up through the narrow rock chimney above you.\n" );
    say( QCTNAME(TP)+" dissipates into a mist and floats up into "+
      "the rock chimney above.\n" );

    TP->move_living("up the chimney", KROAD_DIR + "eroad5", 1);

    return "";
}

void
create_cave_room()
{

    set_noshow_obvious(1);

    set_short( "In a lightless, unnatural tunnel" );
    set_long( "   An eerie disquiet falls over you in this tunnel, "+ 
      "your skin crawls in warning. You sense an unnatural "+ 
      "darkness around you, a hungry thirst for the life that "+ 
      "beats within you.\n   The walls "+ 
      "around you are seeping some dark ichor, you think "+ 
      "the better of investigating further. Light seems to be "+ 
      "sucked into the darkness here, although you feel as if "+
      "something is different here, the darkness not as complete, "+
      "the unnatural pierced by a tiny, dim beam of light "+
      "from above.\n\n" );


    add_prop( ROOM_I_LIGHT, 0 );
    add_prop(ROOM_I_INSIDE,1);


    add_item( ({"light", "beam", "beam light"}),
      "Squinting with the effort, you can barely make "+
      "out a tiny, dim beam of light breaking into "+
      "unnatural darkness of these caverns. It seems "+
      "to come from a hole in the ceiling.\n");
    add_item( ({"ceiling", "hole", "chimney"}),
      "The tiny beam of light seems to struggle its "+
      "way through a hole in the ceiling, barely wide "+
      "enough to put your hand in. You guess it must be "+
      "a rock chimney to somewhere far above.\n");
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


    add_exit( VAMP_KR_DIR + "cavw8", "south", 0 );
    add_exit( VAMP_KR_DIR + "bridge1", "north", 0 );

    add_cmd_item( ({"chimney", "hole", "rock chimney"}),"enter", entchimney);
}
