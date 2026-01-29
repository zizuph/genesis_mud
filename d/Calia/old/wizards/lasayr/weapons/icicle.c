/* Created by Lasayr 8/7/98 */
/* icicle.c                 */
/* Comments:                */
/* Todo:                    */


#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Calia/domain.h"

#define WEAPON_HIT 28
#define WEAPON_PEN 35

void 
create_weapon()
{

    set_name("icicle");
    add_name("knife");
    set_adj(({"long", "icy", "cold", "frost", "crystal"}));
    set_short("long crystal icicle");
    set_long("At first glance, you seem to hold "+
    "nothing but a long piece of ice, the cold "+
    "touch of its length uncomfortable to hold. "+
    "A seemingly melted grip reveals a handle "+
    "for the shaft of the frost-covered "+
    "crystalline weapon. Holding no edge, it "+
    "tapers to a single narrow point used to "+
    "possibly stab or pierce. Little else is "+
    "shown other than the fact it was broken "+
    "from a larger piece.\n");

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);

    set_wt(W_KNIFE); 
    set_dt(W_IMPALE); 

    set_hands(W_ANYH);
    set_wf(this_object());

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON
            (WEAPON_HIT, WEAPON_PEN) - (90+random(21)) * 5);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 15, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({"An aura of visible "+
        "enchantment surfaces in the long piece of "+
        "ice.\n", 1,
	"Enchanted for its use, the icy hand of "+
        "death seems to radiate from the deadly "+
        "point.\n", 25,
	"Obviously crafted by a master of the "+
        "arts, the crystal relies on the knowledge "+
        " of its wielder.\n", 66}));
    add_prop(OBJ_S_WIZINFO, "This weapon is enchanted "+
        "with cold and has a special attack that appears "+
        "based on the spellcraft and INT of the wielder.\n");
}

int try_hit(object enemy)
{
    int skill, stat, skill_e, stat_e, pen, perf, pdam, res;
    mixed *hitresult;
    object me;
    string text, ptext;

    me = query_wielded();
    skill = me->query_skill(SS_SPELLCRAFT);
    stat = me->query_stat(SS_INT);
    skill_e = enemy->query_skill(SS_SPELLCRAFT);
    stat_e = enemy->query_stat(SS_INT);

    res = enemy->query_magic_res(MAGIC_I_RES_COLD);
    pdam = (pdam - res) + 100;

    if ((random(100) < (skill/2)) && 
      (random(skill+stat) > random(skill_e+stat_e)))
    {
	pen = F_PENMOD(40+random(stat/4), skill);
	hitresult = enemy->hit_me(pen, W_IMPALE, me, -1);
	perf = hitresult[2] * 100 / pen;

	ptext = "just misses";
	if (perf > 15)
	    ptext = "scratches";
	if (perf > 30)
	    ptext = "nicks";
	if (perf > 45)
	    ptext = "pierces";
	if (perf > 60)
	    ptext = "deeply pierces";
	if (perf > 75)
	    ptext = "impales";
	if (perf > 90)
	    ptext = "skewers";

	me->catch_msg("A cold numbness pervades the "+
        "length of your arm as the icicle " +ptext+ " "+
        "" +QTNAME(enemy)+ ".\n");

	enemy->catch_msg("You feel a wave of cold "+
        "numbness as " +QTNAME(me)+ " " +ptext+ " you "+
        "with the deadly icicle. Frost lingers in the "+
        "air.\n");

	me->tell_watcher("Your eye catches a shadow of "+
        "frost in the air as " +QTNAME(me)+ " "+
        "delicately handles the cold icicle. A chill "+
        "passes as it "+ptext+" "+QTNAME(enemy)+ ".\n");

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(me);
	    return 0;
	}
    }
    return 1;

}
