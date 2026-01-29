#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit FLOTSAM_OUT;

#define HARD_TO_CLIMB 30
#define PLAYER_I_FOUND_FISH  "_player_i_found_flotsam_fish"

object gob1;

int fish_found = 0;

void
reset_flotsam_room()
{
    fish_found = 0;

    if(!objectp(gob1))
    {
	gob1 = clone_object(FNPC + "tiny_gob");
	gob1->move(TO);
    }
}

create_flotsam_room()
{
    set_short("Alleyway");
    set_long("@@long_descr");

    add_item(({"filth","garbage","rubbish"}),"You name it, if it " +
      "smells bad, yur standin' in it! \n");
    add_item(({"alley","alleyway"}),"You stand in a dark alleyway. " +
      "To your east the alley continues on while to your south it " +
      "opens up into a main street. \n");
    add_item("vermin","Glowing red eyes stare at you from the " +
      "darkness, giving you the impression that you are not " +
      "wanted here. \n");
    add_item(({"drainpipe","rusty drainpipe","pipe"}),"A " +
      "rusty drainpipe crawls up the side of a nearby house.\n");

    add_exit(FROOM + "street28","east",0);
    add_exit(FROOM + "street31","south",0);

    add_cmd_item(({"up drainpipe","drainpipe","up pipe","pipe",
	"up rusty drainpipe","rusty drainpipe"}),"climb",
      "@@climb_pipe");
    add_cmd_item(({"garbage","filth","rubbish"}),"search",
      "@@find_fish");

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + "You stand amidst the filth and " +
    "garbage of one of Flotsams many alleys. Vermin skitter " +
    "into the rubbish as you pass through. The alleyway weaves " +
    "to the east, while to the south the alley opens up " +
    "onto a crowded street. A rusty drainpipe crawls " +
    "up the southeastern corner of a house. \n";
}

string
climb_pipe()
{


    if(this_player()->query_skill(SS_CLIMB) < HARD_TO_CLIMB)
    {
	write("You dont think you are skilled enough to try " +
	  "and climb up the drainpipe.\n");
	say(QCTNAME(this_player()) + " attempts to climb the drainpipe but fails.\n");
	return "";
    }
    write("You skillfully climb up the drainpipe to the " +
      "rooftop of an old house.\n");
    TP->move_living("up the drainpipe and disappears " +
      "onto the roof",FROOM + "rooftop1",1,0);

    return "";
}

string
find_fish()
{

    write("You start searching the garbage...\n");

    /*
       if(fish_found == 0)
	  {
	  write("You find a rotten fish! It sticks to your hand as you " +
	     "try and throw it away... erk!\n");
	  say(QCTNAME(TP) + " searches through the garbage " +
	     "and seems to find something.\n");
	  clone_object(FOBJ + "r_fish")->move(TP);
	  TP->add_prop(PLAYER_I_FOUND_FISH, 1);
	  fish_found = 1;

	  return "";
       }
    */

    write("You find nothing of interest.\n");
    say(QCTNAME(TP) + " searches through the garbage " +
      "but finds nothing of interest.\n");

    return "";
}
