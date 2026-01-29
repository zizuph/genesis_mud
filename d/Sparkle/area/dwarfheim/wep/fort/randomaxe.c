#pragma save_binary
#pragma strict-types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("axe");

    set_wt(W_AXE);

    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1000);
}

void
configaxe(int l)
{
    string adj,lo;

    switch(l)
    {
    case 0: adj = "tiny";
        lo = "It is a rather tiny axe, not very good for combat.\n";
        break;
    case 1: adj = "shimmering";
        lo = "The axe is polished very carefully.\n";
        break;
    case 2: adj = "sturdy";
        lo = "This axe has a sturdy handle, made of oak.\n";
        break;
    case 3: adj = "old";
        lo = "It's an old axe. It is still very good, though.\n";
        break;
    case 4: adj = "sharp";
        lo = "This is a rather sharp axe, well suited for killing.\n";
        break;
    case 5: adj = "battle";
        lo = "This axe has been customized for slaughtering orcs and goblins.\n";

    }

    set_long(lo);
    set_short(adj+" axe");
    set_adj(adj);

    set_hit(l*7);
    set_pen(l*7);
}

