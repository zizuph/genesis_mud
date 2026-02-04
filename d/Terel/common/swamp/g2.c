inherit "/std/room";

#define PATH "/d/Terel/common/swamp/"

create_room(){
   set_short("Swamp");
   set_long("This is a warm section of the swamp. Here small geysers\n"
      + "spout out hot spring waters. The water stays fairly warm and\n"
      + "causes many more plants to grow. Most of the ice and snow is\n"
      + "melted in this area, though some remains. Rocks jut out from the\n"
      + "ground, memoirs of the hills to the north.\n");
   
   add_item("water", "It is hot near the geysers, but it cools quickly\n"
      + "in the cool air where it remains fairly warm. The water is clean.\n");
   add_item("plants", "There are many mosses, grasses and shrubs.\n");
   add_item("rocks", "They jut out from the swamp, like monuments.\n");
   add_item(({"ice", "snow"}), "Mostly all melted away.\n");
   
    add_exit(PATH + "g1", "southeast", 0);
    
   add_exit(PATH + "sw6", "north", 0);
   
   
   add_item("geysers", "They are small, but they blast forth a strong\n"
      + "current of hot spring water. They keep the area in steamy mist.\n");
   add_item(({"steamy mist", "mist", "steam"}),
      "It hangs all over the swamp, it is caused by the hot water geysers.\n");
   
}
