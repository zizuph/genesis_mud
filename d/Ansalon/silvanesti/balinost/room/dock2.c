
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
    set_short("Balinost dock on the Thon-Thalas");
    set_long("@@long_descr");


    add_exit(BROOM + "path","northwest",0);

    reset_balinost_room();
}

string
long_descr()
{
    return tod_descr2()+"This is one of the docks in Balinost.  "+
      "About once a season a transport ship comes to take the last "+
      "of the Silvanesti from here to Southern Ergoth.  The waters "+
      "of the "+
      "Thon-Thalas are dark and muddy.  The river churns southwards "+
      "and empties its load into the Southern Courrain Ocean.  "+
      tod_descr1()+season_descr()+"\n";

}
