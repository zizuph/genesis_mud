/*
 * Ritual Chamber of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 *
 * Arman - On review of component for metafora, revised
 *    it to better reflect an appropriate cost for such
 *    a spell.  11 Jan 2019
 * 2020-01-06: Added a command option to 'perform'.
 * 2022-04-22: Changed Earth's primary gem component from
 *    jade to peridot (Arman).
 * 2023-04-15: Increase clone rate of shards to account
 *    for their usage relative to other caster guilds.
 */

#pragma strict_types

#include <cmdparse.h>
#include <files.h>
#include <composite.h>
#include <macros.h>
#include "defs.h"

inherit TEMPLE_ROOM_BASE;
inherit "/d/Sparkle/area/city/lib/utility_functions";

// Defines
#define OLD_HEAP_ID  "_old_heap_s_unique_id"

// Prototypes
public void         describe_ritual(object component);

// Global Variables
public object       placed_herb = 0;
public object       placed_gem = 0;
// Format for Mapping is spell_name => ({ herb, gem })
public mapping      rituals = 
    ([
        "aeria"       : ({ "chicory", "shard_diamond" }),
        "afoplizo"    : ({ "chicory", "shard_topaz" }),
        "aleipso"     : ({ "strim", "white_pearl" }),
        "anakalo"     : ({ "breadroot", "chalcedony" }),
        "antistasi"   : ({ "skull", "shard_sapphire" }),
        "aorato"      : ({ "eye", "shard_alexandrite" }),
        "apodosi"     : ({ "breadroot", "iridescent_opal" }),
        "choma"       : ({ "streyroot", "yellow_topaz" }),
        "diabrecho"   : ({ "sargassum", "shard_sapphire" }),
        "diasosi"     : ({ "eye", "shard_peridot" }),
        "dynami"      : ({ "cladina", "oval_turquoise" }),
        "earth"       : ({ "cladina", "shard_peridot" }),
        "elefrinisi"  : ({ "wildfeather", "striped_chalcedony" }),
        "evimero"     : ({ "chicory", "green_peridot" }),
        "fire"        : ({ "fireweed", "shard_pyrite" }),
        "floga"       : ({ "fireweed", "fire_opal" }),
        "fragmos"     : ({ "flameroot", "shard_pearl" }),
        "giatreou"    : ({ "chicory", "shard_sapphire" }),
        "gu"          : ({ "cladina", "shard_emerald" }),
        "kato"        : ({ "drakeroot", "shard_onyx" }),
        "kourasi"     : ({ "skull", "shard_emerald" }),
        "metaballo"   : ({ "sargassum", "red_spinel" }),
        "metafora"    : ({ "eye", "diamond" }),
        // "onkolithos"  : ({ "cladina", "shard_peridot" }),
        "panikos"     : ({ "skull", "shard_ruby" }),
        //"perika"      : ({ "fireweed", "shard_pyrite" }),
        "psuchae"     : ({ "drakeroot", "shard_alexandrite" }),
        "pyrofosti"   : ({ "cranberry", "rose_quartz" }),
        "pyros"       : ({ "fireweed", "shard_ruby" }),
        "ripi"        : ({ "chicory", "shard_topaz" }),
        "schirmo"     : ({ "blade", "shining_bloodstone" }),
        "seira"       : ({ "eye", "shard_ruby" }),
        "sfyri"       : ({ "heart", "orange-red_garnet" }),
        "skiamorfi"   : ({ "cranberry", "yellow_amber" }),
        "spirit"      : ({ "drakeroot", "shard_onyx" }),
        "syndyasmos"  : ({ "blade", "shard_alexandrite" }),
        "trefo"       : ({ "skull", "shard_topaz" }),
        "treximo"     : ({ "eye", "shard_sapphire" }),
        "unteristi"   : ({ "athly", "purple_amethyst" }),
        "vekpos"      : ({ "skull", "shard_alexandrite" }),
        "water"       : ({ "sargassum", "shard_aquamarine" }),
        ]);
      
public void
create_temple_room()
{
    set_short("Elemental Temple Inner Sanctum");
    set_long("You are in the cylindrical sacred room known as the Inner Sanctum. "
             + "Shrouded walls surround you, trapping the light in this room and "
             + "creating a somber mood. Though you cannot see clearly outside of "
             + "this room, you can see shadows of Temple patrons passing through "
             + "the halls of the Inner Circle. Above you the walls form into a "
             + "massive dome. There are five white candles arranged on the floor "
             + "at triangular points of the pentagram drawn into the black stone "
             + "floor. A ritual circle connects all the points of the pentagram. "
             + "Here in the Inner Sanctum, you can <perform> various rituals.\n\n");
                   
    add_exit(ELEMENTALIST_TEMPLE + "pool", "north");
    add_subloc("ritual circle");
}

public void
init()
{
    ::init();
    
    add_action("do_place", "place");
    add_action("do_perform", "perform");
    add_action("do_perform", "eperform"); /* added as an option */
    add_action("do_retrieve", "retrieve");
    add_action("do_sacrifice", "sacrifice");
}

public int
do_sacrifice(string arg)
{
	if (!IS_MEMBER(TP))
		return 0;
	
	if (!GUILD_MANAGER->query_is_cleric(TP))
		return 0;
		
	if (!present("_elementalists_ceremonial_dagger_", TP))
	{
		NF("You cannot sacrifice any of your Chymos "+
		    "without a Ceremonial Dagger.\n");
		return 0;
	}
	
	arg = lower_case(arg);
	
	if (!arg || arg != "chymos")
	{
		NF("Sacrifice what? Chymos?\n");
		return 0;
	}
	
	if (GUILD_MANAGER->query_guild_conduit() == MAX_GUILD_CONDUIT_SCORE)
	{
		write("Your sacrifice would be in vain, the Temple Conduit is already "+
		    "full.\n");
		return 1;
	}
	
	if (GUILD_MANAGER->query_player_conduit_earned(TP) < 50)
	{
		write("You do not have enough Chymos to sacrifice.\n");
		return 1;
	}
	
	// Take 50 conduit from the player and add 75 conduit to the Guild
	// (since they went out of their way to sacrifice their own gain for
	//  the good of the guild as a whole, the guild gets the extra 25
	//  conduit)
	GUILD_MANAGER->subtract_player_conduit_earned(TP, 50);
	GUILD_MANAGER->add_guild_conduit(75);
	
	write("You slice the ceremonial dagger across your hand causing it "+
	    "to bleed. As the blood touches the floor, it is absorbed into "+
	    "it and the wound on your hand heals instantly.\n");
	say(QCTNAME(TP)+" slices "+TP->query_possessive()+" ceremonial dagger "+
	    "across "+TP->query_possessive()+" hand causing it to bleed. As the "+
	    "blood touches the floor, it is absorbed into it and the wound on "+
	    QTPNAME(TP)+" hand heals instantly.\n");
		
	return 1;
}

public int
do_place(string arg)
{
    notify_fail("Place what? An herb, a gem (shard) or a leftover?\n");
    if (!strlen(arg))
    {
        return 0;
    }
    
    object component = PARSE_COMMAND_ONE(arg, this_player(), "[the] %i [in] [the] [ritual] [circle]");
    if (!objectp(component))
    {
        return 0;
    }
    
    if ((!IS_HERB_OBJECT(component) && !IS_LEFTOVER_OBJECT(component) &&
         !component->query_gem()) && !component->query_gem_shard())
    {
        return 0;
    }
    
    if (IS_HERB_OBJECT(component))
    {
        if (objectp(placed_herb) && placed_herb != component)
        {
            notify_fail("You cannot place the " + component->singular_short()
                + " in the ritual circle as there is already "
                + "something there. You will need to <retrieve> "
                + "first.\n");
            return 0;
        }
        if (component->num_heap() > 1)
        {
            notify_fail("You cannot place more than one " +
                component->singular_short() + " in the ritual circle.\n");
            return 0;
        } 
        component->move(this_object(), "ritual circle");
        placed_herb = component;
        component->set_no_show();
    }
    if (IS_LEFTOVER_OBJECT(component))
    {
        if (objectp(placed_herb) && placed_herb != component)
        {
            notify_fail("You cannot place the " + component->singular_short()
                + " in the ritual circle as there is already "
                + "something there. You will need to <retrieve> "
                + "first.\n");
            return 0;
        }
        if (component->num_heap() > 1)
        {
            notify_fail("You cannot place more than one " +
                component->singular_short() + " in the ritual circle.\n");
            return 0;
        } 
        component->move(this_object(), "ritual circle");
        placed_herb = component;
        component->set_no_show();
    }
    else if (component->query_gem() || component->query_gem_shard())
    {
        if (objectp(placed_gem) && placed_gem != component)
        {
            notify_fail("You cannot place the " + component->singular_short()
                + " in the ritual circle as there is already "
                + "something there. You will need to <retrieve> "
                + "first.\n");
            return 0;
        }
        if (component->num_heap() > 1)
        {
            notify_fail("You cannot place more than one " +
                component->singular_short() + " in the ritual circle.\n");
            return 0;
        }    
        component->move(this_object(), "ritual circle");
        placed_gem = component;
        component->set_no_show();
    }
    // We set the unique heap id so that it doesn't merge with other heaps
    string heap_id = component->query_prop(HEAP_S_UNIQUE_ID);
    component->add_prop(OLD_HEAP_ID, heap_id);
    component->add_prop(HEAP_S_UNIQUE_ID, heap_id + "_ritual_placed_component");
    write("You place the " + component->singular_short() + " into the ritual "
          + "circle.\n");
    return 1;
}

public int
do_retrieve(string arg)
{
    notify_fail("Retrieve what? Components?\n");
    if (!strlen(arg))
    {
        return 0;
    }
    
    arg = lower_case(arg);
    object * retrieved_objects = ({ });

    if (arg != "components")
    {
        return 0;
    }
    
    if (!objectp(placed_herb) && !objectp(placed_gem))
    {
        notify_fail("There are no components to be retrieved!\n");
        return 0;
    }
    
    if (objectp(placed_herb));
    {
        retrieved_objects += ({ placed_herb });
        placed_herb = 0;
    }
    if (objectp(placed_gem))
    {
        retrieved_objects += ({ placed_gem });
        placed_gem = 0;
    }    
    retrieved_objects->unset_no_show();
    retrieved_objects->set_no_show_composite(0);
    // Reset the heap id so that it can merge with other heaps
    foreach (object retrieved_object : retrieved_objects)
    {
        retrieved_object->add_prop(HEAP_S_UNIQUE_ID, retrieved_object->query_prop(OLD_HEAP_ID));
    }
    retrieved_objects->move(this_player());
    write("You retrieve " + COMPOSITE_DEAD(retrieved_objects) + " from the "
        + "ritual circle.\n");
    return 1;
}

/*
 * Function:    retrieve_ritual_name
 * Description: Looks through all the defined rituals and see if the
 *              the placed gem and herb match one.
 */
public string
retrieve_ritual_name()
{
    string herb_name;
    if (!objectp(placed_herb) || !objectp(placed_gem))
    {                              
        // Invalid to have a ritual name when the two components
        // aren't present
        return 0;
    }

    foreach (string spell_name, string * component_list : rituals)
    {
        if (IS_HERB_OBJECT(placed_herb))
            herb_name = placed_herb->query_herb_name();
        if (IS_LEFTOVER_OBJECT(placed_herb))
            herb_name = placed_herb->query_name();
        if (component_list[0] == herb_name
            && IN_ARRAY(component_list[1], placed_gem->query_names()))
        {
            // We found the ritual! Need to check if the player is capable of
            // creating this ritual.
            object * spellobjs = filter(this_player()->query_spellobjs(), 
                                        &operator(==)(spell_name) @ &->query_spell_name());
            if (this_player()->query_wiz_level())
                return spell_name;
            if (IS_CLERIC(this_player()))
            	return spell_name;
            if (!sizeof(spellobjs))
            {
                // Player does not have access to ritual. Return 0.
                return 0;
            }
            return spell_name;
        }
    }
    // No matching ritual was found.
    return 0;
}

public int
do_perform(string arg)
{
    notify_fail("Perform what? A ritual, perhaps?\n");
    if (!strlen(arg) || lower_case(arg) != "ritual")
    {
        return 0;
    }

    // Check to see if there is a placed herb and placed gem
    if (!objectp(placed_herb) && !objectp(placed_gem))
    {
        notify_fail("You cannot perform a ritual without first placing both an "
                  + "herb and a gem in the ritual circle.\n");
        return 0;
    }
    else if (!objectp(placed_herb))
    {
        notify_fail("You cannot perform a ritual without first placing an "
                  + "herb in the ritual circle.\n");
        return 0;
    }
    else if (!objectp(placed_gem))
    {
        notify_fail("You cannot perform a ritual without first placing a "
                  + "gem in the ritual circle.\n");
        return 0;
    }

    // Look for a ritual that matches the herb and gem
    string ritual_name = retrieve_ritual_name();
    if (!strlen(ritual_name))
    {
        // No matching ritual could be found or player doesn't have the
        // ability to create the spell component
        notify_fail("You sense that you will not be able to complete the "
                  + "ritual with the components that you have placed in "
                  + "the ritual circle. It would be a good idea to <retrieve> "
                  + "the components.\n");
        return 0;
    }

    // Confirm that the component file can actually load.
    string component_file = ELEMENTALIST_COMPONENTS + ritual_name + "_component";
    if (!objectp(safely_load_master_file(component_file)))
    {
        notify_fail("Something is terribly wrong! Please contact the guildmaster "
                  + "to check on this ritual.\n");
        return 0;
    }

    // Everything is good. Let's create the spell component
    object component = clone_object(component_file);
    switch(ritual_name)
    {   
    	case "aeria":	
    	case "antistasi":
    	case "aorato":
        case "diabrecho":
    	case "diasosi":
    	case "fragmos":
    	case "giatreou":
    	case "gu":
    	case "kourasi":
    	case "metafora":
    	case "panikos":
    	case "psuchae":
    	case "pyros":
    	case "seira":
    	case "syndyasmos":
    	case "trefo":
    	case "treximo":
    	case "vekpos":
        case "spirit":
        case "water":
        case "earth":
        case "air":
        case "fire":
    		// Cleric rituals
    		// Randomly set the number of components to 4 + random(4)
    		component->set_heap_size(4 + random(4));
    		break;

        case "afoplizo": 
        case "kato":
        case "onkolithos":
        case "perika":
        case "ripi":
    	default:
    		// Worshipper/Seeker rituals
    		// Randomly set the number of components to 2 + random(6)
    		component->set_heap_size(2 + random(6));
    		break;
    }

    object * components = ({ placed_herb, placed_gem });
    components->unset_no_show();
    components->set_no_show_composite(0);
    describe_ritual(component);
    // Now destroy the placed components
    placed_herb->remove_object();
    placed_gem->remove_object();

    return 1;
}

public void
describe_ritual(object component)
{
    write("Bowing your head in reverence for a moment, you pray out "+
          "to the Elementals for power.\n");
    say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head in reverence "+
        "for a moment, and prays out to the Elementals for power.\n");
    write("You chant: I conjure thee, O Circle of Power, "+
          "that thou beest a meeting place of the Elements;\n");
    say(QCTNAME(TP)+" chants: I conjure thee, O Circle "+
        "of Power, that thou beest a meeting place of the Elements;\n");
    write("You dedicate your offerings to the Elementals for the gift of " + capitalize(component->query_component_type()) + ".\n");
    say(QCTNAME(TP)+" dedicates "+TP->query_possessive()+" offerings "+
        "to the Elementals.\n");
    write("The " + placed_gem->singular_short() + " in the ritual circle shines brightly.\n");
    say("The " + placed_gem->singular_short() + " in the ritual circle shines brightly.\n");
    write("The " + placed_herb->singular_short() + " rises up off the ground, and hovers over "+
          "the light shining from the " + placed_gem->singular_short() + ".\n");
    say("The " + placed_herb->singular_short() + " rises up off the ground, and hovers over "+
        "the light shining from the " + placed_gem->singular_short() + ".\n");
    write("Focusing the energies of the Elementals, you wave your hands "+
          "before your offerings. They are quickly consumed by "+
          "the Elements and replaced with " + COMPOSITE_DEAD(component) + ".\n");
    say("Focusing the energies of the Elementals, "+TP->query_pronoun()+
        " waves "+TP->query_possessive()+" hands before the offerings. "+
        "They are quickly consumed by the Elements and replaced with "+
        COMPOSITE_DEAD(component) + ".\n");

    component->move(this_player());
    write("You take the " + COMPOSITE_DEAD(component) + ".\n");

    say(QCTNAME(TP)+" takes the " + COMPOSITE_DEAD(component) + ".\n");
    write("You bow your head in reverence once more, thanking the Elementals "+
          "for the gifts bestowed upon you.\n");
    say(QCTNAME(TP)+" bows "+TP->query_possessive()+" head once more "+
        "in reverence, thanking the Elementals for the gifts bestowed upon "+
        TP->query_objective()+".\n");
    tell_room(ELEMENTALIST_TEMPLE + "conduit","The light in the conduit flashes "+
        "briefly.\n");
}
