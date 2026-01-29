#include <macros.h>
#include <stdproperties.h>
#include "../knight/guild.h"

inherit IN_BASE;

mapping lords = ([ ]);
mapping colour = ([ ]);
mapping crest = ([ ]);
mapping members = ([ ]);
object guard;

create_vin_room()
{
    set_short("Room of Heraldry");
    set_long("This room is covered with tapestries and banners of "+
      "all sorts. On the tapestries, lineages of Knights are "+
      "painted, and the banners are decorated with the distinct "+
      "crests of the Solamnian houses. The largest and most "+
      "ornate banner is decorated in gold and black. In the "+
      "center of the room is a desk, atop which rests a great "+
      "book. There is also a knight standing behind "+
      "a counter here.\n");
    clone_object(VNPC + "gunthar_guard")->move(TO);
    add_item("desk", "A desk sits in the center of the room "+
      "with a large book upon it.\n");
    add_cmd_item("book", "read", "@@book_desc");
    add_item("counter", "The counter has a plaque on it which "+
      "reads: House capes available here to those who are "+
      "elidgible. Just 'order cape' and the attendant will "+
      "help you.\n");
    add_item(({"banners", "tapestries", "banner", "tapestry"}),
      "The lineages of the houses of Solamnia are painted on the "+
      "tapestries, and the banners portray various crests.\n");
    add_item(({"large banner", "largest banner", "ornate banner"}),
      "You see that this is the traditional banner of the house "+
      "of Solamnus, the descendants of the great Vinas Solamnus.\n");
    add_item("book", "@@book_desc");
    add_exit(VLIB+"library", "south");
    seteuid(getuid(TO));
}

init()
{
    ::init();

    add_action("banish_family", "banish");
    add_action("get_cloak", "order");
    add_action("set_crest", "describe"); //
    add_action("set_family", "declare"); //
    add_action("add_member", "add"); //
    add_action("remove_member", "remove"); //
    add_action("erase_family", "erase"); //
    add_action("appoint_new_lord", "appoint");
    add_action("renounce_family", "renounce"); //
    add_action("list_members", "list");
    add_action("set_colour", "colour"); //
}


string
book_desc()
{
    return "The book is the most current volume of the Solamnian "+
    "Heraldry.\n\n"+
    "Lord Knights may:\n"+
    " - <declare> a house\n"+
    " - <describe> its crest\n"+
    " - set its <colour>\n"+
    "House Lords may:\n"+
    " - <add>/<remove> new members\n"+
    " - <appoint> a new house lord\n"+
    " - <erase> your house\n"+
    "Members of a house may:\n"+
    " - <renounce> their house\n"+
    " - <order> a house cape\n"+
    "All may:\n"+
    " - <list> the houses, or information on a certain house\n"+
    "Conclave Members may:\n"+
    " - <banish> a house\n";
}

/* get a house cloak */
int
get_cloak(string str)
{
    object cloak;
    string fam;

    NF("Order what? A cape?\n");
    if (!str || str != "cape")
	return 0;

    restore_object(CREST);

    NF("The Knight tells you that there is no record of "+
      "your lineage.\n");
    if (member_array(TP->query_name(), m_indexes(members)) < 0)
	return 0;

    NF("The knight remembers that you already got a cape "+
      "and refuses to give you another.\n");
    if (TP->query_prop("_i_got_a_crested_cloak_already"))
	return 0;

    fam = members[TP->query_name()];
    NF("Your house must have a crest and colour defined first.\n");
    if (!crest[fam] || !colour[fam])
	return 0;

    cloak = clone_object(VARM + "crest_cloak");
    cloak->set_crest(crest[fam]);
    cloak->set_colour(colour[fam]);
    cloak->move(TP);
    TP->add_prop("_i_got_a_crested_cloak_already", 1);
    write("The knight goes into the back room and returns "+
      "with a "+cloak->short()+", which you take graciously.\n");
    say("The knight goes into the back room and returns "+
      "with a "+cloak->short()+", which "+QTNAME(TP)+" takes "+
      "graciously.\n");
    return 1;
}


/* Remove a member from a house */
int
remove_member(string str)
{
    string fam, name;

    NF("Remove whom?\n");
    if (!str)
	return 0;

    restore_object(CREST);
    fam = members[TP->query_name()];

    NF("Only the house lord may remove new members.\n");
    if (lords[fam] != TP->query_name())
	return 0;

    NF(C(str)+" is not a member of your house.\n");
    if (member_array(C(str), m_indexes(members)) < 0 ||
      members[C(str)] != fam)
	return 0;
    members = m_delete(members, C(str));
    write("You remove "+C(str)+" from house "+fam+".\n");
    say(QCTNAME(TP)+" erases a name from the book on the desk.\n");
    find_living(L(str))->catch_msg("You are no longer a member of "+
      "house "+fam+".\n");
    save_object(CREST);
    return 1;
}


/* Add a member to a house */
int
add_member(string str)
{
    string fam;

    NF("Add whom?\n");
    if (!str)
	return 0;

    NF("No one by the name "+str+" is present.\n");
    if (!find_living(L(str)) || !P(L(str), E(TP)))
	return 0;

    restore_object(CREST);
    fam = members[TP->query_name()];

    NF("Only the house lord may add new members.\n");
    if (lords[fam] != TP->query_name())
	return 0;

    NF(C(str)+" is a member of another house already.\n");
    if (member_array(C(str), m_indexes(members)) >= 0)
	return 0;

    members[C(str)] = fam;
    write("You add "+C(str)+" to house "+fam+".\n");
    say(QCTNAME(TP)+" adds a name to the book on the desk.\n");
    find_living(L(str))->catch_msg("You are now a member of "+
      "house "+fam+".\n");
    save_object(CREST);
    return 1;
}


/* Leave a house */
int
renounce_family(string str)
{
    string name;

    NF("Renounce what? Your house?\n");
    if (!str)
	return 0;

    if (str != "house" && str != "House")
	return 0;

    restore_object(CREST);
    NF("A house lord may not renounce his house, he may either "+
      "erase it, or appoint a new lord.\n");
    if (member_array(TP->query_name(), m_values(lords)) >= 0)
	return 0;

    name = TP->query_name();
    members = m_delete(members, name);
    save_object(CREST);
    write("You renounce your house.\n");
    say(QCTNAME(TP)+" erases a name from the book on the desk.\n");
    return 1;
}


/* Create a new house */
int
set_family(string str)
{
    NF("Declare your house name as what?\n");
    if (!str)
	return 0;
NF("You are not a Knight of Solamnia.\n");
if (!MEMBER(TP))
return 0;

    NF("You are not a Lord Knight as of yet, and cannot have a "+
      "house of your own!\n");
    if (TP->query_knight_level() == 2 ||
      TP->query_knight_level() == 3 &&
      TP->query_knight_sublevel() < 7)
	return 0;

    restore_object(CREST);

    NF("You are already Lord of a House, you must 'erase' your "+
      "house before you can begin a new one.\n");
    if (member_array(TP->query_name(), m_values(lords)) >= 0)
	return 0;

    NF("You are already a member of House "+members[TP->query_name()]+
      ".\n");
    if (member_array(TP->query_name(), m_indexes(members)) >= 0)
	return 0;

    lords[str] = TP->query_name();
    members[TP->query_name()] = str;
    crest[str] = 0;
    save_object(CREST);
    write("You have created your own house, "+str+". Remember to "+
      "describe your house crest.\n");
    say(QCTNAME(TP)+" fills in the title of a blank page in the "+
      "great book.\n");
    return 1;
}


/* Set crest of your house */
int
set_crest(string str)
{
    string fam;

    restore_object(CREST);
    fam = members[TP->query_name()];

    NF("You are not the lord of the house, and cannot set the crest.\n");
    if (lords[fam] != TP->query_name())
	return 0;

    crest[fam] = str;
    write("You set the crest of your house as: "+str+".\n");
    say(QCTNAME(TP)+" fills in a line on a page in the book.\n");
    save_object(CREST);
    return 1;
}


/* Set colour of your house */
int
set_colour(string str)
{
    string fam;

    restore_object(CREST);
    fam = members[TP->query_name()];

    NF("You are not the lord of the house, and cannot set the house "+
      "colours.\n");
    if (lords[fam] != TP->query_name())
	return 0;

    colour[fam] = str;
    write("You set the colour of your house to: "+str+".\n");
    say(QCTNAME(TP)+" fills in a line on a page in the book.\n");
    save_object(CREST);
    return 1;
}


/* Conclave function to banish an inappropriate family */
int
banish_family(string str)
{
    string *ind, fam;
    int i, sz;

    NF("On whose authority would you banish a house? Not yours!\n");
    if (TP->query_knight_sublevel() != 11 &&
      member_array(TP->query_name(), GUILDMASTERS) < 0)
	return 0;

    NF("Banish which family?\n");
    if (!str)
	return 0;

    restore_object(CREST);
    if (member_array(str, m_indexes(crest)) >= 0)
	fam = str;

    NF("No such family to banish.\n");
    if (!fam)
	return 0;

    lords = m_delete(lords, fam);
    crest = m_delete(crest, fam);
    colour = m_delete(colour, fam);

    ind = m_indexes(members);
    sz = sizeof(ind);
    for (i = 0; i < sz; i++)
    {
	if (members[ind[i]] == fam)
	    members = m_delete(members,ind[i]);
    }

    write("You erase house "+fam+", tearing the page out of the book.\n");
    say(QCTNAME(TP)+" tears a page from the book on the desk.\n");
    save_object(CREST);
    return 1;
}


/* Erase a family and all existing members and crests */
erase_family(string str)
{
    string fam, *ind;
    int i, sz;

    NF("Erase what? Your family?\n");
    if (!str)
	return 0;

    if (str != "family" && str != "Family")
	return 0;

    restore_object(CREST);
    fam = members[TP->query_name()];

    NF("Only the lord may erase the house.\n");
    if (lords[fam] != TP->query_name())
	return 0;

    lords = m_delete(lords, fam);
    crest = m_delete(crest, fam);
    colour = m_delete(colour, fam);

    ind = m_indexes(members);
    sz = sizeof(ind);
    for (i = 0; i < sz; i++)
    {
	if (members[ind[i]] == fam)
	    members = m_delete(members,ind[i]);
    }

    write("You erase your house, tearing the page out of the book.\n");
    say(QCTNAME(TP)+" tears a page from the book on the desk.\n");
    save_object(CREST);
    return 1;
}


/* Appoint a new house lord */
appoint_new_lord(string str)
{
    string fam;

    NF("Appoint whom?\n");
    if (!str)
	return 0;

    NF("No one by the name "+str+" is present.\n");
    if (!find_living(L(str)) || !P(L(str), E(TP)))
	return 0;

    restore_object(CREST);
    fam = members[TP->query_name()];

    NF("Only the house lord may appoint a new house lord.\n");
    if (lords[fam] != TP->query_name())
	return 0;

    NF("That person is not even a member of house "+fam+"!\n");
    if (members[C(str)] != fam)
	return 0;

    NF(C(str)+" is not a lord level Knight, and cannot serve "+
      "as lord of a house.\n");
    if (find_living(str)->query_knight_level() < 3 ||
      (find_living(str)->query_knight_level() == 3 &&
	find_living(str)->query_knight_sublevel() < 7))
	return 0;

    lords[fam] = C(str);

    write("You appoint "+C(str)+" as the new house lord.\n");
    say(QCTNAME(TP)+" erases a name, and fills it in with a new "+
      "one.\n");
    find_living(L(str))->catch_msg("You are now lord of "+
      "house "+fam+".\n");
    save_object(CREST);
    return 1;
}


/* list members of a house */
list_members(string str)
{
    string fam, *ind, *list = ({ });
    int sz,i;

    restore_object(CREST);

    if (!str)
	fam = members[TP->query_name()];
    else
	fam = str;

    if (!fam)
	str = "houses";

    if (str == "houses")
    {
	write("Current Houses of Solamnia:\n");
	ind = m_indexes(crest);
	ind = sort_array(ind);
	for (i = 0; i < sizeof(ind); i++)
	    write(" - "+ind[i]+"\n");
	return 1;
    }

    if (member_array(C(fam), m_values(members)) >= 0)
	fam = C(fam);

    NF("There is no such house.\n");
    if (member_array(fam, m_values(members)) < 0)
	return 0;

    ind = m_indexes(members);
    sz = sizeof(ind);
    for (i = 0; i < sz; i++)
    {
	if (members[ind[i]] == fam)
	    list += ({ ind[i] });
    }

    say(QCTNAME(TP)+" glances at a page in the book.\n");
    write(" -=> House "+fam+" <=-\n");
    write("Lord: "+lords[fam]+"\n");
    write("House crest: "+crest[fam]+"\n");
    write("House colour: "+colour[fam]+"\n");
    list -= ({ lords[fam] });
    list = sort_array(list);
    if (!sizeof(list))
	write("No current members.\n");
    else
	write("Current members:\n");
    for (i = 0; i < sizeof(list); i++)
	write("  "+list[i]+"\n");

    return 1;
}


