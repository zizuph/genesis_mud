#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/castle2/local.h"
inherit "/std/door";

void
create_door()
{
    set_pass_command(({"s", "south"}));
  set_name(({"ornate ironwood door","ornate door","ironwood door","door"}));
  set_door_name(({"ornate ironwood door","ornate door","ironwood door","door"}));
    set_long("This heavily ornamented door leads out castle's " +
      "courtyard.\n");
    set_open_desc("An open ornate ironwood door leading south.\n");
    set_closed_desc("A closed ornate ironwood door.\n");
    set_door_id("ornate ironwood door");
    set_other_room(ROOMSK + "courtyard_north.c");
    set_open(0);
   
}                   