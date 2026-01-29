/* Kirk of Port City - Entrance Foyer
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/1/97      Zima        Created
** 6/20/98     Zima        Recoded door functions
** 7/2021      Tapakah     Removed .ext file inclusion
** 7/2021      Tapakah     Improved dip syntax
*/
/* inherits/includes */
#define  INC_KHALSYS_DEFS
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "defs.h"
#include "../../objects/powder.h"
#include "../../tool/hwvial.h"
#include "../../lib/ktricircum.h"
#include "../../lib/zdoor.h"

#define  KIRK_FONT_DIP "_kirk_font_dip_prop"
#define  OUTSIDE MACDUNN_DIR+"room/road_6_7"

inherit  SR_LIB+"zindoor";
inherit  ROOM+"ksanct";
 
//-------
// WASH
//-------
int
wash ()
{
  write("The water is not used for that.\n");
  return 1;
}
 
//----------------------
// CHECK_EVIL_EFFECT
//----------------------
void
check_evil_effect (object tp, string bodypart)
{
  int align  = tp->query_alignment();
  int undead = tp->query_prop(LIVE_I_UNDEAD);
  int hp;
  if (align<0 || undead) {
    hp = align < 0 ? align : -align;
    if (undead)
      hp *= 3;
    tp->catch_msg("The water burns your "+bodypart+" and you are hurt!\n");
    tp->catch_msg("You scream out in pain and horror!\n");
    tell_room(TO,QCTNAME(tp)+" screams out in pain and horror!\n",tp);
    tp->heal_hp(hp);
  }
}
 
//------
// DIP
//------
int
dip
(string cmd) {
  int rc;
 
  notify_fail("Dip what into the font? Your fingers?\n");
  if (!stringp(cmd)) return 0;
  if (!parse_command(cmd,all_inventory(TO),
                     "[my] 'finger' / 'fingers' / 'hand' 'in' / 'into' [the] [holy] 'font' / "+
                     "'water'"))
    return 0;
 
  write("You dip your fingers into the water of the font.\n");
  tell_room(TO,QCTNAME(TP)+" dips "+(TP->query_possessive())+" fingers "+
            "in the water of the font.\n",TP);
  TP->add_prop(KIRK_FONT_DIP,1);
  check_evil_effect(TP,"hand"); // check effect of evil dipping
  return 1;
}
 
//------------
// DIPPED
//------------
int
dipped (object tp)
{
  //player must have dipped before can sprinkle anything
  if (tp->query_prop(KIRK_FONT_DIP))
    return 1;
  tp->catch_msg("There is no water on your fingers.\n");
  return 0;
}
 
 
//--------------------
// do_sprinkle_powder
//--------------------
void
do_sprinkle_powder (int n, object tp)
{
  switch(n) {
  case 1:
    tp->catch_msg("You do not seem to have the arcane skill required "+
                  "to harness the powers of the water.\n");
    break;
  case 2:
    tell_room(TO,"There is a loud pop and a puff of smoke rises "+
              "from the ground powder.\n");
    break;
  case 3:
    tp->catch_msg("The water seems to have no effect on the "+
                  "strange powder.\n");
  }
}

//------------------------
// DO_SPRINKLE_EFFECT
//------------------------
void
do_sprinkle_effect (object tp, object target)
{
  int    n=0;
  object book;
  
  //check effect of evil being sprinkled
  if (living(target)) {
    check_evil_effect(target, "eyes");
    // check if doing the Omos Rhian: see sean-rhian/book/omos.c
    book = present(SR_OMOS_BOOK,TP);
    if (objectp(book)) {
      TP->add_prop(SR_OMOS_PROP,1);
      write("The " + book->query_short() + " warms briefly in your hands.\n");
    }
  }
  //check effect of quest powder being sprinkled
  else if (target->id(GROUNDED_POWDER)) {
    if (tp->query_skill(SS_SPELLCRAFT) < 10)
      n = 1;
    else if (target->convert(POWDER_INCENSE1))
      n = 2;
    else
      n = 3;
    set_alarm(3.0, 0.0, &do_sprinkle_powder(n,tp));
  }
}

//-----------
// SPRINKLE
//-----------
int
sprinkle (string cmd)
{
  int    rc;         // return codes from parse_command
  object target;     // object being sprinkled
  string str;        // genral use string for parse command
 
  // make sure player is trying to sprinkle something
  notify_fail("Sprinkle who or what with water?\n");
  if (!stringp(cmd))
    return 0;
 
  // check if player is sprinkling himself
  rc = parse_command(cmd,all_inventory(TO),
                     "'me' / 'myself' / 'self' 'with' [holy] 'water'");
  if (rc) {
    if (dipped(TP)) { //must have already dipped fingers in water
      write("You sprinkle yourself with holy water.\n");
      tell_room(TO,QCTNAME(TP)+" sprinkles himself with holy water.\n",TP);
      TP->remove_prop(KIRK_FONT_DIP);
      do_sprinkle_effect(TP,TP);
    }
    return 1;
  }
 
  // check syntax and find object being sprinkled
  rc = parse_command(cmd,(deep_inventory(TP)+all_inventory(TO)),
                     "%o 'with' [holy] 'water'",target);

  if (!rc)
    return 0;
 
  //if TP has dipped, inform TP, target, and others of TP's action
  if (! dipped(TP))
    return 1;
  if (living(target)) {
    TP->catch_msg("You sprinkle "+QTNAME(target)+" with holy water.\n");
    if (!(target->query_npc()))
      target->catch_msg(QCTNAME(TP)+" sprinkles you with holy water.\n");
    tell_room(TO,QCTNAME(TP)+" sprinkles "+QTNAME(target)+
              " with holy water.\n",({TP,target}));
  }
  else {
    str = target->query_short();
    write("You sprinkle the " + str + " with holy water.\n");
    str = present(target,TO) ? "the " + str : LANG_ART(str) + " " + str;
    tell_room(TO,QCTNAME(TP)+" sprinkles "+str+" with holy water.\n",TP);
  }
  TP->remove_prop(KIRK_FONT_DIP);
  do_sprinkle_effect(TP,target);
  return 1;
}

//
// check_exit() - when door is open, player can exit south. This function 
//               adds additional checks (see: sr/lib/zindoor.c)
int
check_exit ()
{
  object book;
  if (book=present(SR_OMOS_BOOK,TP)) {
    book->move(MACDUNN_KIRK+"room/kchapel.c");
    write("The " + book->query_short() + " disappears in a momentary "+
          "flash of light.\n");
  }
  return 0; // player can exit
}


/* room definition */
void
create_khalakhor_room ()
{
  set_short("Entrance foyer of the kirk");
  set_long(
           "   You are standing in the foyer of the kirk, its vaulted ceiling "+
           "rising high above you to a point. Wide pointed arches frame the four "+
           "entrances to the chamber, while an ornate chandelier hangs above "+
           "you, its candles filling the foyer with a subtle light. An emblem "+
           "of three interlocked circles is set in the design of the tiles "+
           "of the floor, while a large marble font filled with water sits "+
           "in the center of the chamber. There is a large circular stained "+
           "glass window set in the wall above the archway of the "+
           "entrance from the north. A set of heavy oak doors guard the "+
           "entrance of the kirk to the south.\n"
           );
 
  INSIDE;
  add_prop(SR_K1SECURE,1);
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_prop(OBJ_I_CONTAIN_WATER,HWATER_PROP_NUM);
  add_item("bolt","It is used to lock the doors.\n");
  add_item("window",&windesc(3));
  add_item("floor",
           "The floor is covered with sparkling clean tiles, an emblem "+
           "set into it.\n");
  add_item("font",
           "The font is a large marble basin sitting on a pedestal filled "+
           "with water. It is sculpted with angelic figures on its sides.\n");
  add_item("water",
           "The font is filled with crystal clear water, obviously used for "+
           "some symbolic purpose.\n");
  add_cmd_item("water","drink","The water is not meant to be drank.\n");
  add_item("emblem",TRICIRCUM);
  add_item(({"foyer","chamber"}),
           "It is the entrance chamber to the kirk.\n");
  add_item("kirk",
           "It is a large stone structure, obviously religious in nature.\n");
  add_item(({"walls","point","ceiling"}),
           "The vaulted ceiling arches from the walls of the chamber into "+
           "a point in the center high above you. An ornate chandelier "+
           "filled with candles hangs from a chain at the point.\n");
  add_item(({"arch","arches","entrance","entrances"}),
           "Four entrances lead into the chamber, framed by elegant arches "+
           "which rise to a point over the center of each. The south entrance "+
           "leads to the outside, while the others seem to lead further into "+
           "the kirk.\n");
  add_item(({"chandelier","chain","candles","light"}),
           "Suspended by a thick gold chain from the central point of the "+
           "vaulted ceiling high above you is an ornate chandelier filled with "+
           "dozens of burning candles, their graceful flickering flames filling "+
           "the chamber with a subtle light.\n");
 
  add_exit("ksanct2","north",0);
  add_exit("kchapel","east",0);
  add_exit("kbellt1","west",0);
 
  setup_indoor("south", OUTSIDE, ({"doors","door"}),
               "They are a pair of heavy oak doors set in the arched entrance "+
               "of the kirk to the south. There is a strong iron bolt which "+
               "is used to lock them.",
               "heavy oak doors",1,BOLTABLE,CLOSED,100,check_exit);
}

void
init ()
{
  ::init();
  add_action(wash, "wash");
  add_action(dip, "dip");
  add_action(sprinkle, "sprinkle");
  add_action(wash, "drink");
  add_action(wash, "sip");
  add_action(wash, "taste");
  add_indoor_actions();
}
 
void
leave_inv (object ob, object to)
{
  if (living(ob)&&(ob->query_prop(KIRK_FONT_DIP)))
    ob->remove_prop(KIRK_FONT_DIP);
  ::leave_inv(ob,to);
}
 
 
void
do_dip (object ob, int step)
{
  if (!objectp(present(ob,TO)))
    return;
  switch(step) {
  case 1:  ob->command("dip fingers in water");        break;
  case 2:  ob->command("sprinkle myself with water");  break;
  case 3:  ob->command("emote traces three circles before his face.");
  default: return;
  }
  set_alarm(3.0,0.0,&do_dip(ob,step+1));
}
 
void
enter_inv (object ob, object from)
{
  if (ob->id(SR_NPC_ID))
    set_alarm(3.0, 0.0, &do_dip(ob,1));
  ::enter_inv(ob,from);
}
