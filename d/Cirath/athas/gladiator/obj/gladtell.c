/* gladtell: Gladiator teller item. 
 *     Rebuilt my Serpine: 4/29/95.
 */


inherit "/std/object";
#include "defs.h"

void
create_object()
{
    if (!IS_CLONE) return;
    set_name("bullhorn");
     add_name("horn");
    add_adj("massive");
    add_adj("ugly");
    add_prop(OBJ_M_NO_DROP, 1);
    set_long("This fat, twisted object is made from the horn of a "+
             "Nightmare Beast, one of the ugliest and deadliest beasts "+
             "of Athas. It allows one to speak into it and instantly "+
             "communicate with all the Gladiators of Athas. They may "+
             "then reply.\nTo use it, just type 'gladtell <message>'.\n");
}

int
query_recover()
{
    return 0;
}

string
query_auto_load() { return MASTER + ":"; }

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if(!IS_WIZ(env))
       remove_object();
}

init()
{
  ::init();
  add_action("gladtell", "gladtell");
}

int
gladtell(string str)
{
    object *glads;
    int i, busy;

    NF("Guess again chummer. Only wizards may gladtell.\n");
    if (!IS_WIZ(TP)) return 0;

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
            "-----------------------------------------------------------------------\n"+
            break_string(str, 70) + "\n" +
            "=======================================================================\n"+
            "======== Use 'reply <message>' to respond to this if you wish. ========\n"+
            "=======================================================================\n\n");
        glads[i]->add_prop("_reply_wizard", this_player()->query_real_name());
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
