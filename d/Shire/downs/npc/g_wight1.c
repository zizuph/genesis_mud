/* This is the first of the grey wights you meet in the
 * dawns. Differs from g_wight by beeing cowards.
 * Dondon 141093 
*/ 


inherit "/d/Shire/common/downs/npc/g_wight.c";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/common/lib/evilkill.h"

create_monster(){
 	::create_monster();
	set_stats(({ 43, 38, 45, 33, 2, 26}));
   add_prop(LIVE_I_UNDEAD,18);
}

