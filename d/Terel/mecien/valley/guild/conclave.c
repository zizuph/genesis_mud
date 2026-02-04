/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <comb_mag.h>
#include <ss_types.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP       this_player()
#define TO       this_object()

int stop, lit;

void
init()
{
   add_action("do_censure",     "censure");
   add_action("list_censured",  "list");
   add_action("fill",           "fill");
   add_action("do_call",        "summon");
   ::init();
}

int
do_call(string str)
{
   object who;

   if (TP->query_mystic_rank() < MYSTIC_ARCHON) return 0;
   
   notify_fail("Call who?\n");
   if (!str) return 0;

   who=find_living(str);
   notify_fail("The spirits cannot locate that person.\n");
   if (!who || who == TP) return 0;

   notify_fail("Only mystics may be called by the ancient spirits.\n");
   if (!MEMBER(who)) return 0;

   notify_fail("You shouldn't mess with wizards like that...\n");
   if (T_WIZ(who)) return 0;

   who->catch_msg("You feel summoned by the archons.\n");
   tell_room(environment(who), "A darkness seems to take shape.\n");
   TP->catch_msg(QCTNAME(who) + " has been called.\n");
   return 1;
}

int
fill(string str)
{
   object vial, chrism;

   notify_fail("Fill what?\n");
   if (!str) return 0;

   if (!parse_command(str, TP, "%o 'with' 'oil' [from] [with] [cruet]", vial))
      return 0;

   notify_fail("You have no vial.\n");
   if (!vial->id("empty_mystic_vial")) return 0;

   notify_fail("The cruet burns you.\n");
   if (!MEMBER(TP)) return 0;

   notify_fail("You cannot open the cruet.\n");
   if (TP->query_mystic_rank() < MYSTIC_ARCHON) return 0;

   TP->catch_msg("You pour oil from the cruet into your vial.\n");
   say(QCTNAME(this_player()) + " pours oil fro the cruet into a vial.\n");
   
   vial->remove_object();
   seteuid(getuid());
   chrism = clone_object(GUILD_DIR + "obj/chrism");
   chrism->move(TP);
   return 1;
}

int
do_censure(string str)
{
   int i;
   string *banned;
   string trash1, trash2;
   object who, ring;

   notify_fail("You have not the authority!\n");
   if (TP->query_mystic_rank() < MYSTIC_ARCHON) return 0;
   
   notify_fail("Whom do you intend to censure?\n");
   if (!strlen(str) || sscanf(str, "%s %s", trash1, trash2)) return 0;
   
   who = find_player(lower_case(str));
   if (!who) who = "/secure/master"->finger_player(lower_case(str));
   if (!who) return 0;
   
   notify_fail("You do not have the authority to do that!\n");
   if (who->query_wiz_level() > 0 && !T_WIZ(TP)) return 0;
   
   if (file_size(BANNED) > 0) {
      banned = explode(read_file(BANNED), "\n");
      for (i=0; i<sizeof(banned); i++)
         if (lower_case(str) == banned[i])
         {
            notify_fail(capitalize(str) +
			" has already been censured.\n");
            return 0;
         }
   }
   write_file(BANNED, lower_case(str) + "\n");
   tell_room(environment(TP), capitalize(str) +
             " has been censured from the Ancient Mystic Order.\n");
   tell_room(environment(TP), 
        "A shadow arises, within it the spirits of judgement.\n" +
        "Voices from within the cloud cry out: " +
        capitalize(str) + " shall be cursed before us!\n" +
        "The spirits, shadow and fog return to the nether reaches.\n");
   if (who && find_player(lower_case(str))) {
       who->catch_msg("You have been banned from " + GUILD + ".\n");
       who->set_rank(MYSTIC_TRAITOR);
       TP->remove_cmdsoul(MYSTIC_SOUL);
       ring = present(MYSTIC_RING, who);
       if (ring) {
         ring->remove_object();
         who->catch_msg("A spirit appears and takes away your ring.\n");
       }
       TP->update_hooks();
   }
   return 1;
}

void
create_room()
{
   lit = 0;

   set_short("Conclave");
   set_long(break_string("Shadows of the utter reaches of the world beckon "
    + "out to this place, the mystery and seclusion. Like some cloud "
    + "of unknowable darkness, this silent hall takes shape. "
    + "It is a small cryptic chamber, fashioned of dark stones "
    + "and is diamond in shape, its walls draped with curtains "
    + "and tapestries of deep red. A long table fashioned of "
    + "ebony sits in the middle of the room. Around it are many "
    + "chairs, some very unusual. A long black candle resides in "
    + "a silver holder in the center of the table. A small alcove houses "
    + "a beautiful crystal cruet. "
    + "A deep feeling permeates this chamber, a feeling of dread "
   + "and secrecy, of solemn vows and oaths.\n", 72));

   add_prop(ROOM_I_NO_TELEPORT, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_M_NO_MAGIC, 1);

   add_exit(GUILD_DIR + "chancery", "out", "@@leaves");
   add_cmd_item("candle", "light", "@@candle_lit");

   add_item("chairs", "There are seven ebony chairs with red cushions.\n"
  + "A large stone chair. A golden chair. A spiralled white chair.\n"
  + "An arcane ebony chair.\n");

   add_item("cruet", "It is a magnificent flask of cut crystal. It is etched\n"
  + "with mysterious symbols, stars and spirits. It contains\n"
  + "some kind of oil.\n");
   add_item("alcove", "It houses a crystal cruet.\n");
   add_item("candle", "It is very large, black as night.\n");
   add_item("holder", "It is silver and holds the black candle.\n");
   add_item("arcane ebony chair", 
    "It is a tall chair, carved intricately from a very rich and\n"
  + "deep black ebony. A silver moon rises like a crest over its\n"
  + "back, with mysterious symbols and runes carved under it.\n");
   add_cmd_item(({"arcane ebony chair", "arcane chair", "runes"}),
                "read", "@@grand");
   add_item("chair", "Which chair do you mean?");
   add_item("golden chair", "It is a chair made of cedar that has been\n"
  + "plated with gold. It has golden hawks carved into the\n"
  + "back, they have ruby eyes. The arm-rests take the shape\n"
  + "of noble cats, their eyes of star-emeralds. The letters\n"
  + "'Mrpr' are inscribed upon the chair.\n");
}

string
grand()
{
   return "Mumon, Patriarch of the Ancients\n";
}

candle_lit()
{
   if (lit == 0) {
      write("You light the candle.\n");
      say(QCTNAME(this_player()) + " lights the candle.\n");
      lit = 1;
      TO->add_prop(ROOM_I_LIGHT, 10);
      return 1;
   }
   write("The candle is already lit.\n");
   return 1;
}

void
enter_inv(object ob, object from)
{
   int stop=0;

   ::enter_inv(ob, from);

   if (MASTER_OB(from) != "/d/Terel/mecien/valley/guild/chancery")
   {
      write("That place has a mystic seal upon it.\n");
      stop=1;
   }
   if (!present("mystic_seal", TP))
   {
     write("You must enter through the ivory arch.\n");
     stop=1;
   }
   if (stop > 0)
   {
      ob->move_living("M", from);
   }
}

void
leave_inv(object ob, object to)
{
   object mseal;

   ::leave_inv(ob, to);

   mseal = present("mystic_seal", TP);
   if (mseal) {
      mseal->remove_object();
   }
}


leaves()
{
  write("You feel a burden lifted from you.\n");
  write("The Ancients are with you.\n");
  say(QCTNAME(this_player()) + " leaves through the curtains.\n");
}

query_prevent_snoop() { return 1;}

int
list_censured(string str)
{
   int i;
   string *banned;
   string foo, bar, msg;
   object who;

   notify_fail("You haven't the authority!\n");
   if (TP->query_mystic_rank() < MYSTIC_ARCHON) return 0;
   
   notify_fail("Whom do you intend to check?\n");
   if (strlen(str) && sscanf(str, "%s %s", foo, bar)) return 0;
   
   if (strlen(str)) {  
       who = find_player(lower_case(str));
       if (!who) who = "/secure/master"->finger_player(lower_case(str));
       if (!who) return 0;
   }
   
   notify_fail("No one is banned!\n");
   if (file_size(BANNED) <= 0) return 0;
   
   banned = explode(read_file(BANNED), "\n");
   if (!str) {
      msg = "These have been censured:";
      for (i=0; i<sizeof(banned); i++) msg += " " + capitalize(banned[i]);
      msg += ".\n";
   } else {
      if (member_array(str, banned) >= 0)
         msg = capitalize(str) + " has been censured.\n";
      else
         msg = capitalize(str) + " has not been censured.\n";
   }
   TP->catch_msg(msg);
   return 1;
}
