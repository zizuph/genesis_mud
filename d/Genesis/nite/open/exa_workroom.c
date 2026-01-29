inherit "/std/room";

void
create_room()
{
    set_short("stone platform");
    set_long("This stone platform stretches out to the ends of your " +
      "imagination.\n");
    add_item(({"platform","stone platform"}),"It is vast.\n");
    add_item("stone", "It is cold and grey.\n");
    add_exit("/d/Khalakhor/teth/workroom","khalakhor");
}

