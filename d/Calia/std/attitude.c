/* 
 * Inherit for attitudes of npcs. 
 * 
 * Coded by Maniac, 4/3/01. 
 * 
 */ 

#include <macros.h> 


/* 
 * Function:     arrived_hook 
 * Description:  Called by alarm when someone arrives in 
 *               the same room as this npc. 
 */ 
int 
arrived_hook(object player) 
{ 
    
} 


/* 
 * Function:     query_can_respond_to 
 * Description:  Returns 1 if this npc can respond to the 
 *               player subject to the optional qualifier, 0 
 *               otherwise. By default returns 1 only if 
 *               this npc can see the living and see in 
 *               the room. 
 */ 
varargs int 
query_can_respond_to(object living, mixed qualifier) 
{ 
    return (CAN_SEE(this_object(), living) && 
            CAN_SEE_IN_ROOM(this_object())); 
} 


/* 
 * Function:     query_want_respond_to 
 * Description:  Returns 1 if this npc wants to respond to the 
 *               player, subject to the optional qualifier, 
 *               0 otherwise (the default). 
 */ 
varargs int 
query_want_respond_to(object living, mixed qualifier) 
{ 
    return 0; 
} 


/* 
 * Function:     query_responds 
 * Description:  Returns 1 if this npc responds to any 
 *               livings, 0 otherwise (the default). 
 * 
 */ 
int 
query_responds() 
{ 
    return 0; 
} 


/* 
 * Function:       query_knows_me 
 * Description:    Returns 1 if the living should know this npc 
 *                 0 otherwise (the default). 
 * 
 */ 
int 
query_knows_me(object living) 
{ 
    return 0; 
} 


/* 
 * Function:     init_attitude 
 * Description:  Call this from init_living of the npc to set up 
 *               the alarm to respond to someone arriving. 
 * 
 */ 
void 
init_attitude(object player) 
{ 
    if (query_knows_me(player)) 
        player->add_introduced(this_object()->query_real_name()); 
 /* 
    if (query_responds() && 
        query_can_respond_to(player) && 
        query_want_respond_to(player)) 
        set_alarm(1.0, 0.0, &arrived_hook(player)); 
 */ 
} 
