/*	This room was created by Jaypeg : 01/04/97
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
      "beats within you.\n   You can now barely trace the outline of "+ 
      "the secret door that you know stands right by you, "+ 
      "it is virtually invisible to you from here. The walls "+ 
      "around you are seeping some dark ichor, you think "+ 
      "the better of investigating further. Light seems to be "+ 
      "sucked into the darkness here, but you can make "+ 
      "out the tunnel continuing further to the south.\n\n" );


    add_prop( ROOM_I_LIGHT, -2 );
    add_prop(ROOM_I_INSIDE,1);


    add_item( ({"tunnel", "passage"}),
      "This narrow tunnel of unnatural silence and "+ 
      "darkness presses in apon you leaving you "+ 
      "feeling clammy and disoriented. The walls "+ 
      "drip some unspeakable ichor, and the floor "+ 
      "you cannot even see by lowering your light "+ 
      "source to it.  The tunnel continues south.\n" );
    add_item( ({"disquiet", "feeling"}),
      "There is a feeling of terror brewing within "+ 
      "you, the aura of unlife and chaos unspeakable "+ 
      "here makes you feel nauseous and panicky.\n" );
    add_item( ({"ichor", "moisture", "walls"}),
      "An undiscribable ichor seeps from the walls, "+ 
      "its moist surface being one of the few things "+ 
      "you can make out here in this tunnel amongst "+ 
      "the unnatural darkness.\n" );
    add_item( ({"door", "secret door"}),
      "Although you know there is a secret door "+
      "here in the north wall, you can't find "+
      "any trace of it now.\n" );

    add_exit( VAMP_KR_DIR + "cav2.c", "south", 0 );


}

init()
{
::init();
     add_action( "tracedoor", "trace");
}

int tracedoor( string door )
{

notify_fail( "Trace what?\n" );

if (door!="door") return 0;

write( "You trace the barely visible outline of the door with a "+
"fingertip, and after a second pause the door is gone leaving "+
"just the open portal.\n" );
say( QCTNAME(TP)+" seems to consider the door, then suddenly "+
"steps through into the darkness. You try to follow, but find "+
"the door still shut.\n" );

TP->move_living( "into the darkness", "/d/Emerald/kroad/vamp/pit.c" );

return 1;

}
