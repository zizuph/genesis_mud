inherit "/std/room";

#define PATH "/d/Terel/mecien/dark/"

create_room(){

set_short("Circle");
set_long("This large cavern has been cut carefully from the\n" +
         "stone. The ceiling forms a polished dome, the floor\n" +
         "is also polished, being inset with a large circle.\n" +
         "In the center of the circle is a small dias, made from\n" +
         "some black stone. Black iron torches are set into the\n" +
         "stone about the circle.\n");

add_item("crystal", "It is beautiful rock crystal, it forms many\n"
   + "strange shapes and shines a variety of hues.\n");
add_exit(PATH + "se4c", "southwest", 0);

}

