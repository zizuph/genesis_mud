/* This is a live flea, normally found on the heads of Grunts who have    */
/* not been trying to think too hard. Coded 07/05/96 by Tulix III.        */

inherit "/std/object";
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Emerald/tulix/t_defs.h"
#include "/d/Emerald/common/guild/grunts/grunts_defs.h"

#pragma strict_types

/* Global variable */
public int flea_size;

/* Prototype functions */
public void do_config(object owner);
public string extra_desc();
public int do_eat(string str);
public int do_infest(string str);
public void do_bite(object target);
public int do_kill(string str);


public void
create_object()
{
    set_name("flea");
    set_pname("fleas");
    
    set_short("flea");
    set_pshort("fleas");
    set_long("This flea is a parasite which is only common among the " +
        "goblins who inhabit Emerald. " + "@@extra_desc");
 
 
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 2); /* Looks like it will float. */
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "Fleas do not sell very well.\n");

    add_prop(OBJ_S_WIZINFO, "This flea is edible, and can be used " +
        "by Grunts to infest other players. Not useful, just fun - so no " +
        "tax is charged for it. This flea came from the head of a Grunt.\n");

    flea_size = 0;
}


/*
 * Function name:   enter_env
 * Description:     called when this object enters a new environment
 * Arguments:       env: destination environment
 *                  old: previous environment
 */
public void
enter_env(object env, object old)
{
    ::enter_env(env, old);
    
    if (!flea_size && interactive(env))
        do_config(env);
    
    return;
}

public void
init()
{
    ::init();

    /* query_guild_name_race() is defined by the guild shadow */
    if ((TP->query_guild_name_race()) == GUILD_NAME)
        add_action(do_infest, "infest");
    
    add_action(do_kill, "kill");
    add_action(do_eat, "eat");
}

/*
 * Function name:   do_config
 * Description:     configure the flea according to the Grunt's rank.
 * Arguments:       onwer: the Grunt who has harvested this flea.
 */
public void    
do_config(object owner)
{
    int grunt_level;
    string flea_adj;
    
    if ((owner->query_guild_name_race()) == GUILD_NAME)
    { 
        grunt_level = owner->query_grunts_level();
        if (grunt_level >= 100)
            grunt_level = 100;
    
        flea_adj = "tiny";        
        
        if (grunt_level > 10)
            flea_adj = "small";        
        if (grunt_level > 20)
            flea_adj = "live";        
        if (grunt_level > 30)
            flea_adj = "large";        
        if (grunt_level > 40)
            flea_adj = "huge";        
        if (grunt_level > 50)
            flea_adj = "gigantic";        
           
        set_short(flea_adj + " flea");
        set_pshort(flea_adj + " fleas");
        set_adj(flea_adj);
    }
    else
    {
        flea_size = 1;
    }

    /* Make sure that the object is only configured once. */
    flea_size = grunt_level;
}

/*
 * Function name: extra_desc
 * Description:   Give a race dependant string to add to the set_long().
 * Returns:       string - contains the extra desciption
 */
public string
extra_desc()
{
    string race;

    if ((TP->query_guild_name_race()) == GUILD_NAME)
    { 
        return "You can either eat this flea (they're usually better " +
            "when cooked), or you can try and put it down someone else's " + 
            "back - to do this, use 'infest <person>'.\n";
    }
    
    race = TP->query_race_name();

    switch (race)
    {
        case "goblin":
            return "Though uncooked, it still looks good to eat.\n";

        case "dwarf":
            return "Dwarves don't eat raw fleas, generally.\n";
        
        case "gnome":
            return "Gnomes tend not to eat raw fleas.\n";
        
        case "hobbit":
            return "Hobbits hate the taste of these fleas, especially raw.\n";
        
        case "elf":
            return "An elf wouldn't stoop to eating this, even if cooked.\n";
        
        case "human": 
            return "Eating it would probably not be pleasant.\n";
    }

    return "You're not sure if you should eat it or not.\n";
}

/*
 * Function name: do_eat
 * Description:   Goblins eat the fleas uncooked, other races don't.
 * Arguments:     str - string name of object to be eaten.
 */
public int
do_eat(string str)
{
    string race;
    object food;

    race = TP->query_race_name();

    /*  use parse_command to check what player wants to eat. */
    parse_command(str, TP, "[the] %o", food);
    
    if ((!objectp(food)) || (food != TO)) 
    {
        NF("Eat what?\n");
        return 0;
    }
    
    switch (race)
    {
        case "goblin": 
        {    
            write("You happily crunch the flea between your teeth.\n" +
                "The flea tasted good, but would have been better cooked.\n");
            say(QCTNAME(TP) + " happily crunches a flea between " + 
                POS(TP) + " teeth.\n");
            
            remove_object();
            break;
        }
        
        default:
        {
            write("You think about eating the flea. You decide not to.\n");
            say(QCTNAME(TP) + " thinks about eating a flea, but decides " +
                "not to...\n");
            break;
        }
    }
    return 1;
}

/*
 * Function name: do_infest
 * Description:   Put the flea down someone else's back.
 * Arguments:     str - string name of object to be 'bugged'.
 */
public int
do_infest(string str)
{    
    string race;
    mixed *target_arr;
    object target;

    if (!strlen(str))
    {
        NF("Infest whom?\n");
        return 0;
    }

    /*  use parse_command to check who we want to infest. */
    parse_command(str, ENV(TP), "[the] %l", target_arr);
    
    if (sizeof(target_arr) < 2)
    {
        NF("Infest whom?\n");
        return 0;
    }
    
    if (!living(target_arr[1]))
    {
        NF("Infest whom?\n");
        return 0;
    }
    
    if (sizeof(target_arr) != 2)
    {
        NF("Infest whom? A single flea can only infest one person.\n");
        return 0;
    }
    
    target = target_arr[1];

    if (target == TP)
    {
        write("You decide against that course of action.\n");
        return 1;
    }

    if (TP->query_base_stat(SS_DEX) >= target->query_skill(SS_AWARENESS))
    {
        TP->catch_msg("You deftly slip the flea down " + QTNAME(target) + 
            "'s neck.\n");

        TO->move(target);
        set_alarm( 6.0, 0.0, &do_bite(target));
    }
    else
    {
        TP->catch_msg(QCTNAME(target) + " notices you, and moves away.\n");
        
        target->catch_msg("\n" + QCTNAME(TP) + " tries to put a flea down " +
            "your neck, but fails.\n");
    }    
    return 1;
}

/*
 * Function name: do_bite
 * Description:   Make the flea bite the infested player.
 * Arguments:     target - the person to be bitten.
 */
public void
do_bite(object target)
{
    /* Check to see if the flea has been dropped etc. */
    if (target != ENV(TO))
        return;

    /* Make sure npc's and creatures do something sensible. */ 
    if (!interactive(target))
    {
        tell_room(ENV(target), QCTNAME(target) + " scratches frantically, " +
            "having picked up a flea somehow.\n", target);
        return;
    }

    set_this_player(target);

    /* Okay, now lets deal with mortals. */
    if (flea_size <= 10)
    {
        write("You itch. It seems you have got a flea!\n");
        say("\n" + QCTNAME(target) + " itches, having got a flea somehow!\n");
        return;
    }

    if (flea_size <= 20)
    {
        write("You scratch hard as a fleas nips your neck!\n");
        say("\n" + QCTNAME(target) + " scratches hard as a flea nips " + 
            POS(target) + " neck!\n");
        return;
    }   

    if (flea_size <= 30)
    {
        write("You jump slightly as a flea bites you on the back!\n");
        say("\n" + QCTNAME(target) + " jumps slightly as a flea bites " + 
            POS(target) + " back!\n");
        return;
    }   

    write("You leap high up in the air, clutching your buttocks...\n" +
        "It seems you have a flea biting your posterior!!\n");
    say("\n" + QCTNAME(target) + " yelps, then leaps high up into the air, " +
        "clutching " + POS(target) + " buttocks!\n" + capitalize(PRON(target)) + 
        " must " + "have a flea biting " + POS(target) + " posterior!\n");
    return;
}   

/*
 * Function name: do_kill
 * Description:   This function is called when somebody attacks this object
 * Arguments:     str - The string name og this object
 */
public int
do_kill(string str)
{
    object target;
    
    if (!strlen(str))
    {
        return 0; /* the mudlib will handle the fail mgs */
    }

    /*  use parse_command to check who we want to infest. */
    parse_command(str, ENV(TP), "[the] %o", target);
    
    if (target != TO)
    {
        NF("Kill whom?\n");
        return 0;
    }
    
    tell_room(ENV(TP), QCTNAME(TP) + " stamps on a flea.\n", TP);
    TP->catch_msg("You stamp on the flea.\n");

    remove_object();
    return 1;
}

