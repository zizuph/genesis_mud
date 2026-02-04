/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house1_attic.c
 *
 * Calathin external house.
 * 09/30/1999 -- Grendil
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;
#include <stdproperties.h>


object door;

string kick_latch();

public void
create_room()
{
    ::create_room();
    
    DARK;
    INSIDE;

    set_short("attic");
    set_long("The attic contains a few boxes stacked in a corner. " +
       "A bed and nightstand can be seen against the southern wall. " +
       "A mat lies on the floor in front of the bed.\n");

    add_item(({"box","boxes"}),"Old boxes covered in dust and rat droppings. " +
       "They appear to have been here awhile.\n");
    add_item(("mat"),"The worn mat is ridden with holes.\n"); 
    add_item(("nightstand"),"The nightstand contains the stub of a burned out " +
       "beeswax candle.\n");
    add_item(({"beeswax candle","candle"}),"The stub of an old candle is melted " +
       "to the nightstand.\n");
    add_item(("bed"),"The bed looks like it has been slept in recently.\n");
    add_item(({"wall","corner","walls"}),"The unpainted walls of an attic. You " +
       "see nothing of interest on the walls.\n");
    add_item(("floor"),"You notice that you are standing over a trapdoor.\n");
    add_item(("trapdoor"),"You notice a metal latch securing the trapdoor to the floor. " +
       "Careful you dont kick it.\n");
    add_item(({"metal latch","latch"}),"Judging from the worn marks on the rusty latch " +
       "it would appear to have been used recently.\n");
    add_item(("attic"),"The attic contains a few boxes stacked in a corner. " +
       "A bed and nightstand can be seen against the southern wall. " +
       "A mat lies on the floor in front of the bed.\n");
    add_item(({"rat droppings","droppings"}),"Disgusting!\n");

     
    add_cmd_item("latch","kick",kick_latch);  
    add_cmd_item(({"droppings", "rat droppings"}),
                 ({"smell", "pick"}),
                 ({"smells like shit from a rat.\n", "You decide that picking up rat shit " +
                     "isn't in your best interest.\n"}));
    
    
    door = clone_object(CALATHIN_DIR + "houses/obj/house1_attic_window");
       door->move(TO);
 
    reset_room();
}



string
kick_latch()
{

    write("You fall through a trapdoor beneath you.\n");
    say(QCTNAME(TP) + " falls through a trapdoor in the floor. The " +
       "door swings shut.\n");

    tell_room(CALATHIN_DIR + "/houses/house1_lr", QCTNAME(TP) + 
       " falls through a hole in the ceiling.\n");
        TP->move_living("M",CALATHIN_DIR + "houses/house1_lr.c",1,0);
        return "";
}



