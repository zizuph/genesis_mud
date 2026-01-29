/*
 * Elemental Summoning for the Elemental Guilds of Calia
 *
 * This is the summoning object, which can manifest itself as one of
 * the elemental beings of the four Elements: fire, water, earth, air.
 * 
 * Fire: fire djini
 * Water: water weird
 * Earth: earth golem
 * Air: air spirit
 * Life: shadowy wisp
 *
 * Created by Petros, May 2011
 */

#pragma strict_types

#include <const.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <composite.h>

#include "../defs.h"

inherit "/std/creature";
inherit "/std/combat/unarmed";

// Global Variables
public string       Elemental_type = "";
public string       Descriptive_adjective = "";
public mapping      Elemental_race_names = ([
    "fire"  : "fire djini",
    "water" : "water weird",
    "earth" : "earth golem",
    "air"   : "air spirit",
    "life"  : "shadowy wisp",
]);   
public mapping      Elemental_m_in = ([
    "fire"  : "arrives trailing fire and smoke.",
    "water" : "sloshes in.",
    "earth" : "lumbers in.",
    "air"   : "floats in.",
    "life"  : "floats in.",
]);    
public mapping      Elemental_m_out = ([
    "fire"  : "leaves",
    "water" : "sloshes",
    "earth" : "lumbers",
    "air"   : "floats",
    "life"  : "floats",
]);    
public mapping      Elemental_mm_in = ([
    "fire"  : "forms from a violent explosion of smoke and flames.",
    "water" : "explodes in the room with the fury of a rainstorm.",
    "earth" : "reforms from the ground before you.",
    "air"   : "forms from merging gusts of wind.",
    "life"  : "forms from the shadows around you.",
]);    
public mapping      Elemental_mm_out = ([
    "fire"  : "dies out and fades away.",
    "water" : "implodes upon itself and vanishes without a trace.",
    "earth" : "descends into the earth.",
    "air"   : "explodes in a fury of chaotic winds.",
    "life"  : "disappears into the shadows around you.",
]);    
public mapping      Elemental_adjectives = ([
    "fire"  : ({"roaring", "red", "menacing", "terrible"}),
    "water" : ({"flowing", "translucent", "shimmering", "watery", "churning"}),
    "earth" : ({"massive", "huge", "large", "rumbling", "grotesque"}),
    "air"   : ({"vague", "indistinct","willowy","hazy","wispy"}),
    "life"  : ({"shimmering","small","vibrating"}),
]);
public mapping      Elemental_long_descriptions = ([
    "fire"  : 
        "Composed of roaring flames churning about in a chaos "
      + "of fiery tendrils, this creature is not of this world. "
      + "The flames shape and form themselves constantly, but there "
      + "does seem to be a vague resemblance to a humanoid "
      + "figure.\n",
    "water" : 
        "A vaguely humanoid shaped creature, comprised "
      + "completely of water, with the exception of the eyes "
      + "which are two large aquamarines.\n",
    "earth" : 
        "It is a huge, lumbering creature, shapeless and "
      + "grey. It seems to be made from dark clay, and two "
      + "dark holes signify where the eyes might be.\n",
    "air"   : 
        "A creature formed from winds and air, this "
      + "spirit is translucent and pale. Wisps of mist "
      + "form what might be strands of hair, billowing out "
      + "in a mad flurry.\n",
    "life"  :
    	"A shadowy mass roughly in the shape of a "
      + "sphere, this creature is certainly not "
      + "from this world.\n",
]);    
public object   summoner = 0;

// Prototypes
public string   query_elemental_race_name();
public string   query_elemental_type();

/*
 * Function:    create_monster
 * Description: Initialization function for the NPC
 */
public void
create_creature()
{
    // Set up some basic attributes of the summoned elemental
    set_name("elemental");
    set_race_name(query_elemental_race_name());
    add_name(({ "familiar", "summoning" }));
    set_gender(G_NEUTER);
    set_alignment(0);
    default_config_creature(80);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_NO_ATTACK, "@@describe_no_attack");
    add_prop(NPC_M_NO_ACCEPT_GIVE, VBFC_ME("check_give"));
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_S_WIZINFO, "This is an elemental that is summoned by" +
        " a member of the Elemental Worshippers of Calia. It should not" +
        " enter into fights. Inquire with guildmaster if you need access" +
        " to the code.\n");    

    // We give the summoning some basic skills.
    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_AWARENESS, 50);
    // Set up the default attack and hitlocs
    set_attack_unarmed(0, 35, 40, W_BLUDGEON, 100, "elemental tendrils");
    set_hitloc_unarmed(0, 5, 100, "elemental body");

    // We use VBFC to describe the elemental summoning
    set_short("@@describe_short");
    set_long("@@describe_long");
}

/*
 * Function:    describe_no_attack
 * Description: VBFC function used in the OBJ_M_NO_ATTACK property
 */
public string
describe_no_attack()
{
    return "Try as you might, you're unable to attack the " + short() + "\n";
}

/*
 * Function:    query_elemental_race_name
 * Description: Depending on the elemental type, we use a different race name.
 *              This funciton retrieves that race name.
 */
public string
query_elemental_race_name()
{
    if (!strlen(Elemental_race_names[query_elemental_type()]))
    {
        return "summoned elemental";
    }
    
    return Elemental_race_names[query_elemental_type()];
}

/*
 * Function:    describe_short
 * Description: VBFC function to return the short description.
 */
public string
describe_short()
{
    string race = query_elemental_race_name();
    if (!strlen(Descriptive_adjective))
    {
        string * adjectives = Elemental_adjectives[query_elemental_type()];
        if (!pointerp(adjectives))
        {
            return race;
        }
        Descriptive_adjective = one_of_list(adjectives);
        add_adj(Descriptive_adjective);
    }
    
    return Descriptive_adjective + " " + race;
}

/*
 * Function:    describe_long
 * Description: VBFC function to return the long description.
 */
public string
describe_long()
{
   if (!strlen(Elemental_long_descriptions[query_elemental_type()]))
    {
        return "This " + short() + " is a summoned elemental creature.\n";
    }
    
    return Elemental_long_descriptions[query_elemental_type()];
}

/*
 * Function:    describe_m_in
 * Description: VBFC function to return the m_in for the elemental
 */
public string
describe_m_in()
{
    if (!strlen(Elemental_m_in[query_elemental_type()]))
    {
        return "arrives.";
    }
    
    return Elemental_m_in[query_elemental_type()];
}

/*
 * Function:    describe_m_out
 * Description: VBFC function to return the m_in for the elemental
 */
public string
describe_m_out()
{
    if (!strlen(Elemental_m_out[query_elemental_type()]))
    {
        return "leaves";
    }
    
    return Elemental_m_out[query_elemental_type()];
}

/*
 * Function:    describe_mm_in
 * Description: VBFC function to return the m_in for the elemental
 */
public string
describe_mm_in()
{
    if (!strlen(Elemental_mm_in[query_elemental_type()]))
    {
        return "arrives in a puff of smoke.";
    }
    
    return Elemental_mm_in[query_elemental_type()];
}

/*
 * Function:    describe_mm_out
 * Description: VBFC function to return the m_in for the elemental
 */
public string
describe_mm_out()
{
    if (!strlen(Elemental_mm_out[query_elemental_type()]))
    {
        return "disappears in a puff of smoke.";
    }
    
    return Elemental_mm_out[query_elemental_type()];
}

/*
 * Function:    query_elemental_type
 * Description: Returns one of the four elemental types currently set
 */
public string
query_elemental_type()
{
    return Elemental_type;
}

public void
set_elemental_type(string element)
{
    Elemental_type = lower_case(element);
    // Remove all the names
    remove_name(query_names());
    set_name("elemental");
    set_race_name(query_elemental_race_name());
    add_name(query_elemental_race_name());
    // Reset the elemental resistances to 0
    remove_prop(MAGIC_I_RES_FIRE);
    remove_prop(MAGIC_I_RES_WATER);
    remove_prop(MAGIC_I_RES_EARTH);
    remove_prop(MAGIC_I_RES_AIR);
    remove_prop(MAGIC_I_RES_LIFE);
    Descriptive_adjective = "";
    
    set_m_in(Elemental_m_in[query_elemental_type()]);
    set_m_out(Elemental_m_out[query_elemental_type()]);
    set_mm_in(Elemental_mm_in[query_elemental_type()]);
    set_mm_out(Elemental_mm_out[query_elemental_type()]);
    switch (query_elemental_type())
    {
    case "fire":
        add_name("djini");
        add_prop(MAGIC_I_RES_FIRE, 90);
        set_attack_unarmed(0, 35, 40, W_BLUDGEON, 100, "fiery hands");
        set_hitloc_unarmed(0, 5, 100, "fiery body");
        break;
        
    case "water":
        add_name("weird");
        add_prop(MAGIC_I_RES_WATER, 90);
        set_attack_unarmed(0, 35, 40, W_BLUDGEON, 100, "watery arms");
        set_hitloc_unarmed(0, 5, 100, "watery body");
        break;
        
    case "earth":
        add_name("golem");
        add_prop(MAGIC_I_RES_EARTH, 90);
        set_attack_unarmed(0, 35, 40, W_BLUDGEON, 100, "massive fists");
        set_hitloc_unarmed(0, 5, 100, "clay body");
        break;
        
    case "air":
        add_name("spirit");
        add_prop(MAGIC_I_RES_AIR, 90);
        set_attack_unarmed(0, 35, 40, W_BLUDGEON, 100, "airy fists");
        set_hitloc_unarmed(0, 5, 100, "airy body");
        break;
        
    case "life":
    	add_name("wisp");
    	add_prop(MAGIC_I_RES_LIFE, 90);
    	set_attack_unarmed(0, 35, 40, W_BLUDGEON, 100, "wispy fists");
        set_hitloc_unarmed(0, 5, 100, "wispy body");
        break;
    }
}


/*
 * Function name: race_sound
 * Description  : This function returns the VBFC value for the sound a
 *                particular living hears when this player speaks. It
 *                operates on previous_object(-1). Notice that we use
 *                query_race rather than query_race_name since the first
 *                will always return a true and valid race name. The
 *                person speaking is this_player().
 * Returns      : string - the race sound the receiver hears.
 */
public string
race_sound()
{
    switch (query_elemental_type())
    {
    case "fire":
        return "churns in a rasping voice";
        
    case "water":
        return "gurgles";
        
    case "earth":
        return "booms";
        
    case "air":
        return "sings in a light, airy voice";
        
    case "life":
    	return "whispers in strange voice";
    }
    
    return ::race_sound();
}

/*
 * Function:    set_summoner
 * Description: Function that allows the summoning spell to indicate
 *              who the summoner is. This allows referencing the
 *              summoner for certain effects and checks.
 */
public void
set_summoner(object obj)
{
    summoner = obj;
}

/*
 * Function:    query_summoner
 * Description: Function that returns who the summoner was that summoned
 *              this elemental.
 */
public object
query_summoner()
{
    return summoner;
}

/*
 * Function:    check_give
 * Description: Function ensures that the summoning only accepts items
 *              from the caster that is maintaining the summoning.
 */
public mixed 
check_give()
{
    object player = this_player();
    object * choma_objects = map(GUILD_MANAGER->get_existing_choma_objects(player),
        &->query_summoned_object());
    if (sizeof(choma_objects) && choma_objects[0] == this_object()
        && present(player, environment(this_object())))
    {
        return 0;
    }
    
    return " will not accept it.\n";
}

/*
 * Function name: catch_question
 * Description:   This function is called in each living being someone asks a
 *                question to.
 * Arguments:     question - The question as put
 */
public void 
catch_question(string question)
{
    // Person asking has to be the summoner
    if (this_player() != query_summoner())
    {
        return;
    }
    
    // If no question asked, just default to standard behavior
    if (!strlen(question))
    {
        return;
    }
    
    question = lower_case(question);
    // Summoner is allowed to ask for specific items
    mixed * parse_results;
    object * items;
    if (parse_command(question, this_object(), "'for' %i", parse_results))
    {
        // Check the first variable
        if (parse_results[0] > 0) // # of items to return
        {
            int index = parse_results[0];
            if (sizeof(parse_results) > index)
            {
                items = parse_results[1..index];
            }
        }
        else if (parse_results[0] < 0) // which item (first, second, etc)
        {
            int index = parse_results[0] * -1;
            if (sizeof(parse_results) > index)
            {
                items = ({ parse_results[index] });
            }
        }
        else
        {
            items = parse_results[1..];
        }
        object * moved = ({ });
        foreach (object item : items)
        {
            if (!item->move(this_player()))
            {
                moved += ({ item });
            }
        }
        if (!sizeof(moved))
        {
            command("say I cannot.");
            return;
        }
        this_player()->catch_msg(QCTNAME(this_object()) + " raises up and "
            + "hands " + COMPOSITE_DEAD(moved) + " to you.\n");
        say(QCTNAME(this_object()) + " hands " + COMPOSITE_DEAD(moved)
            + " to " + QTNAME(this_player()) + ".\n");        
        return;
    }

    if (question == "for all")
    {
        if (!command("give things to " + query_summoner()->query_real_name()))
        {
            command("say I cannot.");
        }
        return;
    }

    if (question == "get")
    {
        command("get all");
        return;
    }

    if (question == "fill")
    {
        if (!command("put things in pack"))
        {
            command("say I cannot.");
        }
        return;
    }

    if (question == "empty")
    {
        if (!command("get all from pack"))
        {
            command("say I cannot.");
        }
        return;
    }

    if (question == "inventory" || question == "things")
    {
        command("say I have " + COMPOSITE_DEAD(all_inventory(this_object())) + 
            ".");
        return;
    }

    return;
}
