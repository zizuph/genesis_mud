inherit "/d/Gondor/minas/sewer/sewer";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"

void
create_sewer() 
{
    set_extra_long("This branch of the tunnel comes to an end "
      + "here. In the roof, there is a drain leading down from "
      + "the surface.");

    add_exit(MINAS_DIR + "sewer/d3c4", "southwest", 0, 0);

    floor("southwest");
    passage("southwest");

    roof("drain");
}

void
hide_murder_weapon()
{
    object  dagger;

    if (objectp(present(MT_PW5_MURDER_WEAPON, TO)))
        return;

    dagger = clone_object(MT_PW5_MURDER_WEAPON_FILE);
    dagger->add_name(MT_PW5_MURDER_WEAPON);
    dagger->set_bloody(1);
    dagger->add_prop(OBJ_I_HIDE, 20 + random(5));
    dagger->move(TO);
}

