#pragma save_binary
#pragma strict_types

#include "spells.h"
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <terrain.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()
#define HIM(x)  (x)->query_objective()
#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())

inherit SPELL_INHERIT;

int glimpse;

private nomask int f_crabandir_duration( int var1, int var2 );

public void
send_craban( object tp, int result, object craban )
{
 object  paralyze, crabandir_sh;

    paralyze = clone_object(
        "/d/Gondor/common/guild2/newspells/obj/crabandir_paralyze" );
    paralyze->set_stop_fun( "remove_craban" );
    paralyze->set_stop_object( craban );
    paralyze->set_stop_message( "You are in control of your undead body "+
        "again.\n" );
    paralyze->set_fail_message( "You can only watch through the eyes of "+
        "the craban, but you have no control over it.\nYou can steer your "+
        "awareness back to your undead body by using the command "+
        "\"peluvo\".\n");
    paralyze->set_stop_verb( "peluvo" );
                                /*Play it safe, add a remove time, even
                                 *though the effect should be ended through
                                 *the alarm in the craban.                */
    paralyze->set_remove_time( result );

    craban->set_paralyze( paralyze );
    craban->set_mage( tp );
    tell_room( environment( tp ), QCTNAME( tp )+ " slumps to the ground.\n"+
        capitalize( HIS( tp ) )+ " undead body is like an empty vessel, "+
        "left behind by a spirit that departed elsewhere.\n", 
        ({ tp, craban }), tp );
    tp->catch_tell( "Your awareness enters the craban which you summoned."+
        "\nYou lose the control over your undead body and start seeing "+
        "with the eyes of the craban.\n" );
    paralyze->move( tp, 1 );
    crabandir_sh = clone_object( CRABANDIR_SH );
    crabandir_sh->shadow_me( tp );
    crabandir_sh->set_puppet( craban );
    craban->set_crabandir_sh( crabandir_sh );
    craban->start_watch();
    IDLENESS->increase_activity( tp, COMBAT_SPELL );
}

public void
move_craban( object tp, object target, int result )
{
 object craban,
 env = environment( tp );

    setuid();
    seteuid( getuid() );
    craban = clone_object( (SPELL_OBJ_DIR + "craban") );
    craban->set_target( target );
    craban->set_duration( result );
    tell_room(env, "A dark cloud appears out of nowhere.\n"
      + "Out of the cloud flies "+ LANG_ADDART( craban->short() )+ ".\n"
      + "The "+ craban->short()+ " lands on the ground, "
      + "and the cloud disappears again.\n" );
    craban->move_living( "M", env );
    craban->command( "emote croaks harshly." );
    set_alarm( 5.0, 0.0, &send_craban( tp, result, craban ) );
}

void
resolve_spell( object caster, object *targets, int *resist, int result )
{
 int duration, spell_power;

    if (check_mage( caster ))
    {
        return;
    }
    spell_power = ( caster->query_skill( gElement_skill )+ caster->
        query_skill( gForm_skill )+ gElement_needed+ gForm_needed )/ 4;
    duration = f_crabandir_duration( spell_power,
        caster->query_stat( SS_OCCUP ));

    set_alarm( 5.0, 0.0, &move_craban( caster, targets[0], duration ) );

    tell_room( environment( caster ), "Employing Dark Sorcery, "+ 
        QTNAME( caster )+ " summons a winged servant from the realm of "+
        "shadows.\n"+ capitalize( HE( caster ) )+ " takes something and "+
        "places it in "+ HIS( caster )+ " right hand, extending it "+
        "skyward, as if beckoning something.\n", caster );
    caster->catch_tell( "Using the power the Dark Lord has bestowed upon "+
        "you, you summon one of the crebain to spy on "+ targets[0]->
        query_name()+ " for you. Taking your berry in your right hand and "+
        "extending it skyward, you beckon your servant with the words "+
        "\"Yalanlye craban! Gimo nin kweth a telo!\"\n" );
}

object *
spell_target_craban( object caster, string str )
{
 object living, env;

    if (!strlen( str ))
    {
        caster->catch_tell( "Target whom?\n" );
        return ({});
    }
    if (environment( caster )->query_prop( ROOM_I_INSIDE ))
    {
        caster->catch_tell( "You are not outdoors. Your craban may find "+
            "it hard to find a way out.\n" );
        return ({});
    }
    living = find_living( str );

    if (!objectp( living ) || living->query_invis())
    {
        caster->catch_tell( "You do not sense "+ LANG_POSS( str )+
            " presence in the realms.\n" );
        return ({});
    }
    if (living->query_wiz_level() && !caster->query_wiz_level())
    {
        caster->catch_tell( "You don't dare spy on "+ str+ ".\n" );
        return ({});
    }
    return ({ living });
}

public varargs int
config_spell( object caster, object *targets, string argument )
{
    set_spell_name( "crabandir" );
    set_spell_desc( "Summon a craban to spy on someone." );
    set_spell_target( spell_target_craban );
                                /*The spell is not being configured for   *
                                 *a casting attempt, and therefore should *
                                 *not return 1                            */
    if (!objectp( caster ))
    {
        return 0;
    }

    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    set_spell_time(spell_resolve_time( caster->query_stat(SS_OCCUP),9,20 ));
    set_spell_mana( 100 );
    set_spell_peaceful( 1 );
    set_spell_task( TASK_ROUTINE- 100 );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        if (parse_command( "crabandir_ingr2", all_inventory(caster), "%o" ))
        {
            set_spell_ingredients( ({ "crabandir_ingr1",
                "crabandir_ingr2" }) );
            glimpse = 0;
        }
        else
        {
            set_spell_ingredients( ({ "crabandir_ingr1" }) );
            glimpse = 1;
        }
    }
    set_spell_element( SS_ELEMENT_DEATH, 60 );
    set_spell_form( SS_FORM_CONJURATION, 50 );
    set_spell_resist( 0 );
    return 0;
}

private nomask int f_crabandir_duration( int var1, int var2 )
{
    if (glimpse)
    {
        return 60+ random( 60 );
    }
    return 300+ 8* var1 + 5* var2 + random( 300 );
}
