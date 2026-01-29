/* === smithy.c ==========================================================
 * ========================================= Raven 2001 Sex & Violence ===
 *
 * The module is a support for smithy.  Inherit this object into a monster
 * and call "add_smithy_armour" & "add_smithy_weapon"  to setup the needed
 * smithy stock.  Smithy is able to complete armour and weapon orders, and
 * can repair, polish and mend weapons and armours. Armours & weapons that
 * are created by the smithy must have a  special  "query_recover" , which
 * will save information about armour / weapon: names, adjectives, shorts,
 * long, class / hit & pen, etc.   This will save unpleasant situations in
 * which player will find himself holding an unconfigured armour / weapon.
 *
 * The module contains 2 vital hooks: "hook_smithy_select_create_armour" &
 * "hook_smithy_select_create_weapon";  which are responsible for creating
 * and configuring smithy made armours and weapons.  These hooks should be
 * masked and configured for your personal smithy. A good way to do so is:
 *
 * object
 * hook_smithy_select_create_armour(mapping design)
 * {
 *     object  armour;
 *
 *     armour= ::hook_smithy_select_create_armour(mapping design);
 *     armour->set_long("Glowing platemail.\n");
 *
 *     return armour;
 * }
 *
 * object
 * hook_smithy_select_create_weapon(mapping design)
 * {
 *     object  weapon;
 *
 *     weapon= ::hook_smithy_select_create_weapon(mapping design);
 *     weapon->set_long("Glowing sword.\n");
 *
 *     return weapon;
 * }
 *
 * === definition functions ==============================================
 * =============================================================== *** ===
 *
 * init_smithy()             function adds smithys actions to the environ-
 *                           ment, and should be called from init_living()
 *
 * add_smithy_armour(s,s,*s) function adds an armour to the smithy stock ,
 *                           the arguments are: armour type "helmet", att-
 *                           ribute "construction" ,  and options list for
 *                           the attribute ({"plate", "chain"}); call this
 *                           function several times with different attrib-
 *                           utes to set the options stock
 *
 * add_smithy_weapon(s,s,*s) function adds a  weapon to the smithy stock ,
 *                           the arguments are: weapon type "knife" , att-
 *                           ribute "construction" ,  and options list for
 *                           the attribute ({"dirk", "dagger"}); call this
 *                           function several times with different attrib-
 *                           utes to set the options stock
 *
 * =======================================================================
 * =============================================================== *** ===
 */

inherit "/lib/trade";
#include <exec.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

/*
 * === global variables ==================================================
 * =============================================================== *** ===
 */

#define ARMOUR_PATH        ("/std/armour")
#define WEAPON_PATH        ("/std/weapon")

#define REPAIR_COST(item)  (item->query_prop(OBJ_I_VALUE) / 20)
#define POLISH_COST(item)  (item->query_prop(OBJ_I_VALUE) / 20)
#define MEND_COST(item)    ((item->check_armour() ?           \
                            F_VALUE_ARMOUR(item->query_ac()) :\
                            F_VALUE_WEAPON(item->query_pen(), \
                            item->query_hit())) * 2)
#define OBTAIN_COST(item)  (item->query_prop(OBJ_I_VALUE) *  4)

#define MODULE_ARMOUR      (   0)
#define MODULE_WEAPON      (   1)

#define SMITHY_S_CLIENT    ("_smithy_s_client")

#define WI                 (W_IMPALE  )
#define WS                 (W_SLASH   )
#define WB                 (W_BLUDGEON)

#define SMITHY_METALS /*  default metal's modifiers   */ \
([/* Metals                AC/WP   DULL  WEIGHT  COST */ \
  "gold"               :({  0.65,  3.00,  2.40, 10.00 }),\
  "silver"             :({  0.65,  2.00,  1.50,  5.00 }),\
  "bronze"             :({  0.70,  1.90,  1.20,  0.75 }),\
  "iron"               :({  0.85,  1.50,  0.80,  0.80 }),\
  "steel"              :({  1.00,  1.00,  1.00,  1.00 }),\
])

#define SMITHY_ARMOUR  /* default armours configurations   */ \
([                     /* TYPE      AC    IM SM BM  VOLUME */ \
  "ringmail cap"       :({A_HEAD  , 14, ({-2, 4,-2}),  400 }),\
  "chain coif"         :({A_HEAD  , 17, ({-4, 6,-2}),  800 }),\
  "double mail coif"   :({A_HEAD  , 21, ({-2, 2, 0}), 1000 }),\
  "plate helm"         :({A_HEAD  , 23, ({ 0, 0, 0}), 1100 }),\
  "tabarded helm"      :({A_HEAD  , 25, ({ 0, 0, 0}), 1200 }),\
  "visored helm"       :({A_HEAD  , 29, ({ 0, 0, 0}), 1500 }),\
  "great helm"         :({A_HEAD  , 35, ({ 0, 0, 0}), 1500 }),\
  "ringmail"           :({A_TORSO , 15, ({-2, 4,-2}), 5000 }),\
  "bezainted mail"     :({A_TORSO , 15, ({ 2, 2,-4}), 8000 }),\
  "scalemail"          :({A_TORSO , 17, ({ 2, 2,-4}), 8000 }),\
  "splint mail"        :({A_TORSO , 18, ({ 2, 2,-4}), 8000 }),\
  "brigandine"         :({A_TORSO , 20, ({ 2, 2,-4}), 8000 }),\
  "chainmail"          :({A_TORSO , 22, ({-4, 6,-2}), 8000 }),\
  "double mail"        :({A_TORSO , 25, ({-2, 2, 0}), 8000 }),\
  "bar mail"           :({A_TORSO , 28, ({-2, 2, 0}), 8000 }),\
  "augmented mail"     :({A_TORSO , 30, ({-2, 2, 0}), 8000 }),\
  "banded mail"        :({A_TORSO , 32, ({ 0, 0, 0}), 8000 }),\
  "breastplate"        :({A_TORSO , 34, ({ 0, 0, 0}), 8500 }),\
  "platemail"          :({A_TORSO , 35, ({ 0, 0, 0}), 9000 }),\
  "scalemail bracers"  :({A_ARMS  , 17, ({ 2, 2,-4}), 1000 }),\
  "chainmail bracers"  :({A_ARMS  , 22, ({-4, 6,-2}), 1200 }),\
  "platemail bracers"  :({A_ARMS  , 35, ({ 0, 0, 0}), 1400 }),\
  "scalemail greaves"  :({A_LEGS  , 17, ({ 2, 2,-4}), 1200 }),\
  "chainmail greaves"  :({A_LEGS  , 22, ({-4, 6,-2}), 1400 }),\
  "platemail greaves"  :({A_LEGS  , 35, ({ 0, 0, 0}), 1600 }),\
  "chainmail gauntlets":({A_HANDS , 22, ({-4, 6,-2}),  300 }),\
  "platemail gauntlets":({A_HANDS , 35, ({ 0, 0, 0}),  300 }),\
  "scalemail boots"    :({A_FEET  , 17, ({ 2, 2,-4}),  500 }),\
  "chainmail boots"    :({A_FEET  , 22, ({-4, 6,-2}),  500 }),\
  "platemail boots"    :({A_FEET  , 35, ({ 0, 0, 0}),  500 }),\
  "buckler"            :({A_SHIELD, 18, ({ 0, 0, 0}),  800 }),\
  "curved heater"      :({A_SHIELD, 23, ({ 0, 0, 0}), 4000 }),\
  "spiked shield"      :({A_SHIELD, 29, ({ 0, 0, 0}), 6000 }),\
  "large shield"       :({A_SHIELD, 35, ({ 0, 0, 0}), 6000 }),\
])

#define SMITHY_WEAPON  /* default weapons configurations              */ \
([                     /* TYPE          WH  WP   DAMAGE    GRIP   VOLU*/ \
  "knife"              :({W_KNIFE     , 10, 11,    WS   , W_ANYH, 1000}),\
  "ballock knife"      :({W_KNIFE     , 10, 12,    WS   , W_ANYH, 1000}),\
  "dagger"             :({W_KNIFE     , 14, 14, WI|WS   , W_ANYH, 1000}),\
  "rondel dagger"      :({W_KNIFE     , 14, 15, WI|WS   , W_ANYH, 1000}),\
  "dirk"               :({W_KNIFE     , 14, 13, WI|WS   , W_ANYH, 1000}),\
  "swiss dagger"       :({W_KNIFE     , 14, 15, WI|WS   , W_ANYH, 1000}),\
  "main gauche"        :({W_KNIFE     , 14, 14, WI|WS   , W_LEFT, 1000}),\
  "cinquedea"          :({W_KNIFE     , 16, 14, WI|WS   , W_ANYH, 1000}),\
  "stilleto"           :({W_KNIFE     , 12, 16, WI      , W_ANYH, 1000}),\
  "misericord"         :({W_KNIFE     , 12, 16, WI      , W_ANYH, 1000}),\
  "bodkin"             :({W_KNIFE     , 12, 14, WI      , W_ANYH, 1000}),\
  "scramasax"          :({W_SWORD     , 18, 19,    WS   , W_ANYH, 2000}),\
  "falchion"           :({W_SWORD     , 21, 25,    WS   , W_ANYH, 2000}),\
  "scimitar"           :({W_SWORD     , 30, 31,    WS   , W_ANYH, 2000}),\
  "gladius"            :({W_SWORD     , 21, 16, WI      , W_ANYH, 2000}),\
  "longsword"          :({W_SWORD     , 29, 25, WI|WS   , W_ANYH, 2000}),\
  "broadsword"         :({W_SWORD     , 28, 27,    WS   , W_ANYH, 2000}),\
  "rapier"             :({W_SWORD     , 35, 20, WI      , W_ANYH, 2000}),\
  "courtelas"          :({W_SWORD     , 27, 30,    WS   , W_BOTH, 4000}),\
  "bastard sword"      :({W_SWORD     , 33, 28, WI|WS   , W_BOTH, 4000}),\
  "estoc"              :({W_SWORD     , 22, 21,    WS   , W_BOTH, 4000}),\
  "two-handed sword"   :({W_SWORD     , 32, 32,    WS   , W_BOTH, 4000}),\
  "battle axe"         :({W_AXE       , 22, 29,    WS   , W_ANYH, 3000}),\
  "waraxe"             :({W_AXE       , 26, 26,    WS   , W_ANYH, 3000}),\
  "broad axe"          :({W_AXE       , 21, 37,    WS   , W_BOTH, 3000}),\
  "bardiche"           :({W_AXE       , 20, 31,    WS   , W_BOTH, 3000}),\
  "lochaber axe"       :({W_AXE       , 24, 35, WI|WS   , W_BOTH, 3000}),\
  "double-headed axe"  :({W_AXE       , 24, 34,    WS   , W_BOTH, 3000}),\
  "mattock"            :({W_AXE       , 26, 34,    WS|WB, W_BOTH, 3000}),\
  "spiked club"        :({W_CLUB      , 20, 17, WI|   WB, W_ANYH, 2500}),\
  "flail"              :({W_CLUB      , 20, 15,       WB, W_ANYH, 2500}),\
  "morningstar"        :({W_CLUB      , 24, 27,       WB, W_ANYH, 2500}),\
  "mace"               :({W_CLUB      , 29, 20,       WB, W_ANYH, 2500}),\
  "warhammer"          :({W_CLUB      , 21, 30, WI|   WB, W_ANYH, 2500}),\
  "glaive"             :({W_POLEARM   , 21, 28,    WS   , W_BOTH, 3000}),\
  "fauchard"           :({W_POLEARM   , 23, 30, WI|WS   , W_BOTH, 3000}),\
  "guisarme"           :({W_POLEARM   , 27, 32, WI|WS   , W_BOTH, 3000}),\
  "halberd"            :({W_POLEARM   , 26, 39, WI|WS   , W_BOTH, 3000}),\
  "staff"              :({W_POLEARM   , 32, 32,       WB, W_BOTH, 3000}),\
  "quarterstaff"       :({W_POLEARM   , 34, 10,       WB, W_BOTH, 3000}),\
  "spear"              :({W_POLEARM   , 22, 16, WI      , W_BOTH, 3000}),\
  "trident"            :({W_POLEARM   , 32, 24, WI      , W_BOTH, 3000}),\
  "luzern hammer"      :({W_POLEARM   , 23, 35, WI      , W_BOTH, 3000}),\
  "partisan"           :({W_POLEARM   , 23, 19, WI      , W_BOTH, 3000}),\
  "roncone"            :({W_POLEARM   , 25, 21, WI      , W_BOTH, 3000}),\
  "corseques"          :({W_POLEARM   , 24, 25, WI      , W_BOTH, 3000}),\
  "military fork"      :({W_POLEARM   , 22, 22, WI      , W_BOTH, 3000}),\
])  

mapping smithy_armour = ([]), /* holding armour attributes and options  */
        smithy_weapon = ([]), /* holding weapon attributes and options  */
        smithy_design = ([]); /* holding information about the order    */
object  smithy_armory       ; /* holding produced weapons and armours   */
int     smithy_crafts =    0; /* flag determining if the smithy is busy */

/*
 * === supporting functions ==============================================
 * =============================================================== *** ===
 */

/*
 * Function name : create_smithy_armory
 * Description   : creates a container to hold the produced items in
 * Arguments     : void    - no arguments
 * Returns       : void    - nothing is returned
 */

void
create_smithy_armory()
{
    if (objectp(smithy_armory) || objectp(smithy_armory =
        present("_smithy_armory", ENV(TO))))       return;

    setuid(); seteuid(getuid());
    smithy_armory = clone_object("/std/container");

    smithy_armory->set_name("_smithy_armory");
    smithy_armory->set_no_show();
    smithy_armory->add_prop(OBJ_I_WEIGHT     , 0);
    smithy_armory->add_prop(OBJ_I_VOLUME     , 0);
    smithy_armory->add_prop(CONT_I_MAX_WEIGHT, 1000000);
    smithy_armory->add_prop(CONT_I_MAX_VOLUME, 1000000);
    smithy_armory->add_prop(OBJ_M_NO_GET     , 1);
    smithy_armory->move(ENV(TO), 1);
}

/*
 * Function name : filter_smithy_armory
 * Description   : filters out objects that belong to the client
 * Arguments     : object  - the object
 *                 string  - the client
 * Returns       : int     - 1 if object belongs to client and 0 if not
 */

int
filter_smithy_armory(object item, string client)
{
    /* oportunity to remove objects of logged out players */
    if (!objectp(find_player(item->query_prop(SMITHY_S_CLIENT))))
    {
       item->remove_object();
       return 0;
    }

    return (item->query_prop(SMITHY_S_CLIENT) == client);
}

/*
 * Function name : format_smithy_option
 * Description   : formats an option list in rows
 * Arguments     : string  - options header
 *                 string* - a string list
 *                 int     - field size
 *                 int     - amount of rows
 * Returns       : string  - string fomated in rows
 */

string
format_smithy_option(string header, string *option, int fields, int rows)
{
    int     amount = sizeof(option), length, n = -1;
    string  output = "";

    fields -= (fields % rows);
    length  = (fields / rows);
    
    output += sprintf("%-*s\n", fields, "");
    output += sprintf("%|*s\n", fields, "- " + header + " -");

    while (++n < amount)
    {
       output += sprintf("%-*s", length, option[n]);
     
       if (!((n + 1) % rows)) output += "\n";
    }

    if (n % rows) 
       output += sprintf("%-*s\n", (rows-(n % rows))*length, "");

    return (" | " + implode(explode(output, "\n"), " | \n | ") + " |\n");
}

/*
 * === definition functions ==============================================
 * =============================================================== *** ===
 */

/*
 * Function name : add_smithy_armour
 * Description   : sets options list for the armour aspect, player will be
 *                 promted later to choose one of these options, the func-
 *                 tion should be called several times with different asp-
 *                 ects and options for same armour type
 * Arguments     : string  - armour type, like "helmet"
 *                 string  - aspect name, like "metal"
 *                 string* - option list, like ({"copper", "silver"})
 * Returns       : void    - nothing is returned
 */

void
add_smithy_armour(string armour, string aspect, string *option)
{
    if (!strlen(armour) || !strlen(aspect) || !sizeof(option))  return;

    if (!mappingp(smithy_armour[armour])) smithy_armour[armour] = ([]);

    smithy_armour[armour][aspect] = option;
}

/*
 * Function name : query_smithy_armour
 * Description   : returns information stored in armour mapping
 * Arguments     : string  - armour type, if 0 returns outer map indices
 *                 aspect  - aspect name, if 0 returns inner map indices
 * Returns       : string* - array of outer/inner map indices or options
 */

varargs string*
query_smithy_armour(string armour = 0, string aspect = 0)
{
    mapping data = smithy_armour;
    
    if (!armour)  return (m_sizeof(data) ? m_indices(data)        : ({}));
    if (!aspect)  return (data[armour]  ? m_indices(data[armour]) : ({}));
    
    return (data[armour][aspect] ? data[armour][aspect] : ({}));
}

/*
 * Function name : add_smithy_weapon
 * Description   : sets options list for the weapon aspect, player will be
 *                 promted later to choose one of these options, the func-
 *                 tion should be called several times with different asp-
 *                 ects and options for same weapon type
 * Arguments     : string  - weapon type, like "sword"
 *                 string  - aspect name, like "metal"
 *                 string* - option list, like ({"copper", "silver"})
 * Returns       : void    - nothing is returned
 */

void
add_smithy_weapon(string weapon, string aspect, string *option)
{
    if (!strlen(weapon) || !strlen(aspect) || !sizeof(option))  return;

    if (!mappingp(smithy_weapon[weapon])) smithy_weapon[weapon] = ([]);

    smithy_weapon[weapon][aspect] = option;
}

/*
 * Function name : query_smithy_weapon
 * Description   : returns information stored in weapon mapping
 * Arguments     : string  - weapon type, if 0 returns outer map indices
 *                 aspect  - aspect name, if 0 returns inner map indices
 * Returns       : string* - array of outer/inner map indices or options
 */

varargs string*
query_smithy_weapon(string weapon = 0, string aspect = 0)
{
    mapping data = smithy_weapon;
    
    if (!weapon)  return (m_sizeof(data) ? m_indices(data)        : ({}));
    if (!aspect)  return (data[weapon]  ? m_indices(data[weapon]) : ({}));
    
    return (data[weapon][aspect] ? data[weapon][aspect] : ({}));
}

/*
 * Function name : add_smithy_design
 * Description   : adds information to the smithy design record
 * Arguments     : mixed   - client name or object
 *                 string  - aspect name
 *                 string  - option
 * Returns       : void    - nothing is returned
 */

nomask void
add_smithy_design(mixed client, string aspect, string option)
{
    client = objectp(client) ? client->query_real_name() : client;

    if (!client || !strlen(aspect) || !strlen(option))          return;

    if (!mappingp(smithy_design[client])) smithy_design[client] = ([]);

    smithy_design[client][aspect] = option;
}

/*
 * Function name : remove_smithy_design
 * Description   : removes design or design aspect from the records
 * Arguments     : mixed   - client name or object
 *                 string  - aspect, if 0 whole the design removed
 * Returns       : void    - nothing is returned
 */

nomask varargs void
remove_smithy_design(mixed client, string aspect = 0)
{
    client = objectp(client) ? client->query_real_name() : client;

    if (!aspect)  
    {
       smithy_design = m_delete(smithy_design, client);
       return;
    }

    if (smithy_design[client])
       smithy_design[client] = m_delete(smithy_design[client], aspect);
}

/*
 * Function name : query_smithy_design
 * Description   : returns information stored in the smithy design map
 * Arguments     : mixed   - client name or object, if 0 indices returned
 *                 string  - requested aspect, if 0 subindices returned
 * Returns       : mixed   - information stored under the aspect
 */

nomask varargs mixed
query_smithy_design(mixed client = 0, string aspect = 0)
{
    mapping data = smithy_design;
    object  player;
    string *member = m_indices(smithy_design);
    int     n      = sizeof(member);
    
    /* an oportunity to clean up the junk records */
    while (--n >= 0)
    {
        player = find_player(member[n]);

        if (!objectp(player) || (ENV(player) != ENV(TO)))
           remove_smithy_design(member[n]);
    }
    
    client = objectp(client) ? client->query_real_name() : client;

    if (!client)  return (m_sizeof(data) ? m_indices(data)         : 0);
    if (!aspect)  return (data[client]   ? m_indices(data[client]) : 0);
    
    return (data[client][aspect] ? data[client][aspect] : 0);
}

/*
 * Function name : add_smithy_armory
 * Description   : adds produced object into the smithy armory
 * Arguments     : mixed   - client name/object
 *                 object  - armour/weapon
 * Returns       : void    - nothing is returned
 */

nomask void
add_smithy_armory(mixed client, object item)
{
    client = objectp(client) ? client->query_real_name() : client;

    if (!objectp(smithy_armory)) create_smithy_armory();
    
    item->add_prop(SMITHY_S_CLIENT, client);
    item->move(smithy_armory, 1);
}

/*
 * Function name : query_smithy_armory
 * Description   : returns contents of ready production stock
 * Arguments     : mixed   - the client, if 0 whole the stock returned
 * Returns       : object* - client products or all the products
 */

nomask varargs object*
query_smithy_armory(mixed client = 0)
{
    object *item;
    
    if (!objectp(smithy_armory)) create_smithy_armory();

    item = INV(smithy_armory);
    
    if (client)
    {
        client = objectp(client) ? client->query_real_name() : client;
        item = filter(item, &filter_smithy_armory(, client));
    }

    return item;
}

/*
 * Function name : set_smithy_crafts
 * Description   : sets smithy busy flag making him busy or unbusy
 * Arguments     : int     - 1 means busy, 0 means not busy
 * Returns       : void    - nothing is returned
 */

void
set_smithy_crafts(int number)
{
    smithy_crafts = number;
}

/*
 * Function name : query_smithy_crafts
 * Description   : checks if the smithy is busy making an order
 * Arguments     : none    - no arguments
 * Returns       : int     - 1 means busy, 0 means not busy
 */

int
query_smithy_crafts()
{
    return smithy_crafts;
}

/*
 * Function name : query_smithy_config
 * Description   : returns smithy default armour, weapon or metal config
 *                 the settings are configured under SMIHTY_ARMOUR,
 *                 SMITHY_WEAPON and SMITHY_METALS
 * Arguments     : string  - the type armour, weapon or metal
 *                 string  - the armour/weapon/metal name
 * Returns       : mixed   - array of default settings for the name
 */

mixed
query_smithy_config(string type, string name)
{
    if (type == "armour")  return SMITHY_ARMOUR[name];
    if (type == "weapon")  return SMITHY_WEAPON[name];
    if (type ==  "metal")  return SMITHY_METALS[name];
    return ({});
}

/*
 * === hooked functions ==================================================
 * =============================================================== *** ===
 */

/*
 * Function name : appeal
 * Description   : the appeal of the module to the player, this hook helps
 *                 in smithy behaviour creating, for example if your smith
 *                 hates dwarves then this hook can return "filthy dwarf"
 *                 if the player is dwarf, or if the smith is funny he can
 *                 call each hobbit "furball"
 * Arguments     : object  - player object
 * Returns       : string  - appeal string
 */

string
appeal(object player)
{
    string  *member = explode(player->query_art_name(), " ");

    return implode(member - ({"a", "an"}), " ");
}

/*
 * Function name : hook_smithy_answer_dark_room
 * Description   : refuse to deal with player when the room is dark
 * Arguments     : void    - no arguments
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_answer_dark_room()
{
    command("say Uhmm, you wouldn't by any chance have a torch handy?");
    command("say It's too dark for me to do business.");
    return 1;
}

/*
 * Function name : hook_smithy_answer_invisible
 * Description   : refuse to deal with player when can't see him
 * Arguments     : void    - no arguments
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_answer_invisible()
{
    command("say Uhmm, where are you hiding? I can't see you!");
    command("peer suspiciously");
    return 1;
}

/*
 * Function name : hook_smithy_repair_faulty_syntax
 * Description   : called when player tries to repair with bad syntax
 * Arguments     : string  - argument writen by the player
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_repair_faulty_syntax(string letter)
{
    notify_fail(CAP(query_verb()) + " what?\n");
    return 0;
}

/*
 * Function name : hook_smithy_repair_faulty_object
 * Description   : called when player tries to repair not weapon or armour
 * Arguments     : object  - the object player tries to repair
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_repair_faulty_object(object item)
{
    command("say " + CAP(LANG_THESHORT(item)) + " is not an armour, it"  +
            " isn't a weapon either, how should I repair this?");
    command("smile merrily");
    return 1;
}

/*
 * Function name : hook_smithy_repair_cannot_repair
 * Description   : called when object cannot be repaired any firther
 * Arguments     : object  - the object
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_repair_cannot_repair(object item)
{
    string  verb = (item->check_weapon() ? "sharpened" : "repaired");
    
    command("say " + CAP(LANG_THESHORT(item)) + " cannot be " + verb +
            " any further, " + appeal(TP) + "!");
    return 1;
}

/*
 * Function name : hook_smithy_repair_cannot_afford
 * Description   : called when player cannot afford the repairing
 * Arguments     : object  - the object player tries to repair
 *                 int     - the cost of repairing
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_repair_cannot_afford(object item, int cost)
{
    command("say You cannot afford to have " + LANG_THESHORT(item) +
            " sharpened, " + appeal(TP) + ".");
    command("gesture");
    return 1;
}

/*
 * Function name : hook_smithy_repair_notify_repair
 * Description   : notify the player about the repair
 * Arguments     : object  - the repaired object
 *                 int*    - array of coins player payed
 *                 int*    - array of coins player got back
 * Returns       : void    - nothing is returned
 */

void
hook_smithy_repair_notify_repair(object item, int* charge, int* change)
{
    string  verb = (item->check_weapon() ? " sharpens " : " repairs "),
            name = LANG_THESHORT(item);
    
    TP->catch_msg("You give " + name + " to " + QTNAME(TO) + ".\n");
    say(QCTNAME(TP)+" gives " + name + " to " + QTNAME(TO) + ".\n");
    tell_room(ENV(TO), QCTNAME(TO) + verb + name + ".\n");
    TP->catch_msg(QCTNAME(TO) + " gives you " + name + ".\n");
    say(QCTNAME(TO)+" gives " + name + " to " + QTNAME(TP) + ".\n");

    TP->catch_msg("You pay " + QTNAME(TO) + " " + text(charge) + ".\n");
    if (strlen(text(change))) write("You get "+text(change)+" back.\n");
}

/*
 * Function name : hook_smithy_polish_faulty_syntax
 * Description   : called when player tries to polish with bad syntax
 * Arguments     : string  - argument writen by the player
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_polish_faulty_syntax(string letter)
{
    notify_fail(CAP(query_verb()) + " what?\n");
    return 0;
}

/*
 * Function name : hook_smithy_polish_faulty_object
 * Description   : called when player tries to polish not weapon or armour
 * Arguments     : object  - the object player tries to polish
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_polish_faulty_object(object item)
{
    command("say " + CAP(LANG_THESHORT(item)) + " is not a weapon, how"  +
            " should I polish it?");
    command("smile merrily");
    return 1;
}

/*
 * Function name : hook_smithy_polish_cannot_polish
 * Description   : called when object cannot be polished any firther
 * Arguments     : object  - the object
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_polish_cannot_polish(object item)
{
    command("say " + CAP(LANG_THESHORT(item)) + " cannot be polished" +
            " any further, " + appeal(TP) + "!");
    return 1;
}

/*
 * Function name : hook_smithy_polish_cannot_afford
 * Description   : called when player cannot afford the polishing
 * Arguments     : object  - the object player tries to polish
 *                 int     - the cost of polishing
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_polish_cannot_afford(object item, int cost)
{
    command("say You cannot afford to have " + LANG_THESHORT(item) +
            " polished, " + appeal(TP) + ".");
    command("gesture");
    return 1;
}

/*
 * Function name : hook_smithy_polish_notify_polish
 * Description   : notify the player about the polish
 * Arguments     : object  - the polished object
 *                 int*    - array of coins player payed
 *                 int*    - array of coins player got back
 * Returns       : void    - nothing is returned
 */

void
hook_smithy_polish_notify_polish(object item, int* charge, int* change)
{
    string  name = LANG_THESHORT(item);
    
    TP->catch_msg("You give " + name + " to " + QTNAME(TO) + ".\n");
    say(QCTNAME(TP)+" gives " + name + " to " + QTNAME(TO) + ".\n");
    tell_room(ENV(TO),   QCTNAME(TO) + " polishes " + name + ".\n");
    TP->catch_msg(QCTNAME(TO) + " gives you " + name + ".\n");
    say(QCTNAME(TO)+" gives " + name + " to " + QTNAME(TP) + ".\n");

    TP->catch_msg("You pay " + QTNAME(TO) + " " + text(charge) + ".\n");
    if (strlen(text(change))) write("You get "+text(change)+" back.\n");
}

/*
 * Function name : hook_smithy_mend_faulty_syntax
 * Description   : called when player tries to mend with bad syntax
 * Arguments     : string  - argument writen by the player
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_mend_faulty_syntax(string letter)
{
    notify_fail(CAP(query_verb()) + " what?\n");
    return 0;
}

/*
 * Function name : hook_smithy_mend_faulty_object
 * Description   : called when player tries to mend not weapon or armour
 * Arguments     : object  - the object player tries to polish
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_mend_faulty_object(object item)
{
    command("say " + CAP(LANG_THESHORT(item)) + " is not an armour, it"  +
            " isn't a weapon either, how should I mend this?");
    command("smile merrily");
    return 1;
}

/*
 * Function name : hook_smithy_mend_cannot_mend
 * Description   : called when object is not broken
 * Arguments     : object  - the object
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_mend_cannot_mend(object item)
{
    command("say " + CAP(LANG_THESHORT(item)) + " isn't broken, " +
            appeal(TP) + "!");
    return 1;
}

/*
 * Function name : hook_smithy_mend_cursed_object
 * Description   : called when object player tries to mend is magical
 * Arguments     : object  - the object
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_mend_cursed_object(object item)
{
    command("say I can't mend " + LANG_THESHORT(item) + ".");
    command("say My deep apologies, " + appeal(TP));
    return 1;
}

/*
 * Function name : hook_smithy_mend_cannot_afford
 * Description   : called when player cannot afford the mending
 * Arguments     : object  - the object player tries to mend
 *                 int     - the cost of mending
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_mend_cannot_afford(object item, int cost)
{
    command("say You cannot afford to have " + LANG_THESHORT(item) +
            " mended, " + appeal(TP) + ".");
    command("gesture");
    return 1;
}

/*
 * Function name : hook_smithy_mend_notify_mend
 * Description   : notify the player about the mending
 * Arguments     : object  - the mended object
 *                 int*    - array of coins player payed
 *                 int*    - array of coins player got back
 * Returns       : void    - nothing is returned
 */

void
hook_smithy_mend_notify_mend(object item, int* charge, int* change)
{
    string  name = LANG_THESHORT(item);
    
    TP->catch_msg("You give " + name + " to " + QTNAME(TO) + ".\n");
    say(QCTNAME(TP)+" gives " + name + " to " + QTNAME(TO) + ".\n");
    tell_room(ENV(TO),   QCTNAME(TO) + " mends " + name + ".\n");
    TP->catch_msg(QCTNAME(TO) + " gives you " + name + ".\n");
    say(QCTNAME(TO)+" gives " + name + " to " + QTNAME(TP) + ".\n");

    TP->catch_msg("You pay " + QTNAME(TO) + " " + text(charge) + ".\n");
    if (strlen(text(change))) write("You get "+text(change)+" back.\n");
}

/*
 * Function name : hook_smithy_browse_faulty_syntax
 * Description   : called when browse syntax is wrong
 * Arguments     : string  - argument writen by the player
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_browse_faulty_syntax(string letter)
{
    if (!letter)
    {
       notify_fail(CAP(query_verb()) + " what?\n");
       return 0;
    }

    command("say What do you want to browse, " + appeal(TP) + "? Armours"+
            ", weapons or orders?");
    command("confused");
    return 1;
}

/*
 * Function name : hook_smithy_browse_armour_browse
 * Description   : shows a list of armours or specific armour attributes
 * Arguments     : string  - argument written by the player
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_browse_armour_browse(string armour)
{
    int     n = -1,  amount;
    string  output, *aspect, *option;
    
    if ((armour == "armours") || (armour == "armour"))
    {
       command("say " + CAP(appeal(TP))+", you came to the right place.");
       command("say I can make these armours for you:");
       command("say " + CAP(COMPOSITE_WORDS(query_smithy_armour())) +".");
       command("say You can ask me about each one of these armours.");
       command("smile .");
       return 1;
    }
    
    command("nod " + OB_NAME(TP));
    command("emote reaches for a shelf and takes a notebook.");
    command("emote starts to list the notebook.");
    command("say Ahh here it is! My " + armour + " manual!");

    TP->catch_msg(QCTNAME(TO) +" shows the notebook to you.\n");
    say(QCTNAME(TO)+" shows the notebook to "+QTNAME(TP)+".\n");

    aspect = query_smithy_armour(armour);
    amount = sizeof(aspect);
    
    output = sprintf(" o%'-'|62so\n", "oooO  "+CAP(armour)+
             " Ordering  Oooo");
    
    while (++n < amount)
    {
       option  = query_smithy_armour(armour, aspect[n]);
       output += format_smithy_option(aspect[n], option, 60, 3);
    }

    output += sprintf(" o%'-'|62so\n", "oooOOooo");

    TP->more(output);
    return 1;
}

/*
 * Function name : hook_smithy_browse_weapon_browse
 * Description   : shows a list of weapons or specific weapon attributes
 * Arguments     : string  - argument written by the player
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_browse_weapon_browse(string weapon)
{
    int     n = -1,  amount;
    string  output, *aspect, *option;
    
    if ((weapon == "weapons") || (weapon == "weapon"))
    {
       command("say " + CAP(appeal(TP))+", you came to the right place.");
       command("say I can make these weapons for you:");
       command("say " + CAP(COMPOSITE_WORDS(query_smithy_weapon())) +".");
       command("say You can ask me about each one of these weapons.");
       command("smile .");
       return 1;
    }
    
    command("nod " + OB_NAME(TP));
    command("emote reaches for a shelf and takes a notebook.");
    command("emote starts to list the notebook.");
    command("say Ahh here it is! My " + weapon + " manual!");

    TP->catch_msg(QCTNAME(TO) +" shows the notebook to you.\n");
    say(QCTNAME(TO)+" shows the notebook to "+QTNAME(TP)+".\n");

    aspect = query_smithy_weapon(weapon);
    amount = sizeof(aspect);
    
    output = sprintf(" o%'-'|62so\n", "oooO  "+CAP(weapon)+
             " Ordering  Oooo");
    
    while (++n < amount)
    {
       option  = query_smithy_weapon(weapon, aspect[n]);
       output += format_smithy_option(aspect[n], option, 60, 3);
    }

    output += sprintf(" o%'-'|62so\n", "oooOOooo");

    TP->more(output);
    return 1;
}

/*
 * Function name : hook_smithy_browse_armory_browse
 * Description   : shows the ready for collection armours and weapons
 * Arguments     : string  - argument writen by the player
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_browse_armory_browse(string letter)
{
    int     size;
    object *item = query_smithy_armory(TP);

    command("say " + CAP(letter) + "? Ahh your orders!");

    command("emote browses over the racks.");

    if (size = sizeof(item))
    {
       command("say " + CAP(COMPOSITE_DEAD(item)) + (size==1 ? " is" : 
               " are") + " awaiting for your coppers!");
       command("grin merrily");
       command("say You can always 'pay' and grab your items, " + 
               appeal(TP) + ".");
       return 1;
    }
    
    command("say Hmm... Nothing I see in the racks is yours, " + 
            appeal(TP) + ".");
    
    return 1;
}

/*
 * Function name : hook_smithy_select_faulty_syntax
 * Description   : called when select syntax is wrong
 * Arguments     : string  - argument writen by the player
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_select_faulty_syntax(string letter)
{
    notify_fail(CAP(query_verb()) + " what?\n");
    return 0;
}

/*
 * Function name : hook_smithy_select_notify_busy
 * Description   : called when smithy is busy with a selection
 * Arguments     : void    - no arguments
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_select_notify_busy()
{
    command("say I am currently busy with an order, " + appeal(TP) + 
            ", please wait a little.");
    command("smile " + OB_NAME(TP));
    return 1;
}

/*
 * Function name : hook_smithy_select_notify_header
 * Description   : writes a header for armour/weapon selection
 * Arguments     : string  - argument writen by the player armour/weapon
 * Returns       : void    - nothing is returned
 */

void
hook_smithy_select_notify_header(string letter)
{
    command("say Excellent! You may 'cancel order' at any time.");
}

/*
 * Function name : hook_smithy_select_notify_prompt
 * Description   : writes a prompt with aspect and options to choose
 * Arguments     : string  - aspect name
 *                 string* - option list
 * Returns       : void    - nothing is returned
 */

void
hook_smithy_select_notify_prompt(string aspect, string *option)
{
    command("say What kind of " + aspect + " would you like?");
    command("say I have the following "+LANG_PWORD(aspect)+" available:");
    command("say " + CAP(COMPOSITE_WORDS(option)) + ".");
}

/*
 * Function name : hook_smithy_select_faulty_option
 * Description   : called when player selects unproper option
 * Arguments     : string  - the unproper option
 *                 string  - aspect name
 *                 string* - option list
 * Returns       : void    - nothing is returned
 */

void
hook_smithy_select_faulty_option(string letter, string aspect,
    string *option)
{
    command("say Hmm I don't have " + aspect + " named " + letter + ".");
    command("say Or mayhaps you wanted to 'cancel order'?");
    command("confused");
}

/*
 * Function name : hook_smithy_select_notify_cancel
 * Description   : called when player cancels the selection
 * Arguments     : void    - no arguments
 * Returns       : void    - nothing is returned
 */

void
hook_smithy_select_notify_cancel()
{
    write("You decide to cancel your order.\n");
    say(QCTNAME(TP) + " cancels " + TP->query_possessive() + " order.\n");
    command("say Next, please!");
}

/*
 * Function name : hook_smithy_select_create_armour
 * Description   : called to create and configure smithy made armour
 * Arguments     : mapping - the design mapping
 * Returns       : object  - armour object
 */

object
hook_smithy_select_create_armour(mapping design)
{
    string  atype  = design["type"] ,   consr  = design["construction"],
            metal  = design["metal"],   color  = design["color"],
            linin  = design["lining"],  ornam  = design["ornament"];
    mixed   config = query_smithy_config("armour", consr),
            metals = query_smithy_config("metal" , metal);
    string  prep   = "is";
    object  item;

    setuid(); seteuid(getuid());
    item = clone_object(ARMOUR_PATH);

    item->set_at(config[0]);
    item->set_ac(ftoi(metals[0] * itof(config[1])));
    item->set_am(config[2]);
    item->set_likely_cond(ftoi(metals[1] * 2.0));

    item->add_prop(OBJ_I_WEIGHT, ftoi(metals[2] * itof(
          F_WEIGHT_DEFAULT_ARMOUR(item->query_ac(), item->query_at()))));
    item->add_prop(OBJ_I_VOLUME, config[3]);
    item->add_prop(OBJ_I_VALUE , ftoi(metals[3] * itof(
          F_VALUE_ARMOUR(item->query_ac()))));

    item->set_name(({consr, atype}));
    item->set_adj(({ ornam ? ornam : color, ornam ? color : metal }));
    item->set_short(implode(item->query_adjs()[0..1], " ") + " " + 
             item->query_name());

    if (member_array(item->query_at(),({A_ARMS, A_HANDS, A_LEGS,
        A_FEET})) >= 1)
    {
       prep = "are";
       item->set_pshort("pairs of " + item->query_short());
       item->set_short("pair of " + item->query_short());
    }

    item->set_long(CAP(LANG_ADDART(item->query_short())) + ".\n");

    return item;
}

/*
 * Function name : hook_smithy_select_create_weapon
 * Description   : called to create and configure smithy made weapon
 * Arguments     : mapping - the design mapping
 * Returns       : object  - weapon object
 */

object
hook_smithy_select_create_weapon(mapping design)
{
    string  atype  = design["type"] ,   consr  = design["construction"],
            metal  = design["metal"],   color  = design["color"],
            hilts  = design["hilt"],    ornam  = design["ornament"];
    mixed   config = query_smithy_config("weapon", consr),
            metals = query_smithy_config("metal" , metal);
    object  item;

    setuid(); seteuid(getuid());
    item = clone_object(WEAPON_PATH);

    item->set_wt(config[0]);
    item->set_hit(config[1]);
    item->set_pen(ftoi(metals[0] * itof(config[2])));
    item->set_dt(config[3]);
    item->set_hands(config[4]);
    item->set_likely_dull(ftoi(metals[1] * 10.0));

    item->add_prop(OBJ_I_WEIGHT, ftoi(metals[2] * itof(
          F_WEIGHT_DEFAULT_WEAPON(item->query_pen(), item->query_wt()))));
    item->add_prop(OBJ_I_VOLUME, config[5]);
    item->add_prop(OBJ_I_VALUE , ftoi(metals[3] * itof(
          F_VALUE_WEAPON(item->query_hit(), item->query_pen()))));

    item->set_name(({consr, atype}));
    item->set_adj(({ ornam ? ornam : color, ornam ? color : metal }));
    item->set_short(implode(item->query_adjs()[0..1], " ") + " " + 
             item->query_name());

    item->set_long(CAP(LANG_ADDART(item->query_short())) + ".\n");

    return item;
}

/*
 * Function name : hook_smithy_select_notify_create
 * Description   : called when player finishes selecting, this hook is
 *                 self calling, which is made to allow item creating
 *                 emotions; inspite the theory item is not completed
 *                 at the end of smithy creating emotions, but before;
 *                 so this hook accepts already made armour/weapon
 * Arguments     : object  - the object of player who ordered
 *                 object  - the already comfigured armour/weapon
 *                 mapping - the player design (helps in messaging)
 *                 int     - the counter, first time its 0
 * Returns       : void    - nothing is returned
 */

void
hook_smithy_select_notify_create(object client, object item, 
    mapping design, int counter)
{
    string metal = design["metal"], 
           name  = design["construction"];
    
    switch (counter)
    {
      case 0: command("say Excellent! I will start crafting it at once.");
              command("emote takes a large piece of " + metal + " from a"+
                      " rack.");
              break;
      case 1: command("emote puts a piece of " + metal + " into the hot" +
                      " forge, using a large pair of pliers to turn the" +
                      " glowing coals around it.");
              break;
      case 2: command("emote removes glowing piece of " + metal + " from"+
                      " the forge with a large pair of pliers.");
              break;
      case 3: command("emote hammers on a glowing piece of " + metal     +
                       " creating a somewhat coarse shape of " +name+".");
              break;
      case 4: command("emote dips a still glowing piece of " + metal     +
                      " in a bucket of water.\nA cloud of steam rises as"+
                      " the hot metal cools down.");
              break;
      case 5: command("emote does some finishing work and engraving on"  +
                      " the " + metal + " " + name + ".");
              break;
      case 6: command("emote finishes creating "+LANG_THESHORT(item)+".");
              command("emote puts "+LANG_THESHORT(item)+" in the rack.");
              break;
    }

    if (counter < 6)
    {
       /* we call this hook again with a greater counter */
       set_alarm(4.0, 0.0,  &hook_smithy_select_notify_create(client,
          item, design, ++counter));
       return;
    }

    if (ENV(client) == ENV(TO))
    {
       command("say " + CAP(appeal(client)) + ", its good you are here!");
       command("say Your " + item->short() + " is now finished.");
       command("say You can 'pay for "+item->query_name()+"' to get it.");
    }
    else
    {
       tell_object(client, "A long-haired sweaty boy arrives.\n");
       tell_object(client, "The long-haired sweaty boy says to you:" + 
           " Your " + item->query_short() + " is now finished.\n");
       tell_object(client, "The long-haired sweaty boy runs away.\n");
    }

    /* the following function must be called at the end of the process */
    TO->finish_smithy_select(client, item); 
}

/*
 * Function name : hook_smithy_obtain_faulty_syntax
 * Description   : called when player tries to obtain a wrong item
 * Arguments     : string  - argument writen by the player
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_obtain_faulty_syntax(string letter)
{
    notify_fail(CAP(query_verb()) + " for what?\n");
    return 0;
}

/*
 * Function name : hook_smithy_obtain_cannot_afford
 * Description   : called when player cannot afford the order
 * Arguments     : object* - items player tried to obtain
 *                 int     - total price of the items
 * Returns       : int     - 0 for notify_fail or 1 for anything else
 */

int
hook_smithy_obtain_cannot_afford(object *item, int cost)
{
    command("say So you want " + COMPOSITE_DEAD(item) + ", " + appeal(TP)+
            "?");
    command("smile .");
    command("say Then you better bring money first!");
    command("say No money - no deal!");
    return 1;
}

/*
 * Function name : hook_smithy_obtain_notify_obtain
 * Description   : called if player succesfully obtained items, note that
 *                 this hook must actually deliver the items to the player
 * Arguments     : object* - items player obtained
 *                 int*    - array of coins payed by the player
 *                 int*    - array of coins player got back
 * Returns       : void    - nothing is returned
 */

void
hook_smithy_obtain_notify_obtain(object *item, int *charge, int* change)
{
    int     n = sizeof(item);
    
    TP->catch_msg("You pay " + QTNAME(TO) + " " + text(charge) + ".\n");
    if (strlen(text(change))) write("You get "+text(change)+" back.\n");

    item->move(TO, 1);

    while (--n >= 0)
    {
       command("give " + OB_NAME(item[n]) + " to " + OB_NAME(TP));

       if (ENV(item[n]) == TO)
       {
          command("say You don't seem to be able to carry the "+
                  item[n]->short()+".");
          command("drop " + OB_NAME(item[n]));
          while (--n >= 0) command("drop " + OB_NAME(item[n]));
       }
    }
}

/*
 * === activating functions ==============================================
 * =============================================================== *** ===
 */

/*
 * Function name : action_smithy_repair
 * Description   : handles attempts to repair weapon or armour
 * Arguments     : string  - argument written by the player
 * Returns       : int     - 1 for success or 0 for failure
 */

int
action_smithy_repair(string text) 
{
    mixed   item;
    int     cost, *coin, repair_left, *charge, *change;

    if (!text || !sizeof(item = (FIND_STR_IN_OBJECT(text, TP))))
       return hook_smithy_repair_faulty_syntax(text);
    
    item = item[0];

    say(QCTNAME(TP) + " asks " + QTNAME(TO) + " to repair " + 
        TP->query_possessive() + " " + item->query_short() + ".\n");
    TP->catch_msg("You ask " + QTNAME(TO) + " to repair your " +
        item->query_short() + ".\n");

    if (!CAN_SEE_IN_ROOM(TO))       return hook_smithy_answer_dark_room();
    if (!CAN_SEE(TO, TP))           return hook_smithy_answer_invisible();

    if (query_smithy_design(TP)) remove_smithy_design(TP);

    if (query_smithy_design() || query_smithy_crafts())    
       return hook_smithy_select_notify_busy();

    if (!item->check_weapon() && !item->check_armour())
       return hook_smithy_repair_faulty_object(item);
    
    if (item->check_weapon())
       repair_left = item->query_dull() - item->query_repair_dull();
    else
       repair_left = item->query_condition() - item->query_repair();
    
    if (!repair_left) 
       return hook_smithy_repair_cannot_repair(item);
    
    cost = REPAIR_COST(item);

    if (sizeof(coin = pay(cost, TP, 0, 0, 0, 0, 1)) == 1)
       return hook_smithy_repair_cannot_afford(item, cost);

    if (item->check_weapon())
       item->set_repair_dull(item->query_dull());
    else
       item->set_repair(item->query_condition());

    charge = coin[0..(SIZEOF_MONEY_TYPES - 1)];
    change = coin[SIZEOF_MONEY_TYPES..(2*SIZEOF_MONEY_TYPES - 1)];
    
    hook_smithy_repair_notify_repair(item, charge, change);

    return 1;
}

/*
 * Function name : action_smithy_polish
 * Description   : handles attempts to polish weapon
 * Arguments     : string  - argument written by the player
 * Returns       : int     - 1 for success or 0 for failure
 */

int
action_smithy_polish(string text) 
{
    mixed   item;
    int     cost, *coin, *charge, *change;

    if (!text || !sizeof(item = (FIND_STR_IN_OBJECT(text, TP))))
       return hook_smithy_polish_faulty_syntax(text);

    item = item[0];

    say(QCTNAME(TP) + " asks " + QTNAME(TO) + " to polish " + 
        TP->query_possessive() + " " + item->query_short() + ".\n");
    TP->catch_msg("You ask " + QTNAME(TO) + " to polish your " +
        item->query_short() + ".\n");

    if (!CAN_SEE_IN_ROOM(TO))       return hook_smithy_answer_dark_room();
    if (!CAN_SEE(TO, TP))           return hook_smithy_answer_invisible();

    if (query_smithy_design(TP)) remove_smithy_design(TP);

    if (query_smithy_design() || query_smithy_crafts())    
       return hook_smithy_select_notify_busy();

    if (!item->check_weapon())
       return hook_smithy_polish_faulty_object(item);

    if (!item->query_corroded()) 
       return hook_smithy_polish_cannot_polish(item);

    cost = POLISH_COST(item);

    if (sizeof(coin = pay(cost, TP, 0, 0, 0, 0, 1)) == 1)
       return hook_smithy_polish_cannot_afford(item, cost);
   
    item->set_repair_corr(item->query_corroded());

    charge = coin[0..(SIZEOF_MONEY_TYPES - 1)];
    change = coin[SIZEOF_MONEY_TYPES..(2*SIZEOF_MONEY_TYPES - 1)];

    hook_smithy_polish_notify_polish(item, charge, change);

    return 1;
}

/*
 * Function name : action_smithy_mend
 * Description   : handles attempts to mend weapons and armours
 * Arguments     : string  - argument written by the player
 * Returns       : int     - 1 for success or 0 for failure
 */

int
action_smithy_mend(string text)
{
    mixed   item;
    int     cost, *coin, *charge, *change;

    if (!text || !sizeof(item = (FIND_STR_IN_OBJECT(text, TP))))
       return hook_smithy_mend_faulty_syntax(text);

    item = item[0];

    say(QCTNAME(TP) + " asks " + QTNAME(TO) + " to mend " + 
        TP->query_possessive() + " " + item->query_short() + ".\n");
    TP->catch_msg("You ask " + QTNAME(TO) + " to mend your " +
        item->query_short() + ".\n");

    if (!CAN_SEE_IN_ROOM(TO))       return hook_smithy_answer_dark_room();
    if (!CAN_SEE(TO, TP))           return hook_smithy_answer_invisible();

    if (query_smithy_design(TP)) remove_smithy_design(TP);

    if (query_smithy_design() || query_smithy_crafts())    
       return hook_smithy_select_notify_busy();

    if (!item->check_weapon() && !item->check_armour())
       return hook_smithy_mend_faulty_object(item);

    if (!item->query_prop(OBJ_I_BROKEN)) 
       return hook_smithy_mend_cannot_mend(item);

    if (item->query_prop(OBJ_I_IS_MAGIC_WEAPON) ||
        item->query_prop(OBJ_I_IS_MAGIC_ARMOUR)  )
       return hook_smithy_mend_cursed_object(item);

    cost = MEND_COST(item);

    if (sizeof(coin = pay(cost, TP, 0, 0, 0, 0, 1)) == 1)
       return hook_smithy_mend_cannot_afford(item, cost);
   
    item->remove_prop(OBJ_I_BROKEN);

    charge = coin[0..(SIZEOF_MONEY_TYPES - 1)];
    change = coin[SIZEOF_MONEY_TYPES..(2*SIZEOF_MONEY_TYPES - 1)];

    hook_smithy_mend_notify_mend(item, charge, change);

    return 1;
}

/*
 * Function name : action_smithy_browse
 * Description   : handles browsing of the selection options and armory
 * Arguments     : string  - argument written by the player
 * Returns       : int     - 1 for success or 0 for failure
 */

int
action_smithy_browse(string text)
{
    string *armour = query_smithy_armour(), 
           *weapon = query_smithy_weapon(), 
           *armory = ({"orders", "order"}), stxt;
    
    if (!text) return hook_smithy_browse_faulty_syntax(text);

    say(QCTNAME(TP)+" inquires "+QTNAME(TO)+" for "+LANG_ADDART(text)+
        ".\n");
    TP->catch_msg("You inquire "+QTNAME(TO)+" for "+LANG_ADDART(text)+
        ".\n");

    if (!CAN_SEE_IN_ROOM(TO))       return hook_smithy_answer_dark_room();
    if (!CAN_SEE(TO, TP))           return hook_smithy_answer_invisible();

    if (query_smithy_design(TP)) remove_smithy_design(TP);

    if (query_smithy_design() || query_smithy_crafts())    
       return hook_smithy_select_notify_busy();

    if (sizeof(armour)) armour += ({"armours", "armour"});
    if (sizeof(weapon)) weapon += ({"weapons", "weapon"});
    
    stxt = LANG_SWORD(text);
    
    if (member_array(text, armour) >= 0)
       return hook_smithy_browse_armour_browse(text);
    
    if (member_array(stxt, armour) >= 0)
       return hook_smithy_browse_armour_browse(stxt);

    if (member_array(text, weapon) >= 0)
       return hook_smithy_browse_weapon_browse(text);
    
    if (member_array(stxt, weapon) >= 0)
       return hook_smithy_browse_weapon_browse(stxt);

    if (member_array(text, armory) >= 0)
       return hook_smithy_browse_armory_browse(text);

    return hook_smithy_browse_faulty_syntax(text);
}

/*
 * Function name : finish_smithy_select
 * Description   : makes the final arrangements for ordered object
 * Arguments     : object  - the client
 *                 object  - the object
 * Returns       : void    - nothing is returned
 */

void
finish_smithy_select(object client, object item)
{
    set_smithy_crafts(0);

    if (!objectp(client))
    {
       item->remove_object();
       return;
    }

    add_smithy_armory(client, item);
}

/*
 * Function name : prompt_smithy_select
 * Description   : loops the input of player
 * Arguments     : int     - module armour/weapon
 *                 string  - armour/weapon type
 *                 int     - order counter
 * Returns       : void    - nothing is returned
 */

void
prompt_smithy_select(int module, string type, int spot)
{
    object  item;
    string  aspect, *option = ({});
    mapping design = ([]);

    if (!sizeof(query_smithy_design(TP))) return;
    
    switch (module)
    {
        case MODULE_ARMOUR: design = smithy_armour[type]; break;
        case MODULE_WEAPON: design = smithy_weapon[type]; break;
    }
    
    if (spot >= sizeof(m_indices(design)))
    {
       if (!objectp(TP) || (ENV(TP) != ENV(TO)))
          return remove_smithy_design(TP);

       design = ([]) + smithy_design[TP->query_real_name()];

       setuid(); seteuid(getuid());

       if (module == MODULE_ARMOUR) 
          item = hook_smithy_select_create_armour(design);
       else if (module == MODULE_WEAPON) 
          item = hook_smithy_select_create_weapon(design);

       remove_smithy_design(TP);

       set_smithy_crafts(1);

       return hook_smithy_select_notify_create(TP, item, design, 0);
    }

    aspect = sort_array(m_indices(design))[spot];
    option = design[aspect];

    hook_smithy_select_notify_prompt(aspect, option);
    write(":");
    
    input_to(&TO->record_smithy_select(, module, type, spot));
}

/*
 * Function name : record_smithy_select
 * Description   : prompts the player to selection of wep/arm attributes
 * Arguments     : string  - argument writen by the player
 *                 int     - module armour/weapon            
 *                 string  - armour/weapon type                       
 *                 int     - order counter
 * Returns       : void    - nothing is returned
 */

void
record_smithy_select(string letter, int module, string type, int spot)
{
    string  aspect, *option = ({});
    mapping design = ([]);

    if ((ENV(TP) != ENV(TO)) || wildmatch("cancel*", letter))
    {
       /* selection was canceled from some reason */
       if (ENV(TP) == ENV(TO)) hook_smithy_select_notify_cancel();
       return remove_smithy_design(TP);
    }

    switch (module)
    {
        case MODULE_ARMOUR: design = smithy_armour[type]; break;
        case MODULE_WEAPON: design = smithy_weapon[type]; break;
    }

    if (!strlen(letter))
    {
       write(":");
       input_to(&record_smithy_select(, module, type, spot));
       return;
    }

    TP->catch_msg("You say to " + QTNAME(TO) + ": " + letter + ".\n");
    say(QCTNAME(TP)+" says to " + QTNAME(TO) + ": " + letter + ".\n");

    aspect = sort_array(m_indices(design))[spot];
    option = design[aspect];
    
    if (member_array(letter, option) < 0)
    {
       hook_smithy_select_faulty_option(letter, aspect, option);
       write(":");
       input_to(&record_smithy_select(, module, type, spot));
       return;
    }
    
    add_smithy_design(TP, aspect, letter); 
    prompt_smithy_select(module, type, ++spot);
}

/*
 * Function name : action_smithy_select
 * Description   : handles weapon/armour ordering
 * Arguments     : string  - argument written by the player
 * Returns       : int     - 1 for success or 0 for failure
 */

public int
action_smithy_select(string text)
{
    int     module;
    string *armour=query_smithy_armour(), *weapon=query_smithy_weapon(); 
    
    if (!text)         return hook_smithy_select_faulty_syntax(text);
    else if (member_array(text, armour) >= 0) module = MODULE_ARMOUR;
    else if (member_array(text, weapon) >= 0) module = MODULE_WEAPON;
    else               return hook_smithy_select_faulty_syntax(text);
    
    say(QCTNAME(TP)+" asks "+QTNAME(TO)+" for "+LANG_ADDART(text)+ ".\n");
    TP->catch_msg("You ask "+QTNAME(TO)+" for "+LANG_ADDART(text)+ ".\n");

    if (!CAN_SEE_IN_ROOM(TO))       return hook_smithy_answer_dark_room();
    if (!CAN_SEE(TO, TP))           return hook_smithy_answer_invisible();

    /* this is a security feature, for example player linkdied in the   */
    /* middle of selection process and smithy_design still contains his */
    /* record, in such a case we remove the record                      */

    if (query_smithy_design(TP)) remove_smithy_design(TP);
    
    /* checking if someone already ordering, query_smithy_design() will */
    /* clean up the junk records and return true only if someone really */
    /* orders something at the moment                                   */

    if (query_smithy_design() || query_smithy_crafts())    
       return hook_smithy_select_notify_busy();

    add_smithy_design(TP, "type", text);
    
    hook_smithy_select_notify_header(text);
    
    prompt_smithy_select(module, text, 0);
    return 1;
}

/*
 * Function name : action_smithy_obtain
 * Description   : handles attempts to pay for ready armour/weapon
 * Arguments     : string  - argument written by the player
 * Returns       : int     - 1 for success or 0 for failure
 */

public int
action_smithy_obtain(string text)
{
    int     cost = 0, *coin, n, *charge, *change;
    string  what;
    object *item;
    
    if (!text || !parse_command(text, ({}), "'for' [the] %s", what) ||
        !(n=sizeof(item=FIND_STR_IN_ARR(what,query_smithy_armory(TP)))))
       return hook_smithy_obtain_faulty_syntax(text);

    say(QCTNAME(TP) + " asks " + QTNAME(TO) + " to give " + 
        TP->query_possessive() + " " + COMPOSITE_DEAD(item) + ".\n");
    TP->catch_msg("You ask " + QTNAME(TO) + " to give you " +
        COMPOSITE_DEAD(item) + ".\n");

    if (!CAN_SEE_IN_ROOM(TO))       return hook_smithy_answer_dark_room();
    if (!CAN_SEE(TO, TP))           return hook_smithy_answer_invisible();

    if (query_smithy_design(TP)) remove_smithy_design(TP);

    if (query_smithy_design() || query_smithy_crafts())    
       return hook_smithy_select_notify_busy();

    while (--n >= 0)  cost += OBTAIN_COST(item[n]);

    if (sizeof(coin = pay(cost, TP, 0, 0, 0, 0, 1)) == 1)
       return hook_smithy_obtain_cannot_afford(item, cost);

    charge = coin[0..(SIZEOF_MONEY_TYPES - 1)];
    change = coin[SIZEOF_MONEY_TYPES..(2*SIZEOF_MONEY_TYPES - 1)];

    item->remove_prop(SMITHY_S_CLIENT);
    
    hook_smithy_obtain_notify_obtain(item, charge, change);

    return 1;
}

/*
 * === initiating functions ==============================================
 * =============================================================== *** ===
 */

/*
 * Function name : init_smithy
 * Description   : adds smithy actions to the environment
 * Arguments     : void    - no arguments
 * Returns       : void    - nothing is returned
 */

void
init_smithy()
{
    add_action(action_smithy_repair, "repair");
    add_action(action_smithy_polish, "polish");

    /* the following commands available only if smithy has stock */
    if (sizeof(query_smithy_weapon() + query_smithy_armour()))
    {
       add_action(action_smithy_mend,     "mend");
       add_action(action_smithy_browse, "browse");
       add_action(action_smithy_select,  "order");
       add_action(action_smithy_obtain,    "pay");
    }
}

