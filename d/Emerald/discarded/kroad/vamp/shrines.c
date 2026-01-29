/*	This room was created by Jaypeg : 01/14/97
 *      This room is ShrineS.c, the southernmost
 *      tip of the shrine of darkness.
 */


inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


void create_room()
{

    set_short( "Southern point of the shrine of darkness" );
    set_long( "   The aura of ancient darkness here swirls like "+ 
      "molasses, leaving you nauseated and dizzy. "+ 
      "You stand weak-kneed at the southern-most "+ 
      "point of the shrine, an ebony spire of basalt "+ 
      "and a blood-stained marble tablet "+ 
      "immediately in front of you, and behind you "+ 
      "the guardians of the gate loom over you.\n   "+ 
      "From here you may proceed to the next tablet, "+ 
      "either to the west'nor'west or east'nor'east, or "+ 
      "follow the clean, narrowing runnel down "+
      "a gentle slope into the "+ 
      "centre of the bowl.\n\n" );


    add_prop( ROOM_I_LIGHT, -2 );
    add_prop(ROOM_I_INSIDE,1);


    add_item( ({"aura", "darkness", 
	"ancient darkness", "nausea", "anxiety",}),
      "The nagging anxiety and gut-twisting "+ 
      "nausea that has been eating away at "+ 
      "at you is as strong here as you felt "+ 
      "from the gates behind you, but the "+ 
      "gruesome sight of the sacrificial "+ 
      "tablets and blood runnels add a "+ 
      "visual aspect that drives you to "+ 
      "the edge.\n" );
    add_item( ({"shrine", "temple", "octagon",}),
      "The octagonal shrine you now stand "+ 
      "in overwhelmes your mortal senses. "+ 
      "The shifting shapes and shadows, "+ 
      "the heady, musky smell of old blood, "+ 
      "and the sound of the wind and waves "+ 
      "twisted by the dark aura confuse and "+ 
      "belittle you.\nThe eight cardinal "+
      "points of the shrine are each marked "+
      "with a shrine and tablet, and from "+
      "each runs a grisley runnel of sinister "+
      "means, forming the shape of a bowl.\n" );
    add_item( ({"centre", "center", "bowl",}),
      "The shrine's octagonal points meet "+ 
      "at the centre, in whole seeming like "+ 
      "bowl of blood. Narrow runnels from "+ 
      "each of the tablets run down to a "+ 
      "xxxx below you.\n" );
    add_item( ({"runnel", "runnels", "blood",}),
      "Narrow runnels take shape under the "+ 
      "tablets, obviously designed to "+ 
      "channel the blood spilt from the tablet "+ 
      "down into the centre of the bowl-"+ 
      "shaped shrine.\n" );
    add_item( ({"spire", "tablet", "tablets",}),
      "Before you, and at each of the eight "+ 
      "points of the octagonal shrine, a "+ 
      "black spire and a whitish marble "+ 
      "tablet sit, and from the dried blood "+ 
      "trails their purpose is much too "+ 
      "obvious. The spire is of the blackest "+ 
      "basalt, standing at least the height of "+ 
      "two men, and the wide tablet of marble "+ 
      "spreads its grisley flat surface before "+ 
      "you.\n" );
    add_item( ({"guardians", "gate", "statues",
	"demons"}),
      "Looming behind you are the two gate "+
      "guardians, demons of hideous and "+
      "frightening demeanor, carved from the "+
      "rock of the shrine itself.\n" );


    add_exit( VAMP_KR_DIR + "shrinesw.c", "wnw", 0 );
    add_exit( VAMP_KR_DIR + "shrinese.c", "ene", 0 );
    add_exit( VAMP_KR_DIR + "shrinec.c", "down", 0 );
    add_exit( VAMP_KR_DIR + "bridge3.c", "south", 0 );

}

