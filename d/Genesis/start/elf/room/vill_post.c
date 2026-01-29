/*
 * Elven startloc post office
 *
 * Added newbie poster
 * TAPAKAH, 25/05/2005
 */
#include "../stddefs.h"
#include "/sys/stdproperties.h"

#pragma save_binary

inherit ELFROOM;

#define MAILCHECKER "/secure/mail_checker"

#define WEST     ROOMDIR + "vill_road_7"


#define NAT_SHORT "In the post office of Greenoaks"
#define FOR_SHORT "In a post office"

#define NAT_LONG \
  "You are in the small post office of Greenoaks. The walls are covered " + \
  "with oak panels, and a low counter, filled with stacks of letters " + \
  "crosses the room. " + \
  "Behind the counter sits a group of brownies in a small cluster, " + \
   "intensively concentrating upon some activity of their own.\n" + \
  "There is an instructive sign, written with large, easy to read letters " + \
  "on the counter.\n"
#define FOR_LONG \
  "You are in what looks like a small post office. The walls are covered " + \
  "with oak panels, and a low counter, filled with stacks of letters, " + \
  "crosses the room. " + \
  "Behind the counter sits a group of brownies in a small cluster, " + \
   "intensively concentrating upon some activity of their own.\n" + \
  "There is an instructive sign, written with large, easy to read letters " + \
  "on the counter.\n"

#define INSTRUCTIONS \
  "read             Read from the mailbox.\n" + \
  "mail <name>      Mail to player 'name'.\n" + \
  "from             List all headers.\n" + \
  "To mail the party responsible for this area, use 'mail author'.\n"

#define PANEL_ITEM ({"panel", "panels", "oak panel", "oak panels"})
#define PANEL_DESC \
  "The oak panel on the walls have their dark colour from age, not " + \
  "from varnish or paint.\n"

#define COUNTER_ITEM ({"counter", "low counter"})
#define COUNTER_DESC \
  "The stacks of letters fills the counter to the point of overflow.\n"

#define MAIL_ITEM ({"mail", "letters", "stack", "stacks"})
#define MAIL_DESC \
  "The stacks are so towering at the top and compressed by their own " + \
  "weight at the bottom, that removing any " + \
  "letters from them is quite impossible.\n"

#define BROWNIE_ITEM ({"brownie", "brownies", "cluster", "personel"})
#define BROWNIE_DESC \
  "The brownies are small and wiry. They have bushy, white or pale gold " + \
  "hair. Beneath the hair, large green eyes stare at the world, " + \
  "giving a constant element of surprise to the fast-fluctuating " + \
  "expressions that fly over their dark-skinned faces. The ears are " + \
  "pointed, almost dagger-shaped, standing out horizontally from their " + \
  "large heads. They smile often, and their teeth are small, triangular " + \
  "and sharp.\n" + \
  "This bunch of brownies seem to be concentrated on a complex game, " + \
  "where you collect points by playing your cards right.\n" 

#define SIGN_ITEM ({"sign", "plate" })
#define SIGN_DESC   "The sign reads:\n" 

  
create_room()
{
  set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
  set_long( N_KNOW(WRAP(NAT_LONG),
		   WRAP(FOR_LONG)));

  add_prop(ROOM_I_INSIDE, 1);
  
  add_exit(WEST,      "west", 0);

  add_items();
  stock();
}


add_items()
{
  add_item(  PANEL_ITEM, WRAP(  PANEL_DESC));
  add_item(COUNTER_ITEM, WRAP(COUNTER_DESC));
  add_item(   MAIL_ITEM, WRAP(   MAIL_DESC));
  add_item(BROWNIE_ITEM, WRAP(BROWNIE_DESC));
  add_item(   SIGN_ITEM, WRAP(   SIGN_DESC + INSTRUCTIONS)); 
  
  add_cmd_item(SIGN_ITEM, "read", WRAP(SIGN_DESC + INSTRUCTIONS));
}

stock()
{

}

init() 
{
  object obj;

  ::init();


  /* Sigh. The case of the mysteriously disappearing items... */

  if (query_item() == 0 || sizeof(query_item()) == 0)
    add_items();

  if (present(MAILREADER_ID, this_player()))
    return 1;
  if ((obj = clone_object(MAILREADER)) != 0)
    {
        obj->set_alias("author", ({ WIZARD_IN_CHARGE }));
	obj->move(this_player());
    }
}

leave_inv(object who, object where) 
{
  object obj;

  if (who && 
      where && 
      where != this_object() &&
      (obj = present(MAILREADER_ID, who)) != 0)
    obj->remove_object();
  ::leave_inv(who, where);
}

query_mail(silent) {
  int mail;
  string new;

  seteuid(getuid());
  mail = MAILCHECKER->query_mail();
  if (!mail)
    return 0;
  if (silent)
    return 1;
  new = "";
  if (mail == 2)
    new = " NEW";
  if (mail == 3)
    new = " unread";
  write("\n"+
        "There is" + new + " mail for you in the nearest post office.\n\n");
  return 1;
}
