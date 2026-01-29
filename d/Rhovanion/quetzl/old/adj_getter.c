#pragma strict_types
#pragma no_clone
#pragma no_inherit

inherit "/std/object";

#define ATTRIBS "/d/Genesis/login/attributes"

public mixed *attrib;
static string *caters;

public void
create_object()
{
    int i;
    caters = ({});
    reset_euid();
    restore_object(ATTRIBS);
    i = sizeof(attrib);
    while(i--)
         caters = ({ attrib[i][0] }) + caters;
}

public string
check_atts()
{
    return implode(caters, " ");
}

public string
get_adj(string which)
{
    string *stuff, *adjlist = ({});
    int i;
    if (which == "ALL")
        which = check_atts();
    stuff = explode(which, " ");
    i = sizeof(stuff);
    while(i--)
        if (member_array(stuff[i], caters) != -1)
            adjlist += attrib[member_array(stuff[i], caters)][2];
    if (!sizeof(adjlist))
        return "";
    i = random(sizeof(adjlist));
    return adjlist[i];
}
