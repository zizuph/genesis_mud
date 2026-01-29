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
	"far, far too far down for your liking.\n   "+
        "Far above you is the stone bridge, its length spanning "+
        "the deep chasm with arrogance, while a little further "+
        "down and across are the cracks in the face that you "+
        "first noticed up under the bridge. You can find no way "+
        "across to the further cracks, but can climb down to a "+
        "larger crack beneath you.\n\n" );

    add_item("basalt", "The harsh rock that you cling to is "+
        "basalt, a black, jagged surface with some areas giving "+
        "a mirror-like surface where a clean break has left the "+
        "rock exposed.\n");
    add_item("rocks", "The rocks below seem to be the same "+
        "black basalt that makes up the walls of the chasm. You "+
        "sincerely hope that you never get to see them close up.\n" );
    add_item( ({"chasm", "mist", "waves"}), "Glancing down you "+
        "can make out the bottom of the chasm from here, where "+
        "angry breakers crash over the rocks that once filled "+
        "the space between these cliff walls. A heavy, salty mist "+
        "spirals its way up on eerily soft wind currents from below.\n" );
    add_item( ({"bridge", "span", "underside"}), "Some "+
        "distance above you is the stone bridge, stretching "+
        "leisurely across the chasm.\n" );
    add_item( ({"cracks", "shadows"}), "Further down the "+
        "sheer face you can make out a single large crack, "+
        "and across from there several more cracks "+
        "filled with shadows, "+
        "but they are too far away for you too see this close "+
        "to the face.\n");
    add_item( ({"crack", "opening"}), "Not too far down the "+
        "sheer face you can make out a large opening, "+
        "that seems to dissapear into the cliff face.\n");
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
    if (TP->resolve_task(TASK_ROUTINE, ({SS_DEX, SS_CLIMB, SS_STR}))>0)
    {
	write( "Hand over hand, you slowly, carefully, make your way "+
	"down the craggy cliff face.\n" );
	say( QCTNAME(TP)+" attempts the dangerous climb down the "+
	"cliff face.\n" );

	TP->move_living( "clinging precariously down the cliff "+
	"face", VAMP_KR_DIR + "cliff4.c" );

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
	VAMP_KR_DIR + "cliff2.c" );

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
}

