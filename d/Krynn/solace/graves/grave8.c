/* The graveyard
*
* Nick
*/

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit GRAVE_STD;

create_solace_room()
{
    set_short("Graveyard");
    set_long(BS(
		"You are standing in the graveyard of Solace. Here you can " +
		"find a large crypt with only one entrance. There are othe" +
		"r graves here, also. They are arranged neatly around the " +
		"crypt.", 70));
    
    add_item(({"crypt", "the crypt", "the large crypt", "large crypt"}),
	     "@@crypt");
    add_item("entrance", "@@special_entrance"); 

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE
    
    add_exit(TDIR + "grave13", "south", 0);

    if (!present("my_stone",find_object(TDIR + "grave13")))
      clone_object(TDIR + "stone")->move(TO);
    else
      add_exit(CRYPT + "hole1","down",0);
}

crypt()
{
    write(BS("It is a very large crypt; it seems to be made for either a " +
	"whole army or maybe someone very large. ", 70));
    say(QCTNAME(TP) + " looks at the crypt.\n");
    return "";
}

query_grave_room() { return 8; }

void
batsay()
{
    tell_room(TO, "A bat flapped its wings as it passed over your head.\n");
}

void
init()
{
    ::init();
    if (!random(3))
      set_alarm(itof(random(5)+2),0.0,"batsay");
}

leave_inv(what, dest)
{
    ::leave_inv(what, dest);
    if (what && what->id("my_stone"))
	add_exit(CRYPT + "hole1", "down", 0);
}

enter_inv(what, from)
{
    ::enter_inv(what, from);
    if (what && what->id("my_stone"))
	remove_exit("down");
}

special_entrance()
{
    if (present("my_stone", TO))
	return "There is a huge stone blocking the entrance.\n";
    return "It doesn't look very inviting.\n";
}
