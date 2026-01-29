inherit "/std/object";
#include "/d/Kalad/defs.h"
#pragma strict_types
#pragma save_binary

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/join_bowl.c
 * Purpose    : Used for rituals.
 * Located    : Temple train room
 * Created By : Sarr 16.Mar.97
 * Modified By: 
 */


void
create_object()
{
    set_name("bowl");
    add_name("_join_bowl_");
    set_adj("golden");
    add_adj("ornate");
    set_short("ornate golden bowl");

    set_long("This is a bowl made of gold with many ornate carvings of "+
    "skulls and symbols. It is filled with dark blood that looks very "+
    "fresh.\n");

    add_prop(OBJ_I_WEIGHT,400);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,0);
}

