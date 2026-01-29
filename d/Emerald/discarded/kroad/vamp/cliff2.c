/*    cliff2.c
 *    Cliff face under the Kahlen bridge.
 *    Re-written by Jaypeg on the 26th Jan 97
 */

inherit "/std/room";
inherit "/d/Emerald/kroad/vamp/lib/out_vamp_tellroom";


#include <tasks.h>
#include <ss_types.h>
#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"

void fall_down(object pl);

void create_room()
{

 ::create_room();

    set_short( "Clinging to a cliff face of a chasm" ); 
    set_long( "   Your fingers wedged desperately in the cracks, "+
        "you cling tenaciously for your life against the slick, "+
        "sheer cliffs of basalt, framing a chasm that ends "+
        "far, far too far down for your liking.\n"+
        "   Above you is the stone bridge, its length spanning the "+
        "deep chasm with arrogance, while below you are the "+
        "cracks in the face and the chasm much further still. "+
        "From here you can climb up towards the bridge or risk "+
        "climbing down further.\n\n" );
    
    
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
    add_item(({"bridge", "span", "underside"}), "Not too "+
        "far above you is the stone bridge, stretching "+
        "leisurely across the chasm.\n");
    add_item(({"cracks", "shadows"}), "Further down the "+
        "sheer face you can make some openings, "+
        "but they are too far away for you to see this close "+
        "to the face.\n");
    
}

init()
{
    ::init();
    add_action( "climbupdown", "climb" );
}

int climbupdown( string whichway )
{
    
    notify_fail( "Climb where?\n" );
    
    if (whichway == "down")
    {    
        if (TP->resolve_task(TASK_ROUTINE, ({SS_STR, SS_DEX, SS_CLIMB}))>0)
        {
        write( "Hand over hand, you slowly, carefully, make your way "+
            "down the craggy cliff face.\n" );
        say( QCTNAME(TP)+" attempts the dangerous climb down the "+
            "cliff face.\n" );
        
        TP->move_living( "clinging precariously down the cliff "+
            "face", VAMP_KR_DIR + "cliff3.c" );
        
        return 1;
    }
    else
    {
        fall_down(TP);
        return 1;
    }
   }
    
    if (whichway == "up")
    {
        if (TP->resolve_task(TASK_ROUTINE, ({SS_STR, SS_DEX, SS_CLIMB}))>0)
        {
        
        write( "Hand over hand, you slowly, carefully, make your way "+
            "up the cliff face...\n" );
        say( QCTNAME(TP)+" attempts the dangerous climb up the "+
            "cliff face, desperately clinging to any crack, "+
            "crevice or outcrop that can offer grip.\n" );
        
        TP->move_living( "clinging precariously to the sheer black "+
            "walls of the cliff face",
            VAMP_KR_DIR + "cliff1.c" );
        
        return 1;
     }
     else
     {
	 fall_down(TP);
	 return 1;

     }
     return 0;
}

}
void
fall_down(object pl)
{
    pl->catch_msg("In an attempt to find another hand-hold, you lose "+
		  "your grip and are cast down the side of the cliff "+
		  "to the water!!\n\n");
    tell_room(environment(pl),
	      QCTNAME(pl)+" loses "+pl->query_possessive()+" grip!!\n",pl);
    pl->move_living("falling down the cliff", 
		    VAMP_AREA_DIR + "fallroom", 1, 0);
    tell_room(VAMP_AREA_DIR + "cliff3",
               QCTNAME(TP)+ " plumnets by you, screaming all way way "+
               "to the bottom of the cavern, landing with a splash!.\n", TP);
    tell_room(VAMP_AREA_DIR + "cliff4",
               QCTNAME(TP)+ " plumnets by you, screaming all way way "+
               "to the bottom of the cavern, landing with a splash!.\n", TP);

}
