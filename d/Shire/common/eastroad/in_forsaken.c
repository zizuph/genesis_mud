/*
 * The Forsaken Inn 
 * Updated by Finwe, September 1997
 * Added walls, ceiling, and floor descrs 
 *  and fixed line spacing
 */

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
 
#define MAX_ORCS 4
void make_npcs();
void reset_room() { make_npcs(); }
 
object leader, *orcs = ({ });
create_eastroad()
{
    set_short("Inside The Forsaken Inn");
    set_long("You are standing inside an abandoned inn. From the smell " +
        "and mess in here you don't think any species has neglected to pay " +
        "a visit. From the tables and chairs stacked up in the corner, you " +
        "judge that this has been a secret hideout for someone.\n");
 
    add_item(({"table","tables","chair","chairs","corner"}),
        "The chairs are all arranged in a circle around a table, and "+
        "this arrangement is backed into the most secure corner of the "+
        "collapsing building.\n");
    add_item(({"smell","mess"}), 
        "The mess and smell in here are worse than you would expect from " +
        "a building abandoned so long ago. It has obviously has had more " +
        "recent occupants.\n");
    add_item(({"rat","rats","hole","holes"}), 
        "The rats must enter through those huge holes. You don't see "+
        "any now, though.\n");
    add_item(({"up", "roof", "ceiling"}),
    "The ceiling is dark and grey from all the smoke in the room.\n");
    add_item(({"wall", "walls"}),
    "The walls are dark and grundgy. They are filthy from lack of " +
    "care and haven't been cleaned in who knows how long.\n");
    add_item(({"down", "ground", "floor"}),
    "The ground repulses you. Garbage and filth cover the floor. It " +
    "reeks, making your stomach reel in disgust.\n");
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    make_npcs();
    reset_room();
}
init()
{
    ::init();
    add_action("do_enter","enter");
}
int
do_enter(string str)
{
    if (str != "hole")
      {
        NF("Enter what?\n");
        return 0;
   }
 
    write("You squeeze through the biggest hole in the abandoned " +
        "building.\n");
    tell_room(QCTNAME(TP)+ " leaves through a hole in the abandoned inn.\n");
    TP->move_living("M","/d/Shire/common/eastroad/forsaken",1);
    return 1;
}

void
make_npcs()
{
    int i;
    if(!leader)
      {
        leader = clone_object(BREE_DIR + "npc/path_orc");
        leader->move(TO);
        tell_room(TO,capitalize(LANG_ADDART(leader->query_nonmet_name()))+
        " sneaks out from behind the bar.\n");
   }
 
    if(!sizeof(orcs))
        orcs = allocate(MAX_ORCS);

    for (i = 0; i < MAX_ORCS; i++)
        if(!orcs[i])
        {
            orcs[i] = clone_object(BREE_DIR + "npc/path_orc");
            leader->team_join(orcs[i]);
            orcs[i]->move(TO);
            tell_room(TO,capitalize(LANG_ADDART(orcs[i]->query_nonmet_name()))+
            " sneaks out from the shadows.\n");
        }
        else
            if(orcs[i]->query_leader() != leader)
            leader->team_join(orcs[i]);
 
}
