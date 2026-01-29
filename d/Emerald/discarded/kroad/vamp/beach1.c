/*   This room was created by Jaypeg : 02/18/97
 *   This is beach1.c, where the players find
 *   themselves washed up after falling into the
 *   Kahlen road chasm.
 */

inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


void create_room()
{

set_short( "On a beach before a cliff" );
set_long( "   You stagger your way up the beach, still "+ 
"unsteady from the fall that brought you here. If it wasn't "+ 
"for the pain in your limbs and throbbing in your head "+ 
"you imagine you'd find this place beautiful to "+ 
"behold, crisp white sand beneath your feet, "+ 
"crystal blue sea behind you with startling dark "+ 
"cliff-faces in front of you. All you can bring "+ 
"yourself to do right now is stagger up to the cliff.\n\n" );

add_prop(ROOM_I_LIGHT, 2);

add_item( ({"beach", "sand", "white sand",}),
"The white sand beach stretches far in either "+ 
"direction, and a little further to the west where "+ 
"the cliff-face greets you. The sand squeaks "+ 
"beneath your feet as you stumble along.\n" );
add_item( ({"pain", "throbbing", "stupor",}),
"You are still reeling from the fall and loss of "+ 
"conciousness, your body battered and your "+ 
"lungs aching from the near drowning.\n" );
add_item( ({"cliff", "cliffs", "cliff-face",}),
"Craggy grey cliff-faces greet you to the west, "+ 
"where the mighty realm of Emerald meets the "+ 
"blue seas. The cliff doesn't look too hard to "+ 
"climb, nor too high immediately to your west "+ 
"from here.\n" );
add_item( ({"sea", "blue sea",}),
"The sparkles of sunlight reflecting off the "+ 
"water cause your headache to increase "+ 
"tenfold. The clear crystal water cuts a crease "+ 
"into the realm of Emerald, seperating it from "+ 
"other far-away lands.\n" );


add_exit(  VAMP_KR_DIR + "beach2.c", "west", 0 );


}

