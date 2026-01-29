inherit "/std/drink";
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include QUESTH
#include "/sys/stdproperties.h"

create_drink() {
    set_soft_amount(100);
    set_alco_amount(5);
    set_name("beer");
    add_name("lazy_beer");
    add_name("bottle");
    set_adj("dusty");
    set_long("This beer looks old...not really fit for drinking.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(HEAP_S_UNIQUE_ID, "lazy_beer");
    add_prop(OBJ_M_NO_GET, "@@prop");
}

prop()
{
    seteuid(getuid());
    if (environment()->query_name() == "table")
    {
    	if (QUEST_MASTER->query_quest_number(SMALLADV, TP) > 1)
            return "You have already advanced past this quest.\n";

    	if (QUEST_MASTER->query_quest_number(SMALLADV, TP) < 1)
            return "You must solve the apple quest before you can solve " +
            	"this one.\n";
    }

    return 0;
}
