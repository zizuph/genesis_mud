/*
 * A beach in Oranea by Ckrik, June 1998
 */

inherit "/d/Earthsea/oranea/base_rooms/base_beach_rocky.c";

void
create_beach()
{
    add_my_desc("You see the fishermen rowing out " +
      "to sea to cast their nets and the faint outlines of a " +
      "small cargo ship anchored in the " +
      "protected waters of the cove. The air is very " +
      "misty here. In the far distance you see a " +
      "mountain piercing through the blue mist covering " +
      "this island. To the southeast is what seems to be " +
      "a pier.\n");
    add_item((({"ship", "cargo ship"})),
      "A small cargo ship is anchored just off shore in the cove..."+
      "You wonder what sort of cargo it might contain.\n");
    add_item (({"cove", "east", "activity"}),
      "There are many boats coming in and going out of the cove. "+
      "Most of them are fishermen's boats, judging by the way the "+
      "seagulls seem to hover around them.\n");
    add_item(("mountain"), "The mountain is too far away and the mist " +
      "is too thick for you to make out anything.\n");
    add_item(("pier"), "You cannot see much through all this mist.\n");

    add_exit("/d/Earthsea/oranea/rooms/beach06", "northwest");
    add_exit("/d/Earthsea/ships/oranea_line/oranea_pier", "southeast");
}
