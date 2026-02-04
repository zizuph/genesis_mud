inherit "std/room";

create_room(){
   
   set_short("Copse of Willow");
   set_long(break_string("This small gathering of willows gleams in the " +
      "sun of the valley, their long branches draping down" +
   " to the ground. Small white stones are scattered about the" +
   " ground and get heavier northwards. A strong wind catches in "
   + " branches, providing a whispering melody. The earth is damp and "
   + " small pools of water collect.\n",75));
   
   add_item("stones", "They are small white stones. They get more\n"
   + "numerous in the grounds to the north.\n");
    add_item("pools", "Because of the wet ground the rain waters have\n"
  + "formed small standing pools.\n");
   add_exit("/d/Terel/mecien/valley/copse2", "south", 0);
   add_exit("/d/Terel/mecien/valley/lv", "north",0);
      add_item(({"trees","tree","willow","willows"}),break_string("These "
   + "majestic trees fill you with a sense of peace and serenity. Their "
   + "branches, as thick as the "
+ "trunks, root the ancient trees to the ground with such solidity you doubt a "
   + "hurricane could uproot them.\n",75));
}

