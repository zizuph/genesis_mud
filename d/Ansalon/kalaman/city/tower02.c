#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/guilds/sohm/defs.h"

inherit KALAMAN_IN;

#define HOW_MANY 3
#define SOHM_I_SEARCH_BOOKSHELF   "_sohm_i_search_bookshelf"
#define SOHM_I_FOUND_INVIS    "_sohm_i_found_zhinpersvek"

object scroll;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("upper level of a wizard's tower");

    add_item(({"strange black stone","black stone","stone","walls","gloomy light",
      "light"}),
      "The tower is made of strange black stone. While seemingly opaque, " +
      "the tower is lit with a gloomy light that seems to come from the walls.\n");
    add_item(({"stone staircase","staircase","stairs","open staircase"}),
      "A stone staircase circles the walls of the tower down to the tower entrance.\n");
    add_item(({"platform","bare platform","large platform"}),
      "The top floor of the tower is an open platform, filled with furniture, " +
      "half-complete experiments, and piles of books.\n");
    add_item(({"furniture","benches"}),
      "A bizarre collection of furniture has been placed " +
      "almost randomly around the large platform you stand upon.\n");
    add_item(({"experiments","half-complete experiments"}),"Weird and wonderful " +
      "experiments seem to have been left abandonned on benches throughout the room.\n");
    add_item(({"piles of books","piles","books","recipe books","ancient treaties"}),
      "Books ranging from ancient treaties of long lost kingdoms to the rather dour " +
      "recipe books of Nordmaarian barbarians are piled around the platform in no " +
      "particular order.\n");

    add_exit(CITY + "tower01","down",0);

    add_search(({"furniture","experiments","books","piles of books","piles"}),
        10,"search_stuff",1);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand at the top of a wizard's tower - a large platform chaotically " +
       "filled with furniture, half-complete experiments, and piles of books scattered " +
       "everywhere. You wonder how anyone could find anything amongst this disorder.\n";
}

string
search_stuff(object searcher, string what)
{
    int times = this_player()->query_prop(SOHM_I_SEARCH_BOOKSHELF);

    if (CAN_SEE_IN_ROOM(this_player()))
      {
	  if (times >= HOW_MANY)
	    {
            if(SOHM_MANAGER->query_scribed_spell(this_player(),"zhinpersvek") ||
               this_player()->query_prop(SOHM_I_FOUND_INVIS))
             {
		this_player()->add_prop(SOHM_I_SEARCH_BOOKSHELF, HOW_MANY);
                tell_room(environment(this_player()), QCTNAME(this_player()) + 
                " searches through the " +what+ ", looking for " +
                "something of interest.\n", ({ this_player() }));
		return ("You don't find anything in the " +what+ " of " +
                "interest or value.\n");
              }
		  this_player()->add_prop(SOHM_I_SEARCH_BOOKSHELF, HOW_MANY); 
		  this_player()->add_prop(SOHM_I_FOUND_INVIS, 1);
                  tell_room(environment(this_player()), QCTNAME(this_player()) + 
                  " searches through the " +what+ ", looking for " +
                  "something of interest.\n", ({ this_player() }));

                  scroll = clone_object("/d/Krynn/common/scrolls/invisibility_scroll");
                  scroll->move(this_player());
                  seteuid(getuid());

		  return ("You search through the " +what+ ", and find " +
                  "a spell parchment of interest!\n");
	    }
	  else
	    {
		this_player()->add_prop(SOHM_I_SEARCH_BOOKSHELF, times + 1);
                tell_room(environment(this_player()), QCTNAME(this_player()) + 
                " searches through the " +what+ ", looking for " +
                "something of interest.\n", ({ this_player() }));
		return ("You search through the " +what+ " for anything of interest. " +
                "You don't uncover anything on this particular search.\n");
	} 
    }
  return 0;
}
