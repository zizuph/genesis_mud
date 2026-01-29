/*
 * Red Dragon Skin Combat Gauntlets
 * Worn by the captain of NW guard
 * -- Kehr, Dec 2006
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

#include <math.h>
#include <macros.h>

inherit FAERUN_ARM_BASE;

#define BOD_TYPE    A_ARMS
#define AC_MOD      0,0,0
#define BOD_TYPE    A_ARMS

#define AC 40

// improved skills array
int *simpr;

void create_faerun_armour()
{
    set_name("gauntlets");
    set_adj(({"red", "combat"}));
    set_short("pair of red combat gauntlets");
    set_pshort("pairs of red combat gauntlets");
    
    set_long("These gauntlets are build from interlocking strips and plates of red-hued " +
    	"steel. All edges have been thoroughly rounded to safeguard you from accidental " +
    	"harm while parrying blows and the insides have been padded with two layers of " +
    	"leather. Steel plates over your forearms are embossed with grotesque motifs.\n");     

	add_item(({"motif", "motifs"}), 
		"You see some strange creatures, with many legs and hands. They seem to be " +
		"entangled in a deadly struggle.\n"); 
		
    set_at(BOD_TYPE);
    set_ac(AC);
    set_am(({AC_MOD}));
    add_prop(OBJ_S_WIZINFO,
    	"----------------------------------------------------------------------------\n" +
        "These gauntlets improve wearers fighting abilities by randomly applying " +
        "+5, +3 or +2 bonus to the following skills:\n" +
        "1. Highest weapon skill\n" +
        "2. Two handed combat\n" +
        "3. Parry\n" +
        "4. Defence\n\n" +
        "Exactly 10 points in total are added. Points are distributed amongst the " +
        "skills based on name_to_random(name, OB_NUM, ...)\n" +
        "----------------------------------------------------------------------------\n");

    add_prop(MAGIC_AM_ID_INFO,
        ({"These gauntlets came from the land far away.", 5,
        "They have been imbued with ancient magics.", 15,
        "The magic within the gauntlets may aid you in battle.", 25,
        "These gauntlets may improve some of your combat skills.", 50}));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(MAGIC_AM_MAGIC,({100,"enchantment"}));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, 2500 + random(250));

    // custom wear/remove handlers here
    set_wf(TO);
}

static int
sk_compare(mixed s1, mixed s2)
{
	return TP->query_skill(s2)-TP->query_skill(s1);	
}

mixed wear (object obj) 
{
	int *skills;
	int s;
	
	simpr = ({-1, -1, -1});
	
	skills = ({SS_WEP_SWORD, SS_WEP_POLEARM, SS_WEP_AXE, SS_WEP_CLUB, SS_WEP_KNIFE, SS_WEP_MISSILE, SS_WEP_JAVELIN});
	sort_array(skills, sk_compare);
	skills = ({skills[0]}) + ({SS_PARRY, SS_2H_COMBAT, SS_DEFENCE});

	// filter out AG skills - no point in having student-layman levels ;)
	skills = filter(skills, &operator(>)(,30) @ TP->query_skill);

	int *tmp=({2,3,5});
	int i;
	
	for(i=0; i<3; i++) {
		// filter out skills that are to high to be improved		
		skills = filter(skills, &operator(<)(,101-tmp[i]) @ TP->query_skill);
		
		// if the list is empty - abandon the process
		if (sizeof(skills)==0) 
			return 0;
		
		// select skill to improve
		simpr[i] = skills[NAME_TO_RANDOM(TP->query_name(), i+atoi(OB_NUM(TO)), sizeof(skills))];
		
		// and improve it
		s=TP->query_skill_extra(simpr[i]);
		TP->set_skill_extra(simpr[i], s+tmp[i]);
	} 

	TP->catch_tell("You feel a slight tingling around your arms.\n");
	return 0;
}

mixed remove (object obj) 
{
	// remove the bonus
	int s,i;
	int *tmp=({2,3,5});
	
	for (i=2; i>=0; i--) {
		if (simpr[i]>=0) {
			s=TP->query_skill_extra(simpr[i]);
			TP->set_skill_extra(simpr[i], max(0, s-tmp[i]));
		}
	}	
	
	return 0;
}