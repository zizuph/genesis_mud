/*
 * /d/Gondor/guilds/rangers/soul/consider.c
 *
 * Included in the soul. The Ranger ability to consider the taint on 
 * the soul of another being. 
 *
 * Originally coded by Elessar 
 * (I think, but there were no credits on original.)
 *
 * Modification log:
 * 07 February 2002 Alto: General cleanup and move.
 * 01 April 2002 Gwyneth: Added a smaller breakdown of alignments in
 *                        the neutral area. Removed TP->catch_msg(QTNAME(ob) +
 *                        with write(ob->query_the_name(TP) +
 *                        as it is MUCH more efficient. catch_msg() hardly
 *                        ever needs to be used with TP. Q*NAME(ob) is used
 *                        when there is more than one person the message is
 *                        going to, essentially a macro for query_*_name().
 * 14 Aug 2002 Gwyneth  : Changed consider to only check for banned guilds
 *                        and outlaw/notorious-outlaw status.
 * 18 June 2004 Tigerlily:Changed to check for evil npcs and players as 
 *                        well, since rangers are punished for teaming with
 *                        evil or killing good creatures
 * 12 December 2015 Varian: Allowed for rconsider to check for banned guilds
 *
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>

public status
collect_arrows(string str)
{
    object *arrows, *broken, *quiver, *corpses, env;
    string preset, name;
    
    if (!strlen(str) || str != "arrows")
    {
        notify_fail("Collect what? arrows?\n");
        return 0;
    }
    
    env = environment(this_player());
    /* All visible arrows in environment */
    arrows = filter(filter(all_inventory(env), &->is_arrow()),
                    &->check_seen(this_player()));
    /* Find all the corpses */
    corpses = filter(all_inventory(env), &operator(==)(,CORPSE_OBJECT) @
                    &function_exists("create_container",));
    /* All the arrows in nearby corpses */
    foreach(object corpse: corpses)
    {
        arrows += filter(all_inventory(corpse), &->is_arrow());
    }
    /* Only arrows that you've fired. */
    arrows = filter(arrows, &operator(==)(,this_player()) @
                    &->query_prop(OBJ_O_BELONGS_TO_RANGER));
    
    broken = filter(arrows, &->query_broken());
    
    arrows -= broken;
    
    if (sizeof(arrows))
    {
        write("You gather all of your arrows that are visible to you in the "
        + "vicinity.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + " "
        + "gathers arrows from the vicinity.\n", ({ this_player() }));
        arrows->move(this_player(), 1);
        
        if (sizeof(broken))
            write("You leave the broken arrows behind.\n");
        
        name =  interactive(this_player()) ? this_player()->query_real_name() :
                OB_NAME(this_player());
    
        quiver = FIND_STR_IN_OBJECT(preset, this_player());
        
        arrows->remove_prop(OBJ_I_HIDE);
        
        if (sizeof(quiver) && objectp(quiver[0]))
            arrows->move(quiver[0]);
        
        return 1;
    }
    
    write("You search, but find " + (sizeof(broken) ? "nothing but broken "
    + "arrows" : "none of your arrows") + " in the vicinity.\n");
    return 1;
}

