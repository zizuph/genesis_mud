//-*-C++-*-
// file name:     /d/Avenir/common/dark/mon/troll_w.c
// creator(s):    Boriska, Nov 1994
// purpose:       Troll worker digging Avenir tunnels
// note:          
// last update:   Lilith 3/10/02 updated desc
//                Casca, 01/04/00. General facelift
// bug(s):
// to-do:


inherit "/std/monster";

#include "/d/Avenir/common/dark/dark.h"
#include "money.h"

create_monster ()
{
    set_name ("goblin");
    add_name ("laborer");

    set_short ("dirty goblin laborer");
    set_pshort ("dirty goblin laborers");
    set_adj (({"dirty", "worker","troll"}));
    set_long("This fellow is a giant amongst goblins. "+
        "He is working for the sybarite elves at digging tunnels. "+
        "He is filty from his labors, and despite his exhaustion, "+
        "appears to be content with his lot.\n"+
        "He is a proud member of B.O.G.L., the Brotherhood of "+
        "Goblin Laborers.\n");
  
    set_race_name("goblin");
  
    set_stats (({90,70,70,10,10,10}));
    set_alignment (0);

    set_skill (SS_WEP_AXE, 75);
    set_skill (SS_PARRY, 60);
    set_skill (SS_DEFENSE, 60);


    set_act_time (10);

    add_act("emote moves a huge piece of rock out of his way.");
    add_act("glance foreman fear");
    add_act("sigh tired");
    add_act("emote examines the wall");
    add_act("emote leans against the wall tiredly.");
    add_act("emote works at the stone wall with his pickaxe.");
    add_act("emote drinks from a waterskin hanging from his belt.");
    add_act("emote gathers the debris from his digging and piles it back "+
        "out of the way.");

    add_prop (CONT_I_WEIGHT, 500000);
    add_prop (CONT_I_VOLUME, 400000);

}

void
equip_me()
{
    clone_object (OBJ + "t_pickaxe")->move(this_object());
    clone_object (OBJ + "t_chainmail")->move(this_object());
    MONEY_MAKE_CC (50)->move(this_object());
    command ("wield all");
    command ("wear all");
}

