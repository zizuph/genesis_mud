/*
 * This file is IGARD_NPC + "igard_uruk_lead.c"
 *
 * Which is modified from:
 *
 * The file /d/Gondor/morgul/npc/ithil_uruk.c
 * and
 *          /d/Gondor/common/npc/redleadorc.c
 *
 * General upgrade, Olorin, February 1996
 * This orc will attack anyone attacking a member    
 * of his team                                       
 * copied in parts from /doc/examples/mobiles/troll.c
 * Revision:
 * Updated code:	Boron May 30. 1996.
 * General revision:	Olorin, 4-Feb-1997.
 * Last modified by Alto, October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/rohan/isengard/igard/npc/igard_monster.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

public string   long_desc();
public void     long_text();
public int      find_home();
public int      go_back_home();

private void    add_pack();
public  int     add_3_orcs(int i);

static  int     Pack_Size;

object HOME;

string long_looks;

#define WEP_ARRAY1 ({IGARD_WEP + "i_largeclub", IGARD_WEP + "i_largescim", IGARD_WEP + "i_largehalberd", IGARD_WEP + "i_largeaxe"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY1 ({IGARD_ARM + "i_chainmail", IGARD_ARM + "i_platemail"})
#define ARM_ARRAY3 ({IGARD_ARM + "i_greaves", IGARD_ARM + "i_bracers"})

void
long_text()
{
    switch (random(3))
    {
    case 0:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " uruk which stands almost as tall as a man. It looks tremendously "
       + "dangerous, and would probably put up quite a fight if offended "
       + "in even the slightest way.\n";
	      break;
    case 1:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " uruk, black of skin and taller than most other orcs. His arms "
       + "are long and muscular and his legs are almost straight. He glares "
       + "about the area, alert for any kind of trouble.\n";
	      break;
    case 2:
       long_looks = "This " + (implode(query_adjs()," "))
       + " uruk is intelligent and serious about his work. His battle-hardened "
       + "demeanor is emphasized by his strong muscular build and the "
       + "sharp calculation with which he surveys his surroundings. He has "
       + "little patience for lesser orcs who cannot bear the sun, and even "
       + "less for intruders looking to cause trouble.\n";
	      break;
    default:
        break;
    }
}


public void
create_igard_uruk()
{
    clone_object(IGARD_ARM + "i_shoes")->move(TO);
}

nomask void
create_igard_monster()
{
    int     rnd = random(41);

    set_name("uruk");
    set_pname("uruks");
    set_race_name("uruk");
    set_adj(alignlook());
    add_adj(alignlook2());
    long_text();
    set_long(&long_desc());
    
    default_config_npc(85 + rnd / 2);
    set_base_stat(SS_INT, 65 + rnd);
    set_base_stat(SS_WIS, 65 + rnd);

    set_alignment(-350-rnd*10);

    set_skill(SS_WEP_SWORD,   75 + rnd);
    set_skill(SS_WEP_POLEARM, 75 + rnd);
    set_skill(SS_WEP_CLUB,    75 + rnd);
    set_skill(SS_WEP_AXE,     75 + rnd);
    set_skill(SS_WEP_KNIFE,   75 + rnd);
    set_skill(SS_PARRY,       75 + rnd);
    set_skill(SS_DEFENCE,     75 + rnd);
    add_prop(CONT_I_HEIGHT,   170 + rnd);
    add_prop(CONT_I_WEIGHT, 85000 + rnd * 500);
    add_prop(CONT_I_VOLUME, 80000 + rnd * 500);    
    add_prop(LIVE_I_SEE_DARK, 5);

    set_chat_time(15 + random(15));
    add_chat("When is the boss going to give us some man flesh to eat?");
    add_chat("All these stinking hill orcs we have to put up with. They "
        + "are lazy and do not deserve the leadership of the Uruk Hai.");
    add_chat("What are you looking at? Move along!");
    add_chat("Those filthy orcs from Lugburz, they'll soon learn the "
        + "White Hand can punch the Eye until it is red, oh yes.");
    add_chat("Standing watch is boring, but the fighting Uruk Hai get "
        + "the job done that needs doing.");
    add_chat("Those horse boys in Rohan are causing trouble again. We'll "
        + "be dealing with them soon enough.");
    add_chat("This place would be a hovel without the fighting Uruk Hai "
        + "keeping order over the rabble.");
    add_chat("Have you seen that maggot Grima? He has the favour of the "
        + "boss, else I would rip that worm tongue of his out.");
    add_chat("Do something useful or I'll have you clapped in the stockade.");
    add_chat("I killed a ranger the other day. It wasn't very difficult.");
    add_chat("Do you know why rangers are always sneaking about? Because they "
        + "know what the fighting Uruk Hai will do if we catch them.");
    add_chat("We have no time for the clap-trap from Lugburz, and that goes "
        + "for orcs and mages alike.");
    add_chat("Those black-robed hooded skulkers beyond Ithilien should come "
        + "out and fight for a change. The Uruk Hai need no poisons and "
        + "clouds to do our fighting for us!");
    add_chat("I killed a dwarf the other day. I stepped on his beard and "
        + "chopped his head clean off.");
    add_chat("We have orders for halflings. The Boss has some questions for "
        + "the little squeakers that need answering.");
    add_chat("The lads have been told not to have sport with any halflings "
        + "we catch, but they'll get more than sport before the Boss is "
        + "done with them.");
    add_chat("Those stinking horse boys in Rohan have a surprise coming. "
        + "I intend to personally remove the crown - and the head - of their "
        + "petty little lord in his golden hall.");
    add_chat("There is work to be done! Where are those cursed hill orcs?");
    add_chat("I killed an elf last month. His shining eyes were delicious.");
    add_chat("We are the fighting Uruk Hai!");


    set_cchat_time(5 + random(10));
    add_cchat("You worm! Challenging the fighting Uruk Hai will be your "
        + "last mistake!");
    add_cchat("I'll tear your heart out, worm!");
    add_cchat("You will bleed quite a bit before you die.");
    add_cchat("Scum! The fighting Uruk Hai will trample you into the dirt!");
    add_cchat("Run while you can, little worm!");
    add_cchat("Uruk Hai!");

    set_act_time(15 + random(15));	
    add_act("grumble");
    add_act("get all from corpse");
    add_act("growl");
    add_act("stretch");		
    add_act("glare");		

    set_cact_time(2 + random(2));
    add_cact("scream"); 
    add_cact("growl"); 
    add_cact("frown"); 
    add_cact("yawn"); 

    set_random_move(5);

    set_alarm(1.0, 0.0, &find_home());

    create_igard_uruk();
}


string
long_desc()
{
    return long_looks;
}


static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Wep2 = WEP_ARRAY2;
    Arm1 = ARM_ARRAY1;
    Arm3 = ARM_ARRAY3;

    set_all_hitloc_unarmed(20);
}


int
find_home()
{
    HOME = environment(TO);
    return 1;
}

int
go_back_home()
{
    object foe;

    if (Victim->query_prop("_enemy_of_igard"))
    {
    foe = Victim;
    }

    if (environment(TO) == HOME)
    {
    return 1;
    }

    if ((TO->query_attack() != 0) || ((objectp(present(foe, ENV(TO))))
        && CAN_SEE(TO, foe)))
    {
    TO->command("kill " + foe->query_real_name());
    set_alarm(60.0, 0.0, &go_back_home());
    return 1;
    }

    tell_room(environment(TO), "The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " adjusts his armours, peers dangerously around "
        + "and returns to his post.\n", ({TO}));

    tell_room(HOME, "The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " arrives at his post, dusting off his "
        + "armours after a recent melee.\n");

    TO->move_living("M", HOME, 1, 0);

    return 1;
}


private void
add_pack()
{
    int     n, 
            p, 
            r;

    TO->set_leader();
    p = Pack_Size + random(Pack_Size/2 + 1);

    for (n = 0; n < p/3; n++)
    {
	       r = p - n*3;
       	if (r > 3) 
	       r = 3;
        set_alarm(1.0, 0.0, &add_3_orcs(r));
    }
}

public void
set_pack_size(int i)
{
    Pack_Size = i;
}


public void
add_3_orcs(int i)
{
    int    n = -1;
    object orc;

    if (i < 1) 
   	return 0;
    if (i > 3) 
   	i = 3;
    while (++n < i)
    {
        switch(random(2))
        {
        case 0:
           	orc = clone_object(IGARD_NPC + "igard_orc2");
            break;
        case 1:
           	orc = clone_object(IGARD_NPC + "igard_orc4");
            break;
        default:
            break;
        }

       	orc->move_living("down", ENV(TO));
       	orc->arm_me();
       	TO->team_join(orc);
    }
}

