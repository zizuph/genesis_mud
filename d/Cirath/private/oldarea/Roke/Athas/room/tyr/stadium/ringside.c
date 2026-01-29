inherit "/std/room";

create_room()
{
    set_short("The Grand Stand of the Arena.");
    set_long("You are standing on the grand stand of the arena.\n"+
	     "There are lots of comfortable seats here and you have a very\n"+
	     "nice view of the fights going on down there.\n");

    add_exit("/d/Roke/Athas/room/tyr/stadium/stadium","arena",0);

}
