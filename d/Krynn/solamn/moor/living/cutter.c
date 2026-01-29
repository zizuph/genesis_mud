/* created by Aridor 09/15/93 */

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "../local.h"
#include <money.h>

inherit "/lib/trade.c";
inherit M_FILE

void
create_krynn_monster()
{
        int i;
        default_config_trade();
        set_name("cutter");
        add_name("peat cutter");
        set_race_name("human");
        set_long(BS("This man earns his living by cutting peat and selling "
             +   "it as fuel.",SL));
        set_adj("peat");
        add_adj("cutter");

        for (i = 0; i < 6; i++)
                set_base_stat(i, 20 + random(6));
        set_skill(SS_DEFENCE, random(10) + 10);
        set_hp(300);
        set_all_attack_unarmed(15, 15);
        set_all_hitloc_unarmed(10);
        set_alignment(10);
        set_knight_prestige(-10);
        add_act("emote slumps forward and almost collapses.");
        add_act("emote looks tiredly in your direction.");
        add_act("emote gets back to work with some renewed effort.");
        add_act("emote digs into the ground.");
        add_act("emote digs into the ground.");
        set_act_time(20);
        add_prop(NPC_I_NO_RUN_AWAY, 1);
	
	set_default_answer(VBFC_ME("my_answer"));
	add_ask(({"fuel","peat","turf"}),VBFC_ME("reply_peat"));


        if (IS_CLONE)
	  set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
        seteuid(geteuid(TO));
        clone_object(OBJ + "spade")->move(TO);
        MONEY_MAKE_CC(random(3))->move(TO);
}


init_living()
{
    ADA("buy");
    ::init_living();
}


reply_peat()
{
    command("say Of course I can sell you peat.");
    command("nod happily");
    command("say One block will be only 30 copper coins.");
    return "";
}


buy(string what)
{
    int *money;
    object block;
    seteuid(getuid(TO));
    if (what != "peat")
    {
        notify_fail("Buy what?\n");
        return 0;
    }
    if (sizeof(money = pay(30,TP,"platinum gold silver copper",0,0)) == 1)
        return 0;
    write("The human peat cutter cuts a block of peat from the ground.\n");
    write("The human peat cutter breathes heavily.\n");
    write("You pay 30 copper coins.\n");
    block = clone_object(OBJ + "peat");
    if (block->move(TP))
    {
        write("You cannot carry the block of peat.\n");
        say(QCTNAME(TP) + " bought a block of peat but couldn't carry it.\n");
        block->move(environment(TO));
        return 1;
    }
    write("The human peat cutter gives you a block of peat.\n");
    say(QCTNAME(TP) + " bought a block of peat.\n");
    return 1;
}


string
my_answer()
{
    set_alarm(3.0,0.0,"command","sigh");
    set_alarm(5.0,0.0,"command","say Can't you see that I have to work hard? I don't have time for that.");
    return "";
}
