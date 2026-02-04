/*
 * /d/Terel/mountains/ghastly_keep/obj/g_vamp_pouch.c
 *
 *  A pouch carried by the Vampire of Ghastly Keep.
 *
 *  Created by Znagsnuf.
 *
 *  2021-05-03 - Cotillion
 *  - Nerfed money reward from 140 plats 
 *
 */

inherit "/std/receptacle";

#include "defs.h";
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

int empty_out(object ob);
int remove_pouch(mixed blah);

create_container()
{
  set_name("pouch");
  set_adj( ({"plain", "burlap"}) );
  set_short("plain burlap pouch");
  set_long("This plain burlap pouch is made for storing coins inside.\n");
  add_prop(CONT_I_IN, 1);
  add_prop(CONT_I_WEIGHT, 100);
  add_prop(CONT_I_VOLUME, 100);
  add_prop(CONT_I_MAX_WEIGHT, 500);
  add_prop(CONT_I_MAX_VOLUME, 400);
  set_alarm(1800.0, -1.0, &remove_pouch());
  add_coins();
}

/*
 * Function name: empty_out()
 * Description  : Moves all objects to the environment
 */
int
empty_out(object ob)
{
    if (ob->move(ENV(TO)))
        return 0;

    else
        return 1;
}

/*
 * Function name: remove_pouch()
 * Description  : Dissolves the pouch leaving behind only coins.
 */
int
remove_pouch(mixed blah)
{
    tell_room(ENV(TO), "The " + short() +
                       " rapidly dissolves into nothing.\n",0);
    map(all_inventory(TO), empty_out);
    TO->remove_object();
}

add_coins()
{
  seteuid(getuid(this_object()));
  MONEY_MAKE(20 + random(80),  "platinum")->move(TO);
}
