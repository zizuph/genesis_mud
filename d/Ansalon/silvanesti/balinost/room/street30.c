
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
    set_short("Streets of the outer circle of Balinost");
    set_long("@@long_descr");

    add_item(({"street","streets","stone","stones","cobblestones"}),
      "The mud underlying the street has swallowed most of the "+
      "stones.  You are surprised to see no weeds growing from "+
      "the missing cobbles, but then you realize that nothing "+
      "grows in this forsaken city.\n");

    add_exit(BROOM + "house09","north",0);
    add_exit(BROOM + "street31","west",0);
    add_exit(BROOM + "street29","east",0);

    reset_balinost_room();
}

string
long_descr()
{
    return tod_descr2()+"You are on the streets of the outer circle "+
      "of Balinost.  These streets used to have had an excellent "+
      "cobblestone make, but these dark times have turned the way "+
      "into a mud with few of the original stones showing. " +
      tod_descr1()+season_descr()+"\n";
}
