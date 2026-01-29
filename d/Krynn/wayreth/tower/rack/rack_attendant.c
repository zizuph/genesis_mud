#include "/d/Krynn/guilds/wohs/defs.h"
#include "/d/Krynn/common/defs.h"
#include <language.h>
#include <macros.h>

inherit "/d/Krynn/wayreth/npc/aide2";

#define LOGBOOK  "/d/Krynn/wayreth/tower/rack/rack_logbook"

string book;

public string
answer_questions()
{
    seteuid(getuid());
    
    object logbook, rack;
    
    if (!CAN_SEE(this_object(), this_player()))
        return "say Who said that?";
    
    if (!QUERY_IS_COUNCIL(TP) && !QUERY_IS_ARCHMAGE(TP) &&
        !TP->query_wiz_level())
        return "say to " + OB_NAME(this_player()) + " I am only " +
            "permitted to give the armoury logs to members of the " +
            "Conclave or Archmages.";
    
    rack = environment(this_object())->query_rack_object();
    
    if (!objectp(rack))
        return "say to " + OB_NAME(this_player()) + " I have yet to "
        + "receive an assignment of which rack to attend. You may contact "
        + "the current guild master to have this matter solved.";
    
    if (strlen(book) && objectp(logbook = find_object(book)))
    {
        if (environment(logbook) != this_player())
            return "say to " + OB_NAME(this_player()) + " Someone has "
            + "already retrieved the logbook, you will have to wait "
            + "your turn.";
        else
            return "say to " + OB_NAME(this_player()) + " You already "
            + "possess the logbook.";
    }
    
    logbook = clone_object(LOGBOOK);
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
create_krynn_monster()
{
     ::create_krynn_monster();
    
    add_name("attendant");
    set_short(implode(query_adjs(), " ") + " attendant");
    set_long(this_object()->query_long() + capitalize(query_possessive())
    + " current assignment is attending to the racks. It may be possible to "
    + "inquire about the armoury from the attendant.\n");
    
    add_prop(OBJ_M_NO_ATTACK, "The aid is ethereal, and cannot be " +
        "attacked.\n");
    
    add_ask(({ "armory", "armoury", "log", "logs", "rack", "racks" }),
    "@@answer_questions@@", 1);
}