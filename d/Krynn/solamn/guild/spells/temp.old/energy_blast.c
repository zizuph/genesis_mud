/* This spells will hit the attacked objet with a ray of raw energy.
 * We will check both the general resistans of magic in the object and
 * the resistance against electricity.
 * With wisdom and skill the spell will be easier to cast.
 * If a success it will cause a penetration of 10.
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <comb_mag.h>

#define CAST_LIMIT      20   /* The limit for this to become a success */
#define MANA_LIMIT      10   /* How much mana will be used */

/* Function name: energy_blast
 * Description:   Will cast a ray of energy on the enemy
 * Arguments:     str - string describing the enemy
 * Returns:       1/0
 */
nomask mixed
energy_blast(string str)
{
    object obj;
    int hurt;
    mixed *hitresult;
    string how;

    if (str)
        obj = present(lower_case(str), environment(this_player()));
    if (!obj)
        obj = this_player()->query_attack();
    if (!obj)
        return "Who do you want to cast this spell upon?\n";

    if (!living(obj) || obj->query_ghost())
	return "You can only kill living things.\n";

    if (this_player()->query_ghost())
	return "You are a ghost, you cannot kill anything else.\n";

    if (obj == this_player())
        return "You stop when you realize you could get hurt this way.\n";

    if (NPMATTACK(obj)) /* Check if magical attack is possible on this object.*/
        return "For some strange reason you cannot cast this spell.\n";

    if ((obj->query_average_stat() / this_player()->query_average_stat()) >
		(this_player()->query_stat(SS_DIS) / 5))
	return "You don't dare to cast the spell.\n";

    if (this_player()->query_mana() < MANA_LIMIT)
        return "You can't concetrate enough to cast this spell.\n";

    if (random(this_player()->query_skill(SS_SPELL_ATTACK) +
        this_player()->query_stat(SS_WIS)) < random(CAST_LIMIT))
    {
        write("You failed to pronounce the words right.\n");
        this_player()->add_mana(-MANA_LIMIT / 3);
        return 1;
    }

    this_player()->add_mana(-MANA_LIMIT);

    hurt = F_PENMOD(10, (this_player()->query_skill(SS_SPELL_ATTACK) +
        this_player()->query_stat(SS_INT)) / 20 + 15);
    hurt -= hurt * this_player()->query_magic_res(MAGIC_I_RES_MAGIC);
    hurt -= hurt * this_player()->query_magic_res(MAGIC_I_RES_ELECTRICITY);

    this_player()->attack_object(obj); /* This MUST be called! */

    hitresult = obj->hit_me(hurt, 0, this_player(), 0);
    how = " without effect";
    if (hitresult[0] > 0)
        how == "";
    if (hitresult[0] > 10)
        how = " hard";
    if (hitresult[0] > 20)
        how = " very hard";

    this_player()->catch_msg("You blast " + QTNAME(obj) + how + ".\n");
    obj->catch_msg(QCTNAME(this_player()) + " blasts you" + how +
        " with an energy spell.\n");

    if (obj->query_hp() <= 0)
        obj->do_die(this_player());

    return 1;
}

/* Function name:
 * Description:
 * Arguments:
 * Returns:
 */

