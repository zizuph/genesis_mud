/*
 * The Central Abanasinian plains
 */
#include "../warfare.h";

inherit AREA_BASE;

#pragma no_clone
#pragma strict_types

public void
configure_area()
{
    set_area_name(WAR_AREA_CENTRAL_ABANASINIA);
    set_default_controller(FREE_ARMY);
}


