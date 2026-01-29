
// A tablet to poison Kilnar's water with for
// the outpost water quest in Avenir.
//   -Cirion, Jan 1996

inherit "/std/food";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/water_quest.h"
#include <poison_types.h>

create_food()
{
    set_amount(2);

    set_name("tablet");
    set_adj(({"white", "powdery"}));
    set_short("white powdery tablet");
    set_long("This is a tiny white tablet. It looks like "
            +"it would dissolve easily if dropped into "
            +"liquid.\n");

    setuid();
    seteuid(getuid());
}

/* This is the function that should be called from the
 * drink should the vbfc for set_drink_msg ever be
 * fixed.
 */
void do_poison()
{
   object poison;
   object who;

   setuid();
   seteuid(getuid());

   who = ENV(calling_object());

   poison = clone_object("/std/poison_effect");
   poison->set_interval(20);
   poison->set_time(400);
   poison->set_damage(({POISON_FATIGUE,40,POISON_HP,40,POISON_MANA,50}));
   poison->set_strength(34);
   poison->set_poison_type("drink");

   poison->move(who);
   WRITE_THIS_LOG( QUEST_FILE, who->query_name()
      +" drank a poisoned drink at "+file_name(ENV(who))+".\n" );
   poison->start_poison();
}

void special_effect(int number)
{
   object poison;

   poison = clone_object("/std/poison_effect");
   poison->set_interval(20);
   poison->set_time(400);
   poison->set_damage(({POISON_FATIGUE,40,POISON_HP,40,POISON_MANA,50}));
   poison->set_strength(34);
   poison->set_poison_type("food");

   if(!poison->move(TP))
      {
        WRITE_THIS_LOG( QUEST_FILE, TP->query_name()
              +" ate the poisoned tablet.\n" );
        poison->start_poison();
       }
}

init()
{
   ::init();
   add_action("do_drop", "drop");
}

int do_drop(string str)
{
  object tablet;
  object drink;
  string foo;
  object *inv;

  if (!str || !strlen(str))
    return 0;

  inv = all_inventory(TP);

  notify_fail( CAP(QVB) +" the tablet into what?\n");

  if (!parse_command(str, inv, "[white] [powdery] 'tablet' [in] [into] %o", drink))
    return 0;

  if(!function_exists("create_drink", drink))
    {
       write("The tablet will only dissolve in liquid.\n");
       return 1;
     }

   if(drink->num_heap() > 1)
     {
       write("The tablet can only be dropped into one drink.\n");
       return 1;
      }

   if(drink->num_heap() == 1)
       drink->add_prop(HEAP_S_UNIQUE_ID, "_avenir_poisoned_drink_unique");

   drink->add_prop(POISON_PROP, 1);
/*
 *  Pity, but this dosen't seem to work :(
 *  drink->set_drink_msg("@@do_poison:/d/Avenir/common/outpost/obj/water_poison@@");
 */
   drink->set_drink_msg("It tastes very strange.\n");

   write("You drop "+short()+" into "+drink->short()+".\n"
        +"The tablet dissolves and becomes invisible.\n");
   say(QCTNAME(TP) + " drops "+short()+" into "+drink->short()+".\n");

   WRITE_THIS_LOG( QUEST_FILE, TP->query_name()
              +" poisoned "+file_name(drink)+".\n" );

   set_alarm(0.5, 0.0, remove_object);
   return 1;

}
