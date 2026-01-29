/* 
 * scavanger hunt item
 */
  
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    seteuid(getuid());
    set_name("fish");
    add_name("_shire_dead_fish_");
    add_name("dead fish");
    set_pname("dead fishes");
    set_adj("smelly");
    set_adj("old");
    set_long("This is a smelly, old, dead fish. It is partially decomposed " + 
        "and stinks terribly. Why anyone would want to keep it is " +
        "anyone's guess.\n");

    add_item(({"bones"}),
        "Most of the bones are gray and look broken or gnawed on. They " +
        "are mostly bare except for some flesh still remaining.\n");
    add_item(({"flesh"}),
        "The flesh is rotten and disgusting looking. It hangs in pieces " +
        "from the bones and smells disgusting.\n");
    add_item(({"tail"}),
        "The tail is dried and curled up. It has a chunk missing from it.\n");
    add_item(({"head", "skull"}),
        "The head of the fish is missing. It looks like someone or " +
        "something bit it off.\n");
    add_item(({"fins"}),
        "The fins are dried and curly.\n");

    add_prop(OBJ_I_VALUE, 100);
}
