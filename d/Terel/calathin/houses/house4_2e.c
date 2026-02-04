/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4f.c
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;
#include <stdproperties.h>
object door;
object guard;
object guard2;

public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("parlor");
    set_long("The parlor is brightly decorated. The walls " +
       "are painted dark red with hunter green trim. " +
       "Two large high backed leather chairs face the eastern wall " +
       "where the large fireplace is. Against the northern wall " +
       "are large bay windows with cushioned seats built into the " +
       "window frame. A large oaken desk faces the room from the south.\n");


    add_item(({"chairs","leather chairs"}),
       "The overstuffed high backed chairs are separated by a small table. " +
       "The chairs look very comfortable.\n");

    add_item(({"small table","table"}),
       "The small table is made of dark walnut.\n");

    add_item(("fireplace"),"The large fireplace is set into the east wall " +
       "The edges and screen covering the fireplace is guilded in gold flake. " +
       "The mantle is made of a single piece of oak.\n");

    add_item(({"bay windows","windows"}),
       "the large bay windows overlook the backyard. Cushioned seats line " +
       "the edge of the windows for people to sit upon while viewing " +
       "the great outdoors.\n");

    add_item(("backyard"),"The backyard looks well maintained. Two " +
       "smaller buildings can be seen at the edge of the yard.\n");

    add_item(("buildings"),"One of the buildings looks like its " +
       "made solely out of glass. The other looks more like the " +
       "servants quarters.\n");

    add_item(({"walls", "paneling"}),
       "The walls have been covered with a dark walnut wood stained " +
       "with a slight reddish tint. The trim at the floor and ceiling " +
       "are painted hunter green and have been carved " +
       "with elaborate patterns. A piece of trim also circles around the " +
       "room at waist level it too is stained a darked color. Eight crystal " +
       "lamps, two to a wall are evenly spaced around the room.\n");

    
    door = clone_object(CALATHIN_DIR + "houses/obj/house4_2dba_door");
       door->move(TO);
    
    door = clone_object(CALATHIN_DIR + "houses/obj/house4_2e_door");
       door->move(TO);


    reset_room();

}

void
reset_room()
{    
  
    if(!guard)
    {
       guard = clone_object(CALATHIN_DIR + "houses/npc/house4_guard");
       guard->move(TO);
       guard2 = clone_object(CALATHIN_DIR + "houses/npc/house4_guard");
       guard2->move(TO);
       guard2->team_join(guard);
   
    }
}


