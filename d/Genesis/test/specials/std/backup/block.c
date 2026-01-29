#pragma strict_types

#include "defs.h"

inherit TIMED_ABILITY_LIB;


#define BLOCKER_SH (ABILITY_DIR+"/std/blocker_sh")

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"

#define TP            this_player()
#define TO            this_object()
#define QSW           query_shadow_who()
#define POSS(obj)     obj->query_possessive()
#define PRO(obj)      obj->query_pronoun()
#define OBJ(obj)      obj->query_objective()
#define SHORT(obj)    obj->short()

public mixed * target_block(object actor, string str);

public void config_ability()
{
    ::config_ability();
    set_ability_time(0);
    set_ability_name("block");
    set_ability_offensive(1);
    
    set_ability_target(target_block);
}


/* No prepare to block message */
static void ability_msg(object actor,mixed * targets,string arg)
{
}


static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    make_ability_effect_object(BLOCKER_SH, actor, 
        targets,resist,results);
}



public mixed *
target_block(object actor, string str)
{

    if (!strlen(str))
    {
        actor->catch_msg("Block who from going where?\n");
        return ({ });
    }

    string location="";
    
    object * candidates = 
        FILTER_LIVE(all_inventory(environment(actor)) - ({ actor }));
    
    mixed match;
    
    if (!parse_command(str,candidates,"%w [exit] 'for' / 'to' %l",
                    location,match) &&
        !parse_command(str,candidates,"%l [from] [going] %w",
                    match,location)  &&
        !parse_command(str,({ }),"%w [exit]",location))
    {
        actor->catch_msg("Block who from going where?\n");
        return ({ });
    }
    
    if (match && pointerp(match))
    {
        match=match[1];
    }
    else
    {
        match=actor->query_attack();
    }
    
    if (!objectp(match))
    {
        actor->catch_msg("Block who from going where?\n");
        return ({ });
    }
    
    // Get all the normal exits
    string * names =({ });
    
    mixed exits=environment(actor)->query_exit();

    for (int i=1;i<sizeof(exits);i+=3)
    {
        names+=({ exits[i] });
    }

    if (member_array("climb",get_localcmd(actor))>=0)
    {
        names+=({ "climb" });
    }

    if (member_array("swim",get_localcmd(actor))>=0)
    {
        names+=({ "swim" });
    }

    // Now check for door exits
    object * objects = all_inventory(environment(actor));
    foreach (object obj : objects)
    {
        // Check if it's a door
        if (IN_ARRAY("/std/door.c", inherit_list(obj))
            && sizeof(obj->query_pass_command()) > 0)
        {
            names += obj->query_pass_command();
            break;
        }
    }

    if (!sizeof(names) || member_array(location,names)<0)
    {
        actor->catch_msg("You find no "+location+" exit to block.\n");
        return ({ });
    }

    return ({  ({ match, location }) });

}
