/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

string
query_to_jail()
{
  return "south";
}

void
create_palan_room()
{

    set_short("Ruins");
    set_long(BS("You are shocked! This place is just rubbish, stones lying "
        +    "around and not even the grass is green anymore. You wonder what "
        +    "happened here; it doesn't look like a fire has destroyed things "
        +    "here since nothing is charred black, but instead a strong force "
        +    "must have simply squashed this building. --- But what is this! "
        +    "Suddenly you notice that there are people there working. It "
        +    "seems as though they are actually rebuilding whatever this was. "
        +    "A crooked sign is lying on the ground in front of you.", SL));

    add_item("sign","You take the sign to turn it and read:\n"
               +    "        Revere Paladine\n"
               +    "       Please keep quiet!\n"
               +    "You are so startled that this should actually have "
               +    "been a temple that you drop the sign again.\n");
    add_cmd_item("sign","read","You take the sign to turn it and read:\n"
		 +    "        Revere Paladine\n"
		 +    "       Please keep quiet!\n"
		 +    "You are so startled that this should actually have "
		 +    "been a temple that you drop the sign again.\n");

    add_exit(ROOM + "street20","south",0,1);

}


