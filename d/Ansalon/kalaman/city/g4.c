/* Added a revelation for OotS - Arman 2017 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/guilds/OotS/defs.h"

inherit CITY_OUT;
#include "/d/Krynn/common/herbsearch.h";

#define KRHERB "/d/Krynn/common/herbs/"
#define H1 KRHERB + "fdlhead"
#define H2 KRHERB + "fdlhead"
#define H3 KRHERB + "licorice"
#define H4 KRHERB + "licorice"

object mantis;

void
reset_kalaman_room()
{
    set_searched(random(2));

    if(!objectp(mantis))
    {
       mantis = clone_object(KNPC + "mantis");
       mantis->move(TO);
    }

}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("A private garden in Kalaman");

    add_item(({"stone path","path"}),
      "A neat path, made of small brown stones, weaves its way around the garden.\n");

    add_item(({"great trees","trees","tree"}),
      "Trees of great size and beauty fill the garden. They have been well taken " +
      "care of and are obviously the pride of some local gardener.\n");
    add_item(({"flowers","flower"}),
      "Flowers of all kinds fill the garden.\n");

    seteuid(getuid(TO));
    set_search_places(({"garden","park","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);

    add_cmd_item(({"with the mantis","with mantis","mantis"}),
         ({"pray","meditate"}),"@@meditate_mantis");

    add_exit(CITY + "g1","northwest",0);
    add_exit(CITY + "g2","west",0);
    add_exit(CITY + "g5","southwest",0);
    reset_kalaman_room();
}

string
long_descr()
{
    return "You find yourself standing in a beautiful garden in the middle " +
    "of Kalaman. " +season_garden()+ "A stone path leads away from " +
    "here to your northwest, west, and southwest.\n";
}

string
meditate_mantis()
{
    if(!objectp(mantis))
      return "What?\n";

    write("You close your eyes and meditate with the praying mantis.\n");
    say(QCTNAME(TP)+ " closes " +HIS(TP)+ " eyes and meditates with the " +
          "praying mantis.\n");

    if(IS_OOTS(TP))
    {
          if(!OOTS_QUERY_REV(TP, "majere"))
          {
            TP->catch_msg("\n\nAs you meditate with the praying mantis, a revelation is " +
                "granted to you on the aspect of the god Majere!\n\n\n");
            OOTS_ADD_REV(TP,"majere","the aspect of majere");  
          }
    }

    return "";
}
