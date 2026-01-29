#include "../local.h"
#include <language.h>
#include <macros.h>

inherit "/d/Ansalon/common/monster/kapak_base";

string book;

public string
answer_questions()
{
    seteuid(getuid());
    
    object logbook, rack;
    
    if (!CAN_SEE(this_object(), this_player()))
        return "say Who said that?";
    
    if (!this_player()->query_guild_leader_occ())
        return "say to " + OB_NAME(this_player()) + " You do not possess the "
        + "proper clearance to access the armoury logs.";
    
    rack = environment(this_object())->query_rack_object();
    
    if (!objectp(rack))
        return "say to " + OB_NAME(this_player()) + " I have yet to receive an "
        + "assignment of which rack to attend. You may contact the current "
        + "guild master to have this matter solved.";
    
    if (strlen(book) && objectp(logbook = find_object(book)))
    {
        if (environment(logbook) != this_player())
            return "say to " + OB_NAME(this_player()) + " Someone has already "
            + "retrieved the logbook, you will have to wait your turn.";
        else
            return "say to " + OB_NAME(this_player()) + " You already possess "
            + "the logbook.";
    }
    
    logbook = clone_object(SOBJ + "rack/new_rack_logbook");
    logbook->set_rack(rack);
    logbook->set_attendant(this_object());
    logbook->move(this_player(), 1);
    
    book = file_name(logbook);
    
    this_player()->catch_msg(QCTNAME(this_object()) + " gives you "
    + LANG_ADDART(logbook->short()) + ".\n");
    this_object()->tell_watcher(QCTNAME(this_object()) + " gives "
    + QTNAME(this_player()) + " " + LANG_ADDART(logbook->short()) + ".\n",
    ({ this_player() }));
    return "say to " + OB_NAME(this_player()) + " This should contain the "
    + "information you have requested.";
}

void
create_kapak()
{
    set_color("red");
    
    add_name("attendant");
    set_adj(({"meanfaced"}));
    set_short("meanfaced draconian attendant");
    set_long("A draconian is a scaly humanoid, and this one is flicking a "
    + "forked tongue from its fang-studded mouth. It's as tall as a man, and "
    + "it walks on powerful hindlegs. Each leg bears a talon. Rounding out "
    + "the monstrosity are its other noticeable features: studded forepaws, "
    + "reptilian eyes, and a baleful glare. This one has a mean reptilian "
    + "face, which looks sly and cunning. It has leathery wings that stretches "
    + "awkwardly from the shoulders. " +  capitalize(query_possessive())
    + " current assignment is attending to the racks. It may be possible to "
    + "inquire about the armoury from the attendant.\n");
    
    add_prop(OBJ_M_NO_ATTACK, "There are guards all around you, attacking the "
    + "attendant would be suicide.\n");
    
    add_ask(({ "armory", "armoury", "log", "logs", "rack", "racks" }),
    "@@answer_questions@@", 1);
}

/*
 * Function name: help_friend
 * Description:   Help my friend
 * Arguments:     attacker - The attacker
 */
void
assist_friend(object friend, object attacker)
{
    /* Dont help friends */
}