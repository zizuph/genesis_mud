/* 	this is a weapon of the town Gelan 
 
    coder(s):   Merlin 
 
    history:    30/3/97      weapon stats changed            Maniac
                     8.94    weapon stats changed            Maniac
                 10. 1.93    townweapon -> weapon            Merlin 
                 8.11.92    created                         Merlin 
 
    purpose:    this is the standard sword for the fighters of Gelan 
 
    quests:     none 
    special:    none 
 
    to do:      none 
    bug:        none known 
*/ 
 
inherit "/std/weapon"; 
#include <formulas.h> 
#include <stdproperties.h> 
#include <wa_types.h> 
#include "weapon.h" 
 
#define HITDIFF 5                              /* Differende between min */ 
                                                /* and max values */ 
#define PENDIFF 5 
 
#define HITMIN  23                              /* Min values */ 
#define PENMIN  23 
 
 
/* 
 * Function name: create_weapon 
 * Description:   makes the sword 
 * Arguments:     none 
 * Returns:       none 
 */ 
 
void
create_weapon() 
{ 
    set_name("sword"); 
 
    set_adj(({"standard","fighter", "steel"})); 
 
    set_short("steel sword"); 
    set_pshort("steel swords"); 
 
    set_long("It's a standard steel sword of one of the fighter guards " 
        + "in Gelan. There is the sign of Gelan on its hilt. The hilt " 
        + "has a faint blue shimmer, so it must be a sword of a fighter.\n"); 
 
    set_default_weapon( 
        HITMIN + random(HITDIFF),               /* weapon hit, max see */ 
                                                /* /sys/wa_types.h     */ 
        PENMIN + random(PENDIFF),               /* penetration, max see */ 
                                                /* /sys/wa_types.h      */ 
        W_SWORD,                                /* weapon type, see        */ 
                                                /* /config/sys/wa_types2.h */ 
        W_SLASH | W_IMPALE ,                    /* damage type, see */ 
                                                /* /sys/wa_types.h  */ 
        W_ANYH,                                 /* hand/foot, see  */ 
                                                /* /sys/wa_types.h */ 
        0);                                     /* object defining */ 
                                                /* (un)wield functions */ 
 
    add_prop(OBJ_I_WEIGHT, 7000); 
    add_prop(OBJ_I_VOLUME, 897); 
} 
 
