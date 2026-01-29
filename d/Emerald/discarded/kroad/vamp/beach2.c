/*	This room was created by Jaypeg : 02/18/97
 *   This is beach2.c, where the players find
 *   themselves washed up after falling into the
 *   Kahlen road chasm and stumbling in from beach1.c.
 */

inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


void create_room()
{

set_short( "At the cliff face on the beach" );
set_long( "At the cliff face on the beach.\n\n" );

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


}

init()
{
::init();
     add_action( "climbcliff", "climb");
}

int climbcliff( string cliff )
{

notify_fail( "Climb what?\n" );

if (cliff!="cliff") return 0;

write( "You painstakingly scramble your battered body over the "+
"cliff edge, and up onto the road above.\n" );
say( QCTNAME(TP)+" leaves the beach, painfully scaling the cliff "+
"face and up onto the level above.\n" );

TP->move_living( "up and over the cliff", 
"/d/Emerald/lake/outside_elev.c" );

return 1;

}
