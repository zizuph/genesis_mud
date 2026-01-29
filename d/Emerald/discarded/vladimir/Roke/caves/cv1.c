inherit "/std/room.c";

void
create_room()
{
   set_name("cave1");
   set_long(
      "As you enter this giant cave you notice the sound of slowly dripping water "+
      "echoing throughout the cave. There are many small rocks scaterred around "+
      "You see a small wooden sign mounted on the east wall, above it, a torch. "+
      "The cave ahead splits into three different directions. Each emits it's own "+
      "aura of evil.\n");
   add_exit("/d/Immortal/vladimir/caves/entrance.c", "out");
   
   add_item(({"sign", "wooden sign"}),
      break_string("As you wipe away the years of dust, you are able to read the "+
         "following; 'Continue no further if you are not true of heart, brave "+
         "of soul +"
         "or quick of mind. The gates below are fools' gates, Hell's gates...\n", 70));
   add_item(({"torch", "flame"}),
      break_string("This torch gives off a large amount of light. It looks magical "+
 "in nature. It seems to be bolted firmly to the wall.\n");
}
