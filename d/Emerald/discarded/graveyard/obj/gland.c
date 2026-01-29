 
/* graveyard/obj/gland.c  is clone by graveyard/npc/fire_bat.c */
 
inherit "/std/object";
 
#include "/d/Emerald/defs.h"
 
int emitting;
 
 
void
create_object()
{
    set_name("gland");
    set_short("@@my_short");
    set_adj(({"red","@@my_adj"}));
    set_long("@@my_long");
 
    add_prop(OBJ_I_WEIGHT,95);
    add_prop(OBJ_I_VOLUME,150);
    add_prop(OBJ_I_LIGHT,1);
    emitting = 1;
    set_alarm( 300.0,0.0,"extinguish");
}
 
string
my_short()
{
    if (emitting)
        return "glowing red gland";
 
    return "dull red gland";
}
 
 
string
my_adj()
{
    if (emitting)
        return "glowing";
 
    return "dull";
}
 
 
string
my_long()
{
    if (emitting)
        return  "A gland from some sort of insect, which is "+
            "currently giving off a red glow.\n" ;
 
    return  "A dull red gland that looks to have once bbeen part "+
        "of some type of insect.\n" ;
}
 
 
void
extinguish()
{
    emitting = 0;
    remove_prop(OBJ_I_LIGHT);
    return;
}
