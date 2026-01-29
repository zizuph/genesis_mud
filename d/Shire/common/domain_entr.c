/*  The old domain_entr re-vamped by Igneous */

#pragma strict_types;

inherit "/d/Shire/room";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/private/shire_admin.h"
#include <std.h>

#define READ_FILE(x)  this_player()->more(read_file(x,1))

//  Prototypes
string shire_wizzes();
string get_domain_lord();
int do_info(string str);

void
create_room()
{
    set_short("Shire-domain entrance");
    set_long(
      "   ______________________________________________\n"+
      "   |                    _           /\\          |\n"+
      "   |          `/\\      / \\__       /  \\    /\\   |\n"+
      "   |      /\\  /: \\__  /     \\__  _/    \\  /  \\  |\n"+   
      "   |    _/  \\/  :   \\/         \\/       \\/    \\ |\n"+
      "   |  _/    /    :  /          /               \\|\n"+
      "   | /     /    _n_           /                 |\n"+
      "   |/          /___\\         /                  |\n"+
      "   |           |# #|                            |\n"+
      "   ::::::::::::::::::::::::::::::::::::::::::::::\n"+
      "    :::::      Welcome to the Shire!      :::::\n"+
      "       ::::::::::::::::::::::::::::::::::::::\n"+
      "\n"+
      "This is the domain entrance of the Shire domain.\n"+
      capitalize(get_domain_lord())+
      " is the Liege of this area.\nOther wizards of the Shire are "+
      shire_wizzes()+
      "\nType 'info' for information about our domain. "+
      "North you can discover more about the Shire domain."+
      " To the south is the Tower of Domains.\n");
    add_exit("/d/Shire/workroom","north");
    add_exit("/d/Genesis/wiz/dom_a1", "south");
}

void
init()
{
    ::init();
    add_action(do_info,"info");
}

int
do_info(string str)
{
    setuid(); seteuid(getuid());
    if (!str)
    {
	notify_fail("Type 'info Shire' to get the domain info or 'info "+
	  "<Shire Wizard name> to find out more about a Shire Wizard.\n");
	return 0;
    }
    str = lower_case(str);
    if (str == "shire")
    {
	READ_FILE("/d/Shire/open/finger_info");
	return 1;
    }

    if (member_array(str,SECURITY->query_domain_members("Shire")) != -1)
    {
	if (file_size("/d/Shire/"+str+"/info") == -1)
	    write(CAP(str)+" doesn't have any info available.\n");
	else
	    READ_FILE("/d/Shire/"+str+"/info");
	return 1;
    }
    notify_fail("Type 'info Shire' to get the domain info or 'info "+
      "<Shire Wizard name> to find out more about a Shire Wizard.\n");
    return 0;
}

string
get_domain_lord()
{
    return SECURITY->query_domain_lord("Shire");
}

string
shire_wizzes()
{
    int sm, s, i, max, nmem;
    string *warr, lord, result;

    warr = SECURITY->query_domain_members("Shire");
    if (!(sm = sizeof(warr)))
	return 0;

    /* Forget about the lord */
    lord = SECURITY->query_domain_lord("Shire");
    if ((i = member_array(lord, warr)) >= 0)
	warr = map(exclude_array(warr, i, i), "cap_map", this_object());

    if ((s = sizeof(warr)) > 0)
    {
	if (s == 1)  /* One other member */
	    result = warr[0] + ". ";
	else  /* Several other members */
	    result = implode(warr[0..(s-2)], ", ") + " and " +  warr[s-1] + ". ";
    }
    else
	result = "not available. ";

    nmem = SECURITY->query_domain_max("Shire") - sm;
    /* Calculate the number of members that still can join */
    if (nmem == 1)
	result += "The Shire domain has one vacancy. ";
    else
	result += "The Shire domain has " + ((nmem > 0) ? ("" + nmem) : "no")
	+ " vacancies. ";
    return result;
}

string
cap_map(string str)
{
    if (str)
	return capitalize(str);
}

void
enter_inv(object ob,object from)
{
    object lord;

    ::enter_inv(ob,from);
    if (!interactive(ob))
	return;
    ob->catch_msg("Horns announce your arrival in the Shire.\n");
    say("Horns sound at "+QCTNAME(ob)+"'s arrival in the Shire.\n");
    TELL_LIEGE(ob->query_cap_name() +" is visiting the Shire's Domain Entrance.");
}
