inherit "/std/weapon";
 
#include "/d/Emerald/defs.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
 
void
create_weapon()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("sword");
    add_name("longsword");
    set_short("fine longsword");
    set_long( "An ornate longsword. Around its hilt are three "
        +"large green gemstones. The blade is made from some dark "+
        "metal of a type you have not seen before.\n" );
 
    set_adj(({"ornate","fine"}));
 
    set_hit(29);
    set_pen(29);
 
    set_wt(W_SWORD);
    set_dt(W_SLASH);
 
    set_hands(W_ANYH);
 
 
    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_WEIGHT,6000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(29,39) + 300);
        /* high cost as it's supposed to be ornate :) */
}
 
