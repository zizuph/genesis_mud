inherit "/d/Gondor/elessar/lib/potion";
#include "/d/Gondor/defs.h"
#include "/sys/herb.h"

create_potion()
{
  ::create_potion();
  set_name("flask");
  set_short("clear brown potion");
  set_adj("brown");
  set_adj("clear");
  set_id_diff(5);
  set_unid_long("This flask contains a clear brown liquid; some potion unknown\n"+
    "to you. Perhaps tasting or smelling will give you a better idea?\n");
  set_id_long("This clear brown liquid is a potion of healing, made from\n"+
    "Gondorian herbs.\n");
  set_potion_taste("You take a tiny sip of the potion just to see how it tastes.\n"+
    "It tastes quite healthy.\n");
  set_potion_smell("You take a whiff of air from the potion. Somehow, it smells\n"+
    "like vegetables.\n");
  set_magic_res(30);
  set_effect(HERB_HEALING,"hp",40);
}
