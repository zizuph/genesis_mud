#pragma save_binary

inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#define POOL   (RANGER_ITH_DIR + "pool")

public string	exa_pool();
public int	do_dive(string arg);

create_room()
{
  set_short("At the brink of a wide flat stone");
  set_long(BSN(
    "You are standing at the brink of a wide flat stone. The "+
    "stone is wet from the mist rising from the falls. Far below you "+
    "the waters pour into a foaming bowl, then swirling darkly about a "+
    "deep oval basin in the rocks. East you can see the dark entrance "+
    "to the passages."));
  add_item(({ "basin", "bowl", "waterfall", "falls", "fall", "torrent", 
    "pool", "water", "waters" }),
    exa_pool);
  add_item("stone", "The flat stone is wet with mist from the falls.\n");
  add_item("mist", "The mist rises from the falls.\n");
  add_item(({ "passages", "passage", "entrance"}),
	"The entrance to the underground passages is back east.\n");
  add_item(({"terrace", "terraces"}),
    BS("The terraces consist of large, flat rocks, smoothed by thousands of " +
    "years of water passing.\n"));
  add_exit(RANGER_ITH_DIR+"landing","east",0);
}

public void
init()
{
  ::init();
  add_action(do_dive, "dive");
  add_action(do_dive, "enter");
}

public int
do_dive(string arg)
{
    string	dest;

    if ( !strlen(arg) )
	NF0(capitalize(query_verb())+" where?\n");

    if ( !sscanf(arg, "into %s", dest) && !sscanf(arg, "in %s", dest) )
	dest = arg;

    if ( dest == "pool" || dest == "water" || dest == "waters" ||
    dest == "basin" || dest == "bowl" || dest == "waterfall" ||
    dest == "falls" || dest == "fall" || dest == "torrent" )
    {
	write(BSN("You are much too high above the water; you would surely "+
	    "injure yourself if you dove from here."));
	return 1;
    }
    NF0(capitalize(query_verb())+" where?\n");

}

public string 
exa_pool()
{
  return(BSN(
    "The torrent falls, splashing over many terraces, and then pours "+
    "down a steep race, into a foaming bowl, then swirling darkly "+
    "about in a deep oval basin in the rocks. There the white waters "+
    "find their way out again through a narrow gate, and flow away, "+
    "fuming and chattering, into calmer and more level reaches. "+
    POOL->query_swimmers()));
}
