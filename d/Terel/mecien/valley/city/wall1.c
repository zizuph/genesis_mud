inherit "std/room";

create_room(){
   
   set_short("City Wall");
   set_long("The craggy walls of the city rise up here. A deep moat\n" +
      "surrounds this side of the city, between the walls and\n" +
      "the hills, thus preventing travel around the city.\n" +
      "The walls are coated with dark moss, fungi and other growths\n" +
      "that have grown up from the moat. The water is dark and\n" +
      "murky, though it looks fresh.\n");
   
   add_exit("/d/Terel/mecien/valley/city/gates", "east", 0);
   
}
