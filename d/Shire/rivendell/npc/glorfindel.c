/*
 * Glorifindel, High Elven Lord of Imladris
 * By Finwe, May 1998
 */


#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Shire/rivendell/npc/elfmaker.h"

inherit "/d/Shire/rivendell/npc/elfmaker.c";
inherit KILL_LOGGER;

#include "/d/Shire/common/make_money.h"

#define ELF_WEP         RWEP_DIR
#define ELF_ARM         RARM_DIR
#define ELF_OBJ         ROBJ_DIR

void
create_elf()
{
    if(!IS_CLONE)
	return;

    set_name("glorfindel");
    set_adj("golden-haired");
    add_adj("elegant");
    set_title("High Elven Lord of Imladris");
    set_race_name("elf");
    set_gender(G_MALE);
    set_long(
      "This is one of the mighty elves who dwell in Imladris. "+
      "He looks tall and fair, a proud elven warrior. He "+
      "guards the ford from evil creatures. He is an elf of " +
      "legends having fought many a battle during the ages. " +
      "Even though he is old, he looks quite young. Tales " +
      "tell that the elves of Imladris possess great magic, " +
      "and are also known for being great warriors.\n");

    set_learn_pref(({ 0,0,0,1,1,1 }));

    set_stats(({120+random(20),130+random(20),120+random(20), 
	220, 230, 100}));
    set_alignment(700 +random(300));
    MAKE_MONEY;
    make_platinum(2+random(4));
    make_gold(6+random(10));

    set_base_stat(SS_OCCUP, query_average_stat()+random(20));
    set_skill(SS_WEP_SWORD,                  90);
    set_skill(SS_2H_COMBAT,                  90);
    set_skill(SS_DEFENCE,                    70);
    set_skill(SS_PARRY,                      70);
    set_skill(SS_AWARENESS,                  70);
    set_skill(SS_SPELLCRAFT,                100);
    set_skill(SS_ELEMENT_EARTH,              80);
    set_skill(SS_ELEMENT_LIFE,               80);
    set_skill(SS_ELEMENT_FIRE,               80);
    set_skill(SS_FORM_CONJURATION,   80);
    set_skill(SS_FORM_ABJURATION,    80);
    set_skill(SS_FORM_DIVINATION,    90);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 100*1000);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(LIVE_I_SEE_DARK, 20);
    add_prop("_ranger_m_no_disarm_drop", 1);
    //add_prop(LIVE_I_QUICKNESS, 10);

    add_subloc("_special_look", TO);

    set_chat_time(4);
    add_chat("Sshhh...I thought I heard something.");
    add_chat("Those foul riders are abroad again.");
    //    add_chat("Elrond would appreciate some help.");
    add_chat("Elrond is watching the river.");
    arm_elf();

}

// Mask the original arm_elf routine
void
arm_elf()
{
    add_equipment(({ELF_WEP + "m_longsword", ELF_ARM + "m_chainmail",
	ELF_ARM + "m_greaves", ELF_ARM + "m_bracers.c"}));
}

void
chk_health()
{
    if(query_hp() < query_max_hp())
    {
	tell_room(ENV(TO), 
	  "Sings an ancient elven hymn. He seems to gain new " +
	  "strength from the song.\n");
	heal_hp(700);
	add_mana(2500);
	add_panic(-1000);
    }
}

int
filter_enemy(object who)
{
    return (who->query_attack() == TO);
}

/*
int
special_attack(object enemy)
{
    object *victim = ({});

    victim = filter(all_inventory(ENV(TO)), "filter_enemy", TO);
    if (!random(4))
	victim = ({enemy});
    else
	victim = ({ victim[random(sizeof(victim))] });
	switch(random(4))
	{
	case 0:
	    command("are on "+victim);
	    break;
	case 1:
	    command("kalya on "+victim);
	    break;
	case 2:
	    command("rilma on "+victim);
	    break;
	case 3:
	    command("silme aure");
	    break;
	}
	return 1;
}
*/

int
introduce_elf(string who)
{
    object ob;
    int i;

    ob = find_player(who);
    if (::introduce_me(who))
    {
	if (i == 0)
	{
	    command("say Greetings in the name of Elrond, the " +
	      "half-elven, true Lord of Rivendell.");
	    command("say Have you come to aid Elrond in these " +
	      "perilious times? Give a helping hand.");
	}
	else if (i == 1)
	{
	    command("shake "+who);
	    command("say Welcome "+CAP(who)+"!");
	    command("smile serious "+who);
	}
	else if (i ==2)
	{
	    command("say Greetings "+CAP(who)+".");
	    command("say And what is your business here so close " +
	      "to Imladris?");
	}
    }
}



int
query_knight_prestige()
{
    return -30;
}

