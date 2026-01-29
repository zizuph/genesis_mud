/*	This room was created by Jaypeg : 02/09/97
*/


inherit "/std/room";

#include <filter_funs.h>
#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


void create_room()
{

    set_short( "Standing before a narrow bridge, crossing a "+
      "chasm to an enormous shrine" );
    set_long( "   A wave of panic hits you here like a crashing "+ 
      "wave, and your knees buckle beneath you. "+ 
      "Looming over you on each side a ghastly "+ 
      "statue of a demon stares down at you, "+ 
      "and you feel like your living soul is being "+ 
      "sucked into their cavernous eyes.\n   Past "+ 
      "the hideous statues is the shrine, octagonal "+ 
      "in design, an ebony spire standing at each of "+ 
      "the points, and under each spire you can see a "+ 
      "knee-high stone tablet, made from what seems to "+ 
      "be marble. In the centre, however, an aura "+ 
      "ancient and repulsive beyond your "+ 
      "mortal comprehension pulses softly, drinking "+ 
      "in the light and life energy around it.\n\n" );


    add_prop( ROOM_I_LIGHT, -2 );
    add_prop(ROOM_I_INSIDE,1);


    add_item( ({"panic", "anxiety"}),
      "The intense and feeling you experience both attracts "+
      "and repulses you to the extremes, setting your veins "+
      "on fire and your nerves alight.\n" );
    add_item( ({"statue", "statues", "demon"}),
      "These demonic statues flank the path into the shrine, "+
      "each of them seem impossible to focus clearly on, as "+
      "if they were changing shape before your eyes.\n" );
    add_item( ({"eyes", "demon's eyes", "eye"}),
      "The eyes in the statues at first seem simply black, black "+
      "to the point of being a void, but as your eyes begin to "+
      "to water and you start to turn away you think you see "+
      "a malignant glimmer there.\n" );
    add_item( ({"shrine", "bowl", "temple"}),
      "The shrine is a large, octagonal bowl, each point marked "+
      "with a spire and a stone tablet. Each point slopes gently "+
      "down to the centre where you suddenly have trouble focusing "+
      "from the pulses of intense forces through your body.\nYou "+
      "buckle and retch trying to hold back the contents of your "+
      "stomach.\n" );
    add_item( ({"spire", "ebony spire"}),
      "A tall, simple spire marks each point of the octagonal "+
      "shrine.\n" );
    add_item( ({"tablet", "altar"}),
      "At each zenith of the eight octagonal sides of the shrine, "+
      "a crudely-cut stone altar sits, its simplicity belying its "+
      "malicious purpose, of which you can only guess.\n" );
    add_item( ({"centre", "center", "aura", "darkness"}),
      "Where the sloping sides of the altar meet a core of darkness "+
      "pulses with raw unnatural energy of repugnant intensity. It "+
      "seems as if there may be a hole at the centre but you are "+
      "unable to focus to be able to be sure.\n" );


    add_exit("cavend", "south");
    add_exit( VAMP_KR_DIR + "bridge2.c", "north", "@@test_bridge");


} 

int
test_bridge()
{
    object bridge_room;
    object *people;

    if (!LOAD_ERR(VAMP_KR_DIR+"bridge2"))
	bridge_room = find_object(VAMP_KR_DIR+"bridge2");
    else
	return 1;

    people = FILTER_LIVE(all_inventory(bridge_room));

    if (sizeof(people)>0)
    {
	this_player()->catch_msg("You consider stepping onto the bridge, but when "+
	  "you see that "+QTNAME(people[0])+" is already there, "+
	  "you decide it would be safer to wait.\n");
	return 1;
    }

    else
    {
	write("You cautiously step out onto the narrow bridge ... \n\n");
	return 0;
    }
}
