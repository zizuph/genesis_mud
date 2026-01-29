inherit "/std/room";
inherit "/lib/trade";

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <const.h>
# include <chapel.h>

string material, bride, groom, master;
object buyer;

/* Prototypes */
int help_text(string str);
int buy(string str);
int restore_ring();
void get_groom(string arg);
void get_bride(string arg);
void get_master(string arg);

void
create_room()
{
   set_short("Jeweler's");
   set_long("   This is where the anxious bride and "+
      "groom come to buy their wedding rings. The large glass "+
      "cases filled with the different styles of wedding rings "+
      "form a U shape around the walls of the room. The bands of "+
      "the many rings sparkle in the light. You see a small sign on the counter. A polite " +
      "gentleman waits to see if you will request any help.\n\n");
   
   add_item(({"gentleman", "jeweler"}), "The jeweler " +
      "is watching you and smiling as you make your selection.\n");
   add_item(({"case", "cases"}), "The glass and wooden cases each contain "+
      "about a hundred wedding sets. Upon closer examination "+
      "the bands seem to dance in the light.\n");
   add_item(({"sets", "wedding sets", "ring", "rings"}),
      "There are six different materials that the various rings are "+
      "made of: Gold, White Gold, Platinum, Mithril, Adamant and Onyx. "+
      "The styles available vary widely, maybe asking the jeweler "+
      "for help will give you more information.\n");
   add_item(({"floor", "ceiling", "wall", "walls"}),
      "The walls of this room are made of white-washed "+
      "plaster. The ceiling looks to be crafted from the same " +
      "kinds of material. On the floor under the glass cases is a thick carpeting. Around the rest of the room the floor is stone.\n");
   add_item("carpet","This is a thick reddish-brown carpet, no doubt to protect the legs of the cases from the stone floor.\n");
   add_item("sign", "Reminder to Brides and Grooms: You can " +
      "restore your lost wedding rings here by typing: newring.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(CHAPEL_DIR + "rectory", "east");
   
   buyer = 0;
   
   config_default_trade();
}

void
init()
{
   ::init();
   add_action(help_text, "request");
   add_action(help_text, "ask");
   add_action(buy, "buy");
   add_action(restore_ring, "newring");
}

int
help_text(string str)
{
   if (str!="help" && str!="for help") {
      notify_fail("Just request help will work.\n");
      return 0;
   }
   write("Now as this "+
      "is a very important moment for you I will try to be "+
      "as clear and concise as possible. You will need three people "+
      "to actually perform the ceremony and be married; The "+
      "bride, the groom and the master of ceremonies.\n" +
      "Either the bride or the groom must "+
      "be the one to purchase the rings, but the master "+
      "of ceremonies will be the one who receives the rings "+
      "so that he may perform the ceremony in the chapel.\n" +
      "\n"+"The following rings are available:\n\n"+
      "Gold wedding bands cost 50 platinum pieces.\n\n"+
      "White Gold wedding bands cost 100 platinum pieces.\n\n"+
      "Platinum bands cost 150 platinum pieces.\n\n"+
      "Mithril wedding bands cost 200 platinum pieces.\n\n"+
      "Adamant wedding bands cost 250 platinum pieces.\n\n"+
      "Onyx wedding bands cost 300 platinum pieces.\n\n");
   write("You can also ask for a new ring <newring> if have " +
      "lost your old one.\n");
   return 1;
}

void
leave_inv(object ob, object to)
{
   ::leave_inv(ob, to);
   if (ob == buyer)
      buyer = 0;
}

int
buy(string arg)
{
   notify_fail("Buy what?\n");
   if (!arg)
      return 0;
   	notify_fail("You probably want to buy more than one single ring.\n");
	if (parse_command(arg, ({ }), "%s 'ring'", material))
	return 0;
   notify_fail("We only sell rings of specific materials here.\n");
   if (parse_command(arg, ({ }), "%s 'rings'", material)) {
      if (member_array(material, MATERIALS) < 0)
         return 0;
      if (buyer) {
         notify_fail("The jeweler is serving someone else now, " +
               "please be patient.\n");
         return 0;
       }
      buyer = this_player();
      write("Who will be the groom?\n");
      input_to(get_groom);
      return 1;
   }
   return 0;
}

void
get_groom(string arg)
{
   groom = arg;
   if (!arg) {
      write("No groom given, aborted.\n");
      buyer = 0;
      return;
   }
   write("Who will be the bride?\n");
   input_to(get_bride);
}

void
get_bride(string arg)
{
   bride = arg;
   if (!arg) {
      write("No bride given, aborted.\n");
      buyer = 0;
      return;
   }
   write("Who will be the master of ceremonies?\n");
   input_to(get_master);
}

void
get_master(string arg)
{
   object bobj, gobj, mobj, bag, ring, wand;
   int    price, *arr;
   
   setuid();
   seteuid(getuid());
   master = arg;
   if (!arg) {
      write("No master of ceremonies given, aborted.\n");
      buyer = 0;
      return;
   }
   buyer = 0;
   bobj = present(bride);
   gobj = present(groom);
   mobj = present(master);
   if (!bobj)
      {
      write("You don't see " + capitalize(bride) + " here!\n");
      return;
   }
   if (!gobj)
      {
      write("You don't see " + capitalize(groom) + " here!\n");
      return;
   }
   if (!mobj)
      {
      write("You don't see " + capitalize(master) + " here!\n");
      return;
   }
   if (bobj->query_gender() != G_FEMALE)
      {
      this_player()->catch_msg("But " + QTNAME(bobj) + " isn't female!\n");
      return;
   }
   if (gobj->query_gender() != G_MALE)
      {
      this_player()->catch_msg("But " + QTNAME(gobj) + " isn't male!\n");
      return;
   }
   if (bobj != this_player() && gobj != this_player())
      {
      write("The couple have to purchase the rings themselves.\n");
      return;
   }
   if (bobj == mobj)
      {
      write("The bride cannot be master of ceremonies!\n");
      return;
   }
   if (gobj == mobj) {
      write("The groom cannot be master of ceremonies!\n");
      return;
   }
   if (M_MANAGER->query_married(bobj->query_real_name()))
      {
      write("But " + capitalize(bride) + " is already married!\n");
      return;
   }
   if (M_MANAGER->query_married(gobj->query_real_name()))
      {
      write("But " + capitalize(groom) + " is already married!\n");
      return;
   }
   if (bobj->query_prop(IS_BRIDE)) {
      write(capitalize(bride) + " is already engaged to be married!\n");
      return;
   }
   if (gobj->query_prop(IS_GROOM)) {
      write(capitalize(groom) + " is already engaged to be married!\n");
      return;
   }
   if (mobj->query_wiz_level() < bobj->query_wiz_level() ||
         mobj->query_wiz_level() < gobj->query_wiz_level()) {
      write("The master of ceremonies would need a higher level.\n");
      return;
   }
   seteuid(getuid());
   ring = clone_object(RING_PATH);
   if (!ring) {
      write("It seems I'm out of rings now.\n");
      return;
   }
   price = (member_array(material, MATERIALS) + 1) * 86400;
   if (sizeof(arr = pay(price, this_player(), 0, 0, 0, 0)) == 1) {
      write("You cannot afford that.\n");
      return;
   }
   if (arr[sizeof(arr)-1] < -1) {
      write("Strange money you've got...  No deal!\n");
      return;
   }
   bag = clone_object(CHAPEL_DIR + "obj/bag");
   ring->move(bag);
   ring->set_material(material);
   ring = clone_object(RING_PATH);
   ring->move(bag);
   ring->set_material(material);
   if (bag->move(mobj))
      bag->move(mobj, 1);
   wand = clone_object(CHAPEL_DIR + "obj/cwand");
   wand->set_groom(groom);
   wand->set_bride(bride);
   if (wand->move(mobj))
      wand->move(mobj, 1);
   bobj->add_prop(IS_BRIDE, 1);
   gobj->add_prop(IS_GROOM, 1);
   write("You've got a deal!\n");
   mobj->catch_msg("The jeweler gives you a ceremonical wand of control.\n");
   mobj->catch_msg("He also give you a bag holding two marriage rings.\n");
   mobj->catch_msg("Use examine wand to learn about specific wedding " +
      "commands.\n");
   tell_room(this_object(), "May you have a long and happy marriage!\n");
}

int
restore_ring()
{
   string name = TP->query_real_name();
   string material;
   object ring;
   
   if (sizeof(FIND_STR_IN_OBJECT(RING_ID, TP)))
      {
      write("But you already have one!\n");
      return 1;
   }
   if (!M_MANAGER->query_married(name))
      {
      write("But you are not married to anyone!\n");
      return 1;
   }
   if (!M_MANAGER->query_spouse(name))
      {
      write("You have lost your spouse for some reason!\n");
      return 1;
   }
   material = M_MANAGER->query_material(name);
   if (!material)
      {
      write("Hmm, I can't seem to remember what material you ring used to " +
         "be made of. I supose I'll make you a gold ring then.\n");
      material = "gold";
   }
   ring = clone_object(RING_PATH);
   ring->set_material(material);
   ring->set_person(M_MANAGER->query_spouse(name));
   ring->move(TP, 1);
   write("The jeweler quickly crafts a new " + material + " ring for you.\n" +
      "The jeweler gives you a new " + material + " ring.\n");
   tell_room(TO, "The jeweler gives " + QCNAME(TP) + " a new wedding ring.\n",
      TP);
   return 1;
}
