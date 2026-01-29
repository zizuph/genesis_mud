/* rotten fruit that can be thrown at other livings
   and will add some dirtiness to them.
   Modified by Ashbless from Shadowhand's Balloon.
 */

inherit "/std/object";

#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include <macros.h>

void
create_object()
{

   set_name("fruit");
   set_adj("rotten");
   set_pname("fruits");
   set_long(BS(
       "The fruit is native to the highlands above Kabal " +
       "and looks to be a hybrid of an apple and a pear. " +
       "It is well past ripeness and the odor is quite potent.\n"));

   add_prop(OBJ_I_WEIGHT, 200);  /* 1/5 of a kg    */
   add_prop(OBJ_I_VOLUME, 200);  /* 1/5 of a liter */

}

void
init()
{
   ::init();
   add_action("do_throw", "throw", 0);
}


string
desc_vbfc(object ob)  { return QTNAME(ob); }


/* return the QTNAMES of all objects the player throws at */

string
desc_many(object *player)
{
   string *desc_list, str;

   desc_list = map(player,"desc_vbfc",TO);

   if (sizeof(desc_list) == 1)
     str = desc_list[0];
   else if (sizeof(desc_list) == 2)
     str = desc_list[0] + " and " + desc_list[1];
   else
     str = implode(desc_list[0..sizeof(desc_list) - 2], ", ") +
       " and " + desc_list[sizeof(desc_list) - 1];

   return str;
}





int
do_throw(string arg)
{
   object *player, *oblist, *ob;
   string what, name;
   int i, is_dirty;

   arg = L(arg);
   player = ({});
   
   notify_fail("Throw what at whom?\n");
   if (!arg || sscanf(arg, "%s at %s", what, name) != 2)
      return 0;
   
   notify_fail("What do you want to throw?\n");
   if (what != "fruit" && what != "rotten fruit")
      return 0;

   notify_fail("You can't see anything!\n");
   if (!CAN_SEE_IN_ROOM(TP))
     return 0;
   
   notify_fail("You can't see anyone by that name here!\n");
   if (!parse_command(name,E(TP),"%l",oblist))
      return 0;
   if (!sizeof(oblist))
     return 0;

   for (i = 0; i < sizeof(oblist); i++)
   {
     if (objectp(oblist[i]) && living(oblist[i])
     && TP != oblist[i]  && CAN_SEE(TP,oblist[i]))
       player = player + ({oblist[i]}); 
   }
   if (!sizeof(player))
     return 0;

   this_player()->catch_msg("SPLAT!!\n" + BS(
      "With a wicked grin, you throw a rotten " +
      "fruit at " + QTNAME(player[0]) + ", laughing uproariously as it " +
      "covers " + player[0]->query_objective() + " from head to toe.\n")); 
   player[0]->catch_msg("SPLAT!\n" + BS(
      QCTNAME(this_player()) + " throws a rotten fruit " +
      "at you with a wicked grin. It explodes, covering you from head " +
      "to toe. " + TP->query_pronoun() + " laughs uproariously.\n"));
   tell_room(environment(this_player()), "SPLAT!!\n" + BS(
      QCTNAME(this_player()) + " throws " +
      "a rotten fruit at " + QTNAME(player[0]) + " with a grin. It covers " +
      QTNAME(player[0]) + " from head to toe, and " + QTNAME(this_player()) +
      " laughs uproariously.\n"), ({player[0], this_player()}));

   player[0]->add_prop(LIVE_I_DIRTY,player[0]->query_prop(LIVE_I_DIRTY) + 10);
   seteuid(getuid(this_object()));
   ob = deep_inventory(player[0]);
   for (i = 0; i < sizeof(ob); i++)
     if (ob[i]->id("dirty"))
       is_dirty = 1;
   if (!is_dirty)
     clone_object(KALAD(std/dirtiness))->move(player[0]);

   remove_object();
   return 1;
}



