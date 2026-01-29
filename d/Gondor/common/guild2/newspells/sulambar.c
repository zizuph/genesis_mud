/*
 * Reduced the chances that the spell fails for mages, with the caveat 
 * that if it is abused again, the fail rates will become astronimical 
 * and the spell may even be pulled all together. Mailed the Nazgul abt 
 * this and advised they note it in their archives for future reference.
 * -- Finwe, October 8, 2005
 */

#pragma save_binary
#pragma strict_types

#include "spells.h"
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <terrain.h>
#include "/std/combat/combat.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define NAME(x)   (x->query_npc() ? file_name(x) : x->query_cap_name())

inherit SPELL_RESIST;
inherit SPELL_INHERIT;

public mixed *do_bolt_damage( object caster, object target, int pen )
{
 int ran, i, j, k, hit, *hloc_ids, ac;
 object cob;
 mixed *hloc;

    /* Pick a hitlocation and apply armour mod to pen */
    ran = random( 100 );

    cob = target->query_combat_object();
    hloc_ids = cob->query_hitloc_id();
    hit = -1;
    k = sizeof( hloc_ids );
    j = 0;    
    for (i=0; i < k; i++)
    {
        hloc = cob->query_hitloc( hloc_ids[i] );
    
        j += hloc[HIT_PHIT];
        if (j >= ran)
        {
            hit = hloc_ids[i];
            ac = (intp(hloc[HIT_AC]) ? 
                hloc[HIT_AC] : hloc[HIT_AC][random(sizeof(hloc[HIT_AC]))]);
            pen -= random( ac/ 2 );
            break;
        }
    }

    return target->hit_me( pen, MAGIC_DT, this_object(), -1, hit );
}

void
resolve_spell( object caster, object *targets, int *resist, int result )
{
	int i, j, _fire_res, _fire_pen;
	string hit_description, victims = "";
	object *_who_can_see, *_everybody, _here;
	mixed *hitresult;
	int charges;

    if (check_mage( caster ))
    {
        return;
    }

	// Do the charge checks only on non npc's
	if(!caster->query_npc())
	{
		// Get the number of charges remaining
		charges = MORGUL_MASTER->query_sulambar_charges(caster);

		// If we don't have any charges remaining, write a message and fail
		if(charges <= 0)
		{
			log_spell( "sulambar", caster->query_name()+ 
				" ran out of sulambar charges.");

			caster->catch_tell("You fail to call the Wind of Doom. It is " +
				"spread over too much land.\n");
			return;
		}

		// Decrease the number of charges
		// MORGUL_MASTER->decrease_sulambar_charge(caster); 
        // Moved to when actually succeeding with a cast. (Toby, 2007-01-05)
	}

    setuid();
    seteuid( getuid() );
    _who_can_see = can_see_caster( caster );
    _here = environment( caster );
	
    caster->catch_tell( "With the power the Dark Lord has bestowed upon "+
        "you, you call the Wind of Doom.\nA few inches in front of your "+
        "eyes, a dense dark cloud appears.\nThe cloud forms almost "+
        "a perfect sphere and grows quickly.\n" );
    _who_can_see->catch_msg( "Employing Dark Sorcery, "+ QTNAME( caster )+
        " calls the Wind of Doom.\nA few inches in front of "+
        caster->query_objective()+ ", a dark dense cloud appears.\nThe "+
        "cloud forms an almost perfect sphere and grows quickly.\n" );
    tell_room( _here, "Unexpectedly, out of nowhere, a dark dense cloud "+
        "appears.\nThe cloud forms an almost perfect sphere and grows "+
        "quickly.\n", _who_can_see+ ({caster}) );
// fails approx 87.5% of the time
//        if ((random( 200 ) >= MIN(caster->query_stat( SS_OCCUP ), 175)) &&
// fails approx 50% of the time.
//        if ((random( 350 ) >= MIN(caster->query_stat( SS_OCCUP ), 175)) &&
// Hmmm ... lets try a new approach. Here, we use the casters occ stat to
// help create the number. The higher the guildstat, the less chance the
// spell will fail. - Gorboth
    if ((random(caster->query_stat(SS_OCCUP) + 50) >=
        MIN(caster->query_stat(SS_OCCUP), 175)) &&
        (_here->query_prop( ROOM_I_TYPE ) != ROOM_UNDER_WATER) &&
        !(_here->terrain_includes_any( TERRAIN_UNDERWATER )) &&
        !caster->query_npc() )
    {
        caster->command( "$frown" );
        caster->catch_tell( "You've mishandled the spell!\n" );
        _fire_pen = F_PENMOD( 120+ random( 60 ), 280 );
        if (_here->query_prop( ROOM_I_INSIDE ))
        {
            tell_room( _here, "KABOOOOM!\n" );
            _fire_pen = _fire_pen* 2;
        }
        else
        {
            tell_room( _here, "FOOOOMP!\n" );
        }
        tell_room( _here, "Somehow the cloud catches the fire and "+
            "explodes.\n" );
        _everybody = FILTER_LIVE( all_inventory( _here ) );
        j = sizeof( _everybody );
        for (i=0; i < j;i++)
        {
            if (caster == _everybody[i])
            {
                _fire_res = spell_resist( caster, caster,
                    SS_ELEMENT_FIRE, TASK_FORMIDABLE );
            }
            else
            {
                _fire_res = spell_resist( caster, _everybody[i],
                    SS_ELEMENT_FIRE, TASK_ROUTINE );
            }
            hitresult = do_bolt_damage( caster, _everybody[i],
                _fire_pen- _fire_pen* _fire_res/ 100 );
            switch (hitresult[0])
            {
            case -2:            /*Manuals don't mention what the return
                                 *value of -2 may mean. -1 is missed.     */
            case -1:
            case 0:
                hit_description = "unharmed ";
                break;
            case 1..12:
                hit_description = "slightly hurt ";
                break;
            case 13..24:
                hit_description = "somewhat hurt ";
                break;
            case 25..36:
                hit_description = "rather hurt ";
                break;
            case 37..48:
                hit_description = "hurt ";
                break;
            case 49..60:
                hit_description = "very hurt ";
                break;
            case 61..72:
                hit_description = "badly tattered ";
                break;
            case 73..84:
                hit_description = "smashed ";
                break;
            case 85..99:
                hit_description = "massacred ";
                break;
            default :
                hit_description = "killed ";
                break;
            }
            _everybody[i]->catch_tell( "You are "+ hit_description+ "by "+
                "the explosion.\n" );
            tell_room( _here, QCTNAME( _everybody[i] )+ " is "+
                hit_description+ "by the explosion.\n", _everybody[i] );
            victims += "\n"+ NAME( _everybody[i] )+ " has been "+
                hit_description+ "by the blast ("+ hitresult[3]+ "[hp], "+
                hitresult[0]+ "[%])";
            if (_everybody[i]->query_hp() <= 0)
            {
                _everybody[i]->do_die( this_object() );
            }
        }
        log_spell( "sulambar", caster->query_name()+ " mishandled the "+
            "spell in "+ file_name( _here )+ ". Explosion's penetration: "+
            _fire_pen+ ", victims:"+ victims );
    }
    else
    {
        caster->catch_tell( "When the cloud is threatening to envelope "+
            "you, you make a quick gesture with both arms.\nQuickly "+
            "the cloud turns into a pale yellow colour and spreads into "+
            "the surrounding areas.\n" );
        _who_can_see->catch_msg( "When the cloud is threatening to "+
            "envelope "+ caster->query_objective()+ ", "+ QTNAME( caster )+
            " makes a quick gesture with both arms.\nQuickly the cloud "+
            "turns into a pale yellow colour and spreads into "+
            "the surrounding areas.\n" );
        tell_room( _here, "Suddenly the cloud turns into a pale yellow "+
            "colour and spreads into the surrounding areas.\n",
            _who_can_see+ ({caster}) );
        make_spell_effect_object( query_spell_object(), caster, targets,
            resist, result);

        // Do the charge checks only on non npc's
        if(!caster->query_npc())
        {
           // Decrease the number of charges
           MORGUL_MASTER->decrease_sulambar_charge(caster); 
        }
    }
    IDLENESS->increase_activity( caster, RARE_SPELL );
    return;
}

public varargs int
config_spell( object caster, object *targets, string argument )
{
    set_spell_name( "sulambar" );
    set_spell_desc( "Summon the Wind of Doom." );
    set_spell_target( spell_target_caster );
                                /*The spell is not being configured for   *
                                 *a casting attempt, and therefore should *
                                 *not return 1                            */
    if (!objectp( caster ))
    {
        return 0;
    }

                                /*Special configuration for morgul npcs.  */
    if (caster->query_npc())
    {
        set_spell_stationary( 1 );
        set_spell_time( spell_resolve_time( caster->query_stat( SS_OCCUP ),
            6, 16 ));
        set_spell_mana( 180 );
        set_spell_task( TASK_SIMPLE );
        set_spell_element( SS_ELEMENT_AIR, 40 );
        set_spell_form( SS_FORM_CONJURATION, 70 );

        set_spell_ingredients( 0 );
        set_spell_resist( 0 );
        set_spell_object( SPELL_OBJ_DIR + "sulambar_cloud" );
        set_spell_visual( 0 );
        set_spell_vocal( 0 );
        return 0;
    }

    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients( ({ "sulambar_ingr1", "sulambar_ingr2", }) );
    }
    set_spell_time( max(spell_resolve_time( caster->query_stat( SS_OCCUP ),
        6, 12 ), COMBAT_SPELL_I_MIN_PREP_TIME) );
                                /*20% seems to be a justified value       */
    set_spell_mana( caster->query_max_mana()/ 5 );
    set_spell_task( TASK_ROUTINE );
    set_spell_element( SS_ELEMENT_AIR, 40 );
    set_spell_form( SS_FORM_CONJURATION, 70 );
    set_spell_resist( 0 );
    set_spell_object( SPELL_OBJ_DIR+ "sulambar_cloud" );
    set_spell_stationary( 1 );
    set_spell_visual( 0 );
    set_spell_vocal( 0 );

    return 0;
}
