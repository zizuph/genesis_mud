#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define H1 KRHERB + "tangleshoot"
#define H2 KRHERB + "hazelnut"
#define H3 KRHERB + "bunchberry"
#define H4 KRHERB + "chantrelle"

void
reset_flotsam_room()
{
   set_searched(random(2));
}

create_flotsam_room()
{
   set_short("Within a vast evergreen forest");
   set_long("@@long_descr");
   
   add_item("branches","The branches of great oaks sway " +
      "with the wind.\n");
   add_item(({"forest","evergreen forest","ancient forest","great oaks",
            "vast evergreen forest","vast forest",
            "ancient oaks","thick underbrush","shadows","trees"}),
      "Surroundings you is an ancient evergreen forest of great " +
      "oaks and thick underbrush. Sounds echoing from the shadows " +
      "give the forest a forboding aspect.\n");
   
   add_invis_exit(FROOM + "nowhere","north","@@no_go");
   add_invis_exit(FROOM + "nowhere","south","@@no_go");
   add_invis_exit(FROOM + "f8","east",0,4);
   add_invis_exit(FROOM + "f5","west",0,4);
   
   set_tell_time(120);
   add_tell("You hear a deep growl from the underbrush nearby.\n");
   add_tell("The branches of great oaks sway as a silent wind " +
      "blows through the forest.\n");
   
   seteuid(getuid(TO));
   set_search_places(({"forest","underbrush","herbs"}));
   add_prop(OBJ_I_SEARCH_TIME,3);
   add_prop(OBJ_S_SEARCH_FUN,"herb_search");
   add_herb_file(H1);
   add_herb_file(H2);
   add_herb_file(H3);
   add_herb_file(H4);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand within a vast evergreen forest." +
   season_descr() +
   " whistles through the branches of ancient oaks, and eerie " +
   "sounds echo from the shadows cast by the trees, as well as " +
   "from the underbrush, giving the forest a forboding aspect." +
   tod_descr2() + 
   "\n";
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   
   if(interactive(ob))
      start_room_tells();
}

int
no_go()
{
   write("Thick underbrush impedes travel in that direction.\n");
   return 1;
}
