inherit "/std/room";

create_room()
{
    set_short("Terel Wizard Entrance");
    set_long("To the east is the domain tower.\n" +
      "You see the Terel workroom just to the south.\n");

    add_exit("/d/Genesis/wiz/dom_a1", "east", 0, 0);
    add_exit("/d/Terel/workroom", "south", 0, 0);
}
