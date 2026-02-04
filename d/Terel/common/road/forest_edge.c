/*
 *  This is the forest entrance, coded by Vader on 6/29/92
 */
inherit "/std/room.c";
#define HOME_DIR "/d/Terel/common/forest/"

create_room()
{
   set_short("Forest Entrance");
   set_long("You are on a path leading south into a large pine "
    + "forest.\nAs you gaze southwards, you think you see several "
    + "tiny eyes\nlooking you over.  To the north, you can see "
    + "a cornerstone,\nand south, nothing but snow covered trees.\n");

   add_item(({"trees", "tree"}), "They are tall and green.  Pine trees "
   + "often do well in the cold.\nThey are covered with snow in such a "
   + "way that the light reflected off\nof them gives it a silver color.\n");

   add_item(({"cornerstone", "stone"}), "It's too far to see any "
    + "detail.\n");


   add_item(({"snow"}), "Don't you just wanna build a Snowman?\n");

   add_exit("/d/Terel/silver/road/road63", "south", 0);
   add_exit("/d/Terel/common/road/cornerstone", "north", 0);

}
