/*
 * file name:  /d/Avenir/registry/proof.c
 * creator(s): Gwyneth, Dec 2003
 * updates:    
 *             Lilith,  3 May 2004 - Corrected subloc when leaving inv.
 *             Gwyneth, 2 Apr 2004 - Added sublocs
 *             Lilith, 27 Feb 2004 - Add_items
 *             Lilith, 24 Feb 2004 - Item description
 *             Mercade,23 Feb 2004 - Added init_arg() 
 * purpose:    Provides proof of relationship/claim registration.      
 * note:       Brainchild of Savannah, catalyzed by Cuthalion.
 * bug(s):
 * to-do:     
 */

inherit "/std/object";

#include "/d/Avenir/common/common.h"
#include "relate.h"

#include <stdproperties.h>

/* You + subloc */
string gSubloc1 = "";
/* He/she + subloc */
string gSubloc2 = "";
string gOwner = "";

/*
 * Function name: relate_desc
 * Description  : Gives a description of the claims/relationships
 *                of the player.
 * Arguments    : string name - Use the met-name, unmet-name or "You"
 * Returns      : string - the description
 */
public string
relate_desc(string name)
{
    int i, j, k;
    mapping clamap, relmap;
    string pronoun, tmp, text = "", *claims, *relates, *cats, *names;

//    pronoun = environment(this_object())->query_pronoun();
//    pronoun = this_player()->query_pronoun();
    pronoun = find_player(lower_case(name))->query_pronoun();

    gSubloc1 = "";
    gSubloc2 = "";

    relmap = RELATE->query_relate_map(name);
    cats = m_indexes(relmap);
    for (i = sizeof(cats) - 1; i >= 0; i--)
    {
        relates = m_indexes(relmap[cats[i]]);
        for (j = sizeof(relates) - 1; j >= 0; j--)
        {
            names = relmap[cats[i]][relates[j]];
            for (k = sizeof(names) - 1; k >= 0; k--)
            {
                tmp = (" the " + relates[j] + " of " + names[k] +
                    ".\n");
                text += (name + " is" + tmp);
                gSubloc1 += ("You are" + tmp);
                gSubloc2 += (CAP(pronoun) + " is" + tmp);
            }
        }
    }

    clamap = RELATE->query_claim_map(name);
    cats = m_indexes(clamap);
    for (i = sizeof(cats) - 1; i >= 0; i--)
    {
        claims = m_indexes(clamap[cats[i]]);
        for (j = sizeof(claims) - 1; j >= 0; j--)
        {
            names = clamap[cats[i]][claims[j]];
            for (k = sizeof(names) - 1; k >= 0; k--)
            {
                tmp = (" to be the " + claims[j] + " of " +
                    names[k] + ".\n");
                text += (name + " claims" + tmp);
                gSubloc1 += ("You claim" + tmp);
                gSubloc2 += (CAP(pronoun) + " claims" + tmp);
            }
        }
    }

    /* For some reason or another, they have no claims or relates. */
    if (!strlen(text))
        set_alarm(1.0, 0.0, &remove_object());
    
    return text;
}

/*
 * Function name: update_list
 * Description  : Updates the text displayed on the paper when a
 *                change is made, or upon logging in.
 * Arguments    : string name - optional name.
 */
varargs void
update_list(string name = 0)
{
    string text;

    /* If we don't have a name, then find out. */
    if (!strlen(name))
    {
        name = environment(this_object())->query_real_name();
    }

    name = CAP(name);

    /* Basic security measure to prevent a wrong subloc. */
    if (strlen(gOwner) && gOwner != name)
        return;

    if (!strlen(gOwner))
        gOwner = name;

    text = "A piece of vellum embossed with the Sybarun trefoil "+
        "and stamped with a gold-leaf seal. Across the top, it "+
        "reads: The relationships below are recognized by the "+
        "Registry of Cynrede.\n\n";

    text += relate_desc(name);

    set_long(text +"\nThere is some fine print at the bottom.\n");
}

/*
 * Function name: do_trefoil
 * Description  : allows players to look at the trefoil
 * Returns      : the text file with ascii trefoil
 */
string
do_trefoil()
{
    string text = read_file("/d/Avenir/doc/trefoil");
    this_player()->more(text);
    return "";
}

void
create_object()
{
    reset_euid();

    set_name(({ "paper", "piece", "proof", "vellum", PROOF_ID }));
    set_adj(({"embossed"}));
    set_short("piece of embossed vellum");

    add_item(({"trefoil", "sybarun trefoil", "emboss", "embossing" }),
        &do_trefoil());
    add_item(({"seal", "gold-leaf seal", "stamp"}), 
        "This is a beautiful gold-leaf seal stamped with the image "+
        "of a stern-looking elf. It has been affixed to the vellum "+
        "as proof that all listed relationships have been duly "+
        "registered.\n");
    add_item(({"print", "fine print" }),
        "You have the option to display your Cynredes for all the "+
        "world to see, using <cynrede [display] on/off>.\n");
    add_cmd_item(({"print", "fine print" }), "read",
        "You have the option to display your Cynredes for all the "+
        "world to see, using <cynrede [display] on/off>.\n");

    add_prop(OBJ_M_NO_BUY,   1);
    add_prop(OBJ_M_NO_SELL,  1);
    add_prop(OBJ_M_NO_DROP,  1);
    add_prop(OBJ_M_NO_GIVE,  1);
    add_prop(OBJ_M_NO_STEAL, 1);
}

public int
toggle_subloc(string str)
{
    object ob = environment();
    string toggle, name;

    name = CAP(this_player()->query_real_name());

    if (strlen(gOwner) && gOwner != name)
    {
        notify_fail("You cannot display someone else's Cynredes.\n");
        return 0;
    }

    if (!present(this_object(), this_player()))
    {
        notify_fail("You cannot do that, as you do not have the proof in hand.\n");
        return 0;
    }

    if (!strlen(str) || !parse_command(str, ({}), "[display] %w", toggle))
    {
        notify_fail("Cynrede [display] <on/off>?\n");
        return 0;
    }

    toggle = lower_case(toggle);

    switch(toggle)
    {
    case "on":
        if (!TP->query_subloc_obj(CYNREDE_SUBLOC))
        {
            ob->add_subloc(CYNREDE_SUBLOC, this_object());
            write("You are now displaying your Cynredes.\n");
        }
        else
            write("You continue your Cynrede display.\n");
        break;

    case "off":
        if (TP->query_subloc_obj(CYNREDE_SUBLOC))
        {
            ob->remove_subloc(CYNREDE_SUBLOC, this_object());
            write("You are now concealing your Cynredes.\n");
        }
        else
            write("You continue to hide your Cynrede display.\n");
        break;

    default:
        notify_fail("Cynrede [display] <on/off>?\n");
        return 0;
    }

    return 1;
}

public void
init()
{
    ::init();
    add_action(toggle_subloc, "cynrede");
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string name;

    if (present(on))
        name = on->query_The_name(for_obj);

    if (subloc == CYNREDE_SUBLOC)
    {
        if (for_obj != on)
            return gSubloc2;
        else
            return gSubloc1;
    }

    return 0;
}

void
leave_env(object from, object to)
{
    if (from->query_subloc_obj(CYNREDE_SUBLOC))
        from->remove_subloc(CYNREDE_SUBLOC, this_object());

    ::leave_env(from, to);
}

/* Function name : query_recover
 * Description   : mask query_recover() to prevent duplication of
 *                 autoloading items
 * Returns       : 0
 */
public string
query_recover()
{
    return 0;
}

private void
slow_init()
{
    object me = environment();

    if (!me->query_subloc_obj(CYNREDE_SUBLOC))
    {
	me->add_subloc(CYNREDE_SUBLOC, this_object());
	tell_object(me, "You are now displaying your Cynredes.\n");
    }
}

/*
 * Function name: init_arg
 * Description  : 
 */
void
init_arg(string arg)
{
    string dummy;

    update_list(this_player()->query_real_name());
    if (sscanf(arg, "#CYNREDE#%s", dummy) && (dummy == "on"))
	set_alarm(1.0, 0.0, slow_init);
}

/* Function name : query_auto_load
 * Description   : Make the item autoloading.
 * Returns       : The file
 */
public string
query_auto_load()
{
    /* The colon is required to force a call to init_arg() */
    return MASTER + ":#CYNREDE#" +
	(TP->query_subloc_obj(CYNREDE_SUBLOC) ? "on" : "off");
}
