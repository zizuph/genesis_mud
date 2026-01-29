/*
    special_gardener.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

int once;

void
create_kalad_monster()
{
    set_name("gardener");
    set_adj("nervous");
    add_adj("sweaty");
    set_race_name("human");
    set_short("nervous sweaty gardener");
    set_long("This poor soul toils in the garden with worn out hands. "+
        "Only, one hand is stuck in his tunic, holding something.\n");

    set_alignment(400);
    set_knight_prestige(-100);
    add_speak("Hey, I'm no thief, no matter what they say!\n");
    set_stats(({70,50,60,40,50,30}));
    set_skill(SS_DEFENSE,30);
    set_act_time(5);
    add_act("emote digs a hole.");
    add_act("emote trims the bushes.");
    add_act("emote waters the flowers.");
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_ask("gem","@@check_ask@@",1);

    add_equipment(({
        NOBLE + "arm/stained_pants",
        NOBLE + "arm/soiled_tunic",
        NOBLE + "wep/hand-shovel",
        }));
}

void
hide_the_gem_here()
{
    int i, n;
    object *obs;

    obs = all_inventory(ENV(TO));
    n = sizeof(obs);

    for (i = 0; i < n; i++)
    {
        if (MASTER_OB(obs[i]) == (NOBLE + "obj/tree"))
            obs[i]->set_gem_here();
    }
}

string
check_ask()
{
    if(once == 0)
    {
        return "say I don't know what you're talking about!";
    }
    else
    {
        set_alarm(6.0,0.0,"go_away");
        return "say Alright! I did it, I did it! I admit it, I "+
            "stole the gem! But, you won't get it out of me! I hide "+
            "it when I ran! No one will find it now! Haha!";
    }
}

void
go_away()
{
    command("emote runs off in a hurry!");
    tell_room(ENV(TO),"Something falls out of his hair as the "+short()+
        " runs away.\n");
    seteuid(getuid());
    clone_object(NOBLE + "obj/petal")->move(ENV(TO));
    remove_object();
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    
    if(once == 0)
    {
        once = 1;
        ob->stop_fight(TO);
        stop_fight(ob);
        command("say No! You can't have my gem! Argh!");
        command("ne");
        command("e");
        command("se");
        command("e");
        command("se");
        command("se");
        command("n");
        command("e");
        command("e");
        command("e");
        command("ne");
        command("e");
        command("n");
        hide_the_gem_here();
        command("s");
        command("w");
        command("sw");
        command("w");
        command("w");
        command("w");
        command("hide");
    }
}

