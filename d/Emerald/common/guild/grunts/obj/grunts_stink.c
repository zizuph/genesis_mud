/* This object creates a nasty smell - originally coded by Charon.        */
/* Recoded 17/06/95 by Tulix III.                                         */
/* It is a lingering reminder of the goblin dung that was thrown at you.  */

inherit "/std/object";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/common/guild/grunts/grunts_defs.h"

/* Define the sub-location which we are going to add to the player */
#define SUBLOC "stink_object_subloc"

/* Prototype functions */
public void do_smell();
public void reset_smell(); 
public string show_subloc(string subloc, object carrier, object for_obj);

/* Global variable */
int i;

public void
create_object()
{
    set_name("grunts_stink");
    set_no_show();                            /* Make completely invisible */
}

/*
 * Function name:   enter_env
 * Description:     called when this object enters a new environment
 * Arguments:       dest: destination environment
 *                  old:  previous environment
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    set_alarm( 65.0, 65.0, do_smell); /* Tell room how badly player smells */
    
    if (living(dest)) /* If destination object is living, add sub-location */
        dest->add_subloc(SUBLOC, TO);
    
    return;
}

/*
 * Function name:   do_smell
 * Description:     tell everyone about the players current odour
 */
public void
do_smell()
{
    i++;
    if (!living(ENV(TO)))
    {
        TO->remove_object();
        return;
    }

    set_this_player(ENV(TO)); /* this_player() not defined by set_alarm() */
    
    
    if (i >= 10)
    {
        tell_room(ENV(TP), QCTNAME(TP) + " seems to have shaken off " +
            "the nasty stench of goblin dung.\n", TP);
        
        write("You seem to have shaken off the nasty stench of " +
            "goblin dung.\n");
        
        TP -> remove_subloc(SUBLOC);  /* remove sub-location and this */
        TO -> remove_object();        /* object when smell is gone    */
        return;
    }

    if (i >=8)
    {
        tell_room(ENV(TP), QCTNAME(TP) + " still smells like a " +
            "pile of goblin dung, but not as badly.\n", TP);
        
        write("You still smell like a pile of goblin dung, but not as " +
            "badly as before.\n");
        
        return;
    }
    
    if (i >=7)
    {
        tell_room(ENV(TP), QCTNAME(TP) + " is suddenly surrounded by " +
            "a swarm of flies.\n", TP);
        
        write("You are suddenly surrounded by a swarm of flies.\n");
        
        return;
    }
    
    if (i >=4)
    {
        tell_room(ENV(TP), QCTNAME(TP) + " reeks of goblin dung. " +
            "The stench is quite over-powering.\n", TP);
        
        write("You reek of goblin dung, rather badly.\n");
        
        return;
    }
    
    if (i >=2)
    {
        tell_room(ENV(TP), QCTNAME(TP) + " stinks of goblin " +
            "dung. You wish you were not so close!\n", TP);
        
        write("You stink of maturing goblin dung.\n");
        
        return;
    }

    tell_room(ENV(TP), QCTNAME(TP) + ", unfortunately, smells like " + 
        "a pile of decaying goblin dung.\n", TP);
        
    write("You smell, alas, exactly like a pile of goblin dung.\n");
    
    return;
}

/*
 * Function name:   reset_smell
 * Description:     reset i to 0: takes player back to the first smell.
 */
public void
reset_smell()
{
    i = 0;    /* This is called when you slip in some more dung or have   */
    return;   /* some hit you if the face. Hence we reset to first smell. */
}

/*
 * Function name:   show_subloc
 * Description:     tell inquisitive people how badly this player smells
 * Arguments:       subloc:  string identifying this sub-location
 *                  carrier: player carrying this object
 *                  for_obj: the player who is examining the carrier 
 * Returns:         sting describing the carriers hygiene problems
 */
public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier -> query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return ""; /* Don't show sub-location as inventory */

    if (for_obj == carrier)
        str = "You stink ";
    else
        str = capitalize(carrier->query_pronoun()) + " stinks ";

    return str + "like a decaying pile of goblin dung.\n";
}
