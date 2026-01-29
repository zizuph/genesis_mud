/* 
 *	/d/Gondor/common/npc/leadorc.c        
 *                                                    
 * This orc will attack anyone attacking a member    
 * of his team                                       
 * copied in parts from /doc/examples/mobiles/troll.c
 * Revision:
 * Updated code:	Boron May 30. 1996.
 * General revision:	Olorin, 4-Feb-1997.
 */
#pragma strict_types

inherit "/d/Gondor/common/npc/std_mordor_orc";

#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

private void    add_pack();
public  int     add_3_orcs(int i);

static  int     Pack_Size;

void
create_monster()
{
    set_adj("chief");
    ::create_monster();

    set_name("captain");
    set_pname("captains");
    add_name("chief");
    set_short("orc captain");
    set_pshort("orc captains");
    set_long(BS("He looks even more evil than the rest, and he is "
        + "bigger and stronger, too. He seems to be the leader of this pack.\n"));
    default_config_npc(   30 + random(5));
    set_base_stat(SS_INT, 20 + random(5));
    set_base_stat(SS_WIS, 20 + random(5));
    set_base_stat(SS_DIS, 95 + random(5));

    set_aggressive(0);
    set_random_move(5);
    set_alignment( -200 - random(5) * 50);

    set_skill(SS_WEP_SWORD, 30 + random(10));
    set_skill(SS_WEP_CLUB,  30 + random(10));
    set_skill(SS_PARRY,     25 + random( 5));
    set_skill(SS_DEFENCE,   30 + random(10));

    add_prop(CONT_I_HEIGHT,   175 + random(   20));
    add_prop(CONT_I_WEIGHT, 80000 + random(10000));
    add_prop(CONT_I_VOLUME, 75000 + random(20000));

    add_cchat("Kill that spy!");
    add_cchat("Kill it and take his equipment! The Shrieker will be interested!");
    add_act("shout To me! Everyone to me!");
    add_act("shout Hurry, you bastards! Keep on running!");
    add_act("snarl");   
    add_cact("spit");   
}

public void
arm_me()
{
    FIX_EUID;

    if (!random(2))
	clone_object(WEP_DIR + "uruksword")->move(TO);
    else
	clone_object(WEP_DIR + "orcscim")->move(TO);
    command("wield all");

    if (random(2))
	clone_object(ARM_DIR + "releather")->move(TO);

    if (random(2))
	 clone_object(ARM_DIR + "reshield")->move(TO);

    if (random(2))
	clone_object(ARM_DIR + "rethelm")->move(TO);

    command("wear all");

    add_pack();
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
	orc = clone_object(NPC_DIR+"redteamorc");
	orc->arm_me();
	orc->move_living("down", ENV(TO));
	TO->team_join(orc);
    }
}

public void
set_pack_size(int i)
{
    Pack_Size = i;
}

/* Solemnian prestige */
public int query_knight_prestige() { return 500; }
