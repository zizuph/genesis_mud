/*
 * Revision Feb 2000 Stern: adapted to genesis gem system
 * Tigerlily, October 2004: 
 *     Updated to add entrance to ranger caves for apprentice task 8
 */

#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/tasks/warg_cave/cave_defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#define GEM_DIR "/d/Genesis/gems/obj/"

int n;

void   reset_room();
int    ranger_entrance();
string notice_entrance();

void
create_room() 
{
    set_short("southern part of a large network of caves");
    set_long(BSN("Part of a large network of caves, this particular section "+
        "is seemingly devoid of life. Rocks and twigs are scattered about "+
        "the floor, dragged in here by something. A pile of debris has collected "+
        "in a corner of the cave. Narrow passageways lead farther to the northwest "+
        "and northeast, and a passageway leads back through the caves to "+
        "the south."));

    add_item(({"rocks","twigs"}),BSN("Not very interesting, just normal rocks and twigs with tiny scratch marks."));
    add_item(({"marks"}),"@@mark_func");
    add_item(({"ceiling"}),BSN("The ceiling is composed of time worn rock."));
    add_item(({"floor"}),BSN("The floor is composed of time worn rock, although there are some tiny marks in it."));
    add_item(({"walls","wall"}),BSN("Composed of time worn rock, there are occasional patches of moss on the walls."));
    add_item(({"patches","patch","moss"}),BSN("A rather common moss, it is slighty phosphorescent."));
    add_item(({"pile","debris","pile of debris"}),
        BSN("This pile of debris is lodged in a small corner of the area,  "+
            "protected from feet and the elements. Who knows what oddities it "+
            "might hold."));
    add_item(({"entrance", "shadowy entrance"}), &notice_entrance());

    add_exit(LEB_DIR + "wolfcave/wcave1","northwest",0);  
    add_exit(LEB_DIR + "wolfcave/cave3","northeast",0);
    add_exit(LEB_DIR + "wolfcave/cave1","south",0);  
    add_exit("/d/Gondor/guilds/rangers/tasks/warg_cave/rcave1", "west", 
        &ranger_entrance(), 0, 1);
    add_prop(ROOM_I_TYPE,ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);  
    add_prop(ROOM_I_INSIDE,1);           
    add_prop(OBJ_I_SEARCH_TIME,2+random(3));
    add_prop(OBJ_S_SEARCH_FUN,"do_search");

    reset_room();
}

string   
mark_func() 
{
/* depending on intelligence and tracking and awareness, the player might get a  */
/* bonus clue as to what is in this cave. The caves are mostly for newbies.      */
    string rt_text;
    rt_text = " bends down to study the markings on the rocks, twigs, and floor.";
    SAY(rt_text);
    if((TP->query_skill(SS_AWARENESS)+TP->query_skill(SS_TRACKING)+TP->query_stat(SS_INT))>35)
    { 
        return BSN("Studying the marks, you make them out to be claw and teeth "+
            "marks from wolves. From the marks, you can tell that at least one very "+       
            "large and powerful wolf roams these caves, and a few cubs too.");
    }
    return BSN("If only you were a bit smarter and wiser in woodcraft, you "+
        "might be able to tell something more.");
}

string
do_search(object player, string str) 
{
    object  sak,
            gem;

    if (!str || (str != "debris" && str != "here" && str != "pile of debris" && 
        str != "in debris") )
    {
        NF("Search where?\n");
        return 0;
    }

    if (n-- > 0)
    {
        seteuid(getuid(TO));
        sak=clone_object(EDORAS_DIR + "obj/bag");
        clone_object(EDORAS_DIR + "obj/fknife")->move(sak, 1);
        gem = clone_object(GEM_DIR + "garnet");
        gem->set_heap_size(1);
        gem->move(sak, 1);
        sak->move(TO);
        SAY(" searches through some debris and finds a dirty bag!");
        return BSN("After some time, you discover a dirty bag buried in the debris!");
    }
    return 0;
}

void 
reset_room()
{
    if (!n && random(2))
        n = 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob))
    {
        return;
    }
    //already killed warg, don't let them go
    // back for reset
    if (strlen(ob->query_prop(WARG_S_TEAM)))
    {
        return;
    }
// condition for either apprentice on task teamed with a 
// full ranger _or_ full ranger who is teamed with
// apprentice on task
    if (sizeof(ob->query_team_others()) != 1)
    {
        return;
    }

    if (((ob->query_prop(RANGER_I_TASK) == WARRIORS_TASK) &&
    RANGERS_FULL_MEMBER(ob->query_team_others()[0])) ||
    ((ob->query_team_others()[0]->query_prop(RANGER_I_TASK) == WARRIORS_TASK) &&
    RANGERS_FULL_MEMBER(ob)))
    {
        if (CAN_SEE_IN_ROOM(ob))
        {
            ob->catch_msg("\nYou notice a shadowy entrance " +
                "to the west.\n\n", TO);
        }
    }
}

/*
 * Function name:   ranger_entrance
 * Description:     Tests to make sure that only those
 *                  rangers working on the task are allowed
 * Returns:         0 : allowed; 1 : notallowed
 */

int
ranger_entrance()
{
    object tp = this_player();
    object *teammate = tp->query_team_others();

   // basic condition = must be teamed
    if (sizeof(teammate) != 1)
    {
        write("There is no obvious exit west.\n");
        return 1;
    }
    
    //already killed warg, don't let them go
    // back for reset
    if (strlen(tp->query_prop(WARG_S_TEAM)))
    {
        write("There is no obvious exit west.\n");
        return 1;
    }

// condition for either apprentice on task teamed with a 
// full ranger _or_ full ranger who is teamed with
// apprentice on task
    if (((tp->query_prop(RANGER_I_TASK) == WARRIORS_TASK) &&
    RANGERS_FULL_MEMBER(teammate[0])) ||
    ((teammate[0]->query_prop(RANGER_I_TASK) == WARRIORS_TASK) &&
    RANGERS_FULL_MEMBER(tp)))
    {
        return 0;
    }
    write("There is no obvious exit west.\n");
    return 1;
}

string
notice_entrance()
{
    object tp = this_player();
    object *teammate = tp->query_team_others();

   // needs to be teamed with exactly one other 
   // ranger and apprentice working task
    if (sizeof(teammate) != 1)
        return "You find no entrance.\n";

    //already killed warg, don't let them go
    // back for reset
    if (strlen(tp->query_prop(WARG_S_TEAM)))
        return "You find no entrance.\n";

// conditions for either full ranger teamed with
// apprentice doing task
// or apprentice doing task teamed with full ranger

    if (((tp->query_prop(RANGER_I_TASK) == WARRIORS_TASK) &&
    RANGERS_FULL_MEMBER(teammate[0])) ||
    ((teammate[0]->query_prop(RANGER_I_TASK) == WARRIORS_TASK) &&
    RANGERS_FULL_MEMBER(tp)))
    {
        return "You notice that there is a shadowy entrance to " +
            "the west that seems to lead to another cave.\n";
    }

    return "You find no entrance.\n";
}
