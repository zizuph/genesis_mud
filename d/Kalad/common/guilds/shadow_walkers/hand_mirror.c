inherit "/std/object";
#include "/d/Kalad/defs.h"
/* Sarr */


void
create_object()
{
    set_name("mirror");
    add_adj("hand");
    set_short("hand mirror");
    set_long("This is a short wooden pole with two mirrors on each "+
    "end. If you are skilled enough, you can discreetly use it to "+
    "look around corners without being noticed. Do 'mview "+
    "<an obvious exit>'.\n");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,90);
    add_prop(OBJ_I_VOLUME,50);
}

void
init()
{
    ::init();
    AA(do_view,mview);
}


static void
describe_combat(object *livings)
{
    int     index;
    int     size;
    string  text = "";
    string  subst = "";
    object  victim;
    mapping fights = ([ ]);

    /* Sanity check. No need to print anything if there aren't enough
     * people to actually fight. Note that if there is only one living, it
     * is possible that we fight that living.
     */
    if ((size = sizeof(livings)) < 1)
    {
	return;
    }

    /* First compile a mapping of all combats going on in the room.
     * The format is the victim as index and an array of all those
     * beating on the poor soul as value. Add this_object() to the
     * list since it isn't in there yet.
     */
    livings += ({ this_object() });
    size++;
    index = -1;
    while(++index < size)
    {
	/* Only if the living is actually fighting. */
	if (objectp(victim = livings[index]->query_attack()))
	{
	    if (pointerp(fights[victim]))
	    {
		fights[victim] += ({ livings[index] });
	    }
	    else
	    {
		fights[victim] = ({ livings[index] });
	    }
	}
    }

    /* No combat going on. */
    if (!m_sizeof(fights))
    {
	return;
    }

    /* First we describe the combat of the player him/herself. This will
     * be a nice compound message. Start with 'outgoing' combat.
     */
    if (objectp(victim = this_object()->query_attack()))
    {
	fights[victim] -= ({ this_object() });

	/* Victim is fighting back. */
	if (victim->query_attack() == this_object())
	{
	    text = "You are in combat with " +
		victim->query_the_name(this_object());
	    fights[this_object()] -= ({ victim });
	    subst = " also";
	}
	else
	{
	    text = "You are fighting " +
		victim->query_the_name(this_object());
	}

	/* Other people helping us attacking the same target. */
	if (sizeof(fights[victim]))
	{
	    text += ", assisted by " + FO_COMPOSITE_LIVE(fights[victim],
		this_object());
	}
	fights = m_delete(fights, victim);

	/* Other people hitting on me. */
	if (index = sizeof(fights[this_object()]))
	{
	    text += ", while " + FO_COMPOSITE_LIVE(fights[this_object()],
		this_object()) + ((index == 1) ? " is" : " are") +
		subst + " fighting you";
	}
	text += ".\n";
    }
    /* If we aren't fighting, someone or something may be fighting us. */
    else if (index = sizeof(fights[this_object()]))
    {
	text = capitalize(FO_COMPOSITE_LIVE(fights[this_object()],
	    this_object())) + ((index == 1) ? " is" : " are") +
	    " fighting you.\n";
    }

    /* Now generate messages about the other combat going on. This will
     * not be as sophisticated as the personal combat, but it will try to
     * to circumvent printing two lines of 'a fights b' and 'b fights a'
     * since I think that is a silly way of putting things.
     */
    fights = m_delete(fights, this_object());
    livings = m_indices(fights);
    size = sizeof(livings);
    index = -1;
    while(++index < size)
    {
	/* Victim is fighting (one of his) attackers. */
	if (objectp(victim = livings[index]->query_attack()) &&
	    (member_array(victim, fights[livings[index]]) >= 0))
	{
	    fights[livings[index]] -= ({ victim });
	    /* Start with the the name of one of the fighters. */
	    text += livings[index]->query_The_name(this_object());

	    /* Then the people helping the first combatant. */
	    if (pointerp(fights[victim]))
	    {
		text += ", with the assistance of " +
		    FO_COMPOSITE_LIVE(fights[victim], this_object());
		fights = m_delete(fights, victim);
	    }

	    /* Then the second living in the fight. */
	    text += " and " + victim->query_the_name(this_object());

	    /* And the helpers on the other side. */
	    if (sizeof(fights[livings[index]]))
	    {
		text += ", aided by " +
		    FO_COMPOSITE_LIVE(fights[victim], this_object());
	    }

	    text += " are fighting eachother.\n";
	}
	else
	{
	    text += capitalize(FO_COMPOSITE_LIVE(fights[livings[index]],
		this_object())) +
		((sizeof(fights[livings[index]]) == 1) ? " is" : " are") +
		" fighting " +
		livings[index]->query_the_name(this_object()) + ".\n";
	}

	fights = m_delete(fights, livings[index]);
    }

    write(text);
}

int
do_view(string str)
{
    int brief;
    int index,i,awar,snk;
    string *room_fnames, *room_exits;
    object room,*contents;
    
    object env;
    object *ob_list;
    object *lv;
    object *dd;
    string item;
    brief == 0;
    NF("There is no obvious exit "+str+" to view towards.\n");
    room_exits = E(TP)->query_exit_cmds();
    index = member_array(str,room_exits);
    if(index == -1)
        return 0;
    room_fnames = E(TP)->query_exit_rooms();
    room = find_object(room_fnames[index]);
    NF("That room is weird..I think.\n");
    if(!room)
        return 0;
    
    /* Don't waste the long description on NPC's. */
    if (!interactive(TP))
    {
	return 0;
    }


    write("You hold out the mirror around the corner and take a "+
    "peek.\n");
    say(QCTNAME(TP)+" holds out a mirror and uses it to look around "+
    "the corner.\n");
    contents = FILTER_LIVE(all_inventory(room));
    for(i=0;i<sizeof(contents);i++)
    {
        snk = TP->query_skill(SS_SNEAK);
        awar = contents[i]->query_skill(SS_AWARENESS);
        if((random(snk)+snk) < (random(awar) + awar))
        {
            contents[i]->catch_msg("You notice a hand and a mirror "+
            "peeking out of a corner.\n");
        }
    }
    /* Wizard gets to see the filename of the room we enter and a flag if
     * there is WIZINFO in the room.
     */
    env = room;
    if (TP->query_wiz_level())
    {
	if (stringp(env->query_prop(OBJ_S_WIZINFO)))
	{
	    write("Wizinfo ");
	}

	write(file_name(env) + "\n");
    }

    /* It is dark. */
    if (!CAN_SEE_IN_ROOM(TP))
    {
 	if (!stringp(item = env->query_prop(ROOM_S_DARK_LONG)))
 	    write(env->query_prop(ROOM_S_DARK_LONG));
 	else
 	    write(item);
	return 1;
    }

    /* Describe the room and its contents. */
#ifdef DAY_AND_NIGHT
    if (!env->query_prop(ROOM_I_INSIDE) && 
	((HOUR > 21) ||
	 (HOUR < 5)) &&
	((env->query_prop(OBJ_I_LIGHT) +
	 query_prop(LIVE_I_SEE_DARK)) < 2))
    {
	write(LD_IS_NIGHT(env));
    }
    else
#endif
    {
	if (brief)
  	{
	    write(capitalize(env->short()) + ".\n");

	    if (!env->query_noshow_obvious())
	    {
		write(env->exits_description());
	    }
	}
	else
	{
	    write(env->long());
	}
    }

    ob_list = all_inventory(env);
    lv = FILTER_LIVE(ob_list);
    dd = FILTER_SHOWN(ob_list - lv);

    item = COMPOSITE_FILE->desc_dead(dd, 1);
    if (stringp(item))
    {
	write(break_string(capitalize(item) + ".", 76) + "\n");
    }
    item = COMPOSITE_FILE->desc_live(lv, 1);
    if (stringp(item))
    {
	write(break_string(capitalize(item) + ".", 76) + "\n");
    }

    /* Give a nice description of the combat that is going on. */
    describe_combat(lv);
    
    

    return 1;
}

