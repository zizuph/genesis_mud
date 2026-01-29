/*
 * death.c
 *
 * Mascarvin herself, need I say more?
 *
 *   Lucius, May 2007
 *
 * Based off original death by:
 *  Khail, Nov.15/96
 *  Mrpr 901120
 *  Tintin 911031
 *  Nick 920211
 */
#pragma strict_types
#include <stdproperties.h>

inherit "/std/monster";


public void
create_monster(void)
{
    set_gender(1);
    set_name("mascarvin");
    add_name(({"woman","female"}));
    set_adj(({"tall","pale"}));
    set_race_name("idrys");
    set_short("tall, pale womanly figure");
    set_long("This tall, pale figure is the Idrys named Mascarvin. "+
	"However you look, you find that her features are always "+
	"slightly blurred, seeming to yield a solid yet indistinct "+
	"impression to your irises. The figures only concession to "+
	"clothing is that of a diaphanous black robe, parted open "+
	"down the front, which does little to obscure the plump "+
	"paleness of her breasts nor hide the black nest at the "+
	"apex of her thighs. Though her face seems hidden from your "+
	"vision, her midnight eyes feel to be boring into you, "+
	"laying out your every tribulation to her purview.\n");

    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(OBJ_M_NO_ATTACK, "Attack Mascarvin? Not likely.\n");
    default_config_npc(400);
}

public varargs string
show_sublocs(object foo, mixed bar)
{
    return "";
}
