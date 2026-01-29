// kn1  Conclave Wait Room
// Grace  Dec 1994

// Thanks to Plugh for his generous help with the chairs.

// Changed this room so that the conclave is taken from the save file
// automatically. 01/02/96 ~Aridor


#include "../local.h"
#include <cmdparse.h>
#include <composite.h>

inherit SPURRM;

#define     IS_SITTING      "_player_i_is_sitting"
#define     SIT_SUBLOC      "_subloc_sitting"

/* Player names should NEVER be hardcoded like this!!
#define     CRN             "diri"
#define     SRD             "ladindell"
#define     RSE             "zaeah"
*/

#define     ROSE            ({ROOM + "kn5", ROOM + "void"})
#define     SWORD           ({ROOM + "kn4", ROOM + "void"})
#define     CROWN           ({ROOM + "kn3", ROOM + "void"})

string crown_desc();
string sword_desc();
string rose_desc();

object* keys = ({0,0,0,0,0,0});
string crown;
string sword;
string rose;


void
create_spur_room()
{
   clone_object(SOBJ + "crown_a")->move(TO);
   clone_object(SOBJ + "sword_a")->move(TO);
   clone_object(SOBJ + "rose_a")->move(TO);

   SHORT("A large waiting room");
   LONG("A large, comfortably-appointed waiting room.\n"+
      "   The walls are draped with brocaded silks in an array of blue "+
      "hues.  A fire burns merrily in the grate of the fireplace lining "+
      "the south wall.  Chairs and foot-stools surround it, "+
      "providing ample seating for relaxing Knights. The "+
      "floor is parquet and reflects the mellow glow of the "+
      "fire.  There are three windows, one alongside each "+
      "door, and archway leading east.\n");       

   
   add_exit(ROOM + "pass1l3", "east", 0);
   set_noshow_obvious(1);
   
   AI(({"silk", "silks", "hangings", "wall", "walls", "brocade"}),
      "The silks are thick and soft. Fanciful dragons, minotaurs, "+
      "and kingfisher birds have been woven into the fabric with "+
      "fine strands of highest quality platinum.\nA break in the "+
      "hangings on the north wall reveals a small doorway.\n");
   ACI(({"silk", "silks", "hangings", "wall", "walls", "brocade"}),
      ({"get", "pull", "take", "tear", "rip"}),
      "You realize that you are standing with your hands raised "+
      "and cannot remember why. All thoughts seem to have fled "+
      "from your mind.\n");
   ACI(({"silk", "silks", "hangings", "wall", "walls", "brocade"}),
      ({"cut", "slash", "damage", "defile"}),
      "An unpleasant tingling feeling flows upward from your "+
      "hands and wraps around your heart. Fear wells within "+
      "you. You cannot continue with this course of action. "+
      "Your hands fall away from the silks.\n");
   AI(({"fireplace", "grate"}), "One of the largest you have seen. "+
      "It is made of the same dark stone as the rest of the Knigh"+
      "ts' Spur. The lintel is unadorned and high enough to allow"+
      " a tall man to pass without bowing his head.\n "+
      "It has a fire burning in it.\n");
   ACI(({"fireplace", "grate"}), "enter", "Why on earth would you "+
      "want to do that! There's a fire in there!\n");
   AI(({"fire", "flames"}), "It is burning merrily, consuming huge "+
      "logs and throwing off delicious heat.\n");
   AI(({"window", "windows"}),
       "There are three windows in this room, one each "+
       "for seeing into the Crown, Sword, and Rose Conclave rooms.\n"+
       "To see into one of them, use <view (crown, sword, or rose)>.\n"+
       "To seek an audience with a High Knight, use <seek (crown, "+
       "sword, or rose)>. You may also <seek guildmaster> to ask the guildmaster(s) "+
       "for an audience.\n");
    AI(({"floor","parquet floor"}),"A hardwood floor that reflects " +
        "the soft glow of the fire.\n");

   add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");
   add_my_desc("@@chair_desc@@", this_object());
   
   set_tell_time(200);
   add_tell("The log in the grate shifts position in a shower of sparks.\n");
   add_tell("The flames flicker, casting odd shadows on the walls.\n");
   add_tell("The wall-hangings sway in the current of warm "
      + "air wafting from the hearth.\n");
   
   restore_object(ADMIN_FILE);
}


nomask void
init()
{
   ::init();
    ADD("do_pass", "north");
    ADD("do_pass", "n");
    ADD("do_sit", "sit");
    ADD("do_rise", "rise");
    ADD("do_rise", "stand");
    ADD("do_view", "view");
    ADD("do_roast", "warm");
    ADD("do_roast", "toast");
    ADD("do_roast", "roast");
    ADD("do_seek", "seek");
}

void
enter_inv(object ob, object from)
   {
       start_room_tells();
       ::enter_inv(ob, from);

       if (ob->query_knight_sublevel() != 11)
          return;

       if (ob->query_knight_level() == 3)
	 set_alarm(0.0, 0.0, "give_key", ob);
       else if (ob->query_knight_level() == 4)
	 set_alarm(0.0, 0.0, "give_key", ob);
       else if (ob->query_knight_level() == 5)
	 set_alarm(0.0, 0.0, "give_key", ob);
   }

void
leave_inv(object ob, object to)
{
   if (this_player()->query_prop(IS_SITTING))
      {
      this_player()->remove_prop(IS_SITTING);
      this_player()->unset_no_show_composite();
      this_player()->remove_subloc(SIT_SUBLOC);
      }
}

nomask string
wizinfo()
{
   return "This is where those wanting to speak to the Conclave can"+
   " wait.\nKeys to the doors are cloned to the Conclave members as "+
   "they enter this room. Only Conclave members and Guildmasters "+
   "may possess the keys.\nCrown Key: /d/Krynn/solamn/hctower/spur"+
   "/obj/crn_key\nSword Key: /d/Krynn/solamn/hctower/spur/obj/swd_key"+
   "\nRose key: /d/Krynn/solamn/hctower/spur/obj/rose_key\n";
}

int
do_pass()
{                                                               
   write("You walk north, past the silk wall-hangings.\n");
   TP->move_living("into the silks hanging on the north wall", ROOM + "kn2", 0, 0);
   set_dircmd("wall");
   return 1;
}    

int
do_roast(string str)
{
     if ((str == "self") || (str == "myself") || (str == "me"))
        {
           write("You warm yourself before the fire.\n");
           say(QCTNAME(TP) + " warms " + TP->query_objective() +
              "self before the fire.\n");
           return 1;
        }
   if ((str == "hand") || (str == "hands"))
        {
           write("You warm your hands near the fire.\n");
           say(QCTNAME(TP) + " warms " + TP->query_possessive() +
              " hands near the fire.\n");
           return 1;
        }
   if ((str == "bottom") || (str == "buns"))
        {
           write("You warm your bottom near the fire.\n");
           say(QCTNAME(TP) + " exposes " + TP->query_possessive() +
              " bottom and warms it near the fire.\n");
           return 1;
        }
   else
      if (str)
         {
            write("You warm your " + str + " near the fire, "+
                 "hoping it won't be burned.\n");
            say(QCTNAME(TP) + " tries to warm " + TP->query_possessive() +
                 " " + str + " over the fire. You hope it doesn't burst into "+
                 "flames.\n");
            return 1;
         }
   NF("Warm what?\n");
   return 0;
}


int
do_view(string str)
{
   if (str == "crown")
      {
         TP->catch_msg(crown_desc());
         return 1;
       }
    else
      if (str == "sword")
         {
         TP->catch_msg(sword_desc());
         return 1;
         }
   else
      if (str == "rose")
         {
         TP->catch_msg(rose_desc());
         return 1;
         }
   NF("Which window would you like to view? crown, sword, or rose?\n");
   return 0;
}

public int
do_seek(string str)
{
    int i,succ;
    object gm;

    if (!str)
    {
        write("Seek an audience with which one? Seek crown, "+
            "sword, rose, or guildmaster.\n"); 
    }
    if ((str == "crown") || (str == "an audience with crown")) 
    {           
        if (find_player(L(crown)))
        {
            write("The High Knight of the Crown Order now knows that "+
                "you seek an audience.\n"); 
            tell_object(find_player(L(crown)),"\n     "+
                this_player()->query_name() + 
                " seeks an audience with you in the Knights' Spur.\n\n");
            return 1;
        }
        write("The High Knight of the Crown is not where you seek. "+
            "Perhaps you should try again later?\n");   
        return 1;
    }
    if ((str == "sword") || (str == "an audience with sword"))
    {
        if (find_player(L(sword)))
        {
            write("The High Knight of the Sword now knows that you "+
                "seek an audience.\n");
            tell_object(find_player(L(sword)),"\n     "+
                this_player()->query_name() + 
                " seeks an audience with you in the Knights' Spur.\n\n");
            return 1;
        }
        write("The High Knight of the Sword is not where you seek. "+
            "Perhaps you should try again later?\n");
        return 1;
    }
    if ((str == "rose") || (str == "an audience with rose"))
    {
        if (find_player(L(rose)))
        {
            write("The High Knight of the Rose now knows that you "+
                "seek an audience.\n");
            tell_object(find_player(L(rose)),"\n     "+
                this_player()->query_name() + 
                " seeks an audience with you in the Knights' Spur.\n\n\n");
            return 1;
        }
        write("The High Knight of the Rose is not where you seek. "+
            "Perhaps you should try again later?\n");
        return 1;
    }
    if ((str == "guildmaster") || (str == "an audience with the guildmaster"))
    {
        succ=0;
        for(i=0;i<sizeof(GUILDMASTERS);i++)
	{
	  gm = find_player(L(GUILDMASTERS[i]));
	  if (gm && !(gm->query_prop(WIZARD_I_BUSY_LEVEL) & 156))
	  {
	    gm->catch_msg("\n******************\n"+
			this_player()->query_name() + 
			" seeks an audience with you at the Knights' Spur.\n\n\n");
	    succ=1;
	  }
	}
	if (succ)
	  write("Someone up there now knows that you seek an audience.\n");
	else
	  write("There is currently no one up there to hear you. "+
		"Perhaps you should try again later?\n");
        return 1;
    }
 
    write("If what you seek isn't crown, sword, rose, or guildmaster, then you "+
        "are seeking in the wrong place.\n");
    return 1;
}
void
give_key(object ob)
{
    int lvl = ob->query_knight_level();
    string key_file;
    if (lvl == 3)
      key_file = "crn_key";
    else if (lvl == 4)
      key_file = "swd_key";
    else if (lvl == 5)
      key_file = "rose_key";
    else
      return;
    seteuid(getuid());
    if (!keys[lvl] && ob && E(ob) == TO)
      {
	  keys[lvl] = clone_object(SOBJ + key_file);
	  keys[lvl]->move(ob);
     ob->catch_msg("\nSuddenly, an ornate key appears in your hand!\n");
      }
}

nomask static int
do_sit(string str)
{
   object *pl;
   int i;
   
   pl = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
   pl = filter(pl, "filter_sitting_in_chair", this_object());
   
   NF("Footstools are for resting feet on.\n");
   if (str && str == "footstool" && str == "stool")
      return 0;
   
   NF("Sit where?\n");
   if (str && str != "chair" && str != "in chair" && 
         str != "on chair" && str != "down")
   return 0;
   
   NF("You cannot sit in two chairs at once!\n");
   if (this_player()->query_prop(IS_SITTING))
      return 0;
   else 
      {
      this_player()->add_prop(IS_SITTING, 1);
      write("You sit in one of the fireside chairs.\n");
      say(QCTNAME(this_player()) + " sits in one of the chairs "+
         "near the fire.\n");
   }
   this_player()->set_no_show_composite(1);
   this_player()->add_subloc(SIT_SUBLOC, this_object());
   return 1;
}

string 
crown_desc()
{
  string *roomfiles;
  object *inv, *live, room;
  int i;

  roomfiles = CROWN;
  inv = ({});
  for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

  if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
    if (sizeof(live) > 0)
      return ("In that room you can see " +
              COMPOSITE_LIVE(live) + ".\n");
    }
    return ("At present, the room appears to be unoccupied.\n");
}

string 
sword_desc()
{
  string *roomfiles;
  object *inv, *live, room;
  int i;

  roomfiles = SWORD;
  inv = ({});
  for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

  if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
    if (sizeof(live) > 0)
      return ("In that room you can see " +
              COMPOSITE_LIVE(live) + ".\n");
    }
    return ("At present, the room appears to be unoccupied.\n");
}

string 
rose_desc()
{
  string *roomfiles;
  object *inv, *live, room;
  int i;

  roomfiles = ROSE;
  inv = ({});
  for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

  if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
    if (sizeof(live) > 0)
      return ("In that room you can see " +
              COMPOSITE_LIVE(live) + ".\n");
    }
    return ("At present, the room appears to be unoccupied.\n");
}

nomask static int
do_rise(string str)
{
   
   NF("Rise from where?\n");
   if (str && str != "chair" && str != "from chair")
      return 0;
   
   NF("You are already standing.\n");
   if (!this_player()->query_prop(IS_SITTING))
      return 0;
   
   else 
      {
      this_player()->remove_prop(IS_SITTING);
      this_player()->unset_no_show_composite();
      this_player()->remove_subloc(SIT_SUBLOC);
      write("You get up from the chair.\n");
      say(QCTNAME(this_player()) + " gets up from the chair.\n");
   }
   return 1;
}


static int
filter_sitting_in_chair(object pl)
{
   return pl->query_prop(IS_SITTING) == 1;
}

static int
filter_remove_sit(object pl)
{
   pl->unset_no_show_composite();
   return 1;
}

static int
filter_add_sit(object pl)
{
   pl->set_no_show_composite(1);
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
chair_desc()
{
   object *pls;
   string *who, str = "";  
   int i;
   
   pls = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
   pls = filter(pls, "filter_sitting_in_chair", this_object());
   filter(pls, "filter_remove_sit", this_object());
   
   who = map(pls, "map_live", this_object());
   filter(pls, "filter_add_sit", this_object());
   if (sizeof(pls) == 1 && pls[0] == this_player())
      str += " You are sitting in one of the fireside chairs.";
   else if (sizeof(pls) > 1)
      str += " " + capitalize(COMPOSITE_WORDS(who)) +
   " are sitting in " + LANG_WNUM(sizeof(pls)) + 
   " of the fireside chairs.";
   
   else if (sizeof(pls))
      str += " " + capitalize(COMPOSITE_WORDS(who)) +
   " is sitting in one of the fireside chairs.";
   
   str += "\n";
   return break_string(str, 70);
}


nomask string
show_subloc(string subloc, object on, object for_pl)
{
   string str;
   
   if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
         subloc != SIT_SUBLOC)
   return "";
   if (for_pl == on)
      str = "You are";
   else
      str = capitalize(on->query_pronoun()) + " is";
}

