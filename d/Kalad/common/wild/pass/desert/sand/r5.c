inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define QUEST_NAME "towerquest"
int pres,i;
object *ob;
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
    ::create_room();
    INSIDE;
    set_short("At the top of the ruined tower");
    set_long("You are at the very top of the ruined tower.\n"+
        "Here the ceiling slopes upward at an angle to a single point in the "+
        "center. One barely man-sized hole lies in the ceiling, allowing a "+
        "thin shaft of light to illuminate the interior of this room. A nearly "+
        "ruined staircase lies on the eastern side of the room, leading "+
        "down into the darkness. A thick layer of sand blankets the floor here, "+
        "so much so that sand is the only thing visible.\n");
    add_item(({"ceiling","roof"}),
        "The dark roof of the tower, it appears as if it may collapse "+
        "at any moment.\n");
    add_item(({"man-sized hole","hole"}),
        "A small opening in the ceiling that allows light to filter into "+
        "this room.\n");
    add_item(({"ruined staircase","staircase"}),
        "A set of stone steps that are crumbling in some places but are still "+
        "serviceable, barely.\n");
    add_item(({"darkness"}),
        "It is inky-black and seems somehow malevolent in nature.\n");
    add_item(({"thick layer","layer","sand","floor"}),
        "The floor is covered in a layer of sand blown in from the hole in "+
        "the ceiling that is several inches in thickness. Only in the "+
        "vicinity of the staircase is it thinner.\n");
    add_exit(CPASS(desert/sand/on_dune),"up","@@close_tower");
    add_exit(CPASS(desert/sand/r4),"down","@@check",-1);
    set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
    if(!ob1)
        {
        ob1 = clone_object(CPASS(npc/rt_sandling));
        ob1 -> move_living("M",TO);
    }
    if(!ob2)
        {
        ob2 = clone_object(CPASS(npc/rt_sandling));
        ob2 -> move_living("M",TO);
        ob1 -> team_join(ob2);
        tell_room(TO,"Two piles of sand shift before your eyes, forming into two "+
            "humanoid shapes.\n");
    }
}
close_tower()
{
    object *ob;
    int i;
    ob = deep_inventory(TP);
    for (i = 0; i < sizeof(ob); i++)
    if(ob[i]->id("mummycorpse"))
        {
        write("You remove the mummified corpse from the ruined tower.\n");
        say(QCTNAME(TP) + " removes the mummified corpse from the ruined tower.\n");
        write("As soon as it is exposed to the desert air, the mummified "+
            "corpse instantly rots away.\n");
        say("As soon as it is exposed to the desert air, the mummified "+
            "corpse instantly rots away.\n");
        ob[i]->remove_object();
//        set_alarm(1.0,0.0,"closure");
        if(TP->test_bit("Kalad",0,14))
            {
            TP->catch_msg("You received no experience.\n");
       }
        else
            {
            TP->catch_msg("You feel more experienced!\n");
            TP->add_exp(2000);
            TP->set_bit(0,14);
            log_file(QUEST_NAME, extract(ctime(time()),4,15)+ " "+
                capitalize(TP->query_real_name()) + " rewarded with 2000xp, "+
                "<"+TP->query_average_stat()+">average stats.\n");
       }
        return 0;
    }
    write("You exit the ruined tower.\n");
    say(QCTNAME(TP) + " leaves the ruined tower.\n");
    return 0;
}

/*
closure()
{
    tell_room(TO,"The ruined tower has been sealed.\n");
    remove_exit("up");
    tell_room(CPASS(desert/sand/on_dune),"The ruined tower has been sealed.\n");
    call_other(CPASS(desert/sand/on_dune),"remove_exit","down");
    return 1;
}
*/

check()
{
    object *ob;
    int pres,i;
    ob = FILTER_LIVE(all_inventory(this_room()));
    pres = 0;
    for (i = 0; i < sizeof(ob); i++)
    {
        if (ob[i]->query_name() == "Sandling")
            {
            pres = 1;
         }
    }
    if (pres == 1)
        {
        write("The way is blocked by the aggressive sandling!\n");
        say(QCTNAME(TP) + " is prevented from going down by the aggressive sandling!\n");
    }
    return pres;
}
