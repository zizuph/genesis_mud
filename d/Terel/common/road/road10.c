// modifications:
// Lilith Jan 2022: updated room desc and exit to moors.

inherit "/std/room";

void
create_room() 
{

    set_short("Road");
   set_long("This is a road heading north from the Cornerstone on "
    + "a steep incline high up into the rolling hills. Southeast "
    + "you can see an obelisk and a pond out on the moors. You "
    + "think you hear some noises, but you are unable to make out "
    + "their origin.\n");

   add_item(({"snow"}), "It makes you want to build a snowman.\n");

   add_item(({"hills", "rolling hills"}), "They go for as far as "
    + "the eye can see.\n");
   add_exit("/d/Terel/common/road/road9", "south", 0);
   add_exit("/d/Terel/common/moor/main/moor_path", "southeast", 0);
   add_exit("/d/Terel/common/road/road11", "north", 0, 3);

   write("A small goblin arrives.\n");
   write("A small goblin hits you with a snowball.\n");
   write("Small goblin disappears.\n");
}

