/*
 *  /d/Gondor/rohan/fangorn/marsh_oak_room.c
 *
 *  The room in Fangorn (quest generated) where the marsh oak lives
 *
 *  Alto, 12 May 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/minas/lib/fangorn_funcs.c";
inherit "/d/Gondor/common/lib/binbit.c";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/lib/porter_defs.h"
#include "/d/Gondor/std/tell.c"



#define INNER_MINAS "/d/Gondor/minas"
#define FANGORN_DIR "/d/Gondor/fangorn"

object branch, actor, roots, *inv;
static object *Huorn = allocate(2);
static object *Ent = allocate(1);

int branch_is_taken = 0;

public string do_search(object actor, string str);
public int get_branch(object actor, int i);


public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("secluded ravine");
    set_area("deepest");
    set_areaname("Fangorn Forest");
    set_land("Fangorn");
    set_grass("sparse, short");
    set_treetype("marsh oak");
    set_forest_density(10);
    set_extraline("The trees are especially close here, "
        + "and the roots and undergrowth cling to your feet as "
        + "you slog around. One tree, in particular, catches "
        + "your eye.");

    add_exit(FANGORN_DIR + "/fangorn9", "south", 0, 0);

    clone_object(FANGORN_DIR + "/obj/machete")->move(TO);

    roots = clone_object(FANGORN_DIR + "/obj/oat_q_path_in");
    roots->move(TO);


    /* add the common room items for Fangorn forest */

    add_fangorn_items();    

    add_item(({"tree", "oak", "marsh oak", "rare marsh oak", "oak tree"}), 
        "This is a rare marsh oak tree. It grows only in wet, "
        + "boggy areas, and is reputed to sequester nutrients and trace "
        + "minerals such that its decomposing wood makes the most "
        + "excellent of fertilizers. The tree has a few scratches "
        + "near the lowest branches.\n");
    add_item(({"scratch", "scratches"}), "There are several deep "
        + "scratches near the lowest branches. They look to have "
        + "been made by a sharp object, such as a machete.\n");
    add_item(({"branches"}), "There are a few smaller branches "
        + "within reach. None of them look as though they would support "
        + "your weight. They are probably small enough to carry long "
        + "distances, however.\n");
    add_item(({"soil"}), "It is dark brown and rich.\n");
    add_item(({"depression"}), "It is rather shallow.\n");
    add_item(({"moss", "patch"}), "It is deep green and spongy.\n");
    add_item(({"undergrowth"}), "Roots cling to your feet as you move "
        + "about.\n");
    set_tell_time(120);

    /* add the common tells for Fangorn forest */

    add_fangorn_tells();

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    
    reset_room();

}  

void
reset_room()
{
    branch_is_taken = 0;

    if(!present(roots))
    {
        roots = clone_object(FANGORN_DIR + "/obj/oat_q_path_in");
        roots->move(TO);
    }

}

/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        {
        start_room_tells();
        }
}


public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(interactive(ob))
    {
        if(!present(roots))
        {
            roots = clone_object(FANGORN_DIR + "/obj/oat_q_path_in");
            roots->move(TO);
        }
    }
}


public void
summon_quest_ent()
{
    clone_npcs(Ent, FANGORN_DIR + "/npc/oat_ent", -1.0);
}


public string
do_search(object actor, string str)
{
    if(!str)
        NFN("Search what?");

    switch(str)
    {
        case "depression" :
            WRITE("You look inside the small depression in the soil.\n");
            get_branch(actor, 1);
            return "As you stand back up, you remember to return the "
                + "moss to its original location.\n";
        case "tree" :
        case "oak tree" :
        case "marsh oak tree" :
            return "You carefully search the marsh oak tree and discover "
                + "a number of good-sized branches within reach.\n";
        case "branches" :
            return "The branches look like they could be easily chopped "
                + "off with a machete.\n";
        case "scratches" :
            return "There are several deep scratches near the lowest "
                + "branches. It looks like someone started to chop off "
                + "some of them.\n";
        case "trees" :
            return "There are many kinds of trees here, including maples, "
                + "willows and elms. One tree, however, stands out from the "
                + "others. It is a rare marsh oak tree.\n";
        case "ground" :
            return "The ground is littered with old leaves.\n";
        case "leaves" :
        case "old leaves" :
            return "You rummage through the old leaves and uncover a large "
                + "patch of moss.\n";
        case "moss" :
        case "patch" :
        case "patch of moss" :
            return "You peel large hunks of moss from the ground and "
                + "see a depression in the soil.\n";
        case "soil" :
            return "The soil has a small depression in it.\n";


     }
     NFN("You don't find any " + str + " to search.");
}


public int
get_branch(object actor, int i)
{
    if ((actor->test_bit("Gondor",
        MTIRITH_PORTER_GROUP,
        MTIRITH_OAT_BIT)) || branch_is_taken)
    {
        WRITE("Your search reveals nothing special.");
        return 0;
    }

    if (!actor->query_prop(QUESTING_FOR_OATS))
    {
        WRITE("Your search reveals nothing special.");
        return 0;
    }


    if (actor->query_prop(QUESTING_FOR_OATS))
    {
        WRITE("You suddenly get the feeling you are being watched!");
        branch_is_taken = 1;

        set_alarm(2.0, 0.0, &summon_quest_ent());

        return 1;
    }

    WRITE("Your search reveals nothing special.");
    return 0;
    
}

void
init()
{
   ::init();
   add_action("chop_branch", "chop");
   add_action("cut_branch", "cut");
}

public void
summon_huorns()
{
    clone_npcs(Huorn, FANGORN_DIR + "/npc/huorn", -1.0);
}

int
chop_branch(string str)
{

    actor = TP;

    inv = all_inventory(TP);
    if (!sizeof(filter(inv, &->id("_oat_quest_machete_"))))
        NF0("You cannot chop things without the proper tool!\n");

    if (!strlen(str))
        NF0("Chop what?\n");

    switch (str)
    {
    case "tree":
        NF0("What part of the tree do you want to chop? The branches?\n");
    case "branches":
    case "branches from tree":
    case "branch from tree":
    case "branch":
        write("You attempt to chop a branch from the marsh oak tree with "
            + "the old rusty machete.\n");
        say(QTNAME(actor) + " attempts to chop a branch from the marsh "
            + "oak tree with the old rusty machete.\n");
        actor->add_prop(I_CUT_TREE, 1);
        set_alarm(1.0, 0.0, &summon_huorns());
        roots->remove_object();
        return 1;
    default:
        NF0("What do you want to chop?\n");
    }        

}

int
cut_branch(string str)
{

    actor = TP;

    inv = all_inventory(TP);
    if (!sizeof(filter(inv, &->id("_oat_quest_machete_"))))
        NF0("You cannot cut things without the proper tool!\n");

    if (!strlen(str))
        NF0("Cut what?\n");

    switch (str)
    {
    case "tree":
        NF0("What part of the tree do you want to cut? The branches?\n");
    case "branches":
    case "branches from tree":
    case "branch from tree":
    case "branch":
        write("You attempt to cut a branch from the marsh oak tree with "
            + "the old rusty machete.\n");
        say(QTNAME(actor) + " attempts to cut a branch from the marsh "
            + "oak tree with the old rusty machete.\n");
        actor->add_prop(I_CUT_TREE, 1);
        set_alarm(1.0, 0.0, &summon_huorns());
        roots->remove_object();
        return 1;
    default:
        NF0("What do you want to cut?\n");
    }        

}

