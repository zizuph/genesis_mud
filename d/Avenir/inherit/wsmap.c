// maps weapon types to weapon skills
// used for setting skills in NPCs having random weapons
// this is  hack using the fact that weapon types start from 0
// Boriska@Genesis July 1994

#include <wa_types.h>
#include <ss_types.h>

int *skill = ({ SS_WEP_SWORD, SS_WEP_POLEARM, SS_WEP_AXE,
		  SS_WEP_KNIFE, SS_WEP_CLUB, });

