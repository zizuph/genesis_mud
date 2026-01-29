#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/castle2/local.h"
inherit "/std/door";

void
create_door()
{
  set_pass_command(({"n", "north"}));
  set_name(({"ornate ironwood door","ornate door","ironwood door","door"}));
  set_door_name(({"ornate ironwood door","ornate door","ironwood door","door"}));
  set_door_desc("ornate ironwood door");
  set_long("This heavily ornamented door leads into the north " +
    "section of the lower building.\n");
  set_open_desc("An open ornate ironwood door leading north.\n");
  set_closed_desc("A closed ornate ironwood door.\n");
  set_door_id("ornate ironwood door");
  set_other_room(ROOMSK + "hall1");
  set_open(0);
 
}
