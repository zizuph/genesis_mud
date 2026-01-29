/*
    /d/Shire/waymeet/rooms/fields/field01.c

    Field in the farm north of Waymeet
    Perrigrine, February 2019
	
	added some trees and juniper berries for a task
	in the inn in Waymeet.
	Raymundo, Jan 2020
	
	for s_field* added tobacco for a task in the Cair Andros Basement
	Raymundo, March 2020
*/

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit WAYM_LIB_DIR + "base_field_south.c";

void reset_shire_room();

void create_field()
{
    area = "near"; /* Distance from areaname */
    areaname = "Waymeet";
    land = "the Shire";
    areatype = 4;
    areadesc = "tobacco field";

    extraline = my_extra();
	add_house();

    reset_shire_room();
	
   add_exit(WAYM_FIELD_DIR + "s_field10","south");
   add_exit(WAYM_FIELD_DIR + "s_field05","east");
   add_exit(WAYM_FIELD_DIR + "s_field07", "west");
   add_exit(WAYM_FIELD_DIR + "s_field02", "north");

}

void reset_shire_room()
{
  
}

void init()
{
    ::init();
  
}