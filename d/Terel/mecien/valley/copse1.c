inherit "std/room";

create_room(){
   
   set_short("Copse of Willow");
   set_long(break_string("This small gathering of willows gleams in the " +
      "sun of the valley, their long branches draping down" +
      " to the ground. The earth is very damp. To the north the copse "
      + "continues.\n",75));
   
   add_exit("/d/Terel/mecien/valley/path4", "south", 0);
   add_exit("/d/Terel/mecien/valley/copse2", "north",0);
      add_item(({"trees","tree","willow","willows"}),break_string("These "
   + "majestic trees fill you with a sense of peace and serenity. Their "
   + "branches, as thick as the "
+ "trunks, root the ancient trees to the ground with such solidity you doubt a "
   + "hurricane could uproot them.\n",75));
}

