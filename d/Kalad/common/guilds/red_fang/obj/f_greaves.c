/* 
 * /d/Kalad/common/wild/pass/goblin/guild/f_greaves.c
 * Purpose    : Armour used by the fang guards
 * Located    : f_guard
 * Created By : Sarr ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("greaves");
    set_adj("black");
    add_adj("obsidian");
    set_short("black obsidian greaves");
    set_long("This platemail is forged by powerful magic smiths. "+
    "It is made of black obsidian stone, and is very protective.\n");
    set_ac(25);
    set_at(A_LEGS);
}
