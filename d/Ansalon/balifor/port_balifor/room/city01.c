
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit BALIFOR_OUT;
object merc;
object merc2;

void
reset_balifor_room()
{
    if(!objectp(merc))
    { 
	merc = clone_object(KNPC + "mercenary");
	merc->move(TO);
    }

    if(!objectp(merc2))
    {
	merc2 = clone_object(KNPC + "mercenary");
	merc2->move(TO);
    }
}

create_balifor_room()
{
    set_short("Street on the Bay");
    set_long("@@long_descr");
    add_item(({"breakwater","Breakwater"}),"@@break_water");
    add_item(({"steppes","Steppes"}),"@@steppes"); 
    add_item(({"main road","road"}),"@@long_descr");
    add_item(({"east","building"}),"To your east stands the " +
      "Pig and Whistle Inn of Balifor.\n");
    add_item(({"wharf","bay"}),"A wharf to your west extends " +
      "out into the Bay of Balifor.\n");
    add_item("pier","To your east is a pier.\n");
    add_item("balifor","You stand at the edge of the city " +
      "of Balifor.\n");
    add_exit(BROOM + "inn","in","@@in",0);
    add_exit(BROOM + "city03","south",0);
    add_exit(BROOM + "city02","north",0);
    add_exit(BROOM + "pier01","west","@@pier",0);

    reset_balifor_room();
}

int
pier()
{
    write("You walk out onto the wharf.\n");
    return 0;
}

int
in()
{
    write("You step into a rowdy Inn.\n");
    return 0;
}

string
long_descr()
{
    return tod_descr1() + " You are standing on the main road "+
    "in Balifor which goes north and south from here. You "+
    "hear the sounds of laughter from the building to the "+
    "east. The wharf extends out into the bay here, leading "+
    "out to a pier. Only the dragonarmies are allowed to dock "+
    "their boats here now. "+season_descr()+"\n";
}

