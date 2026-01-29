inherit "/std/shadow";
#include <formulas.h>
#include <ss_types.h>

int hp = shadow_who->query_hp();

public int
query_hp()
{
    int new_hp = shadow_who->query_hp();

    /* This doubles the rate of healing. */
    hp = new_hp + (new_hp - hp);

    shadow_who->set_hp(hp);
    return hp;
}
