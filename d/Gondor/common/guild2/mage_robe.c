/* 
 *    /d/Gondor/common/guild2/mage_robe.c
 *
 *    The robe of the Mogul Mages
 *    modified from the ranger ring
 *
 *    Olorin, 05-jan-1994
 *
 *    Copyright (c) 1996, 1997 by Christian Markus (Olorin)
 *
 *    Modification log:
 *  05.07.2001 Chmee: support for artirith.
 *  27.05.2002 Chmee: spell_obj functionality enclosed in this object.
 *  01.12.2006 Toby : Changed the v/vital look for the Mages
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/std/armour.c";
inherit "/d/Genesis/newmagic/spellcasting";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "lib/morgul_defs.h"
#include "newspells/spells.h"

#define HIS(x)    (x)->query_possessive()

/*
 *      Global variables:
 */
static object Shadow, Robe_owner;
static int Removed_flag = 1;

public int valid_owner();
private void remove_morgul_spells( int how = 0);
private void add_morgul_spells();

/* For the v/vitals */
#include <time.h>
#include <formulas.h>
#include <state_desc.h>

private string *enc_weight =   SD_ENC_WEIGHT,
               *health_state = SD_HEALTH, 
               *intox_state =  SD_INTOX, 
               *mana_state =   SD_MANA, 
               *soak_state =   ({ "quite a lot more", "a lot more", "some more", "a little more",
                                  "just barely a little bit more" }), 
               *stuff_state =  ({ "quite a lot more", "a lot more", "some more", "a little more",
                                  "just barely a little bit more" });


/*     These are the original defines but they have eat and drink in them and 
       that ruins the string for the Society, thus the own defines.

       soak_state =   SD_SOAK;
       stuff_state =  SD_STUFF;

       End v/vitals defines 
*/

public int query_value()
{
    return 0;
}

/*
 * Function name: create_armour
 * Description:   Creator.
 */
public void create_armour()
{
    set_name( ({ "robe", "cloak" }) );
    add_name( ({ "morgul_guild_object", "token", "guild token", 
        "mage token", "morgul token", "Morgul_Spell_Object" }) );
    set_adj( ({"large", "black", "hooded"}) );
    set_short( "black hooded robe" );
    set_long( "This is a large black robe, with a wide hood. You sense "+
        "a great yet dark power emanating from it.\n" );
    add_item( ({"hood", "wide hood", }), "When worn over the head "
        + "the wide hood of the robe will hide the features of the "
        + "person wearing the robe.\n" );
    set_ac( 1 );
    set_af( this_object() );
    set_at( A_ROBE );
    set_likely_break( 1 );
    add_prop( OBJ_I_VALUE,     0 );
    add_prop( OBJ_I_WEIGHT, 1200 );
    add_prop( OBJ_I_VOLUME,  650 );
    add_prop( OBJ_I_NO_DROP,   1 );

    /* This looseness allows the cloak to be worn over other cloaks
       of standard layers of 4. These layers make sure that one
       can't wear two ranger cloaks at the same time. */
    set_looseness(20);
    set_layers(1);

    setuid();
    seteuid( getuid() );
}

/*
 * Function name : remove
 * Description   : The remove function for the robe. It also load the morgul
 *               : spells.
 * Argument      :      ob - object pointer to the robe
 * Returns       : int  0 - No effect, the armour can be removed
 *                      1 - It can be removed but no text should be
 *                          printed (it was done in the function)
 *                     -1 - It can not be removed, default failmsg will
 *                          be written 
 *                 string - It cannot be removed, 'string' is the fail
 *                          message to print 
 */
public mixed remove( object ob )
{
    if (ob != this_object())
    {
        return -1;
    }
 
    Shadow->remove_shadow();
    Shadow = 0;

    remove_morgul_spells( 1 );
    return 0;
}

/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_af().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed wear( object ob )
{
 object user;
    
    user = this_player();

    if (ob != this_object())
    {
        return -1;
    }
    if (valid_owner())
    {
        write( "You wear the "+ query_short()+ " around your body.\n" );
        say( QCTNAME( user )+ " wears "+ LANG_ASHORT( this_object() )+
            ".\n");

        add_morgul_spells();
        Robe_owner = user;
        return 1;
    }

    user->heal_hp( -(user->query_max_hp()/ 20) );
    say( "As "+ QCTNAME( user )+ " tries to wear the "+ query_short()+
        ", it bursts out in flames and disappears.\n" );
    return "When you try to wear the "+ query_short()+
        ", it bursts out in flames and disappears.\n";
    remove_object();
}

private void add_morgul_spells()
{
 object user;
 int guild_level;
 	
    user = this_player();

    guild_level = (user->query_wiz_level() ? 25 :
        user->query_morgul_level());
    if (guild_level >= MS_YALAR_MIN-1)
    {
        guild_level = MS_YALAR_MIN;
    }
    add_spell_object( user );
    
                                   /*Make sure that every guild level has
                                 *its case here.*/
    switch (guild_level)
    {
    case MS_YALAR_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "yalarochrama" ) );
    case MS_SULAM_MIN..(MS_YALAR_MIN-1):
        add_spell( clone_object( MORGUL_SPELL_DIR+ "sulambar" ) );
    case MS_MORTH_MIN..(MS_SULAM_MIN-1):
        add_spell( clone_object( MORGUL_SPELL_DIR+ "morthul" ) );
    case MS_CRABA_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "crabandir" ) );
    case MS_ARTIR_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "artirith" ) );
    case MS_GOSTA_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "gostangwedh" ) );
    case MS_NIFAR_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "nifarist" ) );
    case MS_THUNA_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "thunaur" ) );
    case MS_EPHES_MIN..(MS_THUNA_MIN-1):
        add_spell( clone_object( MORGUL_SPELL_DIR+ "ephessul" ) );
    case MS_DOLLO_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "dollost" ) );
    case MS_NARUS_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "narusse" ) );
    case MS_RINGU_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "ringurth" ) );
    case MS_SAUTH_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "sauthacuith" ) );
    case MS_FAUGO_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "faugoroth" ) );
    case MS_DRAMA_MIN..(MS_FAUGO_MIN-1):
        add_spell( clone_object( MORGUL_SPELL_DIR+ "dramalgos" ) );
    case MS_ARHAL_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "arhalgul" ) );
    case MS_NARO1_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "naro" ) );
    case MS_OREKI_MIN:
        {
            add_spell( clone_object( MORGUL_SPELL_DIR+ "mortirio" ) );
            add_spell( clone_object( MORGUL_SPELL_DIR+ "orekir" ) );
        }
    case MS_MORTI_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "mortirio" ) );
    case MS_PALAN_MIN:
        add_spell( clone_object( MORGUL_SPELL_DIR+ "palanquendo" ) );
    }
    write( "You feel the dark power of Black Sorcery flowing through "+
        "you.\n" );
    Removed_flag = 0;
    return;
}

/*
 * Function    : remove_morgul_spells
 * Description : This functions basicaly removes the spells from a mage
 * Arguments   : int how = 1 - skip the Removed_flag check (force the
 *             : removal).
 */
private void remove_morgul_spells( int how = 0)
{
 mixed *mm_spell_objects, *mm_spell_names;
 int i, j;

                                /*The safety reasons may create a preasure
                                 *to call this function too often what may
                                 *reveal to be CPU consuming. One can still
                                 *call it with force.                      */
    if (!how)
    {
        if (Removed_flag)
        {
            return;
        }
    }

    if (!Removed_flag)
    {
        if (objectp( Robe_owner ))
        {
            Robe_owner->catch_tell( "As you remove the black hooded robe, "+
                "you feel the dark power of Black Sorcery dissipate.\n" );
        }
        Removed_flag = 1;
                                /*Several morgul spells control their
                                  duration time internally. Since the spell
                                  copies are now being destructed make
                                  sure the spells effect is terminated.
                                  Otherwise the relevant alarm will
                                  fire at void and the spell effect
                                  becomes permanent!                      */
        if (Robe_owner->query_morgul_invis())
        {
            Robe_owner->dispel_artirith( Robe_owner );
        }
        
    }

    mm_spell_objects = m_values( query_spell_map() );
                                /*You can use m_indices() too if you are an
                                 *english language purist ;-)             */
    mm_spell_names = m_indexes( query_spell_map() );

    j = sizeof( mm_spell_objects );
    for (i=0;i<j;i++)
    {
        if (objectp( mm_spell_objects[i] ))
        {
            mm_spell_objects[i]->remove_object();
        }
        remove_spell( mm_spell_names[i] );
    }
    if (objectp( Robe_owner ))
    {
        remove_spell_object( Robe_owner );
    }
    return;
}

/* 
 * Function name: init_arg
 * Description  : Called when autoloading.
 * Arguments    : string arg - the auto-load argument.
 */
public varargs void init_arg( string str )
{
    if (valid_owner())
    {
        write( "The "+ query_short()+ " materializes in your inventory.\n");
    }
    else
    {
        write( "The "+ query_short()+ " bursts out in flames and "+
            "disappears!\n" );
        remove_object();
    }
    return;
}

/*
 * Function name: valid_owner
 * Description  : Checks whether the owner has the rights to this robe
 */
public int valid_owner()
{
 object user, another_robe;

    user = this_player();
    another_robe = present( "Morgul_Spell_Object", user );

                                /*You are not a valid owner if:
                                 *you are not a mage AND not a wizard
                                 *OR you already have another robe.       */
    if ((user->query_guild_name_occ() != GUILD_NAME) &&
        (!user->query_wiz_level()) ||
        (this_object() != another_robe) &&
        (another_robe != 0))
    {
        return 0;
    }
    return 1;
}

/*
 * Function name: query_recover
 * Description  : no recovery, since the robe autoloads
 * Returns      : 0
 */
public string query_recover()
{
    return 0;
}

/*
 * Function name: leave_env
 * Description:   remove the hood shadow if the robe leaves its
 *                environment 
 * Arguments:     from - old environment, to - new environment
 */
public void
leave_env( object from, object to )
{
    if (objectp( from ) && from->query_hooded())
    {
        Shadow->remove_shadow();
    }

    ::leave_env( from, to );
                                /*Call this via alarm otherwise you will
                                 *get an endless recurency.               */
    set_alarm( 0.1, 0.0, remove_object );
}

void
remove_object()
{
    remove_morgul_spells();
    ::remove_object();
}

/*
 * Function name : do_hood
 * Description   : wear the hood
 * Argument      : command verb argument
 * Returns       : 1/0
 */
public int do_hood( string str )
{
 object holder, user;
 string  vb, pron;

    vb = query_verb();
    if (vb == "hood")
    {
        pron = "whom";
    }
    else
    {
        pron = "what";
    }
    notify_fail( capitalize( vb )+ " "+ pron+ "?\n" );
    if (!strlen( str ))
    {
        return 0;
    }

    holder = environment( this_object() );
    user = this_player();

    if ((vb == "hood") && ((str != "me") && (lower_case( str ) !=
        holder->query_real_name())))
    {
        return 0;
    }
    if ((vb == "wear") && (str != "hood"))
    {
        return 0;
    }
    if (holder != user)
    {
        notify_fail( "You do not have the robe!\n" );
        return 0;
    }
    if (query_worn() != user)
    {
        notify_fail( "You do not wear your robe!\n" );
        return 0;
    }
    if (user->query_mm_mounted())
    {
        notify_fail("You are too busy riding to hood yourself.\n");
        return 0;
    }
    if (user->query_hooded())
    {
        notify_fail( "You are already wearing your hood!\n" );
        return 0;
    }

    write( "You pull the hood of your robe over your head, concealing "+
        "your features.\n" );
    say( QCTNAME( user )+ " pulls the hood of "+ HIS( user )+ " robe over "+
        HIS( user )+ " head, concealing "+ HIS( user )+ " features.\n" );

    Shadow = clone_object( GUILD_DIR+ "obj/hood_shadow" );
    Shadow->shadow_me( user );
    return 1;
}

/*
 * Function name: do_reveal
 * Description:   remove the hood
 * Argument:      str - argument
 *                silent - write no message if 1
 * Returns:       1/0
 */
public int do_reveal( string str, int silent = 0 )
{
 object holder, user;
 string  vb, pron;

    vb = query_verb();
    switch (vb)
    {
    case "unhood":
    case "reveal":
        pron = "whom";
        break;
    case "mreveal":
        vb = "remove";
    case "remove":
        pron = "what";
        break;
    }

    holder = environment( this_object() );
    user = this_player();
    notify_fail( capitalize( vb )+ " "+ pron+ "?\n" );
    if (!strlen( str ))
    {
        return 0;
    }
    switch (vb)
    {
    case "unhood":
        if (str == "me")
        {
            break;
        }
        if (lower_case( str ) == holder->query_real_name())
        {
            break;
        }
        notify_fail( "You can only remove your own hood!\n" );
        return 0;
        break;
    case "reveal":
        if (str == "me")
        {
            break;
        }
        if (lower_case( str ) == holder->query_real_name())
        {
            break;
        }
        return 0;
        break;
    case "remove":
        if (str != "hood")
        {
            return 0;
        }
        break;
    }

    if (holder != user)
    {
        notify_fail( "You do not have the robe!\n" );
        return 0;
    }

    if (!user->query_hooded())
    {
        notify_fail( "You are not wearing your hood!\n" );
        return 0;
    }

    if (user->query_mm_mounted())
    {
        write("You are too busy riding to remove your hood.\n");
        return 1;
    }

    if (!silent)
    {
        write( "You remove the hood and reveal your face again.\n" );
        say( QCTNAME( user )+ " removes "+ HIS( user )+ " hood.\n" );
    }

    Shadow->remove_hood_shadow();
    return 1;
}

/*
 * Function name: etendae
 * Description  : A support to the artirith spell.
 * Argument     : A command line (everything typed after the command word)
 * Returns      : Success 1 or failure 0
 */
private nomask int etendae( string str )
{
 object user;
 
    if (strlen( str ) > 0)
    {
        return 0;
    }

    user = this_player();
    if (user->query_morgul_invis())
    {
        user->dispel_artirith( Robe_owner );
        return 1;
    }
    else
    {
        write( "You are not in the realm of shadows.\n" );
        return 1;
    }
}

/*
 * Function name: do_burn
 * Description  : Destroys this robe (if bugged for example).
 * Argument     : A command line (everything typed after the command word)
 * Returns      : Success 1 or failure 0
 */
private nomask int do_burn( string str )
{
 object user;

    if ((str != "robe") &&
        (str != "cloak"))
    {
        notify_fail( "You can't burn this just like that.\n" );
        return 0;
    }
    user = this_player();

    write( "You burn your "+ query_short()+ ".\n" );
    say( QTNAME( user )+ " burns "+ HIS( user)+ " "+query_short()+ ".\n" );
    if ((user->query_hooded()) || (user == query_worn()))
    {
        Shadow->remove_shadow();
        user->heal_hp( -(user->query_max_hp()/ 20) );
        write( "You are hurt by the flames.\n" );
        say( QTNAME( user )+ " is hurt by the flames.\n" );
    }
    set_alarm( 0.1, 0.0, remove_object );
    return 1;
}

public void init()
{
    ::init();

    add_action( do_hood  , "hood"    );
    add_action( do_hood  , "wear"    );
    add_action( do_reveal, "reveal"  );
    add_action( do_reveal, "unhood"  );
    add_action( do_reveal, "remove"  );
    add_action( etendae  , "etendae" );
    add_action( do_burn  , "burn"    );
    add_action("show_vitals", "v");
    add_action("show_vitals", "vitals");
}

/* Function name: query_spell_morgul_level
 * Description  : return Morgul level needed to cast a spell
 * Arguments:     spell - the name of the spell (the command verb)
 * Returns:       the Morgul level required, -1 if no spell
 */
public int
query_spell_morgul_level( string spell )
{
    if (!strlen( spell ))
    {
        return -1;
    }
    switch (lower_case( spell ))
    {
        case "arhalgul":        return MS_ARHAL_MIN;
        case "artirith":        return MS_ARTIR_MIN;
        case "crabandir":       return MS_CRABA_MIN;
        case "dollost":         return MS_DOLLO_MIN;
        case "dramalgos":       return MS_DRAMA_MIN;
        case "ephessul":        return MS_EPHES_MIN;
        case "faugoroth":       return MS_FAUGO_MIN;
        case "gostangwedh":     return MS_GOSTA_MIN;
        case "morthul":         return MS_MORTH_MIN;
        case "mortirio":        return MS_MORTI_MIN;
        case "naro":            return MS_NARO1_MIN;
        case "narusse":         return MS_NARUS_MIN;
        case "nifarist":        return MS_NIFAR_MIN;
        case "orekir":          return MS_OREKI_MIN;
        case "palanquendo":     return MS_PALAN_MIN;
        case "ringurth":        return MS_RINGU_MIN;
        case "sauthacuith":     return MS_SAUTH_MIN;
        case "sulambar":        return MS_SULAM_MIN;
        case "thunaur":         return MS_THUNA_MIN;
        case "yalarochrama":    return MS_YALAR_MIN;
        default:                return -1;
    }
}

/*
 * Function name: sort_spells
 * Description  : Sorts the spells
 * Arguments    : string sp1, string sp2 - the spells to sort
 */
public int
sort_spells( string sp1, string sp2 )
{
    return (query_spell_morgul_level( sp1 )-
        query_spell_morgul_level( sp2 ));
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is typed.
 */
void
list_spells()
{
 int index, size;
 object ob;
                                /*gSpells is a return value of
                                 *query_spell_map()                       */
 string *verb_list = m_indices( gSpells ), desc, space, msg = "\n" +
    "\t ______________________________________________________________\n"+
    "\t/                                                              \\\n"+
    "\t|  The Dark Lord has granted you these spells:                 |\n"+
    "\t|  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                 |\n";
 
    verb_list = sort_array( verb_list, "sort_spells" );

    size = sizeof( verb_list );
    if (!size)
    {
        return;
    }
    index = -1;

    while (++index < size)
    {
        if (ob = get_spell_object( verb_list[index] ))
        {
            desc = ob->query_spell_desc();
            msg += sprintf( "\t| %-12s %-47s |\n", verb_list[index], desc );
        }
    }
    msg +=
    "\t" +
    "\\______________________________________________________________/\n\n";
 
    write( msg );
}


/*
 * vitals - Give vital state information about the living.
 */
varargs int
show_vitals(string str, object target = this_player())
{
    string name;
    int self;
    int value1;
    int value2;
    int *society_time;

    if (!strlen(str))
    {
        str = "all";
    }

    self = (target == this_player());
    name = capitalize(target->query_real_name());
    switch(str)
    {
    case "age":
        write("You are " + CONVTIME(target->query_age() * 2) + " of age.\n");

        return 1;

    case "align":
    case "alignment":
        write("Etani view you as one of the " + target->query_align_text() + ".\n");
        return 1;

    case "all":
        show_vitals("health", this_player());
        show_vitals("panic", this_player());
        show_vitals("stuffed", this_player());
        show_vitals("intox", this_player());
        show_vitals("alignment", this_player());
        show_vitals("encumbrance", this_player());
        show_vitals("age", this_player());
        show_vitals("society", this_player());
        return 1;

    case "encumbrance":
        write("Your undead body is " +GET_PROC_DESC(target->query_encumberance_weight(), enc_weight) + ".\n");
        return 1;

    case "health":
    case "mana":
        write("You are physically " + 
            GET_NUM_DESC(target->query_hp(), target->query_max_hp(), health_state) +
            " and mentally " + GET_NUM_DESC(target->query_mana(), target->query_max_mana(), mana_state) +
            ".\n");
        return 1;

    case "intox":
    case "intoxication":
        if (target->query_intoxicated())
        {
            write(GET_NUM_DESC(target->query_intoxicated(), target->query_prop(LIVE_I_MAX_INTOX), intox_state) + " state.\n");
        }
        else
        {
            write("sober state.\n");
        }
        return 1;

    case "panic":
    case "fatigue":
        /* No changes, call original */
        ("/cmd/live/state.c")->vitals("fatigue", target);
        return 1;

    case "stuffed":
    case "soaked":
        write("Your undead body can be stuffed with " +
            GET_NUM_DESC(target->query_stuffed(), target->query_prop(LIVE_I_MAX_EAT), stuff_state) +
            " food and " + GET_NUM_DESC(target->query_soaked(), target->query_prop(LIVE_I_MAX_DRINK), soak_state) + 
            " liquid can be poured into its ");
        return 1;

    case "society":
        /* Need to work out this in the save files before implementing
        society_time = TIME2NUM(target->query_age());
        if(target->query_morgul_level() || target->query_wiz_level())
           write("You have been in the Dark Lord's Service for " + 
                 society_time[0]+ " days and " +
                 society_time[1]+ " hours.\n");
        */
        return 1;
    default:
        if (!this_player()->query_wiz_level())
        {
            notify_fail("The argument " + str + " is not valid for vitals.\n");
            return 0;
        }
        if (!objectp(target = find_player(lower_case(str))))
        {
            notify_fail("There is no player " + capitalize(str) +
                " in the realms at present.\n");
            return 0;
        }
        ("/cmd/live/state.c")->vitals("health", target);
        ("/cmd/live/state.c")->vitals("panic", target);
        ("/cmd/live/state.c")->vitals("stuffed", target);
        ("/cmd/live/state.c")->vitals("intox", target);
        ("/cmd/live/state.c")->vitals("alignment", target);
        ("/cmd/live/state.c")->vitals("encumbrance", target);
        ("/cmd/live/state.c")->vitals("age", target);
        return 1;
    }

    write("Impossible end of vitals. Please make a sysbug report of this.\n");
    return 1;
}
