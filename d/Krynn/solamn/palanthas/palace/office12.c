/* created by Aridor 09/14/93 */

#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/guilds/sohm/defs.h"

inherit CITY_ROOMBASE;

#define HOW_MANY 3
#define SOHM_I_SEARCH_BOOKSHELF   "_sohm_i_search_bookshelf"
#define SOHM_I_FOUND_PROT         "_sohm_i_found_trothocuir"

object scroll;

string
query_to_jail()
{
  return "south";
}

void
create_palan_room()
{
    set_short("Archive");
    set_long("This is the backroom of the Archive. The walls and "
           + "even the floor are filled with books, scrolls, and sheets. "
           + "You better be careful or everything will be a total mess. "
           + "- Not that it isn't to you already.\n");

    add_item(({"books","scrolls","sheets"}),
        "Books, scrolls, and sheets have been crammed, piled, and dumped " +
        "throughout this backroom without much thought for how specific " +
        "items may be found again!\n");
    add_item(({"walls","bookshelves"}),
        "Across the walls are bookshelves crammed with books, scrolls and " +
        "sheets.\n");
    add_item(({"floor"}),
        "With the bookshelves along the walls full, the floor has been " +
        "used as a proxy storage area!\n");

    clone_object(OBJ + "door12")->move(TO);
    add_exit(PALACE + "office11","south");

    add_search(({"bookshelves","walls","books","scrolls","wall"}),
        10, "search_stuff", 1);
}

string
search_stuff(object searcher, string what)
{
    int times = this_player()->query_prop(SOHM_I_SEARCH_BOOKSHELF);

    if (CAN_SEE_IN_ROOM(this_player()))
    {
        if (times >= HOW_MANY)
	{
             if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothocuir") ||
                 this_player()->query_prop(SOHM_I_FOUND_PROT))
             {
		  this_player()->add_prop(SOHM_I_SEARCH_BOOKSHELF, HOW_MANY);
                  tell_room(environment(this_player()), QCTNAME(this_player()) + 
                      " searches through the " +what+ ", looking for " +
                      "something of interest.\n", ({ this_player() }));
		  return ("You don't find anything in the " +what+ " of " +
                  "interest or value.\n");
              }
	      this_player()->add_prop(SOHM_I_SEARCH_BOOKSHELF, HOW_MANY); 
	      this_player()->add_prop(SOHM_I_FOUND_PROT, 1);
              tell_room(environment(this_player()), QCTNAME(this_player()) + 
                  " searches through the " +what+ ", looking for " +
                  "something of interest.\n", ({ this_player() }));
              scroll = clone_object("/d/Krynn/common/scrolls/prot_divination_scroll");
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