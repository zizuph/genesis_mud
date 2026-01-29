inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
object ob1;

void
create_room()
{
set_short("Body piercing shop");
set_long("You have entered a small dimly lit room. There is a chair in "
	+"one corner, as well as a table in the middle of the room. "
	+"A sign on the wall has something on it to read. There is "
	+"the smell of alcohol on the air, mixed with sweat and dirt. "
	+"The room is som sloppy, only a goblin could live here.\n");
add_item(({"room"}),"Why don't you look around?\n");
add_item(({"smell"}),"There is the smell of strong alcohol, as well "
	+"the smell of sweat and other filth.\n");
add_item(({"chair"}),"The chair seems to be well-used, and has traces "
	+"of blood on it.\n");
add_item(({"table"}),"There is a big bottle sitting on it.\n");
add_item(({"bottle"}),"It says: XXX Brand Whiskey.\n");
add_cmd_item("from bottle","drink","You drink from the bottle and feel "
	+"brave enough to get parts of your body pierced.\n");
add_cmd_item("sign","read","The sign says:\n"
	+"Get your body pierced! It will make you look cool.\n"
	+"I do 9 piercing packages, to buy one try 'buy pierce1'\n"
	+"that will get you my first piercing job. Here is what \n"
	+"I pierce:\n"
	+"pierce1........left ear\n"
	+"pierce2........right ear\n"
	+"pierce3........both ears\n"
	+"pierce4........nose\n"
	+"pierce5........eyebrow\n"
	+"pierce6........tongue\n"
	+"pierce7........lip\n"
	+"pierce8........nipple\n"
	+"pierce9........genitals(only for the very brave)\n");
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
       if (!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/zhent/npc/piercer.c");
      ob1 ->move_living("xxx", this_object());
      }
       
}
