inherit "/std/room";
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>    
#include <filter_funs.h>                 /* filter functions */          
#include <options.h>
#include "/d/Krynn/open/room_tell.c"
 
#define     IS_RESTING       "_player_i_is_resting"
#define     REST_SUBLOC      "_subloc_resting"

int do_emote(string arg);

void
create_room()
{
   set_long("@@long_desc");
   set_short("Teth's den");
   add_item(({"fire","fireplace"}),
      "The heat from the shimmering fireplace makes you sleepy. " +
      "You are also enthralled by the dancing flames.\n");
   add_item(({"flame","flames"}),
      "The flames ebb and wane before your very eyes.\n");
   add_item(({"wooden box","box"}),
      "Carved into the cedar box are two roses with their stems entwined.\n");
   add_item(({"roses","carved roses"}),
      "One rose has small D-shapes embedded in it, the other has " + 
      "L-shapes.\n");
   add_item(({"bookshelf","bookshelves","shelves","books","tomes"}),
      "Both the bookshelves and tomes look interesting, but the room " +
      "makes you much too lazy to investigate any further.\n");
   add_item(({"bowl","bowl of milk","milk"}), "Perhaps Teth owns a cat " +
      "that likes milk? Whatever the case, the bowl is magically always " +
      "full of milk, a cat's delight! Do you have the urge to lap some?\n");
   add_item(({"couch","plush couch"}), "This plush couch looks like it " +
      "would be the perfect place to sit down, and have a chat. It also " +
      "appears to be a napper's heaven.\n");
   add_item(({"rug","fuzzy rug"}), "This rug is very inviting! It's made " +
      "from a soft fur, and is an excellent place to rest on, in front " +
      "of the fireplace.\n");
   add_item(({"tray","serving tray"}), "This serving tray contains both " +
      "jasmine tea and hot chocolate. You are too comfortable to get " +
      "some, but maybe you could wish for it?\n");

   INSIDE;

   add_prop(ROOM_I_LIGHT, 10);

   set_tell_time(180);
   add_tell("The fire flickers and crackles.\n");
   add_tell("SZZZZsssss hisses a burning log in the fire.\n");
   add_tell("The warmth in the room makes you feel very comfortable, and " +
       "very relaxed.\n");
   add_tell("Light plays about the room, as shadows emerge and hide with " +
       "the flickering of the flames in the fire.\n");
   add_tell("Sparks swirl their way up the chimney in the fireplace.\n");
   add_tell("The scents of jasmine tea and hot chocolate caress your " +
       "nose.\n");

   add_exit("/d/Krynn/solamn/vkeep/startroom", "vkeep");
   add_exit("/d/Genesis/start/human/town/tower", "sparkle");
   add_exit("/d/Krynn/teth/testroom", "north");
   add_exit("/d/Krynn/wayreth/tower/yard02", "wohs");

   add_my_desc("@@rug_desc@@", this_object());
}

void
init()
{
  ::init();
  ADD("do_rise", "rise");
  ADD("do_rest", "rest");
  ADD("do_rise", "stand");
  ADD("do_lap", "lap");
  ADD("do_emote", "emote");
  ADD("do_emote", ":");
  ADD("do_wish", "wish");

}

nomask static int
do_emote(string arg)
{
    NF("Emote what?\n");
    if (!arg)
        return 0;
    say(QCTNAME(TP) + " " + arg + "\n");
    if (TP->query_option(OPT_ECHO))
        write("You emote: " + TP->query_name() + " " + arg + "\n");
    else
        write("Ok.\n");
    return 1;
}

nomask static int 
do_lap(string str)
{
    if ((str=="milk")||(str=="bowl of milk"))
      {
        write("Mmmmmmm, that milk is yummy! Perfect for cats.\n");
        say(QCTNAME(TP)+ " laps milk from the bowl and looks very pleased.\n");
        return 1;
      }
    NF("Lap what?\n");
    return 0;
}

nomask static int
do_wish(string str)
{
    seteuid(getuid());

    if ((str=="for chocolate")||(str=="for hot chocolate"))
      {
        clone_object("/d/Krynn/teth/obj/hot_choc")->move(TP);
        write("You wish for a hot chocolate, and suddenly one appears " +
          "in your hands!\n");
        say(QCTNAME(TP)+ " wishes for something and receives it!\n");
        return 1;
      }
    if ((str=="for tea")||(str=="for jasmine tea"))
      {
        clone_object("/d/Krynn/teth/obj/tea")->move(TP);
        write("You wish for a jasmine tea, and suddenly one appears " +
          "in your hands!\n");
        say(QCTNAME(TP) + " wishes for something and receives it!\n");
        return 1;
      }
     NF("Wish for what?\n");
     return 0;
}

void
leave_inv(object ob, object to)
{

  if (this_player()->query_prop(IS_RESTING))
  {
    this_player()->remove_prop(IS_RESTING);
    this_player()->remove_subloc(REST_SUBLOC);
  }

}

/* 
 * Code for rug
 */
nomask static int
do_rest(string str)
{
  object *pl;
  int i;
 
  pl = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
  pl = filter(pl, "filter_resting_on_rug", this_object());
 
  NF("Rest where?\n");

  if (str && str != "rug" && str != "on rug" &&
      str != "on the rug" && str != "down")
    return 0;
 
  NF("You are already resting, relax!\n");
  if (this_player()->query_prop(IS_RESTING))
    return 0;
  else
  {
    this_player()->add_prop(IS_RESTING, 1);
    write("You sink down onto the fuzzy rug, and relax.\n");
    say(QCTNAME(this_player()) + " sinks down onto the warm fuzzy " +
    "rug.\n");
  }
  this_player()->add_subloc(REST_SUBLOC, this_object());
  return 1;
}        

nomask static int
do_rise(string str)
{

 
  NF("Rise from where?\n");
  if (str && str != "rug" && str != "from rug")
    return 0;
 
  NF("You are already standing.\n");
  if (!this_player()->query_prop(IS_RESTING))
    return 0;
 
  else
  {
    this_player()->remove_prop(IS_RESTING);
    /*this_player()->unset_no_show_composite();*/
    this_player()->remove_subloc(REST_SUBLOC);
    write("You barely manage to get up from the comfortable rug.\n");   
    say(QCTNAME(this_player()) + " struggles getting up from the rug.\n");
  }
  return 1;
}

  
static int
filter_resting_on_rug(object pl)
{
  return pl->query_prop(IS_RESTING) == 1;
}
 
static int
filter_remove_rest(object pl)
{
  /*pl->unset_no_show_composite();*/
  return 1;
}
 
static int
filter_add_rest(object pl)           
{
  /*pl->set_no_show_composite(1);*/
  return 1;
}

 
static string
map_live(object pl)
{
  if (pl == this_player())
    return "you";
  return pl->query_the_name(this_player());
}
 
nomask string
rug_desc()
{
  object *pls;
  string *who, str = "";
  int i;
 
  pls = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());           
  pls = filter(pls, "filter_resting_on_rug", this_object());
  filter(pls, "filter_remove_rest", this_object());
 

  who = map(pls, "map_live", this_object());
  filter(pls, "filter_add_rest", this_object());
  if (sizeof(pls) == 1 && pls[0] == this_player())
    str += " You are relaxing on the rug.";
  else if (sizeof(pls) > 1)
    str += " " + capitalize(COMPOSITE_WORDS(who)) +
      " are relaxing on the rug.";
 
  else if (sizeof(pls))
    str += "" + capitalize(COMPOSITE_WORDS(who)) +
      " is relaxing on the rug.";
 
  str += "\n";
  return break_string(str, 70); 
}
 
nomask string
show_subloc(string subloc, object on, object for_pl)
{


  string str;
 
  if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != REST_SUBLOC)
    return "";
  if (for_pl == on)
    str = "You are";
  else
    str = capitalize(on->query_pronoun()) + " is";
}                                
 

string
long_desc()
{
   return "You have entered what appears to be a cozy den. " +
   "It is hard to believe that Teth actually gets any work done here, " +
   "because you even feel yourself dozing off. A warm fire crackles " +
   "and flickers in front of you. An extremely plush couch that would " +
   "love to hold you in its embrace looks inviting. A bowl of milk rests " +
   "in a corner, near the fireplace. After a closer inspection, " +
   "you can't help but notice an ornately crafted wooden box and " +
   "bookshelves which sag under weighty tomes. A fuzzy rug, made of " +
   "soft fur, stretches out in front of the fireplace. A serving tray " +
   "can be seen at the far end of the room.\n";
}

static int
query_prevent_snoop()
{
    return 1;
}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}

