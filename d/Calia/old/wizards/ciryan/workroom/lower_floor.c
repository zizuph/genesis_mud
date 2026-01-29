inherit "/std/room";


create_room()
{
object hatch;
set_short("Lower tower floor");
set_long("This is the lower floor of the tower. The room is dimly lit"+
       " by light filtering in through two small windows. Tapestries in"+
       " warm colours cover the walls and on the floor lies several soft"+
       " rugs. A large bed is the only piece of furniture here. The sound"+
       " from the waves is much stronger now. A strong ladder leads upwards"+
       " through a hatch in the ceiling.\n");

hatch = clone_object("d/Calia/ciryan/workroom/lower_hatch.c");
hatch->move(this_object());

add_item("ladder","This ladder is made from oak wood and looks"+
       " very stable.\n");
add_item(({"window","windows"}),"Looking out through the small windows"+
       " you can see the sea stretching endless to the east.\n");
}
