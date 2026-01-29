/* graveyard/obj/corpse.c is cloned by graveyard/cave6.c */
 
inherit "/std/container";
 
 
#include "/d/Emerald/defs.h"
 
void
create_container()
{
    set_name("corpse");
    set_short("decayed corpse");
    set_adj("decayed");
    set_long("A partially decayed corpse, presumably of someone"+
        " who stumble upon the ants here.\n");
 
    add_prop(OBJ_I_NO_GET,1);
    add_prop(CONT_M_NO_REM, "@@my_rem");
    add_prop(CONT_I_WEIGHT,70000);
    add_prop(CONT_I_VOLUME,60000);
    add_prop(CONT_I_MAX_WEIGHT,130000);
    add_prop(CONT_I_MAX_VOLUME,130000);
 
    set_alarm( 1.0,0.0,"reset_container");
 
    enable_reset();
}
 
void
reset_container()
{
    object obj;
 
    seteuid(getuid(this_object()));
 
    obj=present("sword");
    if(!obj)
    {
        obj=clone_object( GRAVEYARD_DIR + "wep/ornate_sword");
        obj->move(this_object());
    }
}
 
 
mixed
my_rem()
{
    object ant;
 
    ant = present("ant", environment());
    if (ant && !ant->id("corpse"))
        return "The ant blocks your path as you approach the corpse.\n";
 
    return 0;
}
