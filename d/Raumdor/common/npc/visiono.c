/* Vision, by Sarr */
#include "defs.h"
inherit "/std/object";
inherit "/d/Raumdor/common/lib/paralyze.c";

void
create_object()
{
    string radj;
    switch(random(4))
    {
        case 0:
        radj = "horrific";
        break;
        case 1:
        radj = "dire";
        break;
        case 2:
        radj = "appaling";
        break;
        case 3:
        radj = "terrible";
        break;
    }
    set_name("vision");
    set_adj(radj);
    set_short(radj+" vision");
    set_long("@@my_long@@");
    add_prop(OBJ_I_NO_GET,1);
    add_prop(LIVE_I_UNDEAD,55);
}

string
my_long()
{
    if(!TP->query_prop(LIVE_I_UNDEAD))
        set_alarm(2.0,0.0,"summon");
    return
    "As you gaze upon this strange image, you feel fear creeping into "+
    "your heart, for before you, is one of the most ghastly scenes you "+
    "have ever seen. You see what seems to be 4 dead warriors, twisted "+
    "and mangled into a ghastly scene of death. One warrior has both "+
    "its arms severed, and he lays on the ground with a spear through "+
    "his chest. The next, his head split open by an axe, and you see "+
    "blood and brains oozing out of his skull. The third has his eyes "+
    "torn out, with his stomach exposed, and his intestines laying on "+
    "the ground. The last, he lays on the ground, both legs cut off, "+
    "arrow through his head, arm laying in shreds, and his jaw hanging "+
    "open in a silent scream. All four of these warriors are moving "+
    "around in what seems to be agony. They moan and groan, and you "+
    "quickly turn your head in horror.\n";
}

void
summon()
{
    tell_room(E(TO),"One of the ghostly warriors points at you.\n");
    set_alarm(2.0,0.0,"summon2");
}
void
summon2()
{
    tell_room(E(TO),"He moans: Mortals, you will pay for disturbing "+
    "our peace!\n");
    set_alarm(2.0,0.0,"summon3");
}
void
summon3()
{
    int i;
    object g1;
    object g2;
    object g3;
    object g4;
    object paralyze_obj;
    object *players;
    string message;

    message = "All four of the warriors begin to moan and wail " +
        "in great anguish, a sound difficult to endure!\n";
    tell_room(E(TO), ({
        message,
        message,
        "Suddenly a number of voices begin to moan and wail in great " +
            "anguish, a sound difficult to endure!\n"
    }));
    players = FILTER_PLAYERS(all_inventory(E(TO)));
     
    for(i=0; i<sizeof(players); i++)
    {
        if(!random(4))
        {  
            players[i]->command("scream");
            players[i]->catch_msg("You fall to the ground in shock, and " + 
            "begin to weep in sorrow.\n");
            tell_room(E(players[i]), QCTNAME(players[i])+" falls to the " +
                "ground and begins to sob!\n",players[i]);
            paralyze_obj = paralyze(players[i]);
            paralyze_obj->set_fail_message(
                    "You are too overcome with sorrow!\n");
        }
    }
    seteuid(getuid(TO));
    g1 = clone_object(COMMON_NPC_DIR + "vghost");
    g1->move_living("M",E(TO));
    g2 = clone_object(COMMON_NPC_DIR + "vghost_leader");
    g2->move_living("M",E(TO));
    g3 = clone_object(COMMON_NPC_DIR + "vghost");
    g3->move_living("M",E(TO));
    g4 = clone_object(COMMON_NPC_DIR + "vghost");
    g4->move_living("M",E(TO));         
    TO->remove_object();
}
