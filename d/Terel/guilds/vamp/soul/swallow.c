
#include "../guild.h"
#include <filter_funs.h>
#include <macros.h>
#include <std.h>

inherit "/lib/commands";

public int filter_diamond(object ob)
{
    if (ob->query_name()=="diamond")
    {
        return 1;
    }
    return 0;
}

int
swallow(string arg)
{
    if (!arg)
    {
        return 0;
    }
    object * diamonds=filter(deep_inventory(TP), &filter_diamond());
    
    object diamond;
    if (!parse_command(arg,diamonds,"%o",diamond))
    {
        return 0;
    }

    write("You take the "+diamond->singular_short()+" and swallow it, taking "+
    "it inside you to wield its focal energies.\n");
    
    allbb(" swallows "+LANG_ADDART(diamond->singular_short())+".");
    
    if (diamond->num_heap()>1)
    {
        diamond->set_heap_size(diamond->num_heap()-1);
    }
    else
    {
        diamond->remove_object();
    }
    setuid();
    seteuid(getuid());
    clone_object(OBJ_DIR+"swallowed_diamond")->move(TP,1);
    return 1;
    
}

