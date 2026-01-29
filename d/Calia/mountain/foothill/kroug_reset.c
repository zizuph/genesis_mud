
/* 
   An include file to handle the resetting of krougs in kroug rooms.
   The setting functions should be called from the individual room files. 
   This file should be included after the various other defs, since it
   uses them.

   Coded by Maniac.

   History:
          02/9/10            "a" kroug enters         Lavellan
          28/5/01            arming done elsewhere    Maniac 
          10/8/95            Created                  Maniac
*/

int num_commander = 0;
object *commanders = ({ });
int num_elite = 0;
int elite_type = 0;
object *elite = ({ });
int num_tough = 0;
object *tough = ({ });
int num_regular = 0;
object *regular = ({ });
int num_weak = 0;
object *weak = ({ });


int
query_kroug_start_room()
{
    return 1;
}


/* Set the number of kroug commanders to appear on reset.
   Should only ever be 0 or 1. */
void
set_num_commanders(int n)
{
    commanders = allocate(n);
    num_commander = n;
}


/* Set the number of elite krougs to appear on reset.
   Should only every be 0 or 1. */
void
set_num_elite(int n, int type)
{
    elite = allocate(n);
    num_elite = n;
    elite_type = type;
}


/* Set the number of tough krougs to appear on reset */
void
set_num_tough(int n)
{
    tough = allocate(n);
    num_tough = n;
}


/* Set the number of regular krougs to appear on reset */
void
set_num_regular(int n)
{
    regular = allocate(n);
    num_regular = n;
}


/* Set the number of weak krougs to appear on reset */ 
void 
set_num_weak(int n) 
{ 
    weak = allocate(n); 
    num_weak = n; 
} 


/* Arm and move in the monster */ 
void 
arm_and_move_in(object kroug) 
{ 
    /* 
     *  Arming is done in the krougs themselves (the standard kroug 
     *  inherit), as from 28/5/01 
     *  kroug->arm_me(); 
     */ 
    kroug->move_living("M", this_object()); 
//    tell_room(this_object(), QCTNAME(kroug) + " comes steaming in.\n"); 
    tell_room(this_object(), QCNAME(kroug) + " comes steaming in.\n"); 
} 


/* Clone in krougs if lacking any */
void
reset_room()
{
    int i;
  
    enable_reset(110);
    for (i = 0; i < num_commander; i++)
        if (!commanders[i])  {
            commanders[i] = clone_object(MOUNTAIN_MONSTERS+"kroug_commander");  
            arm_and_move_in(commanders[i]); 
        }

    for (i = 0; i < num_elite; i++)
        if (!elite[i])  
            switch (elite_type) {
                case ELITE_SWORD : 
                              elite[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_elite_sword");  
                              arm_and_move_in(elite[i]); 
                              break;
                case ELITE_AXE : 
                              elite[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_elite_axe");  
                              arm_and_move_in(elite[i]); 
                              break;
                case ELITE_SPEAR :
                              elite[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_elite_spear");  
                              arm_and_move_in(elite[i]); 
                              break;
                default: elite[i] = 0;
                         break;
            }

    for (i = 0; i < num_tough; i++)
        if (!tough[i])  
            switch (random(4)) {
                case 0 : 
                              tough[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_tough1");  
                              arm_and_move_in(tough[i]); 
                              break;
                case 1 : 
                              tough[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_tough2");  
                              arm_and_move_in(tough[i]); 
                              break;
                case 2 :
                              tough[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_tough3");  
                              arm_and_move_in(tough[i]); 
                              break;
                default: 
                              tough[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_tough4");  
                              arm_and_move_in(tough[i]); 
                              break;
            }

    for (i = 0; i < num_regular; i++)
        if (!regular[i])  
            switch (random(4)) {
                case 0 : 
                              regular[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_reg1");  
                              arm_and_move_in(regular[i]); 
                              break;
                case 1 : 
                              regular[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_reg2");  
                              arm_and_move_in(regular[i]); 
                              break;
                case 2 :
                              regular[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_reg3");  
                              arm_and_move_in(regular[i]); 
                              break;
                default: 
                              regular[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_reg4");  
                              arm_and_move_in(regular[i]); 
                              break;
            }


    for (i = 0; i < num_weak; i++)
        if (!weak[i])  
            switch (random(4)) {
                case 0 : 
                              weak[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_weak1");  
                              arm_and_move_in(weak[i]); 
                              break;
                case 1 : 
                              weak[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_weak2");  
                              arm_and_move_in(weak[i]); 
                              break;
                case 2 :
                              weak[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_weak3");  
                              arm_and_move_in(weak[i]); 
                              break;
                default: 
                              weak[i] = clone_object(MOUNTAIN_MONSTERS+
                                                      "kroug_weak4");  
                              arm_and_move_in(weak[i]); 
                              break;
            }

}


