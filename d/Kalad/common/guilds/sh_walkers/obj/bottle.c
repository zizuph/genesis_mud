inherit "/std/container";
#include "/d/Kalad/defs.h"
#include <tasks.h>
#define KALAD_SHADOW_INGR "_kalad_shadow_ingr"

/* Mad Scientists' flask, by Sarr */

string mlong;
int f_str;

mixed check_ingr(object ob, object ob2);

int
amount_alco_check(object ob)
{
    int i = ob->query_alco_amount();
    if(i == 0)
        return 0;
    if(i < 11 && i > 0)
        return 10;
    if(i > 10 && i < 21)
        return 25;
    if(i > 19 && i < 31)
        return 33;
    if(i > 30 && i < 41)
        return 46;
    if(i > 40 && i < 51)
        return 58;
    if(i > 50 && i < 60)
        return 70;
    if(i > 59)
        return 85;
} 

void
create_container()
{
    set_name("bottle");
    set_adj("glass");
    set_short("glass bottle");
    set_long("This is a bottle made of glass. It looks like it "+ 
    "can hold some stuff in it.\n");
    mlong = query_long();
    add_prop(CONT_I_WEIGHT,100);
    add_prop(CONT_I_VOLUME,100);
    add_prop(CONT_I_MAX_WEIGHT,1500);
    add_prop(CONT_I_MAX_VOLUME,1500);
    add_prop(CONT_I_RIGID,1);
    add_prop(CONT_I_TRANSP,1);
}

void
init()
{
    ::init();
    AA(do_create,create);
}

int
do_create(string str)
{
    int i,go;
    object *ingr;
    NF("Create what?\n");
    if(str != "explosive liquid")
        return 0;
    NF("You must have the glass bottle first.\n");
    if(!present(TO,TP))
        return 0;
    NF("You can't do it while in combat!\n");
    if(TP->query_attack())
        return 0;
    NF("You don't know how to do that.\n");
    if(TP->query_guild_name_lay() != "Shadow Walkers")
        return 0;
    NF("You don't have the mental power to concentrate on this task.\n");
    if(TP->query_mana() < 80)
        return 0;
    ingr = all_inventory(TO);
    NF("You have too many things in the bottle.\n");
    if(sizeof(ingr) > 4)
        return 0;
    NF("You have too few things in the bottle.\n");
    if(sizeof(ingr) < 4)
        return 0;
    for(i=0;i<sizeof(ingr);i++)
    {
        if(check_ingr(ingr[i],TP) == "vital")
        {
            go = go + 1;
            if(ingr[i]->query_alco_amount())
                f_str = f_str + amount_alco_check(ingr[i]);
        }
        else
           f_str = f_str + check_ingr(ingr[i],TP);
    }
    NF("You don't have all the vital ingredients!\n");
    if(go != 3)
        return 0;
    f_str = f_str + 80;
    write("You mix all the ingredients together...\n");
    write("You combine, mix, seperate, formulate and basically "+
    "use all your alchemy skill you know to create your dangerous "+
    "weapon.\n");
    say(QCTNAME(TP)+" starts to mix stuff up in "+HIS(TP)+" glass "+
    "bottle.\n");
   TP->add_mana(-80);
   set_alarm(4.0,0.0,"mix2",TP);
   return 1;
}

void
mix2(object ob)
{
    object ob2;
    if(ob->resolve_task(TASK_ROUTINE,({TS_INT,SS_ALCHEMY})) > 0)
    {
    ob->catch_msg("You did it right!\n");
    ob->catch_msg("Your mixture is ready. All you need is a rag to stuff "+
    "it in the bottle.\n");
    seteuid(getuid());
    ob2 = clone_object("/d/Kalad/common/guilds/shadow_walkers/bottle_ragless");
    ob2->move(ob);
    ob2->set_fire_str(f_str);
    remove_object();
    }
    else
    {
        ob->catch_msg("You messed up! Oh no!\n");
        ob->catch_msg("The mixture blows up in your face!\n");
        ob->catch_msg("B O O M ! ! !\n");
        ob->heal_hp(-f_str);
        if(ob->query_hp() <= 0)
            ob->do_die(TO);
        remove_object();
    }
}


mixed
check_ingr(object ob, object pla)
{
    if(ob->id("_kalad_water"))
    {
        return "vital";
    }
    if(ob->id("_kalad_horse_crap"))
    {
        return "vital";
    }
    if(ob->query_prop(KALAD_SHADOW_INGR))
    {
        return ob->query_prop(KALAD_SHADOW_INGR);
    }
    if(ob->query_alco_amount() > 0)
        return "vital";
    return 0;
}

