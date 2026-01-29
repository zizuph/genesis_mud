/* 
 * /d/Kalad/common/wild/pass/goblin/guild/f_armour.c
 * Purpose    : Armour used by the goblin fang guards
 * Located    : "f_guard.c"
 * Created By : Sarr ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("platemail");
    set_adj("black");
    add_adj("obsidian");
    set_short("black obsidian platemail");
    set_long("This platemail is forged by powerful magic smiths. "+
    "It is made of black obsidian stone, and is very protective.\n");
    set_ac(32);
    set_at(A_TORSO);
}
