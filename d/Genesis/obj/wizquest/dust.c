/* Dust of contrariness, made for the wizquest by Quis 920518 */

inherit "/std/object";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>

#define REVERSE_SOUL "/d/Genesis/obj/wizquest/reverse_soul"

object rubbed_player = 0;

void start_curse(int timeleft);

query_auto_load()
{
    if (rubbed_player)
	return MASTER + ":" + find_call_out("timeout");
    else
	return 0;
}

void
init_arg(string arg)
{
    int timeleft;

    write("You still feel quite confused.\n");
    sscanf(arg, "%d", timeleft);
    start_curse(timeleft);
}

void
create_object()
{
    set_name("dust");
    set_name("pile");
    set_name("dust of contrariness");
    set_long("This dust looks rather special. Better hang onto it!\n");
    set_short("pile of dust");
    
    add_prop(MAGIC_AM_ID_INFO, ({"@@wrong",10,"@@right",50}));
    add_prop(MAGIC_AM_MAGIC, ({100, "enchantment", 20, "curse"}));
    add_prop(MAGIC_I_RES_IDENTIFY, 50);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 10000);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(OBJ_M_NO_SELL, "You cannot sell THAT!\n");
    add_prop(OBJ_M_NO_BUY, "That cannot be bought this way.\n");
}

string
right()
{
    return
	break_string("This is dust of contrariness.  Rubbing it into your face " +
	   "will cause you to do opposite your intentions. " +
	   "\n", 70);
}

string
wrong()
{
    return
	break_string("This is dust of vanishing.  Rubbing it into your face " +
	   "will cause you to disappear! " +
	   "\n", 70);
    
}

void
init()
{
    add_action("rub_dust", "rub");
}

int
rub_dust(string str)
{
    notify_fail("Rub what?\n");
    if (!str)
	return 0;

    if (parse_command(str, this_object(), " 'me' / 'myself' 'with' 'dust' "))
    {
	write("You rub the dust in your face. " +
	      "You feel slightly dizzy for a moment.\n");
	say(QCTNAME(this_player()) + " rubs some dust into " +
		    this_player()->query_possessive() + " face.\n"); 
	start_curse(600);
	return 1;
    }
    return 0;
}

int
timeout()
{
    this_player()->remove_cmdsoul(REVERSE_SOUL);
    this_player()->update_hooks();
    tell_object(rubbed_player, "Things seem much clearer.\n");
    ::remove_object();
    return 0;
}

public int
remove_object()
{
    if (rubbed_player)
	timeout();
    ::remove_object();
}

wizinfo()
{
    return(break_string("The Dust of Contrariness is a part of " +
			"the Wizard's quest.\n",70)); 
    
}

void
start_curse(int timeleft)
{
    int i;
    string *list;
    
    list = this_player()->query_cmdsoul_list();
    this_player()->add_cmdsoul(REVERSE_SOUL);
    this_player()->update_hooks();
    for(i = 0; i < sizeof(list); i++) 
	this_player()->remove_cmdsoul(list[i]);
    
    for(i = 0; i < sizeof(list); i++)
    {
	this_player()->add_cmdsoul(list[i]);
	this_player()->update_hooks();
    }
    
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_INVIS,1);
    set_no_show();
    rubbed_player = this_player();
    call_out("timeout", timeleft);

}

object
query_rubbed()
{
    return rubbed_player;
}
