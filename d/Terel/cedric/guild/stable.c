#pragma save_binary

inherit "/std/room.c";
#include "/d/Terel/cedric/guild/guild_defs.h"

void
create_room()
{
   set_short("The Minstrel's Stables");
   set_long("You walk very carefully into the room.  As you look around, you notice little that would be considered extraordinary.  The room is build of rough wood, with a hay-loft overhead, a door leading back to the main stables, and a desk with a friendly looking minstrel novice behind it and a sigh over it.\n");
   add_item( ({"loft","hay_loft"}),"The loft is about 4 meters over your head, and piled high with hay.\n");
   add_item("wood","The wood is a dark brown and looks like it contains many splinters!\n");
   add_item( ({"novice","minstrel"}),"The novice notices you looking at her and smiles back.\n");
   add_item("door","The door leads back to where the horses are kept.\n"+
"A 'No Admittance' sign on the door discourages you from venturing back there.\n");
   add_item("desk","The desk gives every sign of being a place where you can give away money.\n");
   add_item("sign","The sign looks like you could read it!\n");
   add_cmd_item("sign","read","@@r_sign");
}