/*
 *  temple5.c
 *
 *  This is the main object of the Venerate Nature
 *  quest.
 *
 *  Created by Carnak, February 2016
 */
#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../local.h"

public int do_grab(string str);

int basin;

void
create_object()
{
    set_name("basin");
    add_name("_chislev_dirt");
    set_short("@@query_short");
    set_long("@@query_long");

    basin = 1;
    will_not_recover = 1;
    
    add_prop(OBJ_M_NO_GET,      "The wooden basin is rooted to the ground.\n");
    add_prop(OBJ_M_NO_DROP,     "This is far too important to drop.\n");
    add_prop(OBJ_M_NO_STEAL,    "This object is protected by a divine force.\n");
    
    add_item(({"soil","pile"}),
    "This is a pile of soil, it has been blessed by Chislev "+
    "and would greatly improve the growth of the vegetation "+
    "in the garden outside of the temple.\n");
}

void
init()
{
    ::init();
    add_action(do_grab,   "grab");
}

/*
 * Function:    do_grab
 * Description: This function changes the object.
 */
public int
do_grab(string str)
{
    if (!str || str != "soil")
        return 0;
    
    if (!this_player()->query_prop(C_QUEST))
    {
        write("The basin formed from roots descends back into the earth, "+
        "leaving nothing behind.\n");
        remove_object();
        return 1;
    }
    
    this_player()->catch_msg("As you grab a large handful of the finely "+
    "grained soil, a surge of energy emerges from it, filling your body "+
    "with a sense of serenity.\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player()) +
    " grabs a large handful of dirt from the gnarled basin.\n",
    this_player(), this_player());
    
    write("The basin formed from roots descends back into the earth, "+
    "leaving nothing behind.\n");
    basin = 0;
    
    remove_prop(OBJ_M_NO_GET);
    
    remove_adj(query_adjs());
    add_adj("blessed");
    
    remove_name("basin");
    add_name(({"soil","pile"}));
    
    this_object()->move(this_player(),1);
    
    return 1;
}

string
query_short()
{
    if (basin)
        return "gnarled root basin";
    
    return "pile of blessed soil";
}

string
query_long()
{
    if (basin)
        return  "A collection of roots have sprouted from the "+
                "ground to form a basin, inside it is a pile of "+
                "soil. You could probably 'grab soil' if you were "+
                "so inclined.\n";
    
    return  "This is a pile of soil, it has been blessed by Chislev "+
            "and would greatly improve the growth of vegetation. "+
            "Perhaps you could 'sprinkle soil' in the garden outside "+
            "of the temple.\n";
}