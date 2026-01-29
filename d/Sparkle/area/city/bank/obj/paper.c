/*
 * /w/aeg/gnome/obj/paper.c
 *
 * paper meant to be a leftover
 * from mechanical creatures
 * 
 * Created March 2008, by Aeg (Matthew Morin)
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("scrap");
    add_name( ({"part", "paper"}) );
    set_pname("thin paper scraps");
    set_adj( ({"thin", "paper"}) );
    set_long("This is a thin, yet strong, piece of tan paper that "
        + "has been torn from its origional place. It is very "
        + "light in weight and transluscent.\n");
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 10);
}
