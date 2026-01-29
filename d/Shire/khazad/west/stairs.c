
inherit "/d/Shire/khazad/moria_room";

void
create_moria_room()
{
  set_short("On a stairway");
  set_long("The walls on either side of the staircase rapidly come "+
  "together and form a bottleneck in the passageway here. Steps "+
  "continue upwards to the east leading further into this long "+
  "abandoned city. The bottom of the staircase is no longer visible "+
  "to the west.\n");

  add_item(({ "steps", "stairs" }),
     "These stone stairs show signs of wear. Small cracks can be seen "+
     "here and there.\n");
  add_item(({ "crack", "signs" }),
     "You might be cracked too if you were this old!\n");
  add_item(({ "stairway", "staircase", "walls" }),
     "Although not nearly as large as it was at the bottom there is "+
     "still a good fifty feet between the walls of the staircase.\n");
  add_exit("/d/Shire/khazad/west/stairs_bottom","down",0,3);
  add_exit("/d/Shire/khazad/west/stairs_top","up",0,3);
}
