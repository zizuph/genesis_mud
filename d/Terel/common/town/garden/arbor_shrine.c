// modified by Lilith, Mar 2022:  updated desc and added items.
 
#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

#define PATH "/d/Terel/common/town/garden/"
inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

int pick;

void
reset_room()
{
	pick = 5;
    set_searched(0);
}

void
create_room()
{
  
    set_short("Arbor Shrine");
    set_long(
    "Dazzling in its vibrant glow, this is a great arbor made from\n"
   +"tall aquamarine bushes. It forms a small shrine of life, giving\n"
   +"the place a feeling of great sanctity. It is very calm here amidst\n"
   +"the glow of green, the smell of foliage and the whispers of the\n"
   +"wind through the leaves.\n");

    set_up_herbs( ({one_of_list(RANGER_HERBS),
                    one_of_list(MM_HERBS),
                    one_of_list(ANY_HERBS),
                  }),
                  ({"ground","garden","bushes","rows","here"}), 
                   3 );
   add_cmd_item("leaf", "pick", "@@pick");
   add_item(({"bush", "bushes", "plants", "foliage"}),
   "They are tall bushes, perhaps evergreen, of a brilliant and very\n"
   +"beautiful aquamarine color. The leaves are very crisp and the\n"
   +"edges jagged.\n");

   add_item(({"garden","sacred garden","ground"}),
      "The sacred garden looks well maintained.\n");
   add_item(({"greenery", "hollies", "yews", "box", "hedges",
      "firs","pines","spruce", "cedar","redwood","trees","juniper", 
      "hemlock", "myrtle", "candleberry", "mosses", "shrubs",
      "moss", "ivy", "forest"}),
      "Kept in perfect condition by the vigilant gardeners.\n");

   add_exit("/d/Terel/common/town/garden/glade", "northwest", 0);
   reset_room();
}

int
pick()
{
   object ob;
   pick--;
   if(pick < 1)
   {
      write("No more leaves may be picked at this time.\n");
      return 1;
   }
   seteuid(getuid(this_object()));
   ob =clone_object(PATH +"leaf");
//   ob=clone_object("/d/Terel/mecien/valley/guild/quest/leaf");
   ob->move(this_player());
   write("You pick a leaf from the bushes of the arbor.\n");
   say(QCTNAME(this_player()) + " picks a leaf from the bushes.\n");
   return 1;
}
