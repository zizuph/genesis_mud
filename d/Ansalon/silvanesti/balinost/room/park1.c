#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/balinost/local.h"
#include <ss_types.h>
#include <macros.h>


inherit BALINOST_OUT;

void
reset_balinost_room()
{
    return;
}

create_balinost_room()
{
    set_short("Northwest corner of Park Square");
    set_long("@@long_descr");

add_item(({"tree","trees"}),"The trees of the park haven't had leaves since "+
      "the summer before the evacuation began.  Since then the wood has begun "+
      "to contort, giving the trees a very hauting appearance.  It looks like "+
      "these trees will soon be similar in appearance to those in the forest "+
      "to the north.\n");
    add_item(({"park","square"}),"The park is square in shape with trees " +
      "lining the perimeter.  In the center of the park is a quartz fountain "+
      "that no longer works.  Stone benches surround the fountain to allow "+
      "people to relax and observe the fountain.\n");
    add_item("fountain","The fountain lies southeast of here.  You feel you "+
      "can examine it better from there.\n");
    add_item(({"bench","benches"}),"The stone benches must have looked "+
      "inviting before darkness overtook the land.  Now the benches are "+
      "cracked, warped, and covered with a slimy film.  These benches are "+
      "decidedly not worth placing your backside upon.\n");

    add_exit(BROOM + "park2","east",0);
    add_exit(BROOM + "park4","south",0);
    add_exit(BROOM + "street01","northwest",0);

    reset_balinost_room();
}

string
long_descr()
{
    return "This is the northwest corner of Balinost's Park Square.  "+
      "Once a place of frolicking and happiness, the park is now lifeless.  "+
      "None of the trees here have leaves, and they all look as if they "+
      "are beginning to twist and deform. "+tod_descr1()+tod_descr2()+
      season_descr() + "\n";
}


