#define ROAD remove_item("road"); \
   add_item(({"road"}), BSN(\
      "You are on an ancient road running from Pelargir in the south "\
      + "to Minas Tirith, the Capital of Gondor. "));
#define ROAD_GROUND remove_item("ground");\
   add_item(({"ground"}), BSN(\
      "The road is running over the fields of Lebennin. "));
#define RAMMAS add_item(({"rammas","rammas echor","wall"}), BSN(\
   "To the northeast, you can see the shadows of the Rammas Echor, "\
   + "the large outer wall of Minas Tirith. "));
#define MINDOLLUIN add_item(({"mindolluin","white mountains","ered nimrais"}),BSN(\
   "To the north, you can see the snow-covered tops of the Ered Nimrais, the White "\
   + "Mountains, running from west to east. The eastern spur of the White Mountains "\
   + "is the Mindolluin, the great mountain west of Minas Tirith. "));
