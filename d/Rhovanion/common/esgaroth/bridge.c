inherit "/d/Rhovanion/lib/room";

create_exits() {}

create_room()
{
    set_short("Bridge");
    set_long("This is a bridge over one of the many open spots of water in " +
        "Esgaroth.\n");
    create_exits();
}
