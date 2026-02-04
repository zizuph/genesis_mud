/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house3_th.c  home of a spy for the LoD
 *
 * Calathin external house.
 * 09/30/1999 -- Tomas
 * Modified 05102002 Goldberry
 *   Relocating Sliver
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

inherit STDROOM;
public string*
query_object_list()
{
    return ({CALATHIN_DIR + "npc/slivar"});
}
object door;


#include <stdproperties.h>


public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("treehouse");
    set_long("The treehouse isn't much more than a box shaped room " +
      "made from wooden planks. In the corner you see a woolen " +
      "blanket stretched before a small metal wood stove. A pile of " +
      "branches and twigs sit to the side of the stove. There are " +
      "no windows or doors except for the trapdoor you came through.\n");

    add_item(({"wooden planks","planks"}),"The treehouse is made " +
       "from wooden planks nailed together to form a small room. " +
       "You notice several knotholes that probably are used to view " +
       "the outdoors throughout the treehouse walls and floor.\n");
    add_item(({"knothole","knotholes"}),"Natural holes in the wooden " +
       "planks.\n");
    add_item(({"woolen blanket","blanket"}),"The thick woolen " +
       "blanket looks quite warm and well used.\n");
    add_item(({"wood stove","stove"}),
       "The wood stove is used to warm the treehouse.\n");
    add_item(({"pile","branches", "twigs"}),
       "A small pile of branches and twigs. Probably used " +
       "for kindling.\n");
    add_item(({"trapdoor","trap door","door"}),
       "The wooden trapdoor leads outside to the tree below.\n");    


    add_cmd_item("knotholes","look in","You put your eye to the " +
       "knothole and gaze at the outdoors.\n");

    
     door = clone_object(CALATHIN_DIR + "houses/obj/house3_th_doora");
        door->move(TO);

     reset_room();
}

