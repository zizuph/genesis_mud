inherit "/std/workroom.c";

create_workroom()
{
  ::create_workroom();
  set_long("   A quite featureless place. Nor entrances neither "+
      "exits are present, and you get a feeling that walls, floor "+
      "and ceiling are just illusion. The medium-sized sphere "+
      "resides in the middle of the room, drawing all your "+
      "attention.\n");

  add_item("sphere","After you take a closer look you see "+
      "it represents copy of planet Genesis itself, only in a "+
      "zillion times smaller. Some dots are moving "+
      "on its surface.\n");
  add_item("dots","Oohh, they are actually the creatures of "+
      "various size, shape and race!\n");
}
