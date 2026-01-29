#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>


inherit BLOODSEA_OUT;

#include "/d/Krynn/common/herbsearch.h" 

object elf1, elf2, elf3;

#define HARD_TO_SWIM  55

#define KRHERB "/d/Krynn/common/herbs/"
#define H1 KRHERB + "bull_kelp"
#define H2 KRHERB + "elkhorn_kelp"
#define H3 KRHERB + "laminaria"
#define H4 KRHERB + "sea_bubble"

void
reset_bloodsea_room()
{
   set_searched(random(2));

   if(!objectp(elf1))
   {
      elf1 = clone_object(BNPC + "sea_elf");
      elf1->arm_me();
      elf1->move(TO);
   }

   if(!objectp(elf2))
   {
      elf2 = clone_object(BNPC + "sea_elf");
      elf2->arm_me();
      elf2->move(TO);
   }

   if(!objectp(elf3))
   {
      elf3 = clone_object(BNPC + "sea_elf_prince");
      elf3->arm_me();
      elf3->move(TO);
   }
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item("surface","You cannot see the surface from here, the sea kelp closes up above you.\n");
    add_item(({"isle","mithas","isle of mithas"}),
        "You cannot see the isle from here, as your vision underwater is limited.\n");
    add_item(({"kelp","sea kelp","forest"}),
        "A forest of kelp surrounds you, swaying gently with the current. It seems the only direction " +
        "you can swim through it is to your southeast.\n");

    add_invis_exit(BROOM +"uw2", "southeast", 0, 2);

    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
 
    seteuid(getuid(TO));
    set_search_places(({"kelp","sea","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);

    reset_bloodsea_room();

}

void
set_sink_path(string sp)
{
    sink_path = BROOM + "uw2";
}

string
short_descr()
{
    return "in a forest of kelp at the bottom of the Bloodsea of Istar";
}
 
string
long_descr()
{
    return "You find yourself floating at the bottom of the Bloodsea of Istar " +
       "surrounded by a forest of kelp that sways gently with the current. " +
       "To your southeast the sea kelp opens " +
       "up somewhat. You could probably swim out of this forest in that direction.\n";
}