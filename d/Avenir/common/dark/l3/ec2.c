// file name: ~Avenir/common/dark/l3/ec2.c
// creator:   Avenir wizards 1994.
// updates:   Lilith Jan 2022: added link to Vampire coven2 meeting room.
// purpose:
// note:
// bug(s):
// to-do:     move to /d/Avenir/common/outpost/cv/meeting

inherit "/std/room";
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Faerun/guilds/vampires/guild.h";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <options.h>

#define ALLOWED     "_live_i_am_allowed_access" 
#define OTHER_ROOM  "/d/Avenir/common/outpost/cv/meeting"
		
string
check_prints()
{
	string str;
	str = "The handprints on the walls here appear to have been made "+
        "in blood.\n";
		
    if (VAMPIRES_MASTER->is_coven2_member(this_player()->query_name()) == 1)
	{
        str += "You have a strong feeling that if you place your hand "+
            "on a matching handprint, you will gain access to a "+
            "different place.\n...Something also tells you that you "+
			"can <allow [name]> to grant temporary access to someone "+
            "here in the alcove with you.\n";
    }

    if (this_player()->query_prop(ALLOWED))
	{
        str += "You have a strong feeling that if you place your hand "+
            "on a matching handprint, you will gain access to a "+
            "different place.\n";
    }
  
    return str;	
}

void
create_room() 
{
    set_short("Dark alcove");
    set_long(
"A dark alcove that must be a meeting place of sorts for the creatures\n"+
"that dwell in these tunnels. The air is filled with fear and despair,\n"+
"bloodlust and anticipation. There are symbols inscribed on the walls\n"+
"here, mostly spirals, and what looks like handprints from various\n"+
"humanoids.\n");

    add_exit("/d/Avenir/common/dark/l3/e3","west",0);

    add_item(({"symbols","spirals", "wall", "walls"}),  
        "There are several symbols inscribed on the walls. The only one "+
        "that has any meaning to you is the spiral, symbol of Aclolthayr "+
        "the Goddess of the Hunt in Sybarus.\n");	
    add_item(({"handprints", "blood", "humanoid handprints", "bloody "+
        "handprints"}), check_prints);   
	
    add_prop(ROOM_I_LIGHT, -2);
    add_prop(ROOM_I_INSIDE, 1);
}

int allow_it(string str)
{
    object who;

    /* Coven2 meeting room */
	if (!VAMPIRES_MASTER->is_coven2_member(this_player()->query_name()) == 1)
    {
        notify_fail("You cannot do that.\n");
		return 0;
	}
	
    if (!str || str == "me" || str == "myself")
    {
        notify_fail(capitalize(query_verb()) + " whom?\n");
        return 0;
    } 

    who = present(str, environment(this_player()));
    if (!who)
    {
        write("You can only "+ query_verb() +" a person who is "+
            "present in the room with you.\n");
		return 1;
    }
   
    if (!interactive(who)) 
    {
        write("You can only "+ query_verb() +" a person who is "+
            "present in the room with you.\n");
        return 1;
    }
	
    who->add_prop(ALLOWED, 1);	
    this_player()->catch_msg("You "+ query_verb() +" "+ 
        who->query_cap_name() +
        " access to your coven's meeting place.\n");
    who->catch_msg(QCTNAME(this_player()) + " indicates that you may "+
        "now place your hand over a handprint in order to access "+
        "another place.\n");
		
   return 1;	
}	

int place_it(string str)
{

    notify_fail(capitalize(query_verb()) + " what where?\n");
    if (!strlen(str))
	return 0;

    /* place hand on matching handprint */
    if (!parse_command(str, ({}),
	"[the] / [my] 'hand' 'to' / 'on' / 'onto' / 'against' / 'over' "+
	"[top] [of] [a] / [the] "+
	"[matching] 'handprint' / 'print' [on] [the] [wall]", str))
    {
        notify_fail("Are you trying to place your hand on a "+
            "handprint?\n");
        return 0;
    }

    /* This isn't meant to be an escape from combat */
    if (!this_player()->query_relaxed_from_combat())
    {
        write("You try to " + query_verb() + " your hand on a "+
            "handprint, but you're too full of adrenaline "+
            "make a good match.\n");
        say(QCTNAME(this_player()) +" leans a hand against the wall.\n");
        return 1;
    }

    /* This isn't meant to be an escape from combat */
    if (this_player()->query_option(OPT_BLOCK_INTIMATE))
    {
        write("You place your hand over a handprint. The wall is cold and "+
        "and damp under it.\n");
        say(QCTNAME(this_player()) +" leans a hand against the wall.\n");
        return 1;
    }

    /* Coven2 owns this */
    if (VAMPIRES_MASTER->is_coven2_member(this_player()->query_name()) == 1)
	{
		write("As you place your hand on a matching handprint you feel "+
            "a tickle and a flash of heat.\n");
        say(QCTNAME(this_player()) +" leans a hand against the wall and "+
            "is swallowed by darkness.\n");
        this_player()->move_living("X", OTHER_ROOM, 1, 0);
		return 1;
    }
	
    /* Infidels not welcome */
    if (IS_INFIDEL(this_player()))
    {
 		write("As you place your hand on a matching handprint you feel "+
            "an intense burning sensation.\n");
        say(QCTNAME(this_player()) +" leans a hand against the wall and "+
           "then jerks it back.\n");
		return 1;
    }

    /* Has player been allowed access? */
    if (this_player()->query_prop(ALLOWED))
    {
        this_player()->remove_prop(ALLOWED);
		write("As you place your hand on a matching handprint you feel "+
            "a tickle and a flash of heat.\n");
        say(QCTNAME(this_player()) +" leans a hand against the wall and is "+
            "swallowed by darkness.\n");
        this_player()->move_living("X", OTHER_ROOM, 1, 0);
		return 1;
    }		



    write("You place your hand over a handprint. The wall is cold and "+
        "and damp under it.\n");
    say(QCTNAME(this_player()) +" leans a hand against the wall.\n");
    return 1;
}

public void
init()
{
	::init();
	
	add_action(place_it, "place");
	add_action(place_it, "fit");
	add_action(place_it, "lay");
	add_action(place_it, "match");
	add_action(place_it, "overlay");
	add_action(place_it, "touch");
	

    if (VAMPIRES_MASTER->is_coven2_member(this_player()->query_name()) == 1)
	{
        add_action(allow_it, "allow");
        add_action(allow_it, "grant");
        add_action(allow_it, "permit");	
	}
}


/*
 * Function to cleanup props if a player leaves the room.
 */
void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob->query_prop(ALLOWED))
	ob->remove_prop(ALLOWED);        

}
