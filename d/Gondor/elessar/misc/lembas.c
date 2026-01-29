/*
 *  Lembas - waybread of the Elves of Lorien
 */

inherit "/std/food";
#include "/sys/macros.h"
#include "/sys/composite.h"
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"
#define PIECE_FILE "/d/Gondor/elessar/misc/lembas"
#define MAX_AMOUNT     3000
#define MAX_WEIGHT    260
#define MAX_VOLUME    300

int current_amount, total_amount, is_piece;

piece_size(int i)
{
  int perc, am, mm;
  mm = MAX_AMOUNT / 5;
  perc = i * 100 / mm;
  if (perc > 200) return "very large piece";
  else if (perc > 160) return "large piece";
  else if (perc > 130) return "fairly large piece";
  else if (perc > 100) return "good sized piece";
  else if (perc > 80) return "normal piece";
  else if (perc > 60) return "medium piece";
  else if (perc > 40) return "small piece";
  else if (perc > 20) return "tiny piece";
  else if (perc > 0) return "few crumbs";
  else return "crumb";
}

consume_text(object *arr, string vb)
{
  string str;
  write(BS("You nibble at the "+piece_size(food_amount)+" of lembas at first, "+
    "then eat the rest of it with relish!\n"));
  say(QCTNAME(TP)+" eats a "+piece_size(food_amount)+" of lembas with relish.\n",TP);
}

set_amount(int am)
{
  int perc;
  total_amount = am;
  food_amount = am;
  current_amount = am;
  perc = am * 100 / MAX_AMOUNT;
  add_prop(OBJ_I_WEIGHT, (MAX_WEIGHT * perc / 100));
  add_prop(OBJ_I_VOLUME, (MAX_VOLUME * perc / 100));
  if (is_piece) add_prop(HEAP_S_UNIQUE_ID,"A piece of a lembas wafer.\n");
  else add_prop(HEAP_S_UNIQUE_ID,"A whole lembas wafer, made by elves.\n");
}

eat_fail()
{
  string str;
  str = "You can try to 'break piece off lembas' and eat that piece.\n"+
    "The piece will be as much as you can eat in one piece.\n";
  say(QCTNAME(TP)+" discovers that "+short()+
    " is too much for "+TP->query_objective()+".\n",TP);
  tp_remove_temp(TP);
  return str;
}

create_food() {
  set_name("lembas");
  add_name("wafer");
  add_name("cake");
  set_adj("thin");
  add_adj("light brown");
  set_short("@@short_func");
  set_pshort("@@pshort_func");
  set_long("@@long_func");
  set_amount(MAX_AMOUNT);
}

long_func()
{
  string str, mainstr;
  int perc;
  if (is_piece) return "This is "+piece_size(food_amount)+" torn off a lembas wafer.\n"+
    "The piece is very light and thin. The crust has been baked light brown,\n"+
    "while the inside is the colour of cream, and smells deliciously.\n";
  perc = ((current_amount * 100) / MAX_AMOUNT);
  str = "You guess that";
  mainstr = "The cake is very thin, and light of weight. The crust is "+
    "of light brown colour, making look like a normal bread. "+
    "This is however a lembas wafer, the waybread of the elves, "+
    "and it is much more nutritious than normal bread. ";
  if (current_amount == MAX_AMOUNT) 
    return BSN(mainstr+"The wafer is whole.");
  else if (perc > 90) str = str + " the lembas wafer is almost whole. ";
  else if (perc > 80) str = str + " a piece or two haven been broken off the wafer. ";
  else if (perc > 70) str = str + " a quarter of the lembas is gone. ";
  else if (perc > 60) str = str + " two thirds of the wafer is left. ";
  else if (perc > 50) str = str + " about half of the lembas wafer is left. ";
  else if (perc > 40) str = str + " about half of the wafer is gone. ";
  else if (perc > 30) str = str + " a quarter of the wafer is left. ";
  else if (perc > 20) str = str + " one third of the lembas is left. ";
  else if (perc > 10) str = str + " most of the lembas is gone. ";
  else if (perc > 0) str = str + " only a small piece of the wafer is left. ";
  str = str + "The inside of the wafer is the colour of cream, and smells delicious. ";
  return BSN(mainstr + str);
}

short_func()
{
  if (is_piece) return piece_size(food_amount)+" of a lembas wafer";
  else if (food_amount > MAX_AMOUNT * 2/3)
    return "thin light brown lembas wafer";
  else if (food_amount > MAX_AMOUNT / 3)
    return "half lembas wafer";
  else return "half-eaten lembas wafer";
}

pshort_func()
{
  if (is_piece) return "lembas wafer pieces";
  else if (food_amount > MAX_AMOUNT * 2/3)
    return "thin light brown lembas wafers";
  else if (food_amount > MAX_AMOUNT / 3 )
    return "half lembas wafers";
  else return "half-eaten lembas wafers";
}

init()
{
  ::init();
  add_action("break_off_piece","break");
  add_action("share_with","share");
}

break_off_piece(string str)
{
  int am, mm;
  string cstr;
  string dummy;
  object piece;
  if (!str) { write("Break what?\n"); return 1; }
  if (!(sscanf(str,"%siece off %s",dummy,cstr)==2)) {
    return 0;
    }
  if (cstr != "lembas" && cstr != "wafer" && cstr != "cake") {
    write("Break a piece off what?\n");
    return 1;
    }
  am = TP->eat_max()/5;
  mm = TP->eat_max() - TP->query_stuffed();
  if (am > mm) am = mm;
  if (am >= current_amount) {
    write("There is no need for breaking off yet another piece; it is\n"+
    "not too much for you to eat. If you want to give a piece to\n"+
    "someone else, 'share piece with' them.\n");
    return 1;
    }
  seteuid(getuid(TO));
  piece = clone_object(PIECE_FILE);
  piece->set_is_piece();
  piece->set_amount(am);
  recalculate(am);
  write("You break off a "+piece_size(am)+" of the lembas wafer.\n");
  say(QCTNAME(TP)+" breaks off a "+piece_size(am)+" of the thin, light brown cake.\n",TP);
  piece->move(TP,1);
  return 1;
}

share_with(string str)
{
  int am, mm;
  object piece, friend;
  string cstr, who;
  if (!str) { write("Share what with who?\n"); return 1; }
  str = lower_case(str);
  if (!(sscanf(str,"%s with %s",cstr,who)==2)) {
  write("Share what with who?\n"); return 1; }
  friend = present(who,ENV(TP));
  if (!friend) { write("What "+capitalize(who)+"? Where?\n"); return 1; }
  if (!CAN_SEE(TP,friend)) {
    write("DEBUG: CAN_SEE failed.\n");
    write("What "+capitalize(who)+"? Where?\n"); return 1; }
  am = friend->eat_max()/5;
  mm = friend->eat_max() - friend->query_stuffed();
  if (am > mm) am = mm;
  if (am >= current_amount) {
    write("You want to share the lembas wafer with "+QTNAME(friend)+
    ",\n but the wafer is too small. You decide to give it all away.\n");
    friend->catch_msg(QCTNAME(TP)+" kindly gives you the rest of "+
    TP->query_possessive()+" lembas wafer.\n");
    say(QCTNAME(TP)+" gives a "+piece_size(food_amount)+" thin light brown wafer to "+QTNAME(friend)+
    ".\n",({TP,friend}));
    TO->move(friend,1);
    return 1;
    }
  piece = clone_object(PIECE_FILE);
  piece->set_is_piece();
  piece->set_amount(am);
  recalculate(am);
  TP->catch_msg("You break off a "+piece_size(am)+" of your lembas wafer, and share it\n"+
    "with "+QTNAME(friend)+".\n");
  friend->catch_msg(QCTNAME(TP)+" shares a "+piece_size(am)+" of "+TP->query_possessive()+
    " lembas wafer with you.\n");
  say(QCTNAME(TP)+" gives a "+piece_size(am)+" of lembas wafer to "+QTNAME(friend)+".\n",
    ({TP,friend}));
  piece->move(friend,1);
  return 1;
}

recalculate(int am)
{
  int perc;
  current_amount -= am;
  food_amount = current_amount;
  if (current_amount <=0) remove_object();
  perc = food_amount * 100 / MAX_AMOUNT;
  if (perc < 25) set_is_piece();
  add_prop(OBJ_I_WEIGHT, (MAX_WEIGHT * perc / 100));
  add_prop(OBJ_I_VOLUME, (MAX_VOLUME * perc / 100));
  return 1;
}

set_is_piece()
{
  is_piece = 1;
  add_name("piece");
}

