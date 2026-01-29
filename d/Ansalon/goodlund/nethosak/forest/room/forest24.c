#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MITHAS_OUT;

#define HAS_SEARCHED   "_has_searched_forest"
#define HOW_MANY                  3

void
create_mithas_room()
{
    set_short("Gloomy forest");
    set_long("@@long_descr"); 

    add_exit(MROOM + "forest22","north",0,2,1);
    add_exit(MROOM + "forest25","east",0,2,1);
    set_noshow_obvious(1);
    add_exit(MROOM + "hut","south","@@only_if_searched");

    add_search(({"forest", "underbrush", "undergrowth", "south"}), 
        10, "search_forest", 1);
    // add_cmd_item(({"forest", "underbrush", "undergrowth"}),
    //    "open", "@@searching_crates");
    add_item(({"forest"}),
     "The forest looks ancient. Old logs and branches "+
     "fill the forest floor and the strong smell of "+
     "decay and moisture fills the air. The forest "+
     "consists of different sorts of trees, a "+
     "mixture of pines and oaktrees.\n");

    add_item(({"trees","oaktrees","pine trees", "pines"}),
     "The trees here consist of a mixture of pines "+
     "and oaktrees. Only a few old trees remains, the rest "+
     "of the trees are either dead or dying.\n");

    add_item(({"underbrush","undergrowth", "faint trails",
        "trails"}),
     "The undergrowth here looks gray and dense with different "+
     "plants and herbs. While it seems like it's impossible "+
     "to enter it, you notice faint trails disappear in to " +
     "it the the south. May be worth a proper investigation.\n");

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

    add_item(({"logs","rotten"}),
     "The logs here have begun to decompose, they must have "+
     "been lying here for years.\n");
}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "You stand within a gloomy forest in the southern part of "+
    "Mithas. The air here is filled with the smell of "+
    "decomposing wood and leaves. Only a few trees are left "+
    "here, most of them have died. Their rotten logs lie all "+
    "over the place, all of them filled with moss and fungus.\n";
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
	else if (times >= (HOW_MANY - 1))
	  {
	   this_player()->add_prop(HAS_SEARCHED, HOW_MANY);
	   write("Your search reveals nothing special.\n");
	   return "";
	  }
	else
	  {
	      this_player()->add_prop(HAS_SEARCHED, times + 1);
	      write("You manage to find a small path through the "+
                    "undergrowth leading south, towards a small " +
                    "wooden hut.\n");
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
	  else if (times >= (HOW_MANY - 1))
	    {
		this_player()->add_prop(HAS_SEARCHED, HOW_MANY);
		return ("Your search reveals nothing special.\n");
	    }
	  else
	    {
		this_player()->add_prop(HAS_SEARCHED, times + 1);
		return ("You manage to find a small path through the "+
                        "undergrowth leading south, towards a small " +
                        "wooden hut.\n");
	}
    }
  return 0;
}

int
only_if_searched()
{
  if (this_player()->query_prop(HAS_SEARCHED))
    return 0;
  write("There is no obvious exit south.\n");
  return 1;
}
