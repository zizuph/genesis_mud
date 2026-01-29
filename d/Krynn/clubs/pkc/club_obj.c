/* created by Aridor 12/01/93
 * 
 * The scabbard or holster of the Prestigious Knights' Club.
 * It's the guild object.
 *
 */
inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "clubdefs.h"

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>

string location = "side";
string my_type = "scabbard";

/*prototypes*/
void soul(object ob);
int is_a_real_scabbard();


string 
query_auto_load() 
{
    return MASTER_OB(TO) + ":" + location + " " + my_type;
}

void
init_arg(string arg)
{
    int num1, num2;
    string str1, str2;
    
    if (sscanf(arg, "%s %s", str1, str2) == 2)
    {
	location = str1;
	my_type = str2;
    }
}

void
check_if_owner_still_member()
{
    if (!environment() || !living(environment()))
	return;

    set_this_player(environment());
    
    if (!TP->query_wiz_level() && 
	CLUBMASTER->is_no_longer_a_member(TP))
    {
	CLUBMASTER->expel_from_club(TP, 
	    "You have not been faithful enough " +
	    "to the Prestigious Knights' Club.\n" +
	    "You have deserted the club for too " +
	    "long and have been removed from the " +
	    "club.\nOf course you will have the " +
	    "chance again to become a member.\n");
    }
    else
	set_no_show_composite(1);
}

void
create_object()
{
    set_name("scabbard");
    add_name(IN_CLUB);
    set_adj("traditional");
    add_adj("ornamented");
    set_long("@@my_long@@");
    add_prop(OBJ_M_NO_DROP, "You cannot drop your personal scabbard.\n");
    set_alarm(5.0, 0.0, &check_if_owner_still_member());

    setuid();
    seteuid(getuid());
}

/*
 * We use leave_env since it better handles linkdeath.
 */
public void
leave_env(object from, object to)
{
    object sheathed = from->query_prop(CLUB_O_SHEATHED_WEAPON);

    ::leave_env(from, to);
    
    if (sheathed)
    {
	sheathed->add_prop(OBJ_M_NO_DROP,
	    sheathed->query_prop(CLUB_M_TMP_NO_DROP));
	sheathed->unset_no_show();
	sheathed->unset_no_show_composite();
	from->catch_msg("You retrieve your " + sheathed->short() +
	    " from the " + my_type + ".\n");
	from->remove_prop(CLUB_O_SHEATHED_WEAPON);	
    }
    
    setuid();
    seteuid(getuid());    
    CLUBMASTER->mark_supporter_logout(from);
}


string
my_long()
{
    object sheathed = TP->query_prop(CLUB_O_SHEATHED_WEAPON);
    if (!location)
    {
	location = "side";
	TP->add_prop(CLUB_S_SCABBARD_LOCATION, location);
    }
    return "This is your personal traditional " + my_type + ". It is " +
	"beautifully crafted and has fine and detailed carvings and " +
	"ornaments on in. This is your personal status symbol of " +
	"membership in the Prestigious Knights' Club. Inscribed in the " +
	my_type + ", you can make out the word: " + 
	capitalize(TP->query_real_name()) + ". If you want to know more " +
	"about the Knights' Club type 'help knights club'.\nThe " + my_type +
	" is strapped to your " + location +
	(sheathed ?
	    (" and " +  LANG_ADDART(sheathed->short()) + " is " +
		(is_a_real_scabbard() ? "sheathed" : "secured") + " in it.\n") :
	    (" and it is empty.\n"));
}


void
switch_the_scabbard()
{
    object sheathed = TP->query_prop(CLUB_O_SHEATHED_WEAPON);
    if (sheathed)
    {
	sheathed->unset_no_show();
	sheathed->unset_no_show_composite();
	TP->remove_prop(CLUB_O_SHEATHED_WEAPON);
	write("You retrieve your " + sheathed->short() + " from your " +
	    my_type + ".\n");
    }
    if (my_type == "holster")
    {
	my_type = "scabbard";
	remove_name("holster");
	set_name("scabbard");
	add_prop(OBJ_M_NO_DROP, "You cannot drop your personal scabbard.\n");
	set_short(0);
	location = "side";
	TP->add_prop(CLUB_S_SCABBARD_LOCATION, location);
    }
    else
    {
	my_type = "holster";
	remove_name("scabbard");
	set_name("holster");
	add_prop(OBJ_M_NO_DROP, "You cannot drop your personal holster.\n");
	set_short(0);
	location = "back";
	TP->add_prop(CLUB_S_SCABBARD_LOCATION, location);
    }
}


int
is_a_real_scabbard()
{
    return (my_type == "scabbard");
}


string 
query_my_type()
{
    return my_type;
}

void
change_location(string where)
{
    location = where;
}

void
remove_from_club(object player)
{
    if (player->query_alignment() < 0)
	(CLUBMASTER)->expel_from_club(player);
}

public void
enter_env(object ob, object from)
{
    object otp;

    ::enter_env(ob, from);
    if (!interactive(ob) || from)
	return;
    
    ob->add_subloc("the_knights_club", TO);

    set_alarm(5.0, 0.0, &soul(ob));
    
    if (my_type == "holster")
    {
	otp = this_player();
	set_this_player(ob);
	switch_the_scabbard();
	switch_the_scabbard();
	set_this_player(otp);
    }

    if (ob->query_alignment() < 0)
	set_alarm(400.0, 0.0, &remove_from_club(ob));
    
    setuid();
    seteuid(getuid());
    CLUBMASTER->mark_supporter_login(ob);
}


/*
 * Function name: soul
 * Description:   Add the cmdsoul to the member
 */
void
soul(object ob)
{
    int i;
    string *souls;
    
    setuid();
    seteuid(getuid(TO));

    souls = ob->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
	ob->remove_cmdsoul(souls[i]);
    for (i = 0; i < sizeof(souls); i++)
	if (souls[i] != CLUB_SOUL)
	    ob->add_cmdsoul(souls[i]);
    ob->add_cmdsoul(CLUB_SOUL);
    ob->update_hooks();
}


string
show_subloc(string subloc, object me, object for_obj)
{
    string str, how;
    int value, myself;
    object sheathed = me->query_prop(CLUB_O_SHEATHED_WEAPON);

    if (!IS_CLUB_MEMBER(me))
	return "";
    
    if (!me->query_prop(CLUB_S_SCABBARD_LOCATION))
	me->add_prop(CLUB_S_SCABBARD_LOCATION, location);
    
    myself = (for_obj == me);
    str = capitalize(me->query_pronoun());
    
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return (myself ? ("You have your " + my_type + " strapped to your ") :
	    (str + " has " + POSSESSIVE(me) + " " + my_type +
		" strapped to " + POSSESSIVE(me) + " ")) + location +
	    (sheathed ? (" and " + LANG_ADDART(sheathed->short()) + 
		" is " + (is_a_real_scabbard() ? "sheathed" : "secured") +
		" in it.\n") : (" and it is empty.\n"));

    how = LANG_ADDART(CLUBMASTER->get_supporter_title(me));
    
    return (myself ? "You have your" : str + " has " + POSSESSIVE(me)) +
	" traditional ornamented " + my_type + " strapped to " +
	(myself ? "your" : POSSESSIVE(me)) + " " + location + ".\n" + 
	(myself ? "You are " : str + " is ") +
	how + "of the Prestigious Knights' Club.\n";
    
}

void
update_me()
{
    seteuid(getuid(TO));

    MASTER_OB(TO)->load_me();

    if (IS_CLONE)
	clone_object(MASTER_OB(TO))->move(E(TO));
    tell_object(E(TO),"Your traditional ornamented " + my_type +
	" was updated.\n");
    remove_object();
}

