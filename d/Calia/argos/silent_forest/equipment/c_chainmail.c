/*   c_chainmail.c
 *
 *  The etheral crystal chainmail, a pretty
 *  good body armour, breaks slightly easier
 *  then regular armours.
 *
 * Baldacin@Genesis, Sep 2003
 * Fixed typo - Jaacar, May 2016
 */
inherit "/std/armour";
#include "../ldefs.h"
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() 
{
    set_name("chainmail");
    set_adj(({"ethereal","crystal"}));
    set_short("ethereal crystal chainmail");
    set_long("This chainmail, made of pure crystal is heavily ornamented with "+
      "gems and pearls, forming a magnificent pattern. The translucent crystal "+
      "material makes the armourpiece seem ethereal and insubstantial. It feels "+
      "very light, which probably affects its condition.\n");
    set_ac(40);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35 + random(15)));
    
    set_likely_cond(5);
    
    add_item(({"magnificent pattern", "pattern"}),"The decorating gems and pearls "+
      "forms a magnificent pattern, resembling an ancient dragon.\n");
}

/*
 * Function name: remove_broken
 * Description  : The armour got broken so we remove it from the
 *                player.
 * Arguments    : int silent - true if no message should be generated
 *                             about the fact that the armour breaks.
 */
void 
remove_broken()
{
        object wearer = TO->query_worn();
	object shards;

	/* If it's not worn, bail out! (Ehh, it should be worn though)*/
        if (!wearer) 
	  return ::remove_broken();

	object room = environment(wearer);

        tell_object(wearer, "The " + short(wearer) + " breaks!!!\nWhat used "+
                "be a splendid piece of crystal armour is now only a pile of "+
                "broken shards on the ground.\n");
        tell_room(environment(wearer), "The " + QSHORT(this_object()) +
                " worn by " + QTNAME(wearer) + " breaks!!!\nWhat used "+
                "to be a splendid piece of crystal armour is now only "+
                "a pile of broken shards on the ground.\n", wearer);

    if (objectp(room))
    {
        setuid();
        seteuid(getuid());
        shards = clone_object(SFOBJDIR+"crystal_shards.c");
        shards->add_prop(OBJ_I_WEIGHT,  TO->query_prop(OBJ_I_WEIGHT));
        shards->add_prop(OBJ_I_VOLUME,  TO->query_prop(OBJ_I_VOLUME) / 2);
        shards->move(environment(wearer), 1);
    }

    return TO->remove_object();
}
