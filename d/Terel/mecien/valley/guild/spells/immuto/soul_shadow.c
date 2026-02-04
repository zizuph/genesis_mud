/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * soul_bear.c
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

string get_soul_id() { return "Mystic Bear"; }

int query_cmd_coul() { return 1; }

/**********************************************************************
* The list of verbs and functions. Please add new in alfabetic order.
**********************************************************************/

mapping
query_cmdlist()
{
   seteuid(getuid());
   return ([
         "growl":"growl",
         "raise":"raise",
         "stare":"stare"
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

/********************* growl  *************************************/
int
growl(string str)
{
   object *ob;

   if (!str) {
      write("You growl like a real bear.\n");
      say(QCTNAME(TP) + " growls.\n");
      return 1;
   }
   ob = my_parse_this(str, "[at] %l");
   
   if (!sizeof(ob)) {
      NF(capitalize(query_verb()) + " who?\n");
      return 0;
   }

   actor("You growl at", ob);
   target(" growls at you.", ob);
   all2act("  growls at", ob);
   
   return 1;
}

/********************* raise  *************************************/
int
raise(string str)
{
   if (!str) {
      write("You raise on your hind legs.\n");
      say(QCTNAME(TP) + " raises on the hind legs.\n");
      return 1;
   }
   return 0;
}

/********************** stare *****************************************/
int
stare(string str)
{
   object *ob;

   if (!str) {
       write("You stare into empty space.\n");
       say(QCTNAME(TP) + " stares into empty space.\n");
       return 1;
   }
   
   ob = my_parse_this(str, "[at] %l");
   
   if (!sizeof(ob)) {
      NF(capitalize(query_verb()) + " who?\n");
      return 0;
   }

   actor("You stare at", ob);
   target(" stares at you.", ob);
   all2act("  stares at", ob);
   return 1;
}
