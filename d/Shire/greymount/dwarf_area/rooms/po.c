/* The Dwarven Post Office in the Grey Mountains */

/*
 *Created By Leia
 *September 12, 2005
 */

inherit "/d/Shire/std/room";
#include "/sys/stdproperties.h"
#include "/d/Shire/sys/defs.h"
#include "../defs.h"

string messages;
int new_mail;

create_room() 
{
    set_short("Dwarven Mining Company Post Office");
    set_long("This is a section of the cave dedicated to sending and recieving mail with other lands. There are finely crafted mailboxes in the wall of stone and a large stone counter behind which the postmaster stands. There is a sign standing on the counter.\n");
    add_item(({"mailboxes","mailbox","box", "boxes"}),
        "There are finely carved holes in the sides of this great stone room. There are golden doors on each hole with diamond knobs to open them. Under each mailbox is a small silver plaque.\n");
    add_item(({"plaques", "small plaques", "small silver plaques"}),
        "Each of these small silver rectangles are engraved with the name of the person to whom the mailbox belongs.\n");
	add_item("counter", "The counter melds into the floor and seems to have been carved out of the rock itself.\n");
	add_item("sign", "This sign contains important information!! Perhaps you should read it.\n");
    add_item("postmaster", "This dwarf is a small, jaunty fellow, whose muscles bulge from beneath his postal uniform. He looks like he could rough you up a bit if you attempted to steal his mail.\n");
	add_cmd_item("sign", "read", "@@read_sign@@");

    add_exit(DT11, "west");
    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}

enter_inv(ob, from)
{
   object reader;
   object vote_room;
   string *masters;

   ::enter_inv(ob, from);

    if (!living(ob))
        return;
   if (present("mailreader", ob)) return;
   reader=clone_object("/secure/mail_reader");
   reader->move(ob, 1);
}

leave_inv(ob, to)
{
   object reader;   
   ::leave_inv(ob, to);
   reader = present("mailreader", ob);
   if (reader) reader->remove_object();
}

query_mail(silent) {
   string name;
   string new;
   
   name = lower_case(this_player()->query_name());
   if (!restore_object("/d/Genesis/post_dir/"+name) || messages == "")
      return 0;
   if (silent)
      return 1;
   new = "";
   if (new_mail)
      new = " NEW";
   write("\n"+
      "********************************************************\n"+
      "There is"+new+" mail for you in the nearest post office.\n"+
      "********************************************************\n\n");
   return 1;
}

string read_sign()
{
    return "\n\nOn the sign you see etched in careful lettering the following "
        + "instructions:\n\n" +
    "Examine the mailreader for a list of different commands available " +
        "to you.\n";
 }