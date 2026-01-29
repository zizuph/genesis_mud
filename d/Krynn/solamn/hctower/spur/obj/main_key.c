// main_key
//grace sept 1994

inherit "/std/key";
inherit "/lib/keep";
#include "../local.h"

create_key() {
    ::create_key();

    set_name("keyring");
    set_adj(({"large", "iron"}));
    set_pshort("large keyrings");
    SHORT("large keyring");
    LONG("This keyring is rather heavy. It has many large iron keys "+
      "threaded onto it. It looks like a master keyring, one that "+
      "would have all of the keys to some place or something.\n");


    add_item(({"keys","iron keys","large keys","key","iron key",
	"large key"}), "The keys are all similar in weight and size, "+
      "though slightly different in shape.\n");
    add_cmd_item(({"keys","iron keys","large keys","key","iron key", 
	"large key"}), ({"remove", "remove from keyring"}), "You cannot "+
      " do that, the ring is welded closed.\n");


    set_key(LOCK_M);
}
