/*
 * h_crucifix.c
 *
 * Used in npc/van_helsing.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  A nice crucifix belonging to van Helsing.
    coded by Calonderiel 930906               */
/* Synced for current situation by Tapakah */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

void
create_object()
{
    set_name("crucifix");
    set_adj("small");
    set_short("small crucifix");
    set_long("This is a most holy crucifix.\n");

    seteuid(getuid(TO));

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, "@@steal_me");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 5000);
}

string
query_recover()
{
    return MASTER;
}

void
init()
{
    /* Not approved! We do not code against specific guilds - EVER!
     * (Gorboth)
     * According to the deal - until vamps are reined in....
     */
  add_action("brandish", "brandish");
}

int
brandish(string str)
{

  object *enemys = environment(TO)->query_enemy(-1);
  object holy;
  int i, f;
  mixed guild_occ;
  
  notify_fail("Brandish what?\n");
  if(interactive(TP)) {
    write("The crucifix sizzles helplessly.\n");
    return 1;
  }
    
	f = 0;
    if (str == "crucifix")
    {
      for (i = 0; i < sizeof(enemys); i++) {
        guild_occ = enemys[i]->query_guild_name_occ();
        if (stringp(guild_occ) && lower_case(guild_occ[0..3]) == "vamp") {
          if (!present("crucifix", enemys[i])) {
            holy = clone_object(ROKEDIR + "obj/h_scare_him");
            holy->move(enemys[i]);
            holy->activate();
          }
          if (present(enemys[i], environment(environment(TO)))) {
            tell_room(environment(enemys[i]),
                      QCTNAME(environment(TO)) +
                      " brandishes a small crucifix!\n", enemys[i]);
            enemys[i]->catch_msg("Suddenly " +
                                 QCTNAME(environment(TO)) +
                                 " reaches out and touches your " +
                                 "forehead with something.\n");
            enemys[i]->add_panic(400);
            enemys[i]->run_away();
		f = 1;
          }
        }
      }
	if(!f) write("You aren't fighting any vampires.\n");
	return 1;
    }
    return 0;
}

string
steal_me()
{
  //    write("Someone is trying to steal your crucifix. \n");
    return "The crucifix resists all your clumsy attempts to steal it!\n";
}
