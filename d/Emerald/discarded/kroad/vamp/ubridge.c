/*    Ubridge.c, re-written by Jaypeg 26th Jan 97
 *    This is the underside of the Kahlen road
 *    bridge (~/kroad/bridge.c), where the players
 *    fall through the trap door, also the only way
 *    to find the vamps guild at the shrine of
 *    darkness.
 *    Noiseroom added - 13th Feb 97
 */



inherit "/std/room";
inherit "/d/Emerald/kroad/vamp/lib/out_vamp_tellroom";
inherit "/d/Emerald/kroad/vamp/climbroom";

#include <tasks.h>
#include <ss_types.h>
#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"

int climbacross(string str);

void create_room()
{
    ::create_room();    

    set_short("Hanging precariously under a bridge over a chasm"); 
    set_long("   You grasp for the underail of the bridge with white knuckled "+
        "desperation, knowing that failure to do so means your certain "+
        "death. Far beneath you the sound of crashing waves and cold, "+
        "salty mist taunt you, tempt you into giving in...\n"+
        "   Above you the bridge spans the chasm, and now your life "+
        "has stopped flashing before your eyes, or at least for the "+
        "moment, you think that you can "+
        "find a way to climb back up onto it. Further down "+
        "where you hang, you can make out now scars in the basalt "+
        "surface of the cliff face. Further down and across you "+
        "think you can see shadows moving amongst the dark cracks of "+
        "the face, perched like vultures in a tree, waiting to feed.\n\n");
    
    
    add_item("rocks", "The rocks far below seem to be the same "+
        "black basalt that makes up the walls of the chasm. You "+
        "sincerely hope that you never get to see them close up.\n" );
    add_item(({"chasm", "mist", "waves"}), "Glancing down you "+
        "can make out the bottom of the chasm from here, where "+
        "angry breakers crash over the rocks that once filled "+
        "the space between these cliff walls. A heavy, salty mist "+
        "spirals its way up on an eerily soft wind current from below.\n");
    add_item(({"underail", "underails", "underside"}), "Looking "+
        "along the underside of the bridge, your eyes follow the "+
        "smooth, sturdy underails that provide support to this "+
        "mighty bridge. You feel that you could use them to "+
        "climb your way across to the cliff face.\n" );
    add_item("basalt", "The harsh rock that you cling to is "+
        "basalt, a black, jagged surface with some areas giving "+
        "a mirror-like surface where a clean break has left the "+
        "rock exposed.\n");
    add_item(({"up", "bridge"}), "Above you the amazing stone "+
        "bridge spreads itself across the chasm, its flawless surface "+
        "only marred in one place above you by a deviously concealed "+
        "trapdoor, only now visible from below.\nYou think that you "+
        "can climb up now you've figured out how to open the trapdoor.\n" );
    add_item(({"cliff", "cliff face", "face", "surface"}),
        "Taking cautious glances at the south cliff face now, you "+
        "believe that you can see horizontal scars in the basalt "+
        "surface, which you guess might be useful in allowing you "+
        "to climb down, towards what could easily be a watery death "+
        "below.\nFirst of all, of course, you'll have to climb across "+
        "by swinging arm over arm, clinging to the supporting beams.\n");
    add_item(({"cracks", "shadows", "moving shadows", "down"}),
        "Much further down you can see several deep gashes in the "+
        "surface, cracks in the otherwise smooth surface of the dark "+
        "cliff face, and within them you sense the slightest movement, "+
        "even through the inky darkness that soaks them.\n");
}

init()
{
    ::init();
    add_action(climbacross, "climb" );
}

int climbacross( string whichway )
{
    if (whichway == "up")
    {
        if (climb_test(TP))
        {
            write( "You get a grip, and throw a leg up over "+
                "the side, trying to haul yourself up onto the bridge "+
                "and safety...\n" );
            say( QCTNAME(TP)+" attempts to climb up onto the bridge, "+
                "throwing a leg over the edge and scrambling to "+
                "reach the safety of the top-side of the bridge.\n" );
        
            TP->move_living( "desperately scrambling up the side of "+
                "the bridge", KROAD_DIR + "bridge.c" );
        
            return 1;
        }

        fall_down(TP, ({ VAMP_KR_DIR + "cliff1",
                         VAMP_KR_DIR + "cliff2",
                         VAMP_KR_DIR + "cliff3",
                         VAMP_KR_DIR + "cliff4", }));
        return 1;
    }
    
    if (whichway == "across")
    {
        if (climb_test(TP))
        { 
            write( "Hand over hand, you slowly, carefully, make your way "+
                "under the bridge towards the south cliff face...\n" );
            say( QCTNAME(TP)+" attempts the dangerous climb towards the "+
                "cliff face, clinging desperately clinging to the "+
                "underside of the bridge.\n" );
            
            TP->move_living( "clinging precariously towards the cliff "+
                "face", VAMP_KR_DIR + "cliff1.c" );
            
            return 1;
        } 

        fall_down(TP, ({ VAMP_KR_DIR + "cliff1",
                         VAMP_KR_DIR + "cliff2",
                         VAMP_KR_DIR + "cliff3",
                         VAMP_KR_DIR + "cliff4", }));
        
        return 1;
    }

    notify_fail( "Climb where?\n" );
    return 0;
}
