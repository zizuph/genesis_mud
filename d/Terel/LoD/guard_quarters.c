/*
 a room for the legion Redhawk 920921
 */

void
reset_room()
{
    object guard;

    if (present("guard"))
        return;

    guard = clone_object(MANSION + "legion/small_guardl");
    guard -> move(TO);
}

public void
create_room()
{
    ::create_room();
    set_short("Guards private quarters");
    set_long("You are standing in something that appeares to be the guards " +
	     "private quarters, there are a table and some beds here " +
	     "that seems recently used.\n");

    add_item(({"bed"}), "Its a comfortable bed that the guards use when " +
	     "they not in duty.\n");

    add_item(({"table"}), "Its a sturdy dinner table made of wood.\n");

    INSIDE;

    add_exit(MANSION + "leg/corr2.c", "east", 0);
    reset_room();
}
