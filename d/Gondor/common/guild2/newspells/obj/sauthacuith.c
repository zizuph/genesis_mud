/*
 * TODO: the target loses the affection after re-loging. This may need to
 * be changed if reveals to be a common practice. (Chmee)
 */

#include <ss_types.h>
#include <filter_funs.h>
#include <macros.h>
#include "../spells.h"

inherit SPELL_OBJECT;

#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()
#define HIM(x)  (x)->query_objective()
#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())

static int con_sucked, con_gained;
static string s_caster, s_target;

private nomask object *can_see_caster( object caster );
private nomask int f_sauthacuith_duration( int var1, int var2 );

varargs public int
dispel_spell_effect( object dispeller )
{
 int old_max, old_hp, new_hp;

    if ((objectp( spell_caster )) &&
        (spell_caster->query_prop( "_live_i_sauthacuith_enhanced" )))
    {
        old_max = spell_caster->query_max_hp();
        old_hp  = spell_caster->query_hp();
                                /*Decrease the stat:                      */
        spell_caster->set_stat_extra( SS_CON,
            spell_caster->query_stat_extra(SS_CON)- con_gained );
                                /*Adjust hitpoints according to the changed
                                 *stat value:                             */
        new_hp  = spell_caster->query_max_hp()* old_hp/ old_max;
        spell_caster->heal_hp( new_hp- old_hp );
        spell_caster->catch_tell( "You feel less vigourous.\n" );
        spell_caster->remove_prop( "_live_i_sauthacuith_enhanced" );
    }
    else
    {                            /*If the caster was logged in:            */
        if (objectp( spell_caster ))
        {
            SPELL_INHERIT->log_spell( "sauthacuith", "The spell effect "+
                "couldn't be dispelled because "+ s_caster+
                " (the caster) wasn't affected." );
        }
        else
        {
            SPELL_INHERIT->log_spell( "sauthacuith", "The spell effect "+
                "couldn't be dispelled because "+ s_caster+
                " (the caster) couldn't be found within the realms." );
        }
    }
                                /*Increase the stat if the victim is still
                                 *alive and affected by sauthacuith.      */
    if ((objectp( spell_target )) &&
        (member_array( "sauthacuith drain effect", spell_target->
        query_magic_effects()->query_spell_effect_desc() ) != -1))
    {
        old_max = spell_target->query_max_hp();
        old_hp  = spell_target->query_hp();
        spell_target->set_stat_extra( SS_CON,
            spell_target->query_stat_extra( SS_CON )+ con_sucked );
                                /*Adjust hitpoints according to the changed
                                 *stat value:                             */
        new_hp  = spell_target->query_max_hp() * old_hp / old_max;
        spell_target->heal_hp( new_hp- old_hp );
        spell_target->catch_tell( "You feel more vigourous.\n" );
    }
    else
    {                            /*If the target was logged in:            */
        if (objectp( s_target ))
        {
            SPELL_INHERIT->log_spell( "sauthacuith", "The spell effect "+
                "couldn't be dispelled because "+ s_target+
                " (the target) wasn't affected." );
        }
        else
        {
            SPELL_INHERIT->log_spell( "sauthacuith", "The spell effect "+
                "couldn't be dispelled because "+ s_target+
                " (the target) couldn't be found within the realms." );
        }
    }
    remove_spell_effect_object();
}

public int
setup_spell_effect()
{
 int old_max, old_hp, new_hp, sauthacuith_duration, relative_loss,
    relative_gain;
 object *spect_caster, *spect_target;

    set_spell_effect_desc( "sauthacuith drain effect" );

    if (!::setup_spell_effect())
    {
        return 0;
    }
    sauthacuith_duration = f_sauthacuith_duration( spell_power,
        spell_caster->query_stat( SS_OCCUP ));

    setuid();
    seteuid( getuid() );
    s_caster = spell_caster->query_name();
    s_target = spell_target->query_name();

                                /*A mage with accordingly to his skills and
                                 *generated value will drain from 13% to 25%
                                 *of a victim's con.                      */
    con_sucked = spell_target->query_stat( SS_CON )*
        (random(6) + (33* spell_power)/ 100)/ 100;
    con_gained = con_sucked*
        spell_caster->query_skill( SS_SPELLCRAFT )/ 100;
    old_max = spell_target->query_max_hp();
    old_hp  = spell_target->query_hp();
    relative_loss = con_sucked* 100/
        spell_target->query_stat( SS_CON );
    relative_gain = con_gained* 100/
        spell_caster->query_stat( SS_CON );

                                /*Decrease the stat:                      */
    spell_target->set_stat_extra( SS_CON,
        spell_target->query_stat_extra( SS_CON )- con_sucked );
                                /*Adjust hitpoints according to the changed
                                 *stat value:                             */
    new_hp  = spell_target->query_max_hp()* old_hp/ old_max;
    spell_target->heal_hp( new_hp- old_hp );

    old_max = spell_caster->query_max_hp();
    old_hp  = spell_caster->query_hp();
                                /*Increase the stat:                      */
    spell_caster->set_stat_extra( SS_CON,
        spell_caster->query_stat_extra( SS_CON )+ con_gained );
                                /*Adjust hitpoints according to the changed
                                 *stat value:                             */
    new_hp  = spell_caster->query_max_hp()* old_hp/ old_max;
    spell_caster->heal_hp( new_hp- old_hp );
    spell_caster->add_prop( "_live_i_sauthacuith_enhanced", 1 );

                                /*These are all who can't see the caster
                                 *excluding the caster and the target.    */
    spect_caster = FILTER_LIVE( all_inventory( environment(spell_caster) )-
        ({ spell_caster, spell_target }) );
    spect_caster = spect_caster-
        FILTER_IS_SEEN( spell_caster, spect_caster );
                                /*These are all who can't see the target
                                 *excluding the caster and the target.    */
    spect_target = FILTER_LIVE( all_inventory( environment(spell_target) )-
        ({ spell_caster, spell_target }) );
    spect_target = spect_target-
        FILTER_IS_SEEN( spell_target, spect_target );

    switch (relative_gain)
    {
    case 0..10:
        spell_caster->catch_tell( "You feel invigorated as you drain "+
            "a portion of "+ spell_target->query_the_name( spell_caster )+
            "'s life force.\n" );
        spell_target->catch_tell( "You slump slightly as you feel a bit "+
            "of your lifeforce drain out of you.\n" );
        tell_room( environment( spell_caster ), QCTNAME( spell_target )+
            " slumps slightly as "+ QTNAME( spell_caster )+ " drains "+
            "a bit of "+ QTNAME( spell_target )+ "'s lifeforce from "+
            HIM( spell_target )+ ".\n",
            ({ spell_target, spell_caster, spect_target }) );
        break;
    case 11..20:
        spell_caster->catch_tell( "You feel more vigourous as you drain "+
            "the life force from "+ spell_target->query_the_name(
            spell_caster )+ ".\n" );
        spell_target->catch_tell( "You feel weakened as "+ spell_caster->
            query_the_name( spell_target )+ " drains some of your "+
            "lifeforce from you into "+ HIM( spell_caster )+ "self!\n" );
        tell_room( environment( spell_caster ), QCTNAME( spell_target )+
            " looks weakened as "+ QTNAME( spell_caster )+ " drains "+
            "some of "+ QTNAME( spell_target )+ "'s lifeforce.\n",
            ({ spell_target, spell_caster, spect_target }) );    
        break;
    case 21..30:
        spell_caster->catch_tell( "Your eyes glow fiercely as the life "+
            "force of "+ spell_target->query_the_name( spell_caster )+
            " greatly energises your undead body.\n" );
        spell_target->catch_tell( spell_caster->query_The_name(
            spell_target )+ "'s undead eyes glow fiercely as your "+
            "lifeforce is drained into "+ HIM( spell_caster )+ "!\n" );
        tell_room( environment( spell_caster ), QCTNAME( spell_caster )+
            "'s undead eyes glow fiercely as "+ HE( spell_caster )+
            " drains the lifeforce from "+ QTNAME( spell_target )+ ".\n",
            ({ spell_target, spell_caster, spect_caster }) );
        break;
    default:
        spell_caster->catch_tell( "You exalt exuberantly the power of the "+
            "Dark Lord as you feel the immense life force of "+
            spell_target->query_the_name( spell_caster )+ " enters your "+
            "undead body.\n" );
        spell_target->catch_tell( "You helplessly watch "+ spell_target->
            query_the_name( spell_caster )+ "exulting exuberantly as "+
            HE( spell_caster )+ " drains your very soul from your body!\n"+
            "You feel greatly weakened.\n" );
        tell_room( environment( spell_caster ), QCTNAME( spell_caster )+
            " exults exuberantly the power of the Dark Lord.\n",
            ({ spell_caster, spell_target }) );
    }

    SPELL_INHERIT->log_spell( "sauthacuith", "(Caster: "+
        NAME( spell_caster )+ ") (Victim : "+ NAME( spell_target )+
        ") (Duration: "+ sauthacuith_duration+ ") (Constitution drained: "+
        con_sucked+ " ("+ relative_loss+ "%)"+ " and gained: "+ con_gained+
        " ("+ relative_gain+ "%)"+")" );

    set_alarm( itof( sauthacuith_duration ), 0.0, dispel_spell_effect );
}

/*
 * Function name : f_sauthacuith_duration
 * Description   : returns the duration of the sauthacuith spell in seconds.
 *               : It should be around 15+ (0-10) + ~5 minutes. An average
 *               : mage with guild exp == 100 with keep the bonus for about
 *               : 25 minutes. Note there is no upper limit for the duration
 *               : of this spells. A mage with SS_OCCUP == 200 may keep
 *               : extra con as long as 32 minutes.  
 * Arguments:    : int var1 - should be spell_power
 *               : int var2 - spell_caster->query_stat( SS_OCCUP )
 */
private nomask int f_sauthacuith_duration( int var1, int var2 )
{
    return 14* var1 + 4* var2 + random( 300 );
}

object *can_see_caster( object caster )
{

    return FILTER_IS_SEEN( caster,
      FILTER_PLAYERS( all_inventory( environment( caster ))) - ({caster} ));
}
