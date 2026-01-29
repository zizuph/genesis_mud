#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "/d/Genesis/delivery/delivery.h"
#include "/d/Shire/defs.h"
#include "/d/Shire/waymeet/defs.h"
#define PRICELIST_ID ({"pricelist","list","sign", "prices"})
#define BLANK_PARCHMENT "_i_have_a_blank_parchment_"
static object scribe;

//Can't leave the shop with a blank parchment.
int
block_people()
{
   if(TP->query_prop(BLANK_PARCHMENT))
   {
      write("The scribe says: You can't leave without finishing your "
         + "scroll. Either destroy it or dictate your text.\n");
      return 1;
   }
   else
   {
      return 0;
   }
}

void
create_room()
{

   configure_shire_inn();
   set_short("In the Parchment Shop");
   set_long("You stand in a rather strange basement. Huge gears line the "
   + "walls, and are activated when the floor moves up and down. You see "
   + "a large, flat table in front of you and behind it stacks of various "
   + "types of paper and jars labeled 'ink'. There is a single lamp on the "
   + "table illuminating the scribe's workspace, but otherwise the "
   + "room seems to fade "
   + "into shadow. There is a pricelist on the table.\n");

   add_item( ({"wall", "walls"}), "The walls are made of river stone, "
      + "mortared together to provide a strong foundation for the house. "
      + "You see large gears that move when the floor raises and lowers.\n");
      
   add_item( ({"gear", "gears"}), "The gears are quite large, some of them "
      + "nearly a hobbit high! They have thick teeth and are responsible "
      + "for keeping the ceiling (or floor, depending on your perspective) "
      + "from falling down on your head.\n");
      
   add_item("head", "You reach your hands up and touch your shoulders. "
      + "Then you move them toward eachother... that's your neck. Now "
      + "you move your hands up. Ahh. Yes. There it is: Your head.\n");
      
   add_item( "ceiling", "The ceiling is the bottom of the floor from "
      + "upstairs, as you might expect.\n");
   add_item( "floor", "The floor is made of river stones. It's a bit "
      + "bumpy, and feels cold to the touch, but it's solid. It's a floor.\n");
   add_cmd_item("floor", "touch", "It's damp and cold and hard.\n");
   
   add_item( ({"table", "desk"}), "The table is large and flat. It looks "
      + "like the type of place where you could write without bumping your "
      + "elbows on anything. You see a pricelist and a lamp on the table, "
      + "alongside an ink well.\n");
      
   add_item( ({"price list", "pricelist", "list"}), "The pricelist has "
      + "writing on it. One usually reads writing.\n");
   add_item("lamp", "The lamp illuminates the table. You see no way "
      + "to remove the lampshade without burning your fingers.\n");
   add_cmd_item("lamp", "extinguish", "You'd burn your fingers on the "
      + "lampshade!\n");
   add_cmd_item("lampshade", "remove", "You'd burn your fingers, though!\n");
   
   add_item( ({"stack", "stacks", "paper", "stacks of paper"}), "There "
      + "are many kinds of paper behind the table. If you order a scroll "
      + "you could likely select the type of paper you want!\n");
   add_item( ({"jar", "jars"}), "They're full of ink.\n");
   
   add_item( ({"shadow", "shadows"}), "The shadows seem deep at the "
      + "edges of the room. The lamp only illuminates so much.\n");

   add_item(PRICELIST_ID, "@@pricelist_desc");
   
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_M_NO_TELEPORT, 1);
  
   add_prop(ROOM_M_NO_ATTACK, 1);
   add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
   
   add_exit(WAYM_HOUSE_DIR + "h_4_3","up", block_people);
   reset_shire_room();

}

//so you can read the pricelist.
string
pricelist_desc()
{
  return("\n"
    + "+-------------------------------------------------------------+\n"
    + "| One of our fine scrolls is available for the price of 1     |\n"
    + "| platinum coin, including the cost of having it scribed.     |\n"
    + "|                                                             |\n"
    + "| Don't forget to <select> a paper type and <dictate> the     |\n"
    + "| text you wish the scribe to write for you.                  |\n"
    + "| Thank you for your support.                                 |\n"
    + "+-------------------------------------------------------------+\n");
}

void
reset_shire_room() 
{
   if(!scribe)
   {
      scribe = clone_object(WAYM_NPC_DIR + "scribe");
   }
   if(!present(scribe))
   {
      scribe->move(TO);
      scribe->command("emote brushes the dirt of his robe.");
   }

}

void
init() 
{
    ::init();
    add_action("do_read", "read", 0);
   add_action("dont_order", "order");
    init_shire_inn();
}

//I don't like the order verb for this room, so i redefined it.
int
dont_order()
{
   write("The scribe says: This is not an inn. Just buy things, don't "
      + "order them.\n");
   return 1;
}
void
inn_hook_cant_pay(int price)
{
    scribe->command("emote goes Ack!");
    scribe->command("say You're a bit short of coin for this. "
        + "Order again when you have money.");
    TP->remove_prop(BLANK_PARCHMENT);
}
int
do_read(string str)
{
  if (!str) return 0;
  if (member_array(str, PRICELIST_ID) == -1) return 0;
  write(pricelist_desc());
  return 1;
}

//When you buy your scroll.
int
do_order(string str) 
{

  if (!scribe || !present(scribe)) 
  {
    notify_fail("There is no one here to scribe your parchment.\n"+
                "The scribe has been killed!\n");
    return 0;
  }
  
  if(TP->query_prop(BLANK_PARCHMENT))
  {
     notify_fail("You can only have one blank scroll at a time.\n");
     return 0;
  }
  scribe->command("say Be sure to <select> the paper you want.");
  return ::do_order(str);
}

mixed *
get_order(string str)
{
  object order;
  int price;

  switch (str) 
  {
   case "scroll":
   case "parchment":
   case "vellum":
   case "paper":
   case "rag paper":
        order = clone_object(WAYM_OBJ_DIR + "scroll_2");
        price = 1728;
      TP->add_prop(BLANK_PARCHMENT, 1);
        break;
  }

  return (({order}) + ({price}));
}

