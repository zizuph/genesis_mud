/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "std/room";
#define PATH "/d/Terel/mecien/valley/guild/"

object monster;

reset_room(arg){
   
   if(!monster){
      monster=clone_object(PATH + "empmas");
      monster->move(this_object());
   } else {
      monster->reset_trader();
   }
}
create_room(){
   
set_short("Emporium");
set_long(
"An incredible hall, filled with pillars that circle it and rise up into\n"
+"a small dome which is set with many skylights. The hall itself is round,\n"
+"the pillars standing near the walls like supports. The floor is made of\n"
+"beautiful blue stone, the walls and pillars of a silvery-white stone.\n"
+"Stone benches fill the central area of the hall, along with a stone table\n"
+"and a dias. A silver wheel hangs from the dome on silver chains, from\n"
+"which banners are suspended.\n" 
);
   
   add_item("banners", "There are four banners: red, blue, white and silver.\n");
   add_item("red banner", "Of fiery red silk, it has the image of an eagle and\n"
           + "a censer, a few words are written upon it.\n");
   add_cmd_item("red banner", "read",
      "Our flame shall reach the ends of the world.\n");
   add_item("blue banner", "Of royal blue, it bears the image of a serpent and\n"
          + "a crystal flagon, a few words are written upon it.\n");
   add_cmd_item("blue banner", "read",
      "Let our waters be both life and death.\n");
   add_item("white banner", "Of purest white, it displays a dove flying over a\n"
               + "golden harp, a few words are written upon it.\n");
   add_cmd_item("white banner", "read",
      "The voice of the mystic drifts in the winds as a song of peace.\n");
   add_item("silver banner", "It is brilliant silver, it exhibits the image of\n"
            + "a ram and a ring of stone, a few words are written upon it.\n");
   add_cmd_item("silver banner", "read",
        "As the stones of the earth shall we be bound in strength.\n");
   add_item("wheel", "It is a large decorative wheel of intricate silver\n"
   + "workmanship, it is set with stars of crystal.\n");
  add_item("dias", "A small dias in the center, like a speakers podium.\n");

   add_exit(PATH + "s_hall2", "east", 0);
   add_exit(PATH + "forge", "west", 0);
   
   
   reset_room();
}




