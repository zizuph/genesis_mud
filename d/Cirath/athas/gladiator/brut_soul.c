#pragma save_binary
#pragma strict_types
 
inherit "/cmd/std/command_driver";
#include "defs.h"
#include <cmdparse.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"
 
#define MORE(x, y, z) CO("/std/board/board_more")->more(x, y, z)
#define HESHE (this_player()->query_pronoun())
#define HISHER (this_player()->query_possessive())
#define HIMHER (this_player()->query_objective())
string
get_soul_id()
{
    return "brutus";
}
 
int
query_cmd_soul()
{
    return 1;
}
 
/* **********************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 */
mapping
query_cmdlist()
{
   return ([
        /* ************** COMMANDS ************** */
                "gladtell"    : "gladtell",
                ]);
}
 void
create()
{
    seteuid(getuid());
}

int
gladtell(string str)
{
    object *glads;
    int i, busy;

    NF("Tell them what?\n");
    if (!strlen(str)) return 0;

    glads = filter(users(), "is_glad", this_object()) - ({this_player()});

    for (i = 0; i < sizeof(glads); i++)
    {
        if (IS_WIZ(glads[i]))
        {
            busy = glads[i]->query_prop("_wizard_busy_level");
            if (busy & (2 | 8 | 16 | 128)) continue;
        }

        glads[i]->catch_msg("\n"+
            "==== " + (CAP(TP->query_name())) + " tells all the Gladiators:\n"+
            "--------------------------------------------------"
            +"---------------------\n"+
     break_string(str, 70) + "\n");
    }

    if (this_player()->query_get_echo())
        write("\nYou tell the gladiators:  " + str + "\n\n");
    else write("Ok.\n");
    return 1;
}

int
is_glad(object ob)
{
    return IS_MEMBER(ob);
}

