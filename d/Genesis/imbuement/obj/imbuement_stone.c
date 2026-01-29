/*
 *  /d/Genesis/imbuement/obj/imbuement_stone.c
 *
 *  These stones are containtment vessels for the random enchantments that
 *  will be randomly distributed throughout the realms in the form of
 *  weapon and armour imbuements. A skilled enchanter can drain the
 *  enchantment from an imbued item and place the imbuement into one of
 *  these special stones.
 *
 *  The "color" of the stone is the signature characteristic of its
 *  imbuement type. For example, a damage_fire mod is called an
 *  "orangestone". An empty stone is simply called a nullstone, and
 *  will have its name changed when it is used to store an imbuement
 *  type.
 *
 *  The imbuement economy is based on the "power" of the enchantment
 *  that is being dealt with. Mods spawn as power level 1, 2, or 3. These
 *  numbers become the currency for the economy. If you disenchant a
 *  level 1 mod, you get 1 unit of currency, represented by these stones.
 *
 *    Quality    | Units of Power
 *    -----------+---------------
 *    cracked    | 1
 *    blemished  | 3
 *    normal     | 9
 *    unblemished| 27
 *    glittering | 81
 * 
 *  The stones combine, as an homage to Diablo II, so that any 3 of a given
 *  stone type of a given quality can be upgraded to a single stone of the
 *  next level up. So, for example, 3 cracked stones can <combine> to become
 *  a single blemished stone. 3 blemished stones can <combine> to become
 *  one normal stone, and so on.
 *
 *  Thus, when an object with a Power Level 1 damage_fire mod (for example)
 *  is disenchanted, the player receives 1 "cracked orangestone." If the
 *  mod was a Power Level 2, the player would receive 2 "cracked
 *  orangestones." But if the mod had been Power Level 3, the player would
 *  receive 1 "blemished orangestone."
 *
 *  Players can hoard these stones, which will stay with them over
 *  logouts and reboots. Members of the Enchanters guilds can put them
 *  to use such that they can imbue a given item with the power that is
 *  contained inside a stone. The way this works is as follows:
 *
 *    Imbuement Level Desired |  Reagent Cost        |  Power Unit Equivalent
 *    ------------------------+----------------------+------------------------
 *    Power Level 1           |  1 normal stone      |  9
 *    Power Level 2           |  1 unblemished stone |  27
 *    Power Level 3           |  1 glittering stone  |  81
 *
 *  Thus, we have an exponentially difficult climb toward allowing a player
 *  to give a chosen item a Power Level 3 imbuement. For example, if a
 *  player wanted to give a damage_fire mod to a favorite weapon, they
 *  would first need to find and disenchant 9 power units worth of
 *  that single mod type to produce 1 (normal) orangestone. If, however,
 *  they wanted to create a Power Level 3 damage_fire mod, they would
 *  be forced to find 81 of these power units to produce the 1 glittering
 *  orangestone required. This could be months worth of effort on many
 *  players part! :-)
 *
 *  Created June 2008, by Cooper Sherry (Gorboth)
 *    - Many thanks to Petros for cleaning up the code a bit!
 */
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include "../imbuement.h"
//#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Definitions */
//#define              STONE_NAME        "_imbuement_container_stone"

/* Global Variables */
//public object       *Other_Matches = ({});
public int           In_Socket     = 0; /* Is it fit in a craft forge? */
public string        Stone_Type    = "type";
public string        Stone_Quality = "quality";
//public int           Stone_Removal = 0; /* Is the stone being removed? */
public mapping       Stone_Descs = ([
                         "ruststone"    : "metal-like smell",
                         "snapstone"    : "freezing touch",
                         "blackstone"   : "midnight color",
                         "ampstone"     : "tingling sensation",
                         "orangestone"  : "burning touch",
                         "bluestone"    : "damp surface",
                         "sinkstone"    : "unusually heavy weight",
                         "blowstone"    : "feather-like weight",

                         "fellstone"    : "chalky surface",
                         "darkstone"    : "utterly black surface",
                         "charstone"    : "smell of cooked meat",
                         "gearstone"    : "angular shape",
                         "piestone"     : "smell of raspberries",
                         "gallstone"    : "smell of burnt hair",
                         "hoofstone"    : "leathery smell",
                         "doomstone"    : "bulky size",
                         "lifestone"    : "feeling of hope",
                         "heavenstone"  : "ring-like shape",
                         "firestone"    : "smell of burning wood",

                         "ogrestone"    : "cumbersome shape",
                         "hobbitstone"  : "minute size",
                         "dwarfstone"   : "fuzzy surface",
                         "elfstone"     : "smell of the forest",
                         "gnomestone"   : "attached bells and whistles",
                         "steelstone"   : "gleaming surface",

                         "palmstone"    : "fleshy texture",
                         "edgestone"    : "sharp sides",
                         "cleavestone"  : "blade-like edges",
                         "skewerstone"  : "pointed shape",
                         "needlestone"  : "numerous spikes",
                         "crushstone"   : "blocky shape",
                         "twinstone"    : "dual-cores",        
                         "eyestone"     : "mirror-like surface",
                         "shieldstone"  : "flat shape",
                         "deftstone"    : "supple shape",
                         "molestone"    : "earthy smell",
                         "rodentstone"  : "squeaky clean surface",
                         "lodestone"    : "complex appearance",
                         "corpsestone"  : "odor of rotting flesh",
                         "ankhstone"    : "salt-like taste",
                         "emberstone"   : "warm surface",
                         "guststone"    : "hollow feel",
                         "soilstone"    : "slimy texture",
                         "surfstone"    : "perfect rock-skipping shape",

                         "salvestone"   : "smell of herbs",
                         "tarpstone"    : "rough texture",
                         "woolstone"    : "soft texture",
                         "larsstone"    : "strange Swedish grin",
                         "riverstone"   : "remarkably clear surface",
                         "rubberstone"  : "perfectly round, bouncy shape",
                         "powderstone"  : "chakly surface",
                         "mummystone"   : "dusty surface",
                         "quietstone"   : "triangular shape",
                         "sweatstone"   : "sticky surface",
                         "duckstone"    : "ability to float on water",

                         "aspstone"     : "deep green color",
                         "balmstone"    : "glassy surface",
                         "grogstone"    : "smell of whiskey",
                         "torchstone"   : "glittering surface",
                         "nightstone"   : "moon-like shape",
                         "morningstone" : "pale blue surface",
                         "ironstone"    : "square shape",
                         "guidestone"   : "jagged edges",
                         "stingstone"   : "trapezoidal shape",
                         "wardstone"    : "cross-like shape",
                         "mercurystone" : "silvery surface",
                                ]);

/* Prototypes */
public void          create_object();
public void          init_arg(string str);
public string        query_auto_load();
//public string        query_recover();
public int           count_others();
public void          init();

public string        query_stone_type()          { return Stone_Type; }
public string        query_stone_quality()       { return Stone_Quality; }
//public int           query_stone_removal()       { return Stone_Removal; }
public void          set_in_socket(int i)        { In_Socket = i; }
public int           query_in_socket()           { return In_Socket; }
public mapping       query_stone_descs()         { return Stone_Descs; }

public void
set_stone_type(string s)
{
    string * colors = ({ 
                         "rust",
                         "snap",
                         "black",
                         "amp",
                         "orange",
                         "blue",
                         "sink",
                         "blow",

                         "fell",
                         "dark",
                         "char",
                         "gear",
                         "pie",
                         "gall",
                         "hoof",
                         "doom",
                         "life",
                         "heaven",
                         "fire",

                         "ogre",
                         "hobbit",
                         "dwarf",
                         "elf",
                         "gnome",
                         "steel",

                         "palm",
                         "edge",
                         "cleave",
                         "skewer",
                         "needle",
                         "crush",
                         "twin",        
                         "eye",
                         "shield",
                         "deft",
                         "mole",
                         "rodent",
                         "lode",
                         "corpse",
                         "ankh",
                         "ember",
                         "gust",
                         "soil",
                         "surf",

                         "salve",
                         "tarp",
                         "wool",
                         "lars",
                         "river",
                         "rubber",
                         "powder",
                         "mummy",
                         "quiet",
                         "sweat",
                         "duck",

                         "asp",
                         "balm",
                         "grog",
                         "torch",
                         "night",
                         "morning",
                         "iron",
                         "guide",
                         "sting",
                         "ward",
                         "mercury",

                         "null",
                });
    string color;

    if (!IMBUE_MASTER->check_access()) return;

    if (wildmatch("*stone", Stone_Type))
    {
        color = s[..-6]; // take off the "stone" at the end
        if (IN_ARRAY(color, colors))
        {
            remove_adj(color);
            remove_name(Stone_Type);
        }
    }
    Stone_Type = s;
    if (wildmatch("*stone", s))
    {
        color = s[..-6]; // take off the "stone" at the end
        if (IN_ARRAY(color, colors))
        {
            add_adj(color);
            add_name(s);
        }
    }

    if (Stone_Type != "nullstone")
    {
        remove_name("nullstone");
    }
}

public void
set_stone_quality(string s) 
{ 
    string * qualities = ({ "cracked", "blemished", "ordinary",
                            "unblemished", "glittering" });

    if (!IMBUE_MASTER->check_access()) return;

    if (IN_ARRAY(Stone_Quality, qualities))
    {
        remove_adj(Stone_Quality);
    }                            
    Stone_Quality = s;
    if (IN_ARRAY(s, qualities))
    {
        add_adj(Stone_Quality);
    }                            
}

/*
 * Function name:        create_object
 * Description  :        set up the stone object object
 */
public void
create_object()
{
    send_debug_message("mine_stone", "create_object called!");

    set_name("stone");
    add_name(STONE_NAME);

    set_stone_quality("ordinary");
    set_stone_type("nullstone");

    set_long("@@stone_long_description@@");
    set_short("@@stone_short_description@@");
    add_prop(OBJ_M_NO_STEAL, 1);

    setuid();
    seteuid(getuid());
} /* create_object */

public string
stone_short_description()
{
    string short_desc;

    short_desc = ((Stone_Type == "nullstone") ? "" : Stone_Quality + " ") 
               + Stone_Type;
    
    return short_desc;
}

public string
stone_long_description()
{
    string s_txt;
    string socket = ((In_Socket) ? " It is fit within the socket atop the"
                                 + " strange device. You could <pry> it"
                                 + " out if you wished.\n" : "\n");
    
    if (Stone_Type == "nullstone")
    {
        return "This is a nullstone, used by enchanters throughout the"
          + " realms to capture and store the strange magics they might"
          + " be fortunate enough to encounter. While in this state,"
          + " it is nothing more than an empty vessel.\n";
    }

    s_txt = "This is " + LANG_ADDART(Stone_Type) + ", distiguishable by its ";

    s_txt += Stone_Descs[Stone_Type] + ". ";

    switch(Stone_Quality)
    {
        case "cracked":
            s_txt += "Though its surface is laced with numerous cracks,"
                  + " there appears to be a power within this stone. ";
            break;
        case "blemished":
            s_txt += "Slight blemishes mar the surface of this stone,"
                  + " not able to diminish the sense of power that lurks"
                  + " within. ";
            break;
        case "ordinary":
            s_txt += "Though unremarkable for a stone of this type,"
                  + " it carries an unmistakable feeling of hidden power. ";
            break;
        case "unblemished":
            s_txt += "The surface of this stone is utterly spotless, and"
                  + " it nearly pulses with some hidden power. ";
            break;
        case "glittering":
            s_txt += "Glittering with energy and radiance, this stone is"
                  + " clearly filled with a great power. ";
            break;
        default:
            s_txt += "There is something wrong with this stone. ";
            break;
    }

    s_txt += "A ghostly light";

    switch(min(count_others(),2))
    {
        case 0:
            s_txt += " faintly shows beneath its surface.";
            break;
        case 1:
            s_txt += " shimmers beneath its surface.";
            break;
        case 2:
            s_txt += " pulses powerfully beneath its surface!";

            if (Stone_Quality != "glittering")
            {
                s_txt += " You get the feeling that you could <combine>"
                   + " this stone with the other two you have of its"
                   + " same type.";
            }
            break;
        default:
            s_txt += " flashes inside it!?";
            break;
    }

    return s_txt + socket;
}

/*
 * Function name: init_arg
 * Description  : This function is called when the stone recovers.
 * Arguments    : string str - the recover argument.
 */
public void
init_arg(string str)
{
    string  s_type,
            s_qual,
            foobar;

    if (!IMBUE_MASTER->check_access()) return;

    send_debug_message("imbue_stone", "init_arg called!");

    if (sscanf(str, "%stone_begin#%s#%s#%stone_end#", 
               foobar, s_type, s_qual, foobar) == 4)
    {
        set_stone_type(s_type);
        set_stone_quality(s_qual);
    }
} /* init_arg */


/*
 * Function name: query_auto_load
 * Description  : We let the players hoard these over logins. Upon recovery
 *                we keep track of the heapsize and type and quality of
 *                the stone.
 */
public string
query_auto_load()
{
    send_debug_message("imbue_stone", "query_auto_load called!");
    string file = MASTER;

    return file + ":stone_begin#"
                + Stone_Type + "#"
                + Stone_Quality + "#"
                + "stone_end#";
} /* query_auto_load */


//  What was this needed for?
#if 0
/*
 * Function name: query_recover
 * Description  : This function is called to see whether this object may
 *                recover.
 */
public string
query_recover()
{
    return 0;
} /* query_recover */
#endif

/*
 * Function name:        count_others()
 * Description  :        see if we have any matches for this particular
 *                       stone in our inventory.
 * Returns      :        int - number of others
 */
public int
count_others()
{
    object *things = all_inventory(environment(this_object()));
    int     found = 0;

    foreach(object thing: things)
    {
        if (thing->query_stone_type() == Stone_Type &&
            thing->query_stone_quality() == Stone_Quality &&
            thing != this_object())
        {
            found++;
        }
    }

    return found;
} /* count_others */


/*
 * Function name:        combine_stones
 * Description  :        Allow the player to combine three of the same
 *                       stones together to upgrade to the next level of
 *                       quality.
 * Arguments    :        string arg - What was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
combine_stones(string arg)
{
    return STONE_MASTER->try_combine(arg);
} /* combines_stones */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(combine_stones, "combine");
} /* init */


/*
 * Function name:        randomise
 * Description  :        sets stone properties randomly
 */
public void
randomise()
{
    if (!IMBUE_MASTER->check_access()) return;

    set_stone_type(one_of_list(m_indices(Stone_Descs)));
    set_stone_quality(one_of_list(({ "cracked", "blemished", "ordinary",
                            "unblemished", "glittering" })));
} /* randomise */


/*
 * Function name: enter_env
 * Description:   Track item movement
 */
public void
enter_env(object to, object from)
{
    string t = capitalize(short()) + " moved from " +
        (from ? (IS_PLAYER_OBJECT(from) ? capitalize(from->query_real_name()) :
        file_name(from)) : "the void") + " to " +
        (to ? (IS_PLAYER_OBJECT(to) ? capitalize(to->query_real_name()) :
        file_name(to)) : "the void");

    IMBUE_LOGGER->log("stones", t);
    IMBUE_LOGGER->log("stonemove", t);

    ::enter_env(to, from);
} /* enter_env */
