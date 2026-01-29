/* === tavern.c ==========================================================
 * =============================================== Araven 2001 Genesis ===
 *
 * The module is a support for an establishment licensed to sell alcoholic
 * beverages to be consumed on the premises.  Module supports an automatic
 * menu, drinks, food and wares addition and assignation of a waiter. Next
 * is an example of how to configure the tavern.
 *
 * inherit "/std/room";
 * inherit TAVERN_LIB;
 *
 * void
 * create_room()
 * {
 *     set_short("The Lost Dwarf Pub");
 *     set_long("You are in the Lost Dwarf Pub.\n");
 *
 *     set_tavern_name("The Lost Dwarf Pub");
 *
 *     add_tavern_drink("wine", "red", "red wine", "red wines", "This" +
 *        " red wine is from tavern module.\n", 1200, 200, 50);
 *
 *     add_tavern_drink("/d/Domain/area/obj/my_special_drink");
 *
 *     add_tavern_food("stew", "warm", "warm stew", "warm stews", "This" +
 *        " warm stew is from tavern module.\n", 1000, 60);
 *
 *     add_tavern_food("/d/Domain/area/obj/my_special_food");
 *
 *     add_tavern_wares(({
 *                        "/d/Domain/area/obj/bottle",
 *                        "/d/Domain/area/obj/tavern_key",
 *                      });
 *
 *     set_tavern_waiter("/d/Domain/area/npc/waiter");
 *
 *     clone_object("/d/Domain/area/npc/waiter")->move(this_object());
 * }
 *
 * void
 * init()
 * {
 *     ::init();
 *     init_tavern();
 * }
 *
 * === definition functions ==============================================
 * =============================================================== *** ===
 *
 * init_tavern()             function initiates tavern related commands  ,
 *                           should be called from init()
 *
 * set_tavern_name(s)        function sets tavern name, which is then used
 *                           as a header to automatic menu
 *
 * add_tavern_drink(mx,mx,s,s,s,i,i,i)        function adds a drink to the
 *                           tavern, while the arguments are :  name(s) or
 *                           filename (if filename given rest of arguments
 *                           will be ignored), adj(s), short desc , plural
 *                           short desc, long desc, cost , soft amount and
 *                           alco amount
 *
 * add_tavern_food(mx,mx,s,s,s,i,i)           function adds a  food to the
 *                           tavern, while the arguments are :  name(s) or
 *                           filename (if filename given rest of arguments
 *                           will be ignored), adj(s), short desc , plural
 *                           short desc, long desc, cost and food amount
 *
 * add_tavern_wares(mx)      function adds wares to the tavern menu, which
 *                           can come in a form of single filename or in a
 *                           form of array of filenames
 *
 * set_tavern_waiter(s)      function sets the filename of tavern waiter ,
 *                           from the moment  the  waiter  is  set all the
 *                           messages would be produced by him , and if he
 *                           is not present tavern would  refuse  to  deal
 *                           with the customers , to access the waiter use
 *                           tavern_waiter()  function , which returns the
 *                           object pointer of him / her (when this module
 *                           inherited by living  tavern_waiter()  returns
 *                           this_object() even if waiter wasnt set
 *
 * =======================================================================
 * =============================================================== *** ===
 */

#pragma strict_types

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
inherit "/lib/trade";

/*
 * === global variables ==================================================
 * =============================================================== *** ===
 */

#define MAXIMUM_BUYS (20) /* maximum size allowed to buy                */

#define DRINK_NAME (0) /* (string*) names location in drink mapping     */
#define DRINK_ADJS (1) /* (string*) adjs location in drink mapping      */
#define DRINK_SING (2) /* (string ) short location in drink mapping     */
#define DRINK_PLUR (3) /* (string ) pshort location in drink mapping    */
#define DRINK_LONG (4) /* (string ) long desc location in drink mapping */
#define DRINK_COST (5) /* (int    ) cost location in drink mapping      */
#define DRINK_SOFT (6) /* (int    ) soft location in drink mapping      */
#define DRINK_ALCO (7) /* (int    ) alcohol location in drink mapping   */
#define DRINK_FILE (8) /* (string ) file location in drink mapping      */
#define DRINK_SIZE (9) /* size of array in drink's mapping              */

#define FOOD_NAME  (0) /* (string*) names location in food mapping      */
#define FOOD_ADJS  (1) /* (string*) adjs location in food mapping       */
#define FOOD_SING  (2) /* (string ) short location in food mapping      */
#define FOOD_PLUR  (3) /* (string ) pshort location in food mapping     */
#define FOOD_LONG  (4) /* (string ) long desc location in food mapping  */
#define FOOD_COST  (5) /* (int    ) cost location in food mapping       */
#define FOOD_FOOD  (6) /* (int    ) soft location in food mapping       */
#define FOOD_FILE  (7) /* (string ) file location in food mapping       */
#define FOOD_SIZE  (8) /* size of array in food's mapping               */

static  mapping tavern_drink,  /* drinks sold here                      */
                tavern_food;   /* foods sold here                       */
static  string *tavern_wares,  /* wares sold here (key, bottle)         */ 
                tavern_name,   /* the name of the tavern                */
                tavern_waiter; /* the man who sells the drinks          */
static  object  waiter_object; /* holds the object pointer to waiter    */

/*
 * === supporting functions ==============================================
 * =============================================================== *** ===
 */

/*
 * Function name : flatten_array
 * Description   : acepts a multi-dimensional array and returns the array
 *                 flattened, for example if you input {1, {2,3}, {4,5},
 *                 {{6,7}, {8,9}}} you will get {1,2,3,4,5,6,7,8,9} back
 * Arguments     : mixed   - unflattened array
 * Returns       : mixed   - flattened array
 */
private mixed
flatten_array(mixed list)
{
    mixed   rval = ({});
    int     size, n = -1;
    
    if (!pointerp(list))
    {
        return list;
    }
  
    size = sizeof(list);
    
    while (++n < size)
    {
        rval += (pointerp(list[n]) ? flatten_array(list[n]) : ({list[n]}));
    }

    return rval;
}

/*
 * Function name : make_pattern
 * Description   : creates a pattern from names and adjectives
 * Arguments     : string* - the names list
 *                 string* - the adjectives list
 * Returns       : string  - the parse pattern
 */
private string
make_pattern(string *name, string *adjs)
{
    string *list = ({}), word, patt = "";
    int     size, n = -1;
    
    if (sizeof(adjs))
    {
        adjs  = ({}) + flatten_array(map(adjs, &explode(, " ")));
        patt += ("[" + implode(adjs, "] [") + "] ");
    }
    
    name = ({}) + flatten_array(map(name, &explode(, " ")));

    if (!(size = sizeof(name)))
    {
        return 0;
    }

    while (++n < size)
    {
        if ((word = LANG_SWORD(name[n])) == name[n])
        {
            list += ({ name[n], LANG_PWORD(name[n]) });
        }
        else
        {
            list += ({ name[n], word });
        }
    }
    
    patt += ("'" + implode(list, "' / '") + "'");
    
    return (strlen(patt) ? ("[the] " + patt) : 0);
}

/*
 * Function name : find_pattern
 * Description   : parses a given name thru patterns to find a fitting one
 * Arguments     : string  - the drink / food name
 *                 string* - the patterns list
 * Returns       : string  - fitting pattern or 0
 */
private string
find_pattern(string name, string *patt)
{
    int     size = sizeof(patt);

    while (--size >= 0)
    {
        if (parse_command(name, ({}), patt[size]))
        {
            return patt[size];
        }
    }

    return 0;
}

/*
 * Function name : clone_tavern_drink
 * Description   : configures the drink objects and returns them
 * Arguments     : string  - the drink name or parse pattern
 *                 int     - the amount to clone
 * Returns       : object* - the configured drink objects
 */
public nomask varargs object*
clone_tavern_drink(string name, int size = 1)
{
    object  item;
    mixed   data;

    if (!name || !(name = this_object()->query_tavern_drink(name)))
    {
        return ({ });
    }
    
    seteuid(getuid(this_object()));
    data = tavern_drink[name];

    if (stringp(data[DRINK_FILE]))
    {
        item = clone_object(data[DRINK_FILE]);
    }
    else
    {
        item = clone_object("/std/drink");
        item->set_name(data[DRINK_NAME]);
        item->set_adj(data[DRINK_ADJS]);
        item->set_short(data[DRINK_SING]);
        item->set_pshort(data[DRINK_PLUR]);
        item->set_long(data[DRINK_LONG]);
        item->set_soft_amount(data[DRINK_SOFT]);
        item->set_alco_amount(data[DRINK_ALCO]);

        item->add_prop(HEAP_I_UNIT_VOLUME, data[DRINK_SOFT] +
            data[DRINK_ALCO]);
        item->add_prop(HEAP_I_UNIT_WEIGHT, data[DRINK_SOFT] +
            data[DRINK_ALCO]);
        item->add_prop(HEAP_I_UNIT_VALUE , data[DRINK_COST]);
    }

    item->set_heap_size(max(1, size));
    
    return ({ item });
}

/*
 * Function name : clone_tavern_food
 * Description   : configures the food objects and returns them
 * Arguments     : string  - the food name or parse pattern
 *                 int     - the amount to clone
 * Returns       : object* - the configured food objects
 */
public nomask varargs object*
clone_tavern_food(string name, int size = 1)
{
    object  item;
    mixed   data;

    if (!name || !(name = this_object()->query_tavern_food(name)))
    {
        return ({ });
    }

    seteuid(getuid(this_object()));
    data = tavern_food[name];

    if (stringp(data[FOOD_FILE]))
    {
        item = clone_object(data[FOOD_FILE]);
    }
    else
    {
        item = clone_object("/std/food");
        item->set_name(data[FOOD_NAME]);
        item->set_adj(data[FOOD_ADJS]);
        item->set_short(data[FOOD_SING]);
        item->set_pshort(data[FOOD_PLUR]);
        item->set_long(data[FOOD_LONG]);
        item->set_amount(data[FOOD_FOOD]);

        item->add_prop(HEAP_I_UNIT_VOLUME, data[FOOD_FOOD]);
        item->add_prop(HEAP_I_UNIT_WEIGHT, data[FOOD_FOOD]);
        item->add_prop(HEAP_I_UNIT_VALUE , data[FOOD_COST]);
    }

    item->set_heap_size(max(1, size));

    return ({ item });
}

/*
 * Function name : clone_tavern_wares
 * Description   : clones the requested wares
 * Arguments     : mixed   - ware path/object
 * Returns       : object* - cloned wares
 */
public nomask varargs object*
clone_tavern_wares(mixed file, int size = 1)
{
    mixed   item;
    int     n = -1;
    
    setuid(); seteuid(getuid());

    file = objectp(file) ? MASTER_OB(file) : file;

    if (!stringp(file) || LOAD_ERR(file) || (size < 1))
    {
        return ({ });
    }

    if (file->query_prop(HEAP_I_IS))
    {
        item = clone_object(file);
        item->set_heap_size(size);
        return ({ item });
    }
    
    item = ({ });
    
    while (++n < size)
    {
        item += ({ clone_object(file) });
    }

    return item;
}

/*
 * Function name : tavern_waiter()
 * Description   : returns the object pointer to the waiter if there is
 *                 any, (when monster inherits this module this_object()
 *                 is returned)
 * Arguments     : void    - no arguments
 * Returns       : object  - the waiter object
 */
public nomask object
tavern_waiter()
{
    object *live;
    string  file;
    int     size;
    
    if (living(this_object()))
    {
        return this_object();
    }

    if (objectp(waiter_object))
    {
        if (environment(waiter_object) != this_object())
        {
            waiter_object = 0;
        }
        
        return waiter_object;
    }
    
    if (!strlen(tavern_waiter) || !this_object()->query_prop(ROOM_I_IS) ||
        LOAD_ERR(tavern_waiter))
    {
        return 0;
    }

    live = FILTER_LIVE(all_inventory(this_object()));
    size = sizeof(live);

    while (--size >= 0)
    {
        file = MASTER_OB(live[size]);

        if ((file == tavern_waiter) || ((file + ".c") == tavern_waiter))
        {
            waiter_object = live[size];
            return waiter_object;
        }
    }

    return 0;
}

/*
 * === definition functions ==============================================
 * =============================================================== *** ===
 */

/*
 * Function name : set_tavern_name
 * Description   : sets the name of the tavern (used in the menu)
 * Arguments     : string  - the name of the tavern
 * Returns       : void    - nothing is returned
 */
public nomask void
set_tavern_name(string name)
{
    tavern_name = name;
}

/*
 * Function name : query_tavern_name
 * Description   : returns the name of the tavern (used in the menu)
 * Arguments     : void    - no arguments
 * Returns       : string  - the name of the tavern
 */
public nomask string
query_tavern_name()
{
    return (stringp(tavern_name) ? tavern_name : "The Last Home Inn");
}

/*
 * Function name : add_tavern_drink
 * Description   : add a drink to the menu list
 * Arguments     : mixed   - the name/names of the drink, or filename
 *                           of a drink (if filename is set then rest
 *                           of variables ignored)
 *                 mixed   - the adjective/adjectives of the drink
 *                 string  - short description of the drink
 *                 string  - plural short description
 *                 string  - long description of the drink
 *                 int     - the cost of the drink
 *                 int     - the soft amount
 *                 int     - the alcohol amount
 * Returns       : void    - nothing is returned
 */
public nomask varargs void
add_tavern_drink(mixed name, mixed adjs, string sing, string plur,
    string desc, int cost, int soft, int alco)
{
    string  patt, file;
    object  item;
    
    if (stringp(name) && wildmatch("*/*", name))
    {
        file = name;
        item = file->get_this_object();

        if (function_exists("create_heap", item) != DRINK_OBJECT)
        {
            return;
        }

        name = item->query_name(-1);
        adjs = item->query_adjs();
        sing = item->short();
        plur = item->plural_short();
        desc = item->long();
        cost = item->query_prop(HEAP_I_UNIT_VALUE);
        soft = item->query_soft_amount();
        alco = item->query_alco_amount();
    }
    else
    {
        name = (pointerp(name) ? name : ({ name }));
        adjs = (pointerp(adjs) ? adjs : ({ adjs }));
    }

    if (!(patt = make_pattern(name, adjs)))
    {
        return;
    }
    
    if (!mappingp(tavern_drink))
    {
        tavern_drink = ([ ]);
    }
    
    tavern_drink[patt] = allocate(DRINK_SIZE);

    tavern_drink[patt][DRINK_NAME] = name;
    tavern_drink[patt][DRINK_ADJS] = adjs;
    tavern_drink[patt][DRINK_SING] = sing;
    tavern_drink[patt][DRINK_PLUR] = plur;
    tavern_drink[patt][DRINK_LONG] = desc;
    tavern_drink[patt][DRINK_COST] = max(0, cost);
    tavern_drink[patt][DRINK_SOFT] = max(0, soft);
    tavern_drink[patt][DRINK_ALCO] = max(0, alco);
    tavern_drink[patt][DRINK_FILE] = file;
}

/*
 * Function name : query_tavern_drink
 * Description   : returns data stored in drink mapping
 * Arguments     : string  - the name or parse pattern of the drink
 *                 int     - the requested aspect, like soft amount
 * Returns       : mixed   - array of drink's parse patterns if no name
 *                           is given; if name is given returns the parse
 *                           pattern of this name; if name and aspect is
 *                           given returns the reguested aspect of the
 *                           name like soft amount/names/etc
 */
public nomask varargs mixed
query_tavern_drink(string name = 0, int aspect = -1)
{ 
    if (!name)
    {
        return (mappingp(tavern_drink) ? m_indices(tavern_drink) : ({}));
    }
    
    if (!mappingp(tavern_drink))
    {
        return 0;
    }
    
    if (!pointerp(tavern_drink[name]))
    {
        name = find_pattern(name, m_indices(tavern_drink));
    }
    
    if (aspect == -1)
    {
        return name;
    }

    return (pointerp(tavern_drink[name]) ? tavern_drink[name][aspect] : 0);
}

/*
 * Function name : remove_tavern_drink
 * Description   : remove a drink from tavern
 * Arguments     : string  - the name or parse pattern of the drink
 * Returns       : int     - 1 if removed or 0 otherwise
 */
public nomask int
remove_tavern_drink(string name)
{
    if (!(name = query_tavern_drink(name)))
    {
        return 0;
    }
    
    tavern_drink = m_delete(tavern_drink, name);

    return 1;
}

/*
 * Function name : add_tavern_food
 * Description   : add a food to the menu list
 * Arguments     : mixed    - the name/names of the food, or filename (if
 *                            filename is set, rest of variables are
 *                            ignored)
 *                 mixed    - the adjective/adjectives of the food
 *                 string   - short description of the food
 *                 string   - the plural short description
 *                 string   - long description of the food
 *                 int      - the cost of the food
 *                 int      - the amount of the food
 * Returns       : void     - nothing is returned
 */
public nomask varargs void
add_tavern_food(mixed name, mixed adjs, string sing, string plur,
    string desc, int cost, int food)
{
    string  patt, file;
    object  item;
    
    if (stringp(name) && wildmatch("*/*", name))
    {
        file = name;
        item = file->get_this_object();

        if (function_exists("create_heap", item) != FOOD_OBJECT)
        {
            return;
        }

        name = item->query_name(-1);
        adjs = item->query_adjs();
        sing = item->short();
        plur = item->plural_short();
        desc = item->long();
        cost = item->query_prop(HEAP_I_UNIT_VALUE);
        food = item->query_amount();
    }
    else
    {
        name = (pointerp(name) ? name : ({ name }));
        adjs = (pointerp(adjs) ? adjs : ({ adjs }));
    }

    if (!(patt = make_pattern(name, adjs)))
    {
        return;
    }
    
    if (!mappingp(tavern_food))
    {
        tavern_food = ([ ]);
    }
    
    tavern_food[patt] = allocate(FOOD_SIZE);

    tavern_food[patt][FOOD_NAME] = name;
    tavern_food[patt][FOOD_ADJS] = adjs;
    tavern_food[patt][FOOD_SING] = sing;
    tavern_food[patt][FOOD_PLUR] = plur;
    tavern_food[patt][FOOD_LONG] = desc;
    tavern_food[patt][FOOD_COST] = max(0, cost);
    tavern_food[patt][FOOD_FOOD] = max(0, food);
    tavern_food[patt][FOOD_FILE] = file;
}

/*
 * Function name : query_tavern_food
 * Description   : returns data stored in food mapping
 * Arguments     : string  - the name or parse pattern of the food
 *                 int     - the requested aspect, like amount
 * Returns       : mixed   - array of food's parse patterns if no name
 *                           is given; if name is given returns the parse
 *                           pattern of this name; if name and aspect is
 *                           given returns the reguested aspect of the
 *                           name like amount/names/etc
 */
public nomask varargs mixed
query_tavern_food(string name = 0, int aspect = -1)
{ 
    if (!name)
    {
        return (mappingp(tavern_food) ? m_indices(tavern_food) : ({}));
    }
    
    if (!mappingp(tavern_food))
    {
        return 0;
    }
    
    if (!pointerp(tavern_food[name]))
    {
        name = find_pattern(name, m_indices(tavern_food));
    }
    
    if (aspect == -1)
    {
        return name;
    }

    return (pointerp(tavern_food[name]) ? tavern_food[name][aspect] : 0);
}

/*
 * Function name : remove_tavern_food
 * Description   : remove a food from tavern
 * Arguments     : string  - the name or parse pattern of the food
 * Returns       : int     - 1 if removed or 0 otherwise
 */
public nomask int
remove_tavern_food(string name)
{
    if (!(name = query_tavern_food(name)))
    {
        return 0;
    }
    
    tavern_food = m_delete(tavern_food, name);

    return 1;
}

/*
 * Function name : add_tavern_wares
 * Description   : adds differnt wares to the tavern, like bottle/key
 * Arguments     : mixed   - wares path/pathes
 * Returns       : void    - nothing is returned
 */
public nomask void
add_tavern_wares(mixed file)
{
    if (!sizeof(file = filter(pointerp(file) ? file : ({file}), stringp)))
    {
        return;
    }

    if (!pointerp(tavern_wares))
    {
        tavern_wares = ({});
    }

    tavern_wares -= file;
    tavern_wares += file;
}

/*
 * Function name : query_tavern_wares
 * Description   : returns pathes of wares in stock
 * Arguments     : none    - no arguments
 * Returns       : string* - wares pathes list
 */
public nomask string*
query_tavern_wares()
{
    return (pointerp(tavern_wares) ? (({}) + tavern_wares) : ({}));
}

/*
 * Function name : set_tavern_waiter
 * Description   : sets the waiter file of this tavern, for case you
 *                 inherit this module in an npc there is no taste in
 *                 setting the waiter, as he will automatically become
 *                 this_object()
 * Arguments     : string  - full path to waiter
 * Returns       : void    - nothing is returned
 */
public nomask void
set_tavern_waiter(string file)
{
    tavern_waiter = file;
}

/*
 * Function name : query_tavern_waiter
 * Description   : returns the tavern waiter filename
 * Arguments     : void    - no arguments
 * Returns       : string  - the waiter filename
 */
public nomask string
query_tavern_waiter()
{
    return tavern_waiter;
}

/*
 * === hooked functions ==================================================
 * =============================================================== *** ===
 */

/*
 * Function name : appeal
 * Description   : the appeal of waiter to player
 * Arguments     : object  - appeal player
 * Returns       : string  - appeal string
 */
public varargs string
appeal(object player = this_player())
{
    mixed   text;

    /* maybe appeal defined in the waiter itself      */
    if ((tavern_waiter() != this_object()) &&
        stringp(text = tavern_waiter()->appeal(player)))
    {
        return text;
    }
    
    switch (player->query_gender())
    {
        case  0: return "milord";
        case  1: return "milady";
        default: return "weird one";
    }
}

/*
 * Function name : hook_tavern_answer_dark_room
 * Description   : refuse to deal when the room is dark
 * Arguments     : void    - no arguments
 * Returns       : int     - 0 for nofity_fail or 1 for the rest
 */
public int
hook_tavern_answer_dark_room()
{
    tavern_waiter()->command("say I cant see you, light a torch first," +
        " please.");
    return 1;
}

/*
 * Function name : hook_tavern_answer_invisible
 * Description   : refuse to deal with player who is invisible for waiter
 * Arguments     : void    - no arguments
 * Returns       : int     - 0 for nofity_fail or 1 for the rest
 */
public int
hook_tavern_answer_invisible()
{
    tavern_waiter()->command("say Show yourself first, then we do" +
        " business!");
    tavern_waiter()->command("peer suspiciously");
    return 1;
}

/*
 * Function name : hook_tavern_buy_faulty_syntax
 * Description   : notify the player of invalid syntax
 * Arguments     : string  - arguments to the command
 * Returns       : int     - 0 for notify_fail and 1 for the rest
 */
public int
hook_tavern_buy_faulty_syntax(string text)
{
    if (!strlen(text))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (tavern_waiter())
    {
        tavern_waiter()->command("say I have no " + text + " for sale, " +
            appeal() + ".");
        return 1;
    }
    else
    {
        notify_fail("There is no " + text + " in stock.\n");
        return 0;
    }
}

/*
 * Function name : hook_tavern_buy_waiter_absent
 * Description   : called when there should be a waiter and he isnt here
 * Arguments     : void    - no arguments
 * Returns       : int     - 0 for notify_fail and 1 for the rest
 */
public int
hook_tavern_buy_waiter_absent()
{
    notify_fail("There is noone here to serve you.\n");
    return 0;
}

/*
 * Function name : hook_tavern_buy_notify_header
 * Description   : gives a header message when player tries to buy
 * Arguments     : string  - argument writen by the player
 * Returns       : void    - nothing is returned
 */
public void
hook_tavern_buy_notify_header(string text)
{
    if (tavern_waiter())
    {
        write("You order " + text + " from " +
            tavern_waiter()->query_the_name(this_player()) + ".\n");

        say(QCTNAME(this_player()) + " orders " + text + " from " +
            QTNAME(tavern_waiter()) + ".\n");
    }
}

/*
 * Function name : hook_tavern_buy_exceed_maximum
 * Description   : tells the player that he ordered too many items
 * Arguments     : int     - the amount the player ordered
 * Returns       : int     - 0 for notify_fail and 1 for the rest
 */
public int
hook_tavern_buy_exceed_maximum(int size)
{
    if (tavern_waiter())
    {
        tavern_waiter()->command("say You cannot buy more than " +
            MAXIMUM_BUYS + " meals or drinks at a time, " + appeal() +
            ".");

        return 1;
    }
    else
    {
        notify_fail("You cannot buy more than " + MAXIMUM_BUYS +
            " meals or drinks at a time.\n");
        return 0;
    }
}

/*
 * Function name : hook_tavern_buy_cannot_afford
 * Description   : notify that player cant pay the price
 * Arguments     : object* - the items player tried to buy
 *                 int     - the price he should had payed
 * Returns       : void    - nothing is returned
 */
public void
hook_tavern_buy_cannot_afford(object *item, int cost)
{
    if (tavern_waiter())
    {
        tavern_waiter()->command("grumble");
        tavern_waiter()->command("say You haven't got enough money to" +
            " pay the price, " + appeal() + "!");
    }
    else
    {
        write("You haven't got enough money to pay the price.\n");
    }
}

/*
 * Function name : hook_tavern_buy_cannot_carry
 * Description   : notify that player cannot carry the objects he bought
 * Arguments     : object* - the objects player couldn't carry
 * Returns       : void    - nothing is returned
 */
public void
hook_tavern_buy_cannot_carry(object *item)
{
    int     n = sizeof(item), size;
    
    while (--n >= 0)
    {
        size += (item[n]->query_prop(HEAP_I_IS) ? item[n]->num_heap() : 1);
    }
    
    if (tavern_waiter())
    {
        tavern_waiter()->command("say "+capitalize(COMPOSITE_DEAD(item)) +
            " " + (size > 1 ? "are" : "is") + " too heavy for you, " +
            appeal() + ".");
        tavern_waiter()->command("say I will just put " +
            (size > 1 ? "them" : "it") + " here.");
        tavern_waiter()->command("emote drops " + COMPOSITE_DEAD(item) +
            ".");
    }
    else
    {    
        write(capitalize(COMPOSITE_DEAD(item)) + " " +
            (size > 1 ? "are" : "is") + " too heavy for you. You drop " +
            (size > 1 ? "them" : "it") + " to the ground.\n");
        say(capitalize(COMPOSITE_DEAD(item)) + " " +
            (size > 1 ? "are" : "is") + "  too heavy for " +
            QTNAME(this_player()) + " and falls to the ground.\n");
    }
}

/*
 * Function name : hook_tavern_buy_notify_action
 * Description   : notify the player about the succesful buy
 * Arguments     : object* - the items player ordered
 *                 int*    - array of coins payed by the player
 *                 int*    - array of change player got
 * Returns       : void    - nothing is returned
 */
public void
hook_tavern_buy_notify_action(object *item, int *charge, int *change)
{
    if (!tavern_waiter())
    {
        write("You pay " + text(charge) + " for " + COMPOSITE_DEAD(item) +
            ".\n");

        if (strlen(text(change)))
        {
            write("You get " + text(change) + " back.\n");
        }

        return;
    }
    
    write("You pay " + tavern_waiter()->query_the_name(this_player()) +
        " " + text(charge) + ".\n");
    say(QCTNAME(this_player()) + " pays to " + QTNAME(tavern_waiter()) +
        ".\n");

    if (strlen(text(change)))
    {
        write("You get " + text(change) + " back.\n");
        say(QCTNAME(this_player()) + " gets some change back.\n");
    }

    write(tavern_waiter()->query_The_name(this_player()) + " gives you " +
        COMPOSITE_DEAD(item) + ".\n");
    say(QCTNAME(tavern_waiter()) + " gives " + COMPOSITE_DEAD(item) +
        " to " + QTNAME(this_player()) + ".\n");
}

/*
 * Function name : hook_tavern_menu_dark_room
 * Description   : notify that it is too dark to read the menu
 * Arguments     : void    - no arguments
 * Returns       : int     - 0 for notify_fail and 1 for the rest
 */
public int
hook_tavern_menu_dark_room()
{
    write("It is too dark to read things.\n");
    return 1;
}

/*
 * Function name : hook_tavern_menu_notify_header
 * Description   : writes a header for the menu
 * Arguments     : void    - no arguments
 * Returns       : void    - nothing is returned
 */
public void
hook_tavern_menu_notify_header()
{
    write(sprintf("\n\t%|52s\n\n", query_tavern_name()));
}

/*
 * Function name : hook_tavern_menu_format_prices
 * Description   : returns a format of price to print in menu
 * Arguments     : int     - the price
 * Returns       : string  - the formated money string
 */
string
hook_tavern_menu_format_prices(int price)
{
    int    *coins, *value, pc, gc, sc, cc;
 
    price = max(0, price);
    coins = MONEY_SPLIT(price);
    value = MONEY_VALUES;
 
    pc = coins[3];
 
    if (pc > 5)
    {
        return sprintf("%'.'3dp", pc);
    }
 
    gc = coins[2] + (value[3]*coins[3]) / value[2];
 
    if (gc > 5)
    {
        return sprintf("%'.'3dg", gc);
    }
 
    sc = coins[1] + (value[2]*coins[2] + value[3]*coins[3]) / value[1];
 
    if (sc > 5)
    {
        return sprintf("%'.'3ds", sc);
    }
 
    return sprintf("%'.'3dc", price);
}

/*
 * Function name : hook_tavern_menu_notify_dishes
 * Description   : writes one line of menu
 * Arguments     : string  - the name of drink/food/ware
 *                 int     - the price
 * Returns       : void    - nothing is returned
 */
public void
hook_tavern_menu_notify_dishes(string name, int cost)
{
    write(sprintf("\t%'.'-50s%s\n", capitalize(name),
        hook_tavern_menu_format_prices(cost)));
}

/*
 * Function name : hook_tavern_menu_notify_footer
 * Description   : writes a footer for the menu
 * Arguments     : void    - no arguments
 * Returns       : void    - nothing is returned
 */
public void
hook_tavern_menu_notify_footer()
{
}

/*
 * === activating functions ==============================================
 * =============================================================== *** ===
 */

/*
 * Function name : action_tavern_buy
 * Description   : handles attempts to buy something from the tavern
 * Arguments     : string  - string written by the player
 * Returns       : int     - 1 on success or 0 on failure
 */
public nomask int
action_tavern_buy(string text)
{
    int     quan, size, cost, *pays;
    string  name;
    object *item;
    
    if (!text)
    {
        return hook_tavern_buy_faulty_syntax(text);
    }

    if (this_object()->query_prop(ROOM_I_IS) && strlen(tavern_waiter) &&
        !objectp(tavern_waiter()))
    {
        return hook_tavern_buy_waiter_absent();
    }

    hook_tavern_buy_notify_header(text);
    
    if (tavern_waiter())
    {
        if (!CAN_SEE_IN_ROOM(tavern_waiter()))
        {
            return hook_tavern_answer_dark_room();
        }

        if (!CAN_SEE(tavern_waiter(), this_player()))
        {
            return hook_tavern_answer_invisible();
        }
    }
    
    if (!parse_command(text, ({}), "%d %s", quan, text))
    {
         quan = 1;
    }
    
    if (quan > MAXIMUM_BUYS)
    {
        return hook_tavern_buy_exceed_maximum(quan);
    }
    
    if (stringp(name = query_tavern_drink(text)))
    {
        item = clone_tavern_drink(name, quan);
    }
    else if (stringp(name = query_tavern_food(text)))
    {
        item = clone_tavern_food(name, quan);
    }
    else
    {
        item = map(query_tavern_wares(), &->get_this_object());

        if (sizeof(item) && sizeof(item = FIND_STR_IN_ARR(text, item)))
        {
            item = clone_tavern_wares(item[0], quan);
        }
    }

    if (!(size = sizeof(item)))
    {
        return hook_tavern_buy_faulty_syntax(text);
    }

    while (--size >= 0)
    {
        cost += item[size]->query_prop(OBJ_I_VALUE);
    }

    if (sizeof(pays = pay(cost, this_player(), "", 0, 0, "", 1)) == 1)
    {
        hook_tavern_buy_cannot_afford(item, cost);
        item->remove_object();
        return 1;
    }

    size = SIZEOF_MONEY_TYPES;

    hook_tavern_buy_notify_action(item, pays[0..(size - 1)],
        pays[size..(2 * size - 1)]);

    item = filter(item, &->move(this_player()));

    if (sizeof(item))
    {
        hook_tavern_buy_cannot_carry(item);
        item->move(environment(this_player()));
    }

    return 1;
}

/*
 * Function name : action_tavern_menu
 * Description   : handles attempts to read menu
 * Arguments     : string  - string written by the player
 * Returns       : int     - 1 on success or 0 on failure
 */
public nomask int
action_tavern_menu(string text)
{
    int     size, n, cost;
    string *list, name;
    object *item;

    if (!text || !parse_command(text, ({}), "[the] 'menu'"))
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if (!CAN_SEE_IN_ROOM(this_player()))
    {
        return hook_tavern_menu_dark_room();
    }

    if (!sizeof(query_tavern_drink()) && !sizeof(query_tavern_food()) &&
        !sizeof(query_tavern_wares()))
    {
        write("There appears to be nothing for sale here.\n");
        return 1;
    }

    hook_tavern_menu_notify_header();

    if (size = sizeof(list = query_tavern_drink()))
    {
        n = -1;
    
        while (++n < size)
        {
            if (!strlen(name = query_tavern_drink(list[n], DRINK_SING)))
            {
                name = query_tavern_drink(list[n], DRINK_NAME)[0];
            }

            hook_tavern_menu_notify_dishes(name,
                query_tavern_drink(list[n], DRINK_COST));
        }

        write("\n");
    }
    
    if (size = sizeof(list = query_tavern_food()))
    {
        n = -1;
    
        while (++n < size)
        {
            if (!strlen(name = query_tavern_food(list[n], FOOD_SING)))
            {
                name = query_tavern_food(list[n], FOOD_NAME)[0];
            }

            hook_tavern_menu_notify_dishes(name,
                query_tavern_food(list[n], FOOD_COST));
        }

        write("\n");
    }
    
    if (size = sizeof(list = query_tavern_wares()))
    {
        n    = -1;
        item = map(query_tavern_wares(), &->get_this_object());

        while (++n < size)
        {
            if (item[n]->query_prop(HEAP_I_IS))
            {
                name = item[n]->singular_short();
                cost = item[n]->query_prop(HEAP_I_UNIT_VOLUME);
            }
            else
            {
                name = item[n]->short();
                cost = item[n]->query_prop(OBJ_I_VALUE);
            }

            hook_tavern_menu_notify_dishes(name, cost);
        }
        
        write("\n");
    }

    hook_tavern_menu_notify_footer();

    return 1;
}

/*
 * Function name : init_tavern
 * Description   : adds tavern related actions to environment
 * Arguments     : void    - no arguments
 * Returns       : void    - nothing is returned
 */
public nomask void
init_tavern()
{
    add_action(action_tavern_buy ,   "buy");
    add_action(action_tavern_buy , "order");
    add_action(action_tavern_menu,  "read");
}
