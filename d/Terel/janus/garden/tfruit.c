/*  tfruit.c */
/*  janus 920831 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define TP             this_player()
#define TO             this_object()
#define ETP            environment(TP)
#define HOME           "/d/Terel/janus"

#define LIVE_S_FROM_FILE   "_live_s_from_file"

public void set_me_up(mixed where);

public void
create_object()
{
  set_name("fruit");
  set_adj("turquoise");
  set_long("A walnut sized turqoise fruit.\n");
  
  add_prop(OBJ_I_WEIGHT,50);
  add_prop(OBJ_I_VOLUME,50);
  add_prop(OBJ_I_VALUE, 100);
  add_prop(OBJ_M_NO_DROP, 0);
  add_prop(MAGIC_AM_MAGIC, ({90, "alteration"})); 
  add_prop("is_mixable",1);
}

public void
do_puke(object who)
{
   if (!who) return;
   who->command("$burp loudly");
   who->catch_msg("Suddenly the fruit and the rest of your " +
                  "stomach content burst from your mouth in " +
                  "a wet, soursmelling cascade.\n");
   tell_room(environment(who), "A huge cascade of fruit pieces, " +
             "and old food comes from " + QTNAME(who) +
             "'s mouth. A sour smell permeates the air.\n", who);
   who->reduce_hit_point(6);
   if (who->query_hp() <= 0) who->do_die(TO);
   remove_object();
}

public int
do_eat(string str)
{
  object wheretogo;
  object krympp;
  object rath;
  object mound;
  object ob;
  object diploma;
  
  if (!str) return 0;
  
  notify_fail(capitalize(query_verb()) + " what?\n");
  if (!id(str)) return 0;

  seteuid(getuid(TO));
   
  mound   = present("moundi", ETP);
  rath    = present("rath", ETP);
  diploma = present("diploma", TP);
  krympp  = present("krympp", ETP);
  
  if (krympp || TP->query_prop(LIVE_S_FROM_FILE)) {     
      write("The fruit taste delicious. You feel strange, very strange. " +
            "Your head spins, but nothing seems to happen. \n");
      say(QCTNAME(TP) + " eats something.\n");
      return 1;
  } else if (mound && diploma) {
      set_me_up(JANUSDIR + "garden/hive/mound1");
      remove_object();
  } else if (rath && diploma) {
      wheretogo = clone_object(JANUSDIR + "garden/shrink");
      set_me_up(wheretogo);
      remove_object();
  } else if (diploma) {     
      wheretogo = clone_object(JANUSDIR + "garden/shrink");
      set_me_up(wheretogo);
      remove_object();
  } else {
      write("The fruit was spoiled, YEUCH. Your stomach is in uproar.\n");
      say(QCTNAME(TP) + " eats a fruit and " +
           TP->query_possessive() + " face takes on a green tinge.\n");
      set_no_show();
      set_alarm(15.0, -1.0, &do_puke(TP));
  }

  return 1;
}

public void
init()
{
    ::init();
    add_action(do_eat, "eat");
    add_action(do_eat, "consume");
}

public void
set_me_up(mixed where)
{
   if (!where) return;
   TP->add_prop(LIVE_S_FROM_FILE, MASTER_OB(ETP));
   write("The fruit taste delicious but you feel strange, very " +
         "strange. Your head spins and things around you grow to " +
         "gargantuan proportions very quickly.\n");
   say(QCTNAME(TP) + " eats something and suddenly grows smaller " +
       "and smaller and disappears from sight.\n");
   TP->move_living("M", where, 1);
}
