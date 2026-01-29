/* 
  Goblin Nose Ring, made for the Goblin Start Area by Quis 920824 
*/

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>

#include "../goblins.h"

#define GOBLIN_SOUL GOBLIN_GUILD_DIR + "goblin_soul"

void load_soul();

query_auto_load()
{
    return MASTER;
}

void
init_arg(string arg)
{
}

void
create_object()
{
    set_name("ring");
    set_adj("brass");
    set_adj("nose");
    set_long("The nose ring pierces your nose.  Removing it would be painful.\n");
    set_short("Goblin nose ring");
    
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 6);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
}

init()
{
    ::init();
    load_soul();
    add_prop(OBJ_M_NO_DROP, "Ouch! That is too painful!\n");
}

wizinfo()
{
    return(BSNN("The Goblin nose ring is to provide powers that " + 
      "the soul cannot.  It also handles loading the goblin soul."));
}

/* 
 * Function : load_soul
 * Description : unload all other souls, and place ours ahead of theirs.
 */

void
load_soul()
{
    int i;
    string *list;
    
    list = this_player()->query_cmdsoul_list();

    this_player()->add_cmdsoul(GOBLIN_SOUL);

    for (i = 0; i < sizeof(list); i++) 
	  this_player()->remove_cmdsoul(list[i]);
    
    for (i = 0; i < sizeof(list); i++)
    	  this_player()->add_cmdsoul(list[i]);

    this_player()->update_hooks();
    
}