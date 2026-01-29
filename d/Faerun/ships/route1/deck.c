inherit "/d/Genesis/ship/deck";


public void
create_deck()
{
    set_short("On the white fast sloop");
    set_long("You are standing on the deck of the Brevari, a fast "+
      "sloop painted in white. It has some rather large sails, but no "+
      "rowers that you can see. However, it is still quite "+
      "fast, even when there is just little wind.\n\n");
    add_item(({"mast"}), "There are one mast "+
      "supporting the elegant white sail, and you can see people high up "+
      "climbing about.\n");
    add_item(({"sail", "sails"}), "The sails are made out of "+
      "thick, incredibly strong canvas, but you can't see that from "+
      "down here really. What you see is that the sail are set and "+
      "when a gust of wind fills it, you feel a rift going "+
      "through all of the sloop and notice the mast swaying slightly "+
      "under the pressure.\n");
    add_exit("cabin", "aft");
}
