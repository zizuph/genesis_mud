/*    Cliff1.c, re-written by Jaypeg 26th Jan 97
 *    This is the cliff wall under the Kahlen bridge,
 *    where players can make their way down the cliff
 *    or to the underside of the bridge, or quite
 *    possibly in some deep water ;)
 */


inherit "/std/room";
inherit "/d/Emerald/kroad/vamp/lib/out_vamp_tellroom";
inherit "/d/Emerald/kroad/vamp/climbroom";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"

int climbupdown(string str);

void create_room()
{ 
    ::create_room();

    set_short( "Clinging to a cliff face of a chasm, underneath "+
        "a stone bridge" ); 
    set_long( "   Your fingers wedged desperately in the cracks, "+
        "you cling tenaciously for your life against the slick, "+
        "sheer cliffs of basalt, framing a chasm that ends "+
        "far, far too far down for your liking.\n"+
        "   Immediately above you is a stone bridge, its amazing "+
        "length spanning the chasm with an arrogance towards the "+
        "insane drop to the wave-worn rocks so far down. You feel "+
        "that all you can do to save yourself from experiencing "+
        "that height on a more personal basis is to climb either "+
        "across the chasm by scrambling along the underside of the "+
        "bridge, and there seeking a way back up, or by risking "+
        "your life again by climbing further down the sheer "+
        "face.\n\n" );
    
    
    add_item("basalt", "The harsh rock that you cling to is "+
        "basalt, a black, jagged surface with some areas giving "+
        "a mirror-like surface where a clean break has left the "+
        "rock exposed.\n");
    add_item("rocks", "The rocks far below seem to be the same "+
        "black basalt that makes up the walls of the chasm. You "+
        "sincerely hope that you never get to see them close up.\n" );
    add_item(({"chasm", "mist", "waves"}), "Glancing down you "+
        "can make out the bottom of the chasm from here, where "+
        "angry breakers crash over the rocks that once filled "+
        "the space between these cliff walls. A heavy, salty mist "+
        "spirals its way up on eerily soft wind currents from below.\n");
    add_item(({"bridge", "span", "underside"}), "If you "+
        "extend yourself fully from here, you feel that you "+
        "might be able to find hand-holds in the smooth surface "+
        "of the supporting beams, enough to swing yourself, "+
        "monkey-like, towards the centre of the bridge, where "+
        "you may be able to find up the trapdoor which "+
        "got you down here in the first place.\n");
    add_item(({"cracks", "shadows"}), "Much further down the "+
        "sheer face you think you can make out the openings, "+
        "but they are too far away for you to see this close "+
        "to the face.\n");
}

init()
{
    ::init();
    add_action( climbupdown, "climb" );
}

int climbupdown( string whichway )
{
    if (whichway == "down")
    {
        if (climb_test(TP))
        {
            write( "Hand over hand, you slowly, carefully, make your way "+
                  "down the craggy cliff face.\n" );
            say( QCTNAME(TP)+" attempts the dangerous climb down the "+
                "cliff.\n" );
            
            TP->move_living( "down, clinging precariously to the cliff "+
                            "face", VAMP_AREA_DIR + "cliff2" );
            
            return 1;
        }

        fall_down(TP, ({ VAMP_AREA_DIR + "cliff2", 
                         VAMP_AREA_DIR + "cliff3",
                         VAMP_AREA_DIR + "cliff4" }));
        return 1;
    }
    
    if (whichway == "across")
    { 
        if (climb_test(TP))
        {
            write( "Hand over hand, you slowly, carefully, make your way "+
                  "under the bridge away from the south cliff face...\n" );
            say( QCTNAME(TP)+" attempts to climb away from the cliff face, "+
                "along the underside of the bridge.\n" );
            
            TP->move_living( "clinging precariously to the under-rail of "+
                            "the bridge, away from the cliff face",
                            VAMP_AREA_DIR + "ubridge" );
            
            return 1;
        }

        fall_down(TP, ({ VAMP_AREA_DIR + "cliff2", 
                         VAMP_AREA_DIR + "cliff3",
                         VAMP_AREA_DIR + "cliff4" }));
        return 1;
    }

    notify_fail( "Climb where?\n" );    
    return 0;
}
