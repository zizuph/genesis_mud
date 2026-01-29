/*
 *    /d/Gondor/common/guild2/newspells/obj/craban.c
 *
 *    A crow to spy on living targets for the Morgul spell crabandir.
 *
 *    December 1995 by Olorin
 *
 *      Copyright (c) 1995, 1996 by Christian Markus
 *
 *    Modification log:
 *    08.08.2001 Obsolete code removed.
 *
 *    2006-12-06, Toby:
 *         Fixed runtime error. 
 *          Changed object target_env to mixed target_env
 *          to remove runtime as a result of
 *             target_env = environment( gTarget )
 *          If there is no environment of gTarget env returns 0.
 *    2008-06-18, Toby:
 *         Fixed typo lighting to lightning when craban is killed
 */
#pragma strict_types

inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";
inherit "/std/act/action.c";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../spells.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define SKIES (SPELL_OBJ_DIR+ "watcher_room")
#define MIN_ANI_HANDL    40
#define MIN_AWARE        40
#define MIN_SPELLCRAFT    20
#define MIN_WIS        60
#define MAX_FAIL    12

#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()
#define HIM(x)  (x)->query_objective()
#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())


void watch_target();
public void  remove_craban();
public int query_time_left();
public string long_desc();
mixed check_attack();
string wiz_info();
void set_crabandir_sh( object ob );

static object gMage, gTarget, gParalyze, crabandir_sh;
static int gDuration, gFail, gWatch, gExploded, gRemoved;

public void
create_creature()
{
    set_name( ({ "craban", "crow", "bird", "beast" }) );
    set_pname( ({ "crebain", "crows", "birds" }) );
    set_race_name( "crow" );
    set_adj( ({ "large", "black" }) );
    set_short( "black crow" );
    set_pshort( "black crows" );
    set_long( long_desc );
    set_alignment( -100 );

    set_stats( ({ 10, 60, 25, 40, 40, 10 }) );
    set_whimpy( 80 );

    set_skill( SS_AWARENESS, 90 );
    set_skill( SS_DEFENCE,   40 );

    add_prop( CONT_I_WEIGHT, 700 );
    add_prop( CONT_I_VOLUME, 700 );
    add_prop( CONT_I_MAX_WEIGHT, 800 );
    add_prop( CONT_I_MAX_VOLUME, 800 );

    add_prop( OBJ_M_NO_ATTACK, check_attack );

    add_prop( LIVE_I_UNDEAD, 100 );
    add_prop( LIVE_I_SEE_DARK, 5 );

    add_prop( MAGIC_I_RES_POISON, 70 );
    add_prop( MAGIC_I_RES_MAGIC,  40 );
    add_prop( MAGIC_I_RES_AIR,    70 );

    add_prop( NPC_I_NO_LOOKS, 1 );
    add_prop( NPC_M_NO_ACCEPT_GIVE, " is not able to carry something.\n" );

    add_prop( LIVE_I_NO_CORPSE,   1 );
    add_prop( LIVE_I_UNDEAD,    100 );

    add_prop( OBJ_S_WIZINFO, wiz_info );

    set_attack_unarmed( 0,  5, 15, W_IMPALE,            50, "beak" );
    set_attack_unarmed( 1, 15, 10, W_SLASH | W_IMPALE,  75, "claws" );

    set_hitloc_unarmed( 0, ({ 12, 12,  5}),  40, "body" );
    set_hitloc_unarmed( 1, ({ 15,  5, 15}),  20, "left wing" );
    set_hitloc_unarmed( 2, ({ 15,  5, 15}),  20, "right wing" );
    set_hitloc_unarmed( 3, ({ 20, 10,  5}),  10, "head" );
    set_hitloc_unarmed( 4, ({ 10, 10, 20}),  10, "claws" );

    set_tell_active( 1 );

    set_act_time( 30 );
    add_act( "emote croaks harshly." );
    add_act( "emote flaps its wings." );

    set_m_in( "flies into view" );
    set_m_out( "flies away to the" );
}

string
wiz_info()
{
    return
        "This craban is a demon summoned by the Morgul spell crabandir, "
      + "taking the shape of a bird. The mage who cast the spell can "
      + "see through the eyes of the crow, but cannot control it. The "
      + "crow can be send to spy on any living that is outdoors. It "
      + "cannot follow indoors. It can be attacked only in one case "
      + "out of five. If it wimpies, the demon returns whence it was "
      + "summoned, hurting the attacker. The spell will end in "
      + query_time_left() + " seconds.\n";
}

mixed
check_attack()
{
    if (random( 5 ) > 0)
    {
        return "The "+ short()+ " is flying out of reach. It is "+
            "impossible to attack it.\n";
    }
    return 0;
}

public string
long_desc()
{
 string msg;
 int _awareness, _spellcraft, _animal_handl, _wisdom;

    msg = "This large black crow is a craban out of Mordor where these "+
        "birds are bred to serve the servants of the Dark Lord as spies. ";
    _spellcraft = this_player()->query_skill( SS_SPELLCRAFT );
    _awareness = this_player()->query_skill( SS_AWARENESS );
    _animal_handl = this_player()->query_skill( SS_ANI_HANDL );
    _wisdom = this_player()->query_stat( SS_WIS );

    if ((_spellcraft > (MIN_SPELLCRAFT/ 2+ random( MIN_SPELLCRAFT ))) ||
        (_awareness > (MIN_AWARE/ 2+ random( MIN_AWARE ))))
    {
        msg += "The crow does not look like a normal beast. Your skilled "+
            "senses notice the power of Dark Sorcery emanating from the "+
            "bird. ";
    }
    if ((_animal_handl > (MIN_ANI_HANDL/ 2+ random( MIN_ANI_HANDL ))) &&
        (_wisdom > (MIN_WIS/ 2+ random( MIN_WIS ))))
    {
        msg += "The eyes of the craban show more intelligence by far "+
            "than one could expect from a crow. The craban seems to watch ";
        if (gTarget == this_player())
        {
            msg += "you";
        }
        else
        {
            msg += gTarget->query_the_name( this_player() );
        }
        msg += " intently.\n";
    }

    return msg;
}

varargs void
explode_crow( object attacker )
{
 int dam;
 mixed result;
 string msg;
 object _here;

    _here = environment( this_object() );
    if (!objectp( attacker ))
    {
        attacker = query_attack();
    }
    if (!objectp( attacker ) || !living( attacker ) ||
        !present( attacker, _here) || !objectp( gMage ))
    {
        remove_craban();
        return;
    }

    dam = MIN( 2* gMage->query_mana(), gMage->query_hp() );
    dam -= dam * attacker->query_magic_res( MAGIC_I_RES_LIGHT )/ 100;

    msg = "The "+ short()+ " suddenly explodes violently in a cloud of "+
        "black smoke.\nFrom the cloud, a bolt of lightning strikes ";

    tell_room( _here, msg+ QTNAME( attacker )+ ".\n",
        ({ this_object(), attacker }) );
    attacker->catch_tell( msg + "you.\n" );

    gMage->catch_msg( "The "+ short()+ " flees from combat, returning to "+
        "the shadows whence you summoned it.\nIt disappears in a violent "+
        "explosion, hitting "+ QTNAME( attacker )+ " with a bolt of "+
        "lightning.\nYour awareness returns to your undead body, both "+
        "weakened by the dissipation of energy.\n", this_object() );
    tell_room( environment( gMage ), "The body of "+ QTNAME( gMage )+
        " begins to stir again.\n"+ capitalize( HIS( gMage ) )+ " spirit "+
        "seems to have returned to "+ HIS( gMage )+ " undead body.\n",
        gMage );

    result = attacker->hit_me( dam, MAGIC_DT, TO, -1 );
    if (pointerp( result ) && result[3])
    {
        dam = result[3];
        SPELL_INHERIT->log_spell( "crabandir", NAME( attacker )+ " was "+
            "hit by "+ gMage->query_name()+ "'s craban with damage "+ dam+
            "[hp]." );    
    }
    else
    {
        dam = random( dam );
        SPELL_INHERIT->log_spell( "crabandir", NAME( attacker )+ " was "+
            "hit by "+ gMage->query_name()+ "'s craban with unknown "+
            "damage." );
    }
    if (attacker->query_hp() <= 0)
    {
        SPELL_INHERIT->log_spell( "crabandir", NAME( attacker )+ " ("+
            attacker->query_average_stat()+ ") killed by the "+ gMage->
            query_name()+ "'s ("+ gMage->query_average_stat()+ ") craban "+
            "in "+ file_name( environment( attacker ) )+ "." );
        attacker->do_die( this_object() );
    }
    gMage->add_mana( - dam/ 4 );
    gMage->heal_hp( -dam/ 2 );
    tell_room( _here, "The black cloud disperses, and leaves no remains.\n",
        this_object() );

    gExploded = 1;
    remove_craban();
}

public void
remove_object()
{
    if (!gRemoved)
    {
        remove_craban();
        return;
    }

    ::remove_object();
}

/*
 * Function name: remove_craban
 * Description  : End the effect, remove paralyze from the caster,
 *                remove crow, prevent recursion errors.
 */
public void
remove_craban()
{
 string  mage_msg = "";

    if (gRemoved++)
    {
        return;
    }
    if (previous_object() != gParalyze)
    {
        gParalyze->stop_paralyze();
    }
    
//    gMage->remove_stun();
    crabandir_sh->remove_shadow();
    if (!gExploded)
    {
        gExploded = 1;
        if (!query_ghost())
        {
            tell_room( environment( this_object() ), "The "+ short()+
                " flaps its wings and flies up into the sky and away.\n",
                this_object() );
            mage_msg = " and the craban returns to the shadows whence "+
                "you summoned it";
        }
        if (objectp( gMage ))
        {
            gMage->catch_tell( "Your awareness enters your undead body "+
                "again"+ mage_msg+ ".\n" );
            tell_room( environment( gMage ), "The body of "+
                QTNAME( gMage )+ " begins to stir again.\n"+ capitalize(
                HIS( gMage ) )+ " spirit seems to have returned to "+
                HIS( gMage )+ " undead body.\n", gMage );
                                /* prevent double messages if
                                 *remove_craban() is called twice.        */
            gMage = 0;
        }
    }
    remove_object();
}

void
set_mage( object ob )
{
    if (objectp( ob ))
    {
        gMage = ob;
    }
}

void
set_paralyze( object ob )
{
    if (objectp( ob ))
    {
        gParalyze = ob;
    }
}

void
set_target( object ob )
{
    if (objectp( ob ) && living( ob ))
    {
        gTarget = ob;
    }
}

void
set_duration( int value )
{
    gDuration = set_alarm( itof( value ), 0.0, remove_craban );
}

void
start_watch()
{
    if (!objectp( gMage ) || !objectp( gTarget ) ||
        !gDuration || !sizeof( get_alarm( gDuration ) ))
    {
        remove_craban();
    }
    tell_room( environment( this_object() ), "The "+ short()+ " nods its "+
        "head briefly.\nThe "+ short()+ " flaps its wings and flies up to "+
        "the sky.\n", this_object() );
    move_living( "M", SKIES, 0, 0 );
    gWatch = set_alarm( 10.0+ 20.0* rnd(), 5.0, watch_target );
    SPELL_INHERIT->log_spell( "crabandir","(Caster: "+ NAME( gMage )+
        ") (Victim : "+ NAME( gTarget )+ ") (Duration: "+
        query_time_left()+ "[s]).\n" );
}

void
watch_target()
{
 mixed   target_env;
 string  txt;

    if (!objectp( gMage ))
    {
        set_alarm( 0.0, 0.0, remove_craban );
        return;
    }

    target_env = environment( gTarget );
    if (!objectp( gTarget ) || !objectp( target_env ))
    {
        gMage->catch_tell( "Your "+ short()+ " fails to locate its target "+
            "and flies off.\nThe spell ends.\n" );
        set_alarm( 0.0, 0.0, remove_craban );
        return;
    }

    if (MASTER_OB(environment( this_object() )) == SKIES)
    {
        txt = "You begin to receive a vision from your "+ short()+ " as "+
            "it flies slowly over the land of "+ target_env->query_domain()+
            " looking for "+ QTNAME( gTarget )+ ".\n";

        if (!target_env->query_prop( ROOM_I_INSIDE ) &&
			!target_env->query_prop( ROOM_M_NO_SCRY ) && 
            interactive( gTarget ) &&
			!gTarget->query_prop( LIVE_M_NO_SCRY ) && 
			!gTarget->query_invis() )
        {
            txt += "Your "+ short()+ " spies "+ QTNAME( gTarget )+
                " below and glides down to investigate.\n";
            gMage->catch_msg( txt, this_object() );
            tell_room( environment( this_object() ), "The "+ short()+
                " flies away as if it is following someone.\n",
                this_object() );
            move_living( "M", target_env, 1, 0 );
            tell_room( target_env, capitalize( LANG_ADDART( short() ) )+
                " appears overhead and slowly flies about.\n",
                this_object() );
        }
        else
        {
            gMage->catch_msg( txt, this_object() );
        }
        return;
    }
    if (environment( this_object() ) != target_env)
    {
        if (!gFail)
        {
            txt = "Your "+ short()+ " attempts to follow "+
                QTNAME( gTarget )+ ".\n";
        }
        else
        {
            txt = "";
        }
        if (target_env->query_prop( ROOM_I_INSIDE ) ||
			target_env->query_prop( ROOM_M_NO_SCRY ) || 
            target_env->query_prevent_snoop()  || !interactive( gTarget ) ||
			gTarget->query_invis() || gTarget->query_prop( LIVE_M_NO_SCRY ))
        {
            if (gFail++ > MAX_FAIL)
            {
                txt += "Your "+ short()+ " fails to locate "+ QTNAME(
                    gTarget )+ " and flies off.\nThe spell ends.\n";
                set_alarm( 0.0, 0.0, remove_craban );
            }
            else
            {
                txt += "The "+ short()+ " has lost "+ QTNAME( gTarget )+
                    ".\nIt flies slowly over the land of "+ target_env->
                    query_domain()+ " trying to locate "+ HIM( gTarget )+
                    " again.\n";
            }
            gMage->catch_msg( txt, this_object() );
        }
        else
        {
            gMage->catch_msg( txt, this_object() );
            tell_room( environment( this_object() ), "The "+ short()+
                " flies away as if it is following someone.\n",
                this_object() );
            move_living( "M", target_env, 1, 0 );
            tell_room( target_env, capitalize( LANG_ADDART( short() ) )+
                " appears overhead and slowly flies about.\n",
                this_object() );
            gFail = 0;
        }
        return;
    }

    switch (random( 9 ))
    {
    case 0:
        txt = "The "+ short()+ " circling overhead croaks harshly.\n";
        break;
    case 1:
        txt = capitalize( LANG_ADDART( short() ) )+ " circles slowly "+
            "overhead.\n";
            break;
    case 2:
        txt = capitalize( LANG_ADDART( short() ) )+ " flaps its wings "+
            "slowly, staying overhead.\n";
        break;
    case 3:
        txt = capitalize( LANG_ADDART( short() ) )+ " flies overhead, "+
            "watching the ground and everyone on it closely.\n";
        break;
    default:
        txt = 0;
        break;
    }
    if (strlen( txt ))
    {
        tell_room( target_env, txt, this_object() );
    }
}

void set_crabandir_sh( object ob )
{
    crabandir_sh = ob;
}

void
catch_msg( mixed str, object from_player )
{
    ::catch_msg( str, from_player );

    if ((from_player == this_object() ) || !objectp( gMage ))
    {
        return;
    }
    gMage->catch_tell( "Through the eyes of the craban you see:\n" );
    gMage->catch_msg( str, from_player );
}

/*
 * This trigger hopefully won't fire too frequently.
 */
public void emote_hook( string emote, object actor, string adverb,
    object *oblist, int cmd_attr = 0, int target = 0 )
{
 int i;
 string message = "";

    message += QCTNAME( actor )+ " does something but the details escape "+
        "the bird's attention.\n";
    gMage->catch_msg( message, this_object() );
}

void
enter_env( object to, object from )
{
 string  message = "";
 object *inv, *ld, tp;

    ::enter_env( to, from );

    if (!objectp( to ) || !objectp( from ))
    {
        return;
    }
    if (!objectp( gMage ))
    {
        remove_craban();
        return;
    }

    if (!objectp( to ) || (MASTER_OB( to ) == SKIES))
    {
        return;
    }
    if (present( gTarget, to ))
    {
        message += "Through the eyes of the craban you see:\n"+ to->long();
        inv = FILTER_CAN_SEE( all_inventory( to ), gMage );
        inv -= ({ this_object() });
        tp = this_player();
        set_this_player( gMage );
        if (sizeof( ld = FILTER_DEAD( inv ) ))
        {
            message += capitalize( COMPOSITE_DEAD( ld ) )+ ".\n";
        }
        if (sizeof( ld = FILTER_LIVE( inv ) ))
        {
            message += capitalize( COMPOSITE_LIVE( ld ) )+ ".\n";
        }
        set_this_player( tp );
        gMage->catch_msg( message, this_object() );
    }
}

public void
attacked_by( object ob )
{
    ::attacked_by( ob );

    set_alarm( 0.0, 0.0, &ob->catch_msg(
        "The "+short()+" croaks threateningly.\n"
      + "You feel the power of Dark Sorcery emanating from the bird.\n"
      + "Horrified, you realize that this is no normal beast, it "
      + "is a demon summoned from the realm of shadows by "
      + "the Black Magic of Mordor.\n") );
}

public int
query_time_left()
{
  mixed info;
    if (pointerp( info = get_alarm( gDuration ) ))
    {
        return ftoi( info[2] );
    }
    return -1;
}

public void
run_away()
{
    explode_crow();
}

public int
query_see_special_msg()
{
    return 1;
}
