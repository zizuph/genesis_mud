inherit "/std/key";

#include "/d/Terel/LoD/dungeon/quest.h"

public void
create_key()
{
    ::create_key();

    set_name("key");
    add_name(DQ_CHAIN_KEY);
    set_adj(({"rusty", "iron"}));
    set_long("It is a rusty iron key.\n");
}
