/*
 * h_holy_w_sprinkler.c
 *
 * Used in npc/van_helsing.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Holy water sprinkler, another name for a morning star */
/* coded in this form 93-08-30 by Calonderiel and Arren */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    /* Set name, short description and long description */
    set_name("holy water sprinkler");
    add_name(({"club", "sprinkler"}));
    set_short("holy water sprinkler");
    set_pshort("holy water sprinklers");
    set_long("This weapon has three parts. A handle attached to a chain, " +
             "and the chain ends in a heavy spiked ball. " +
             "All parts are made of a silvery metal.\n");

    /* Better add an adjective or two */
    set_adj("metal");
    add_adj("silvery");

    set_default_weapon(29, 25, W_CLUB, W_BLUDGEON, W_RIGHT, 0);
    add_prop(MAGIC_AM_MAGIC, ({25, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"The holy water sprinkler seems to " +
                                 "be magical.\n", 1,
                                 "This holy water sprinkler is suitable " +
                                 "when fighting vampires.\n", 15}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_WEIGHT, 8800);
    add_prop(OBJ_I_VOLUME, 1500);
}

int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
        int dam)
{
    if (enemy->query_guild_name_occ() == "Vampyr guild")
        enemy->hit_me(99, MAGIC_DT, query_wielded(), -1);
    return 0;
}
