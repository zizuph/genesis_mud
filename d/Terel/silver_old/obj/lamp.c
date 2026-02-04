/*
 * A magic lamp
 * lamp.c
 * Coded by Shinto 11-12-98
 * 
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

create_object()
{
    set_name("lamp");
    set_adj("metal");
    set_short("metal lamp");
    set_pshort("metal lamps");
    set_long("A intricate metal framed lamp, glass lines each frame "+
                   "and a flame burns from within.\n");
    add_prop(OBJ_I_LIGHT, 2);
    add_prop(MAGIC_AM_MAGIC, 1);
    add_prop(MAGIC_AM_ID_INFO, "This lamp will continuously produce "+
                   "light.", 20);
    add_prop(OBJ_S_WIZINFO, "This lamp produces 2 levels of light, and "+
                   "does not extinguish. It can be found on the salesman in "+
                   "the silver forest, he can't be killed as he runs away, it "+
                   "could be stolen from him, he has 80 awareness which "+
                   "will make that a little difficult.\n");
}
