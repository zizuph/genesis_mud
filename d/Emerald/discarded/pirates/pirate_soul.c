inherit "/cmd/std/command_driver";

#include <macros.h>
#include "/d/Emerald/defs.h"
#include "/d/Emerald/common/guild/pirates/combat.h"

#define RIPPED "ripped"
#define BLESSED "blessed"
#define apos attacker->query_possessive()
#define tpos target->query_possessive()
#define apro attacker ->query_pronoun()
#define tpro target->query_pronoun()
#define tobj target->query_objective()
#define an QTNAME(attacker)
#define nt QTNAME(target)

/* Prototypes */
void insult_ob(object *ob);
void allow_insult(object ob);
void hook_ob(object *ob);
void allow_hook(object ob);

/* ************************************************************************
* Return the proper name of the soul in order to get a nice printout.
*/

string
get_soul_id()
{
   return "pirates";
}

/* ************************************************************************
* This is a command soul.
*/

int
query_cmd_soul()
{
   return 1;
}

/* ************************************************************************
* The list of verbs etc. Please add new ones in alphabetical order.
*/

mapping
query_cmdlist()
{
   return ([ "ahoy"      :   "ahoy",
         "chantey"  :  "chantey",
         "check"    :  "check",
         "draw"     :  "draw",
         "greed"    :  "greed",
         "hook"     :  "hook",
         "insult"   :  "insult",
         "knife"    :  "knife",
         "patch"    :  "patch",
         "pburp"    :  "pburp",
         "pstare"   :  "pstare",
         "rip"      :  "rip",
         "stagger"  :  "stagger",
         "story"    :  "story",
         "threaten" :  "threaten"
]);
}

int
ahoy(string arg)
{
   object *oblist;
   notify_fail("Say ahoy to whom?\n");
   
   if(!arg)
      {
      write("You shout ahoy there matie!\n");
      allbb(" shouts: Ahoy there matie!");
      return 1;
   }
   
   oblist = parse_this(arg,"[to] %l");
   
   if(!sizeof(oblist))
      return 0;
   
   actor("You shout ahoy matie to",oblist);
   target(" greets you: Ahoy there matie!",oblist);
   all2act("greets",oblist," in the tradition of Pirates.");
   return 1;
}

int
chantey()
{
   write("You sing 'Yo Ho Ho and a Bottle of Rum'.\n");
   allbb(" sings a pirate chantey:\n"+
      "       Sixteen Men on a Dead Man's Chest\n"+
      "       Yo Ho Ho and a Bottle of Rum!");
   return 1;
}

int
check(string arg)
{
   NF("Check what?\n");
   if(!arg)
      return 0;
   if(arg == "map" || arg == "my map")
      {
      write("You check your map to refresh your memory of "+
         "your burried treasure.\n");
      allbb(" looks carefully at "+TP->query_possessive()+
         " map to refresh "+TP->query_possessive()+" memory of the "+
         "location of "+TP->query_possessive()+" burried treasure.");
      return 1;
   }
   if(arg == "wind" || arg == "the wind")
      {
      write("You check the wind to see if the conditions "+
         "are in your favour.\n");
      allbb(" checks the wind to see if the conditions are "+
         "in "+TP->query_possessive()+" favour.\n");
      return 1;
   }
   return 0;
}

int
draw(string str)
{
   object corpse, symbol, sym;
   
   NF("Draw what?\n");
   if (!strlen(str))
      return 0;
   
   if(str != "symbol")
      return 0;
   
   corpse = present("corpse", ENV(TP));
   symbol = present("symbol",ENV(TP));
   NF("There is already a symbol here!\n");
   if(symbol)
      return 0;
   
   notify_fail("There is no corpse here.\n");
   if (!corpse)
      return 0;
   
   if(str == "symbol")
      {
      NF("There is no apparent opening in the corpse that "+
         "would allow you to extract the appropriate amount of "+
         "blood.\n");
      if(!corpse->query_prop(RIPPED))
         return 0;
   }
   
   if (corpse->query_prop(BLESSED)) {
      write(" recoils in horror from the corpse.\n");
      say("The corpse has been blessed, you recoil in horror.\n");
      return 1;
   }
   
   write("You plunge your pegleg into the open chest "+
      "cavity of the corpse and scrible the symbol of "+
      "el Diablo upon the ground.\n");
   all(" plunges "+TP->query_possessive()+" pegleg into the open "+
      "chest "+
      "cavity of the corpse and scribles the symbol of "+
      "el Diablo upon the ground.\n");
   setuid();
   seteuid(getuid());
   sym = clone_object(PIRATES_DIR+"obj/symbol.c");
   sym ->move(ENV(TP));
   
   return 1;
}                   

int
patch()
{
   write("You adjust your eyepatch.\n");
   allbb(" adjusts his eyepatch and you try to catch "+
      "a glimpse of what's under there.");
   return 1;
}

int
greed(string arg)
{
   object *oblist;
   NF("Show your greed to whom?\n");
   
   if(!arg)
      {
      write("You are so greedy you try to steal your own money!\n");
      allbb(" is so greedy "+TP->query_pronoun()+
         " tries to steal "+TP->query_possessive()+" own money!\n");
      return 1;
   }
   
   oblist = parse_this(arg,"[to] %l");
   
   if(!sizeof(oblist))
      return 0;
   
   actor("You look at",oblist," as if you wished "+
      oblist[0]->query_possessive()+" money was in your pocket.");
   target(" looks at you as if "+TP->query_pronoun()+
      " wishes your money was in "+TP->query_possessive()+
      " pocket!\n",oblist);
   all2act("looks at",oblist," as if "+TP->query_pronoun()+
      " wishes that "+QTNAME(oblist[0])+"'s money was in "+
      TP->query_possessive()+" pocket.\n");
   return 1;
}

int
pburp(string arg)
{
   object *oblist;
   notify_fail("Burp at whom?\n");
   
   if(!arg)
      {
      write("You belch with the soured stench of alcohol.\n");
      allbb(" belches causing a soured stench of alcohol to waft "+
         "across the room.");
      return 1;
   }
   
   oblist = parse_this(arg,"[at]  %l");
   if(!sizeof(oblist))
      return 0;
   
   actor("You burp on",oblist," with the putrid stench of "+
      "soured alcohol.");
   target(" belches on you with the putrid stench of "+
      "soured alcohol.",oblist);
   all2act("belches on",oblist," with the putrid stench of "+
      "soured alcohol.");
   return 1;
}

int
stagger()
{
   write("You stagger to and fro.\n");
   allbb(" staggers to and fro. He appears to have had too much to drink.");
   return 1;
}

int
pstare(string arg)
{
   object *oblist;
   notify_fail("Stare at whom?\n");
   
   if(!arg)
      {
      write("Your eyes are so blurry that you don't even know "+
         "at what you are staring!\n");
      allbb(" stares bleary eyed at all three of you.");
      return 1;
   }
   
   oblist = parse_this(arg,"[to] %l");
   
   if(!sizeof(oblist))
      return 0;
   
   actor("You stare at",oblist," bleary eyed.");
   target(" stares at you with bleary eyes, as if he "+
      "doesn't know which one of you is you.",oblist);
   all2act("stares at",oblist," in the tradition of Pirates, "+
      "bleary eyed.");
   return 1;
}

/* This function was taken from the vamp soul
* it is based on the function suck
* it enables a pirate to rip the heart out
* of a corpse and eat it to gain a very small
* amount of stuffed value, fatigue, and a
* reduction in mana and alignment
* thanks Mylos
*/
int
rip(string str)
{
   object *oblist, room, corpse, suck, cors, *items;
   int i, co_we, co_vo, obdis, dis;
   string his_her;
   
   room = ENV(TP);
   
   NF("Rip what?\n");
   if (!strlen(str))
      return 0;
   
   if(str != "corpse")
      return 0;
   corpse = present("corpse", ENV(TP));
   
   notify_fail("There is no corpse here.\n");
   if (!corpse)
      return 0;
   
   if(str == "corpse")
      {
      notify_fail("From the hole in the chest of the corpse, you "+
            "determine that the heart is probably missing.\n");
      if (corpse->query_prop(RIPPED))
         return 0;
   }
   
   notify_fail("You can't force yourself to eat any more.\n");
   if (TP->query_stuffed() >= TP->eat_max())
      return 0;
   
   co_we = corpse->query_prop(CONT_I_WEIGHT);
   co_vo = corpse->query_prop(CONT_I_VOLUME);
   
   notify_fail("You are too full to do that.\n");
   if ((TP->eat_max() - TP->query_stuffed()) < co_vo / 800)
      return 0;
   
   if (corpse->query_prop(BLESSED)) {
      write(" recoils in horror from the corpse.\n");
      say("The corpse has been blessed, you recoil in horror.\n");
      return 1;
   }
   
   notify_fail("You do not have enough mental strength to do that.\n");
   if (TP->query_mana() < MAX(TP->query_max_mana() / 10, 2))
      return 0;
   
   notify_fail("From the hole in the chest of the corpse, you "+
         "determine that the heart is probably missing.\n");
   if(corpse->query_prop(RIPPED))
      return 0;
   
   if(str == "corpse")
      write("You rip the heart from the chest of the corpse,\n"+
      "offering the sacrifice to the Lord of Darkness.\n");
   write("You greedily consume the bloody flesh.\n");
   all(" rips the heart from the chest of a corpse\n"+
      "offering the sacrifice to the Lord of Darkness.");
   all(" geedily consumes the bloody flesh.");
   corpse->add_prop(RIPPED, 1);
   TP->add_mana(-2);
   
   if (TP->query_alignment() >= (-1000)) {
      TP->set_alignment(TP->query_alignment() - 2);
   }
   TP->eat_food(co_vo / 800);
   TP->add_fatigue(10);
   return 1;
}                   

int
story()
{
   string string1, string2;
   
   switch (random(10)) {
      case 0:
      string1="beautiful";
      string2="You get tears of joy in your eyes.";
      break;
      case 1:
      string1="sad";
      string2="You get a lump in your throat.";
      break;
      case 2:
      string1="boring";
      string2="You yawn to show your 'interest'.";
      break;
      case 3:
      string1="extremely long";
      string2="You tap your foot to show your 'patience'.";
      break;
      case 4:
      string1="intellegent";
      string2="You are impressed.";
      break;
      case 5:
      string1="colorful";
      string2="You blush, you never knew some of those words existed!";
      break;
      case 6:
      string1="funny";
      string2="You laugh so hard your diaphram hurts.";
      break;
      case 7:
      string1="typical";
      string2="You think every sailor has a story like this one.";
      break;
      case 8:
      string1="stupid";
      string2="You sigh heavily. Even you have better stories than that one.";
      break;
      default:
      string1="entertaining";
      string2="You are ready to hear another.";
      break;
   }
   write("You tell a "+string1+" sea story.\n");
   allbb(" tells a "+string1+" sea story.\n"+string2+"");
   return 1;
}

int
threaten(string arg)
{
   object *oblist, *wep;
   string swd;
   int nos;
   
   notify_fail("Threaten whom?\n");
   if(!arg)
      return 0;
   wep = this_player()->query_weapon(-1);
   nos = 0;
   if (sizeof(wep) && wep[0]->query_wt() == W_SWORD)
      {
      nos++;
      swd = wep[0]->query_short();
   }
   if (sizeof(wep) > 1 && wep[1]->query_wt() == W_SWORD)
      {
      nos++;
      swd = wep[1]->query_short();
   }
   if(nos == 2)
      {
      write("You pick one of the two swords you have wielded.\n");
      swd = wep[random(1)]->query_short();
   }
   if(nos == 0)
      {
      write("You are not wielding a sword.\n");
      return 1;
   }
   
   oblist = parse_this(arg,"[the] %l");
   if (!oblist)
      return 0;
   notify_fail("Be more specific.\n");
   if (sizeof(oblist) > 1)
      return 0;
   
   actor("You put the tip of your "+ swd +" on",oblist,"'s chest "+
      "and contemplate running "+ oblist[0]->query_objective() +" through "+
      "with your blade.");
   target(" puts the tip of "+this_player()->query_possessive()+ " " + swd+
      " on your chest and comtemplates running you through with "+
      this_player()->query_possessive() +" blade.",oblist);
   all2act("puts the tip of "+this_player()->query_possessive()+ " "+ swd+
      " on",oblist,"'s chest and contemplates running "+
      oblist[0]->query_objective() +" through with "+
      this_player()->query_possessive() +" blade.");
   return 1;
}



/********************* insult *********************************************/
int
insult(string str)
{
   object ob, *obj;
   int tpint, obint;
   mixed *hitresult;
   string how;
   
   seteuid(getuid());
   
   if (!str) {
      ob = TP->query_attack();
      NF("Insult whom?\n");
      if (!ob)
         return 0;
   }
   else {
      obj = parse_this(str, "%l");
      NF("Choose one victim to insult.\n");
      if (sizeof(obj) != 1)
         return 0;
      ob = obj[0];
   }
   
   if(TP->query_prop(PIR_I_HOOK)){
      NF("You are unable to use your hook and think of a good "+
         "insult at the same time.\n");
      return 0;
   }
   
   
   tpint = TP->query_stat(SS_INT);
   obint = ob->query_stat(SS_INT);
   if(!intp(obint))
      {
      NF("You can't insult an object without intelect.\n");
      return 0;
   }
   
   if(obint <= tpint/5)
      {
      notify_fail(ob->query_The_name(TP) + " is too stupid "+
            "to understand your insult.\n");
      return 0;
   }
   
   if(obint >= tpint*13/10)
      {
      notify_fail(ob->query_The_name(TP) + " is too smart to be effected "+
            "by your insults.\n");
      return 0;
   }
   
   how = c_can_attack(ob, query_verb());
   if (stringp(how)) {
      NF(how);
      return 0;
   }
   
   if (!TP->query_prop(PIR_I_INSULT)) {
      TP->add_prop(PIR_I_INSULT, 3);
      set_alarm(2.0, 0.0, &insult_ob(({ ob, TP })));
      TP->catch_msg("You prepare to insult " + QTNAME(ob) + ".\n");
      if (ob != TP->query_attack()) {
         say(QCTNAME(TP) + " engages " + QTNAME(ob) + " in a "+
            "fight to the death!\n",({ob,TP}));
         ob->catch_msg(QCTNAME(TP)+" engages you in a fight "+
            "to the death!\n");
       }
   }
   else if (TP->query_prop(PIR_I_INSULT) > 1)
      write("You are already preparing another insult.\n");
   else
      write("You are still trying to think of a "+
      "decent insult.\n");
   return 1;
}

void
insult_ob(object *ob)
{
   string how;
   int a, b;

   set_this_player(ob[1]);
   how = c_can_attack(ob[0], "insult");
   if (stringp(how)) {
      ob[1]->catch_msg("You are unable to insult the intended "+
         "victim.\n");
      TP->remove_prop(PIR_I_INSULT);
      return;
   }
   
   a = 35 - MAX(10, TP->query_stat(SS_INT) / 10) - 
       MIN(10, TP->query_skill(SS_INSULT) / 10);
   b = MAX(35 - a, 10);
   set_alarm(itof(b), 0.0, &allow_insult(TP));

//   set_alarm(itof(MAX(35 - MAX(10, TP->query_stat(SS_INT) / 10) -
//                   MIN(10, TP->query_skill(SS_INSULT) / 10,10))),
//             0.0, &allow_insult(TP));
   
   if (ob[0] && environment(TP) != environment(ob[0]))
      return;
   
   TP->add_prop(LIVE_O_SPELL_ATTACK, this_object());
   TP->attack_object(ob[0]);
   TP->add_prop(PIR_I_INSULT, 2);
}

void
allow_insult(object ob)
{
   TP->catch_msg("You are ready to insult again.\n");
   ob->remove_prop(PIR_I_INSULT);
}

/********************* hook *********************************************/
int
hook(string str)
{
   object ob, *obj;
   int tpint, obint;
   mixed *hitresult;
   string how;
   
   seteuid(getuid());
   
   if(!present("ADV_PIRATE",TP)) {
      NF("What?\n");
      return 0;
   }
   
   if (!str) {
      ob = TP->query_attack();
      NF("Hook whom?\n");
      if (!ob)
         return 0;
   }
   else {
      obj = parse_this(str, "%l");
      NF("Choose one victim to hook.\n");
      if (sizeof(obj) != 1)
         return 0;
      ob = obj[0];
   }
   
   if(obj->query_npc() && !function_exists("create_monster",ob)){
      NF("You are only trained to use this attack on humanoids.\n");
      return 0;
   }
   
   if(!present("hook",TP)){
      NF("You must have a hook to use this skill.\n");
      return 0;
   }
   
   how = c_can_attack(ob, query_verb());
   if (stringp(how)) {
      NF(how);
      return 0;
   }
   
   if (!TP->query_prop(PIR_I_HOOK)) {
      TP->add_prop(PIR_I_HOOK, 3);
      set_alarm(2.0, 0.0, &hook_ob(({ ob, TP })));
      if (ob != TP->query_attack()) {
      TP->catch_msg("You engage " + QTNAME(ob) + " in a "+
         "fight to the death.\n");
         say(QCTNAME(TP) + " engages " + QTNAME(ob) + " in a "+
            "fight to the death!\n",({ob,TP}));
         ob->catch_msg(QCTNAME(TP)+" engages you in a fight "+
            "to the death!\n");
       }
   }
   else if (TP->query_prop(PIR_I_HOOK) > 1)
      write("You are still waiting for the perfect oportunity to "+
      "strike.\n");
   else
      write("You think you should give yourself a rest before your "+
      "next hooking exertion.\n");
   return 1;
}

void
hook_ob(object *ob)
{
    int a,b;
    string how;
   
    set_this_player(ob[1]);
    how = c_can_attack(ob[0], "hook");
    if (stringp(how)) {
	ob[1]->catch_msg("You are unable to hook the intended "+
         "victim.\n");
	TP->remove_prop(PIR_I_HOOK);
	return;
    }
    
    a = MAX(10, TP->query_stat(SS_DEX) / 10) - 
	MIN(10, TP->query_skill(SS_HOOK) / 10);
    b = MAX(35 - a, 10);
    set_alarm(itof(b), 0.0, &allow_hook(TP));

//   set_alarm(itof(MAX(35 - MAX(10, TP->query_stat(SS_DEX) / 10) -
//                      MIN(10, TP->query_skill(SS_HOOK) / 10),10), 0.0,
//                  &allow_hook(TP));
   
   
   if ( (ob[0] && environment(TP)) != environment(ob[0]))
      return;
   
   TP->add_prop(LIVE_O_SPELL_ATTACK, this_object());
   TP->attack_object(ob[0]);
   TP->add_prop(PIR_I_HOOK, 2);
}

void
allow_hook(object ob)
{
   TP->catch_msg("You are ready to use your hook again.\n");
   ob->remove_prop(PIR_I_HOOK);
}



/*************************** Special attacks end up here ****************/
void
spell_attack(object attacker, object target)
{
   object allow;
   string how, how2, how3, how4;
   mixed *hitresult;
   int i, at, full_succ, tpint, tpskill, tpmana, tpmaxmana,
   obint, obmana, obmaxmana, d1, d2, d3, delay;
   if(TP->query_prop(PIR_I_INSULT)){
      
      attacker->add_prop(PIR_I_INSULT, 1);
      
      tpint     = attacker->query_stat(SS_INT);
      tpskill   = attacker->query_skill(SS_INSULT);
      tpmana    = attacker->query_mana();
      tpmaxmana = attacker->query_max_mana();
      obint     = target->query_stat(SS_INT);
      obmana    = target->query_mana();
      obmaxmana = target->query_max_mana();
      
      d1 = tpint*tpmana/tpmaxmana;
      d2 = obint*obmana/obmaxmana;
      d3 = d1 + tpskill - d2;
      delay = random(6)*d3/100;
      
      if(delay)
         {
         attacker->add_attack_delay(delay,0);
         if (delay > 5){                
            how = "crushed";
            how2 = " grabs "+tpos+" heart with both hands as your insult "+
            "destroys "+tpos+" will to live.\n";
            how3 = " grab your heart with both hands as "+apos+" insult "+
            "destroys your will to live.\n";
            how4 = " grabs "+tpos+" heart with both hands as "+an+"'s insult "+
            "destroys "+tpos+" will to live.\n";
         }
         else if (delay > 4){
            how = "injured";
            how2 = " moans from the pain your hideous insult inflicts.\n";
            how3 = " moan from the pain "+apos+" hideous insult inflicts.\n";
            how4 = " moans from the pain "+an+"'s hideous insult inflicts.\n";           } 
         else if (delay > 3){
            how = "offended";
            how2 = " gasps as your sharp tongue hurts "+tobj+".\n";
            how3 = " gasp as "+apos+" sharp tongue hurts you.\n";
            how4 = " gasps as "+an+"'s sharp tongue hurts "+tobj+".\n";
         }
         else if (delay > 2){
            how = "annoyed";
            how2 = " scowls at your sensitive remark.\n";
            how3 = " scowl at "+apos+" sensitive remark.\n";
            how4 = " scowls at "+an+"'s sensitive remark.\n";
         }
         else if (delay > 1){
            how = "embarassed";
            how2 = " blushes at your crude language.\n";
            how3 = " blush at "+apos+" crude language.\n";
            how4 = " blushes at "+an+"'s crude language.\n";
         }
         else if (delay > 0){
            how = "unaffected";
            how2 = " laughs at your poor use of language.\n";
            how3 = " laugh at "+apos+" poor use of language.\n";
            how4 = " laughs at "+an+"'s poor use of language.\n";
         }
         
         attacker->catch_msg("You insult " + QTNAME(target) +". ");
         attacker->catch_msg(capitalize(tpro) + " is " + how + ".\n"+
            capitalize(tpro)+how2);
         
         target->catch_msg(QCTNAME(attacker) +
            " insults you. You are "+how+".\n");
         target->catch_msg("You" + how3);
         
         tell_room(environment(attacker),capitalize(an) + " insults "+nt+". "+
            capitalize(tpro)+" is "+how+".\n",({attacker, target}));
         tell_watcher(capitalize(tpro)+how4,attacker, target);
         return;
      }
      
      attacker->catch_msg("You try to insult " + QTNAME(target)+
         " but you jumble your words.\n");
      target->catch_msg(QCTNAME(attacker) +
         " tries to insult you but "+apro+" jumbles "+apos+" words.\n");
      tell_watcher(capitalize(an)+" tries to insult "+nt+" but "+
         "jumbles "+apos+" words.\n",
         attacker, target);
      return;
   }
   else if (TP->query_prop(PIR_I_HOOK))
      {
      attacker->add_prop(PIR_I_HOOK, 1);
      if (random(F_HOOK_HIT(attacker, target)) > random(HOOK_HIT)) {  
         hitresult = target->hit_me(F_HOOK_PEN(attacker, target), 
            W_IMPALE, attacker, -1); 
         
         how = "hastily scratch";
         how2 = "It's difficult to tell if "+tpro+" even noticed.\n";
         how3 = "hastily scratches";
         
         if (hitresult[0] > 50){
            how = "expertly gorge";
            how2 = "Hunks of meaty flesh hang precariously from "+
            "the devestating wound.\n";
            how3 = "quickly gorges";
          }
         else if (hitresult[0] > 40){
            how = "swiftly gash";
            how2 = "Hot red liquid pours from the gaping wound.\n";
            how3 = "swiftly gashes";
          }
         else if (hitresult[0] > 30){
            how = "nimbly lacerate";
            how2 = "Blood begins to run from the clean slice.\n";
            how3 = "nimbly lacerates";
          }
         else if (hitresult[0] > 20){
            how = "quickly slash";
            how2 = "You leave a thin red mark across your enemy.\n";
            how3 = "quickly slashes";
          }
         else if (hitresult[0] > 10){
            how = "hurriedly nick";
            how2 = "You left no more than a scratch upon your enemy.\n";
            how3 = "hurriedly nicks";
          }
         else if (hitresult[0] > 0){
            how = "hastily scratch";
            how2 = "It's difficult to tell if "+tpro+" even noticed.\n";
            how3 = "hastily scratches";
          }
         
         
 attacker->catch_msg("You "+how+" "+QTNAME(target) +" with "+
"your hook.\n");
         
         attacker->catch_msg(how2);
         
         target->catch_msg(QCTNAME(attacker) +
            " "+how3+" you with "+apos+" hook.\n"+how2);
         
         tell_room(environment(attacker),QCTNAME(attacker)+" "+how+
" "+QTNAME(target)+" with "+apos+" hook.\n",attacker);
         tell_watcher(how2,target,attacker);
         
         if (target->query_hp() <= 0) {
            if(living(target)) {
               log_file("hook", CAP(attacker->query_real_name())+
                  " killed "+
                  target->query_real_name()+" with a hook " + 
                  target->query_max_hp() + "\n");
             }
            attacker->catch_msg("In a final dramatic sigh, the last of "+
               "your victim's life drains from his wounds.\n"); 
            
            target->catch_msg("You have been destroyed by "+
               QTNAME(attacker)+"'s vicous hook.\n");
            
            target->do_die(attacker);
            return;
          }
         return;
}
      
      target->hit_me(0, W_IMPALE, attacker, -1);
      attacker->catch_msg("You try to hook " + QTNAME(target)+
         " but you manage too hook nothing more than your own "+
         "clothing.\n");
      target->catch_msg(QCTNAME(attacker) +
         " tries to use "+apos+" hook against you but "+apro+
         " manages to hook nothing "+
         "more than "+apos+" own clothing.\n");
      tell_watcher(capitalize(an)+" tries to use "+apos+
         " hook against "+nt+" but "+
         "manages to hook nothing more than "+apos+" own clothing.\n",
         attacker, target);
      return;
      
   }
   return;
   
}










