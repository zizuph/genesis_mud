/*
 * /d/Gondor/ithilien/forest/haradtent3.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#ifdef OBJ_DIR
#undef OBJ_DIR
#endif
#define OBJ_DIR     "/d/Gondor/ithilien/obj/"

object	Cook; 

public void	create_gondor();
public void	reset_room();
public string	do_search(object searcher, string str);
public void	leave_inv(object ob, object to);
public void	remove_sack();

public void
create_gondor()
{
    set_short("Inside a Haradrim tent");
    set_long(BSN(
	"This tent is quite large.  A central fire pit holds "+
    	"a briskly burning fire, and grey sacks are stacked "+
	"along the canvas walls."));

    add_item( ({ "pit", "fire", "fire pit", "firepit" }), BSN(
	"The fire pit, a crude makeshift construction of unhewn stones, "+
	"holds a briskly burning fire.  The smoke from the fire escapes " +
	"through a hole in the roof of the tent."));
    add_item( ({ "smoke", "hole", "roof", "canvas roof" }), BSN(
	"A ragged hole in the canvas roof vents the smoke "+
	"from the fire pit."));
    add_item( ({ "grey sacks",  "grey sack",  "provisions", "sack", "sacks" }),
	BSN(
	"Grey sacks, apparently filled with provisions, "+
	"are stacked along the walls of the tent."));

    add_prop(ROOM_I_INSIDE,1);
    add_prop(OBJ_I_HAS_FIRE,1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_exit(ITH_DIR+"forest/haradcamp3","out",0);

    reset_room();
}

public void
reset_room()
{
    Cook = clone_npc(Cook, (ITH_DIR + "npc/haradcook"));
}

public string
do_search(object searcher, string str)
{
    if(str == "fire" || str == "fire place" || str == "fireplace")
    {
	write("Ouch!\n");
	TP->heal_hp(-25);
	SAY(" burns "+TP->query_possessive()+
		" fingers searching the fireplace.");
	return "You burn your fingers searching the fireplace.\n";
    }

    if ( str != "provisions" && str != "sacks" && str != "sack" &&
    str != "grey sack" && str != "grey sacks" )
	return "Your search reveals nothing special.\n";

    if ( !objectp(present("saltsack", TO)) )
	clone_object(OBJ_DIR + "saltsack")->move(TO);

    return BSN("Among a lot of uninteresting provisions, you find an open "+
	"sack of salt. Perhaps you could take a pinch of salt or two "+
	"from it.");

}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if ( ob && interactive(ob) && to && to != TO )
	set_alarm(2.0, 0.0, remove_sack);
}

public void
remove_sack()
{
    object *sack, *inv = all_inventory(TO);

    if ( sizeof(inv) && !sizeof(FILTER_PLAYERS(inv)) &&
    sizeof(sack = filter(inv, &->id("saltsack"))) )
	sack->remove_object();
}
