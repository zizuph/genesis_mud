/*
 * A beach in Oranea by Ckrik, June 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_beach_rocky.c";

void
create_beach()
{
    add_my_desc("The cove to the east is bustling with activity. "+
      "You see many fishermen rowing out to sea to cast " +
      "their nets and a small cargo ship anchored in the " +
      "protected waters of the cove. The air is rather " +
      "misty here.\n");
    add_item((({"ship", "cargo ship"})),
      "A small cargo ship is anchored in the cove not far from here.\n");
    add_item (({"cove", "east", "activity"}),
      "There are many ships coming in and out of the cove.\n");
    add_exit("/d/Earthsea/oranea/rooms/beach05", "north");
    add_exit("/d/Earthsea/oranea/rooms/beach07", "southeast");
}
