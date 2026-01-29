/*	This room was created by Jaypeg : 01/19/97
 *	This room is altarroom.c, the Altar of Darkness
 *	in the centre of the Vampires guild.
 */


inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"


void create_room()
{

    set_short( "At the altar of darkness.\nA towering "+
      "altar of darkness" );
    set_long( "   Here darkness, confusion and the unknown "+ 
      "reach a pinnacle, but the undead blood in your "+ 
      "veins makes the experience one of ecstasy. "+ 
      "You stand before the greatest altar to Val-Shoreil, "+ 
      "god of Darkness, and all that is Unknown.\n"+ 
      "   Eight arms reaching from the top of the altar "+ 
      "stretch out in hunger, lusting for life, then "+ 
      "twisting upon themselves until they meet in a cup "+ 
      "of purest white. This room of high "+
      "ceiling and black, featureless walls is rather "+ 
      "bare, besides the shaft of runnels that allows access "+
      "to the octagonal shrine above. A "+ 
      "slope in the western wall leads down to the coffin "+ 
      "crypt that grants rejuvenation for your undying "+ 
      "body.\nA towering altar of darkness.\n\n" );


    add_prop( ROOM_I_LIGHT, -3 );
    add_prop(ROOM_I_INSIDE,1);


    add_item( ({"altar", "altar of darkness"}),
      "As the ultimate vehicle of darkness, the altar "+
      "throbs and pulses with the energy of the fear, "+
      "confusion, and the spilt blood of all mortal beings "+
      "of Emerald, for these are the fuels of the "+
      "great god of darkness, Val-Shoreil.\n"+
      "Standing at well over a man's height, this "+
      "sculpture that seems to be carved of the "+
      "element of negativity itself, its form "+
      "twisting and wavering as your puny senses "+
      "are overcome by its power. Eight arms of "+
      "ebony power reach out to catch the offerings "+
      "that might drip down from the shrine above, "+
      "funneling the liquid life into the heart of "+
      "despair at its core.\nOriginally "+
      "built for the purpose of summoning his avatar "+
      "into the material plane, the altar and the "+
      "entire shrine were built to focus these elements "+
      "to his means. As a child of his darkness, and "+
      "not his servant, the altar excites you, filling you "+
      "with energy and power that would kill you if you "+
      "weren't already dead!\n" );
    add_item( ({"arms", "core", "cup", "heart"}),
      "From the base of the altar eight sinewy "+
      "black arms reach out, each offering a cup-"+
      "like hand to catch what may fall from above, "+
      "where channels like open veins lead down to "+
      "the centre of the altar, channeling to a simple "+
      "pure-white cup in its centre, where a small hole "+
      "allows a drop to fall into nothingness.\n" );



    add_exit( VAMP_KR_DIR + "shrinec.c", "up", 0 );
    add_exit( "hall2", "down", 0 );


}

void
init()
{
  ::init();
  LOAD_CLONE_HANDLER("/d/Emerald/kroad/clone_handler");
}
