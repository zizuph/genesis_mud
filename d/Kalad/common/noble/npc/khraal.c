inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "default.h"

void
create_kalad_monster()
{
    object ob;

    set_name("khraal");
    set_adj("black-skinned");
    add_adj("green-spotted");
    set_race_name("goblin");
    set_short("black-skinned green-spotted goblin");
    set_long("This is one mean looking goblin. He works behind the "+
        "bar, mopping up spilled drinks, moving heavy crates around, and "+
        "other tough, manual labor work. But his eyes are keen and sharp, "+
        "and you detect a notion of grim intelligence in them.\n");
    set_skill(SS_DEFENCE,50);
    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_AWARENESS,100);
    set_stats(({110,80,100,70,70,70}));

    set_act_time(5);
    add_act("emote wipes up a spot on the counter.");
    add_act("emote cleans some glasses.");
    add_act("emote refills the wine casket.");    
    add_act("emote dusts the chairs and tables.");
    add_act("emote moves around some beer kegs.");

    seteuid(getuid());   

    // Clone a chest
    ob = clone_object(NOBLE + "obj/gob_chest");
    ob->remove_prop(CONT_I_LOCK);
    ob->remove_prop(CONT_I_CLOSED);

    // Put a map inside the chest
    clone_object(NOBLE + "obj/quest_map")->move(ob);
    ob->add_prop(CONT_I_CLOSED, 1);
    ob->add_prop(CONT_I_LOCK, 1);
    ob->move(TO);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(OBJ_M_NO_ATTACK, "The pub owner won't let you kill his "+
        "hired help.\n");
}

int
do_arrest(string str)
{
    object chest;

    NF("Arrest whom?\n");
    if(str != "goblin")
        return 0;

    NF("You have no reason to.\n");
    if (!TP->query_prop("_kalad_permission_arrest"))
        return 0;

    write("You arrest the "+short()+" in the name of Lord Alexander "+
        "for crimes of protecting the guilty.\n");
    say(QCTNAME(TP)+" arrests the "+short()+" in the name of Lord "+
        "Alexander for crimes of protecting the guildty.\n");
    tell_room(ENV(TP),"Two wary noble district guards arrive.\n");
    command("shout Hey! This is unjust!!");
    tell_room(ENV(TP),"The wary noble distruct guard says: "+
        "We shall arrest him at once, my Lord.\n");
    tell_room(ENV(TP),"The two wary noble district guards searches the "+
    short()+".\n");

    chest = present("chest",TO);
    tell_room(ENV(TP),"The wary noble district guard gives "+QTNAME(TP)+" "+
        "a "+chest->short()+".\n",TP);
    write("The wary noble district guard gives you a "+chest->short()+
        ".\n");

    chest->move(TP);
    tell_room(ENV(TP),"The wary noble district guard says: He had this "+
        "on him sir.\n");
    tell_room(ENV(TP),"The two wary noble district guards drag the "+
        short()+" out south.\n");

    remove_object();
    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(do_arrest, "arrest");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (MASTER_OB(ob) == (NOBLE + "obj/free_goblin_key"))
    {
        if (from->query_prop("_kalad_free_goblin_quest"))
            set_alarm(3.0, 0.0, "return_map", from, ob);
        else
            set_alarm(3.0, 0.0, "return_normal", from);
    }
    else
        // Drop the thing if we have an environment yet
        if (!ob->id("map") && environment())
            command("drop " + ob->query_name());
}

void
return_normal(object ob)
{
    command("say I do not know what to do with this, master....");
    command("give key to "+lower_case(ob->query_name()));
}

void
return_map(object ob,object key)
{
    object chest,map;

    command("emote peers around.");
    chest = present("chest",TO);
    if (!chest)
    {
	command("searches for the chest.");
	return;
    }
    command("nod "+ob->query_name());
    command("emote unlocks a chest with the key.");
    command("emote gets something from the chest.");
    map = present("map",chest);
    if (!(map))
        map = clone_object(NOBLE + "obj/quest_map");
    chest->remove_prop(CONT_I_LOCK);
    chest->remove_prop(CONT_I_CLOSED);
    map->move(TO);    
    command("emote locks the chest with the key.");
    command("emote eats the key.");
    chest->add_prop(CONT_I_CLOSED,1);
    chest->add_prop(CONT_I_LOCK,1);
    command("give map to "+lower_case(ob->query_name()));
    key->remove_object();
}
    
