
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit BALIFOR_OUT;
object kender;

void
reset_balifor_room()
{
    if(!objectp(kender))
    {
	kender = clone_object(KNPC + "kender");
	kender->move(TO);
    }
}

create_balifor_room()
{
    set_short("Street on the Bay");
    set_long("@@long_descr");
    add_item(({"breakwater","Breakwater"}),"@@break_water");
    add_item(({"steppes","Steppes"}),"@@steppes");   
    add_item(({"main","main road"}),
      "You are standing on the main road that heads south and " +
      "northwest.\n");
    add_item(({"coast","bay","bay of balifor"}),
      "To your west is the Bay of Balifor.\n");
    add_item(({"southeast","building"}),
      "To your southeast there is a building where quite a few " +
      "people are entering or leaving. Your guess is that it " +
      "is an inn or tavern.\n");
    add_item(({"dark ships","ships"}),
      "Dark ships of the dragonarmies patrol the bay.\n");
    add_item(({"smaller road","road","gate","Gates","northeast"}),
      "To your northeast a smaller road heads towards the Gates " +
      "of the City.\n");
    add_exit(BROOM + "city06","northwest",0);
    add_exit(BROOM + "city01","south",0);
    add_exit(BROOM + "city09","northeast",0);

    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + "You are standing on the main " +
    "road along the " +
    "coast in Balifor. To the southeast, you hear the sounds of "+
    "laughter, and spot many people going in and out of a building. "+
    "As you look out over the bay, you spot the dark ships of the "+
    "dragonarmy sailing in and out of Port Balifor. The main road "+
    "continues to the south and northwest. Looking northeast along "+
    "a smaller road, quite a distance ahead you spot the Gates "+
    "leading out of the City. "+season_descr()+"\n";
}

