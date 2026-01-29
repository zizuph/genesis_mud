inherit "/std/room";

create_room()
{
	set_short("This is Geraden's workroom.\n");
	set_long("You have entered a large and spacious workroom.  Benches " +
		"line the walls, and there is a large desk in one corner.  "+
		"The entire room is bathed in a green light from a large "+

		"emerald that hovers near the ceiling.\n");
	add_item("emerald", "A soothing green light eminates from the emerald\n"+
		"spreading outwards in all directions.  As you stare into the\n"+
		"deapths, you feel a great sense of peace.\n");
	add_exit("/d/Rhovanion/geraden/esmirin/town/Eentrance", "Esmirin",0);
	add_exit("/d/Terel/common/town/mansion/second/stage", "stage", 0);
	add_exit("/d/Terel/cedric/guild/dias", "dias", 0);
	add_exit("/d/Terel/common/road/cornerstone", "cornerstone", 0);
     add_exit("/d/Rhovanion/geraden/bored/relax2", "relax",0);
}
