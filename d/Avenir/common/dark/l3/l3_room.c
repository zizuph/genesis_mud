// file name:		~Avenir/common/dark/l3/l3_room.c
// creator(s):		Denis
// revision history:
//			Jan 96: Added reset-ability to the impaquest
//				(function reset_statues)
//				Small cleanup.
//					-=Denis	
// purpose: Inherit file for all Unterdark level 3 rooms except altar.c
//          to support imps arrives/deaths and statues descriprions.
//          provide ability to smash imp statues for solving a quest.
// note:
// bug(s):
// to-do:

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"
#include "l3_defs.h"

int no_imps;

reset_room()
{
    int i;
    object imp;
    object shield;
    object *players;

    if(query_prop(STATUES_IN_ROOM))
    {
        add_prop(STATUES_IN_ROOM, query_prop(STATUES_IN_ROOM) - 1);
        seteuid(getuid());
        imp=clone_object(MON + "imp");
        shield = clone_object(OBJ + "hook_shield");
        shield->move(imp);
        shield = clone_object(OBJ + "hook_shield");
        shield->move(imp);
        imp->command("wield all");
        imp->move_living("M", TO);
        players=FILTER_PLAYERS(all_inventory(TO));
        for(i=0; i < sizeof(players); i++)
            if(CAN_SEE_IN_ROOM(players[i]))
                if(query_prop(STATUES_IN_ROOM) >= 1)
                    players[i]->catch_msg(
                      "One of the statues standing at the tunnel wall "+
                      "starts to move and soon stone turns into flesh. "+
                      "The creature waves its wings dangerously.\n");
                else
                    players[i]->catch_msg(
            "The stone of the statue beigns to melt into flesh. A moment " +
            "later, a " + imp->short() + " is standing where the statue "+
            "was, stretching out its wings and claws.\n");
            else
                players[i]->catch_msg(
                  "You sense something unnatural moving near you.\n");
    }
}

init()
{
    ::init();
    add_item(({"statue", "statues"}), "@@statues_desc");
    add_action("break_statue", "break");
    add_action("break_statue", "smash");
    add_action("break_statue", "destroy");
}

/*-----[ Dead and yet unborn imps can be seen as statues ]-----*/
/*-----[ Furthemore, players know if there will be 1 imp ]-----*/
/*-----[ in the room or more.                            ]-----*/
string statues_desc()
{
    if(!query_prop(STATUES_IN_ROOM))
        return "There are no statues in this room.\n";
    else if(query_prop(STATUES_IN_ROOM) == 1)
             return "The stone statue is carved in the likeness of "+
                    "a small creature, about one meter high, with "+
                    "wings and a long, pointed tail. The detail of "+
                    "the statue is incredible, and you can almost "+
                    "feel its eyes following your movements.\n";
         else
             return "The statues are of stone and about one meter "+
                    "high. They depict, with a grotesque realism, "+
                    "nasty looking creatures with wings and long "+
                    "tails in various intimidating poses. It seems "+
                    "that the eyes of the statues are following "+
                    "your movements.\n";
}

/*-----[ This function is called from imp to "awake" friends ]-----*/
delayed_reset_room()
{
    if(query_prop(STATUES_IN_ROOM))
        set_alarm(itof(20 + random(100)), 0.0, "reset_room");
}

/*-----[ Break statues action handler. ]----*/
int break_statue(string str)
{
    NF(capitalize(query_verb()) + " what?\n");
    if(query_prop(STATUES_IN_ROOM) && (str == "statue" || str == "statues"))
    {
        NF("You have nothing that would be able to break the statue.\n");
        if(sizeof(filter(all_inventory(TP), &->query_prop(IS_STATUE_SMASHER))))
        {
            remove_prop(STATUES_IN_ROOM);
            write("You smash the imp statues into tiny shards with your " +
                  "sacrificial white hammer.\n");
            tell_room(TO,QCTNAME(TP)+" smashes imp statues into pieces " +
                      "with " + POSSESS(TP) + " sacrificial white " +
		      "hammer.\n",TP);
            if(!sizeof(filter(all_inventory(TO), &->query_prop(IS_IMP))))
            {
                write("There are no traces of imps left here!\n");
                TP->add_prop(ROOMS_FREED_FROM_IMPS,
                  TP->query_prop(ROOMS_FREED_FROM_IMPS) + 1);
                no_imps = 1;
            }
            return 1;
        }
    }
}

/*
 * Function name: reset_statues
 * Descrition:    is called from the impquest daemon (entry.c) to reset
 *                the imp statues if they were smashed during the quest
 *                solving.
 */
reset_statues()
{
    if(no_imps)
    {
	no_imps = 0;
        add_prop(STATUES_IN_ROOM, random(3) + 1);
        if(random(2))
	    reset();
    }
}
