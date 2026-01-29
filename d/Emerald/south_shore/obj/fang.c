/*  /d/Emerald/south_shore/obj/fang.c
 *
 *  Magical fang Demerga occasionally drops.
 *  When wielded, it gives the player a buff in 
 *  knife and spellcraft skills.
 *
 *  Created 12.29.2021 by Velith
 */

inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
#include "/d/Emerald/sys/macros.h";
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("fang");
    set_pname("fangs");
    add_name("dagger");
    add_name("knife");
    add_name("saetira");
    set_short("pearlescent serrated fang");
    add_adj( ({ "serrated", "pearlescent" }) );
    set_long("This pearlescent fang is certainly a lethal weapon. "
             + "Legends of old describe its name as Saetira, the Stinging Pearl. "
             + "As the light dances over the iridescent blade, you notice fine "
             + "serrations that could effortlessly rip through flesh. The point "
             + "of this fang has been sharpened with deadly precision, allowing "
             + "it to puncture even the toughest of hides. The smooth jewel-toned "
             + "hilt rests easily in your hand, as if it were an extension of "
             + "your own arm.\n");
    set_hit(40);
    set_pen(35);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_wf(TO);
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME,  500);
    set_hands(W_LEFT);
    set_magic_spellpower(48);
    set_spellpower_elements(({ SS_ELEMENT_WATER }));
    
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This weapon is a 40/35 knife."
             + "Players can wield it in the left hand. It gives the "
             + "wielder fifteen levels of knife and spellcraft skill. There "
             + "are no requirements to wield this knife. This weapon"
             + "is dropped by Demerga.\n");
    add_prop(MAGIC_AM_ID_INFO, ({"This is Saetira, the lethal fang " 
             + "of the great serpent Demerga.\n", 10,"Through centuries "
             + "of evolution, this particular feature of the serpentine "
             + "race has been shaped and honed into the dagger you "
             + "possess.\n", 20, "This fang increases the wielder's "
             + "knife and spellcraft skills.\n", 30 }) );
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(40, 35));

}
/* Function name : Wield
 * Description : Sets wielder to the person wielding the knife.
 *               Gives the wielder the skill boosts.
 * Returns : Null.
 */
mixed
wield(object what)
{
    object tp = this_player();
    tp->set_skill_extra(SS_SPELLCRAFT,
                                   this_player()->query_skill_extra(SS_SPELLCRAFT) + 10);
    tp->set_skill_extra(SS_WEP_KNIFE,
                                   this_player()->query_skill_extra(SS_WEP_KNIFE) + 10);

    tp->catch_msg("A strange thrill runs through you.\n");
}

/* Function name : Unwield
 * Description : Uses the do_normal function which resets the knife and
 *     spellcraft skills back to normal. Unsets the person wielding the
 *     knife as wielder.
 * Returns : Null.
 */
mixed
unwield(object what)
{
    object tp = this_player();
    tp->set_skill_extra(SS_SPELLCRAFT,
                                   this_player()->query_skill_extra(SS_SPELLCRAFT) - 10);
    tp->set_skill_extra(SS_WEP_KNIFE,
                                   this_player()->query_skill_extra(SS_WEP_KNIFE) - 10);

    tp->catch_msg("You feel oddly drained as you loosen your grip on the fang.\n");
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string
stat_object()
{
    return ::stat_object() + stat_object_spellpower();
}
