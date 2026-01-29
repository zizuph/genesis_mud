// file name:        ware_worker.c
// creator(s):       Ilyian
// revision history: Lilith, Feb '99: Fixed long uptime problem with
//                       generation of too many crates.
//                   Denis, May'97: Regular updates (triggers, etc).
// purpose:          
// note:             Examples taken from monsters by Kazz and Boriska
// bug(s):           
// to-do:            

# pragma strict_types

# include "/d/Avenir/include/defs.h"
# include "/d/Avenir/include/paths.h"
# include <macros.h>
# include <money.h>
# include <ss_types.h>

inherit "/d/Avenir/inherit/monster";

public void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name(({ "sisyphus" , "worker" }));
    set_race_name("goblin");
    set_adj("strong");
    add_adj("tired");
    set_living_name("_warehouse_worker_");
    set_long("This large goblin must be a dock worker of sorts. He is "+
             "moving crates and containers from one side of warehouse "+
             "to the other. He seems to be in no mood to be disturbed.\n");

    set_stats(({75, 35, 50, 27, 27, 57}));
    set_stat_extra(0,300);

    set_alignment(random (11) -5);


    set_skill(SS_DEFENSE, 30);
    set_skill(SS_WEP_KNIFE, 35);

    set_act_time(10);
    add_act("emote grates: Beat it, chump!");
    add_act("emote grates: Where the hell is Jarod?");
    add_act("emote grates: Why can't they just do regular shipments?");
    add_act("grumble");
    add_act("sigh");
    add_act("emote moves some crates around the warehouse.");
    add_act("emote drops a box on his foot and swears and swears and swears.");

    set_cact_time(10);
    add_cact("growl");
    add_cact("spit all");
    add_cact("emote grabs a crate and throws it at you.");

    set_cchat_time(15);
    add_cchat("You die! Worm!");
    add_cchat("Beat it before I really get angry!");

    trig_new("%s 'places' %s", "react_jarod");
}

public void
equip_me()
{
   seteuid(getuid());
   MONEY_MAKE_SC(random(25))->move(this_object());
   clone_object(PORT+ "obj/gobknife.c")->move(this_object());
   command("emote pulls a knife from his belt.");
   command("emote peers suspiciously at you.");
   command ("wield all");
}

public void
emote_hook(string emote, object who, string adverb)
{
    if (emote == "smile")
    {
        command("emote grates: What the hell are you smilin' at?");
        command("grumble");
    }
}

public void
react_jarod(object who, string str)
{
    set_alarm(itof(random(4)), 0.0,
	      &command("emote points at a pile of boxes."));
    set_alarm(itof(random(4)), 0.0, 
	      &command("emote grates: Get those to the outpost immediately!"));
}

public void
add_introduced(string str1)
{
    set_alarm(itof(random(6)), 0.0, &command("introduce myself"));
    set_alarm(itof(random(6)), 0.0,
	      &command("emote grates: Yeah, wadda you want?"));
}

public void
do_box()
{
    seteuid(getuid());
    if (!present("std_crate_ware", environment(this_object())))
    {
        clone_object(PORT + "obj/std_crate.c")->move(this_object());
        clone_object(PORT + "obj/std_crate.c")->move(this_object());
        clone_object(PORT + "obj/std_crate.c")->move(this_object());
        command("drop crates");
    }
}
