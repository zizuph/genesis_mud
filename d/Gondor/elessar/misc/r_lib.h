//
// Heh, this is silly.... Sir Rogon.
// 
#include "/d/Immortal/rogon/include/lib.h"

#ifdef 0
//
// The following is a little instruction to the macros defined above:
//
VPOSS(ob)   
     : Possessive form of a living. Used in say() and tell_room()
     : The ob gets "your"
     : Others gets "Rogon's" or "the dwarven wizard's"
VCPOSS(ob)
     : Capitalized possessive form.
     : "Your", "Rogon's", "The dwarven wizard's"
VHE_SHE(ob) VCHE_SHE(ob)
     : Subjective form. (Capitalized for C)
     : "you", "he"/"she"/"it"
VHIM_HER(ob) VCHIM_HER(ob)
     : Objective form.
     : "you", "him"/"her"/"it"
VHIS_HER(ob) VCHIS_HER(ob)
     : Possesive form.
     : "Your", "his"/"her"/"its"
VTNAME(ob) VCTNAME(ob)
     : The 'the-name'.
     : "you", "Rogon"/"the dwarven wizard"
VSELF(ob) VCSELF(ob)
     : Self-mode..
     : "yourself", "himself"/"herself"/"itself".

// Some filters.
FILTER_SEES_FIGHT(objs)
     : Filters the living objects objs which sees fights.

#endif
