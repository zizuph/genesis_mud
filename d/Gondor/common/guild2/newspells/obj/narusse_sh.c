/*
 *    /d/Gondor/common/guild2/newspells/obj/narusse_sh.c
 *
 *    The shadow for the Morgul spell narusse (Flame Blade)
 *    Note: It's a weapon's shadow so it masks functions in a weapon, not
 *    in a mage.
 *
 *    Copyright (c) 1996 by Christian Markus
 *
 *  Modification Log:
 *   Jan 10 2000  Morbeche -  Commented out log writings used
 *                            for debugging
 *   May 24 2001  Chmee    -  Completely rewritten.
 */
#pragma strict_types

#include "../spells.h"

inherit "/std/shadow";
inherit SPELL_OBJECT;

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>

#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "morgul_corpse.h"

#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()
#define HIM(x)  (x)->query_objective()
#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())

#define MAX_HIT               60
#define BASE_PEN              25
#define EXTRA_PEN             16
#define FLAME_PEN             (BASE_PEN + random(EXTRA_PEN))
#define WEAPON_SKILL_capitalize     100

#define EXTRA_SKILL_BASE      25
                                /*2.0 spellcraft = 1.0 weapon skill       */
#define EXCHANGE_FACTOR      2.0
                                /*It's 25* 2.0                            */
#define SPELLCRAFT_DRAIN_BASE (ftoi( itof( EXTRA_SKILL_BASE )* \
                                  EXCHANGE_FACTOR ))
#define MIN_SPELLCRAFT_LEFT   20

#define RANGER_M_NOT_DISARM   "_ranger_m_not_disarm"
#define WEAPONS_O_OWNER       "_weapons_o_owner"
#define SCABBARD          "d/Gondor/ithilien/emyn-arnen/obj/scabbard.c"
#define NUT_CRACKER       "d/Gondor/common/guild2/newspells/obj/nut_cracker"

#define JUST_UNWIELDED 3
#define IN_SCABBARD    2
#define FROM_HAND      1
#define ELSEWHERE      0


//     Global variables
static int Duration, Flicker, MagicWeapon, OldToHit, Brawl_proof = 0;
static int Spellcraft_drain, Wep_skill_gain, Weapon_type, Two_handed_loss;
static mixed   MagicMagic, MagicInfo;
static object  OldWieldFunc;
static string  OldShort;
static mixed   FlickMess = ({ 
  ({ "The searing-hot flames engulfing ", " flicker hungrily.\n" }),
  ({ "The flames dance menacingly across ", ".\n" }),
  ({ "The flames hiss softly as they burn on ", ".\n" }),
  ({ "The flames on ", " flare briefly.\n" }),
  ({ "The flames on ", " cast a dull radiance, lengthening "
    + "shadows rather than truly illuminating.\n" })
});

public void flicker();
public void burn_enemy( object enemy, string hit_loc = "body" );
mixed query_flick_message();
void calculate_skill_gain();
void enhance_mage();
void degrade_mage();
private nomask int f_narusse_duration( int var1, int var2 );

/*
 * Description: Many things are done in this function and the succession
 * of command execution is crucial here. I tried to do it in a planned way,
 * then I had to modify it a bit while adding new things and now every-
 * thing is working. So be carefull while adding new things.
 */
public int setup_spell_effect()
{
 int narusse_duration, _spellcraft_weight, Ti1;
 object  env;

    set_spell_effect_desc( "narusse flame weapon" );

    if (!::setup_spell_effect())
    {
        remove_shadow();
        return 0;
    }
                                /*Let us shadow the weapon.               */
    if (!shadow_me( spell_target ))
    {
        remove_shadow();
        return 0;
    }
    env = environment( spell_caster );
    tell_room( env, QCPNAME( spell_caster )+ " "+ shadow_who->short()+
        " is suddenly engulfed in scorching flames.\n", spell_caster );
    spell_caster->catch_tell( "Your "+ spell_target->short()+
        " is suddenly engulfed in scorching flames.\n", spell_caster );

    Weapon_type = SS_WEP_FIRST+ shadow_who->query_wt();
    calculate_skill_gain();
    spell_caster->add_prop( "_live_i_narusse_enhanced", 1 );

    narusse_duration = f_narusse_duration( spell_power,
        spell_caster->query_stat( SS_OCCUP ));
    Duration = set_alarm( itof( narusse_duration ), 0.0,
        &dispel_spell_effect( spell_caster ) );
/*
 * I have accumulated enough statistics and find the further logging
 * useless.
    SPELL_INHERIT->log_spell( "narusse", NAME( spell_caster )+ 
        "  Flame weapon cast successfully on "+ file_name( shadow_who )+
        " for "+ narusse_duration+ "[s]. Weapon skill raised by "+
        Wep_skill_gain+ ", spellcraft decreased by "+ Spellcraft_drain+
        "." );
 */
    Flicker = set_alarm( 20.0 + rnd() * 20.0, 0.0, flicker );

                                /*Let us redefine the unwield function
                                 *here.                                   */
    OldWieldFunc = shadow_who->query_wf();
    shadow_who->set_wf( this_object() );
    OldToHit = shadow_who->query_hit();
    shadow_who->set_hit( OldToHit + (MAX_HIT - OldToHit) / 2 );

    OldShort = shadow_who->short();
    shadow_who->set_adj( "flaming" );
    shadow_who->add_prop( WEAPONS_O_OWNER, spell_caster );

    // props for magical weapons:
    MagicWeapon = shadow_who->query_prop( OBJ_I_IS_MAGIC_WEAPON );
    shadow_who->add_prop( OBJ_I_IS_MAGIC_WEAPON );
    MagicMagic = shadow_who->query_prop( MAGIC_AM_MAGIC );
    shadow_who->add_prop( MAGIC_AM_MAGIC, ({ spell_caster->query_skill(
        SS_FORM_ENCHANTMENT ), "enchantment" }) );
    MagicInfo = shadow_who->query_prop( MAGIC_AM_ID_INFO );
    shadow_who->add_prop( MAGIC_AM_ID_INFO,
        ({
        1, "The Fires of Orodruin have been summoned upon this weapon.\n",
        10, "While the enchantment lasts, the wielder of this weapon "
        + "will be more skilled using this weapon in combat.\n",
        15, "The wielder however will sacrifice some of his or her"
        + "spellcraft skill in exchange.\n",
        25, "This weapon will hit its target with magical accuracy.\n",
        }) );

                                /*A weapon may gain protection from ranger's
                                 *brawl. The chance is not very big though
                                 *for an experienced mage (SS_OCCUP > 200)
                                 *who didn't lose too much spellcraft for
                                 *narusse may exceed 50%.                 */

    _spellcraft_weight = 20* (spell_caster->query_skill( SS_SPELLCRAFT )-
        Spellcraft_drain)/ 9;

    if (spell_caster->resolve_task( TASK_FORMIDABLE, ({ SKILL_WEIGHT, 100,
       TS_OCC, SKILL_WEIGHT, _spellcraft_weight, SS_SPELLCRAFT })) > 0)
    {
        Brawl_proof = 1;
    }

    shadow_who->set_short( "flaming " + shadow_who->short() );
    enhance_mage();

    spell_caster->query_combat_object()->cb_update_weapon( shadow_who );
    return 1;
}

/*
 * Function name: calculate_skill_gain
 * Description  : Calculate the loss of spelcraft and gain of skill of
 *                the spell_caster.
 */
void calculate_skill_gain()
{
 int Spellcraft;

    Two_handed_loss = min( spell_caster->query_skill( SS_2H_COMBAT ),
        spell_caster->query_skill_extra( SS_2H_COMBAT ) );
    Spellcraft = spell_caster->query_skill( SS_SPELLCRAFT )-
        MIN_SPELLCRAFT_LEFT;
    Spellcraft = max( 0, min( SPELLCRAFT_DRAIN_BASE, Spellcraft ) );
                                /*X+1 because we want to roll between X and
                                 *0                                       */
    Spellcraft_drain = random( Spellcraft+ 1 );
    Wep_skill_gain = EXTRA_SKILL_BASE+
        ftoi( itof( Spellcraft_drain )/ EXCHANGE_FACTOR + 0.5 );
    
    if ((spell_caster->query_skill( Weapon_type )+ Wep_skill_gain) >
        WEAPON_SKILL_capitalize)
    {
        Wep_skill_gain = WEAPON_SKILL_capitalize-
            spell_caster->query_skill( Weapon_type );
        Spellcraft_drain = max( 0, ftoi( itof( Wep_skill_gain )*
            EXCHANGE_FACTOR+ 0.5 )- EXTRA_SKILL_BASE );
    }
}

void enhance_mage()
{
 string message;
 string _grip = ((shadow_who->query_hands() == W_BOTH) ? "s" : "" ),
     _n_grip = (_grip == "s" ? "" : "s"), _short = shadow_who->short();
 string *wield_messages =
 ({
    "Your hand"+ _grip+ " wrap"+ _n_grip+
        " tightly around the hilt of the "+ _short+ ".\n",
    "The "+ _short+ " seems to be an extension of your arm"+ _grip+ ".\n",
    "You feel more confident when you hold the "+ _short+ " than you did "+
        "before.\n",
    "The hilt of the "+ _short+ " seems to perfectly fit your hand"+ _grip+
        "!\n",
    "You confidently grip your "+ _short+ ".\n",
    "The "+ _short+ " seems to adhere itself to your hand"+ _grip+ ".\n"
 });
 int i = sizeof( wield_messages );

    spell_caster->set_skill_extra( Weapon_type, spell_caster->
        query_skill_extra( Weapon_type )+ Wep_skill_gain );
    spell_caster->set_skill_extra( SS_SPELLCRAFT, spell_caster->
        query_skill_extra( SS_SPELLCRAFT )- Spellcraft_drain );
    spell_caster->set_skill_extra( SS_2H_COMBAT, spell_caster->
        query_skill_extra( SS_2H_COMBAT )- Two_handed_loss );
    if (Wep_skill_gain > 0)
    {
        message = "You feel more like a fighter";
        if (Spellcraft_drain > 0)
        {
            message += ", but less like a mage";
        }
        message += " now!\n";
        spell_caster->catch_tell( message );
    }
    if (Brawl_proof)
    {
        spell_caster->add_prop( RANGER_M_NOT_DISARM, "The "+ _short+
            " wielded by "+ QTNAME( spell_caster )+ " is magically "+
            "enchanted. It is impossible to disarm the wielder!\n" );
        spell_caster->catch_tell( wield_messages[random( i )] );
    }
}

void degrade_mage()
{
    spell_caster->set_skill_extra( Weapon_type, spell_caster->
        query_skill_extra( Weapon_type )- Wep_skill_gain );
    spell_caster->set_skill_extra( SS_SPELLCRAFT, spell_caster->
        query_skill_extra( SS_SPELLCRAFT )+ Spellcraft_drain );
    spell_caster->set_skill_extra( SS_2H_COMBAT, spell_caster->
        query_skill_extra( SS_2H_COMBAT )+ Two_handed_loss );
    if (Brawl_proof)
    {
        spell_caster->remove_prop( RANGER_M_NOT_DISARM );
    }
    if (Wep_skill_gain > 0)
    {
        spell_caster->catch_tell( "As you break the contact with your "+
            shadow_who->short()+ ", you feel as though your skills "+
            "change.\n" );
    }
}

public void remove_shadow()
{
 int weapon_state;
 object  env;

    remove_alarm( Duration );
    Duration = 0;

                                /*The weapon can be either in caster's hand
                                 *or in his scabbard. It shouldn't be
                                 *anywhere else.                          */
    if (objectp( spell_caster ))
    {
        env = environment( spell_caster );
    }
    else if (objectp( env = environment( shadow_who ) ))
    {
        while (!env->query_prop( ROOM_I_IS ))
        {
            env = environment( env );
        }
    }
    else
    {                            /*If we don't have an environment, then
                                 *let's just go away.                     */
        shadow_who->remove_object();
        return ::remove_shadow();
    }

                                /*Let us set one useful flag. Note that
                                 *these conditions are sensitive to the
                                 *sequence they are called.                  */
    if ((calling_program(-1) == SCABBARD) &&
        (calling_function(-1) == "leave_inv"))
    {
         weapon_state = ELSEWHERE;
    }
    else if (environment( shadow_who )->id( "_emyn_arnen_scabbard" ))
    {
        weapon_state = IN_SCABBARD;
    }
    else if (calling_function(-1) == "unwield")
    {                            /*I'm not sure why, but in spite of what
                                 *this flag suggests the weapon is still
                                 *wielded.                                  */
        weapon_state = JUST_UNWIELDED;
    }
    else if ((shadow_who->query_wielded()) == spell_caster)
    {
        weapon_state = FROM_HAND;
    }


                                /*The spell's timeout or the sword was
                                 *unwielded.                              */
    if ((weapon_state == FROM_HAND) || (weapon_state == JUST_UNWIELDED))
    {
        tell_room( env, "The searing-hot flames engulfing "+ 
            QPNAME( spell_caster )+ " "+ shadow_who->short()+
            " quietly flicker out of existence as "+ HE( spell_caster )+
            " releases "+ HIS( spell_caster )+ " grip upon it.\n",
            spell_caster );
        spell_caster->catch_msg( "The searing-hot flames engulfing "+
            "your "+ shadow_who->short()+ " quietly flicker out of "+
            "existence as you release your grip upon it.\n" );
    }
    else if (weapon_state == IN_SCABBARD)
    {
        spell_caster->catch_msg( "You feel as though the effects of "+
            "narusse have dispersed.\n" );
    }
    else if (weapon_state == ELSEWHERE)
    {
        tell_room( env, "The searing-hot flames engulfing "+ 
            QPNAME( spell_caster )+ " "+ shadow_who->short()+
            " quietly flicker out of existence as "+ HE( spell_caster )+
            " touches it.\n", spell_caster );
        spell_caster->catch_msg( "The searing-hot flames engulfing "+
            "your "+ shadow_who->short()+ " quietly flicker out of "+
            "existence as the spell disperses.\n" );        
    }

                                /*Let us restore the caster here.         */
    spell_caster->remove_prop( "_live_i_narusse_enhanced" );

                                /*And the weapon.                         */
    remove_alarm( Flicker );
    shadow_who->remove_prop( WEAPONS_O_OWNER, spell_caster );
                                /*A weapon should never remain wielded after
                                 *the spell end.                          */
    if (weapon_state == FROM_HAND)
    {
        shadow_who->unwield_me();
    }

    if (MagicWeapon)
    {
        if (weapon_state != IN_SCABBARD)
        {
            tell_room( env, "When the flames die out, you notice that the "+
                shadow_who->short() + " looks scorched.\n" );
        }
        shadow_who->set_corroded( shadow_who->query_corroded()+ 1 );
        shadow_who->remove_adj( "flaming" );
        shadow_who->set_short( OldShort );
        if (objectp( OldWieldFunc ))
        {
            shadow_who->set_wf( OldWieldFunc );
        }
        else
        {
            shadow_who->set_wf( 0 );
        }
        shadow_who->add_prop( MAGIC_AM_MAGIC, MagicMagic );
        shadow_who->add_prop( MAGIC_AM_ID_INFO, MagicInfo );
        shadow_who->set_hit( OldToHit );
                                /*I left this line because of historical
                                 *reasons. It used to be possible in the
                                 *past that a magical weapon didn't break
                                 *and remained wielded after the spell wore
                                 *off (it shouldn't happen in this version).
                                 *If that's the case cb_update_weapon() must
                                 *be called.                              */
//      spell_caster->query_combat_object()->cb_update_weapon( shadow_who );
    }
    else
    {
        if (weapon_state != IN_SCABBARD)
        {
            tell_room( env, "When the flames die out, the "+
                shadow_who->short()+ " crumbles to ashes.\n" );
        }

        setuid();
        seteuid( getuid() );
        clone_object( SPELL_OBJ_DIR+ "ashes" )->
            move( environment( shadow_who ), 1 );
                                /*This is to avoid the ugly 'You drop
                                 *something' when you drop a weapon.      */
        shadow_who->set_short( "crumbling weapon" );
        NUT_CRACKER->crack( shadow_who );
    }
    return ::remove_shadow();
}

/*
 * Function name : f_narusse_duration
 * Description   : The function returns the duration of the narusse spell
 *                 : in seconds.
 *               : It should be around 10+ (0-15) + (0-25)+ ~5 minutes. An
 *               : apprentice (exp = 80) will keep the spell for about 20
 *               : minutes. A full mage with (exp = 150) for 47 minutes.
 * Arguments:    : int var1 - should be spell_power
 *               : int var2 - spell_caster->query_stat( SS_OCCUP )
 */
private nomask int f_narusse_duration( int var1, int var2 )
{
    if (spell_caster->query_name() == "Chmee")
    {
        return 90;
    }
    return 300+ 60* (var1- 30) + 10* var2 + random(300);
}

varargs public int dispel_spell_effect( object dispeller )
{
    remove_shadow();
    remove_spell_effect_object();
}

public int query_flame_blade()
{
    return 1;
}

string long()
{
    return (shadow_who->long()+ "It is engulfed in searing-hot flames.\n");
}

public void flicker()
{
 int i;
 mixed env;

    if (!objectp( spell_caster ))
    {
        remove_shadow();
        return;
    }

    Flicker = set_alarm( 30.0+ rnd()* 60.0, 0.0, flicker );

    i = random( sizeof( FlickMess ) );

    env = environment( shadow_who );

    if(env == 0)
       env = "NO_ENV";

    if (!objectp(env))
       return;
    
    if (env == spell_caster)
    {
        spell_caster->catch_msg( FlickMess[i][0]+ "your "+
            shadow_who->short()+ FlickMess[i][1] );
        tell_room( environment( spell_caster ), FlickMess[i][0]+
            QTNAME( spell_caster )+ "'s "+ shadow_who->short()+
            FlickMess[i][1], spell_caster );
    }
    else if (env->id( "_emyn_arnen_scabbard" ))
    {
        switch (random( 3 ))
        {
        case 0:
            spell_caster->catch_msg( "A shower of sparks spouts out of "+
                "your "+ env->short()+ ".\n" );
            tell_room( environment( spell_caster ), "A shower of sparks "+
                "spouts out of "+ QTNAME( spell_caster )+ "'s "+
                env->short()+ ".\n", spell_caster );
            break;
        case 1:
            spell_caster->catch_msg( "Your "+ env->short()+ " sizzles and "+
                "crackles furiously.\n" );
            tell_room( environment( spell_caster ), QCTNAME( spell_caster )+
                "'s "+ env->short()+ " sizzles and crackles furiously.\n",
                spell_caster );
            break;
        case 2:
            spell_caster->catch_msg( "Smoke curls out of your "+
                env->short()+ ", leaving an irritating smell in the "+
                "air.\n" );
            tell_room( environment( spell_caster ), "Smoke curls out of "+
                QTNAME( spell_caster )+ "'s "+ env->short()+ ", leaving "+
                "an irritating smell in the air.\n", spell_caster );
            break;
        }
    }
}

public void burn_enemy( object enemy, string hit_loc = "body" )
{
 string flame, how;
 int dam = 0, pen, res;
 mixed   rval;
 object corpse_sh;
 
    if (!objectp( spell_caster ))
    {
        remove_shadow();
        return;
    }

    if (!objectp( enemy ))
    {
        return;
    }
    pen = FLAME_PEN;
    res = enemy->query_magic_res( MAGIC_I_RES_FIRE );

//  I decided it's the weapon what is enchanted so mages' skill shouldn't
//  affect the target's resistance.  
//    res -= res * spell_caster->query_skill( SS_SPELLCRAFT )*
//        RESISTANCE_MODIFIER/ 10000;

    pen -= pen* res/ 100;

    rval = enemy->hit_me( F_PENMOD(pen, spell_caster->query_skill(
        SS_ELEMENT_FIRE)), MAGIC_DT, spell_caster, -1 );
    if (pointerp( rval ))
    {
        dam = rval[0];
    }
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

    spell_caster->catch_msg("The searing-hot flames surrounding your "
      + shadow_who->short() + " " + flame + " the " + hit_loc
      + " of " +QTNAME(enemy) + ".\n" + capitalize(HE(enemy))
      + " looks " + how + " by the flames.\n");

    enemy->catch_msg("The searing-hot flames surrounding "
      + QPNAME(spell_caster) + " " + shadow_who->short() + " " + flame
      + " your " + hit_loc + ".\n"
      + "You are " + how + " by the flames.\n");

    spell_caster->tell_watcher("The searing-hot flames surrounding "
      + QPNAME(spell_caster) + " " + shadow_who->short() + " " + flame
      + " the " + hit_loc + " of " + QTNAME(enemy) + ".\n"
      + capitalize(HE(enemy)) + " looks " + how + " by the flames.\n",
      enemy);

    if (enemy->query_hp() <= 0)
    {
        spell_caster->catch_msg( QCTNAME( enemy )+ " gasps "+ HIS( enemy )+
            " last breath as the flames of Orodruin consume "+ HIM( enemy )+
            ".\n" );
        enemy->catch_msg( "You gasp you last breath as the flames of "+
            "Orodruin consume your body.\n" );
        spell_caster->tell_watcher( QCTNAME( enemy )+ " gasps "+
            HIS( enemy )+ " last breath as the flames of Orodruin consume "+
            HIM( enemy )+ ".\n");
 
        corpse_sh = clone_object( MORGUL_DEATH_SHADOW );
        corpse_sh->shadow_me( enemy );
        corpse_sh->set_death_cause( NARUSSE_CS );
        corpse_sh->set_death_variant( random( NARUSSE_VR ) );
        enemy->do_die( spell_caster );
        corpse_sh->remove_shadow();
    }
}

public varargs int did_hit( int aid, string hdesc, int phurt, object enemy,
    int dt, int phit, int dam )
{
    int rval =
        shadow_who->did_hit( aid, hdesc, phurt, enemy, dt, phit, dam );

    if (!objectp( enemy ))
    {
        return (rval);
    }
    if (phurt > 0)
    {
        set_alarm( 0.0, 0.0, &burn_enemy( enemy, hdesc ) );
    }
    return (rval);
}

public string stat_object()
{
 string  str = shadow_who->stat_object();

    str += "This weapon has been enchanted by a spell of the Society "
    +  "of Morgul Mages, engulfing it in flames, inflicting extra "
    +  "damage upon successful hits.\n"
    +  "Remaining duration: " + ftoa(get_alarm(Duration)[2])
    +  " seconds.\n";
    return str;
}

mixed query_flick_message()
{
    return FlickMess;
}

public mixed unwield( object ob )
{
 mixed rval = 0;

    if (objectp( OldWieldFunc ))
    {
        rval = OldWieldFunc->unwield( ob );
    }

    if (stringp( rval ) || (intp( rval ) && (rval < 0)))
    {
        return rval;
    }
    degrade_mage();
                                /*Flaming swords are sheatable. Also this
                                 *function cal be called from remove_shadow
                                 *so it would be folly to call it
                                 *recursively.                            */
    if ((calling_program(-1) != SCABBARD) && (Duration != 0))
    {
        dispel_spell_effect();
    }
                                /*We return 1 because remove_shadow issues
                                 *out own unwield message.                */
    return 1;
}

public mixed wield( object ob )
{
 mixed rval = 0;

	
    if (objectp( OldWieldFunc ))
    {
        rval = OldWieldFunc->wield( ob );
    }
    if (stringp( rval ) || (intp( rval ) && (rval < 0)))
    {
        return rval;
    }

    enhance_mage();
    return 0;
}

/*
public void leave_env( object from, object to )
{
    shadow_who->leave_env(from, to);
    dispel_spell_effect();
}
*/
