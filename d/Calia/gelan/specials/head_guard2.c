/* 	this is a special object of the town Gelan

    coder(s):   Merlin & Maniac

    history:
                 17/12/96   corrected bug                    Maniac
                 16/12/96   reduced number of alarms         Maniac
                 26/7/95    introduced guard allocation in
                            help_me function. Added 
                            documentation in file header.    Maniac

    purpose:    supervises all the other guards, is chief of guard

    quests:     none
    special:    supervises the other guards

    bug:        none known


   This code is basically the control object for the guards in Gelan.
   The most important function is help_me, which handles calls for
   help from guards or protected monsters in the town that have been
   attacked. It allocates some guards to the new situation if possible,
   splitting guards away from other situations if necessary. 
   Other important documentation can be found in the files 
   "stdguard.c" and "stdaided.c".

*/

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "specials.h"
#include GUARD_INCLUDE

#define GUARD_NAME          0                   /* second indexes in the */
                                                /* guards array */
#define GUARD_OBJECT        1
#define GUARD_ID            2
#define GUARD_GENDER        3
#define GUARD_START_ROOM    4

/* The array consists of subarrays for every rank of guard type.
   The subarrays hold all informations about the guards as detailed by the
.
*/

mixed * guards = ({
/* (0) entrance guards */
     ({  ({"gamalus",0,"entrance_guard", G_MALE, 
                        GELAN_ROOMS + "gate"}), 
     }),
/* (1) apprentice entrance guards wave 1 */
     ({  ({"cavasi", 0,"apprentice_fighter", G_MALE, 
                       GELAN_ROOMS + "palace_road_nw" }),
         ({"cissa",  0,"apprentice_fighter", G_FEMALE, 
                       GELAN_ROOMS + "palace_road_ne" }),
     }),
/* (2) fighter entrance guard wave 1 */
    ({  ({"cumulus",0,"fighter",  G_FEMALE, 
                       GELAN_ROOMS + "square_southend_center_w"}),
        ({"curlu",  0,"fighter",  G_MALE,
                      GELAN_ROOMS + "square_southend_center_e"}),
        ({"cemano", 0,"fighter",  G_FEMALE,
                      GELAN_ROOMS + "gate"}),
        ({"cacami", 0,"fighter",  G_MALE,
                      GELAN_ROOMS + "square_se"}),
        ({"cecama", 0,"fighter",  G_FEMALE,      
                      GELAN_ROOMS + "square_sw"}),
    }),
/* (3) experienced entrance guard wave 1 */
   ({  ({"cimo",   0,"exp_fighter", G_MALE,
                     GELAN_ROOMS + "square_northend_center_w"}),
       ({"casik",  0,"exp_fighter", G_FEMALE,
                     GELAN_ROOMS + "square_northend_center_e"}),      
   }),
/* (4) gelan guide */
        ({  ({"gizmo",  0,"guide",  G_MALE, 
                    GELAN_ROOMS + "guards_info"}),        
   }),
   
});




/* Resets an individual guard */
void
reset_guard(int rank, int i)
{
    object guard;

    guard = clone_object(GELAN_MONSTERS + (guards[rank][i][GUARD_ID]));
    guard->set_name(guards[rank][i][GUARD_NAME]);
    guard->set_gender(guards[rank][i][GUARD_GENDER]);
    guards[rank][i][GUARD_OBJECT] = guard;
    guard->arm_me();
    guard->set_up_move_strings();
    guard->move_living("X", guards[rank][i][GUARD_START_ROOM]);
    guard->set_start_room(guards[rank][i][GUARD_START_ROOM]);
}


void
reset_rank(int rank)
{
    int i;

    for(i = 0; i < sizeof(guards[rank]); i++)
        if (guards[rank][i][GUARD_OBJECT] == 0) /* guard found, now clone it */
            reset_guard(rank, i);  
}

/*
 * Function name: resets_guards 
 * Description: Resets the guards and sends them to their   
 */
void
reset_guards()
{
   int rank;

   setuid();
   seteuid(getuid());

   reset_rank(0); 

   for (rank = 1; rank < MAX_RANKS; rank++) 
      set_alarm(itof(rank), 0.0, &reset_rank(rank));
} /* reset_guards */


/*
 * Function name: help_me_call
 * Description:   sends request for assistance to the guards
 * Arguments:     guards to alarm, room of the attacker, and attacker. 
 * Returns:       none
 */
void
help_me_call(object *gds, string room, object attacker)
{
    int i;
    object r;

    if (!objectp(attacker) || 
        !objectp(r = find_object(room)) ||  
        !objectp(present(attacker, r))) 
        return;

    for (i = 0; i < sizeof(gds); i++) 
        gds[i]->help_other(room, attacker);
}


/*
 * Function name: help_me
 * Description:   reacts to a help request of a guards, sends it to all
 *                active guards
 * Arguments:     actual room and actual attacker
 * Returns:       number of guards alarmed
 */
int
help_me(string room, object attacker)
{
    int i, j, number, m, num_targs, total_alloc, to_alloc;
    string targ, this_target;
    object *to_send = ({ });  
    mapping allocation = (["none" : 0]); 
                          /* records how many guards allocated 
                           to each target, if any. */

    seteuid(getuid());

    number = 0;
    this_target = attacker->query_real_name();

   /* Calculate allocation of guards to each target, storing
      details in the mapping "allocation" */
    for (i = 0; i < sizeof(guards); i++)
       for (j = 0; j < sizeof(guards[i]); j++)
       {
           if ((guards[i][j][GUARD_ID] == "guide") ||
               (!guards[i][j][GUARD_OBJECT]))
               continue;
             targ = 
              (guards[i][j][GUARD_OBJECT]->query_attack())->query_real_name();
             if (!targ) 
             { 
                m = allocation["none"] + 1;
                allocation = m_delete(allocation, "none");
                allocation += (["none" : m]); 
                number++;
             }
             else
             {
                m = allocation[targ] + 1; 
                allocation = m_delete(allocation, targ);
                allocation += ([targ : m]); 
                number++;
              }    
          }

    num_targs = m_sizeof(allocation); /* number of targets */
    if (allocation[this_target]) 
        num_targs = num_targs - 1;

    total_alloc = number / num_targs; /* number of guards to send  
                                           to new situation */
    total_alloc = total_alloc - allocation[this_target]; 

    if (total_alloc < 0) 
        total_alloc = 0;
    if (total_alloc < allocation["none"]) 
        total_alloc = allocation["none"];

    to_alloc = total_alloc;      /* still to allocate */ 

    /* first, currently unallocated guards must be sent */
    for(i = 0; i < sizeof(guards); i++) {
        if (!to_alloc)
            break; 
        for(j = 0; j < sizeof(guards[i]); j++)
        {
           if (!to_alloc)
               break; 
           if ((guards[i][j][GUARD_ID] == "guide") ||
               (!guards[i][j][GUARD_OBJECT]))
               continue;
           targ = 
               (guards[i][j][GUARD_OBJECT]->query_attack())->query_real_name();
           if (!targ) {
               to_send += ({ guards[i][j][GUARD_OBJECT] }); 
               to_alloc--;
           }
        }
    } 

    allocation = m_delete(allocation, "none");

    /* Now if necessary, already allocated guards have to be called, 
       provided they are enough "spare" assigned to their current task */ 
    for(i = 0; i < sizeof(guards); i++) {
        if (!to_alloc)
            break; 
        for(j = 0; j < sizeof(guards[i]); j++) {
           if (!to_alloc) 
               break; 
           if ((guards[i][j][GUARD_ID] == "guide") ||
               (!guards[i][j][GUARD_OBJECT]))
               continue;
           targ = 
                (guards[i][j][GUARD_OBJECT]->query_attack())->query_real_name();
           if ((targ != this_target) && 
               (allocation[targ] > total_alloc)) {
               to_send += ({ guards[i][j][GUARD_OBJECT] }); 
               to_alloc--;
               m = allocation[targ] - 1;
               allocation = m_delete(allocation, targ);
               allocation += ([targ : m]); 
           }
        }
    } 

    if (sizeof(to_send)) 
        set_alarm(1.0, 0.0, &help_me_call(to_send, room, attacker));
    return total_alloc;
}


/*
 * Function name: remove_object
 * Description:   removes the head_guard and all active guards
 * Arguments:     none
 * Returns:       none
 */

void
remove_object()
{
   int i,j;

   for(i = 0; i < sizeof(guards); i++)
       for(j = 0; j < sizeof(guards[i]); j++)
           if(guards[i][j][GUARD_OBJECT])
                 guards[i][j][GUARD_OBJECT]->remove_object();
}
