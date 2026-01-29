/*
 * /d/Gondor/common/guild2/newspells/naro.c
 *
 * Modification log:
 * Gwyneth 11/16/02 - Changed fatigue drain to stuffed drain per
 *                    Goldberry's orders.
 */
#include "spells.h"
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

inherit SPELL_RESIST;
inherit SPELL_INHERIT;

#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()
#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())

int Spell_level = 0;
nomask string *count_naro_optional_ingredients( object caster );

object *spell_target_naro( object caster, string str )
{
 string str1, str2;
 object target1 = 0, target2 = 0, *T1;

    if (environment( caster )->query_prop( ROOM_M_NO_ATTACK ))
    {
        caster->catch_tell( "The powers stronger then the Eye consider "+
            "this spell too offensive to cast it here!"+ "\n" );
        return ({});
    }
    if (!strlen( str ))
    {
        caster->catch_tell( "Whom do you wish to cast on?\n" );
        return ({});
    }
    if (sscanf( str, "%s drego %s", str1, str2 ))
    {
        Spell_level = 1;
        if (str2 == "nin!" || str2 == "nin")
        {
            return ::spell_target_one_other_present_living( caster, str1 );
        }
        caster->catch_tell( "Command your victim to do what?\n" );
        return ({ });
    }
    if (sscanf(str, "%s libo %s", str1, str2))
    {
        Spell_level = 2;
        if (str2 == "makil!" || str2 == "makil")
        {
            return ::spell_target_one_other_present_living( caster, str1 );
        }
        caster->catch_tell( "Command your victim to do what?\n" );
        return ({ });
    }
    if (sscanf( str, "%s maetho %s", str1, str2) )
    {
        Spell_level = 3;
        T1 = ::spell_target_one_other_present_living( caster, str1 );
        if (sizeof( T1 ))
        {
            target1 = T1[0];
        }
        T1 = ::spell_target_one_other_present_living( caster, str2 );
        if (sizeof( T1 ))
        {
            target2 = T1[0];
        }
        if (!objectp( target1  ) || !objectp( target2  ))
        {
            caster->catch_tell( "Cast naro <target> maetho <target>\n" );
            return ({});
        }
        if (target1 == target2)
        {
            caster->catch_tell( "You can not command "+
                target1->query_the_name(caster)+ " to attack itself.\n" );
            return ({ });
        }
        return (({ target1, target2 }));
    }
    caster->catch_tell( "Command your victim to do what?\n" );
    return ({ });
}

mixed do_drego( object caster, object target )
{
 object *doors, room, cobj, naro_ob;
 string *wdir;
 int i, stuff, eat;

    caster->catch_tell( "Peering deeply into the eyes of "+ 
        target->query_the_name( caster )+ " you command: Drego nin!\n"+
        "Trembling in fear and panic, "+ HE( target )+ " runs away!\n" );
    target->catch_tell( "Staring deeply into your eyes with eyes burning "+
        "like red coals, "+ caster->query_the_name( target)+ " tells you: "+
        "Drego nin!\nYou do not understand what the words mean, but you "+
        "are filled with fear and panic and try to run away.\n" );
    tell_room( environment( caster ), QCTNAME( caster )+ " stares "+
        "threateningly into the eyes of "+ QTNAME( target )+ ", rasping "+
        "the words: Drego nin!\n"+ QCTNAME( target )+ " starts to tremble "+
        "and then runs away in panic.\n", ({ caster, target, }) );

    target->run_away();
    target->
        set_whimpy( MIN( MAX(25, target->query_whimpy()* 150/ 100), 100) );
    target->add_panic( random( caster->query_stat( SS_DIS ) )+
        caster->query_stat( SS_OCCUP ));

    if (environment( caster ) == (room = environment(target)))
    {
        wdir = room->query_exit_cmds();
        if (sizeof( doors = filter(all_inventory(room), &operator(==)
            (DOOR_OBJECT) @ &function_exists("create_object", )) ))
        {
            for (i=0;i<sizeof(doors);i++)
            {
                wdir += doors[i]->query_pass_command();
            }
        }
        cobj = target->query_combat_object();
        if ((objectp( cobj )) && (sizeof( wdir )))
        {
            cobj->cb_run_away( wdir[random( sizeof( wdir ) )] );
        }
    }

    if (environment( target ) == environment( caster ))
    {
        tell_room( environment( caster ), "Sick and panicked, "+
            QTNAME( target )+ " falls down on the ground.\n", target );
        target->catch_tell( "Sick and panicked even more, you fall "+
            "down on the ground" );
        target->command("$puke");
        target->add_panic( random( caster->query_stat( SS_DIS ) )+
            caster->query_stat( SS_OCCUP )- target->query_stat( SS_DIS ));
        stuff = target->query_stuffed();
        eat = (-15 * caster->query_stat( SS_OCCUP ));
        eat = (-eat > stuff ? -stuff : eat);
        target->eat_food( eat );
    }
    else if (target->query_npc())
    {
        setuid();
        seteuid( getuid() );
        naro_ob = clone_object( SPELL_OBJ_DIR + "naro_drego_ob" );
        naro_ob->set_from_room( environment( caster ) );
        naro_ob->move_back_with_delay( caster, random(100) + 200 );
        naro_ob->move( target, 1 );
    }
/* I decided I have enough statistics acumulated and won't log attacks
 * against npcs any more.
    log_spell( "naro", "DREGO   Caster: ("+ NAME( caster )+ ") Target: ("+
        NAME(target)+ ") Environment: ("+ file_name(environment( caster ))+
        ")" );
 */
    if (!(target->query_npc()))
    {
        log_spell( "naro", "DREGO   Caster: ("+ caster->query_cap_name()+
            ") Target: ("+ target->query_cap_name()+ ") Environment: ("+
            file_name( environment( caster ) )+ ")" );
    }
    IDLENESS->increase_activity( caster, COMBAT_SPELL );
}

void do_libo( object caster, object target, int result )
{
 object weapon;
 int res;

    caster->catch_tell( "You raise your hand, menacing "+ 
        target->query_the_name( caster )+ ", and command: Libo makil!\n"+
        target->query_The_name( caster )+ " seems striken dumb, "+ 
        HIS( target )+ " chest heaving heavily.\n" );
    target->catch_tell( caster->query_The_name( target )+ " raises "+ 
        HIS( caster )+ " hand, menacing at you, and commands: "+
        "Libo makil!\nYou fail to understand the words, but you are "+
        "striken dumb.\nYou feel your tongue cleave to your mouth, and "+
        "your heart labouring.\n" );
    tell_room( environment( caster ), QCTNAME( caster )+ " raises "+ 
        HIS( caster )+ " hand, "+ "menacing at "+ QTNAME(target)+
        ", and commands: Libo makil!\n"+ QCTNAME(target)+ " seems striken "+
        "dumb, "+ HIS( target )+ " chest heaving heavily.\n",
        ({ caster, target}) );

    if (!sizeof( target->query_weapon( -1 ) ))
    {
        return;
    }
    weapon = target->query_weapon( -1 )
        [random(sizeof( target->query_weapon( -1 ) ))];

    if (weapon->query_prop( OBJ_I_IS_MAGIC_WEAPON ))
    {
        res = weapon_spell_resist( caster, weapon,
            SS_ELEMENT_DEATH, TASK_DIFFICULT );
        if (res >= random( 100 ))
        {
            caster->catch_tell( target->query_The_possessive_name( caster )+
                " " + weapon->short() + " resists the effects of your "+
                "spell entirely!\n" );
            log_spell( "naro", "LIBO:  Weapon "+ file_name( weapon )+ 
                " resists spell.   Caster: ("+ caster->query_cap_name()+
                ")" );
            IDLENESS->increase_activity( this_player(), SMALL_SPELL );
            return;
        }
        weapon->set_dull( weapon->query_dull() + random( 2 ) + 1 );
        weapon->set_corroded( weapon->query_corroded() + random( 3 ) + 2 );
        caster->catch_tell( target->query_The_possessive_name( caster )+
            " "+ weapon->short()+ " is left damaged and heavily "+
            "corroded by your spell.\n" );
        target->catch_tell( "Your "+ weapon->short()+ " is left damaged "+
            " and heavily corroded by "+ caster->query_the_possessive_name()+
              " spell.\n" );
    }
    else
    {
        weapon->remove_broken();
        target->command( "$drop "+ OB_NAME( weapon ) );
    }
                                /*If a mage breaks player's weapon, that
                                 *player will attack a mage.               */
    if (!(target->query_npc()))
    {
        if (this_player()->check_seen( target ))
        {
            tell_object( target, "Filled with grief and blinded by "+
                "the anger you rush toward " +
                this_player()->query_the_name( target ) + ".\n");
            tell_room( environment( this_player() ), QCTNAME( target )+
                " suddenly rushes toward " + QCNAME( this_player() )+ ".\n",
                ({this_player(), target}) );
        }
        else
        {
            tell_object( target, "Filled with grief and blinded by "+
                "the anger you rush toward the source of voice.\n");
            tell_room( environment( this_player() ), QCTNAME( target ) +
                " suddenly rushes toward the source of voice.\n",
                ({this_player(), target}) );
        }
        tell_object( this_player(),
            target->query_The_name( this_player() ) +
            " suddenly rushes in your direction.\n" );
        target->attack_object( this_player() );
        log_spell( "naro", "LIBO: Caster: ("+ caster->query_cap_name()+
            ")  Target: ("+ target->query_cap_name()+ ") Weapon: ("+
            file_name(weapon)+ ") "+ (weapon->query_prop( OBJ_I_BROKEN ) ?
            "BROKE" : "DAMAGED") );
    }
/*
 * I stoped logging attacks against npcs so the procedure has been moved
 * into the above if check,
 */
        IDLENESS->increase_activity( caster, COMBAT_SPELL );
}

void
do_maetho( object caster, object target, object victim )
{
    caster->catch_tell( "You peer deeply into the eyes of "+ 
        target->query_the_name(caster)+ " and pointing at "+ 
        victim->query_the_name(caster)+ ", you command: "+
        "Maetho!\nActing like a possessed creature, "+
        target->query_the_name(caster)+ " turns to attack "+
        victim->query_the_name(caster)+ "!\n" );
    target->catch_tell( "Staring deeply into your eyes with eyes burning "+
        "like red coals, "+ caster->query_the_name(target)+ " points at "+
        victim->query_the_name(target)+ " and tells you: Maetho!\nYou do "+
        "not understand what the word means, but feeling as if you are "+
        "possessed and you turn to attack "+ victim->query_the_name(target)+
        "!\n" );
    victim->catch_tell( caster->query_The_name(victim)+ " stares "+
        "threateningly into the eyes of "+ target->query_the_name(victim)+
        ", and pointing at you rasps the word: Maetho!\nActing like a "+
        "possessed creature, "+ target->query_the_name(victim)+
        " turns to attack you!\n" );
    tell_room( environment(caster), QCTNAME(caster)+ " stares "+
        "threateningly into the eyes of "+ QTNAME(target)+ ", and pointing "+
        "at "+ QTNAME(victim)+ " rasps the word: Maetho!\nActing like a "+
        "possessed creature, "+ QTNAME(target)+ " turns to attack "+ 
        QTNAME(victim)+ "!\n", ({ caster, target, victim, }) );
    if (interactive( target ))
    {
        target->add_prop( LIVE_O_LAST_KILL, victim );
    }
    target->attack_object( victim );
/* I decided I have enough statistics acumulated and won't log attacks
 * against npcs any more.
    log_spell( "naro", "MAETHO:  Caster: ("+ caster->query_cap_name()+ 
        ")  Target: ("+ NAME( target )+ ") attacks "+ NAME( victim ) );
 */
    if (!(target->query_npc()) || !(victim->query_npc()))
    {
        log_spell( "naro", "MAETHO:  Caster: ("+ caster->query_cap_name()+ 
            ")  Target: ("+ NAME( target )+ ") attacks "+ NAME( victim ) );
    }
    IDLENESS->increase_activity( caster, RARE_SPELL );
}

void
resolve_spell( object caster, object *targets, int *resist, int result )
{
    if (check_mage( caster ))
    {
        return;
    }

    if (resist[0] >= random( 100 ))
    {
        caster->catch_tell( "Your spell has been resisted.\n" );
        return;
    }
    targets[0]->catch_tell( caster->query_The_name( targets[0] )+
        " looks at you with burning eyes, trying to control your will.\n" );
    caster->catch_tell( "You look deep into the eyes of "+ 
        targets[0]->query_the_name(caster)+ " trying to control "+ 
        HIS( targets[0] )+ " will with the power that the Dark Lord has "+
        "bestowed upon you!\n" );
    switch (Spell_level)
    {
    case 1:
        do_drego( caster, targets[0] );
        break;
    case 2:
        do_libo( caster, targets[0], result );
        break;
    case 3:
        do_maetho( caster, targets[0], targets[1] );
        break;
    }
}

/*
 * Function:    get_naro_component_name
 * Description: Used to calculate the names of the naro component in
 *              count_naro_optional_ingredients. This function should return
 *              the proper name of the naro component. It specifically handles
 *              heaps additionally.
 */
public string *
get_naro_component_name(object obj)
{
    if (!objectp(obj))
    {
        return ({ });
    }
    
    string * component_names = ({"_leftover_skull", "naro_ingr2", "naro_ingr3"});
    foreach (string name : component_names)
    {
        if (obj->id(name))
        {
            int num_additions = 1; // by default, add it once
            // We need to add the name the number of times of the heap size
            if (IS_HEAP_OBJECT(obj))
            {
                num_additions = obj->num_heap();
            }
            string * naro_names = ({ });
            for (int i = 0; i < num_additions; ++i)
            {
                naro_names += ({ name });
            }
            return naro_names;
        }
    }
    return ({ });    
}

/*
 * Function name: count_naro_optional_ingredients
 * Description  : This function checks which of the default naro
 *                components are ready for spellcasting. The outcome
 *                is later used to calculated the task difficulty and
 *                to set spell ingredients.
 * Return values: An array of names of components found.
 */
nomask string * count_naro_optional_ingredients( object caster )
{
    object * candidate_ingredients = filter(get_item_search_list(caster), &filter_components(, caster));
    string * found_naro_ingredients = ({ });
    foreach (object item : candidate_ingredients)
    {
        found_naro_ingredients += get_naro_component_name(item);
        if (sizeof(found_naro_ingredients) > 3)
        {
            break;
        }
    }
    // We limit the maximum number of ingredients returned to be 3. This goes into the
    // calculation of the spell task.
    if (sizeof(found_naro_ingredients) > 3)
    {
        return found_naro_ingredients[0..2];
    }
    return found_naro_ingredients;
}
/*
 int i, j;
 string *default_component_list = ({"_leftover_skull", "naro_ingr2", "naro_ingr3"});
 string *found_naro_ingredients = ({});
 object *itemlist, *items;
 
    itemlist = get_item_search_list( caster );
    i = sizeof( default_component_list );
    while (i--)
    {
        if (parse_command(default_component_list[i], itemlist, "%i", items))
        {
            items = filter(items[1..], &filter_components(, caster));
            if (sizeof( items ))
            {
                found_naro_ingredients += ({ default_component_list[i] });
            }
        }
    }
    return found_naro_ingredients;
}
*/

public varargs int
config_spell( object caster, object *targets, string argument )
{
 int nr_of_naro_ingr, guild_level;
 string *naro_ingredients;

    set_spell_name( "naro" );
    set_spell_desc( "Command others to do your bidding." );
    set_spell_target( spell_target_naro );
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
    guild_level = (caster->query_wiz_level() ? 25 :
        caster->query_morgul_level());

    switch (Spell_level)
    {
    case 3:
        if (guild_level < MS_NARO3_MIN)
        {
            caster->catch_tell( "The Dark Lord didn't grant you the power "+
                "to command 'maetho'!\n" );
            return 1;
        }
    case 2:
        if (guild_level < MS_NARO2_MIN)
        {
            caster->catch_tell( "The Dark Lord didn't grant you the power "+
                "to command 'libo makil'!\n" );
            return 1;
        }
    }

    naro_ingredients = count_naro_optional_ingredients(  caster );
    nr_of_naro_ingr =  sizeof( naro_ingredients );
    
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
        set_spell_task( TASK_SIMPLE );
        caster->catch_tell("Nr. of ingredients: "+ nr_of_naro_ingr+ ".\n" );
    }
    else
    {
        set_spell_ingredients( naro_ingredients );
        if (nr_of_naro_ingr == 0)
        {
            set_spell_task( Spell_level* TASK_DIFFICULT );
        }
        else
        {
            set_spell_task( (300* Spell_level)* (4-nr_of_naro_ingr)/ 3 );
        }
    }
    set_spell_time( max(spell_resolve_time( caster->query_stat( SS_OCCUP ),
        2+ Spell_level, 6+ Spell_level ), COMBAT_SPELL_I_MIN_PREP_TIME) );
    set_spell_mana( 15* Spell_level );

// There was 57 and 54 respectively 
    set_spell_element( SS_ELEMENT_DEATH, 12+ 15* Spell_level );
    set_spell_form( SS_FORM_ENCHANTMENT, 9+ 15* Spell_level );
    set_spell_resist( spell_resist );
    set_spell_peaceful( 1 );
    return 0;
}
