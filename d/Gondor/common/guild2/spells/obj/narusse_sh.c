/*
 *	/d/Gondor/common/guild2/spells/obj/narusse_sh.c
 *
 *	The shadow for the Morgul spell narusse (Flame Blade)
 *
 *	Copyright (c) 1996 by Christian Markus
*
*  Modification Log:
*   Jan 10 2000  Morbeche -  Commented out log writings used
*                            for debugging
 */
#pragma strict_types

inherit "/std/shadow.c";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

#define HE(x)		(x)->query_pronoun()
#define HIS(x)		(x)->query_possessive()
#define HIM(x)		(x)->query_objective()

#define MAX_HIT		60
#define BASE_PEN	25
#define EXTRA_PEN	16
#define FLAME_PEN	(BASE_PEN + random(EXTRA_PEN))
#define EXTRA_SKILL	30
#define RANGER_M_NOT_DISARM	"_ranger_m_not_disarm"

#define DEBUG		0

//	Prototypes
void   flicker();

// 	Global variables
static int     Duration,
               Flicker,
               MagicWeapon,
               OldToHit;
static mixed   MagicMagic,
               MagicInfo;
static object  Mage,
               OldWieldFunc;
static string  OldShort;
static mixed   FlickMess = ({ 
       ({ "The searing-hot flames engulfing ", " flicker hungrily.\n" }),
       ({ "The flames dance menacingly across the blade of ", ".\n" }),
       ({ "The flames hiss softly as they burn on ", ".\n" }),
       ({ "The flames on ", " flare briefly.\n" }),
       ({ "The flames on ", " cast a dull radiance, lengthening "
        + "shadows rather than truly illuminating.\n" })
						});

public mixed
unwield(object ob)
{
    mixed rval = 0;

    if (objectp(OldWieldFunc))
        rval = OldWieldFunc->unwield(ob);

    if (stringp(rval) || (intp(rval) && (rval < 0)))
        return rval;

/*
    write_file("/d/Gondor/log/narusse",
        Mage->query_name() + " unwielded. " + ctime(time()) + ".\n");
*/

     set_alarm(0.0, 0.0, remove_shadow);

    /* We return 1 if the Duration == 0, meaning that the spell caused us
     * to be unwielded. Else, we return 0, to have the normal messages.
     */
    return (Duration == 0);
}

public void
remove_shadow()
{
    int     wt;
    object  env;

    remove_alarm(Duration);
    Duration = 0;

/*
    write_file("/d/Gondor/log/narusse", "Remove_shadow called, "
      + "variable Mage points to "
      + (objectp(Mage) ? Mage->query_name() : "nobody") + ". " + ctime(time()) + ".\n");
*/

    if (objectp(Mage))
    {
        env = ENV(Mage);
    }
    else if (objectp(env = ENV(shadow_who)))
    {
        while (!env->query_prop(ROOM_I_IS))
            env = ENV(env);
    }
    else
    {
        // if we don't have an environment, then let's just go away
        shadow_who->remove_object(); 
        ::remove_shadow();
    }

    if (!objectp(Mage))
    {
        tell_room(env, "The searing-hot flames engulfing the "
          + shadow_who->short() + " quietly flicker out of "
          + "existence.\n");
    }
    else
    {
        Mage->remove_prop(RANGER_M_NOT_DISARM);
        tell_room(env, "The searing-hot flames engulfing " + QTNAME(Mage)
          + "'s " + shadow_who->short() + " quietly flicker out of "
          + "existence as " + HE(Mage) + " releases " + HIS(Mage)
          + " grip upon it.\n", Mage);
        Mage->catch_msg("The searing-hot flames engulfing your "
          + shadow_who->short() + " quietly flicker out of existence "
          + "as you release your grip upon it.\n");
        wt = shadow_who->query_wt();
        Mage->set_skill_extra(SS_WEP_FIRST + wt,
            Mage->query_skill_extra(SS_WEP_FIRST + wt) - EXTRA_SKILL);
/*
        write_file("/d/Gondor/log/narusse",
          Mage->query_name() + " got temp weapon skill " + wt
          + " reduced to " + Mage->query_skill_extra(SS_WEP_FIRST + wt)
          + ". Skill now " + Mage->query_skill(SS_WEP_FIRST + wt)
           + ". " + ctime(time()) + ".\n");
*/
    }

    remove_alarm(Flicker);

    if (MagicWeapon)
    {
        tell_room(env, "When the flames die out, you notice that the "
          + shadow_who->short() + " looks scorched.\n");
        shadow_who->set_corroded(shadow_who->query_corroded() + 1);
        shadow_who->remove_adj("flaming");
        shadow_who->remove_prop(OBJ_M_NO_DROP);
        shadow_who->set_short(OldShort);
        if (objectp(OldWieldFunc))
            shadow_who->set_wf(OldWieldFunc);
        else
            shadow_who->set_wf(0);
        shadow_who->add_prop(MAGIC_AM_MAGIC, MagicMagic);
        shadow_who->add_prop(MAGIC_AM_ID_INFO, MagicInfo);
        shadow_who->set_hit(OldToHit);
        Mage->query_combat_object()->cb_update_weapon(shadow_who);
        // should the weapon be unwielded?
        // According to the message above, this has to be done.
        shadow_who->unwield_me();
        unwield(shadow_who);
    }
    else
    {
        tell_room(env, "When the flames die out, the " + shadow_who->short()
          + " crumbles to ashes.\n");
        shadow_who->unwield_me();
        unwield(shadow_who);
        shadow_who->remove_object();
        FIX_EUID
        clone_object(MORGUL_S_ASHES)->move(env);
    }

/*
    write_file("/d/Gondor/log/narusse",
        "Mage var set to 0. " + ctime(time()) + "\n");
*/
    Mage = 0;

    ::remove_shadow();
}

public int
enchant_weapon(int duration)
{
    int     wt;
    object  env;

    if (!objectp(Mage) || (Duration && sizeof(get_alarm(Duration))))
    {
        ::remove_shadow();
        return 0;
    }

    env = ENV(Mage);
    tell_room(env, QCTNAME(Mage) + "'s " + shadow_who->short()
      + " is suddenly engulfed in scorching flames.\n", Mage);
    Mage->catch_msg("Your " + shadow_who->short() + " is suddenly "
      + "engulfed in scorching flames.\n", Mage);

    wt = shadow_who->query_wt();
    Mage->set_skill_extra(SS_WEP_FIRST + wt,
        Mage->query_skill_extra(SS_WEP_FIRST + wt) + EXTRA_SKILL);
/*
    write_file("/d/Gondor/log/narusse",
        Mage->query_name() + " had weapon skill " + wt
      + " increased to " + Mage->query_skill(SS_WEP_FIRST + wt)
      + " by " + Mage->query_skill_extra(SS_WEP_FIRST + wt) + " extra. "
     + ctime(time()) + ".\n");
*/

    Duration = set_alarm(itof(duration), 0.0, remove_shadow);
    Flicker = set_alarm(20.0 + rnd() * 20.0, 0.0, flicker);
    OldWieldFunc = shadow_who->query_wf();
    shadow_who->set_wf(TO);
    OldShort = shadow_who->short();
    shadow_who->set_adj("flaming");

    // props for magical weapons:
    MagicWeapon = shadow_who->query_prop(OBJ_I_IS_MAGIC_WEAPON);
    shadow_who->add_prop(OBJ_I_IS_MAGIC_WEAPON);
    MagicMagic = shadow_who->query_prop(MAGIC_AM_MAGIC);
    shadow_who->add_prop(MAGIC_AM_MAGIC, ({ "enchantment", 
        Mage->query_skill(SS_FORM_ENCHANTMENT) }) );
    MagicInfo = shadow_who->query_prop(MAGIC_AM_ID_INFO);
    shadow_who->add_prop(MAGIC_AM_ID_INFO, ({
        1, "The Fires of Orodruin have been summoned upon this blade.\n",
       10, "While the enchantment lasts, the wielder of this blade "
           + "will be more skilled using this blade in combat.\n",
       25, "This blade will hit its target with magical accuracy.\n", }) );
    shadow_who->add_prop(OBJ_M_NO_DROP, "Unwield the "
      + shadow_who->short() + " first!\n");
    // prevent ranger disarm
    Mage->add_prop(RANGER_M_NOT_DISARM,
        "The " + shadow_who->short() + " wielded by "
      + QTNAME(Mage) + " is magically enchanted. It is impossible "
      + "to disarm the wielder!\n");

    // tohit
    OldToHit = shadow_who->query_hit();
    shadow_who->set_hit(OldToHit + (MAX_HIT - OldToHit) / 2);
     Mage->query_combat_object()->cb_update_weapon(shadow_who);

    shadow_who->set_short("flaming " + shadow_who->short());

    return 1;
}

public void
set_mage(object mage)
{
    Mage = mage;
}

public int
query_flame_blade()
{
    return 1;
}

string
long()
{
    return (shadow_who->long() + "It is engulfed in searing-hot flames.\n");
}

public void
flicker()
{
    int     i;

    if (!objectp(Mage))
    {
        remove_shadow();
        return;
    }

    Flicker = set_alarm(30.0 + rnd() * 60.0, 0.0, flicker);

    i = random(sizeof(FlickMess));

    Mage->catch_msg(FlickMess[i][0] + "your "
      + shadow_who->short() + FlickMess[i][1]);
 	tell_room(ENV(Mage), FlickMess[i][0] + QTNAME(Mage)
	  + "'s " + shadow_who->short() + FlickMess[i][1],
		Mage);
}

public void
burn_enemy(object enemy, string hit_loc = "body")
{
    string  flame,
            how;
    int     dam = 0,
            pen,
            res;
    mixed   rval;

    if (!objectp(Mage))
    {
        remove_shadow();
        return;
    }

    if (!objectp(enemy))
        return;

    pen = FLAME_PEN;
    res = enemy->query_magic_res(MAGIC_I_RES_FIRE);
    pen -= pen * res / 100;

    rval = enemy->hit_me(F_PENMOD(pen, Mage->query_skill(SS_ELEMENT_FIRE)),
        MAGIC_DT, Mage, -1);
#if DEBUG
    write(implode(rval, ", ") + ".\n");
#endif

    if (pointerp(rval))
        dam = rval[0];

    switch (pen)
    {
    case  0..8:
        flame = "lick";
        break;
    case  9..12:
        flame = "singe";
        break;
    case 13..16:
        flame = "scorch";
        break;
	case 17..20:
		flame = "burn";
		break;
    default:
        flame = "wither";
        break;
    }

    switch (dam)
    {
    case  -1..0:
        how = "unharmed";
        break;
    case   1..5:
        how = "slightly hurt";
        break;
    case  6..10:
        how = "somewhat hurt";
        break;
    case 11..20:
        how = "hurt";
        break;
    case 21..30:
        how = "rather hurt";
        break;
    case 31..50:
        how = "very hurt";
        break;
    default:
        how = "badly hurt";
        break;
    }

    Mage->catch_msg("The searing-hot flames surrounding your "
      + shadow_who->short() + " " + flame + " the " + hit_loc
      + " of " +QTNAME(enemy) + ".\n" + CAP(HE(enemy))
      + " looks " + how + " by the flames.\n");

    enemy->catch_msg("The searing-hot flames surrounding "
      + QTNAME(Mage) + "'s " + shadow_who->short() + " " + flame
      + " your " + hit_loc + ".\n"
      + "You are " + how + " by the flames.\n");

    Mage->tell_watcher("The searing-hot flames surrounding "
      + QTNAME(Mage) + "'s " + shadow_who->short() + " " + flame
      + " the " + hit_loc + " of " + QTNAME(enemy) + ".\n"
      + CAP(HE(enemy)) + " looks " + how + " by the flames.\n", enemy);

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(Mage);
    }
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    int     rval = shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

#if DEBUG
write("did_hit: "+aid + ", "+hdesc+", "+phurt+", "+file_name(enemy)+", "+dt+", "+phit+", "+dam+"\n");
#endif
    if (!objectp(enemy))
        return (rval);
    if (phurt > 0)
        set_alarm(0.0, 0.0, &burn_enemy(enemy, hdesc));
    return (rval);
}

public string
stat_object()
{
    string  str = shadow_who->stat_object();

    str += "This weapon has been enchanted by a spell of the Society "
        +  "of Morgul Mages, engulfing it in flames, inflicting extra "
        +  "damage upon successful hits.\n"
        +  "Remaining duration: " + ftoa(get_alarm(Duration)[2])
        +  " seconds.\n";
    return str;
}

/*
 * Function name: dispel_magic
 * Description:   Function called by a dispel spell
 * Argument:      magic - How strong the dispel is
 * Returns:       0 - No dispelling, 1 - Object dispelled
 */
public int
dispel_magic(int magic)
{
    if (magic < shadow_who->query_magic_res(MAGIC_I_RES_MAGIC))
        return 0;

    remove_shadow();
    return 1;
}

mixed query_flick_message() { return FlickMess; }

