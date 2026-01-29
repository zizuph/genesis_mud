/*
 *  File: /d/Gondor/common/guild2/obj/ephessul.c
 *
 *  The spell objects of the morgul spell ephessul.
 *  Original concept by Olorin (if I'm not mistaken)
 *  The spell was rebuild to fit the new spell system by Igneous
 *  and then completely rewritten by myself (Chmee).
 *  Spell messages were created mostly by Newton. 12.12.2001
 */
#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "../spells.h"

#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()
#define HIM(x)  (x)->query_objective()
#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())

inherit SPELL_OBJECT;
inherit "/std/object.c";

static int _spell_level;

private nomask int calc_spell_level();
private nomask int f_ephessul_duration( int var1, int var2 );
private nomask int _enhanced_sences( object spectator );
nomask void _deploy_ephessul( int stage );
varargs public int dispel_ephessul( object dispeller );

string
wizinfo()
{
 string out;

    out = "The spellobject for the 'ephessul' spell of the Morgul Mages.\n"+
        "The following protections have been assigned to "+
        spell_target->query_name()+ ":\n";
    switch (_spell_level)
    {
    case 4:
        out += "MAGIC_I_RES_ACID   : 50% non-additive,\n"+
            "MAGIC_I_RES_COLD   : 50% non-additive,\n";
    case 3:
        out += "MAGIC_I_RES_AIR    : 60% non-additive.\n";
    case 2:
        out += "MAGIC_I_RES_FIRE   : 50% non-additive,\n";
    case 1:
        out += "MAGIC_I_RES_LIFE   : 70% non-additive,\n"+
            "MAGIC_I_RES_DEATH  : 40% additive,\n";
    case 0:
        out += "MAGIC_I_RES_POISON : 40% additive,\n"+
            "MAGIC_I_RES_MAGIC  : 40% additive,\n";
    }
    return out;
}

void
create_object()
{
    set_name( "Morgul_Ephessul_Object" );
    set_long( "A Morgul magic protection enchantment.\n" );
    add_prop( OBJ_I_VOLUME, 0 );
    add_prop( OBJ_I_WEIGHT, 0 );
    add_prop( OBJ_I_NO_DROP, 1 );
    add_prop( OBJ_I_NO_GIVE, 1 );
    add_prop( OBJ_I_NO_STEAL, 1 );
    set_no_show();
                                /*Let us protect this object a little just
                                 *in case of implementation of some 'dispell
                                 *magic' spell.                           */
    add_prop( MAGIC_I_RES_MAGIC, 100 );
    add_prop( MAGIC_I_RES_AIR, 50 );
                                /*Frankly I don't really understand what
                                 *are these properties good for. The manual
                                 *page is rather cryptic and my researches
                                 *indicate that these properties are simply
                                 *obsolete since the Shiva's new magic
                                 *system doesn't use them at all.         */
    add_prop( OBJ_I_RES_MAGIC, 100 );
    add_prop( OBJ_I_RES_AIR, 50 );

    add_prop( MAGIC_AM_MAGIC, ({ 100, "enchantment" }) );
    add_prop( OBJ_S_WIZINFO, wizinfo );
    set_no_show();
}

varargs public int
dispel_spell_effect( object dispeller )
{
    dispel_ephessul( dispeller );
}


varargs public int
dispel_ephessul( object dispeller )
{
    spell_target->remove_subloc( query_spell_effect_desc() );
                                /*I'm not sure if this line is necessary.*/
    spell_target->remove_arm( this_object() );
    spell_target->remove_magic_effect( this_object() );
    spell_target->add_prop( MORGUL_I_SULAMBAR_RES,
        spell_target->query_prop( MORGUL_I_SULAMBAR_RES )- 1 );
    
    if (spell_target->query_guild_name_occ() == GUILD_NAME)
    {
        spell_target->catch_tell( "You feel the power of the Windfence "+
            "disappearing.\nYou are not protected anymore!\n" );
    }
    else
    {
        spell_target->catch_tell( "The wind blowing around you starts "+
            "losing power until it dies completely. The Morgul spell "+
            "wears off.\n" );
    }
    
    remove_spell_effect_object();
    return 1;
}

void
end_warning()
{
    set_alarm( itof( 18 ), 0.0, dispel_ephessul );
    if (_enhanced_sences( spell_target ))
    {
        spell_target->catch_tell( "You feel that the air shield around "+
            "you loses power.\n" );
    }
}

public int
setup_spell_effect()
{
 int ephessul_duration;
 object *_spectators;

    set_spell_effect_desc( "windfence" );
    if (!::setup_spell_effect())
    {
        return 0;
    }
    ephessul_duration = f_ephessul_duration( spell_power, spell_caster->
        query_stat( SS_OCCUP ));
    spell_target->add_prop( MORGUL_I_SULAMBAR_RES,
        spell_target->query_prop( MORGUL_I_SULAMBAR_RES )+ 1 );
    _spell_level = calc_spell_level();
    spell_target->add_subloc( query_spell_effect_desc(), this_object() );
    if (spell_caster != spell_target)
    {
        _spell_level = max( 0, _spell_level- 1 );
    }
    spell_target->add_magic_effect( this_object() );

                                /*These are all who can't see the caster
                                 *excluding the caster.                   */
    _spectators = FILTER_LIVE( all_inventory( environment(spell_caster) )-
        ({ spell_caster }) );
    _spectators = _spectators - FILTER_IS_SEEN( spell_caster, _spectators );

    spell_caster->catch_tell( "With the power the Dark Lord has bestowed "+
        "upon you, you call the Windfence.\nYou mumble the dark words:\n"+
        "\t'Telio, ephessul, berio bior Beleghir Morui'\n"+
        "Your robe starts shining with a pale, green glow.\n");
    tell_room( environment( spell_caster ), "Employing Dark Sorcery, "+ 
        QTNAME( spell_caster )+ " calls upon the Power of Sauron.\n"+ 
        capitalize( HE( spell_caster ) )+ " mumbles a few, strange words "+
        "and suddenly "+ HIS( spell_caster )+ " robe starts shining with "+
        "a pale, green glow.\n", ({ _spectators, spell_caster }) );
    _spectators->
        catch_msg( "You hear someone mumbles a few, strange words.\n" );

    set_alarm( 5.0, 0.0, &_deploy_ephessul( 0 ) );
    set_alarm( itof( ephessul_duration ), 0.0, end_warning );
    SPELL_INHERIT->log_spell( "ephessul", "Caster: "+ spell_caster->
        query_cap_name()+ ", target: "+ NAME( spell_target )+
        ", duration: "+ (ephessul_duration+ 30)/ 60+ "[min], level: "+
        _spell_level );
    move( spell_target, 1 );
}

mixed
query_magic_protection( string prop, object who = previous_object() )
{
    if (who == spell_target)
    {
        switch (prop)
        {
        case MAGIC_I_RES_MAGIC:      return ({40, 1});
        case MAGIC_I_RES_POISON:  return ({40, 1});

        case MAGIC_I_RES_DEATH:
            if (_spell_level > 0)
            {
                return ({40, 1});
            }
            break;
        case MAGIC_I_RES_LIFE:
            if (_spell_level > 0)
            {
                return ({70, 0});
            }
            break;

        case MAGIC_I_RES_FIRE:
            if (_spell_level > 1)
            {
                return ({50, 0});
            }
            break;

        case MAGIC_I_RES_AIR:
            if (_spell_level > 2)
            {
                return ({60, 0});
            }
            break;

        case MAGIC_I_RES_COLD:
            if (_spell_level > 3)
            {
                return ({50, 0});
            }
            break;
        case MAGIC_I_RES_ACID:
            if (_spell_level > 3)
            {
                return ({50, 0});
            }
            break;
        }
    }
    return ::query_magic_protection( prop, who );
}

private nomask int calc_spell_level()
{
 int _g_exp = spell_caster->query_stat( SS_OCCUP );
                                /*Base: poison and magic resistance, 100%.
                                 *The probability estimations are made for
                                 *a fully trained mage with guild exp close
                                 *to 150.                                 */
    if (random( 100 ) > (spell_power+ ((_g_exp- 100)* 4)/ 10))
    {
        return 0;
    }                            /*Death and life spells resistance, 82%  */
    else if (random( 100 ) > (((spell_power* 85)/ 100)+
        ((_g_exp- 100)* 4)/ 10))
    {
        return 1;
    }                            /*Fire spells resistance, 60%            */
    else if (random( 100 ) > ((spell_power* 3/ 4)+ ((_g_exp- 100)* 4)/ 10))
    {
        return 2;
    }                           /*Air spells resistance, 40%              */
    else if (random( 100 ) > ((spell_power/ 2)+ ((_g_exp- 100)* 4)/ 10))
    {
        return 3;
    }                           /*Cold and acid resistance, 20%           */
    else
    {
        return 4;
    }
}

/*
 * Function name : _enhanced_sences
 * Description   : Filters knowledgable spectators who can see enhanced
 *                 messages.
 * Arguments:    : objects spectator - selfexplanatory
 * Return value  : 1 - true or 0 - false.
 */
private nomask int _enhanced_sences( object spectator )
{
    if (spectator->query_guild_name_occ() == GUILD_NAME)
    {
        return 1;
    }
    else if (random(100) < max( 0, spectator->resolve_task( TASK_DIFFICULT,
        ({ SKILL_WEIGHT, 15, SS_ELEMENT_AIR
           SKILL_WEIGHT, 50, SS_SPELLCRAFT,
           SKILL_WEIGHT, 15, SS_FORM_ENCHANTMENT,
           SKILL_WEIGHT, 10, TS_INT,
           SKILL_WEIGHT, 10, TS_WIS }) )))
    {
        return 1;
    }
    return 0;
}

nomask void _deploy_ephessul( int stage )
{
 object *_spectators, *_enhanced_spectators;

    if (stage <= _spell_level)
    {
        set_alarm( 5.0, 0.0, &_deploy_ephessul( stage+ 1 ) );
    }
    else
    {
        spell_target->catch_tell( "The wind extinguishes forming a "+
            "protective cocoon around your body\n" );
        tell_room( environment( spell_target ), "The air returns to a "+
            "state of tranquility.\n", ({ spell_target }), this_object() );
        spell_caster->catch_tell( "Your robe stops glowing.\n" );
                                /*These are all who can't see the caster
                                 *excluding the caster.                   */
        _spectators = FILTER_LIVE( all_inventory( environment(
            spell_caster ) )- ({ spell_caster }) );
        _spectators = _spectators - FILTER_IS_SEEN( spell_caster,
            _spectators );
        tell_room( environment( spell_caster ), QTNAME( spell_caster )+
            "'s robe stops glowing.\n", ({ _spectators, spell_caster}) );
        return;
    }

    _spectators = FILTER_LIVE( all_inventory( environment(spell_target) ));
    _enhanced_spectators = filter( _spectators, _enhanced_sences );
    _spectators = _spectators - _enhanced_spectators;
    switch( stage )
    {
    case 0:
        if (sizeof( _enhanced_spectators ))
        {
            _enhanced_spectators->catch_tell( "A gentle zephyr blows that "+
                "purges the air of contaminants and mystical "+
                "qualitites.\n" );
        }
        if (sizeof( _spectators ))
        {
            _spectators->catch_tell( "A gentle zephyr cools your skin.\n" );
        }
        break;
    case 1:
        if (sizeof( _enhanced_spectators ))
        {
            _enhanced_spectators->catch_tell( "The zephyr gains momentum "+
                "and becomes a firm breeze that wafts through the area, "+
                "making it impossible to distinguish between life and "+
                "death.\n" );
        }
        if (sizeof( _spectators ))
        {
            _spectators->catch_tell( "The zephyr gains momentum and "+
                "becomes a firm breeze that wafts through the area, "+
                "rising some dust up.\n" );
        }
        break;
    case 2:
        if (sizeof( _enhanced_spectators ))
        {
            _enhanced_spectators->catch_tell( "The breeze rapidly gains "+
                "force with fierce gusts of wind that threaten to "+
                "extinguish flames.\n" );
        }
        if (sizeof( _spectators ))
        {
            _spectators->catch_tell( "The breeze rapidly gains force with "+
                "fierce gusts of wind that threaten your stability.\n" );
        }
        break;
    case 3:
        if (sizeof( _enhanced_spectators ))
        {
            _enhanced_spectators->catch_tell( "The gusts of wind "+
                "consolidate their force into a mighty gale that ravages "+
                "the atmosphere itself.\n" );
        }
        if (sizeof( _spectators ))
        {
            _spectators->catch_tell( "The gusts of wind consolidate their "+
                "force into a mighty gale tossing your clothes there and "+
                "fro.\n" );
        }
        break;
    case 4:
        if (sizeof( _enhanced_spectators ))
        {
            _enhanced_spectators->catch_tell( "The gale increases in "+
                "corrosive strength and frigidity until a whining squall "+
                "whistles frantically.\n" );
        }
        if (sizeof( _spectators ))
        {
            _spectators->catch_tell( "The gale increases until a whining "+
                "squall whistles frantically.\n" );
        }
    }
    return;
}

/*
 * Function name : f_ephessul_duration
 * Description   : Calculates the duration of the ephessul effect. For a
 *                 full mage should be around 1/2 of ringurth (20 minutes)
 * Arguments:    : int var1 - should be spell_power
 *               : int var2 - spell_caster->query_stat( SS_OCCUP )
 */
private nomask int f_ephessul_duration( int var1, int var2 )
{
 int base, dispersion;
     base = 12* var1 + 5* var2;
    if (spell_caster != spell_target)
    {
        base = (2* base)/ 3;
    }
    dispersion = random( base/ 10 );
                                /*+/- 5%                                  */
    return base- (base/ 20)+ dispersion+ 25;
}

public string
show_subloc( string subloc, object on, object for_obj )
{
    if (on->query_prop( TEMP_SUBLOC_SHOW_ONLY_THINGS ) ||
        subloc != query_spell_effect_desc())
    {
        return environment( this_object() )->
            show_subloc( subloc, on, for_obj );
    }

    if (for_obj == on)
    {
        switch (_spell_level)
        {
            case 0:
                return "A zephyr evelopes you gently.\n";
                break;
            case 1:
                return "A firm breeze blows around you.\n";
                break;
            case 2:
                return "Fierce gusts of wind toss your clothes and hair.\n";
                break;
            case 3:
                return "Gale force winds form a cocoon around you.\n";
                break;
            case 4:
                return "You feel as if you were in the eye of a cyclone.\n";               
        }
    }
    else
    {
        switch (_spell_level)
        {
            case 0:
                return "A zephyr evelopes "+ HIM( spell_target )+
                    " gently.\n";
                break;
            case 1:
                return "A firm breeze blows around "+ HIM( spell_target )+
                    ".\n";
                break;
            case 2:
                return "Fierce gusts of wind toss "+ HIS( spell_target )+
                    " clothes and hair.\n";
                break;
            case 3:
                return "Gale force winds form a cocoon around "+
                    HIM( spell_target )+ ".\n";
                break;
            case 4:
                return capitalize( HE( spell_target ) )+ " looks as if "+
                    HE( spell_target )+ " was in the eye of a cyclone.\n";                
        }
    }
}
