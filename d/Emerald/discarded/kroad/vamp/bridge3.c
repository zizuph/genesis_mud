/*	This room was created by Jaypeg : 01/12/97
*/


inherit "/std/room";

#include <filter_funs.h>
#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


void create_room()
{

    set_short( "Before the shrine of darkness" );
    set_long( "   A wave of panic hits you here like a "+ 
      "crashing wave, and your knees buckle beneath "+ 
      "you. Looming over you on each side a ghastly "+ 
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
      "Your mortal senses reel at the intensity of "+
      "feeling and nausea you are experiencing, a reaction "+
      "to the immense power of the shrine before you, a "+
      "focus of unnatural energy. Worse still, the intensity "+
      "seems to be building.\n" );
    add_item( ({"statue", "statues", "demon"}),
      "Two towering black statues guard the gateway into "+
      "the shrine proper, like warped angels of darkness. "+
      "Their hulking muscular form and giant scaly wings "+
      "are exquisitely carved from some type of black rock, "+
      "with a level of detail that causes you to fear if "+
      "they might come to life at any moment and tear you "+
      "apart.\n" );
    add_item( ({"eyes", "demon's eyes", "eye"}),
      "Wide black orbs in a black stone face, the eyes of "+
      "the demon statues yet seems to have life in them, "+
      "burning behind them. And although you know this "+
      "to be only a statue, you feel as though the eyes "+
      "are watching you.\n" );
    add_item( ({"shrine", "bowl", "temple"}),
      "Beyond the looming gates and statues lies the bowl-"+
      "shaped temple, a shrine of darkness. The shrine seems "+
      "to be octagonal in shape, each point marked with a "+
      "black spire and a marble tablet.\n" );
    add_item( ({"spire", "ebony spire"}),
      "At each of the eight point of the shrine, an ebony "+
      "spire adds an even more threatening aspect to the "+
      "shrine, completed by the marble altar you can make "+
      "out beneath each of them.\n" );
    add_item( ({"tablet", "altar"}),
      "Beneath each spire, at each corner of the shrine, "+
      "sits a marble tablet, a few feet high. The tablet's "+
      "sinister presence gives you shivers.\n" );
    add_item( ({"centre", "center", "aura", "darkness"}),
      "The distress you feel has a definate source in the "+
      "swirling black darkness at the centre of the shrine. "+
      "There the unnatural is at its greatest, and that is "+
      "known and sure in you dissipates like smoke in a breeze.\n" );


    add_exit("/d/Emerald/common/guild/vamp/room/shrines", "north");
    add_exit( VAMP_KR_DIR + "bridge2.c", "south", "@@test_bridge");


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
