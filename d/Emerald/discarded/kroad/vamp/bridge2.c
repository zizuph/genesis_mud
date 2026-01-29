/*	This room was created by Jaypeg : 01/10/97
 *	This is room bridge2.c - Middle of the bridge to
 *	the vamps guild.
 */


inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


void create_room()
{

    set_short( "Balanced on a thin, stone span" );
    set_long( "   You waver dangerously in the winds, trying "+ 
      "to keep yourself from overbalancing and "+ 
      "falling off the thin, stone bridge that you are "+ 
      "standing on, and into the turbulent swell amongst "+ 
      "the black rocks below you.\n   Across the bridge "+ 
      "are the gates to this dark, black temple, and the "+ 
      "nagging panic that has been growing on you is "+ 
      "especially strong here. Dark spires of rigid basalt "+ 
      "encompass the octagonal shrine, you can make "+ 
      "few details out from here.\n   Before you can enter "+ 
      "the shrine, first you must navigate your way across "+ 
      "the rest of this narrow bridge, and past the two "+ 
      "towering blackened stone guardians, demons "+ 
      "of hideous appearance and demeanor.\n\n" );


    add_prop( ROOM_I_LIGHT, -2 );
    add_prop(ROOM_I_INSIDE,1);


    add_item( ({"span", "bridge", "stone bridge"}),
      "You stand precariously on a narrow, stone "+ 
      "bridge, and here at its apex it could not be "+ 
      "more than a foot wide. Strong winds blast "+ 
      "through the chasm, causing you to teeter "+ 
      "and shift your weight. From here you can "+ 
      "go back into the dark caverns, across through "+ 
      "the gates into the shrine before you, or down to "+ 
      "be dashed into the jagged rocks and sucked "+ 
      "under the roaring swell.\n" );
    add_item( ({"winds", "gusts", "strong winds"}),
      "Just like the ocean swell below you, the winds "+
      "become wild and gusty here between the cliff "+
      "faces, whipping here and there at random.\n" );
    add_item( ({"swell", "rocks", "fall", "chasm"}),
      "Here the waves and winds are suddenly "+ 
      "compressed between the cliff walls of "+ 
      "the caverns and the shrine, with dramatic "+ 
      "effect. The winds are unpredictable and "+ 
      "extreme, changing from gentle breezes "+ 
      "to devastating gusts in mere moments.\n"+ 
      "Below you the roughened swell gets sucked "+ 
      "and tossed, crashing amongst the jagged "+ 
      "black rocks that once filled this chasm.\n" );
    add_item( ({"panic", "anxiety", "nausea"}),
      "The gnawing anxiety, that has plagued you "+
      "is intensified here, as you gaze forward at "+
      "the shrine. Its seemingly contemptuous abomination "+
      "of life instills a panic in you that is more than "+
      "just fear, it is the feeling that something more "+
      "ancient and dark than you can imagine is breathing "+
      "hungrily down your neck.\n" );
    add_item( ({"guardians", "demons", "statues",}),
      "Exquisitely horrific vestiges of black stone "+ 
      "stand guard over the gates of the shrine, "+ 
      "their unceasing gaze chilling all who must "+ 
      "approach them.  They take the form of some "+ 
      "type of demon, although it is hard to make "+ 
      "out details, as it seems they waver and twist "+ 
      "in form. Their oppressive height and chilling "+ 
      "gaze, however, never waver.\n" );
    add_item( ({"gates", "temple", "shrine"}),
      "Past the guardians you can make out the "+
      "octagonal shape of the shrine. Black gates "+
      "carved of the basalt of the cliff itself separate "+
      "you from the darkness beyond, and you imagine "+
      "that they are more for containing horrors than "+
      "preventing entry within.\n" );
    add_item( ({"spires", "spire", "rigid basalt"}),
      "From here you can see a black spire, one at "+
      "each point of the octagonal shrine, standing "+
      "rigid and defiant.\n" );

    add_exit( VAMP_KR_DIR + "bridge3.c", "north", 0 );
    add_exit( VAMP_KR_DIR + "bridge1.c", "south", 0 );


}
