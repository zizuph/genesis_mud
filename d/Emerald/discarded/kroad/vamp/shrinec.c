/*	This room was created by Jaypeg : 01/20/97
*/


inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"
#include "/d/Emerald/common/guild/vamp/guild.h"

int vamp_chk();

void create_room()
{

    set_short( "In the centre of the shrine of darkness" );
    set_long( "   The inky, thick, blackness "+
      "reaches an axis here, and light seems to "+ 
      "be sucked into the shrine, especially below "+ 
      "you where the runnels meet from the eight "+ 
      "points of the octagon, and form anti-clock"+ 
      "wise channels in the narrow shaft running "+ 
      "to what must be another room below.\n   "+ 
      "From here you may move to any of the "+ 
      "eight points of the shrine, or try to squeeze "+ 
      "yourself down the shaft into the room "+ 
      "below.\n\n" );


    add_prop( ROOM_I_LIGHT, -2 );
    add_prop(ROOM_I_INSIDE,1);


    add_item( ({"darkness", "dark", "aura"}),
      "It is dark here beyond your comprehension, "+ 
      "and the light sources you tote with you "+ 
      "seem virtually useless, somehow you are "+ 
      "still able to see, its as if the darkness has "+ 
      "reversed apon itself, and there is a black "+ 
      "light shed from the shaft beneath your feet.\n" );
    add_item( ({"light", "black light"}),
      "Here the wane light shed by your light "+
      "sources pales even more than before, "+
      "and what little light escapes the aura "+
      "of the shrine get twisted, warped, and "+
      "reversed into a black light that oozes "+
      "from the shaft below your feet.\n" );
    add_item( ({"runnels", "channels", "shaft", 
	"below", "room below"}),
      "From each of the eight points of the shrine "+
      "a narrow runnel runs from the marble tablet "+
      "at the edge of the bowl, down into the centre "+
      "where you now stand. Here they merge, into a "+
      "spiral shaft made of small channels, where "+
      "you can imagine blood would flow in a sickly "+
      "dance down into whatever room is below you.\n"+
      "The shaft is narrow, you are not very sure "+
      "how anyone would be able to get down there, "+
      "but you can make out faint variations in the "+
      "inky blackness below that would indicate that "+
      "at sometime, somehow, someone was able to work "+
      "some kind of black magic in what seems to be "+
      "the core of this enormous shrine of darkness.\n" );


    add_exit( VAMP_KR_DIR + "shrines.c", "south", 0 );
    add_exit( VAMP_KR_DIR + "shrinesw.c", "southwest", 0 );
    add_exit( VAMP_KR_DIR + "shrinew.c", "west", 0 );
    add_exit( VAMP_KR_DIR + "shrinenw.c", "northwest", 0 );
    add_exit( VAMP_KR_DIR + "shrinen.c", "north", 0 );
    add_exit( VAMP_KR_DIR + "shrinene.c", "northeast", 0 );
    add_exit( VAMP_KR_DIR + "shrinee.c", "east", 0 );
    add_exit( VAMP_KR_DIR + "shrinese.c", "southeast", 0 );
    add_exit( VAMP_KR_DIR + "altarroom.c", "down", vamp_chk);


}

int vamp_chk()
{
   if (!IS_MEMBER(TP) && !IS_WIZ(TP))
	{
	    write("You cant get in!\n");
	    return 1;
	} 
	else
 {
	    write("You walk on in.\n");
	    say("He walks in.\n");
	    return 0;
	}
    }
