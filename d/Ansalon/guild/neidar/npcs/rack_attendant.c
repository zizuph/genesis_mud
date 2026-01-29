#include "../guild.h"
#include <language.h>
#include <macros.h>
#include <std.h>

inherit "/d/Ansalon/estwilde/living/dwarf_guard";

string book;

public string
answer_questions()
{
    seteuid(getuid());
    
    object logbook, rack;
    
    if (!CAN_SEE(this_object(), this_player()))
        return "say Who said that?";
    
    if (!this_player()->query_guild_leader_occ() &&
        !SECURITY->query_wiz_level(this_player()->query_real_name()))
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

    // AK_DEBUG("Logbook cloning commencing");    
    logbook = clone_object(GUILD_OBJS + "rack/new_rack_logbook");
    // AK_DEBUG("Logbook cloned");
    logbook->set_rack(rack);
    // AK_DEBUG("Rack set");
    logbook->set_attendant(this_object());
    // AK_DEBUG("Attendant set");
    logbook->move(this_player(), 1);
    // AK_DEBUG("Logbook moved");
    
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
create_krynn_monster()
{
     ::create_krynn_monster();
    
    add_name("attendant");
    set_short(implode(query_adjs(), " ") + " attendant");
    set_long(this_object()->query_long() + capitalize(query_possessive())
    + " current assignment is attending to the racks. It may be possible to "
    + "inquire about the armoury from the attendant.\n");
    
    add_prop(OBJ_M_NO_ATTACK, "There are numerous dwarves in the vicinity, "
    + "attacking the attendant would be suicide.\n");
    
    add_ask(({ "armory", "armoury", "log", "logs", "rack", "racks" }),
    "@@answer_questions@@", 1);
}