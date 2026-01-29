/*
 * The Solace Area
 */
#include "../warfare.h";

inherit AREA_BASE;

#pragma no_clone
#pragma strict_types

public void
configure_area()
{
    set_area_name(WAR_AREA_NIGHLUND);
    set_default_controller(BLUE_ARMY);
}


