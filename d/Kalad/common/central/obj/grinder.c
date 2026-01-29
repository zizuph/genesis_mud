/*
 * Coffee grinder...
 *
 * Turn the handle to grind the coffee...but make sure there's
 * only coffee in there!
 *
 * By Korat    Additions by Napture
 *
 */

inherit "/std/receptacle";
#include <stdproperties.h>
#include <macros.h>

#define GRAIN_FILE  "/d/Kalad/common/central/obj/grain.c"

#define GROUND_PROP "_ground_beans"
  /* Record in the *beans* how many times they've been ground... */
                                    

int broken;  /* Does the grinder work; 1=bit broken, 2=completely broken */

void
create_receptacle()
{
    set_name("grinder");
    set_adj("coffee");
    set_long("An old coffee grinder. Like all coffee grinders, this one also "+
        "has a small wheel on the side and a small drawer in the bottom.\n");
    add_prop(CONT_I_WEIGHT, 100);
    add_prop(CONT_I_MAX_WEIGHT, 300);
    add_prop(CONT_I_VOLUME, 1500);
    add_prop(CONT_I_MAX_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_M_NO_SELL,1);

    broken = 0;

    add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");
}

wizinfo()
{
    return "The grinder is currently " + (broken ? "broken!" : "okay.") +
           "\nBut don't tell the mortal this..just say you can't explain "+
           "why it's not working!\n";
}

void
init()
{
   ::init();
   add_action("turn","turn");
}

turn(string str)
{
    object *inv;  /* Used to hold all the objects inside */
    object *grain;
    
    seteuid(getuid());
    notify_fail("Turn what?\n");
    if(!str)  
      /* Don't need to set notify_fail() here, as it's at the top */
        return 0;  /* Return 0 to allow any other `turn` commands to work */
      
    if (str != "wheel" && str != "handle")   
        return 0;
   
/* Got here, so must be trying to turn this grinder */
    /* First, check if it is open...can't grind stuff while it is open! */

    if (!query_prop(CONT_I_CLOSED))  {
        notify_fail("Turning the grinder's handle whilst it is " +
                    "open seems to have no effect!\n");
        return 0;
    }


    /* See what is inside */
    inv = all_inventory(this_object());

    
    /* Set a standard fail message...so it doesn't give too many
     * hints as to why it doesn't seem to work
     */
    notify_fail("The wheel of the grinder moves around.\n");
    
    /* Does the grinder work?  Doesn't matter what's inside
     * if it doesn't work at all */
    if (broken == 2)
        return 0;
        
    /* Now, check if anything is inside... */           
    if (sizeof(inv) == 0)  {  /* Nothing in there to grind! */
        return 0;  /* Already set the fail message */
    }

    /* Too many things inside or (||) what is inside isn't the beans! */
    if (sizeof(inv) > 1 || !(inv[0]->query_prop("_korat_quest_beans")
                             || inv[0]->query_prop("_korat_quest_grain")) 
                        || inv[0]->num_heap() > 1)  {
        /* Let everyone else know what this player is doing */
        tell_room(environment(this_player()),
            QCTNAME(this_player()) + " tries in vain to turn the " +
            "handle of " + this_player()->query_possessive() +
            " grinder.\n", this_player());
    
        /* Wont use notify_fail here, cause it's a specific thing
         * and we don't want any other commands attempted
         */
        /* Check if this has been tried before */
        if (broken == 0)  {
            broken++;
            /* Just a warning to the player! */                
            write("The handle is too stiff to turn!\n");
            return 1;
        }
        /* Wont get here if broken==2, cause that is taken care
         * of above, and ==0 is just above, so broken must be ==1
         * which means that a player has tried before (and got a
         * warning)
         */
            broken++;
              /* This goes to this_player() too, so no need for
               * an extra write() call
               */
            tell_room(environment(this_player()),
                "You hear a loud crunch from inside the grinder!\n");
            return 1;
    }

    /* Now, we've found that inv[0] is the beans... */
    
    /* Tell everyone else what is going on too! */
    tell_room(environment(this_player()),
              QCTNAME(this_player()) + " turns the wheel on " +
              this_player()->query_possessive() + " grinder.\n",
              this_player());
              
    if (inv[0]->query_prop(GROUND_PROP) < 5)  {
        write("You turn the wheel around for a short while.\n");
          /* Increase how many times the beans have been ground */
        inv[0]->add_prop(GROUND_PROP, inv[0]->query_prop(GROUND_PROP)+1);
        return 1;  /* Return 1, cause the command 'worked' */
    }
    write("You turn around the wheel some, and notice that "+
          "it becomes easier now...maybe it's finished?\n");

  /* Change the beans to grain! */
    inv[0]->remove_object();
    grain = clone_object(GRAIN_FILE);
    if (grain->move(this_object(), 1))  {
        /* A check to make sure the grain moved in okay! */
        write("The grinder suddenly seems empty!\n");
        grain->remove_object();
    }            
          
    return 1;
}

