// Bazaar Street10 (/d/Avenir/common/bazaar/extr/str10.c)
// creator(s):   Triana 1994
// last update:  Tepisch Sept 94, Ilyian May 95


#include "../bazaar.h"
inherit (EXTR + "std_ctr2");

#define BAZAAR_MAP	(BAZAAR +"mortal_bazaar")


void
create_room()
{
   add_exit(EXTR + "str11", "east", 0);
   add_exit(BAZAAR + "pier/pier", "west", 0);

   AI(({"building","brown building"}), "It is an unobtrusive "+
     "brown color. Going east and then north will bring you "+
     "to the entrance.\n");

   AI(({"compound", "south compound"}), "The sounds of training "+
     "appear to be coming from it. If you go east and then turn "+
     "south you will find the entrance.\n");

   AI(({"sign", "signpost"}), "It is an ordinary signpost, with "+
      "words written in Common language.\n");
   
   set_short("West side, near Dancing Potato and Survival Center");
   make_the_room("\n   A gravel path continues east into the "+
       "market's center. The oddly unappetizing smell of cooking "+
       "food wafts from the brown building north of you. "+
       "Grunts and muffled clanging sounds come from the "+
       "compound to the south. To the west, a wooden pier extends "+
       "over the black waters of the edge of the island.\n"+
       "A signpost has been planted here.\n");

    add_npc(NPC + "grd", 2);
    add_npc(NPC + "garbage_picker");
}

void
do_crunch()
{
   write("Gravel crunches under your feet.\n");
}

void
do_nogo()
{
   write("The entrance to that building is further east.\n");
}

int
do_read(string str)
{
    if ( (str!="sign") && (str!="signpost") )
        return 0;

    setuid();
    seteuid(getuid());

    this_player()->more(read_file(BAZAAR_MAP));
    write("\nYou determine that you are just west of the flower stall, "+
        "which is number 3 on the map.\n");
    return 1;
}

void
init()
{
    ::init();
    ADD(do_read, "read");
    ADD(do_crunch,"west");
    ADD(do_nogo, "north");
    ADD(do_nogo, "south");
}
