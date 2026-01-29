/* created by Aridor 02/09/94 */

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;
#include <macros.h>
#define HAS_SEARCHED   "_searched_for_path"
#define HOW_MANY                  3

void
create_mithas_room()
{
    set_short("Gloomy forest");
    set_long("@@long_descr"); 

    add_exit(MROOM + "forest61","northeast",0,2,1);
    add_exit(MROOM + "forest63","east",0,2,1);
    set_noshow_obvious(1);
    //add_exit(MROOM + "dragon_clearing","southeast","@@only_if_searched");

    //add_search(({"forest","trees"}),10,"search_forest",1);
    //add_cmd_item(({"forest","trees"}),"open","@@searching_crates");

    add_item(({"forest"}),
     "The forest looks ancient. Old logs and branches "+
     "fill the forest floor and the strong smell of "+
     "decay and moisture fills the air. The forest "+
     "consists of different sorts of trees, a "+
     "mixture of pines and oaktrees.\n");

    add_item(({"trees","oaktrees","pine trees", "pines"}),
     "The trees here consist of a mixture of pines "+
     "and oaktrees. Some of them look quite old "+
     "while others are fairly young.\n");

    add_item(({"underbrush","undergrowth"}),
     "The undergrowth here looks dense with different "+
     "plants and herbs. It seems like it's impossible "+
     "to enter it. \n");

    add_item(({"trail","path"}),
     "The forest trail twists itself further into "+
     "the forest. It's a bit overgrown with different "+
     "plants and herbs.\n");

    add_item(({"canopy", "treetops"}),
     "The canopy above you looks thick, only a few sunrays "+
     "are able to enter the forest. You notice a few birds "+
     "above you, but they quickly vanish in the thick canopy.\n");

    add_item(({"leaves","branches"}),
     "The branches and leaves here, have almost decomposed "+
     "into dirt. A few of them look alive, but "+
     "they are still covered with moss and fungus.\n");

    add_item(({"herbs","plants"}),
     "There are a lot of different herbs here! If you want to "+
     "look at a specific one, perhaps you should search for "+
     "it.\n");
}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+ 
    "You stand on an old forest path in the "+
    "southern part of Mithas. The trail here is "+
    "covered in moss and branches, it looks "+
    "like there hasn't been anyone here for "+
    "years.\n";
}


string
searching_forest()
{
  int times = this_player()->query_prop(HAS_SEARCHED);
  if (CAN_SEE_IN_ROOM(this_player()))
    {
	if (times >= HOW_MANY)
	  {
	      this_player()->add_prop(HAS_SEARCHED, HOW_MANY);
	      return ("Your search reveals nothing special.\n");
	  }
	else
	  {
	      this_player()->add_prop(HAS_SEARCHED, times + 1);
	      write("You notice an old path through the forest "+
                    "to the southeast.\n");
	      return "";
	  }
    }
  return 0;
}

string
search_forest(object searcher, string what)
{
    int times = this_player()->query_prop(HAS_SEARCHED);
    if (CAN_SEE_IN_ROOM(this_player()))
      {
	  if (times >= HOW_MANY)
	    {
		this_player()->add_prop(HAS_SEARCHED, HOW_MANY);
		return ("Your search reveals nothing special.\n");
	    }
	  else
	    {
		this_player()->add_prop(HAS_SEARCHED, times + 1);
		return ("You notice an old path through the forest "+
                        "to the southeast.\n");
	}
    }
  return 0;
}

only_if_searched()
{
  if (this_player()->query_prop(HAS_SEARCHED))
    return 0;
  write("There is no obvious exit southeast.\n");
  return 1;
}
