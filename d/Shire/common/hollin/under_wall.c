#include "outroom.h"

#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

static int door_status;
int alarm_id;
string race_name;
string race_name;

#define OPENED 0
#define CLOSED 1
#define SEIZED 2

#define STAND_MINES  STAND_PARENT + "mines/"

#define WALL_NAMES   ({ "rock", "wall", "stone", "design" })
#define LETTER_NAMES ({ "chars", "letters", "characters", "arch", "lines" })
#define GATE_NAMES   ({ "portal", "door", "stair", "stairs", "gate" })

#define ALL_NAMES    (WALL_NAMES + LETTER_NAMES + GATE_NAMES)

#define ELF_NAMES_PL (["dwarf":"naugrim", "elf":"quendi", "human":"edain",\
      "hobbit":"suzin", "goblin":"glamhoth", "gnome":"alwin"])
#define ELF_NAMES_S  (["dwarf":"khazad", "elf":"pened", "human":"firen",\
      "hobbit":"perian", "goblin": "yrch", "gnome":"piryrch"])
#define MORIA_ROOM "/d/Shire/moria/mines/stair0"

// Prototypes
void say_friend(object who);


create_outroom() {
   set_short("@@my_short@@");
   set_long("@@my_long@@");
   door_status = OPENED;
   
   ITEM(WALL_NAMES,   "@@exa_wall");
   ITEM(LETTER_NAMES, "@@exa_letters");
   ITEM(GATE_NAMES,   "@@exa_gate");
   ITEM( ({"crown","anvil","hammer","seven stars","stars"}),
      "The anvil and hammer surmounted by a crown with seven stars "+
      "are the emblems of Durin the King.\n");
   ITEM( ({"trees","two trees"}),
      "These are the Trees of the High Elves.\n");
   ITEM( "star", "It is the Star of the House of Feanor.\n");
   CMD_ITEM(WALL_NAMES, ({"kick","climb","smash","read" }),
      ({"It has no effect.\n",
            "The wall is too smooth to climb.\n",
            "Smashing the wall has no effect.\n",
            "Read what?? Try to be a bit more specific.\n"
       }) );
   CMD_ITEM(LETTER_NAMES, "read", "@@read_wall");
   CMD_ITEM(GATE_NAMES, "enter","@@enter");
   CMD_ITEM(({"star"}),({"touch", "feel"}),
      ({"You touch it. It radiates power, but nothing seems to happen.\n",
            "You feel it. But nothing happens.\n"}));
   
   NORTH("tree_n");
   WEST( "in_front");
   SOUTH("tree_s");
   add_exit(MORIA_ROOM, "east", 0, 3);
//   add_exit(MORIA_ROOM, "east", "@@block_room@@");
   add_prop("_steed_as_no_enter", ({ "east" }));
}

reset_room() {
   door_status = OPENED;
}

init() {
   ::init(); /* Must be done in rooms. */
   add_action("my_say","say");
   add_action("my_say","'",1);
   add_action("my_say","yell");
   add_action("my_say","shout");
   add_action("my_say","speak");
   add_action("do_ponder","ponder");
   add_action("do_ponder","consider");
}

my_short() {
   if(door_status == OPENED)
      return "Western Gate of Moria";
   else
      return "Under a polished vertical wall";
}

my_long() {
   string s;
   
   s = "You are standing under a polished vertical wall. ";
   
   switch(door_status) 
   {
      case CLOSED:
      if(night()) 
         s += "As the moon shines upon the grey face of the rock, faint lines appear, "+
      "like slender veins of silver running in the stone. At first they are "+
      "no more than pale gossamer-threads, so fine that they only twinkle "+
      "fitfully where the moon catch them, but steadily they grow broader "+
      "and clearer, until their design can be guessed! ";
      else 
         s +=
      "From here you see that you can not travel further east, barred "+
      "by the immense wall in front of you. Neither cracks not joints "+
      "can be seen on it, so it seems impossible to climb. In the north "+
      "and the south you can see two trees almost like an archway into "+
      "the wall here, though the southern seems quite stunted, and "+
      "seems to have reached its peak of growth a long time ago. To the "+
      "west there is a plain in front of a dark and forbidden looking lake. ";
      break;
      case SEIZED:
      s += "Up along the wall several tentacle arms firmly seize the door!! ";
      break;
      case OPENED:
      s = "You are standing under an opened door into the Mines of Moria. "+
      "Through the opening a shadowy stair can be seen climbing steeply up, "+
      "but beyond the lower steps the darkness is deeper than the night. ";
      break;
   }
   return s;
}

varargs string 
elvish_for(string *ret) 
{
   string s=ELF_NAMES_S[race_name];
   object *pl;
   int i;
   string rname;
   
   pl = FILTER_LIVE(all_inventory(TO));
   i = sizeof(pl);
   while (i--) {
      rname = pl[i]->query_race_name();
      if (rname != race_name)
         return "gwaithrim";
   }
   if (sizeof(pl) > 1)
      return ELF_NAMES_PL[race_name];
   
   if (strlen(s)) 
      return s;
   else 
      return "mellon";
}

string
exa_wall() 
{
   say(QCTNAME(this_player())+" studies the wall.\n");
   /*
   switch(door_status) {
      case CLOSED:
      */
      if(night()) return
         "At the top, as high up as you can reach, is an arch of interlacing\n"+
      "letters in an Elvish character. Below, though the threads are in places\n"+
      "blurred or broken, the outline can be seen of an anvil and a hammer\n"+
      "surmounted by a crown with seven stars. Beneath these again are\n"+
      "two trees, each bearing crescent moons. More clearly than all else\n"+
      "there shines forth in the middle of the door a single star with many\n"+
      "rays.\n";
      else return
         "The wall twinkles in the sharp light, polished through years of "+
      "constant ice and water. No crack nor joint can be seen on it, "+
      "impossible to climb even for the superiour masters of that art.\n";
      
      /*
      case OPENED: return
      "An opening in the wall can be seen here, although you couldn't see a\n"+
      "crack nor joint in the rock before. Through the Gate of Moria you can see\n"+
      "only a shadowy stair climbing steeply into darkness.\n";
      
      case SEIZED: return
      "The Gate of Moria is seized by the arms of the Watcher!!\n"+
      "You stand helplessly in between the slimy arms and the Gate.\n";
   }
   */
}

string
exa_letters() 
{
   string s;
   string *race_ret;
   
   if(!night())
      return "What?\n";
   
   switch(door_status) 
   {
      case CLOSED:
      case SEIZED:
      elvish_for(race_ret);
      if(WIS(TP)>50 || TP->query_skill(SS_LANGUAGE)>10)
         s = "Here is written in the Feanorian characters\n"+
      "according to the mode of Beleriand:\n"+
      "\n"+
      "    Ennyn Durin Aran Moria:\n"+
      "    Pedo "+race_ret[0]+" a minno.\n"+
      "    Im Narvi hain echant:\n"+
      "    Celebrimbor o Eregion\n"+
      "    teithant i thiw hin.\n\n"+
      "You can now see that it is inscribed in Ithildin, that mirrors only starlight\n"+
      "and moonlight. ";
      else 
         return
      "You try to figure out what those strange letters really mean,\n"+
      "but you are either too uneducated or too unskilled in languages\n"+
      "to understand what here is written.\n";
      
      if (TP->query_skill(SS_LANGUAGE)>30)
         s+= "They say simply:\n\n"+
      " 'The Doors of Durin, Lord of Moria.\n"+
      "  Speak, "+race_ret[1]+", and enter.\n"+
      "  I, Narvi, made them.\n"+
      "  Celebrimbor of Hollin drew these signs.\n"+
      "\nYou probably have to say a password to enter.\n";
      else
         s+= "Though you can read this text using your elemental knowledge\n"+
      "of words, you just can't figure out the meaning of the text.\n"+
      "Though something is clear. Durin, Moria, Narvi, Celebrimbor\n"+
      "and Eregion must be names, that is for sure.\n";
      
      s += "You might consider these names in the text.\n";
      return s;
      case OPENED:
      return "The doors are open and leads east into the mountain!\n";
   }
}

int
read_wall(string what)
{
   if (!night())
      return notify_fail("Read what?\n");
   write(exa_letters());
   return 1;
}

string
exa_gate() {
   switch(door_status) {
      case CLOSED:
      return "Which gate??\nYou can't see any gate here, so why do you think there is one here?\n";
      case OPENED:
      return "The gate leads into the Mines of Moria.\n";
      case SEIZED:
      return "The gate is seized by some tentacles!\n";
   }
}

enter() {
   if(door_status==OPENED) 
      {
      
      write("You run headlong into the darkness of the mountain.\n");
      say(QCTNAME(TP)+" runs east into the mountain.\n", TP);
      TP->move_living("M", MORIA_ROOM,1);
      return 1;
   }
   notify_fail("Walk into the wall you mean?!?\n");
   return 0;
}

#define notify(str)     tell_room(TO, str + "\n");

int
my_say(string str) {
   string right_word = elvish_for();
   string verb = query_verb();
   
   if (verb[0..0]=="'")
      str = verb[1..strlen(verb)-1]+(strlen(str)?str:"");
   
   if (!strlen(str)) 
      return 0;
   
   str = lower_case(str);
   
   if (strlen(str) >= strlen(right_word) &&
         lower_case(str[0 .. strlen(right_word)-1]) == right_word)
   alarm_id = set_alarm(4.0, 0.0, "say_mellon");
   if (str=="mellon"||str=="friend"||lower_case(str)==TP->query_race_name())
      set_alarm(4.0, 0.0, &say_friend(TP));
   return 0;
}

say_mellon() 
{
   remove_alarm(alarm_id);
   if (!night())
      return 0;
   
   if(door_status==CLOSED) {
      door_status = OPENED;
      notify("Suddenly the star shines out briefly and fades again. Then silently");
      notify("a great doorway gets outlined, though not a crack or joint has been visible");
      notify("before. Slowly it divides in the middle and swings outwards inch by inch,");
      notify("until both doors lay back against the wall.");
      TO->open_door();
     /* set_alarm(10.0,0.0,"start_watcher"); ---  for nothing happens --- */
   }
   else if (door_status==SEIZED) {
      notify("Suddenly the star shines out and fades again. A crack is heard,");
      notify("and a great doorway is outlined, but then the Watcher stops the");
      notify("movement! The doorway is firmly seized by it!\n");
   }
}

say_friend(object who) {
   if(door_status==CLOSED && present(who,this_object())) {
      notify("Suddenly the star shines out briefly, but fades again.");
      write("You have the feeling that you were close to solving "+
         "the riddle of getting into the Mines of Moria.\n");
   }
}

void
open_door()
{
   door_status = OPENED;
   add_exit(MORIA_ROOM,"east",0);
}

int
do_ponder(string what)
{
   what = lower_case(what);
   
   switch(what) 
   {
      case "durin":
      if(WIS(TP)>25)
         write("Hm, well Durin was the dwarven king in Khazad-dum wasn't he?\n");
      else
         write("No, you couldn't ponder on who that might be.\n");
      return 1;
      case "moria":
      case "khazad-dum":
      if(WIS(TP)>10 || TP->query_skill(SS_LOC_SENSE)>6) {
         write("Ah! Moria! Khazad-dum! That is the name of the dwarven underground\n");
         write("city Dwarrow-delf east of these doors of Durin.\n");
          } else
         write("Hmm. Now didn't you hear that name somewhere.. Hmm..");
      return 1;
      case "dwarrow-delf":
      write("Well, it is an ancient city of dwarves. But that is all you can tell.\n");
      return 1;
      case "narvi":
      if(WIS(TP)>25)
         {
         write("Narvi was a famous dwarven door-crafter. He was known to make beautiful\n");
         write("enchanted and magical locks and doors several centuries ago.\n");
          }
      else
         write("You don't seem to recall that name.\n");
      return 1;
      case "hollin":
      case "eregion":
      if(WIS(TP)>40 || TP->query_skill(SS_LOC_SENSE)>8) {
         write("Hollin is the area west of the Misty Mountains and south of the\n");
         write("Great EASTroad. It is called Eregion in ancient elvish and dwarfish.\n");
          } else {
         write("Now isn't that name familiar?? Well, then what is it??\n");
          }
      return 1;
      case "celebrimbor":
      if (WIS(TP)>75 || TP->query_skill(SS_LANGUAGE)>30) {
         write("Celebrimbor was a famous elven artist and writer. He usually made\n");
         write("incredibly nice looking texts in all kinds of materials.\n");
         write("You recognize the style and layout of him on the wall.\n");
          } else
         write("He seems completely unknown to you.\n");
      return 1;
      default:
      return 0;
   }
}

int
block_room()
{
if (this_player()->query_wiz_level()) return 0;

write("The gate is closed, preventing entrance to the mines.\n");
return 1;
} 
