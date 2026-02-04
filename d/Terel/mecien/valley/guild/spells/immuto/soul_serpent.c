/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * soul_serpent.c
 *
 * This soul holds the general commands and feelings of the Mystic Bear
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

#define TP             this_player()
#define TO             this_object()
#define NF(xx)         notify_fail(xx)

/**********************************************************************
* Soul identifying and autoloading
**********************************************************************/

string get_soul_id() { return "Mystic Serpent"; }

int query_cmd_coul() { return 1; }

/**********************************************************************
* The list of verbs and functions. Please add new in alfabetic order.
**********************************************************************/

mapping
query_cmdlist()
{
   seteuid(getuid());
   return ([
         "hiss":"hiss",
         "rise":"rise",
         "gaze":"gaze"
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

/********************* hiss   *************************************/
int
hiss(string str)
{
   object *ob;

   if (!str) {
      write("You send forth a serpentine hiss.\n");
      say(QCTNAME(TP) + " hisses.\n");
      return 1;
   }
   
   ob = my_parse_this(str, "[at] %l");
   
   if (!sizeof(ob)) {
     NF(capitalize(query_verb()) + " who?\n");
     return 0;
   }
   
   actor("You send forth a serpentine hiss at", ob);
   target(" sends forth a serpentine hiss at you.", ob);
   all2act("  sends forth a serpentine hiss toward", ob);

   return 1;
}

/********************* rise   *************************************/
int
rise(string str)
{
   if (!str) {
      write("You rise up on your coils.\n");
      say(QCTNAME(TP) + " rises up on " + TP->query_possessive() +
          "coils.\n");
      return 1;
   }
   return 0;
}

/********************** gaze  *****************************************/
int
gaze(string str)
{
   int i;
   object *ob;

   if (!str) {
       write("You cast your gaze about this place.\n");
       say(QCTNAME(TP) + " gazes about this area.\n");
       return 1;
   }

   ob = my_parse_this(str, "[at] %l");
   
   if (!sizeof(ob)) {
     NF(capitalize(query_verb()) + " who?\n");
     return 0;
   }
   
   actor("You gaze at", ob, " with your serpentine eyes.");
   if (sizeof(ob) == 1) {
      target(" gazes at you with its serpentine eyes. You feel bewitched.", ob);
      all2act("  gazes at", ob, " with its serpentine eyes.");
      if (TP->query_stat(SS_DIS) > ob[0]->query_stat(SS_DIS)) {
         tell_room(environment(TP), QCTNAME(ob[0]) + " seems shaken.\n",
                  ({TP, ob[0]}));
         ob[0]->command("$worship serpent");
      }
    } else {
      target(" gazes at you with its serpentine eyes.", ob);
      all2act("  gazes at", ob, " with its serpentine eyes.");
   }

   return 1;
}
