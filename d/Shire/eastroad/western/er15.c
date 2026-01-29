#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   area = "a short distance from"; /* Distance from areaname */
   areaname = "Bywater";
   land = "the Shire";
   areatype = 8;
   areadesc = "rolling plain";
   grass = "green";
   
    add_prop(ROOM_M_NO_ATTACK, "The Three Farthing Stone glows, " +
        "preventing your attack.\n");
    add_prop(OBJ_M_NO_ATTACK, "The Three Farthing Stone glows, " +
        "preventing your attack.\n");
    add_prop(ROOM_I_NO_MAGIC_ATTACK,"The Three Farthing Stone " +
        "glows, preventing your attack.\n");
  
   extraline = "You are standing at the Three Farthing Stone, the "+
   "famous stone that was erected to celebrate the first setting of "+
   "boundaries in Siragale, now known as the Shire. Around the "+
   "Stone you can see the remains of many camps. If you go east " +
   "along the road, you will come to the "+
   "hamlet of Frogmorton, while not far to the west lies Bywater and "+
   "Hobbiton. To the north, the river known as The Water rushes "+
   "along merrily towards its meeting with the Baranduin river.";

room_add_object("/d/Shire/eastroad/obj/farthing_stone");
/*   
   add_item(({"stone","three farthing stone"}),"This stone marks the "+
      "boundaries between the divisions of the Shire, known as "+
      "Farthings. Rumour has it that the stone is magical, a gift "+
      "from the Eldar to mark the junction of the Farthings.\n");
*/   
   add_item("bywater",
      "The hamlet of Bywater lies a few miles to the west, just off"+
      "the Great East Road. Bywater has a well known inn, The "+
      "Green Dragon, that is well worth a visit.\n");
   
   add_item("hobbiton",
      "Beyond Bywater lies the village of Hobbiton, the former capital "+
      "of the Shire. Hobbiton is still one of the largest places in the "+
      "Shire, and is situated almost in the middle of the Shire.\n");
   
   add_item(({"camp","campsite","remains","camping site"}),
      "The remains of camp fires long extinguished lie beside "+
      "the Stone, marking where other travellers have stopped "+
      "for the night. The Stone seems to invite you to nap here.\n");
   
   add_item(({"frogmorton","hamlet"}),
      "Situated on the Great East Road between Hobbiton and Bree, "+
      "Frogmorton is a pretty little hamlet, and makes a nice resting "+
      "spot.\n");
   
   add_item(({"river","baranduin","water","the water"}),
      "Running through the Shire, The Water feeds into the Baranduin "+
      "river far to the east.\n");

   add_exit(EAST_R_DIR + "er14","west",0,2);
   add_exit(EAST_R_DIR + "er16","east",0,2);
   add_exit(EAST_R_DIR + "er15n","north",0,2,1);
   add_exit(EAST_R_DIR + "er15s","south",0,2);   
}

string
nap_desc()
{
   return "You lie down beside the Three Farthing Stone, "+
   "and have a peaceful nap. It almost feels as if there "+
   "is a magical presence keeping watch over you, ensuring a safe "+
   "rest.\n";
}

void
init()
{
   ::init();
   add_action("rest_player","camp",0);
   add_action("rest_player","rest",0);
   add_action("rest_player","sleep",0);
   add_action("rest_player","nap",0);

}

int
rest_player()
{
// The stone is magical, allowing people people to reduce fatigue. 
//This is also a no attack room due to the Stone
   TP->add_fatigue(-1);  
   write(nap_desc());
   return 1;
}
