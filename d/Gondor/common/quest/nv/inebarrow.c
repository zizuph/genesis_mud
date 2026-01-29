#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define TREASURES (({ "/d/Gondor/common/obj/gems", \
    "/d/Gondor/common/wep/num_dagger", \
	"/d/Gondor/common/arm/tattered_rags", \
	"/d/Gondor/common/obj/gold_chain", \
	}))
#define AWARE_NEEDED  30

public int door_msg();
public int do_smell(string str);

int strength_left, tfound;

public void
create_room() 
{
    set_short("in a dark and cold barrow");
    set_long(BSN("The chamber is cold and dark, with a "+
	"rather low ceiling. In the south end is a closed stone door, "+
	"probably sealed off for centuries. The dusty ground is cold as "+
	"the stale air in the chamber. This is a tomb, or barrow, and on the "+
	"floor lie the remains of someone long dead."));

    add_item(({"remains"}), BSN("A bony skeleton, shrouded in " +
	"smouldering rags that were probably "+
	"majestic once upon a time. These remnants of some long dead Dunadan lord "+
	"are now totally lifeless, and only bring a feeling of death and despair "+
	"to those who look upon them."));
    add_item(({"floor","ground"}),BSN(
	"The ground is covered in dust. No living being has been here in ages."));
    add_item("door",BSN(
	"The door of the barrow is made of one large, solid stone slab. "+
	"No handle or lock can be seen, nor any other mechanism for "+
	"opening it. You feel trapped!"));
    add_cmd_item("door","open","You find no handle or knob to open it with.\n"+
	"Are you trapped?!\n");
	
    add_exit("/d/Gondor/common/quest/nv/edown","south", door_msg, 1);
    set_noshow_obvious(1);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(OBJ_S_SEARCH_FUN,"search_barrow");
    add_prop(OBJ_I_SEARCH_TIME,6);
    add_prop(ROOM_I_LIGHT,-1);
    strength_left = 200;
}

public void
init()
{
    ::init();
    add_action(do_smell, "smell");
}

void 
reset_room()
{
    strength_left = 200;
    tfound = 0;
}

public int
do_smell(string str)
{
    if (str=="air")
    {
	this_player()->command("puke");
	return 1;
    }
    write("Smell what?\n");
    return 1;
}

public int
door_msg()
{
    if (strength_left < TP->query_stat(SS_STR)) 
    {
	write("You manage to push the door wide enough open to squeeze through!\n");
	say(QCTNAME(TP)+" manages to push the door wide enough open to squeeze through!\n",TP);
	return 0;
    }
    strength_left -= TP->query_stat(SS_STR);
    write("You push at the stone door, and it opens a little more.\n"+
	"You still cannot get out though - try again!\n");
    say(QCTNAME(TP)+" pushes at the door. It moves a little, but not enough.\n",TP);
    return 1;
}

public string
search_barrow(object searcher, string str)
{
    object tob;
    if (!strlen(str) || (str != "floor" && str != "remains" && str != "ground")) 
	return 0;
    if (tfound >= 3) 
	return 0;
    if (searcher->query_skill(SS_AWARENESS) >= AWARE_NEEDED)
    {
	tfound++;
	tob = clone_object(TREASURES[random(sizeof(TREASURES))]);
	if (tob->id("gem"))
	{
	    tob->set_gem_type("sapphire");
	    tob->set_heap_size(5 + random(6));
	}
	tob->move(searcher,1);
	tell_room(TO,QCTNAME(searcher)+" finds something.\n",searcher);
	return "You find "+LANG_ASHORT(tob)+"!\n";
    }
    return 0;
}
