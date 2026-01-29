/* Sindar npc generator

 Based on the Noldor elfmaker by Finwe which was based on Hobbitmaker
 by Palmer - Dec 03, 2003


 Sindaran phrases to be added:

 Le aphadar aen! - You are being followed
 Tolo dan na ngalad. - Come back to the Light
 Nuitho i'ruith. - Hold your wrath
 Valiroimë! - Good luck!
 Drann - The Shire
 Mithrandir - Gandalf / Grey Pilgrim
 Naugrim - Dwarves / Stunted People
 Suilad - greeting(s)

*/


#include "/d/Shire/sys/defs.h"
#include <formulas.h>
#include "/d/Shire/rivendell/local.h"

inherit SHIRE_MONSTER;
// inherit "/d/Shire/rivendell/npc/names";

#define NUM_TYPES       3 /* Number of types of elves */
#define CITIZEN         0
#define FISHERMAN       1
#define GUARD           2

#define ELF_WEP         "/d/Shire/greyhavens/wep/"
#define ELF_ARM         "/d/Shire/greyhavens/arm/"
#define ELF_OBJ         "/d/Shire/greyhavens/obj/"

#define CITIZEN_WEP     ({"spear"})
#define FISHERMAN_WEP   ({"spear"})
#define GUARD_WEP       ({"longbow"})

#define CITIZEN_ARMOUR   ({"chainmail"})
#define FISHERMAN_ARMOUR ({"chainmail", "chainmail"})
#define GUARD_ARMOUR     ({"chainmail"})

// Prototypes
string get_adjective();

// Global Vars
int npc_power, npc_type = 1;
string adj1 = "";

void create_elf() {}

nomask void
create_shire_monster()
{
    set_race_name("grey-elf");
    set_name("grey-elf");
    add_name(SHIRE_NPC);
    add_name("elf");
    set_adj(({get_adjective(), get_adjective()}));
    set_appearance_offset(-50);

    add_prop(CONT_I_HEIGHT, 200);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_WEIGHT, 0);
    add_prop("_ranger_m_no_disarm_drop", 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    // add_prop(LIVE_I_QUICKNESS, 125); /* speed up attacks */
    add_prop(NPC_I_NO_LOOKS, 500); /*sets visual looks */
    set_long("@@elf_long@@");

    set_act_time(NPC_TELL_TIME);
    set_cact_time(5);

    add_act("emote casts a melancholy look toward the Tower Hills.");
    add_act("emote turns to face the sea and smiles wistfully.");
    add_act("emote turns to face the sea and breathes deeply of the ocean air.");
    add_cact("say Nets ready!");
    add_cact("shout To arms! Spears at ready! Servants of the Dark One are " +
        "attacking us!");

    create_elf();
}


public string
get_adjective()
{
    string *adjectives, adj;

    adjectives = ({ "proud", "strong", "pensive", "slender",
      "thoughtful", "contemplative", "solemn",
      "quiet", "gentle", "musing"});
    adj = adjectives[random(sizeof(adjectives))];
    // Make sure both adjectives aren't the same:
    while (adj == adj1)
    {
        adj = adjectives[random(sizeof(adjectives))];
    }
    adj1 = adj;
    return adj;
}

public string
elf_long()
{
    string str = query_The_name(TP);

    switch(random(2))
    {
    case 0:
        str += " is a Sindar. This Grey Elf has a look of kindness in " +HIS_HER(TO)+
        " blue-grey eyes." + CAP(HE_SHE(TO)) + " is tall and slender with " +
        "alabaster skin and shiny white hair.\n";
        break;
    case 1:
        str += " is a quiet Grey Elf. " +CAP(HE_SHE(TO)) + " looks " +
        "proud and wise.\n";
        break;
    }
    return str;
}

void
arm_elf()
{
    string *filenames = ({});
    int arm_num;

    setuid(); seteuid(getuid());

    switch(npc_type)
    {
    case CITIZEN:
        filenames += ({ELF_WEP + ONE_OF_LIST(CITIZEN_WEP)});
        filenames += ({ELF_ARM + ONE_OF_LIST(CITIZEN_ARMOUR)});
	break;
    case GUARD:
        filenames += ({ELF_WEP + ONE_OF_LIST(GUARD_WEP)});
        filenames += ({ELF_ARM + ONE_OF_LIST(GUARD_ARMOUR)});
        filenames += ({ELF_ARM + "bracers.c"});
        filenames += ({ELF_ARM + "greaves.c"});
	break;
        case FISHERMAN:
        filenames += ({ELF_WEP + ONE_OF_LIST(FISHERMAN_WEP)});
        filenames += ({ELF_ARM + ONE_OF_LIST(FISHERMAN_ARMOUR)});
        break;
    }
    if (sizeof(filenames))
    	add_equipment(filenames);


}

nomask public void
set_elf_skills()
{
    int ran_num2,
    npc_stat_avg = query_average_stat(),
    mod_skills,
    com_skill,
    spe_skill,
    gen_skill;


    set_alignment(500 + 2 * npc_stat_avg);

    if (npc_stat_avg > 50)
    {
	mod_skills = npc_stat_avg/3 + 100;
    }
    else
    {
	mod_skills = npc_stat_avg * 2;
    }

    com_skill = mod_skills * 90 / 100;
    spe_skill = mod_skills * 95 / 100;
    gen_skill = mod_skills * 90 / 100;

    if(spe_skill > 150)
    	spe_skill = 150;
    else if(spe_skill < 5)
	    spe_skill = 5;

    if(com_skill > 140)
	    com_skill = 140;
    else if(com_skill < 5)
	    com_skill = 5;

    if(gen_skill > 140)
	    gen_skill = 140;
    else if(gen_skill < 10)
	    gen_skill = 10;

    set_skill(SS_WEP_MISSILE, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_PARRY,       100);
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_SNEAK,       100);
    set_skill(SS_HIDE,        100);
    set_skill(SS_AWARENESS,   100);
    set_skill(SS_ACROBAT,     100);
    arm_elf();
}

nomask public void
set_type(int some_num)
{
    if (some_num < 0 || some_num > NUM_TYPES)
	    some_num = 0;

    npc_type = some_num;
    set_gender(random(2));

/*
    if (!query_gender())
    	set_name(get_male_name());
    else
	    set_name(get_female_name());
*/
    switch(npc_type)
    {
        case CITIZEN:
            add_name("citizen");
            break;
        case FISHERMAN:
            add_name("fisherman");
            break;
        case GUARD:
            add_name("guard");
            break;
    }
}

nomask public void
set_elf_average(int level)
{
    int *npc_stats, i, ran_num;

    if (level > 200)
	    level = 200;

    npc_stats = allocate(6);
    ran_num = random(10);

    npc_stats[0] = level - (ran_num * 3);   // STR
    npc_stats[1] = level + (ran_num * 3);   // DEX
    npc_stats[2] = level - (ran_num * 2);   // CON
    npc_stats[3] = level + ran_num;         // INT
    npc_stats[4] = level + (ran_num * 2);   // WIS
    npc_stats[5] = level - ran_num;         // DIS

    i = -1;
    while (++i < 6)
    {
	if (npc_stats[i] < 10)
	    npc_stats[i] = 10;
    }

    // command("wear armours");
    set_stats(npc_stats);
    refresh_mobile();
    set_alarm(0.5,0.0, &set_elf_skills());
}

void
introduce_elf(string who)
{
    object obj;

    if (query_attack())
    {
	if (query_attack()->query_real_name() == lower_case(who))
	    command("say Begone, you murdering " +
	      query_attack()->query_race_name() +
	      " servant of the Nameless One!");
	else
	    command("say A servant of the Dark One, a " +
	      query_attack()->query_nonmet_name() +  "is amoung us. "+
	      "To arms!");
	return;
    }
    if (interactive(obj = present(who, environment())))
    {
	command("say Suilad.");

	switch (random(3))
	{
	case 0:
	    command("say Nice to meet you "+obj->query_name());
	    break;
	case 1:
	    command("greet "+who);
	    break;
	case 2:
	    command("say How do you do, kind " +
	      obj->query_race_name() + "?");
	    break;

	}
    }
}

public void
add_introduced(string name)
{
    set_alarm(2.0,0.0,&introduce_elf(name));
}

void
do_die(object killer)
{
    object room = E(TO);
    if (query_hp() < 1)
    {
    tell_room(room, "The elf mutters a last prayer to Ulmo then dies.\n", ({ TO }));

    }
    return ::do_die(killer);

}


int
query_elfmaker_elf()
{
    return 1;
}

public int
special_attack(object enemy)
{
    if (!present("_sindar_paralyze_", enemy) && !random(10))
    {
	    clone_object("/d/Shire/greyhavens/obj/net_special.c")->move(enemy, 1);
	    enemy->catch_tell("\n"+short()+" throws a net at you!\n"+
	        "You are tangled in the net and cannot move!\n\n");
    }
}

