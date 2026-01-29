#include "/d/Avenir/include/steed.h"
#include "spells.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <terrain.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

inherit SPELL_INHERIT;

#define MORGUL_O_STEED            "_morgul_o_steed"
#define MORGUL_I_NO_SUMMON_STEED  "_morgul_i_no_summon_steed"

int yalarochrama_resist( object caster, object target, int element,
    int difficulty, int casting_sucess )
{
 object room, steed;

    room = environment( caster );

    if (!room->query_prop( ROOM_I_IS ) || 
        (room->query_prop( ROOM_I_INSIDE ) && 
        (file_name( room ) != AVENIR_PORT_PATH)))
    {
        return 1;
    }
    if (room->query_prop( ROOM_M_NO_TELEPORT ) || 
        room->query_prop( MORGUL_I_NO_SUMMON_STEED ))
    {
        return 2;
    }
    if ((room->query_prop( ROOM_I_TYPE ) == ROOM_UNDER_WATER) ||
        (room->terrain_includes_any( TERRAIN_UNDERWATER )))
    {
        return 3;
    }
    if (!objectp( steed = caster->query_prop( MORGUL_O_STEED ) ))
    {
        return 0;
    }    
    if (room == environment( steed ))
    {
        return 4;
    }
    return 0;
}

void move_steed( object mage )
{
 object  room = environment( mage ),
 steed = mage->query_prop( MORGUL_O_STEED );

    if (yalarochrama_resist( mage, steed, 0, 0, 0 ))
    {
        tell_object( mage, "Your winged steed tries to follow your "+
            "summons but is unable to reach you!\n" );
        if (objectp( steed ))
        {
            environment(steed)->notify_winged_steed_take_off();
            tell_room( environment( steed ), "The winged beast stretches "+
                "its pinions and flies off into the sky.\n", steed );
            steed->remove_object();
        }
        return;
    }
    if (!objectp( steed ))
    {
        setuid();
        seteuid( getuid() );
        steed = clone_object( STEED );
        IDLENESS->increase_activity( mage, RARE_SPELL );
        steed->set_owner( mage );
        mage->add_prop( MORGUL_O_STEED, steed );
    }
    steed->move_living( "M", room );
    tell_room( room,
        "With a terrible screech a huge winged leathery beast descends from the sky and lands here!\n",
        ({ steed, mage }) );
    tell_object( mage,
        "Your winged steed descends from the sky and lands here.\n" );
    room->notify_winged_steed_landing();
}

void land_announce( object mage, int i )
{
    switch (i)
    {
    case 1:
        tell_room( environment( mage ), "A dark shape, like a cloud and "+
            "yet not like a cloud, for it moves far too quickly, is "+
            "coming out of the sky, speeding towards you, blocking out "+
            "all light as it approaches.\n" );
        set_alarm( 5.0, 0.0, &land_announce( mage, 2 ) );
        environment(mage)->notify_winged_steed_approach(2);
        break;
    case 2:
    default:
        tell_room( environment( mage ), "Blind fear mixed with terror and deadly cold "+
            "embrace you as the dark shape draws nearer.\n" );
        move_steed( mage );
        environment(mage)->notify_winged_steed_approach(1);
        return;
    }
}

void resolve_spell( object caster, object *targets, int *resist,
    int success )
{
 object steed;

    if (resist[0])
    {
        switch (resist[0])
        {
        case 1:
            caster->catch_tell( "You are unable to summon your steed from "+
                "this location.\n" );
            return;
        case 2:
            caster->catch_tell( "A power greater than the Dark Lord "+
                "prevents you from summoning your winged steed.\n" );
            return;
        case 3:
            caster->catch_tell( "You are unable to summon your steed "+
                "while underwater.\n" );
            return;
        case 4:
            caster->catch_tell( "But your steed is standing right next "+
                "to you.\n" );
            return;
        }
    }
    if (check_mage( caster ))
    {
        return;
    }
    tell_room( environment( caster ), QCTNAME( caster )+ " begins to "+
        "chant in a horrible, rasping speech and gazes far into the "+
        "distant sky.\n"+ capitalize( caster->query_pronoun() )+ " lifts "+
        caster->query_possessive()+ " arms to the sky and begins a "+
        "keening wail, as if calling to something.\nFar off, storm clouds "+
        "break, and a distant figure appears in the sky.\n", caster );
    caster->catch_tell( "Using the power the Dark Lord has bestowed upon "+
        "you, you summon your winged steed with a horrible chant, wailing "+
        "the words \"Yala roch rama\" over and over again. Far off, storm "+
        "clouds break, and a distant figure appears in the sky.\n" );
    set_alarm( itof( random( 40 )+ 10 ), 0.0, &land_announce( caster, 1 ) );

    if (objectp( steed = caster->query_prop( MORGUL_O_STEED ) ) &&
        environment( steed )->query_prop( ROOM_I_IS ))
    {
        environment(steed)->notify_winged_steed_take_off();
        tell_room( environment( steed ), "The winged beast stretches its "+ 
            "pinions and flies off into the sky.\n", steed );
        steed->move_living( "M", STEED_ROOM );
    }
}
    
int
config_spell(object caster, object *targets, string args)
{
    set_spell_name( "yalarochrama" );
    set_spell_desc( "Summon a winged steed." );
    set_spell_target( spell_target_caster );
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
    if (caster->query_wiz_level())
    {
        set_spell_ingredients(0);
    }
    else
    {
        set_spell_ingredients( ({ "snake skin", "_gem_ingredient" }) );
    }
    set_spell_time( 10 );
    set_spell_mana( 200 );
    set_spell_task( TASK_ROUTINE );
    set_spell_element( SS_ELEMENT_AIR, 40 );
    set_spell_form( SS_FORM_CONJURATION, 80 );
    set_spell_resist( yalarochrama_resist );
    set_spell_peaceful( 0 );
    set_spell_stationary( 1 );
    set_spell_visual( 0 );
    return 0;
}
