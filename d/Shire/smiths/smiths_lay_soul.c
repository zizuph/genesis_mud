/*     CMDSOUL FOR SMITHS GUILD LAYMAN BRANCH
       By Morinir / Lars Madsen
       (c) Shire 1996 ;)
*/

#pragma save_binary;

inherit "/cmd/std/command_driver";

#include "/d/Shire/common/defs.h"
#include "smiths.h"
#include <cmdparse.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <composite.h>
#include <files.h>
#include <time.h>
#include <std.h>
#include <options.h>
#include <adverbs.h>
#include <options.h>

#define CHECK_WEAPON       "check_weapon"
#define STD_WEAPON         "/std/weapon"
#define CHECK_ARMOUR       "check_armour"
#define STD_ARMOUR         "/std/armour"
#define MEMBER_NOT_READY   "_member_not_ready"
#define SMITHS_SUBLOC "_live_as_smiths_subloc"
#define MORE(x)   this_player()->more(read_file(x,2))

//** Prototypes **//
int help(string s);
int sminspect(string s);
int smlist();
int smlaugh(string s);
int smcheck(string s);
int smbroke(string s);
int smboast(string s);
int smtell(string s);
int smtired();
int smsearch();
int smsigh(string s);
int smarmour();
int find(string s);
int smmark(string s);
int smfinger(string s);
int smcollect();
int smshow(string s);
int smwave(string s);
int smremind(string s);
int smwipe(string s);
int smvictory(string s);
int smsuggest(string s);
int smcomplain(string s);
int smlisten(string s);
int smgreet(string s);
object find_item(string str,string error);
void whet_found();

string
get_soul_id() // { return "smiths_guild_soul"; }
{
    return "Blacksmiths of the Shire";
}

int
query_cmd_soul(){ return 1; }

mapping
query_cmdlist()
{
    return ([
	          "help"      : "help",         /* help */
              "find"      : "find",
              "smarmour"  : "smarmour",
              "smboast"   : "smboast",
              "smbroke"   : "smbroke",
              "smcheck"   : "smcheck",
              "smcollect" : "smcollect",
              "smcomplain": "smcomplain",
              "smfinger"  : "smfinger",
              "smgreet"   : "smgreet",
              "sminspect" : "sminspect",
              "smlist"    : "smlist",
              "smlaugh"   : "smlaugh",
              "smlisten"  : "smlisten",
              "smmark"    : "smmark",
              "smremind"  : "smremind",
              "smremove"  : "smremove",
              "smsearch"  : "smsearch",
              "smshow"    : "smshow",
              "smsigh"    : "smsigh",
              "smsuggest" : "smsuggest",
              "smtell"    : "smtell",
              "smtired"   : "smtired",
              "smwave"    : "smwave",
              "smwipe"    : "smwipe",
              "smvictory" : "smvictory",
           ]);
}

int
help(string str)
{
    setuid(); seteuid(getuid());
    switch (str)
    {
        case "smiths": 
        case "smiths general":
	        MORE(SMITHSDIR_HELP + "general");
            break;
        case "smiths emotes":
        case "smiths emotions":
            MORE (SMITHSDIR_HELP + "emotes");
            break;
        case "smiths abilities":
            MORE (SMITHSDIR_HELP + "abilities");
            break;
        case "smiths weapons":
        case "smiths weap":
        case "smiths wep":
            MORE (SMITHSDIR_HELP + "weapons");
            break;
        case "smiths armours":
        case "smiths arms":
        case "smiths arm":
        case "smiths armo":
            MORE (SMITHSDIR_HELP + "armours");
            break;
        case "smiths necklace":
        case "smiths neck":
        case "smiths descr":
        case "smiths desc":
        case "smiths levels":
        case "smiths lev":
            MORE (SMITHSDIR_HELP + "levels");
            break;
        case "smiths titles":
        case "smiths titl":
        case "smiths title":
            MORE (SMITHSDIR_HELP + "titles");
            break;
        case "smiths forges":
        case "smiths forging":
        case "smiths forg":
            MORE (SMITHSDIR_HELP + "forging");
            break;

        default:
	        return 0;
    }
    return 1;
}


int
smarmour() {
    write("You study your armour and tell everyone about the finer details"+
      " of this type of armour.\n");
    say(QCTNAME(TP)+" studies "+HIS_HER(TP)+" armour, then starts telling"+
      " you about all the finer details of this particulary type of armour."+
      " It looks like "+HE_SHE(TP)+" is quite pleased about having found"+
      " a listener.\n");
    TP->command("smile");
    return 1;
}


int
smboast(string str) {
    write("You boast openly with your skills in crafting items.\n");
    allbb(" boasts openly with "+HIS_HER(TP)+" skills in crafting items.");
    return 1;
}


int
smbroke(string str) {
    object *presents;
    int    i;
    int    count_to;

    presents=all_inventory(ENV(TP)) - ({TP});
    presents=filter(presents, interactive);

    if (!sizeof(presents)) {
	write("You wonder if anyone has some broken items for you.\n");
	return 1;
    }

    actor("You wonder if", presents, " has some broken items for you.");
    targetbb(" wonders if you have some broken items for him.",
      presents);
    all2actbb("  wonders if", presents, " has some broken items for him.");

    return 1;
}

int
smcheck(string str) {
    object obj;

    obj=find_item(str,"check");

    if (obj==0) return 1;

    if (function_exists(CHECK_WEAPON, obj) != STD_WEAPON)
    {
	write("You can only check weapons.\n");
	return 1;
    }

    {
	TP->catch_msg("You grip the "+obj->short()+" and make a few slashes"+ 
	  " in the air, then nod in appreciation of the good"+ 
	  " craftmanship.\n");
	say(QCTNAME(TP)+" grips the "+obj->short()+" and make a few"+ 
	  " slashes in the air, then nods in appreciation of the good"+ 
	  " craftmanship.\n");
	return 1;
    }
    return 0;
}


int
smcollect() {
    write("You start searching for items useful for forging purposes.\n");
    allbb(" starts searching for items useful for forging purposes.");
    return 1;
}


int
smcomplain(string str) {
    object item;

    notify_fail("Complain about what?\n");

    item=find_item(str,"complain about");
    if (!item) return 0;

    if (TP->query_race_name()=="dwarf") {
	write("You grumble about the poor quality of the "+item->short()+".\n");
	all(" grumbles about the poor quality of the "+item->short()+" "+
	  HE_SHE(TP)+" is carrying.");
	return 1;
    }
    write("You complain about the poor quality of the "+item->short()+".\n");
    all(" complains about the poor quality of the "+item->short()+" "+
      HE_SHE(TP)+" is carrying.");
    return 1;
}


/*
       we no longer use SS_FORGE_XP
       if function is uncommented for some reason provide a prototype

int
smfast(string str) {
    object *targets;

    notify_fail("Explain to whom how fast you are?\n");

    if (!TP->query_skill(SS_FORGE_XP)) {
	write("You haven't really done much forging recently, have you?\n");
	return 1;
    }

    if (TP->query_skill(SS_FORGE_XP)==1) {
	write("You want to boast about how experienced you are even though you"+
	  " have made only 1 item!?\n");
	return 1;
    }

    if ((!str) || (str=="all")) {
	allbb(" explains to everyone how experienced "+HE_SHE(TP)+" is in"+ 
	  " forging"+
	  " quality items. "+CAP(HE_SHE(TP))+" has forged "+
	  TP->query_skill(SS_FORGE_XP)+" items since "+HE_SHE(TP)+
	  " joined the Smiths Guild.");
	write("You explain to everyone how experienced you are in forging"+
	  " quality items. You have forged "+
	  TP->query_skill(SS_FORGE_XP)+" items since you joined the Smiths"+
	  " Guild.\n");
	return 1;
    }

    targets = parse_this(str, "[at] [the] %l");

    if (!sizeof(targets)) return 0;

    actor("You explain", targets, " how experienced you are in forging"+
      " quality items. You have forged "+
      TP->query_skill(SS_FORGE_XP)+" items since you joined the Smiths"+
      " Guild.");
    targetbb(" explains to you how experienced "+HE_SHE(TP)+" is in"+
      " forging"+
      " quality items. "+CAP(HE_SHE(TP))+" has forged "+
      TP->query_skill(SS_FORGE_XP)+" items since "+HE_SHE(TP)+
      " joined the Smiths Guild.", targets);
    all2actbb("  explains to ", targets," how experienced "+HE_SHE(TP)+
      " is in"+
      " forging quality items. "+CAP(HE_SHE(TP))+" has forged "+
      TP->query_skill(SS_FORGE_XP)+" items since "+HE_SHE(TP)+
      " joined the Smiths Guild.");
    return 1;
}
*/

int
smfinger(string str) {
    object obj;

    obj=find_item(str,"feel");

    if (obj==0) return 1;

    if (function_exists(CHECK_WEAPON, obj) != STD_WEAPON)
    {
	write("You can only feel weapons.\n");
	return 1;
    }

    {
	TP->catch_msg("You let your fingers run along the blade of the "+ 
	  obj->short()+" to show that you are not an opponent to take"+
	  " lightly.\n");
	switch (STR(TP)) {
	case 0..20:
	    say(QCTNAME(TP)+" starts fingering the "+
	      obj->short()+". "+CAP(HE_SHE(TP))+" doesn't look very"+
	      " threatening.\n");
	    break;
	case 21..40:
	    say(QCTNAME(TP)+" starts fingering the "+
	      obj->short()+". Perhaps it would be wise not to mess with "+
	      HIM_HER(TP)+".\n");
	    break;
	case 41..60:
	    say(QCTNAME(TP)+" starts fingering the "+
	      obj->short()+". It would be foolish to provoke "+HIM_HER(TP)+".\n");
	    break;
	case 61..90:
	    say(QCTNAME(TP)+" starts fingering the "+
	      obj->short()+". "+CAP(HE_SHE(TP))+" looks quite threatening.\n");
	    break;
	default:
	    say(QCTNAME(TP)+" starts fingering the "+
	      obj->short()+". No one would mess with "+HIM_HER(TP)+" unless they"+
	      " have a deathwish.\n");
	    break;
	}            
	return 1;
    }
    return 0;
}

int
smgreet(string str) {
    object *presents;
    int    i;
    int    count_to;

    presents=all_inventory(ENV(TP)) - ({TP});
    presents=filter(presents, interactive);

    if (!sizeof(presents)) {
	write("You greet all in the manner of smiths.\n");
	return 1;
    }

    actor("You greet", presents, " in the manner of smiths.");
    targetbb(" greets you in the manner of smiths.",
      presents);
    all2actbb("  greets", presents, " in the manner of smiths.");

    /*  We shouldn't force other players to do something when
	we use our emotes.

       for (i=0; i<sizeof(presents); i++) {
	  if (!IS_MEMBER(presents[i]))
	     presents[i]->command("bow "+TP->query_real_name());
       }
    */

    return 1;
}


int
sminspect(string str) {
   object obj;
   object *to_inspect;
   int tohit,topen,inspect,penalty,fatigue;

   notify_fail("Inspect what?\n");
   if (!strlen(str))
   {
       return 0;
   }

   if ((!parse_command(str, TP, "[the] %i", to_inspect)) ||
      (!sizeof(to_inspect = NORMAL_ACCESS(to_inspect, 0, 0))))
   {
      return 0;
   }

   if (objectp(obj = TP->query_attack()))
   {
      TP->catch_msg("You are currently fighting " + obj->query_the_name(TP) +
         "! You do not have the time to inspect anything.\n");
      return 1;
   }
   if (sizeof(to_inspect) != 1)
   {
      write("Please select only one item to inspect.\n");
      return 1;
   }
   else
   {
      obj = to_inspect[0];
   }

   if (obj->query_smiths_item()) {
      write("This item seems useful for forging purposes.\n");
      obj->appraise_object();

      return 1;
   }

   if (function_exists(CHECK_WEAPON, obj) == STD_WEAPON) {

      inspect=TP->query_skill(SS_APPR_OBJ)+TP->query_stat(SS_LAYMAN);
      if (inspect<10) {
         write("You don't know how to inspect a weapon!\n");
         return 1;
      }

      fatigue=TP->query_max_fatigue()/10;

      if (TP->query_fatigue()<fatigue) {
         write("You are too tired to inspect anything right now.\n");
         return 1;
      }

      TP->add_fatigue(-fatigue);

      write("You study the weapon carefully.\nThis is what you notice:\n");

      obj->appraise_object();

      tohit=obj->query_hit(); /* figure out tohit for wielded weapon */
      topen=obj->query_pen(); /* figure out topen for wielded weapon */

      switch(inspect) {
         case 10..25:
            penalty=random(40)-20;
            break;
         case 26..50:
            penalty=random(30)-15;
            break;
         case 51..75:
            penalty=random(20)-10;
            break;
         case 76..100:
            penalty=random(14)-7;
            break;
         case 101..150:
            penalty=random(6)-3;
            break;
         default:
            penalty=random(4)-2;
            break;
      }

      tohit=tohit+penalty;
      topen=topen+penalty;

      if (tohit<0) tohit==0;
      if (topen<0) topen==0;

      /* make modification for inspect skill later */

      if (topen<10)
         write("This weapon doesn't seem very effective.\n");
      if ((topen>9) && (topen<20))
         write("This weapon might do some damage with a lucky hit.\n");
      if ((topen>19) && (topen<30))
         write("This weapon seems quite effective.\n");
      if ((topen>29) && (topen<40))
         write("This weapon could most likely kill with a single swipe.\n");
      if ((topen>39) && (topen<50))
         write("This weapon is extremely powerful and more lethal than"+
         " many of the famous weapons.\n");
      if (topen>49)
         write("This weapon is an extremely powerful artifact.\nWith this"+
         " weapon even a single warrior will be able to match a large"+
         " force.\n");

      if (tohit<10)
         write("It is almost impossible to get a good strike with this"+
         " weapon.\n");
      if ((tohit>9) && (tohit<20))
         write("It is difficult to use this weapon properly.\n");
      if ((tohit>19) && (tohit<30))
         write("It feels good when you wield this weapon--you would most"+
         " likely have no trouble getting a good hit with this weapon.\n");
      if ((tohit>29) && (tohit<40))
         write("You should have no trouble handling this weapon--or making"+
         " a cruel hit with it for that matter.\n");
      if ((tohit>39) && (tohit<50))
         write("Even an apprentice warrior could kill easily with this"+
         " weapon.\n");
      if (tohit>49)
         write("With this weapon almost every strike could be a killing"+
         " blow.\n");
      if ((obj->query_prop(OBJ_I_IS_MAGIC_WEAPON)) &&
         (inspect>70))
         write("This weapon is most likely enchanted.\n");
      return 1;
   }

   if (function_exists(CHECK_ARMOUR, obj) != STD_ARMOUR) {
      write("You study the "+obj->short()+
         " carefully.\nThis is what you notice:\n");
      obj->appraise_object();

      return 1;
   }

   inspect=TP->query_skill(SS_APPR_OBJ)+TP->query_stat(SS_LAYMAN);
   if (inspect<10) {
      write("You don't know how to inspect an armour!\n");
      return 1;
   }

   fatigue=TP->query_max_fatigue()/10;

   if (TP->query_fatigue()<fatigue) {
      write("You are too tired to inspect anything right now.\n");
      return 1;
   }

   TP->add_fatigue(-fatigue);

   write("You study the armour carefully.\nThis is what you notice:\n");

   obj->appraise_object();

   tohit=obj->query_ac();  /* figure out ac for the armour */

   switch(inspect) {
      case 10..25:
         penalty=random(40)-20;
         break;
      case 26..50:
         penalty=random(30)-15;
         break;
      case 51..75:
         penalty=random(20)-10;
         break;
      case 76..100:
         penalty=random(14)-7;
         break;
      case 101..150:
         penalty=random(6)-3;
         break;
      default:
         penalty=random(4)-2;
         break;
   }

   tohit=tohit+penalty;

   if (tohit<0) tohit==0;

   /* make modification for inspect skill later */

   if (tohit<10)
      write("This armour wouldn't even protect you from a very weak blow.\n");
   if ((tohit>9) && (tohit<20))
      write("This armour could perhaps reduce damage a little.\n");
   if ((tohit>19) && (tohit<30))
      write("This seems to be an armour of average quality.\n");
   if ((tohit>29) && (tohit<40))
      write("This armour would protect you very well.\n");
   if ((tohit>39) && (tohit<50))
      write("This is an extremely well-made armour which would protect you"+
      " very well.\n");
   if (tohit>49)
      write("Virtually nothing could harm you if you wore this armour.\n");
   if ((obj->query_prop(OBJ_I_IS_MAGIC_ARMOUR)) &&
      (inspect>70))
      write("This armour is most likely enchanted.\n");
   return 1;
}



int
smlaugh(string str) {
    object person, wep;
    object *to_tell;

    notify_fail("Laugh at whose weapon?\n");
    if (!strlen(str)) {
	return 0;
    }

    if ((!parse_command(str, ENV(TP), "[the] %i", to_tell)) ||
      (!sizeof(to_tell = NORMAL_ACCESS(to_tell, 0, 0)))) {
	return 0;
    }

    if (sizeof(to_tell) != 1) {
	write("Please select only one person to laugh at.\n");
	return 1;
    }
    else {
	person = to_tell[0];
    }

    if ((!person->query_weapon(W_RIGHT)) && (!person->query_weapon(W_LEFT))
      && (!person->query_weapon(W_BOTH))) {
	TP->catch_msg("But "+QTNAME(person)+" is not wielding any weapon!\n");
	return 1;
    }

    wep=person->query_weapon(W_RIGHT);
    if (!wep) wep=person->query_weapon(W_LEFT);
    if (!wep) wep=person->query_weapon(W_BOTH);

    to_tell+=({TP});

    TP->catch_msg("You laugh at "+QTNAME(person)+"'s "+wep->short()+" for"+
      " being such a pitiful weapon.\n");
    person->catch_msg(QCTNAME(TP)+" laughs at your "+wep->short()+" for being"+
      " such a pitiful weapon.\n");
    tell_room(ENV(TP),QCTNAME(TP)+" laughs at "+QCTNAME(person)+"s "+
      wep->short()+" for being such a pitiful weapon.\n",to_tell);
    return 1;
}

int
smlist()
{
    object *pl= users(),
           *smiths = ({});
    int     i,
            sz = sizeof(pl);
    string  name;

    for (i = 0; i < sz; i++)
    {
        if (pl[i]->query_guild_name_lay() == GUILD_NAME)
        {
            name = pl[i]->query_name();
            if (extract(name,strlen(name)-2,strlen(name)-1) != "jr")
                smiths += ({ pl[i] });
        }
    }
 
    sz = sizeof(smiths);
    if (!sz)
    {
        NF("There are no Blacksmiths present right now.\n");
        return 0;
    }
 
    if (sz == 1)
    {
        write("You are the only Blacksmith present.\n");
        return 1;
    }

    write("---------------------------------------------------"+
        "---------------------\n"+
        "                        "+sz+" Blacksmiths roam the lands:\n"+
        "---------------------------------------------------"+
        "---------------------\n");
    for (i = 0; i < sz; i++)
    {
        write("          "+smiths[i]->query_name()+", "+
            smiths[i]->query_guild_title_lay()+"\n");
    }

    write("---------------------------------------------------"+
        "---------------------\n");
    return 1;
}


int
smlisten(string str) {
    write("You listen to the distant ringing of hammers beating upon metal.\n");
    allbb(" listens to the distant ringing of hammers beating upon metal.");
    return 1;
}

int
smmark(string str) {
    object obj;
    string marked="obj_has_smmark";

    obj=find_item(str,"mark");

    if (obj==0) return 1;

    if (obj->query_prop(marked)) {
	write("You have already marked this item once.\n");
	return 1;
    }

    if (!IS_ARMOUR_OBJECT(obj) && !IS_WEAPON_OBJECT(obj)) {
        write("You can only mark weapons and armours.\n");
        return 1;
    }

    if ((obj->query_prop(OBJ_I_IS_MAGIC_WEAPON)) 
      || (obj->query_prop(OBJ_I_IS_MAGIC_WEAPON))) {
	write("You wouldn't want to mark this fine item... would you?\n");
	return 1;
    }

    write("You mark the item with your personal mark.\n");
    obj->set_long(obj->query_long()+"It is marked with "+TP->query_name()+
      "'s mark.\n");
    obj->add_prop(marked,1);
// item non-sellable now
    obj->add_prop(OBJ_M_NO_SELL,1);



    return 1;
}


int
smremind(string str) {
    object *targets;

    notify_fail("Wave to whom?\n");

    if ((!str) || (str=="all")) {
	allbb(" reminds you that only a professional smith like "+HIM_HER(TP)+
	  "self knows how to take care of finely forged items.");
	write("You remind everyone that only a professional smith like yourself"+
	  " knows how to take care of finely forged items.\n");
	return 1;
    }

    targets = parse_this(str, "[at] [the] %l");

    if (!sizeof(targets)) return 0;

    actor("You remind", targets, " that only a professional smith like"+
      " yourself knows how to take care of finely forged items.");
    targetbb(" reminds you that only a professional smith like "+
      HIM_HER(TP)+"self knows how to take care of finely forged items.",
      targets);
    all2actbb("  reminds ", targets, " that only a professional smith like "+
      HIM_HER(TP)+"self knows how to take care of finely forged items.");
    return 1;
}

int
smremove(string str) {
    object obj;
    mixed tmp;
    string marked="obj_has_smmark";

    obj=find_item(str,"mark");

    if (obj==0) return 1;
/*
    if ((obj->query_prop(OBJ_I_IS_MAGIC_WEAPON)) 
      || (obj->query_prop(OBJ_I_IS_MAGIC_WEAPON))) {
	write("You wouldn't want to mark this fine item... would you?\n");
	return 1;
    }
*/
    if (!obj->query_prop(marked))
    {
	write("This item has no Smiths mark.\n");
	return 1;
    }

    write("You remove the Smiths mark from the item.\n");
    obj->remove_prop(marked);
    tmp = implode(explode(obj->query_long(), "\n")[..-2], "\n") + "\n";
    obj->set_long(tmp);
// object now sellable
    obj->remove_prop(OBJ_M_NO_SELL);


    return 1;
}

int
smsearch() {
    if (present("corpse", ENV(TP))) {
	write("You search the corpse for valuable items.\n");
	say(QCTNAME(TP)+" searches the corpse for valuable items.\n");
    }
    else {
	write("but there is no corpse here!\n");
    }
    return 1;
}


int
smsigh(string str) {
    notify_fail("Sigh about what? the palantari? Gil-galad's spear? Durin's"+
      " axe? Elendil's sword? or perhaps the Silmarils?\n");

    if ((str=="the palantari") ||
      (str=="the silmarils")) {
	write("You sigh, wondering when the day will come when you will be"+
	  " able to make an item like "+str+".\n");
	say(QCTNAME(TP)+" sighs, wondering when the day will come when "+
	  HE_SHE(TP)+" will be able to make an item like "+str+".\n");
	return 1;
    }

    if ((str=="gil-galad's spear") ||
      (str=="durin's axe") || (str=="elendil's sword")) {
	write("You sigh, wondering when the day will come when you will be"+
	  " able to make an item like "+CAP(str)+".\n");
	say(QCTNAME(TP)+" sighs, wondering when the day will come when "+
	  HE_SHE(TP)+" will be able to make an item like "+CAP(str)+".\n");
	return 1;
    }
    return 0;
}

int
smshow(string str) {
    object *targets;
    object item;
    string *parts;

    notify_fail("Show what to whom?\n");

    if (!str) return 0;

    parts=explode(str," ");

    item=find_item(parts[0],"show");  /* check find item!!!! */
    if (!present(item,TP)) return 0;

    if ((sizeof(parts)==1) || (parts[1]=="all")) {
	allbb(" shows you "+HIS_HER(TP)+" "+item->short()+", while smiling"+
	  " proudly.");
	write("You show your "+item->short()+" to everyone so that they"+
	  " can see the fine item.\n");
	return 1;
    }

    if (sizeof(parts)!=2) return 0;

    targets = parse_this(parts[0], "[at] [the] %l");
    if (!sizeof(targets)) return 0;

    item=find_item(parts[1],"show");  /* check find item!!!! */
    if (!present(item,TP)) return 0;

    actor("You show your "+item->short()+" to ", targets, ", while smiling"+
      " proudly.");
    targetbb(" show you "+HIS_HER(TP)+" "+item->short()+", while smiling"+
      " proudly.",targets);
    all2actbb("  shows ", targets, " "+HIS_HER(TP)+" "+item->short()+
      ", while smiling proudly.");
    return 1;
}


int
smsuggest(string str) {
    object *targets;

    notify_fail("Suggest a change of weapons to whom?\n");

    if ((!str) || (str=="all")) {
	allbb(" suggests to you that you replace your old useless weapons"+
	  " and armours with new ones "+HE_SHE(TP)+" forged himself.");
	write("You suggest that everyone replaces their old useless weapons"+
	  " and armours with new ones forged by yourself.\n");
	return 1;
    }

    targets = parse_this(str, "[at] [the] %l");

    if (!sizeof(targets)) return 0;

    actor("You suggest", targets, " to replace the old useless weapons"+
      " and armours with new ones forged by yourself.");
    targetbb(" suggests to you that you replace your old useless weapons"+
      " and armours with new ones "+HE_SHE(TP)+" forged himself.",
      targets);
    all2actbb("  suggests ", targets, " to replace the old useless weapons "+
      " and armours with new ones "+HE_SHE(TP)+" forged himself.");
    return 1;
}

int
smtell(string str) {
    object person;
    object *to_tell;

    notify_fail("Tell whom what?\n");
    if ((!strlen(str)) || (str=="all")) {
	TP->catch_msg("You start telling about all the finer details in"+ 
	  " forging a weapon.\n");
	say(QCTNAME(TP)+" starts telling you about all the finer details in"+ 
	  " forging a weapon, and after a very long lecture you feel as if"+ 
	  " you could stand up and sleep.\n");
	return 1;
    }

    if ((!parse_command(str, ENV(TP), "[the] %i", to_tell)) ||
      (!sizeof(to_tell = NORMAL_ACCESS(to_tell, 0, 0)))) {
	return 0;
    }

    if (sizeof(to_tell) != 1) {
	write("Please select only one person to tell.\n");
	return 1;
    }
    else {
	person = to_tell[0];
    }
    to_tell+=({TP});

    if (!living(person)) {
	write("Feels a bit silly, doesn't it?\n");
	return 1;
    }

    TP->catch_msg("You start telling "+QCTNAME(person)+" about all the"+ 
      " finer details in forging a weapon.\n");
    person->catch_msg(QCTNAME(TP)+" starts telling you about all the"+ 
      " finer details in forging a weapon, and after a very long"+ 
      " lecture you feel as if you could stand up and sleep.\n");
    tell_room(ENV(TP),QCTNAME(TP)+" starts telling "+QTNAME(person)+" about"+
      " all the finer details in forging a weapon, and after a very long"+
      " lecture "+QTNAME(person)+" starts to look extremely sleepy.\n",
      to_tell);

    set_alarm(3.0, 0.0, &person->command("yawn"));
    return 1;
}



int
smtired() {
    write("You smile tiredly though a proud gleam is visible in your eyes.\n");
    say(QCTNAME(TP)+" smiles tiredly though a proud gleam is visible in "+
      HIS_HER(TP)+" eyes.\n");
    return 1;
}

int
smvictory(string str) {
    if (!present("corpse",ENV(TP))) {
	write("But there are no defeated foes nearby!\n");
	return 1;
    }

    TP->command("grin grimly");

    write("You kick the corpse of your foe, saying: This is what you get"+
      " from using bad armours.\n");
    allbb(" kicks the corpse of "+HIS_HER(TP)+" foe, saying: This is what you"+
      " get for using bad armours.");
    return 1;
}

int
smwave(string str) {
    object *targets;

    notify_fail("Wave to whom?\n");

    if ((!str) || (str=="all")) {
	allbb(" waves, saying: May your forge fires burn fiercely.");
	write("You wave, saying: May your forge fires burn fiercely.\n");
	return 1;
    }

    targets = parse_this(str, "[at] [the] %l");

    if (!sizeof(targets)) return 0;

    actor("You wave to", targets, " saying: May your forge fires burn"+
      " fiercely.");
    targetbb(" waves to you, saying: May your forge fires burn fiercely.",
      targets);
    all2actbb("  waves to ", targets, ", saying: May your forge fires burn"+
      " fiercely.");
    return 1;
}


int
smwipe(string str) {
    write("You wipe the sweat from your brow, recalling the heat from the"+
      " forgefires.\n");
    allbb(" wipes the sweat from "+HIS_HER(TP)+" brow, recalling the heat"+
      " from the forgefires.");
    return 1;
}




 

object
find_item(string str,string error) {
    object obj;
    object *to_mark;

    notify_fail(CAP(error)+" what?\n");
    if (!strlen(str))
    {
	return obj;
    }

    if ((!parse_command(str, TP, "[the] %i", to_mark)) ||
      (!sizeof(to_mark = NORMAL_ACCESS(to_mark, 0, 0))))
    {
	return obj;
    }

    if (sizeof(to_mark) != 1)
    {
	write("Please select only one item to "+error+".\n");
	return obj;
    }
    else
    {
	obj = to_mark[0];
    }

    return obj;
}

/*
 * Find whetstone ability
*/

int
find(string str) {
    if ((TP->query_guild_name_lay()!=GUILD_NAME) &&
      (TP->query_guild_name_occ()!=GUILD_NAME)) {
	return 0;
    }

    if (str!="whetstone") return 0;
    if (ENV(TP)->query_prop(ROOM_I_INSIDE)) {
	write("You cannot search for whetstones when you are inside!\n");
	return 1;
    }

    if (objectp(TP->query_attack())) {
	TP->catch_msg("You don't have time to search for anything while"+
	  " you are in combat.\n");
	return 1;
    }

    write("You start to search for something to sharpen your weapons with.\n");
    say(QCTNAME(TP)+" starts to search for something to sharpen "+HIS_HER(TP)+
      " weapons with.\n");
    if (random(TP->query_skill(SS_AWARENESS))>10)
	set_alarm(5.0, 0.0, &whet_found());
    else {
	write("You are not able to find a whetstone.\n");
	say(QCTNAME(TP)+" doesn't seem to find anything.\n");
    }
    return 1;
}

void
whet_found() {
    object stone;

    FIXEUID

    stone = clone_object(SMITHSDIR_OBJ+"sm_whet");
    stone->move(TP);
    write("You find a small rock that might be used to sharpen weapons"+
      " with.\n");
    say(QCTNAME(TP)+" has found a small rock.\n");
}


