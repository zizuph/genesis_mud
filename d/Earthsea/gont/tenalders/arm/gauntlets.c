#pragma strict_types
/*
 * Modified by Ckrik March 2004 to add extra pen and
 *   combat attack descriptions.
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define TO_HIT 45
#define PEN 45

object gauntlets_shadow;

public void
create_armour()
{
    set_name("gauntlets");
    set_adj(({"black", "leather", "jewel-studded"}));
    add_pname("gauntletses");
    add_name(({"pair of leather gauntlets", "pair of gauntlets"}));
    add_pname(({"pairs of leather gauntlets", "pairs of gauntlets"})),
    set_short("pair of jewel-studded black leather gauntlets");
    set_pshort("pairs of jewel-studded black leather gauntlets");
    add_name("pair of jewel-studded leather gauntlets");
    add_pname("pairs of jewel-studded leather gauntlets");
    set_long("A pair of jewel-studded black "+
        "leather gauntlets. They are delicately made, as if for "+
        "a woman's hands, however, the jewel studs are placed "+
        "in such a way as to provide extra protection "+
        "and inflict greater damage during unarmed combat.\n");
    set_default_armour(40, A_HANDS, 0, this_object());
    add_prop(OBJ_I_VALUE, 3000);
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "These are the unarmed Karg priestess' " +
        "gauntlets. They are enchanted to raise the wearer's unarmed " +
        "combat skill.\n");
    add_prop(MAGIC_AM_ID_INFO, ({
        "The dazzling gauntlets have been enchanted to enhance unarmed "+
	"combat and inflict great damage.", 
	20
    }));
}

public int
is_earthsea_unarmed_enhancer()
{
    return 1;
}

public mixed
wear()
{
    object tp = this_player();
    object combat;
    object *weapons;
    mixed *data;
    int ske;

    weapons = tp->query_weapon(-1);
    switch (sizeof(weapons))
      {
      case 1:
	return "The " + weapons[0]->short() + " is in the way.\n";
      case 2:
	return "The " + weapons[0]->short() + " and " +
	  weapons[1]->short() + " are in the way.\n";
      default:
	return "Something in your hands are in the way.\n";
      case 0:
      }
    ske = tp->query_skill_extra(SS_UNARM_COMBAT);

    tp->set_skill_extra(SS_UNARM_COMBAT, ske + 20);

    combat = tp->query_combat_object();
    /* Warning: Begin ugly HACK!!!!---------------------------> */
    if (tp->query_combat_file() == 
	"/std/combat/chumlock" ||
	tp->query_combat_file() ==
	"/std/combat/chumanoid")
      {
	/* We'll also restrict to unarmed combat
	 * elsewhere by masking wield()
	 */
	data = combat->query_attack(W_RIGHT);
	combat->cb_add_attack(TO_HIT, PEN, W_BLUDGEON, 
			      data[3], W_RIGHT,
			      tp->query_skill(SS_UNARM_COMBAT) + 5);
	data = combat->query_attack(W_LEFT);
	combat->cb_add_attack(TO_HIT, PEN, W_BLUDGEON, 
			      data[3], W_LEFT,
			      tp->query_skill(SS_UNARM_COMBAT) + 5);
      }
    /* <----------------------------------------End ugly HACK!!! */
    setuid();
    seteuid(getuid());

    gauntlets_shadow = clone_object(
	"/d/Earthsea/gont/tenalders/arm/gauntlets_shadow"
    );
    gauntlets_shadow->set_gauntlets_shadow_owner(this_object());
    gauntlets_shadow->shadow_me(tp);
    
    write("You feel you could crush an ox wearing these gauntlets.\n");

    return 0;
}

public int
remove()
{
    object tp = query_worn();
    object combat;
    int ske = tp->query_skill_extra(SS_UNARM_COMBAT);

    tp->set_skill_extra(SS_UNARM_COMBAT, ske - 20);

    combat = tp->query_combat_object();
    combat->cb_configure();
    gauntlets_shadow->remove_shadow();
    
    return 0;
}
