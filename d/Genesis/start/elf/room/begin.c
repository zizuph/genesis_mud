/*
 * This is the Elven starting location.
 *
 * Created by Caution
 *
 * Revision history:
 * /Mercade, 09-02-1994: Added the question-book by Styles
 *
 * Added newbie poster
 * TAPAKAH, 25/05/2005
 * Added newbie portal
 * TAPAKAH, 17/07/2005
 *
 * To convert this over to the new Faerie, comment out the old exits 
 * and the portal, and remove the comment to link to the new area
 * -- Finwe, Jan 2006
 *
 * 06-01-15 Arandir	Connected the new Faerie
 * 
 * 10/08/21 Lavellan Re-enabled portal that had been commented out at some point  
 *
 */

#include "../stddefs.h"
#include "/sys/stdproperties.h"

#pragma save_binary

inherit ELFROOM;

#define NORTH   ROOMDIR + "trade_road_5"
#define SOUTH   ROOMDIR + "beach_1"

#define NAT_SHORT "In the Glade of Beginnings"
#define FOR_SHORT "In a spring glade"

#define NAT_LONG \
  "You are in the Glade of Beginnings. It is hallowed to all things new\n"+\
  "and fresh, to the start of growth, and to renewed efforts. Here it\n"+\
  "is eternal spring morning, and the pale dawn light before sunrise\n"+\
  "makes the morning mists seem to glow from within. Although no wind\n"+\
  "can be felt, they thread their slow dance over the dark, damp grass,\n"+\
  "now and then twirling around each other, as if in sudden joy. The\n"+\
  "air is crisp and slightly chilly, but it is fresh and filled with\n"+\
  "the smell of wet grass and green leaves.\n" 

#define FOR_LONG \
  "You are in a large forest glade. Here it is early morning, and the\n"+\
  "morning mists move over the dark, damp grass. The air is fresh and\n"+\
  "slightly chilly, as in spring, and it carries the smell of wet grass\n"+\
  "and green leaves.\n"

#define WIZINFO \
  "This room is the default start room for elves.\n"

#define GLADE_ITEM ({"glade", "forest glade"})
#define GLADE_DESC "It is an open place in the forest.\n"

#define MIST_ITEM  ({"fog", "mist", "mists", "morning mists"})
#define MIST_NDESC \
  "In the mist, pale, insubstantial beings, clad in flowing, white veils\n"+\
  "dance and play.\n"
#define MIST_FDESC \
  "It is a pale fog that moves in thick banks close to the ground.\n"

#define FAIRY_ITEM ({"beings", "fairies"})
#define FAIRY_DESC \
  "Out of the corner of the eye they seem vaguely female, with long, white\n"+\
  "hair and mothlike wings, but when you look directly at them, they seem\n" +\
  "to fade away.\n"

#define GRASS_ITEM ({"grass", "ground"})
#define GRASS_DESC \
  "The ground is covered with thick and short grass. It is dark green,\n" + \
  "almost black in this light, and wet from the dew and the fog.\n"



string start_offer();

create_room()
{
  set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
  set_long(N_KNOW(NAT_LONG, FOR_LONG)         /* + " @@start_offer@@" */  );

  add_item(GLADE_ITEM, GLADE_DESC);
  add_item(MIST_ITEM,  N_OBS(MIST_NDESC, MIST_FDESC));
  add_item(FAIRY_ITEM, FAIRY_DESC);
  add_item(GRASS_ITEM, GRASS_DESC);

  STD_WIZINFO;

  // add_exit(NORTH, "north", 0);
  // add_exit(SOUTH, "south", 0);

  add_exit ("/d/Sparkle/area/faerie/rooms/forest/ctroad04", "south", 0);

  stock();
}


void stock()
{
    seteuid(getuid());
    if (!present("faq_book"))
    {
        clone_object("/d/Genesis/start/FAQ/faq_book")->move(this_object());
    	clone_object("/d/Genesis/start/newbie/poster")->move(this_object());
    	clone_object("/d/Genesis/start/newbie/portal")->move(this_object());
    }

  restock_object(OBJDIR+"crystal", 1, "crystal");
}

reset_room()
{
  stock();
}


wizinfo()
{
  return WIZINFO;
}

init()
{
  ::init();
  if (IS_NATIVE(this_player())) {
    add_action("do_start", "start");
    set_alarm(1.0, 0.0, start_offer);
  }
}


string start_offer()
{
  if (this_player() &&
      IS_NATIVE(this_player()) &&
      this_player()->query_default_start_location()!=file_name(this_object()))
    write("\nTo start here, give the command 'start here'.\n");
}
      

int do_start(string arg)
{
  if (arg && 
      arg == "here" && 
      this_player() && 
      IS_NATIVE(this_player())) {

    this_player()->set_default_start_location(file_name(this_object()));

    write("The next time you return to this world, you will " + 
	  "begin your journey here.\n");

    return 1;
  }
}


enter_inv(object obj, object origin)
{

  /*
   * if (obj && interactive(obj))
   *   notify(MAINTAINER,
   *	      obj->query_real_name() + " enters from " + 
   *	      (origin ? file_name(origin) : "nowhere") + 
   *	      ".");
   */
  return ::enter_inv(obj, origin);
}
