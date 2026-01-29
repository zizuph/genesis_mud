#include <stdproperties.h>
#include <macros.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";

 
void
create_nov_room()
{
                   
    set_name("In the chamber of storage");
    add_name( ({ "room", "hall", "corridor" }) );

    set_short("This is the room where the Necromancers bring their " +
    "artifacts for safe keeping");
    set_long("This is the room where the Necromancers bring their " +
    "artifacts for safe keeping. You never know who or what you " +
    "may find in here. The racks are built of a smooth white " +
    "material, looking closer you see they are made out of bones " +
    "solidly fused together making it impossible to tell which " +
    "race they came from. Between the racks is a small skull.\n");

    add_item(({"skull"}),
        "It is a small white skull with two emeralds sitting in " +
        "the eyesockets. You feel the urge to push it.\n");

    //add_exit(NOV_DIR + "temple/ncentral",   "east");
    add_exit(NOV_DIR + "temple/ncentral",   "south");
    
    clone_object(NOV_DIR + "obj/rack1")->move(this_object());
    clone_object(NOV_DIR + "obj/rack2")->move(this_object());
    clone_object(NOV_DIR + "obj/rack3")->move(this_object());

}



int
do_pushsk(string str)
{
	if (str != "skull")
	{
		return 0;
	}
	
	write("You push the small white skull, but nothing happens.\n");
      
      tell_room(environment(this_player()), QCTNAME(this_player())+" pushes a small " +
      "white skull, but nothing happens.\n",({this_player()}));
      
      return 1;
}


void
init()
{
    ::init();


    add_action(do_pushsk, "push");

   
}