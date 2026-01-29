/* 
 * A Stone Rune For Staying at The Meade and Mutton Inn. 
 * Created By Leia
 * 9/13/2005 
*/
inherit "/std/key";

#include <stdproperties.h>

create_key()
{
    ::create_key();

    set_name("rune");
    add_name("inn_rune");
    set_pname("runes");
    set_short("stone carved rune");
    set_pshort("stone carved runes");
    set_adj(({"stone", "carved"}));
    set_long("This is a stone carved rune that means 'rest'. You wonder what it could possibly be used for.\n");
    add_prop(OBJ_I_VALUE, 60);
    add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
