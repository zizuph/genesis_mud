inherit "/std/object";
#include "defs.h"
#include <poison_types.h>


/* Pile of bones, Sarr 
 * 2017-05-24 Malus: Added name "pile"
 */

int sta;

int aid,aid2;

void
create_object()
{
    set_name("bones");
    add_name("pile");
    add_pname("piles");
    set_adj("bloody");
    set_short("pile of bloody bones");
    set_pshort("piles of bloody bones");
    set_long("These are the remains of a human skeleton, only the "+
    "bones are covered with blood.\n");
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1400);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_GET,"The bloody bones slip from your hands.\n");
    aid = set_alarm(25.0,0.0,"decay");
    aid2 = set_alarm(5.0,7.0,"twitch");
}

twitch()
{
    if(sta == 0)
    { 
        tell_room(E(TO),"The "+short()+" twitch slightly.\n");
        sta = 1;
        return;    
    }
    if(sta == 1)
    {
        tell_room(E(TO),"The "+short()+" start to stir more.\n");
        sta = 2;
        return;
    }
    if(sta == 2)
    {
        tell_room(E(TO),"The "+short()+" begin to move around "+
        "faster, growing in size!\n");
        sta = 0;
        return;
    }
}    
   

void
decay()
{
    object skel,enemy;
    seteuid(getuid());
    tell_room(E(TO),"The "+short()+" form together again!\n");
    skel = clone_object(COMMON_NPC_DIR + "bloody_skeleton");
    enemy = query_prop(QUEST_BLOODY_SKELETON);
    skel->move_living("M",E(TO));
    if(present(enemy,E(skel)))
    {
        skel->command("emote gurgles: You caaaanot escape frommm meee!");
        skel->command("kill " + OB_NAME(enemy));
    }
    else
    {
        if(find_player(lower_case(enemy->query_name())) )
        {
            tell_room(E(TO),"The "+skel->short()+" limps away.\n");
            skel->move_living("M",E(enemy));
            tell_room(E(skel),"A "+skel->short()+" arrives.\n");
            skel->command("emote gurgles: You caaanot escape fromm mee!");
            skel->command("kill "+lower_case(enemy->query_name()));
        }
    }
    remove_object();
}

void
init()
{
    ::init();
    add_action("do_utter", "utter");
}
 
int
do_utter(string str)
{
    object ob;
    ob = present("cross",TP);
    NF("You do not have a cross with you!\n");
    if(!ob)
        return 0;
    NF("You utter: "+str+", but nothing happens.\n");
    if(str != "Pagina Lumestica")
        return 0;
    remove_alarm(aid);
    remove_alarm(aid2);
    write("Holding the "+ob->short()+" in your hands, you "+
    "utter: "+str+", and the "+short()+" begins to steam.\n");
    say("Holding the "+ob->short()+" in "+HIS(TP)+" hands, "+
    QTNAME(TP)+" utters: "+str+", and the "+short()+" beings to "+
    "steam.\n");
    set_alarm(3.0,0.0,"utter2",TP);
    return 1;
}

void
utter2(object ob)
{
    set_this_player(ob);
    tell_room(E(TO),"The "+short()+" suddenly melt into a bubbling "+
    "pool of blood, which slowly begins to dissolve.\n");
    set_alarm(3.0,0.0,"utter3",TP);
}

void
utter3(object ob)
{
    object skel,poison;
    set_this_player(ob);
    if(present(TP,E(TO)))
    {
        TP->catch_msg("A bloody skeletal hand shoots out of the pool and"+
        " slashes across your legs, then evaporates along with the "+
         "rest of the pool.\n");
        seteuid(getuid());
        poison = clone_object("/std/poison_effect");
        poison->move(TP);
        poison->set_time(200);
        poison->set_interval(10);
        poison->set_strength(30);
        poison->set_damage(({POISON_HP,5,POISON_FATIGUE,25}));
        poison->start_poison();
        skel = clone_object(COMMON_NPC_DIR + "bloody_skeleton");
        skel->move(E(TO));
        skel->set_ok_kill();
        skel->heal_hp(-8000);
        ob->attack_object(skel);
        skel->do_die(ob);
    }
    remove_object();
}

