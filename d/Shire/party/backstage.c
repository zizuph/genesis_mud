#include "defs.h"

inherit PARTY_BASE;


void
create_party_room()
{
    set_short("Backstage");
    set_long("Around you lies the paraphanalea of the backstage area of "+
      "the party ampitheatre stage. Above you rises a high timber roof, "+
      "safely shingled from the elements outside.\nBetween you and the "+
      "stage is a solid timber wall, and behind it several false walls. "+
      "From around the sides of the back wall hang heavy black curtains, "+
      "shielding you from the noise and light from the stage. A few wall-"+
      "mounted candleabra provide dim light, feebly assisted by overhead "+
      "shuttered windows.\n");

    add_exit(PARTY_DIR+"stage","stage");
}

