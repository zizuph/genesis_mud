/* huntclub_joinrm.c - Tomas/Finwe, November 2017
* 
*  Modifications:
*     added rumbald -- Tomas December 3, 2017
*     added AG guild skills -- Tomas December 6, 2017
*/


inherit "/lib/guild_support";
inherit "/d/Shire/room";
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";


#include "/d/Shire/common/defs.h"
#include "huntclub.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/d/Shire/bits.h"
#include "/sys/money.h"
#include <std.h>

//store support
#include "/d/Shire/clubs/huntclub/huntclub_shop_items.c"
#define STORE_ROOM (HUNTCLUB_DIR + "huntclub_shop_store")


#define NUM         sizeof(query_money_types(-1))
#define CLOSED      0    /* 1 = closed,   0 = open.  */



/* Prototypes */
int do_join(string str);
int do_abandon(string str);
int do_tallystick(string str);
int check_member();
int closed;

static void create_board();

object rumbald;

void set_up_skills();


void
create_room()
{
    object board;
    
    closed = CLOSED; 
    
    
    set_short("Hunters Lodge, home of the Hunter's/Huntress' Club");
    set_long("You're standing in the foyer of a large hall within the hunting lodge. " +
       "Supple leather armchairs and dark stained tables are arranged around a massive " +
       "dual-sided fireplace located in the center of the hall. Warm looking fur rugs " +
       "can be seen resting over tightly fitted oak floorboards. Well lit antler " +
       "chandeliers hang from an ornately carved beamed cathedral ceiling. Large " +
       "shuttered windows set within the walls by the door. Many heads of various " +
       "animals are mounted on a trophy wall on the west wall. There's a bulletin " +
       "board posted on the wall amongst the heads. You also notice large " +
       "wicker basket containing long white objects sitting on one of the tables.\n");
       
    add_item(({"lodge", "hunters lodge"}),
        "You are standing in a large hunters lodge.\n");
    
    add_item(({"table", "tables"}),
    	"Sever dark stained tables can be seen near the chairs. The appear to be strong " +
    	"enough to stand on. There's a large wicker basket on one of the tables.\n");
    
    add_item(({"heads", "animals","trophies"}),
        "Taxidermy at finest. Various animal heads mounted on backboards, and mounted " +
        "on the western wall.\n");
    
    add_item("poster", "A solid piece of polished oak, with intricately carved borders. " +
        "There's writing on it. Perhaps you can 'examine' it.\n");
        
    add_item(({"windows", "shuttered windows"}),
        "Large windows set deep within the walls by the doors. Heavy shutters with " +
        "arrow slits, currently cover the windows.\n");
    
    add_item(({"basket", "wicker basket"}),
        "Just a plain wicker basket. There's a brass plaque on the side.\n");
    
    add_item(({"white objects", "objects"}),
        "They look like sticks, or perhaps bones.. There's a plaque on the basket " +
        "that might help explain what they are.\n");
    
    add_item(({"plaque","sign"}),
        "Its a brass plaque tied to the basket. Perhaps you can read it.\n");
    
    add_item(({"chairs", "chairs", "arm chair", "armchairs"}),
        "Plush leather high backed arm chairs arranged around the fireplace, for weary " +
        "hunters to sit on.\n");
        
    add_item(({"chandeliers","chandelier"}), 
        "Rustic multi-tiered antlers, holding at least 20 lit candles extend from the ceiling. "+
        "Two giant racks are mounted at either ends above the fireplace hearth.\n");
        
    add_item(({"candles"}),
        "Large white candles are arranged within the chandeliers, providing warm light "+
        "throughout the hall.\n");
        
	add_item(({"carvings","ornately carved","beams","beamed","cathedral", "ceiling"}),
		"The ornately carved cathedral ceiling extends high above you. The carvings are of various " +
		"animals, bears, deers, all in various exciting poses.\n");

    add_item(({"wall","walls"}),
        "horizontally laid pine trees with white mortar lines.\n");
        
	add_item(({"mortar", "mortar lines", "lines"}),"Bleached white mortar can be seen between the pine tree " +
	    "logs, which make up the walls.\n");

    add_item(({"floor", "ground","floorboards","boards"}),
    	"Cedar planked floor, with the occasional fur rug here and there.\n");

    add_item(({"fireplace", "dual-sided", "stone fireplace"}),"This massive natural stone fireplace looks " +
        "large enough to stand in. It rests at the center of the lodge. A roasting rack sits alongside    " +
        "the fireplace. The fireplace has two sides which share the same flue. There's a roaring fire inside.\n");
    
    add_item(({"fire","roaring fire"}),
        "A cracking fire can be seen within the massive fireplace, providing warmth to the entire lodge; " +
        "Cozy isn't it?\n");
    add_item(({"flue", "chimney"}),"the large natural rock chimney narrows as it extends through and " +
        "beyond the arched ceiling.\n");
        
	add_item(({"fur","fur rugs", "rugs","rug"}),
		"Several very comfortabe looking fur throw rugs can be seen on the floor. They " +
		"look comfy enough to lay on.\n");

    add_item("sign", "Perhaps you could read it?\n");
    
    add_item(({"iron chains","chains"}),
      "Strong looking iron chains hold the heavy looking antler chandeliers overhead.\n");
/*      
    add_item(({"bulletin board","bulletin","board"}),
      "The bulletin board looks temporary, and is there for you to post ideas or issues " +
      "you might find with the club. One in particular, would be race/creature singular " +
      "to plural. Such as, elf should be elves, etc. If you find one, please let us know. " +
      " -- mgmt.\n");
*/

    add_cmd_item("plaque","read",
      "The Hunter's/Huntress' Club is a club where you can record your kills. " +
      "There are no alignment restrictions, and any race/subrace may join. You " +
      "can become a member by typing, <join the hunt>. Upon joining you will " +
      "receive a tallystick as proof of membership. Should you ever lose your " +
      "tallystick, you can get a new one by typing <tallystick me> here.  If " +
      "you ever wish to leave the Club, come here and <abandon the hunt>.\n");
    
    add_cmd_item("shutters", "open",
      "The shutters are closed and locked. You don't see a way to open them.\n");
    
    add_cmd_item("windows", "open",
      "The shutters are closed and locked. You don't see a way to open them.\n");
    
   
    
      
    set_room_tell_time(900);
    add_room_tell("The fire crackles and pops.");
    add_room_tell("The candles flicker slightly, casting shadows along the walls.");
    
    // safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);    
    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(ROOM_I_LIGHT, 2);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");

    create_skill_raise();
    create_guild_support();
    set_up_skills();

    add_exit(HUNTCLUB_DIR + "huntclub_porch","south");
    add_exit(HUNTCLUB_DIR, "north", "@@wiz_check",0,0);
    
    config_default_trade();  /* Set up the trading system */
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 100,    700, 4000,    0 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,    4,    4 })); /* Threshold */
    set_store_room(STORE_ROOM);

    set_standard_equip(HUNTCLUB_EQUIP);
    
    reset_room();
}


int check_intro()
{
    if(rumbald->query_introduced(TP)) return 1;
    rumbald->command("say If you want hire something then you should at "+
      "least introduce yourself!");
    rumbald->command("say Yes, I mean you, you ugly "+
      TP->query_nonmet_name()+"!");
    return 0;
}
int check_light()
{
    if(CAN_SEE_IN_ROOM(rumbald)) return 1;
    rumbald->command("say I am sorry "+TP->query_name()+" but I can't work "+
      "when I can't see.");
    rumbald->command("sigh");
    return 0;
}

string
wizinfo() 
{
    return ("If there should be due cause to close down the guild, do so by\n"+
      "typing:  Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed. -- tomas\n");
}

void
init()
{
    ::init();
    add_action("do_join", "join");
    add_action("do_abandon", "abandon");
    add_action("do_tallystick", "tallystick");
    add_action("do_sit","sit");
    add_action("do_stoke","stoke");
    add_action("do_stand","stand");
    add_action("do_stand","rise");
    add_action("do_lean","lean");
    add_action("do_layrug","lay");
    add_action("do_sell","sell");
    
    init_skill_raise();
    init_guild_support();
    init_shop();
    
}


static void
create_board()
{
    object board;
    if ((board = clone_object("/d/Shire/std/board")))
    {
      board->set_board_name("/d/Shire/clubs/huntclub/board");
        board->set_num_notes(100);
        board->set_anonymous(0);
        board->set_silent(0);
        board->set_show_lvl(0);
        board->set_remove_rank(WIZ_NORMAL);
        board->set_remove_str("Sorry, mortals are not allowed to "+
        "remove notes.\n");
        board->move(TO);
    }
}

string
close_guild() 
{
    if (closed) {
    closed = 0;
    return "  **The guild is now open**";
    }
    closed = 1;
    return "  **The guild is now closed**";
}

int
query_closed() 
{ 
    return closed; 
}

public int
check_member()
{
    if(!TP->test_bit("Shire",FOURTH_GROUP,HUNTCLUB_BIT))
    {
        write("You're not a member of The Hunter's/Huntress' Club.\n");
        return 1;
    }
    return 0;
}


void
set_up_skills() {
    string me;
    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    me = "handle animals";
    sk_add_train(SS_ANI_HANDL,      ({ me, me }),   0,0,30);
    me = "be aware of surroundings";
    sk_add_train(SS_AWARENESS,      ({ me, me }),   0,0,30);
    me = "be aware of locations";
    sk_add_train(SS_LOC_SENSE,      ({ me, me }),   0,0,25);
    me = "find and remove traps";
    sk_add_train(SS_TRACKING,        ({me,me}),     0,0,30);
    me = "hunting";
    sk_add_train(SS_HUNTING,        ({me,me}),      0,0,30);
}

int
sk_improve(string str) 
{
    return ::sk_improve(str);
}

int
do_sell(string str)
{
   write("Rumbald says, I'm nairy buyin anythin, jest sellin.\n");
   return 1;
}

int
do_join(string str)
{
    object tallystick;
    int i;
    object shadow, who = this_player();

    if(str != "the hunt")
    {
        write("Join what, the hunt?\n");
        return 0;
    }

    if(TP->test_bit("Shire",FOURTH_GROUP,HUNTCLUB_BIT))
    {
        write("You're already a member of The Hunter's/Huntress' Club.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());


    write("Welcome to The Hunter's/Huntress' Club!\n");
    write_file(HUNTCLUB_LOG, TP->query_name()+ " joined " +
      extract(ctime(time()), 4, 15) + "\n");

    seteuid(getuid(TO));
    TP->set_bit(FOURTH_GROUP,HUNTCLUB_BIT);
    
    shadow = clone_object(HUNTCLUB_SHADOW);
    shadow->shadow_me(who);
  
    tallystick = present("_huntclub_tallystick_", TP);
    if (!tallystick)
    {
        tallystick = clone_object(HUNTCLUB_DIR + "obj/tallystick");
        tallystick->move(TP,1);
        write("You reach into the basket and select a tallystick.\n");
        say(QCTNAME(TP) +
            " becomes an a member of The Hunter's/Huntress' Club.\n");
    }

    return 1;
}

int
do_abandon(string str)
{
    object tallystick;
    int result;

    if (str !="the hunt")
    {
        write("Abandon what? the hunt?\n");
        return 1;
    }

    if(!(TP->test_bit("Shire",FOURTH_GROUP,HUNTCLUB_BIT)))
    {
        write("You aren't a member of The Hunter's/Huntress' Club.\n");
        return 1;
    }
    write("We hope you find your way back soon.\n");
    tallystick = present("_huntclub_tallystick_", TP);
    if (tallystick)
    {
        tallystick->remove_object();
        write("You toss your tallystick into the fireplace, where it bursts into flames.\n");
    }
    say(QCTNAME(TP) + " leaves the The Hunter's/Huntress' Club.\n");
    write_file(HUNTCLUB_LOG, TP->query_name()+" left "+
      extract(ctime(time()), 4, 15) + "\n");
    TP->clear_bit(FOURTH_GROUP,HUNTCLUB_BIT);
    TP->remove_huntclub_shadow(); 
    TP->remove_cmdsoul(HUNTCLUB_SOUL);
    TP->update_hooks();
    return 1;
}

int
do_tallystick(string str)
{
    object tallystick;

    if (str != "me")
        return 0;

    if (!(TP->test_bit("Shire",FOURTH_GROUP,HUNTCLUB_BIT)))
    {
        write("Only Members of the Hunt Club may tallystick themselves here.\n");
        return 1;
    }

    tallystick = present("_huntclub_tallystick_", TP);

    if (tallystick)
    {
        write("You already have a tallystick.\n");
        return 1;
    }
    tallystick = clone_object(HUNTCLUB_DIR + "obj/tallystick");
    tallystick -> move(TP,1);
    write("You receive a bone tallystick.\n");
    say(QCTNAME(TP)+" chooses a tallystick from the wicker basket.\n");
    return 1;
}

int do_climb(string str)
{
  if(!str)
  {
    NF("Climb where?");
  }
  switch(str)
  {
    if(!TP->query_prop("_standing"))
    {
      write("You are already standing on the ground.\n");
      return 1;
    }
    case "down": case "off table": case "down off table":
    case "down off the table":
      write("You climb down off the table.\n");
      SAY(" climbs down from the table.");
      TP->remove_prop("_standing");
      TP->remove_prop(LIVE_S_EXTRA_SHORT);
      break;
    case "up": case "walls": case "wall": case "up the wall":
      write("You try to climb, but find no purchase to do so.\n");
      SAY(" paws uselessly at the air trying to climb impossible "+
         "things.");
      break;
    case "table": case "on table": case "up table": case "up on table":
    case "the table": case "up on the table":
      write("Perhaps you wish to stand on the table?\n");
      break;
    default:
      write("Perhaps you wish to stand on the table or climb down "+
        "from it?\n");
      break;
  }
  return 1;
}

int do_stoke(string str)
{
  if(!str) { NF("What do you want to stoke?"); }
/*
  if(TP->query_prop(LIVE_S_EXTRA_SHORT) != "%w 'by the fire'")
  {
    write("And how do you expect to do that from here?\n");
    return 1;
  }
*/
  write("You stoke the fire, sending embers flying as the fire burns "+
     "brighter.\n");
  SAY(" stokes the fire sending sparks flying as the fire erupts "+
     "briefly.");
  return 1;
}


int do_sit(string str)
{
   if (!str) { NF("Sit where?\n"); return 0; }
   if(TP->query_prop("_sitting"))
   {
      write("But you are already sitting somewhere!\n");
      return 1;
   }
  if(TP->query_prop("_leaning") || TP->query_prop("_standing"))
  {
    write("Perhaps you should stand up first?\n");
    return 1;
  }
   switch(str) 
   {
    case "down": case "in chair": case "chair": case "in the chair":
    case "in a chair": case "on chair": case "on a chair":
      write("You sit down in one of the chairs by the table.\n");
      SAY(" pulls up a chair and sits by the table.");
      TP->add_prop("_sitting",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in a chair");
      break;
    case "by fire": case "by the fire": case "the fire":
      write("You pull up a chair and sit by the fire.\n");
      SAY(" pulls up a chair and sits by the fire.");
      TP->add_prop("_sitting",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting by the fire");
      break;
    case "in shadow": case "in the shadow": case "in shadows":
    case "in the shadows":
      write("You hunker down into a chair obscured by the shadows.\n");
      SAY(" silently sinks into a chair hidden in the shadows.");
      TP->add_prop("_sitting",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in the shadows");
      break;
    default: 
      write("Perhaps you'd like to sit in the shadows, in a chair, "+
        "or by the fire?\n");
      break;
   }
   return 1;
}

int do_layrug(string str)
{
   if (!str) { NF("lay where?\n"); return 0; }
   if(TP->query_prop("_layrug"))
   {
      write("But you are already laying on one of the rugs!\n");
      return 1;
   }
  if(TP->query_prop("_leaning") || TP->query_prop("_standing") || TP->query_prop("_sitting"))
  {
    write("Perhaps you should stand up first?\n");
    return 1;
  }
   switch(str) 
   {
    case "down": case "on rug": case "rug": case "on a fur rug":
    case "on a rug": case "on the rug": case "by the fire":
      write("You lay down on one of the fur rugs by the fire.\n");
      SAY(" lays down on one of the fur rugs by the fire.");
      TP->add_prop("_layrug",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," laying in front of the fire");
      break;
    default: 
      write("Perhaps you'd like to lay down by the fire?\n");
      break;
   }
   return 1;
}


int do_lean(string str)
{
   if (!str) { NF("Lean where?\n"); return 0; }
  if(TP->query_prop("_leaning"))
  {
     write("You are already leaning against a wall!\n");
     return 1;
   }
  if(TP->query_prop("_sitting") || TP->query_prop("_standing"))
  {
    write("Perhaps you should stand up first?\n");
    return 1;
  }
   switch(str) 
   {
    case "wall": case "the wall": case "against the wall":
    case "against wall": case "a wall": case "against a wall":
      write("You lean against a wall near the table.\n");
      SAY(" saunters over to the table and leans against a wall.");
      TP->add_prop("_leaning",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is leaning against a wall");
      break;
    case "by fire": case "by the fire": case "the fire":
      write("You lean against a wall by the fire.\n");
      SAY(" strolls over to the fire and leans against the wall.");
      TP->add_prop("_leaning",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is leaning against the wall "+
        "by the fire");
      break;
    case "in shadow": case "in the shadow": case "in shadows":
    case "in the shadows":
      write("You lean against a wall in the shadows.\n");
      SAY(" leans against a wall obscured by the shadows.");
      TP->add_prop("_leaning",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is leaning against a wall "+
        "in the shadows");
      break;
    default:
      write("Perhaps you'd like to lean by the fire, against the "+
        "wall, or in the shadows?\n");
      break;
   }
   return 1;
}


int do_stand(string str)
{
  if(!str)
  {
    NF("Stand where?");
  }
  if(str == "on table" || str == "table" || str == "on the table")
  {
    if(TP->query_prop("_standing"))
    {
      write("You are already standing on the table.\n");
      return 1;
    }
    if(TP->query_prop("_sitting") || TP->query_prop("_leaning") || TP->query_prop("_layrug"))
    {
      write("Perhaps you should stand up first?\n");
      return 1;
    }
    write("You clamber up onto the table and stand on it.\n");
    SAY(" climbs up onto one of the tables and looks around the room.");
    TP->add_prop("_standing",1);
    TP->add_prop(LIVE_S_EXTRA_SHORT," is standing on the table");
    return 1;
  }
   
   if (str != "up") {
      NF(CAP(query_verb())+" what? Up?\n");
      return 0;
   }
  if(TP->query_prop("_sitting"))
  {
    write("You stand up and leave your chair behind.\n");
    say(QCTNAME(TP)+" stands up slowly.\n",TP);
    TP->remove_prop("_sitting");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
  }
  if(TP->query_prop("_layrug"))
  {
    write("You stand up from the rug.\n");
    say(QCTNAME(TP)+" stands up slowly.\n",TP);
    TP->remove_prop("_layrug");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
  }
  if(TP->query_prop("_leaning"))
  {
    write("You stand away from the wall.\n");
    SAY(" leaves "+HIS_HER(TP)+" place by the wall.");
    TP->remove_prop("_leaning");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
  } 
  if(!TP->query_prop("_sitting") && !TP->query_prop("_leaning") &&
    !TP->query_prop("_standing"))
  {
    write("You are already standing! Perhaps you'd like to sit down "+
      "or lean against a wall to rest for a bit?\n");
    return 1;
  }
}

void leave_inv(object ob, object to)
{
   ::leave_inv(ob, to);
   
   if(!objectp(to) || !objectp(ob))
      return;
  if(TP->query_prop("_sitting"))
  {
    write("You rise from your chair before leaving.\n");
    say(QCTNAME(TP) + " moves from "+HIS_HER(TP)+" position.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->remove_prop("_sitting");
  }
  if(TP->query_prop("_standing"))
  {
    write("You climb down from the table before leaving.\n");
    say(QCTNAME(TP) + " climbs down from "+HIS_HER(TP)+" position.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->remove_prop("_standing");
  }
  if(TP->query_prop("_leaning"))
  {
    write("You push away from the wall before leaving.\n");
    say(QCTNAME(TP) + " pushes away from "+HIS_HER(TP)+" position.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->remove_prop("_leaning");
  }
}

reset_room()
{
    if (!present("board", TO))
        create_board();
        
    if(!rumbald)
      {
      rumbald = clone_object(HUNTCLUB_DIR + "npc/" + "rumbald.c");
      rumbald->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(rumbald->query_nonmet_name()))+
         " strolls in confidently, shaking out his coat, stomping his feet.\n");
      rumbald->command("lean by fire");
   }
    
}

void
enter_inv(object ob, object from) 
{
    ::enter_inv(ob, from);

    if (!query_ip_number(ob) || !closed)
    return;

    if (ob->query_wiz_level()) 
    write("\n\nWARNING!\nYou shouldn't be here. "+
      "I'm doing some work on the guild.\n");
    else {
    write("The guild is closed. Come back later.\n");
    ob->move(HUNTCLUB_DIR + "huntclub_porch.c");
    }
}