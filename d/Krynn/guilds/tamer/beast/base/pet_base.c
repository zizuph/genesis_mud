
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <cmdparse.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <herb.h>
#include "defs.h"

inherit "/d/Krynn/guilds/tamer/beast/base/combat_base";

#include "emote.c"

static int      leave;
static string   vorare;


/*
 * Function name: query_race_name
 * Description  : Gives the race (species) name of this living. This may
 *                be set with set_race_name(). For players, the value
 *                returned for query_race() will always return one of the
 *                default races defined by the mud. For NPC's it is the same
 *                as query_race().
 * Returns      : string - the race name.
 */
public string
query_race_name()
{
    return query_maturity_race();
}

/*
 * Function name: query_race
 * Description  : If you define different player objects for different
 *                races you should mask this function in those objects to
 *                always return the true race of the living even though
 *                query_race_name gives the current race of the living.
 *                You should nomask the redefinition of this function.
 * Returns      : string - the race name.
 */
public string
query_race()
{
    return query_race_name();
}

/*
 * Function name: query_adjs
 * Description  : This function returns an array of all adjectives of
 *                this object.
 * Returns      : string * - an array of all adjectives of this object
 *                           or 0 if there are no adjectives.
 */
public string *
query_adjs() 
{
    string *adj, *arm;

    adj = ::query_adjs() + ({ query_maturity_desc() });
    
    //if (MANAGER->query_worn_armour(query_tamer_name()))
    if (sizeof(query_armour(-1)))
        arm = MANAGER->query_pet_armour(query_tamer_name());
    
    if (sizeof(arm))
        adj += arm[..1];
    
    return adj;
}

/*
 * Function name: query_adj
 * Description  : Gives the adjective(s) of the object.
 * Arguments    : int arg - if true, all adjectives are returns, else only
 *                          the first adjective is returned.
 * Returns      : mixed   - int 0    - if there are no adjectives.
 *                          string   - one adjective if 'arg' is false.
 *                          string * - an array with all adjectives if
 *                                     'arg' is true.
 */
varargs public mixed
query_adj(int arg)
{
    if (!arg)
        return query_adjs()[0];
    
    return query_adjs();
}

public int
adjectiv_id(string str)
{
    return IN_ARRAY(str, query_adjs());
}

public string *
parse_command_adjectiv_id_list() 
{
    return query_adjs();
}

/* 
 * Function:    parse_command_id_list
 * Description: This function removes the pet name so that the
 *              pet name cant be abused if named as players, it
 *              also adds pet_race as an id when the pet is a pup
 *
 */
public string *
parse_command_id_list()
{
    string  tamer,
            *arm,
            *list;
    
    list    = ({}) + query_names();
    tamer   = query_tamer_name();
           
    if (this_player()->query_real_name() != tamer)
        list -= ({ MANAGER->query_pet_name(tamer) });
    
    if (!IN_ARRAY(query_maturity_race(), list))
        list += ({ query_maturity_race() });
    
    if (MANAGER->query_worn_armour(query_tamer_name()))
        arm = MANAGER->query_pet_armour(query_tamer_name());
    
    if (sizeof(arm))
        list += arm[-1..];
    
    return list;
}

public string
query_nonmet_name()
{
    //if (MANAGER->query_worn_armour(query_tamer_name()))
    if (sizeof(query_armour(-1)))
        return implode(MANAGER->query_pet_armour(query_tamer_name()), " ");
    
    if (query_maturity() > 6)
        return implode(::query_adjs(), " ") + " " + query_maturity_race();
    
    return query_maturity_desc() + " " + query_maturity_race();
}

public string
query_long()
{
    object *armour;
    string  desc, long_desc,
            maturity, name,
            tamer;
    mixed   pet_adjs;
    mapping adj_desc;
    
    if (!strlen(tamer = query_tamer_name()))
        return ::query_long();
    
    maturity = (query_maturity() < 4 ? "young" : (query_maturity() > 6 ?
               "adult" : "adolescent"));
    name     = GENUS->query_name(query_genus());
    pet_adjs = ::query_adjs();

    if (!pointerp(pet_adjs))
        pet_adjs = ({ pet_adjs });
    
    pet_adjs -= ({ MANAGER->query_pet_size(tamer) });
    adj_desc =  GENUS->query_behaviour() + GENUS->query_appearance()
                + GENUS->query_colours();
    
    if (!sizeof(pet_adjs))
        return ::query_long();
    
    long_desc =  "This is " + LANG_ADDART(maturity) + " " + name
    + ", a member of the " + GENUS->query_family(query_genus()) + " family. "
    + GENUS->query_vorare_desc()[vorare] + " The " + query_race_name() + " is "
    + "of " + LANG_ADDART(MANAGER->query_pet_size(tamer)) + " stature. "
    + adj_desc[pet_adjs[0]] + (sizeof(pet_adjs) > 1 ? " "
    + adj_desc[pet_adjs[1]] : "");
    
    desc = (sizeof(armour = query_armour(-1)) ? armour[0]->pet_desc_long() +
    " " : "") + long_desc +  (m_sizeof(query_injury()) ? ("\nThe " +
    query_nonmet_name() + " is afflicted with injuries to " +
    this_object()->query_possessive() + " " +
    COMPOSITE_WORDS(m_indexes(query_injury())) + ".") : "");
    
    if (this_interactive()->query_real_name() == tamer)
        desc += " You may 'help tamers' for further information on the "
                + "guild.\n"
                + capitalize(this_object()->query_pronoun()) + " can "
                + GET_NUM_DESC(this_object()->query_stuffed(),
                this_object()->query_prop(LIVE_I_MAX_EAT), SD_STUFF) + ", is "
                + GET_NUM_DESC_SUB(this_object()->query_max_fatigue() -
                this_object()->query_fatigue(),
                this_object()->query_max_fatigue(),
                SD_FATIGUE, SD_STAT_DENOM, 1) + " and "
                + GET_PROC_DESC(this_object()->query_encumberance_weight(),
                SD_ENC_WEIGHT) + ".";
    
    desc += "\n";
    
    return desc;
}

/* 
 * Function name: create_steed
 * Description:   Creation function of the steed
 */
public nomask void
create_battle_beast()
{
    setuid();
    seteuid(getuid());
    
    set_name("pet");
    
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(KNIGHT_I_NO_RESCUE, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    
    this_object()->add_cmdsoul(PET_SOUL);
    this_object()->update_hooks();
}

public int
do_leave(string str)
{
    if (!this_player()->query_guild_member(GUILD_NAME) ||
         this_player()->query_real_name() != query_tamer_name())
        return 0;
    
    notify_fail("Return what? pet to the wilds?\n");
    if (!strlen(str) || !parse_command(str, ({}), 
                        "[the] 'pet' [to] [the] 'wilds'"))
    {
        return 0;
    }
    
    if (!leave || (time() - leave) > 20)
    {
        this_player()->catch_msg("Are you sure you wish to break the bond " +
        "with your pet and leave the taming of beasts behind you? If you " +
        "desire to abandon your calling as a beastmaster, please repeat " +
        "<return pet to the wilds>.\n");
        leave = time();
        return 1;
    }
    
    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        this_player()->catch_msg("The least you could do is let your pet " +
        "wander free in the wilderness. You can only return your pet to " +
        "the wilds if you are outside.\n");
        return 1;
    }
    
    this_player()->remove_lay_member();
    this_player()->catch_msg("You release " + QTNAME(this_object())
    + " back into the wilds.\n" + QCTNAME(this_object()) + " runs off into "
    + "the distance, turning to look back at you before hesitantly returning "
    + "to the wilderness.\n");
    this_player()->tell_watcher(QCTNAME(this_player()) + " release "
    + QTNAME(this_object()) + " back into the wilds.\n");
    
    this_object()->remove_object();
    return 1;
}

/* FOOD AND ARMOUR */

/* Function name: set_tamer
 * Description:   Sets the name of the tamer to whom the mount belongs.
 */
public void
set_vorare(string str)
{
    vorare = str;
}

/* Function name: query_tamer
 * Description:   Returns the name of the tamer to whom the mount belongs.
 */
public string
query_vorare()
{
    return vorare;
}

public int
can_feed(object food)
{
    return 1;
}

public int
is_diet(object food)
{
    mixed  *new,
           *match,
           *names,
           *adjs;
    int     i;
   
    if (!pointerp(adjs = food->query_adjs()))
        adjs = ({ food->query_adjs() });
    
    if (!pointerp(names = food->query_names()))
        names = ({ food->query_names() });
    
    new = explode(food->short() + " " + food->long(), " ") + names + adjs;
    
    for (i = 0; i < sizeof(new); i++)
    {
        if (!stringp(new[i]))
            continue;
        
        /*  This function was inspired by Gorboth's ogre forge,
            thank you for sharing your code  */
            
        sscanf(new[i], "%s?", match);
        sscanf(new[i], "%s.", match);
        sscanf(new[i], "%s,", match);
        sscanf(new[i], "%s!", match);
        sscanf(new[i], "%s;", match);

        if (match)
        {
            new[i] = match;
        }
        
        match = 0;
    }
    
    switch(vorare)
    {
        case "omnivore":
        return 1;
        
        case "herbivore":
        match = filter(new, &operator(>)(,-1) @ &member_array(, HERBIVORE));
            break;
            
        case "carnivore":
        match = filter(new, &operator(>)(,-1) @ &member_array(, CARNIVORE));
            break;
    }
    
    if (sizeof(match))
        return 1;
    
    return 0;
}

public varargs int
do_feed(object o, object feeder)
{
    int value = 0,
        success,
        skill;
    
    if (query_unconscious())
    {
        feeder->catch_msg(QCTNAME(this_object()) + " is unconscious " +
        "and is not responding to your nurturing attempts.\n");
    }
    
    if (!o->query_amount() || !o->query_prop(HEAP_I_IS))
    {
        feeder->catch_msg(QCTNAME(this_object()) + " isnt remotely "+
        "interested in the " + o->short()/*temp*/ + ".\n");
        return 1;
    }

    if (!is_diet(o))
    {
        feeder->catch_msg(QCTNAME(this_object()) + " is " + LANG_ADDART(vorare)
        + ", it doesnt eat this kind of food.\n");
        MANAGER->add_achievement(query_tamer(), FOOD_VORARE);
        return 1;
    }
    
    if (pointerp(o->query_effect()))
    {
        if (IN_ARRAY(HERB_POISONING, o->query_effect()))
        {
            feeder->catch_msg(QCTNAME(this_object()) + " refuses to eat the " +
            o->short()/*temp*/ + ", it may be poisonous.\n");
            MANAGER->add_achievement(query_tamer(), FOOD_POISON);
            return 1;
        }

    if (o->query_herb_value())
        value = o->query_herb_value() / 10;
    }
    
    if ((value += o->query_value()) && eat_food(o->query_amount(), 1) &&
        SATISFACTION >= MANAGER->query_satisfaction(feeder) + value &&
        feeder->query_real_name() == query_tamer_name())
    {
        //express_emotion("satisfaction", feeder);
        MANAGER->add_satisfaction(feeder, value, o);
        MANAGER->add_achievement(query_tamer(), FOOD_VALUE);
    }
    
    feeder->catch_msg("You feed " + QTNAME(this_object()) + " with " +
    LANG_ADDART(o->short()/*temp*/) + ".\n");
    
    tell_room(environment(this_object()), QCTNAME(feeder) + " feeds "
    + QTNAME(this_object()) + " with " + LANG_ADDART(o->short()/*temp*/)
    + ".\n", feeder);
    
    if (o->query_herb_name())
    {
        feeder->catch_msg(QCTNAME(this_object()) + " seems unaffected "+
        "by the effects of the " + o->short() + ".\n");
        MANAGER->add_achievement(query_tamer(), FOOD_HERB);
    }
    
    if (!value)
        MANAGER->add_achievement(query_tamer(), FOOD_NO_VALUE);
    
    skill   = feeder->query_base_skill(SS_ANI_HANDL);
    success = (max(1, skill) * max(1, (skill/5)) / query_maturity());
    
    if (feeder->query_real_name() == query_tamer_name() && !random(success))
        this_object()->do_skill_raise(SS_ANI_HANDL, this_player());
    
    eat_food(o->query_amount(), 0);
    o->reduce_heap_size(1);
    
    return 1;
}

public int
do_order(string str)
{
    string *order_list, order, request,
           *achievements;
           
    int     price;
    object  ob;
    
    if (!sizeof(order_list = GENUS->query_location(environment(this_object()))))
        return 0;
    
    if (!objectp(this_player()) || this_object() == this_player())
        return 0;
    
    if (this_player()->query_real_name() != query_tamer_name())
        return 0;
    
    if (sizeof(filter(order_list, &operator(>)(,-1) @ &member_array(,
        ({"herbivore", "carnivore", "omnivore"})))))
        order = "food";
    else if (sizeof(filter(order_list, &operator(>)(,-1) @ &member_array(,
            ({"metal", "leather"})))))
        order = "armour";
    
    achievements = MANAGER->query_achievements(this_player());

    setuid();
    seteuid(getuid());
    
    switch(order)
    {
        case "food":
        
        if (!IN_ARRAY(FOOD_INN, achievements))
            return 0;
        
        ob = clone_object(PET_FOOD);
        ob->set_vorare((order != "omnivore" ? order :
                       GENUS->query_vorare(query_genus())));
            break;
            
        case "armour":
        if (!IN_ARRAY(FIND_PET_ARMOUR, achievements))
            return 0;
        
        ob = clone_object(PET_ARMOUR);
            break;
        
        default:
            return 0;
    }
    
    if (!objectp(ob))
        return 0;
    
    price = ob->query_value();
    
    if (!strlen(str) || !parse_command(str, ({}), "[pet] / [beast] %s", request)
        || request != order)
    {
        notify_fail("Order what? " + capitalize(order) + "?\n");
        return 0;
    }

    if (IN_ARRAY(request, ({"armour", "armor"})))
    {
        ob->move(this_player());
        ob->start_armour(this_player(), this_object());
        return 1;
    }
    
    if (!MONEY_ADD(this_player(), -price))
    {
        this_player()->catch_msg("You were unable to afford to pay for the "
        + ob->short() + "\n");
        ob->remove_object();
        return 1;
    }
    
    ob->move(this_player());
    this_player()->catch_msg("You order " + ob->short() + " for "
    + capitalize(MANAGER->query_pet_name(this_player())) + ".\n");
    
    return 1;
}

void
init_living()
{
    ::init_living();
    
    if (this_player()->query_real_name() == query_tamer_name())
    {
        add_action(do_order,        "order");
        add_action(do_leave,        "return");
        this_player()->add_pet_skill_effect(this_object());
    }
}


/* Function name: move_living
 * Description:   Records the time in which the steed last moved.
 *                Further: if horse moves by itself (e.g. panic) move
 *                the riders as well. Also does a check
 *                for the destination when the steed has riders.
 * Arguments:     see original move_living function.
 * Returns:       see original move_living function.
 *                int 8 if the destination was not valid
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    object  player;
    int     result;
    
    if (objectp(player = query_tamer()) && idle_time() > 1200)
    {
        result = player->query_age() - MANAGER->query_pet_age(player);
        result += (idle_time() / 2);
        MANAGER->set_pet_age(player, result);
    }
    return ::move_living(how, to_dest, dont_follow, no_glance);
}

public int
query_idle_pet()
{
    if (!objectp(query_tamer()) || environment(query_tamer()) != environment())
        return idle_time();
    
    return 0;
}