inherit "/std/container";
#include "/d/Kalad/defs.h"

int state;
int ain;

void
create_container()
{
    set_name("cauldron");
    set_adj("eerie");
    set_short("eerie cauldron");
    set_long("A large, iron pot filled with mysterious liquid. The "+
    "liquid is @@colr@@, and bubbles slightly. There are many "+
    "arcane symbols decorating it. On the very top, arond the rim, "+
    "there are words you can read.\n");
    add_item("words","@@words@@");
    add_cmd_item("words","read","@@words@@");
    add_prop(OBJ_M_NO_GET,1);
    add_prop(CONT_I_MAX_WEIGHT,100000);
    add_prop(CONT_I_MAX_VOLUME,1000000);
    seteuid(getuid());
}
string
colr()
{
    if(state == 1)
        return "putrid green";
    if(state == 2)
        return "putrid yellow";
    return "deep red";
}

string
words()
{
    return 
    "Within this dark cauldron, place a sacrifice unto Him.\n"+
    "To invoke His wrath, place here the blood of a child, \n"+
    "and the herb known as bloodweed.\n"+
    "To destroy the flesh, place here the sacrifice, but only\n"+
    "if He is pleased.\n"+
    "The color shall reflect the state of His pleasure.\n";
}

void
return_normal()
{
    tell_room(E(TO),"The liquid in the "+short()+" suddenly "+
    "turns to a deep red color.\n");
    state = 0;
}

void
do_bubble(object ob)
{
    if(state == 2)
    {
        tell_room(E(TO),"The "+ob->short()+" bubbles away in the liquid.\n");
        ob->remove_object();
        return;
    }
    if(state == 1)
    {
        tell_room(E(TO),"The "+ob->short()+" bubbles away into the "+
        "liquid, turning it into a putrid yellow color.\n");
        ob->remove_object();
        set_alarm(itof(random(200)+500),0.0,&return_normal());
        state = 2;
        ain = 0;
        return;
    }
    tell_room(E(TO),"The "+ob->short()+" bubbles away into the "+
    "liquid, turning it into a putrid green color.\n");
    ob->remove_object();
    state = 1;
}

void
do_burn(object ob)
{
    string rc;
    object ob2 = clone_object("/std/leftover");
    rc = ob->query_race();
    if(!stringp(rc))
        rc = "human";
    ob2->leftover_init("skull",ob->query_race());
    tell_room(E(TO),"The flesh on the "+ob->short()+" burns and bubbles "+
    "away, until it leaves a bare "+ob2->short()+"!\n");
    ob->remove_object();
    ob2->move(TO);
}

void
check_it(object ob)
{
    if(ob->query_herb_name() == "bloodweed" && ain != 1)
    {
        ain = 1;
        return do_bubble(ob);
    }
    if(sizeof(ob->query_contents()) && ob->query_contents()[1] == "child" 
       && ain != 2)
    {
        ain = 2;
        return do_bubble(ob);
    }
    if(state == 2 && ob->id("head"))
        return do_burn(ob);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    set_alarm(1.0,0.0,&check_it(ob));
}

