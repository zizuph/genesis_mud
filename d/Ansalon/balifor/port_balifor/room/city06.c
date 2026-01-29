#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit BALIFOR_OUT;

create_balifor_room()
{
    set_short("Street on the Bay");
    set_long("@@long_descr");
    add_item(({"Breakwater","breakwater"}),"@@break_water");
    add_item(({"steppes","Steppes"}),"@@steppes");
    add_item(({"main road","road"}),
      "You stand upon the main road that leads northwest and " +
      "southeast.\n");
    add_item("smaller road","A smaller road branches off " +
      "from the main road to the northeast.\n");
    add_item(({"southeast","wharf","pier"}),
      "To the southeast the wharf extends out to a pier.\n");
    add_item(({"coast","bay","Bay"}),
      "Out to the west is the Bay of Balifor.\n");
    add_exit(BROOM + "city02","southeast",0);
    add_exit(BROOM + "city07","northwest",0);
    add_exit(BROOM + "city08","northeast",0);
    add_exit(BROOM + "pier02","southwest","@@pier",0);

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
    return tod_descr1() + " You are standing on the main road "+
    "along the coast of Balifor. To the southeast, the wharf "+
    "extends out to a pier. Northwest you see the Breakwater. "+
    "The main road continues northwest and southeast while a "+
    "smaller road branches off from the main road here going "+
    "northeast, away from the Bay. "+season_descr()+"\n";
}
