#include "../../local.h"
#include <language.h>
#include <macros.h>

inherit NPCSTD + "vin_knight_base";

object gLogbook, gRackItem;

public string
answer_questions()
{
    setuid();
    seteuid(getuid());
    
    if (!CAN_SEE(this_object(), this_player()))
        return "say Who said that?";
    
    if (!this_player()->query_guild_leader_occ() &&
        !this_player()->query_wiz_level())
        return "say to " + OB_NAME(this_player()) + " You are not a member of "
        + "the conclave and thus do not possess the proper clearance to access "
        + "the armoury logs.";
    
    if (objectp(environment()) && !objectp(gRackItem))
        gRackItem = environment()->query_rack_object();
    
    if (!objectp(gRackItem))
        return "say to " + OB_NAME(this_player()) + " I have yet to receive an "
        + "assignment of which rack to attend. You may contact the current "
        + "guild master to have this matter solved.";
    
    if (objectp(gLogbook))
    {
        if (environment(gLogbook) != this_player())
            return "say to " + OB_NAME(this_player()) + " Someone has already "
            + "retrieved the logbook, you will have to wait your turn.";
        else
            return "say to " + OB_NAME(this_player()) + " You already possess "
            + "the logbook.";
    }
    
    gLogbook = clone_object(VOBJ + "new_rack_logbook");
    gLogbook->set_rack(gRackItem);
    gLogbook->set_attendant(this_object());
    gLogbook->move(this_player(), 1);
    
    this_player()->catch_msg(QCTNAME(this_object()) + " gives you "
    + LANG_ADDART(gLogbook->short()) + ".\n");
    this_object()->tell_watcher(QCTNAME(this_object()) + " gives "
    + QTNAME(this_player()) + " " + LANG_ADDART(gLogbook->short()) + ".\n",
    ({ this_player() }));
    return "say to " + OB_NAME(this_player()) + " This should contain the "
    + "information you have requested.";
}

void
create_knight_npc()
{
    set_level(3);
    
    string *adjs  = query_adjs();
    int     level = query_level();
    
    if (!sizeof(adjs))
        return;
    
    add_name("attendant");
    set_short(implode(adjs, " ") + " attendant");
    set_long("This is " + LANG_ADDART(adjs[0]) + " " + adjs[1] + " "
    + (query_gender() ? (query_gender() > 1 ? "neuter" : "female") : "male")
    + " " + query_race() + " serving as a guard for the Knights of Solamnia. "
    + capitalize(query_possessive()) + " current assignment is attending to "
    + "the racks. It may be possible to inquire about the armoury from the "
    + "attendant.\n" + capitalize(query_possessive()) + " tunic is decorated "
    + "with the symbol of the " + (level < 4 ? "Order of the Crown" :
    (level > 4 ? "Order of the Rose" : "Order of the Sword")) + ".\n");
    
    add_prop(OBJ_M_NO_ATTACK, "There are guards all around you, attacking this "
    + "knight would be suicide.\n");
    
    add_ask(({ "armory", "armoury", "log", "logs", "rack", "racks" }),
    "@@answer_questions@@", 1);
}