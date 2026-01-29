
inherit "/d/Shire/khazad/moria_room";

void
create_moria_room()
{
  set_short("Inside Durin's Doors");
  set_long("The west end of the ancient entry hall of Khazad-dum. "+
     "The Doors of Durin stand immediately to your west. Smooth, high walls "+
     "to the north and south guide the broad path you stand on eastwards. "+
  "The high ceiling is hidden in the darkness above. A thin layer "+
  "of dust covers the ground.\n");

  add_item(({ "walls", "wall" }),
     "Carved by dwarven craftsman of ages past these unadorned walls "+
     "are cold, and smooth to the touch.\n");
  add_item(({ "floor", "ground" }),
     "Besides being covered by a fine dust the floor looks rather "+
     "barren as far as you can see.\n");
  add_item(({ "doors", "doors of durin" }),
     "While intricately carved and crafted on the "+
     "outside, the inside matches the plain, unadorned walls. In fact "+
     "because of the superb craftmanship, you can no longer "+
     "distinguish the closed doors from the western wall.\n");
  add_item(({ "ceiling", "roof" }),
     "It is hidden high in the darkness above you.\n");
  add_exit("/d/Shire/khazad/west/stairs_bottom","east",0,1);
}
