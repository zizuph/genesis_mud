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
    set_short("The fountain at the center of Park Square");
    set_long("@@long_descr");

    add_item("fountain","The fountain is made entirely of quartz.  You "+
      "aren't quite sure how it worked in the past, but it certainly "+
      "doesn't work at all now.  You are unable to see to the bottom "+
      "of the fountain through the muddy water, and can't estimate its "+
      "depth.  A weathered bronze plaque is mounted on one of the "+
      "ledges.\n");
    add_item("plaque","The bronze plaque hasn't survived time as well "+
      "as the fountain itself has.  Although much of the lettering is "+
      "rusty, the words are still legible.\n");

    add_cmd_item("plaque","read","@@read_plaque");
    add_exit(BROOM + "park2","north",0);
    add_exit(BROOM + "park7","south",0);
    add_exit(BROOM + "park4","west",0);
    add_exit(BROOM + "park5","east",0);

    reset_balinost_room();
}

string
long_descr()
{

    return "This is the fountain at the center of Park Square.  The "+
      "fountain appears broken, and the water is muddy.  The pool "+
      "surrounding the spout is twenty feet in diameter and must "+
      "have been a brilliant sight during the fountain's working "+
      "days.  "+tod_descr1()+tod_descr2()+season_descr()+"\n";

}

string
read_plaque()
{
    return "The plaque reads:\n\n"+
      "          Dedicated to the memory of a good friend.\n"+
      "     May this fountain forever flow in the name of Balif.\n\n";
}
