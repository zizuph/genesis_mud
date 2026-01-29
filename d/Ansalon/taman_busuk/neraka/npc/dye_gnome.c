/* Ashlar, 2 Jul 97 - The gnome dyer */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

void arm_me();

void
create_krynn_monster()
{
    set_name("okrish");
    add_name("dyer");
    set_title("the Dyer");
    set_race_name("gnome");
    set_adj("small");
    add_adj("spotty");
    set_long("This gnome is covered in spots of different colours. He " +
        "operates the machine with the nervous mock-confidence of " +
        "someone who pretends to know what he is doing.\n");
    set_stats(({65,80,60,80,80,55}));

    set_introduce(1);
}

void
arm_me()
{
    object arm, wep;
    seteuid(getuid(TO));
    
    arm = clone_object(NARM+"breeches");
    arm->move(TO);
    arm = clone_object(NARM+"scarf");
    arm->set_colour("red");
    arm->set_colour2("golden");
    arm->set_type("stars");
    arm->move(TO);
    /*
    wep = clone_object(NWEP+"knobkerrie");
    wep->move(TO);
    */
    command("wear all");
    command("wield all");
    
}


