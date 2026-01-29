inherit "/std/monster";

#include <ss_types.h>

#include "/d/Gondor/defs.h"

string *
random_color()
{
    switch(random(4))
    {
    case 0:
        return ({ "citizen", "gondorian" });
        break;
    case 1:
        return ({ "ranger", "dunadan" });
        break;
    case 2:
        return ({ "horseman", "rohirrim" });
        break;
    case 3:
        return ({ "soldier", "gondorian" });
        break;
    }
}

void
create_monster()
{
    string *color;

    color = random_color();
    
    set_name(color + ({ "prisoner"}));
    set_race_name("human");
    add_adj("chained");
    add_adj(color[1]);
    set_long(BSN("This "+color[1]+" "+color[0]+" is a prisoner in the "
      + "dungeons of Minas Morgul. He seems to be closer to death than "
      + "to life; his eyes are dim and without any hope. He is naked, "
      + "soiled with excrements, covered with scab and many scars. "
      + "It would probably a deed of kindness to finish what the "
      + "servants of the Dark Lord began and to kill him, but within "
      + "these dungeons, kindness is a very scarce commodity."));

    default_config_npc(40);
    set_alignment(100);

    set_base_stat(SS_STR, 30);
    set_base_stat(SS_CON, 20);

}

