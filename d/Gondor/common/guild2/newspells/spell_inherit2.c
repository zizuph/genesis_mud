/* File         : /d/Gondor/common/guild2/newspells/spell_inherit.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : May 28nd 2000
 * Purpose      : This an inheritatble file for all the morgul mage spells
 * Related Files: ~Genesis/newmagic/spell.c
 * Comments     : All the mage spells should inherit this file
 *                My thanks to Olorin his inital work on the Morgul
 *                Mages... his dream and vision for the guild will
 *                continue to shine with this new system.
 * Modifications: Continous modifications and maintenance activities by
 *              : Chmee since April, 2001.
 *              : Major change regarding the engine loading spells.
 *              : Spells are no more holdable items, spell_obj is no more
 *              : and its functionality is moved to mage_robe.c
 *              : Chmee, May, 2002.
 *
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
#include "spells.h"
#include "../lib/morgul_defs.h"
#include <filter_funs.h>
#include <composite.h>
#include <tasks.h>
#include <macros.h>
#include <language.h>
#include <files.h>
#include <wa_types.h>
#include <cmdparse.h>

inherit SPELL_LIB;

                                /* True if a caster needs to have both
                                 * hands free to cast this spell.          */
static int gSpell_free_hands = 1;


public void
set_free_hands(int hands)
{
    gSpell_free_hands = hands;
}

public int
query_free_hands( void )
{
    return gSpell_free_hands;
}

void
hook_no_mana_fail()
{
    write( "You do not feel strong enough to cast the spell.\n" );
}

void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write( "One of the ingredients is missing!\n" );
}

void
hook_targets_gone()
{
    write( "The target of your spell seems have escaped your wrath.\n" );
}

void
hook_stun_fail()
{
    write( "You are too stunned to call upon the Dark Lord.\n" );
}

/*
 * Function name: spell_resolve_time
 * Description  : Calculates the time for set_spell_time accordingly to
 *                mage's occ exp.
 * Arguments    : guild_exp - self explanatory, min - spell time for a mage
 *              : with exp == 150, max - spell time for a newbie
 */
nomask int spell_resolve_time( int guild_exp, int min, int max )
{
 int Outcome;

    Outcome = max+ ftoi(0.5+ itof( (min- max)* guild_exp )/ 150.0);
    if (Outcome < min)
    {
        Outcome = min;
    }

    return Outcome;
}

/*
 * Some redefines. I don't like the way the default system works.
 */
                                /*Let us check the targets during the spell
                                 *resolution if this is a combat spell.   */
public int
query_spell_pretarget()
{
    if (gSpell_offensive)
    {
        return 0;
    }
    return 1;
}

public int
test_movement_fail( object caster )
{
 string *allowed_spells = ({ "palanquendo", "nifarist", "gostangwedh"});

    if ((gSpell_offensive) ||
        (member_array( query_spell_name(), allowed_spells) != -1 ))
    {
        return 0;
    }
    else
    {
        return ::test_movement_fail( caster );
    }
}

                                /*Comparing to the original one this
                                 *function has the check for closed
                                 *containers removed and the check for
                                 *nested (1st level) containers added.    */
public object *
get_item_search_list( object caster )
{      
 int i, j;
 object *eyes = ({}), *skulls = ({}), *skins = ({}), *other = ({}),
    *inv = all_inventory( caster );

    i = sizeof( inv );
    j=i;
    while (i--)
    {
        if (inv[i]->query_prop( CONT_I_HOLDS_COMPONENTS ))
        {
            inv += all_inventory( inv[i] );
        }
    }
                                /*Let us check for nested containers.     */
    i = sizeof( inv );
    for (j;j<i;j++)
    {
        if (inv[j]->query_prop( CONT_I_HOLDS_COMPONENTS ))
        {
            inv += all_inventory( inv[j] );
        }        
    }
                                /*Now let us sort the ingredients, so the
                                  morgul special ingredients are at the
                                  end of the list. I don't use filter funs
                                  here to optimize the speed of code.     */
    i = sizeof( inv );
    for (j=0;j<i;j++)
    {
        if (inv[j]->id( "eye" ))
        {
            eyes += ({ inv[j] });
        }
        else if (inv[j]->id( "skull" ))
        {
            skulls += ({ inv[j] });
        }
        else if (inv[j]->id( "snake skin" ))
        {
            skins += ({ inv[j] });
        }
        else
        {
            other += ({ inv[j] });
        }
    }
    return other+ eyes+ skulls+ skins;
}

void
log_spell(string spell, string txt)
{
    setuid();
    seteuid(getuid());
    write_file( MORGUL_LOG_DIR+ spell, ctime(time())+ " "+ txt+
        " \n" ); 
}

varargs int
check_mage( object caster, int skip_check )
{
 object *stuff;
 string h_text;

    write("Checkpoint2A.\n");
    // Safety
    if (!objectp( caster ))
    {
        return 0;
    }

    if (!caster->query_wiz_level() &&
        !present( MORGUL_S_GUILD_OBJECT, caster ))
    {
        caster->catch_tell( "Without your robe, you cannot cast "+
            "this spell!\n" );
        return 1;
    }
    if (skip_check)
    {
        return 0;
    }
                                /*If the caster needs to have his hands
                                 *free to cast the spell.                 */        
    if (gSpell_free_hands == 1)
    {
        stuff = caster->query_weapon(-1);

        if (sizeof( stuff ))
        {
            if (sizeof(stuff) <= 2 || stuff[0]->query_hands() == W_BOTH)
            {
                h_text = "hands";
            }
            else
            {
                if (stuff[0]->query_hands() == W_RIGHT)
                {
                    h_text = "right hand";
                }
                if (stuff[0]->query_hands() == W_LEFT)
                {
                    h_text = "left hand";
                }
            }
            caster->catch_tell( "You can not call upon the power of the "+
                "Dark Lord with "+ COMPOSITE_ALL_DEAD( stuff )+
                " in your "+ h_text+ ".\n" );
            return 1;
        }
    }
    write("Checkpoint2B.\n");
    return 0;
}

object *
can_see_caster( object caster )
{
    return FILTER_IS_SEEN( caster, FILTER_PLAYERS( all_inventory(
        environment( caster ) ) )- ({caster}) );
}

void
concentrate_msg( object caster, object *targets, string args )
{
    caster->catch_tell( "You prepare to employ Dark Sorcery and draw upon "+
        "the power of the Dark Lord.\n" );
    can_see_caster( caster )->catch_msg( QCTNAME( caster )+
        " draws power from the realm of shadows.\n" );
}

public object *
my_spell_target_one_valid_enemy( object caster, string str )
{
    object *oblist;

    if (!strlen( str ) && objectp(caster->query_attack()))
    {
        return ({ caster->query_attack() });
    }

    if ((member_array( query_spell_name(), ({ "thunaur", "dramalgos" }))
        != -1))
    {
        oblist = PARSE_THIS( str, "[at] / [on] [the] %i" );
        if (sizeof( oblist ) == 1)
        {
            if (oblist[0]->id( "_Morgul_Sulambar_Cloud" ))
            {                   /*It's hard to start a fight with an item.*/
                set_spell_offensive( 0 );
                return oblist;
            }
            else if (!living( oblist[0] ))
            {
                return ({});
            }
        }
    }
    else
    {
        oblist = PARSE_THIS(str, "[at] / [on] [the] %l");
    }

    if (!sizeof(oblist))
    {
        caster->catch_tell( "You can't find your target.\n" );
        return ({});
    }
    if (sizeof(oblist) > 1)
    {
        caster->catch_tell( "You will have to be more specific!  You can "+
            "only select one target.\n" );
        return ({});
    }
    return oblist;
}

/* Function name: default_morgul_spell_setup
 * Description  : This function sets up some defaults and does
 *                some other checks making sure the mage casting
 *                the spell is able to do so.
 * Arguments    : mage - the mage casting the spell
 * Returns      : 1 if everything is ok
 *                0 if setup failed
 */
varargs int
default_morgul_spell_setup( object mage, int skip_check )
{
    if (!check_mage( mage, skip_check ))
    {
	write("Made it to default check (returns 0).\n");
        return 0;
    }
    set_spell_fail( "Your spell seems to have noeffect.\n" );

    // We can move around a bit in order to cast.
    set_spell_stationary( 0 );
    write("Made it to default check (returns 1).\n");
    return 1;
}
void
hook_combat_fail( object *enemies )
{
    write( "You are unable to call upon this spell while in "+
        "combat with "+ FO_COMPOSITE_ALL_LIVE( enemies, this_player() )+
        ".\n" );
}

void
hook_room_no_magic_fail( mixed reason, object room )
{
    if (stringp( reason ))
    {
        write( reason );
    }
    else
    {
        write( "A power greater than the Dark Lord prevents you "+
            "from casting this spell.\n" );
    }
}
