/*  /d/Avenir/inherit/defeat.c (this is identical to conquer.c)
 *  
 *  Coded by Lilith. This is a re-coding of the notify_death() 
 *  function in /std/living/combat.c
 *
 *  Last update: 19 Nov 1996, by Lilith
 *
 *  PURPOSE: THIS FILE MAKES IT POSSIBLE TO MASK 'DYING' SO THAT THE 
 *  CREATURE IS 'DEFEATED' INSTEAD. Good for use with npcs that are 
 *  important for domain theme and/or can't die because they are 
 *  'immortal.'  
 *  -----------------------------------
 *
 *  HOW TO USE:
 *
 *  Add the following line to the creature/monster file:
 *  inherit "/d/Avenir/inherit/defeat";
 *
 *  You might want to mask do_die() to emphasize that the creature
 *  wasn't killed.
 *
 *  -----------------------------------
 *  EXAMPLE:
 *
 *  inherit "/std/monster";
 *  inherit "/d/Avenir/inherit/defeat";
 *
 *  void
 *  create_monster()
 *  {
 *      set_name("Hercules");
 *      set_race_name("human");
 *      set_adj(({"brawny", "golden-haired"}));
 *      set_long("He is a hero out of legend, a demi-god. "+
 *          "He faced all of his tasks with courage, and "+
 *          "defeated his enemies with strength and intellect.\n");
 *
 *      set_stats(({ 150, 150, 150, 175, 175, 175 }));
 *
 *      add_prop(NPC_I_NO_LOOKS, 1);
 *      add_prop(NPC_I_NO_RUN_AWAY, 1);
 *
 *  }
 *
 *  void
 *  do_die(object killer)
 *  {
 *      if (query_hp() > 0) 
 *      return;
 *
 *      if (killer && environment(this_object()) == environment(killer)) 
 *      {
 *          tell_room(environment(this_object()), (QCTNAME(TO) + 
 *              "says: You thought you could kill me, eh?\n"+
 *              "Hearty laughter echoes in the room as he "+
 *              "slowly fades from view.\n");
 *
 *      ::do_die(killer);
 *  }
 *
 *  -----------------------------------
 *  
 * NOTE:
 *
 *  add_prop(LIVE_I_NO_CORPSE, 1) will be invoked in the 
 *  notify_death() function to make sure a corpse isn't left.
 *
 *  HOWEVER--some special attacks sever limbs or smash people to
 *  bloody pulps if there isn't a LIVE_I_NO_CORPSE prop set in the
 *  npc, so you should probably set it in the create() function
 *  anyway.
 *
 *  This file needs to be inherited, see EXAMPLE above for
 *  instructions on usage.
 *
 */
#pragma strict_types

#include <macros.h>
#include <stdproperties.h> 


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    /*
     * Lets make sure there isn't a corpse, else why go to all the
     * trouble to make this NPC defeatable rather than killable?
     */
    this_object()->add_prop(LIVE_I_NO_CORPSE, 1);

    tell_room(environment(),
        QCTNAME(this_object()) + " was defeated.\n", this_object());


    if (!living(killer))
    {
        return;
    }
 
    /*
     * Give specific information about who killed this poor soul.
     */
    tell_object(killer, 
        "You defeated " + this_object()->query_the_name(killer) + ".\n");
    tell_room(environment(this_object()),  QCTNAME(killer) + 
        " defeated "+ this_object()->query_objective() + 
        ".\n", ({ this_object(), killer }));
}

