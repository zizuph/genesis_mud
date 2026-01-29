// -*-C++-*-
// Bazaar market tells (~Avenir/common/bazaar/bazaar_tells.c)
// adapted from:
// Sybarus Source fluctuations (/d/Avenir/common/source_flux.c)
// creator(s):   Tepisch July 94
// last update:  Grace   Feb 95, Ilyian May 95, Kazz May 95
//               Boriska Aug 95  Changes to reduce CPU usage
//               This object made into top 10 CPU usage list!!!
// purpose:      To give Bazaar the feeling of traffic, crowdedness.
// note:         Anyone is welcome to add new tells :)
// bug(s):
// to-do:

#pragma save_binary

#pragma strict_types
#pragma no_clone
#pragma no_inherit

#include "bazaar.h"

private void do_tells();
int in_tell_zone(object ob);

// What areas should be affected by the fluctuation?
private string *areas = ({ "/d/Avenir/common/bazaar/extr/", });
private int num_areas = sizeof(areas);


//Bazaar Marketplace tells:
//Anyone with ideas for messages is welcome to make additions.

private string *tells = ({
  "A dark-haired human pushes roughly past you.\n", 
  "Someone stepped on your foot.\n", 
  "You are jostled by several people at once.\n", 
  "The cries of hawkers seem over-loud, even over the voices of "+ 
     "the crowd.\n", 
  "You feel claustrophobic in this frightened horde of people.\n", 
  "A small child falls against you and then runs off, leaving "+ 
     "behind his unpleasant stench.\n", 
  "You can barely hear the sound of someone sobbing.\n", 
  "From somewhere nearby wafts an exotic and unfamiliar scent.\n", 
  "A pale-faced girl falls to her knees on the cobblestones.\nA "+  
     "stout man kicks the girl out of his way.\n",
  "A tall elegant elf brushes disdainfully past you.\n", 
  "You notice someone glaring right at you, but they disappear in "+ 
   	"the crowd.\n", 
  "Someone grabbed your behind!\n", 
  "You hear a glorious voice humming silently.\n", 
  "A handsome, bare chested human smiles at you as he walks by.\n", 
  "You see someone grab a woman's breast, then stagger away bleeding "+
     "from a dagger slice in his belly.\n", 
  "A goblin sneezes in your face and continues walking away.\n", 
  "A small rodent-like creature scampers away.\n", 
  "A shrill laugh pierces the crowd noise.\n", 
  "You find it difficult to breathe the air made warm and humid "+ 
     "from the press of so many bodies.\n", 
  "A nearby woman struggles to recover her hold of a large parcel "+ 
     "which was almost torn from her hands in the throng.\n", 
  "Through a break in the crowd you see money exchanging hands.\n", 
  "A mangy cat wanders past you, stinking of fish.\n", 
  "You hear the faint screams of a child being horribly abused.\n", 
  "In the corner of your eye you see a guard's staff flash "+   
     "upwards.\nYou hear a dull thud and a scream, abruptly stifled.\n", 
  "Bird poop lands on the person in front of you.\n", 
  "A human voice shouts: There's the Infidel! Quick! Catch him!\n", 
  "The crowd presses you headlong into a large creature which "+  
     "snarls viciously at you.\n", 
  "There is a feeling of suppressed violence in the air.\n", 
  "To the east you can see a pack of youths beating on a smaller child.\n",
  "A battered and bruised man stumbles through the crush of "+  
     "people.\nYou notice that long strips of flesh are missing "+  
	 "from his back.\n", 
  "Just behind you, someone's stomach grumbles hungrily.\n", 
  "A voice cries out: Stelly? Stelly? Ohmygod! Where are you?\n", 
  "Someone near you is in desperate need of a bath. The "+ 
     "stench is over-whelming!\n", 
});

private int num_tells = sizeof(tells);

private int alarm_id = 0; // stores alarm id of tell alarm

// Bazaar Marketplace tells made every PERIOD seconds. 
private float
period() { return 120.0 + rnd() * 60.0; }

// call this to start area tells
void
start_tells() { alarm_id = set_alarm(period(), 0.0, do_tells); }

// call this when area tells should be stopped for some reason
void
stop_tells() {
  if (!alarm_id)
    remove_alarm(alarm_id);
  alarm_id = 0;
}

void
create() { start_tells(); }

// main tells' teller :) 
private void
do_tells()
{
  object *ppl;
  int tell;
  
  /*  Get list of users that should be affected by the flux  */
  ppl = filter(users(), in_tell_zone);
  
  /* Find new tell  */
  tell = random(num_tells);
  ppl->catch_msg(tells[tell]);

  start_tells();
}

/* Check to see if a specific player should be affected */
int
in_tell_zone(object ob)
{
  string str;
    int i;

    // If the player was removed or is not in a room, he should not be
    // affected 

    if (!ob || !environment(ob))
      return 0;
     if(environment(ob)->query_prop(NO_BAZAAR_TELLS))
       return 0;
 

    /*
     * Check that the room of the player is outside
     *   (This woud be useful for weather, etc)
     *  if (environment(ob)->query_prop(ROOM_I_INSIDE))
     *   return 0;
     */

    /* Get the filename of the room */
    str = file_name(environment(ob));

    /*
     * Check to see if the filename matches anything in the AREAS
     * array
     */
    for (i = 0; i < num_areas; i++)
      /*
       * Only compare the first N characters of the room's filename.
       * N == the length of the string in the AREAS array
       */
      if (areas[i] == str[0..strlen(areas[i])-1])
	return 1;
    
    /* The player should not be affected */
    return 0;
}



