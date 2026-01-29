// Akram
// creator(s): Cirion
// last update: Created May 23rd, 1997
#pragma strict_types
inherit "/d/Avenir/inherit/monster";

#include "defs.h"

#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>


public void
create_monster(void)
{
    ::create_monster();

    set_name("akram");
    set_adj(({"tall"}));
    set_title("the Union Master");
    set_race_name("elf");

    set_long("Shadows play about this tall figure.\n");

    set_alignment(0);
    set_stats(({200,200,200,200,200,200}));

    add_prop(CONT_I_HEIGHT, 252);
    add_prop(CONT_I_WEIGHT, 56000);

    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_UNDEAD, 100);

    equip(({ UNION + "obj/cape" , UNION + "obj/shirt",
	     UNION + "obj/boots", UNION + "obj/band_c",
	     UNION + "obj/knife", UNION + "obj/slash" }));
}

public string
race_sound(void)
{
   return "speaks";
}
