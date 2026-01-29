/* Valley near Tantallon
 * By Teth, Jan 18 1996
 */

#include "local.h"
inherit VALLEYBASE;

public void
create_valley()
{
    add_my_desc("A stream of sewage ends in this area, forming an extensive " +
        "puddle. Foothills surround you, in all directions except south.\n");
    AI(({"stream of sewage","stream"}),"The stream of sewage flows off of " +
        "the foothills to the northwest, from the city of Tantallon.\n");
    AI(({"tantallon","city","city of tantallon"}),"You can barely see it, " +
        "up and to the northwest.\n");
    AI("sewage","The sewage is raw human excrement, mixed with wastes and " +
        "dirt.\n");
    AI(({"excrement","human excrement","raw excrement","raw human excrement",
        "wastes","dirt"}),"Shit!\n");
    AI(({"extensive puddle","puddle"}),"The puddle of excrement is shallow, "+
        "but nauseous.\n");

    AE(TROOM + "valley3", "south", 0, 1);
    reset_tant_room();
}

