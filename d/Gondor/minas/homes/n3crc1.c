inherit "/d/Gondor/mercade/homes/street";
inherit "/d/Gondor/elessar/lib/street";

create_street() {
  circle = "First";
  areaname = "northern";
  streetname = "Lampwrights' Street";
  streettype = "alley";
  activity = 1;
  wealth = 0;
  add_exit("/d/Gondor/minas/n2crc1","east");
  extraline = "The street ends here, as a steep cliff-wall rises up to the "+
  "west. To the south you see the Second Wall above the roofs of the "+
  "houses, and to the north lies the First Wall. The alley turns into "+
  "a street to the east. ";
  add_item("wall","The First Wall is to the north, and the Second Wall can be seen\n"+
  "over the roofs to the south. Upon both walls some guards are posted.\n");
  add_item("cliff","The cliff is the eastern end of the the Ered Nimrais, the White\n"+
  "Mountains, a mountainrange which stretches out towards the west.\n");
  make_the_room();
}
