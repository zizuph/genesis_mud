inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/common/town/mansion/"

reset_room(arg){
   
}

create_room(){
   
   set_short("Grand Hall");
   set_long("This is the magnificent grand hall of the mansion, its brightly\n"
      +"polished wooden walls gleam a marvelous chestnut colour. The floor\n"
      +"is covered with a plush burgundy carpet. High above, an arched\n"
      +"wooden ceiling set with crystal chandeliers, lights the hall.\n"
      +"Upon the walls hang large portrait paintings, tapestries, shields\n"
      +"with coats of arms and devices. A small balcony hangs over the\n"
      +"hall from the east wall, from which banners and crests hang.\n"
   );
   add_item(({"coat of arms", "shields", "devices"}),
      "There are four shields that display coats of arms and devices.\n"
      + "They hang along the walls. The first is the largest and hangs\n"
      + "upon the north wall.\n"
   );
   add_item(({"balcony"}), "It is too high to look at closely.\n");
   add_item("carpet", "It is a thick plush burgundy red carpet. It covers\n"
      + "most of the floor.\n"
   );
   
   add_cmd_item(({"carpet", "burgundy carpet", "red carpet"}),
               ({"move", "roll", "pull"}),
              ({"It is just too large!\n", "It is secure.\n","Too heavy\n"
               }));

   add_item(({"crystal chandelier", "chandelier", "lights"}),
      "They are beautiful, many faceted crystal chandeliers that hang\n"
      + "from the high vaulted wooden ceiling.\n");
   
   add_item(({"portrait paintings", "paintings", "painting", "portrait", "portraits"}),
      "These are grandly painted portraits of unknown nobles.\n");
   
   add_item(({"walls", "wall"}),
      "The walls appear to be made of chestnut. Rich in colour, and highly\n"
     +"polished, they seem to glow with warmth.\n");
   
   add_exit(PATH + "stairs", "west", 0);
   add_exit(PATH + "gallery", "south", 0);
   
   reset_room();
   
}

