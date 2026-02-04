/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * soul_wolf.c
 *
 * This soul holds the general commands and feelings of the Mystic Wolf
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

string get_soul_id() { return "Mystic Wolf"; }

int query_cmd_coul() { return 1; }

/**********************************************************************
* The list of verbs and functions. Please add new in alfabetic order.
**********************************************************************/

mapping
query_cmdlist()
{
   seteuid(getuid());
   return ([
         "howl":"howl",
         "growl":"growl",
         "snarl":"snarl"
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

/********************** howl *****************************************/
int
howl(string str)
{
   object *ob;

   if (!str) {
       write("You howl like a real wolf.\n");
       say(QCTNAME(TP) + " howls loudly.\n");
       return 1;
   }
   ob = my_parse_this(str, "[at] %l");
   if (!sizeof(ob)) {
     NF(capitalize(query_verb()) + " who?\n");
     return 0;
   }
   
   actor("You howl at", ob);
   target(" howls at you.", ob);
   all2act("  howls at", ob);

   return 1;
}

/********************* growl  *************************************/
int
growl(string str)
{
   object *ob;

   if (!str) {
      write("You growl like a real wolf.\n");
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

/********************* snarl  *************************************/
int
snarl(string str)
{
   object *ob;

   if (!str) {
      write("You snarl like a real wolf.\n");
      say(QCTNAME(TP) + " snarls.\n");
      return 1;
   }
   ob = my_parse_this(str, "[at] %l");
   if (!sizeof(ob)) {
     NF(capitalize(query_verb()) + " who?\n");
     return 0;
   }
   
   actor("You snarl at", ob);
   target(" snarls at you.", ob);
   all2act("  snarls at", ob);
   
   return 1;
}
