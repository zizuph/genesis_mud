/*
 * sheep.c
 *
 * Used in carisca/f3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

void
create_creature()
{
    set_name("sheep");
    set_race_name("sheep");
    set_short("white sheep");
    set_long("This is a normal, fluffy sheep.\n");
  
    set_gender(G_NEUTER);

    default_config_mobile(15);

    set_attack_unarmed(0, 10, 5, W_IMPALE, 70, "teeth");
    set_attack_unarmed(1, 10, 5, W_BLUDGEON, 30, "legs");

    set_hitloc_unarmed(0, 1, 15, "head");
    set_hitloc_unarmed(1, 1, 55, "fluffy body");
    set_hitloc_unarmed(2, 1, 30, "little legs");

    remove_prop(OBJ_I_NO_GET);
}

int
query_auto_load()
{
    return 0; //FIXA, behovs for jabberwock?
}
