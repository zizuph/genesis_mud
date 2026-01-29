#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Swamp");
    set_long("@@long_descr");

    add_exit(MROOM + "forest28","northeast",0);
    add_exit(MROOM + "swamp2","southwest","@@cross_swamp");

    add_cmd_item(({"stream","water","from stream","water from stream"}),
      "drink","@@drink_water");

}

string
drink_water()
{
    if(TP->drink_soft(TP->drink_max() /16, 0))
    {
        write("You manage to find a small pool that contains "+
              "some fairly clean water, and take a drink from "+
              "it.\n");
        say(QCTNAME(TP) + " finds a small pool that contains "+
              "some fairly clean water, and takes a drink from "+
              "it.\n");
        return "";
    }
    else
        write("You are full of water, you can't drink anymore.\n");
    return "";
}

int
cross_swamp()
{
    if((TP->query_encumberance_weight() >= 26) || (TP->query_stat(0) <= 78))
    {
        write("You as try to move forward, both your feet gets "+
              "stuck in the black-brown mud, and you find yourself "+
              "unable to move forward.\n");
        return 1;
    }
    write("You strain you muscles as you pull your feet from "+
          "and black-brown mud and move forward.\n");
    return 0;
}

string
long_descr()
{
    return tod_descr()+ " " +season_descr()+
    "You are standing in the middle of a large swamp on "+
    "the isle of Mithas. This area much have been fertile "+
    "soil once, with a wide variety of different plant and "+
    "tree species. Now it has all overcome to the massive "+
    "amount of rain that falls here, and turned this place "+
    "into a gloomy and swampy area. A small stream runs from "+
    "the northwest here and disappears to the southeast. "+
    "The small swampy area continues to the southwest.\n";
}
