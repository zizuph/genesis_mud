#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit BALIFOR_OUT;

create_balifor_room()
{
    set_short("Street on the Bay");
    set_long("@@long_descr");
    add_item(({"Breakwater","breakwater"}),"@@break_water");
    add_item(({"steppes","Steppes"}),"@@steppes");
    add_item(({"main road","road"}),"The main road travels " +
      "northeast and southwest along the coast.\n");
    add_item(({"coast","bay"}),
      "To your west is the Bay of Balifor, where wharfs extend " +
      "out from the land to make up much of what is considered " +
      "Port Balifor.\n");
    add_item(({"wharfs","wharf"}),"To your northwest a wharf " +
      "extends out into the Bay.\n");
    add_item("smaller road","A smaller road branches " +
      "off from the main road to the southeast.\n");
    add_exit(BROOM + "city14","southeast",0);
    add_exit(BROOM + "city05","southwest",0);
    add_exit(BROOM + "city03","northeast",0);
    add_exit(BROOM + "pier03","northwest","@@pier",0);

}

int
pier()
{
    write("You walk out onto the wharf.\n");
    return 0;
}

string
long_descr()
{
    return tod_descr1() + "You are standing on the main road "+
    "along the coast of Balifor. To the northwest, the wharf " +
    "extends out to a pier. Southwest you see the Breakwater. "+
    "The main road continues to the southwest and northeast "+
    "along the coast, while a smaller road branches off from "+
    "the main road here going southeast, away from the Bay. "+
    season_descr()+"\n";
}
