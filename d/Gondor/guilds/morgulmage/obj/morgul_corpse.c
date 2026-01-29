/*
 * /d/Gondor/guilds/morgulmage/obj/morgul_corpse.c
 *
 * This is a modification of the CORPSE_OBJECT to support
 * violent, morgul death sequences.
 * Coded by Chmee. Ideas by various Morgul mages.
 *
 * Adapted to changes in /std/corpse.c by Mercade, 12 August 2004.
 */

#pragma save_binary
#pragma strict_types

#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/guilds/morgulmage/morgul_corpse.h"

inherit CORPSE_OBJECT;

/* Doubled definition from /std/corpse.c */
#define DECAY_LIMIT	 3

public nomask void set_death_cause( int cause );
public nomask void set_death_variant( int variant );
public nomask void set_corpse_size( int size );

string HE, HIS, HIM;
int _death_cause, _death_variant, _corpse_size;

void set_name( string n )
{
 object _corpse_owner;

    _corpse_owner = previous_object( -1 );
    HE = _corpse_owner->query_pronoun();
    HIS = _corpse_owner->query_possessive();
    HIM = _corpse_owner->query_objective();

    ::set_name( n );

    switch (_death_cause)
    {
    case DRAMALGOS_CS:
        switch (_corpse_size)
        {
        case SMALL_CS:
            switch (_death_variant)
            {
            case 0:
                add_name( "speck" );
                break;
            case 1:
                add_name( "smear" );
                break;
            case 2:
                add_name( "particle" );
                break;
            default:
                add_name( "patch" );
            }
            break;
        case MEDIUM_CS:
            switch (_death_variant)
            {
            case 0:
                add_name( "pulp" );
                break;
            case 1:
                add_name( "lump" );
                break;
            case 2:
                add_name( ({ "pile", "bones", "blood" }) );
                break;
            default:
                add_name( "remnant" );
            }
            break;
        case LARGE_CS:
            switch (_death_variant)
            {
            case 0:
                add_name( ({ "pile", "viscera" }) );
                add_adj( "steaming" );
                break;
            case 1:
                add_name( ({ "mound", "gore" }) );
                break;
            case 2:
                add_name( ({ "guts", "blood" }) );
                add_name( ({ "mountain of blood", "mountain of guts" }), 1 );
                add_pname( ({ "mountains of blood", "mountains of guts" }) );
                break;
            default:
                add_name( "innards" );
                add_name( "hill of innards", 1);
                add_pname( "hills of innards" );
            }
        }
        break;
    case NARUSSE_CS:
    case THUNAUR_CS:
        switch (_corpse_size)
        {
        case SMALL_CS:
            switch (_death_variant)
            {
            case 0:
                add_name( "speck" );
                break;
            case 1:
                add_name( "smear" );
                add_name( "remains",1 );
                break;
            case 2:
                add_name( "lump" );
                break;
            default:
                add_name( "remnant" );
            }
            break;
        case MEDIUM_CS:
            switch (_death_variant)
            {
            case 0:
                add_name( "array" );
                add_name( "entrails", 1 );
                break;
            case 1:
                add_name( "flesh" );
                break;
            case 2:
                add_name( "pile" );
                add_name( "entrails", 1 );
                break;
            default:
                add_name( "carcass" );
            }
            break;
        case LARGE_CS:
            switch (_death_variant)
            {
            case 0:
                add_name( "mound" );
                add_name( ({ "mound of flesh", "flesh" }), 1);
                add_pname( "mounds of flesh" );
                break;
            case 1:
                add_name( "gore" );
                add_name( "mountain of gore", 1 );
                add_pname( "mountains of gore" );
                break;
            case 2:
                add_name( ({ "blood", "limbs" }) );
                add_name( ({ "pillar of blood", "pillar of limbs" }), 1 );
                add_pname( ({ "pillars of blood", "pillars of limbs" }) );
                break;
            default:
                add_name( "mound" );
                add_name( ({ "mound of meat", "meat" }), 1 );
                add_pname( "mounds of meat" );
            }
        }
        break;
    case MORTHUL_CS:
        switch (_death_variant)
        {
        case 0:
             add_name( "cadaver" );
             break;
        case 1:
            add_name( "mound" );
            add_name( ({ "mound of flesh", "flesh" }), 1);
            add_pname( "mounds of flesh" );
            break;
        default:
            add_name( "carcass" );
            break;
        }
    case OREKIR_CS:
        switch (_death_variant)
        {
        case 0:
             add_name( ({"cadaver", "remnant"}) );
             add_pname( ({"cadavers", "remnants"}) );
             break;
        case 1:
            add_name( "mound" );
            add_name( ({ "mound of flesh", "flesh" }), 1);
            add_pname( "mounds of flesh" );
            break;
        case 2:
            add_name( "pile" );
            add_name( "entrails", 1 );
            add_pname( "piles of entrails" );
            break;
        default:
            add_name( "carcass" );
            break;
        }
    }
}

string short_func()
{
 object pob;

    pob = vbfc_caller();
    if (!pob || !interactive( pob ) || pob == this_object())
    {
        pob = previous_object(-1);
    }
    if (!pob || !interactive( pob ))
    {
        pob = this_player();
    }

    switch (_death_cause)
    {
    case DRAMALGOS_CS:
        switch (_corpse_size)
        {
        case SMALL_CS:
            switch (_death_variant)
            {
            case 0:
                return "bloody speck";
            case 1:
                return "smear of blood";
            case 2:
                return "crimson particle";
            default:
                return "patch of bloody gore";
            }
            break;
        case MEDIUM_CS:
            switch (_death_variant)
            {
            case 0:
                return "bloody pulp";
            case 1:
                return "smashed lump of flesh";
            case 2:
                return "crushed pile of blood and bones";
            default:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "collapsed remnant of yourself";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return "collapsed remnant of "+ capitalize( met_name );
                }
                else
                {
                    return "collapsed remnant of "+
                        LANG_ADDART( nonmet_name );
                }
            }
        case LARGE_CS:
            switch (_death_variant)
            {
            case 0:
                return "steaming pile of viscera";
            case 1:
                return "mound of stinking gore";
            case 2:
                return "mountain of blood and guts";
            default:
                return "squashed hill of innards";
            }
        }
        break;
    case NARUSSE_CS:
    case THUNAUR_CS:
        switch (_corpse_size)
        {
        case SMALL_CS:
            switch (_death_variant)
            {
            case 0:
                return "blackened speck";
            case 1:
                return "scorched smear of remains";
            case 2:
                return "blistered lump";
            default:
                return "burned remnant";
            }
        case MEDIUM_CS:
            switch (_death_variant)
            {
            case 0:
                return "blackened array of entrails";
            case 1:
                return "charred confusion of flesh";
            case 2:
                return "blistered pile of entrails";
            default:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "burnt, disemboweled carcass of yourself";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return "burnt, disemboweled carcass of "+
                        capitalize( met_name );
                }
                else
                {
                    return "burnt, disemboweled carcass of "+
                        LANG_ADDART( nonmet_name );
                }
            }
        case LARGE_CS:
            switch (_death_variant)
            {
            case 0:
                return "huge mound of searing flesh";
                break;
            case 1:
                return "bubbling mountain of gore";
                break;
            case 2:
                return "boiling pillar of blood and limbs";
                break;
            default:
                return "steaming mound of razed meat";
            }
        }
        break;
    case MORTHUL_CS:
    case OREKIR_CS:
        switch (_death_variant)
        {
        case 0:
             return "rotten cadaver";
        case 1:
            return "carrion-infested mound of flesh";
        case 2:
            if (pob && pob->query_real_name() == met_name)
            {
                return "sickly-green carcass of yourself";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "sickly-green carcass of "+ capitalize( met_name );
            }
            else
            {
                return "sickly-green carcass of "+
                    LANG_ADDART( nonmet_name );
            }
        default:
            if (pob && pob->query_real_name() == met_name)
            {
                return "gangrenous corpse of yourself";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "gangrenous corpse of "+ capitalize( met_name );
            }
            else
            {
                return "gangrenous corpse of "+ LANG_ADDART( nonmet_name );
            }
        }
    }
}

string pshort_func()
{
 object pob;

    pob = vbfc_caller();
    if (!pob || !interactive( pob ) || pob == this_object())
    {
        pob = previous_object( -1 );
    }
    if (!pob || !interactive( pob ))
    {
        pob = this_player();
    }

    switch (_death_cause)
    {
    case DRAMALGOS_CS:
        switch (_corpse_size)
        {
        case SMALL_CS:
            switch (_death_variant)
            {
            case 0:
                return "bloody specks";
            case 1:
                return "smears of blood";
            case 2:
                return "crimson particles";
            default:
                return "patches of bloody gore";
            }
        case MEDIUM_CS:
            switch (_death_variant)
            {
            case 0:
                return "bloody pulps";
            case 1:
                return "smashed lumps of flesh";
            case 2:
                return "crushed piles of blood and bones";
            default:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "collapsed remnants of yourself";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return "collapsed remnants of "+ capitalize( met_name );
                }
                else
                {
                    return "collapsed remnants of "+
                        LANG_ADDART( nonmet_name );
                }
            }
        case LARGE_CS:
            switch (_death_variant)
            {
            case 0:
                return "steaming piles of viscera";
            case 1:
                return "mounds of stinking gore";
            case 2:
                return "mountains of blood and guts";
            default:
                return "squashed hills of innards";
            }
        }
        break;
    case NARUSSE_CS:
    case THUNAUR_CS:
        switch (_corpse_size)
        {
        case SMALL_CS:
            switch (_death_variant)
            {
            case 0:
                return "blackened specks";
            case 1:
                return "scorched smears of remains";
            case 2:
                return "blistered lumps";
            default:
                return "burned remnants";
            }
        case MEDIUM_CS:
            switch (_death_variant)
            {
            case 0:
                return "blackened arrays of entrails";
            case 1:
                return "charred confusions of flesh";
            case 2:
                return "blistered piles of entrails";
            default:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "burnt, disemboweled carcasses of yourself";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return "burnt, disemboweled carcasses of "+
                        capitalize( met_name );
                }
                else
                {
                    return "burnt, disemboweled carcasses of "+
                        LANG_ADDART( nonmet_name );
                }
            }
        case LARGE_CS:
            switch (_death_variant)
            {
            case 0:
                return "huge mounds of searing flesh";
            case 1:
                return "bubbling mountains of gore";
            case 2:
                return "boiling pillars of blood and limbs";
            default:
                return "steaming mounds of razed meat";
            }
        }
        break;
    case MORTHUL_CS:
    case OREKIR_CS:
        switch (_death_variant)
        {
        case 0:
            return "rotten cadavers";
        case 1:
            return "carrion-infested mounds of flesh";
        case 2:
            if (pob && pob->query_real_name() == met_name)
            {
                return "sickly-green carcasses of yourself";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "sickly-green carcasses of "+ capitalize( met_name );
            }
            else
            {
                return "sickly-green carcasses of "+
                    LANG_ADDART( nonmet_name );
            }
        default:
            if (pob && pob->query_real_name() == met_name)
            {
                   return "gangrenous corpses of yourself";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "gangrenous corpses of "+ capitalize( met_name );
            }
            else
            {
                return "gangrenous corpses of "+ LANG_ADDART( nonmet_name );
            }
        }
    }
}


string long_func()
{
 object pob;

    pob = vbfc_caller();
    if (!pob || !interactive( pob ) || pob == this_object())
    {
        pob = this_player();
    }
    switch (_death_cause)
    {
    case DRAMALGOS_CS:
        switch (_corpse_size)
        {
        case SMALL_CS:
            switch (_death_variant)
            {
            case 0:
                return "This bloody speck is all that is left of "+
                    LANG_ADDART( nonmet_name )+ ".\n";
            case 1:
                return "Such a smear of blood usualy occurs when you "+
                    "squash a mosquito. You can barely recognize the "+
                    "remains of "+ LANG_ADDART( nonmet_name )+ ".\n";
            case 2:
                return "This crimson particle faintly resembles you "+
                    LANG_ADDART( nonmet_name )+ ".\n";
            default:
                return capitalize( LANG_ADDART( nonmet_name ) )+
                    " finished "+ HIS+ " promising career as a patch of "+
                    "bloody gore.\n";
            }
        case MEDIUM_CS:
            switch (_death_variant)
            {
            case 0:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "To your terror and dismay you recognize "+
                        "yourself as this bloody pulp.\n";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return "Some powerful force has smashed "+ capitalize(
                        met_name )+ " into a bloody pulp.\n";
                }
                else
                {
                    return "Some powerful force has smashed this "+
                        nonmet_name+ " into a bloody pulp.\n";
                }
            case 1:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "You feel sick recalling the moment when the "+
                        "Morgul spell smashed you into this lump of "+
                        "flesh.\n";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return capitalize( met_name )+ " fought defiantly but "+
                        "in the end it didn't help "+ HIM+ " avoid "+
                        "being reduced to a smashed lump of flesh.\n";
                }
                else
                {
                    return "It would take a huge hammer and anvil to "+
                        "reduce this "+ nonmet_name+ " into a smashed "+
                        "lump of flesh. Now you wonder with some concern "+
                        "where that hammer and anvil is.\n";
                }
            case 2:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "You still remember a nauseous feeling of blood "+
                        "pouring out of your ears when the Morgul spell "+
                        "crushed your bones. This messy pile is all that"+
                        "has left.\n";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return "You recognize "+ capitalize( met_name )+ " in "+
                        "this crushed pile of blood and bones. From the "+
                        "looks, "+ HE+ " wasn't granted a merciful death.\n";
                }
                else
                {
                    return "This "+ nonmet_name+ " is a victim of what "+
                        "looks like a malevolent force of nature. Fierce "+
                        "winds have torn "+ HIS+ " body leaving this "+
                        "crushed pile of blood and bones.\n";
                }
            default:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "It's really a unique opportunity to look at "+
                        "yourself from the inside. Judging from the state "+
                        "of your internal organs you were quite healthy, "+
                        "at least until the Morgul spell reduced you to "+
                        "this collapsed remnant of flesh.\n";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return "You can't really say what makes you confident "+
                        "that this collapsed remnant was once "+ capitalize(
                        met_name )+ ". Neither the shape nor surviving "+
                        "bone structure helps in distinguishing this "+
                        "corpse.\n";
                }
                else
                {
                    return "This is a collapsed remnant of "+ LANG_ADDART(
                        nonmet_name )+ ". Judging from the state of the "+
                        "internal organs this "+ nonmet_name+ " was quite "+
                        "a healthy "+ query_prop( CORPSE_S_RACE )+
                        ", at least before "+ HE+ " had this 'accident'.\n";
                }
            }
        case LARGE_CS:
            switch (_death_variant)
            {
            case 0:
                return "This steaming pile of viscera was once "+
                    LANG_ADDART( nonmet_name )+ ". The surrounding area "+
                    "resembles that of a slaughter-house. You "+
                    "decide you are not interested in meeting the "+
                    "butcher.\n";
            case 1:
                return "This mound of stinking gore was once "+
                    LANG_ADDART( nonmet_name )+ ". Looking at the maggots "+
                    "feasting in it you wonder morbidly if this is the "+
                    "beginning or the end of the food chain.\n";
            case 2:
                return "This mountain of blood and guts was once "+
                    LANG_ADDART( nonmet_name )+ ". Internal organs form "+
                    "intricate patterns around other body parts, with the "+
                    "intense smell of blood creating a ghoulishly "+
                    "artistic touch to the scene.\n";
            default:
                return "This squashed hills of innards was once "+
                    LANG_ADDART( nonmet_name )+ ". You wonder what "+
                    "wrathful being could reduce such as massive creature "+
                    "into this nightmare of body parts and organs.\n";
            }
        }
        break;
    case NARUSSE_CS:
    case THUNAUR_CS:
        switch (_corpse_size)
        {
        case SMALL_CS:
            switch (_death_variant)
            {
            case 0:
                return "This blackened speck is all that is left of "+
                    LANG_ADDART( nonmet_name )+ ". Extreme temperature "+
                    "did not seem to do any favours to this creature.\n";
            case 1:
                return "This scorched smear of remains is all that is "+
                    "left of "+ LANG_ADDART( nonmet_name )+ ". You have "+
                    "the feeling, with grim amusement, that this creature "+
                    "went down in a blaze of glory.\n";
            case 2:
                return "This blistered lump is all that is left of "+
                     LANG_ADDART( nonmet_name )+ ". By the looks, intense "+
                     "heat boiled up the tissues and vaporized the water "+
                     "in them forming terminal blisters.\n";
            default:
                return "This burned remnant is all that is left of "+
                    LANG_ADDART( nonmet_name )+ ". Flames have completely "+
                    "carbonized protruding body parts and gruesomely "+
                    "fried the rest of the body.\n";
            }
        case MEDIUM_CS:
            switch (_death_variant)
            {
            case 0:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "You are looking at your own remains. "+
                        "Surprising, as you don't recognise anything from "+
                        "this blackened array of entrails. It looks like "+
                        "an intense fire has burnt it into its current "+
                        "gruesome form.\n";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return "You barely recognize "+ capitalize( met_name )+
                        " from this blackened array of entrails. Now "+
                        HE+ " looks like a failed cooking experiment of "+
                        "a sadistic troll chef.\n";
                }
                else
                {
                    return "You feel a morbid sense of pride at being "+
                        "able to recognise "+ LANG_ADDART( nonmet_name )+
                        " from this blackened array of entrails. "+
                        capitalize( HE )+ " looks like "+ HE+ " decided "+
                        "to take a nap too close to a campfire. A rather "+
                        "big campfire.\n";
                }
            case 1:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "You feel a strange sense of of melancholy "+
                        "observing your former body reduced to a charred "+
                        "confusion of flesh. What a pity.\n";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return "The head has remained almost untouched and "+
                        "that's how you recognize "+ capitalize( met_name )+
                        " from this charred confusion of flesh. You hope "+
                        "the sight won't haunt you in your dreams.\n";
                }
                else
                {
                    return "In spite of being almost unrecognizable you "+
                        "are quite confident that this charred confusion "+
                        "of flesh once belonged to "+ LANG_ADDART(
                        nonmet_name )+ ". You hope your end will be "+
                        "different.\n";
                }
            case 2:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "Looking at you sad remains you recall only "+
                        "an intense flash and then darkness. The blisters "+
                        "must had formed when the heat boiled your tissues "+
                        "up. The body didn't endure the pressure and "+
                        "cracked longwise pouring your internal organs "+
                        "out.\n";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return "You see a blistered pile of entrails. The "+
                        "blisters must had formed when the heat boiled up "+
                        "the tissues. The body didn't endure the "+
                        "pressure and cracked longwise from the left "+
                        "groin up to the chest. The relatively untouched "+
                        "upper part clearly points at "+ capitalize(
                        met_name )+ " being the previous owner of this "+
                        "body.\n";
                }
                else
                {
                    return "You see a blistered pile of entrails. The "+
                        "blisters must had formed when the heat boiled up "+
                        "the tissues. The body didn't endure the "+
                        "pressure and cracked longwise from the left "+
                        "groin up to the chest. The expression of horror "+
                        "on the relatively untouched face of this "+
                        LANG_ADDART( nonmet_name )+ " is one of those you "+
                        "will never forget.\n";
                }
            default:
                if (pob && pob->query_real_name() == met_name)
                {
                    return "This is a burnt and disemboweled carcass of "+
                        "yourself. Intense flame tore you in half and "+
                        "disemboweled you like a sacrificial lamb. Even "+
                        "the smell is similar.\n";
                }
                else if (pob && pob->query_met( met_name ))
                {
                    return "This is a burnt and disemboweled carcass of "+
                        capitalize( met_name )+ ". Intense flame tore "+
                        HIM+ " in half and disemboweled " +HIM+ " like "+
                        "a sacrificial lamb. Even the smell is similar. "+
                        "Worms are going to have a feast.\n";
                }
                else
                {
                    return "This is a burnt and disemboweled carcass of "+
                        LANG_ADDART( nonmet_name )+ ". Intense flame tore "+
                        HIM+ " in half and disemboweled " +HIM+ " like "+
                        "a sacrificial lamb. Even the smell is similar. "+
                        "Worms are going to have a feast.\n";
                }
            }
            break;
        case LARGE_CS:
            switch (_death_variant)
            {
            case 0:
                return "Someone decided to fry "+ LANG_ADDART( nonmet_name)+
                    " in one piece. This huge mound of searing flesh looks "+
                    "as if it has been prepared for some giant's dinner. "+
                    "You could even cut a cutlet or two for yourself if "+
                    "you were hungry enough.\n";
            case 1:
                return "This "+ nonmet_name+ " looks like a failed "+
                    "giant's dish. It is as if a cook left it too long in "+
                    "the pot or under a raging fire and it is now only a "+
                    "bubbling mountain of gore.\n";
            case 2:
                return "A powerful blast of energy must have discharged "+
                    "here just recently reducing an unfortunate "+
                    nonmet_name+ " to a boiling pillar of blood and "+
                    "limbs.\n";
            default:
                return "This "+ nonmet_name+ " looks almost exactly like a "+
                    "miller's kid who fell between the gears. Of course "+
                    "the miller wouldn't cook his kid afterwards.\n";
            }
        }
        break;
    case MORTHUL_CS:
        switch (_death_variant)
        {
        case 0:
            if (pob && pob->query_real_name() == met_name)
            {
                return "No doubts, this rotten cadaver is your former "+
                    "body. By the looks the maggots don't care much about "+
                    "the poison that killed you.\n";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "In spite of having significantly decayed, you "+
                    "have no problems in recognizing "+ capitalize(
                    met_name )+ " in this rotten cadaver. From memory, "+
                    HE+ " used to smell better.\n";
            }
            else
            {
                return "This is a rotten cadaver of "+ LANG_ADDART(
                    nonmet_name )+ ". No doubt, morgul poison was  "+
                    "involved in this death. You think you would prefer "+
                    "dying in a less painful way.\n";
            }
        case 1:
            if (pob && pob->query_real_name() == met_name)
            {
                return "You feel sick observing worms devouring your "+
                    "former body. Either they like morgul poison or the "+
                    "poison wore off, as there is little meat left on "+
                    "carcass.\n";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "The worms haven't got to the head yet so you "+
                    "immediately recognize this to be the corpse of "+
                    capitalize( met_name )+ ". The expression of horror "+
                    "on "+ HIS+ " face indicates that "+ HIS+ " death was "+
                    "not an easy one.\n";
            }
            else
            {
                return "It looks like this "+ LANG_ADDART( nonmet_name )+
                    " struggled desperately to save " +HIS+ " life. Alas, "+
                    "the poison was revealed to be stronger and now "+ HE+
                    " serves as a food for small carrion-eaters.\n";
            }
        case 2:
            if (pob && pob->query_real_name() == met_name)
            {
                return "Your face turns green when you look at your "+
                    "decaying carcass. Though the pain and sickness "+
                    "has passed the memory of it is still fresh.\n";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "In spite of being covered by fungi in all colors "+
                    "of the rainbow, the carcass is still recognizable. "+
                    "You have no doubts it belonged to "+
                    capitalize( met_name )+ ".\n";
            }
            else
            {
                return "One could say that this "+ nonmet_name+ " has "+
                    "decayed in a morbidly beautiful way. Indeed, fungi "+
                    "have formed intriguing patterns all over the carcass "+
                    "in a spectrum of colors. The sickly-green one "+
                    "dominates however.\n";
            }
        default:
            if (pob && pob->query_real_name() == met_name)
            {
                return "Though this happened so recently the corpse is "+
                    "already very degraded. You can barely recognize "+
                    "yourself under the large, gangrenous blotches.\n";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "Gangrena has made terrible havoc in the once "+
                    "sound body of "+ capitalize( met_name )+ " changing "+
                    "it beyond recognition. The sickly sweet smell of "+
                    "decaying eggs makes breathing a torture.\n";
            }
            else
            {
                return "The morgul poison left this battlefield and has "+
                    "been replaced by bacteria. The corpse of this "+
                    nonmet_name+ " has changed beyond recognition. Large, "+
                    "gangrenous blotches cover all "+ HIS+ " body and the "+
                    "sickly sweet smell of decaying eggs makes breathing "+
                    "a torture.\n";
            }
        }
    case OREKIR_CS:
        switch (_death_variant)
        {
        case 0:
            if (pob && pob->query_real_name() == met_name)
            {
                return "No doubts, this rotten cadaver is your former "+
                    "body. By the looks the maggots don't care much about "+
                    "it since its stripped of all food.\n";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "In spite of having significantly decayed, you "+
                    "have no problems in recognizing "+ capitalize(
                    met_name )+ " in this sickly misshaped cadaver. From "+
                    "memory, " +HE+ " used to smell better.\n";
            }
            else
            {
                return "This is a rotten misshaped cadaver of "+ LANG_ADDART(
                    nonmet_name )+ ". No doubt, morgul magics was  "+
                    "involved in shaping it, or deforming it.\n";
            }
        case 1:
            if (pob && pob->query_real_name() == met_name)
            {
                return "You feel sick observing worms crawling all over your "+
                    "former body searching for eadable parts. There are however "+
                    "no bones left in it and only a little meat left on the "+
                    "carcass.\n";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "The worms haven't got to the head yet so you "+
                    "immediately recognize this to be the corpse of "+
                    capitalize( met_name )+ " though not a single bone is left "+
                    "in it. The expression of horror on "+ HIS+ 
                    " face indicates that "+ HIS+ " death was not an easy one.\n";
            }
            else
            {
                return "It looks like this "+ LANG_ADDART( nonmet_name )+
                    " never had a single bone in " +HIS+ " body alive. Alas, "+
                    "no doubt morgul magics have been involved in creating this "+
                    "pile of gore remaining of its former life form.\n";
            }
        case 2:
            if (pob && pob->query_real_name() == met_name)
            {
                return "Your face turns green when you look at your "+
                    "decaying carcass. Though the pain and sickness "+
                    "has passed the memory of it is still fresh. You "+
                    "notice that every single bone in your former body "+
                    "have been stripped away, leaving only a misshapen "+
                    "form to rot and decay.\n";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "In spite of being covered by fungi in all colors "+
                    "of the rainbow, the carcass is still barely recognizable "+
                    "without a single bone in the body. You have no doubts it "+
                    "belonged to " +capitalize( met_name )+ ".\n";
            }
            else
            {
                return "One could say that this "+ nonmet_name+ " has "+
                    "decayed in a morbidly beautiful way. Indeed, fungi "+
                    "have formed intriguing patterns all over the formless "+
                    "carcass in a spectrum of colors. The sickly-green one "+
                    "dominates however.\n";
            }
        default:
            if (pob && pob->query_real_name() == met_name)
            {
                return "Though this happened so recently the corpse is "+
                    "already very degraded and suspiciously formless. "+
                    "You can barely recognize yourself under the large, "+
                    "gangrenous blotches and without a single bone left "+
                    "in your dead body.\n";
            }
            else if (pob && pob->query_met( met_name ))
            {
                return "Gangrena has made terrible havoc in the once "+
                    "sound body of "+ capitalize( met_name )+ " changing "+
                    "it beyond recognition. Bones seem to have been torn "+
                    "out mercilessly, all at once, from the decaying carcass. "+
                    "The sickly sweet smell of decaying eggs makes breathing "+
                    "a torture.\n";
            }
            else
            {
                return "The shapeless corpse of this " +nonmet_name+ " has been changed "+
                    "beyond recognition. Large, gangrenous blotches cover all of "+ 
                    HIS+ " boneless body and the sickly sweet smell of "+
                    "decaying eggs makes breathing a torture.\n";
            }
        }
    }
}

void
decay_fun()
{
    object *ob;
    string desc;
    int i;

    ob = filter(all_inventory(this_object()), move_out);
    /* fix this to get singular/plural of 'appear' */
    i = ((sizeof(ob) != 1) ? sizeof(ob) :
         ((ob[0]->query_prop(HEAP_I_IS)) ? (int)ob[0]->num_heap() : 1));
    if (strlen(desc = COMPOSITE_DEAD(ob)))
    {
        tell_room( environment( this_object() ), "The "+
            QSHORT(this_object())+ " rapidly loses its integrity, and " +
            desc + " appear" +
	    ((i == 1 || desc == "something" || desc == "nothing") ? "s" : "") +
            " from it.\n");
    }
    else
    {
        tell_room( environment( this_object() ), "The "+
            QSHORT(this_object())+ " rapidly loses its integrity.\n" );
    }

    /* Set the short decay limit so it will remove itself. */
    set_decay(DECAY_LIMIT);
}

public nomask void set_death_cause( int cause )
{
    _death_cause = cause;
}

public nomask void set_death_variant( int variant )
{
    _death_variant = variant;
}
public nomask void set_corpse_size( int size )
{
    _corpse_size = size;
}
