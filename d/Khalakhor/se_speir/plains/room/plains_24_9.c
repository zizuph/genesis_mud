/**********************************************************************
 * - Added a laying function so players can lay upon grass or some  - *
 * - other player.                                                  - *
 * - Modified by Damaris@Genesis 02/2005                            - *
 **********************************************************************/
#include "plains.h"
#include <macros.h>


inherit PLAINBASE;
inherit SR_DIR+"lib/branchcmd";
#include "laying.c"

public void reset_room() { ::reset_room(); set_numbranches(2); }

public void
create_khalakhor_room()
{
    proxim = (["river"  : ({0, "east"}),
               "harbour": ({2, "southwest"})]);
    create_plain();
    set_branchnum(5); // Hasthorn branches avail. here
    set_numbranches(2);
    
    add_my_desc(lay_desc, this_object());
    
    add_item(({"river","bank"}),
       "The river, called the Sora cuts across the plains to the east, " +
       "running more or less in a southwesterly direction. There is a "+
       "small shrub with long thorns growing along the river's bank.\n");

    add_item(({"shrub","thorns","hawthorn"}),
       "The small shrub is growing in the moist bank of the river "+
       "just to the east. It has very long thorns growing out of it.\n");

    add_exit(PLAINS + "plains_23_10", "southwest");
    add_exit(PLAINS + "plains_23_9", "west");
}

public void
setup_plains_herbs()
{
    herbs = ({"/d/Krynn/common/herbs/hawthorn"});
    set_up_herbs(herbs, ({"grass","here","shrub","bank"}),3);
}

public void
init()
{
   ::init();
   init_lay();   
   add_action(&break_branch(),"break");

}
