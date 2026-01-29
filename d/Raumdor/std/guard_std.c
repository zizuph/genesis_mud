/* This is so that any guards on the list recognize eachother and help  */
/* eachother when being attacked, regardless if they are teamed or not. */
/* Sarr */

#include "../common/drakmere/defs.h"
inherit STD_MONSTER;

/*RAUMDOR GUARDS LIST, they help eachother out*/
/* Add any guards you want to help eachother to the list */
string *friends = ({
    DRAKMERE_NPC_DIR + "dguard",
    DRAKMERE_NPC_DIR + "dguard_s",
    DRAKMERE_NPC_DIR + "eg_guard",
    DRAKMERE_NPC_DIR + "eg_guard_s",
    DRAKMERE_NPC_DIR + "drakmere",
    DRAKMERE_NPC_DIR + "dguard_cap", 
    DRAKMERE_NPC_DIR + "dguard_chief",
});


void
create_monster()
{
    ::create_monster();
}

int
query_drakmere_guard()
{
    return 1;
}

void
kill_undead(object ob)
{
    command("kill " + OB_NAME(ob));
}

do_die(object who)
{
    who->add_prop(IS_ENEMY_OF_DRAKMERE,who->query_prop(IS_ENEMY_OF_DRAKMERE)+1);
    ::do_die(who);
}


void
attacked_by(object enemy)
{
    ::attacked_by(enemy);
    object *livings = FILTER_LIVE(all_inventory(E(TO))) - ({TO});

    foreach (object living: livings)
    {
        if (member_array(MASTER_OB(living), friends) >= 0)
            set_alarm(1.0, 0.0, "call_friends", living, enemy);
    }
}

void
call_friends(object friend, object enemy)
{
    friend->aid_guard(enemy);
}

void aid_guard(object ob) /* You can redefine this in your guard if you like */ 
{
    if (ob->query_attack() && present(ob,E(TO)))
        command("$kill " + OB_NAME(ob));
}

void
init_living()
{
    ::init_living();
    if(TP->query_prop(LIVE_I_UNDEAD))
    {
        set_alarm(0.5,0.0,"kill_undead",TP);
    }
    if(TP->query_prop(IS_ENEMY_OF_DRAKMERE))
    {
         command("$kill " + OB_NAME(TP));
         return;
    }
    object who;
    if(who = TP->query_attack())
    {
        who = TP->query_attack();
        if(!who->query_prop(LIVE_I_UNDEAD))
            if(who->query_npc())
                set_alarm(2.0,0.0,"aid_guard",TP);
    }
}
   
