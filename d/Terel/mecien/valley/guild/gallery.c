/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){
   set_short("Gallery");
   set_long(
      "Austere in its silence, this ancient stone hall rests in a peace\n"
      + "all of its own. Its vast vaulted ceiling provides an echo, but also\n"
      + "drowns out all strong noise. Massive windows of stained glass line\n"
      + "the upper walls, through which light descends into the solemnity of\n"
      + "this great hall. The lower part of the walls are covered with tapestries.\n"
   );
   
   add_item("ceiling", "It is a vast vaulted ceiling, in which all the noises\n"
      + "of the world fade into oblivion.\n");
   add_item(({"window", "stained glass", "windows"}),
      "These massive windows hold colorful images of creatures from the\n"
      + "enchanted world. There are faeries, sylphs, pixies, unicorn, fauns,\n"
      + "dryads, centaur, leprechaun and peries.\n");
   
   add_item(({"tapestry", "tapestries"}), "They are made of red velvet and " +
      "sewn with silver writings.\n");
   add_cmd_item("tapestry", "read", "Which one do you wish to read?\n");
add_cmd_item("writings", "read", "Which tapestry do you wish to read?\n");
   add_item("writings", "They are sewn in silver upon each of the dozen tapestries.\n");
   add_cmd_item(({"1", "tapestry 1", "first tapestry"}),
      "read", "I arise from the ground to meet the fiery sky. Though I am " +
      "gentle, my countenance is brilliant.\n"); 
   add_cmd_item(({"2", "tapestry 2", "second tapestry"}),
      "read", "By my hue shall you know me, always, for I am never changing. " +
      "\n");
   add_cmd_item(({"3", "tapestry 3", "third tapestry"}),
      "read", "From whence have I fallen.\n");
   
   add_cmd_item(({"4", "tapestry 4", "fourth tapestry"}),
      "read", "I shall comfort thee, for my touch is like the wind.\n");
   add_cmd_item(({"5", "tapestry 5", "fifth tapestry"}),
      "read", "Though I seem dead, I am life. One day I shall cover you with my glory.\n");
   add_cmd_item(({"6", "tapestry 6", "sixth tapestry"}), 
      "read", "My touch is like stone, the bitter tear of rain.\n");
   add_cmd_item(({"7", "tapestry 7", "seventh tapestry"}),
      "read", "Though the fire has come, yet do I remain.\n");
   add_cmd_item(({"8", "tapestry 8", "eighth tapestry"}),
      "read", "Though you cannot understand me, I hold great knowledge.\n");
   add_cmd_item(({"9", "tapestry 9", "ninth tapestry"}),
      "read", "My precious face gleams bright.\n");
   add_cmd_item(({"10", "tapestry 10", "tenth tapestry"}),
      "read", "So clear to the mind, that I shall bring vision "
      + "in the dark.\n");
   
   add_cmd_item(({"11", "tapestry 11", "eleventh tapestry"}),
      "read", "I am the sweet taste of life.\n");
   add_cmd_item(({"12", "tapestry 12", "twelfth tapestry"}), 
      "read", "Though the dead lie about me, I collect myself up to record the ages.\n");

   add_exit("/d/Terel/mecien/valley/guild/temple", "north", 0);
}


