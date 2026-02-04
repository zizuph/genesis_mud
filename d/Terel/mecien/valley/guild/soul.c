/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * mystic_soul.c
 *
 * This soul holds the general commands and feelings of the Mystic Order
 * It is based upon Nick's soul for the Solamnian Knights
 * (copied by Mortricia from /doc/examples/solamn/solamn_soul.c)
 *
 */

inherit "/cmd/std/soul_cmd";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include "/secure/std.h"

#define TP             this_player()
#define TO             this_object()
#define NF(xx)         notify_fail(xx)
#define GUILD_HELP_DIR "/d/Terel/mecien/valley/guild/help/"
#define GUILD_NAME     "The Ancient Mystic Order"
#define T_WIZ(xx)      xx->query_wiz_level() &&\
                       SECURITY->query_wiz_dom(xx)=="Terel"
#define MEMBER(xx)     xx->query_guild_member(GUILD_NAME)
#define MED_TIME       30
#define MED_MANA_LIM   100
#define MED_INC_FAT    2
#define PARA_OBJ       "/d/Terel/mecien/valley/guild/paralyze"

/**********************************************************************
* Soul identifying and autoloading
**********************************************************************/

string get_soul_id() { return "Mystic Order"; }

int query_cmd_coul() { return 1; }

/**********************************************************************
* The list of verbs and functions. Please add new in alfabetic order.
**********************************************************************/

mapping
query_cmdlist()
{
   seteuid(getuid(TO));
   return ([
         "adore":"adore",
         "beseech":"beseech",
         "chant":"chant",
         "farewell":"farewell",
         "hail":"hail",
         "help":"help",
       "laugh":"laugh",
         "meditate":"meditate",
         "ms":"ms",
         "reverence":"reverence",
         "ridicule":"ridicule",
         "salute":"salute",
         "scold":"scold",
         "scorn":"scorn",
	"smile":"smile",
         "wail":"wail"
      ]);
}

mixed
my_parse_this(string str, string form)
{
   object   *oblist, *tmplist;
   int      i;
   
   tmplist = ({});
   if (!CAN_SEE_IN_ROOM(TP)) return tmplist;
   
   if (!str || (!parse_command(lower_case(str), environment(TP),
               form, oblist)))
   return ({});
   
   oblist = NORMAL_ACCESS(oblist, 0, 0);
   
   if (!sizeof(oblist)) return ({});
   
   for (i = 0; i < sizeof(oblist); i++) {
      if (objectp(oblist[i]) && living(oblist[i]) &&
            (TP != oblist[i]) && CAN_SEE(TP, oblist[i]))
      tmplist = tmplist + ({ oblist[i] });
   }
   return tmplist;
}

/**********************************************************************
* Here follows the functions. New functions should be added in
* alphabetical order.
*********************************************************************/

/********************* adore *****************************************/
int
adore(string str)
{
   object *ob;
   
   NF("Adore who?\n");
   if (!str) return 0;
   ob = my_parse_this(str, "[the] %l");
   if (!sizeof(ob)) return 0;
   
   TP->catch_msg("You grant " + QTNAME(ob[0]) + " the adoration that " +
      ob[0]->query_pronoun() + " deserves.\n");
   ob[0]->catch_msg(QCTNAME(TP) + " adores you.\n");
   say(QCTNAME(TP) + " shows adoration for " + QTNAME(ob[0]) + ".\n",
      ({ ob[0], TP }));
   return 1;
}

/********************* beseech ***************************************/
int
beseech(string str)
{
   object *ob;
   
   NF("Beseech who?\n");
   if (!str) return 0;
   ob = my_parse_this(str, "[the] %l");
   if (!sizeof(ob)) return 0;
   
   TP->catch_msg("You beseech " + QTNAME(ob[0]) + ".\n");
   ob[0]->catch_msg(QCTNAME(TP) + " beseeches you.\n");
   say(QCTNAME(TP) + " beseeches " + QTNAME(ob[0]) + ".\n",
      ({ ob[0], TP }));
   return 1;
}

/********************* chant *****************************************/
int
chant(string str)
{
   object *ob;
   int i;
   
   if (!str) {
      write("You chant a hymn to the Ancient Ones.\n");
      say(QCTNAME(TP) + " chants an ancient hymn.\n");
      return 1;
   }
   
   NF("Chant who?\n");
   ob = my_parse_this(str, "[the] %l");
   if (!sizeof(ob)) return 0;
   
   for (i = 0; i < sizeof(ob); i++) {
      TP->catch_msg("You chant the honour of " + QTNAME(ob[i]) +
         ".\n");
      if (ob[i]->query_wiz_level()) {
         ob[i]->catch_msg(QCTNAME(TP) + " chants your greatness.\n");
        } else {
         ob[i]->catch_msg(QCTNAME(TP) + " chants your honour.\n");
        }
   }
   return 1;
}

/********************* farewell *************************************/
int
farewell(string str)
{
   object *ob;
   
   if (!str || str == "all") {
      write("You bid farewell to everyone.\n");
      say(QCTNAME(TP) + " bids farewell to you.\n");
      return 1;
   }
   NF("Farewell who?\n");
   ob = my_parse_this(str, "[to] %l");
   if (!sizeof(ob)) return 0;
   if (sizeof(ob) > 1) return 0;
   
   TP->catch_msg("You bid farewell to " + QTNAME(ob[0]) + ".\n");
   ob[0]->catch_msg(QCTNAME(TP) + " bids farewell to you.\n");
   say(QCTNAME(TP) + " bids farewell to " + QTNAME(ob[0]) + ".\n",
      ({ob[0], TP}));
   return 1;
}


/********************* hail ****************************************/
int
hail(string str)
{
   object *ob;
   string proper;
   int rank;
   
   if (!str || str == "all") {
      write("You hail all present.\n");
      say(QCTNAME(TP) + " hails everyone with a sign of peace.\n");
      return 1;
   }
   NF("Hail who?\n");
   ob = my_parse_this(str, "[to] %l");
   if (!sizeof(ob)) return 0;
   if (sizeof(ob) > 1) return 0;
   
   NF("This person is not of the Order.\n");
   if (!MEMBER(ob[0])) return 0;
   
   rank = ob[0]->query_stat(SS_OCCUP);
   switch(rank) {
       case 150..9999: proper = "most arcane majesty"; break;
       case 100..149:  proper = "most imperious reverence"; break;
       case 90..99:    proper = "my hallowed lord"; break;
       case 80..89:    proper = "your exalted grace"; break;
       case 70..79:    proper = "most hallowed master"; break;
       case 60..69:    proper = "hallowed elder"; break;
       case 50..59:    proper = "hallowed reverence"; break;
       case 40..49:    proper = "most honoured master"; break;
       case 30..39:    proper = "honoured elder"; break;
       case 20..29:    proper = "honoured reverence"; break;
       case 10..19:    proper = "mystic friend"; break;
       default:        proper = "mystic novice"; break;
   }
   
   if (TP->query_stat(SS_OCCUP) < ob[0]->query_stat(SS_OCCUP)) {
       TP->catch_msg("You hail "+QTNAME(ob[0])+
                     " in solemn humility.\n");
       ob[0]->catch_msg(QCTNAME(TP)+" kneels before you and chants: "+
                        "Hail, " + proper + "\n");
       say(QCTNAME(TP) + " kneels before " + QTNAME(ob[0]) + 
           " and chants: Hail, " + proper + "\n", ({ob[0], TP}));
       return 1;
   }
   TP->catch_msg("You hail " + QTNAME(ob[0]) + " with a mystic blessing.\n");
   ob[0]->catch_msg(QCTNAME(TP) + " hails you with a mystic blessing.\n");
  say(QCTNAME(TP) + " hails " + QTNAME(ob[0]) + 
     " with a mystic blessing.\n", ({ob[0], TP}));
   return 1;
}

/************** help *************************************************/
int
help(string str)
{
    string subject, filename;

    if (!str) return 0;

    if (sscanf(str, "mystic %s", subject) != 1) return 0;

    seteuid(getuid(TO));
    filename = GUILD_HELP_DIR + subject;
    if (file_size(filename) > 0) {
        write(read_file(filename));
        return 1;
    }

    NF("No help on that subject I'm afraid.\n");
    return 0;
}

int
laugh(string str)
{
if(!str) return 0;
if(str == "mysteriously"){
write("You laugh mysteriously.\n");
say(QCTNAME(this_player()) + " laughs mysteriously.\n");
return 1;
}
return 0;
}

/************** meditate *********************************************/
int
meditate(string str)
{
    object para;

    if (str != "here") return 0;

    write("You close your eyes and start to meditate.\n");
    say(QCTNAME(TP) + " closes " + TP->query_possessive() +
	" eyes and starts to meditate.\n");
    seteuid(getuid(TO));
    para = clone_object(PARA_OBJ);
    para -> set_stop_verb("");              /* No stop verb!    */
    para -> set_remove_time(MED_TIME);      /* Duration         */
    para -> set_stop_fun("stop_meditate");  /* Stop func called */
    para -> set_stop_object(TO);            /* in this object   */
    para -> set_stop_message("You stop to meditate.\n");
    para -> set_fail_message("You cannot do that while meditating.\n");
    para -> move(TP);
    return 1;
}

void
stop_meditate(object ob)
{
    int fat, m_fat;

    fat = ob -> query_fatigue();
    m_fat = ob -> query_max_fatigue();

    if (ob -> query_mana() >= MED_MANA_LIM) {
	if (fat + MED_INC_FAT < m_fat) {
	    ob -> add_fatigue(MED_INC_FAT);
            ob -> catch_msg("You open your eyes and feel relaxed.\n");
	} else {
	    ob -> set_fatigue(m_fat);
            ob -> catch_msg("You open your eyes and feel " +
			    "very relaxed.\n");
	}
    } else {
        ob -> catch_msg("You open your eyes.\n");
    }

    tell_room(environment(ob), QCTNAME(ob) + " opens " +
              ob -> query_possessive() + " eyes.\n", ob);
}

/********************* ms (mystic speech) ****************************/
int
ms(string msg)
{
    int i;
    object *ob;

    if (TP->query_skill(SS_LANGUAGE) < 20) {
        NF(break_string(
	    "To be able to speak the Ancient Mystic Tongue you " +
            "must improve thy language skills.\n", 72));
        return 0;
    }

    if (!msg) {
        NF("Say what in the mystic language?\n");
        return 0;
    }

    if (TP->query_get_echo()) {
        write(break_string("You intone: " + msg +
	      ", using the Ancient Tongue.\n", 72));
    } else {
	write("Ok.\n");
    }

    ob = all_inventory(environment(TP));
    for (i=0; i<sizeof(ob); i++) {
        if (living(ob[i]) && ob[i] != TP) {
            if (MEMBER(ob[i]) && ob[i]->query_skill(SS_LANGUAGE) > 19) {
                ob[i]->catch_msg(QCTNAME(TP) + " intones:\n" +
		       break_string(msg + "\n", 72));
            } else {
                ob[i]->catch_msg(QCTNAME(TP) +
                       " speaks in a mystical language.\n");
	    }
        }
    }
    return 1;
}

/********************* reverence *************************************/
int
reverence(string str)
{
    object *ob;

    NF("Reverence who?\n");
    if (!str) return 0;
    ob = my_parse_this(str, "[to] %l");
    if (!sizeof(ob)) return 0;
    if (sizeof(ob) > 1) return 0;
    TP->catch_msg("You show your reverence for " + QTNAME(ob[0]) +
		  ".\n");
    ob[0]->catch_msg(QCTNAME(TP) + " shows " +
		  TP->query_possessive() + " reverence for you.\n");
    say(QCTNAME(TP) + " shows " + TP->query_possessive() +
		  " reverence for " + QTNAME(ob[0]) + ".\n",
	          ({ob[0], TP}));
    return 1;
}

/********************* ridicule *************************************/
int
ridicule(string str)
{
    object *ob;
    int my_wis, ob_wis;
    string xself;

    NF("Ridicule who?\n");
    if (!str) return 0;
    ob = my_parse_this(str, "[the] %l");
    if (!sizeof(ob)) return 0;

    my_wis = TP->query_stat(SS_WIS);
    ob_wis = ob[0]->query_stat(SS_WIS);
    if (ob[0]->query_wis_level() && !(TP->query_wiz_level()))
	ob_wis *= 2;
    if (TP->query_gender() == 0) xself="himself";
    if (TP->query_gender() == 1) xself="herself";
    if (TP->query_gender() == 2) xself="itself";

    if (my_wis + random(my_wis) > ob_wis + random(ob_wis)) {
	TP->catch_msg("You managed to ridicule "+QTNAME(ob[0])+".\n");
        ob[0]->catch_msg(QCTNAME(TP) + " managed to ridicule you.\n");
        say(QCTNAME(TP)+" managed to ridicule "+QTNAME(ob[0])+".\n",
	    ({ ob[0], TP }));
    } else {
	TP->catch_msg("You are making a fool of yourself instead.\n");
	ob[0]->catch_msg(QCTNAME(TP) + " makes a fool of " + xself +
		  " when trying to ridicule you.\n");
        say(QCTNAME(TP) + " makes a fool of " + xself +
		  " when trying to ridicule "+QTNAME(ob[0])+".\n",
	    ({ ob[0], TP }));
    }
    return 1;
}

/********************* salute *************************************/
int
salute(string str)
{
    int i;
    object *ob;
    string x;

    if (!str) {
	write("You salute everyone.\n");
	say(QCTNAME(TP) + " salutes you.\n");
	return 1;
    }
    NF("Salute who?\n");
    ob = my_parse_this(str, "[the] %l");
    if (!sizeof(ob)) return 0;

    for (i=0; i<sizeof(ob); i++) {
	if (T_WIZ(ob[i])) {
	    x = "king";
	    if (ob[i]->query_gender() == 1) x = "queen";
	    TP->catch_msg("You salute " + QTNAME(ob[i]) +
			  " as your " + x + ".\n");
	    ob[i]->catch_msg(QCTNAME(TP) + " salutes you as " +
			  TP->query_possessive() + " " + x + ".\n");
	} else if (MEMBER(ob[i]) || ob[i]->query_wiz_level()) {
	    TP->catch_msg("You salute "+QTNAME(ob[i])+".\n");
	    ob[i]->catch_msg(QCTNAME(TP) + " salutes you.\n");
	} else {
	    TP->catch_msg("You bid "+QTNAME(ob[i])+" welcome.\n");
	    ob[i]->catch_msg(QCTNAME(TP) + " bids you welcome.\n");
	}
    }
    return 1;
}

/********************* scold *************************************/
int
scold(string str)
{
    object *ob;

    if (!str || str == "all") {
	write("You scold each and all.\n");
	say(QCTNAME(TP) + " scolds each and all.\n");
	return 1;
    }
    NF("Scold who?\n");
    ob = my_parse_this(str, "[the] %l");
    if (!sizeof(ob)) return 0;

    TP->catch_msg("You give "+QTNAME(ob[0])+ " a real scolding.\n");
    ob[0]->catch_msg(QCTNAME(TP) + " scolds you for being such "+
		     "a scourge.\n");
    say(QCTNAME(TP) + " scolds " + QTNAME(ob[0]) +
	" for being such a scourge.\n", ({ ob[0], TP }));
    return 1;
}

/********************* scorn *************************************/
int
scorn(string str)
{
    object *ob;
    string x;

    NF("Scorn who?\n");
    if (!str) return 0;
    ob = my_parse_this(str, "[the] %l");
    if (!sizeof(ob)) return 0;
    if (sizeof(ob) > 1) return 0;
    if (ob[0]->query_gender() == 0) x="him";
    if (ob[0]->query_gender() == 1) x="her";
    if (ob[0]->query_gender() == 2) x="it";

    TP->catch_msg("You tell "+QTNAME(ob[0])+ " that you scorn " +
		  x + ".\n");
    ob[0]->catch_msg(QCTNAME(TP) + " scorns you.\n");
    say(QCTNAME(TP) + " scorns " + QTNAME(ob[0]) +
	" with great contempt.\n",
	({ ob[0], TP }));
    return 1;
}

int
smile(string str)
{
if(!str) return 0;
if(str == "mysteriously"){
write("You smile mysteriously.\n");
say(QCTNAME(this_player()) + " smiles mysteriously.\n");
return 1;
}
return 0;
}

/********************** wail *************************************/
int
wail(string str)
{
    object *ob;

    if (!str) {
	write("You wail loudly.\n");
	say(QCTNAME(TP) + " wails loudly in anguish.\n");
	return 1;
    }
    NF("Wail to whom?\n");
    ob = my_parse_this(str, "[to] %l");
    if (!sizeof(ob)) return 0;
    if (sizeof(ob) > 1) return 0;
    TP->catch_msg("You wail in front of " + QTNAME(ob[0]) + ".\n");
    ob[0]->catch_msg(QCTNAME(TP) + " wails in front of you.\n");
    say(QCTNAME(TP) + " wails in front of " + QTNAME(ob[0]) + ".\n",
	({ob[0], TP}));
    return 1;
}
