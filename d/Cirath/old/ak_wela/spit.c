inherit "/d/Cirath/ak_wela/inherit/beach";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_long("This is a little spit of sand just south of the " +
             "piers of Ak Wela.  From the north comes the sounds of " +
             "large crowds of people, but here it is extremely calm, " +
             "with only the occasional bird call to interrupt the " +
             "silence.  The beach is littered with all manner of " +
             "floatsam and jetsam.\n");
    set_short("A spit of sand");

    ::create_room();
    reset_room();
}
