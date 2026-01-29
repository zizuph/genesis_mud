inherit "/d/Genesis/ship/deck";


public void
create_deck()
{
    set_short("On the ship");
    set_long("You are standing on the deck of a rather "+
      "new ship. It has some rather large sails, but no "+
      "rowers that you can see. However, it is still quite "+
      "fast, even when there is no wind. Perhaps there is "+
      "some magic at work here.\n\n");
    add_item(({"mast", "masts"}), "There are three great masts "+
      "supporting the enormous sails, and you can see people high up "+
      "climbing about.\n");
    add_item(({"sail", "sails"}), "The sails are made out of "+
      "thick, incredibly strong canvas, but you can't see that from "+
      "down here really. What you see is that the sails are set and "+
      "when a gust of wind fills one or several, you feel a rift going "+
      "through all of the ship and notice the masts swaying slightly "+
      "under the enormous pressure.\n");
    add_exit("cabin", "aft");
}
