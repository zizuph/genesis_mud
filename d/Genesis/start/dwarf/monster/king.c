//
// Added some asks to guide people in understanding that he needs help
// getting lifted up on the throne. askthrone() and askhelp()
// --Baldacin, Dec 2015.

#pragma save_binary

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "../defs.h"
#include "../qbits.h"

/* wh|||!! A quest! */

void
create_monster()
{
    set_name("king");
    add_name("dwarf");
    set_adj("dwarf");
    set_short("dwarf king");
    set_race_name("dwarf");
   
    set_long("The dwarf king looks very strong.\n");

    set_default_answer(VBFC_ME("otherrespons")); 
    add_ask(({"coffee","about coffee","give me the cup","cup",
                  "the cup","give me coffee"}),VBFC("askfurther"),1); 
    add_ask(({"throne","about throne", "about the throne"}),
        VBFC("askthrone"),1);
    add_ask(({"help","lift", "lift up"}), VBFC("askhelp"),1);

    trig_new("%w 'says:' 'coffee' %s","givecup");
    trig_new("%w 'says:' 'coffee\n' %s","givecup");

    set_act_time(8);
    add_act("emote tries to climb the throne but fails.");
    add_act("emote walks around drinking his coffee. He seems to enjoy it a lot.\n");
    add_act("emote looks like he's got problems with his stomach.\n");

    default_config_npc(75);
  
    set_skill(SS_WEP_AXE,75);
    set_skill(SS_PARRY,30);
    set_skill(SS_DEFENCE,20);
}

void
arm_me()
{
    clone_object(D_OBJ+"axe2")->move(TO);
    clone_object(D_OBJ+"mail")->move(TO);
    clone_object(D_OBJ+"crown")->move(TO);
    clone_object("/d/Genesis/start/dwarf/obj/cup")->move(TO);
    command("wield all");
    command("wear all");
}

int
lift(string s)
{
    NF("Lift whom?\n");

    if(s != "king" && s!= "the king")
        return 0;

    seteuid(getuid(TO));

    TP->catch_msg("You help the king climbing his throne.\n");

    if(!QDONE(HELPKING))
    {
        TP->add_exp(100,0);
        QSET(HELPKING);
        QLOG("helped the king");
        TP->catch_msg("You feel more experienced!\n");
    }

    say(QCTNAME(TP)+" helps the king up on the throne.\n");

    set_alarm(10.0, 0.0,
              &tell_room(E(TO),"The king jumps down from the throne to get something he dropped.\n"));

    return 1;
}

void
askthrone()
{
    command("say The throne is made of polished gold and decorated with "+
        "jewels, truly worthy of a King.");    
    set_alarm(1.0,0.0,&command("smile proud"));
    set_alarm(3.0,0.0,&command("say It is near impossible for me to get up "+
        "on the throne without some help though!"));
    set_alarm(5.0,0.0,&command("blush"));
}

void
askhelp()
{
    command("say Yes, I could use some help getting up on the throne!");    
    set_alarm(1.0,0.0,&command("blush"));
    set_alarm(3.0,0.0,&command("say It would be most helpful if you could "+
        "just lift me slightly, just enough to get me started!"));
    set_alarm(5.0,0.0,&command("smile hope"));
}

string
otherrespons(string s)
{
    command("emote just complains about his throne and his stomach.");
    return "";
}

string
askfurther(string s)
{
    if(!QDONE(HELPKING))
    {
        command("say Why should We, the King, give our coffee to you?");
        command("say What have you done for us lately?");
        return "";
    }
    command("say We want Our coffee to help Our stomach.");
    return "";
}

string
givecup(string s)
{
    object ob;
    if(!QDONE(HELPKING))
    {
        command("say Why should We, the King, give our coffee to you?");
        command("say Help Us to the throne, and We'll think about it.");
        return "";
    }
    command("emote laughs loudly. 'We will always help people that helps Us!");
    ob=present("cup",TO);
    ob->move(TP);
    tell_room(E(TO),"The King hands you his cup of coffee.\n");
}

void
init_living()
{
    ::init_living();

    add_action(lift, "lift");
}
