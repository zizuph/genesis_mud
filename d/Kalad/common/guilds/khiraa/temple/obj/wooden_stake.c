inherit "/std/container";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <cmdparse.h>
#include <composite.h>
#pragma strict_types
#pragma save_binary

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/wooden_stake.c
 * Purpose    : A wooden stake to attach heads and skulls on.
 * Located    : Obtained for free from Vile.
 * Created By : Sarr 12.Jun.97
 * Modified By: 
 */

string stuff;
object *ostuff;
int stuff_amount;
int stuck_str;

void
create_container()
{
    set_name("stake");
    set_adj("long");
    add_adj("wooden");
    set_short("@@stake_short@@");
    
    set_long("@@stake_long@@");

    add_prop(CONT_I_WEIGHT,90);
    add_prop(CONT_I_VOLUME,50);
    add_prop(OBJ_I_VALUE,0);
    add_prop(CONT_I_MAX_WEIGHT,10000);
    add_prop(CONT_I_MAX_VOLUME,10000);
    add_prop(CONT_I_CLOSED,1);
    stuff_amount = 6;
    seteuid(getuid());
}

string
stake_short()
{
    if(query_prop(OBJ_M_NO_GET))
    {
        if(stringp(stuff))
            return "long wooden stake in the ground with "+stuff+" on it";
        return "long wooden stake in the ground";
    }
    return "long wooden stake";
}

string
stake_long()
{
    if(query_prop(OBJ_M_NO_GET))
    {
        if(stringp(stuff))
            return "This is a long wooden stake with many barbs on "+
            "it. It is stuck firmly in the ground. There is "+stuff+
            " marked with numerous cryptic symbols and runes impaled "+
            "upon its length.\n";
        return "This is a long wooden stake with many barbs on it. "+
        "It is stuck firmly in the ground. It looks perfect for "+
        "impaling things on it.\n";
    }
    return "This is a long wooden stake with many barbs on, perfect "+
    "for impaling things on it, after you have stabbed it in the ground.\n";
}

int
do_stab(string str)
{
    object stake,*obs;
    if(!IS_DK(TP) && !IS_LP(TP))
        return 0;
    NF("Fix what?\n");
    if(!str)
        return 0;
    obs = FIND_STR_IN_OBJECT(str,TP);
    if(!sizeof(obs))
        return 0;
    stake = obs[0];
    if(stake != TO)
        return 0;
    NF("You can only stab it outside.\n");
    if(E(TP)->query_prop(ROOM_I_INSIDE))
        return 0;
    write("You stab the "+short()+" firmly in the ground.\n");
    say(QCTNAME(TP)+" stabs the "+short()+" firmly in the ground.\n");
    move(E(TP));
    stuck_str = TP->query_stat(SS_STR);
    add_prop(OBJ_M_NO_GET,"It is stuck firmly in the ground. You "+
    "could try to 'pull' it out.\n");
    return 1;
}


int
do_impale(string str)
{
    string s2,s3;
    object *obs,what;
    if(!IS_DK(TP) && !IS_LP(TP))
        return 0;
    NF("Impale what on what stake?\n");
    if(!str)
        return 0;
    if(sscanf(str,"%s on %s",s2,s3) != 2)
        return 0;
    obs = FIND_STR_IN_OBJECT(s3,E(TP));
    if(!sizeof(obs))
        return 0;
    if(obs[0] != TO)
        return 0;
    obs = FIND_STR_IN_OBJECT(s2,TP);
    if(!sizeof(obs))
        return 0;
    NF("One item at a time.\n");
    if(sizeof(obs) > 1)
        return 0;
    what = obs[0];
    NF("You can only impale heads and skulls.\n");
    if(!what->id("skull") && !what->id("head"))
        return 0;
    NF("There is no more room on the "+short()+" for you to put the "+
    what->short()+" on.\n");
    if(stuff_amount == 0)
        return 0;
    write("You impale the "+what->short()+" on the "+short()+" with "+
    "brutal force.\n");
    say(QCTNAME(TP)+" impales the "+what->short()+" on the "+short()+
    " with brutal force.\n");
    remove_prop(CONT_I_CLOSED);
    what->move(TO);
    add_prop(CONT_I_CLOSED,1);
    stuff = COMPOSITE_DEAD(all_inventory(TO));
    stuff_amount--;    
    return 1;
}

int
do_pull(string str)
{
    object stake,*obs;
    NF("Pull what out of the ground?\n");
    if(!str)
        return 0;
    obs = FIND_STR_IN_OBJECT(str,E(TP));
    if(!sizeof(obs))
        return 0;
    stake = obs[0];
    NF("That is not a stake.\n");
    if(MASTER_OB(stake) != MASTER_OB(TO))
        return 0;
    NF("That stake is not in the ground.\n");
    if(!stringp(stake->query_prop(OBJ_M_NO_GET)))
        return 0;
    if((TP->query_stat(SS_STR) + random(10)) < stake->query_stuck_str())
    {
        write("You try with all your might to pull out the "+
        stake->short()+", but its stuck in too deep.\n");
        say(QCTNAME(TP)+" tries to pull out the "+stake->short()+", "+
        "but couldn't manage.\n");
        return 1;
    }
    write("You pull out the "+stake->short()+" from the ground!\n");
    say(QCTNAME(TP)+" pulls the "+stake->short()+" out of the ground!\n");
    stake->remove_prop(CONT_I_CLOSED);
    all_inventory(stake)->move(E(TP));
    clone_object(KHIRAA_DIR(temple/obj/wooden_stake))->move(E(TP));
    stake->remove_object();
    return 1;
}
    
void
init()
{
    ::init();
    add_action(do_impale,"impale");
    add_action(do_stab,"stab");
    add_action(do_pull,"pull");
}

int
query_stuck_str()
{
    return stuck_str;
}

