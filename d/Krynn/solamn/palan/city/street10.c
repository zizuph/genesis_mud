/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

object ken;

string
query_to_jail()
{
  return "northeast";
}

void
reset_palan_room()
{
    if (ken)
      return;
    ken = clone_object(PLAINS_LIV + "kender");
    ken->move(TO);
}

void
create_palan_room()
{

    set_short("Southwestern city");
    set_long(BS("This long straight street leads from "
        +   "the Central Plaza to the southwestern "
        +    "areas of Palanthas. The street appears "
        +    "cleaned and the houses that line the "
        +    "street look neat and tidy, but seem a "
        +    "little bit small. There are flowers in "
        +    "the windows and all doors and windows "
        +    "are closed.",SL));

    add_exit(ROOM + "street8","southwest",0,1);
    add_exit(ROOM + "plaza","northeast",0,1);

    add_item(({"windows","window","door","doors","house",
             "houses","flowers"}),
             "It looks like it's very ordinary.\n");
    reset_room();
}
