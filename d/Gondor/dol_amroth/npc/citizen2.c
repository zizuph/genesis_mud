/* -*- Mode: C -*-
 *
 * citizen1.c
 *
 * Skippern 20(c)02
 * 
 * Group one of citizens, this group is only allowed to walk outside
 *  (streets and piers) within the city wall. They will have a set of
 *  descriptions, some equipment but no name. (Named npc's are unique
 *  files)
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include "../defs.h"
#include <const.h>
#include <macros.h>
#include <ss_types.h>

#define LONG_DESC   ({ "This is a young citizen of Dol Amroth, clearly of " +\
                       "some Dunadan descent.\n", \
                       "This is a young citizen of Dol Amroth, clearly of " +\
                       "some Dunadan descent.\n", \
                       "This is a young citizen of Dol Amroth, clarely of " +\
                       "some Dunadan descent.\n", \
                       "This is a young citizen of Dor-en-Ernil, clarely of " +\
                       "some Dunadan descent.\n", \
                       "This is a young citizen of Belfals, clearly of " +\
                       "some Dunadan descent.\n", \
                       "This is a young citizen of Pelargir, clearly of " +\
                       "some Dunadan descent.\n" })   
#define NO_LIGHT    ({ "I am tired.", \
                       "I should realy be home by now.", \
                       "Its difficoult to play in the dark." })
#define EMOTE_ARR   ({ "glitter", "dpace", "silence", "grin", "uplift", \
                       "sigh", "ponder", "smile", "nod", "listen for sound", \
                       "listen here", "dsmile", "hum", "close grate", \
                       "emote plays with a cat.", "close grate" })
#define SEC_ADJ       ({ "humble",  "black-haired", "dark-haired", \
                         "tall",  "fat", "lean", "thin" })

/* Prototypes */
         void   do_my_act();
         void   get_armed();

void
create_dunadan()
{
    set_name("citizen");
    add_name( ({ "human", "dunadan" }) );
    set_adj("young");
    add_adj(one_of_list(SEC_ADJ));
    set_long(one_of_list(LONG_DESC));
    set_alignment(100+random(900));
    set_dunedain_house( one_of_list( ({ "Agarwaen", "Amandil", "Aranarth", 
	"Belecthor", "Beor", "Borlad", "Hador", "Haladin", "Hallacar",
	"Hurin", "Thalion", "Umarth" }) ) );
    set_gender( one_of_list( ({G_MALE,G_FEMALE}) ));
    add_cmdsoul("/d/Gondor/common/dunedain/dunedain_soul");
    default_config_npc(8+random(10));
    set_restrain_path( ({ DOL_HILLS+"streets",DOL_TRADE+"streets",
	DOL_TRADE+"piers",DOL_OTHER+"streets",DOL_OTHER+"pier",
	DOL_COMMON+"streets",DOL_COMMON+"piers",DOL_CRAFT+"streets",
	DOL_CRAFT+"piers" }) );
    set_random_move(10+random(20), 1);
	
	default_config_npc(30);
	set_base_stat(SS_DEX, 35);

    add_prop(LIVE_I_NEVERKNOWN,1);

    set_chat_time(50+random(100));
    add_chat("The city is so empty without the guards.");
    add_chat("Damn this guards just leaving us unprotected. What if " +
	     "the enemy attacks us?");
    add_chat("I hope my son returns safe and sound.");

    set_act_time(10+random(100));
    add_act(&do_my_act());

    get_armed();
}

void
get_armed()
{
    object ob;

    FIX_EUID;

    ob = clone_object(DOL_TG + "pants");
    ob->move(TO);
    ob = clone_object(DOL_TG + "jacket");
    ob->move(TO);
    command("wear all");
}

public void
cant_see_in_room()
{
    if (CAN_SEE_IN_ROOM(this_object()))
        return;

    command("light lamp posts");
    command("say "+one_of_list(NO_LIGHT));
    return;
}


void
do_my_act()
{
    if (!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();

    command(one_of_list(EMOTE_ARR));
}

