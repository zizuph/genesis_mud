/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * soul_cricket.c
 *
 * This soul holds the general commands and feelings of the Mystic Flea
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
#define IS_WIZ(xx)     xx->query_wiz_level()

string get_soul_id() { return "Mystic Cricket"; }

int query_cmd_coul() { return 1; }

mapping
query_cmdlist()
{
   seteuid(getuid());
   return ([
         "bite":"bite",
         "crick":"crick",
         "jump":"jump",
         "look":"look",
         "examine":"look",
         "l":"look",
         "exa":"look",
         "tickle":"tickle"
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
               form, oblist))) return ({});

   oblist = NORMAL_ACCESS(oblist, 0, 0);

   if (!sizeof(oblist)) return ({});

   for (i = 0; i < sizeof(oblist); i++) {
      if (objectp(oblist[i]) && (TP != oblist[i]) &&
         CAN_SEE(TP, oblist[i])) tmplist += ({ oblist[i] });
   }
   return tmplist;
}

/********************** crick ***************************************/
int
crick(string str)
{
    object where;

    if (str) return 0;

    where = environment(TP);
    write("You utter: CRICK CRRRICK\n");
    if (living(where)) {
        tell_room(environment(where), "CRICK CRRRICK\n");
        tell_room(environment(where), "The strange sound seems to " +
           "come from "+QTNAME(where)+".\n", where);
        where->catch_msg("The strange sound comes from you!?\n");
    } else {
        say("CRICK CRRRICK\n");
    }
    return 1;
}

/********************** bite ***************************************/
int
bite(string str)
{
   object where;

   where = environment(TP);
   NF("No one to bite here!\n");
   if (!living(where)) return 0;

   TP->catch_msg("You bite " + QTNAME(where) + ".\n");
   where->catch_msg("Something bites you. Maybe a flea?\n");
   return 1;
}

/********************** jump *****************************************/
int
jump(string str)
{
   object where;
   object *ob;

   where = environment(TP);
   if (!str) {
       if (living(where)) {
          TP->catch_msg("You jump off " + QTNAME(where) + "\n");
          where->catch_msg("Something tickles you. Maybe a flea?\n");
          TP->move_living("M", environment(where));
       } else {
          write("You jump just like a real cricket.\n");
          say(QCTNAME(TP) + " leaps a small distance.\n");
       }
       return 1;
   }
   NF("Jump who?\n");
   ob = my_parse_this(str, "[on] %l");
   if (!sizeof(ob)) return 0;
   if (sizeof(ob) > 1) return 0;

   if (IS_WIZ(ob[0])) {
       TP->catch_msg("Your try to jump on " + QTNAME(ob[0]) +
                     " failed.\n");
       return 1;
   }
   if (TP->move(ob[0])) {
       TP->catch_msg("Your try to jump on " + QTNAME(ob[0]) +
                     " failed.\n");
       return 1;
   }
   TP->catch_msg("You jump up on " + QTNAME(ob[0]) + ".\n");
   ob[0]->catch_msg("Something tickles you. Maybe a flea?\n");
   return 1;
}

/********************** look *****************************************/
int
look(string str)
{
   object where;
   object *ob, *tmp;
   int i;
   string dum, desc;

   where = environment(TP);
   if (!living(where)) return 0;

   if (!str) {
       tmp = ({ });
       ob = all_inventory(where);
       for (i=0; i<sizeof(ob); i++) {
           if (ob[i] != TP && CAN_SEE(TP, ob[i])) tmp += ({ ob[i] });
       }
       desc = COMPOSITE_DEAD(tmp);
       TP->catch_msg(break_string("You find "+desc+".\n", 72));
       return 1;
   }

   desc = str;
   if (sscanf(desc, "at %s", dum)==1) desc= dum;
   if (desc == "me" || desc == "myself") desc = TP->query_name();

   ob = FIND_STR_IN_OBJECT(desc, where);

   NF(capitalize(query_verb()) + " what?\n");
   if (!sizeof(ob)) return 0;

   for (i=0; i<sizeof(ob); i++) {
       TP->catch_msg(ob[i]->long());
   }
   return 1;
}

/********************** tickle ***************************************/
int
tickle(string str)
{
   object where;

   where = environment(TP);
   NF("No one to tickle here!\n");
   if (!living(where)) return 0;

   TP->catch_msg("You tickle " + QTNAME(where) + ".\n");
   where->catch_msg("Something tickles you. Maybe a flea?\n");
   return 1;
}
