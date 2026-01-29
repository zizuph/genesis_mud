
/* 
   Ownership functions, used for calling hooks in the owner
   of this object when certain things happen. 

   set_owner(object o) sets the owner of this object. 

   If this object is a room owned by the npc, call enter_owned_room 
   when something enters the room, and leave_owned_room when something 
   leaves the room. The functions will call the hooks in the npc if it 
   was a player doing the moving and the npc is present. 

   If this object is a carryable object, call owned_object_enter 
   when the object enters a new environment. The function will call a
   hook in the npc if this object moved into the environment of a player 
   or left the environment of a player. 

   If the object has actions which you want to be noted when they are 
   carried out, call owned_object_action when the action is carried out. 
   The function will call a hook in the npc if it is present.  

   Copyright Miguel Leith 1996 

   Coded by Maniac, 5/8/96 
 */ 

#pragma save_binary
#pragma strict_types



object owner; 

/* Set the owner of this object */ 
void
set_owner(object o)
{
    owner = o; 
}


object
query_owner()
{
    return owner; 
}


/* Someone entered the inventory of a room owned by an npc 
   and in which the npc is present. */ 
void
enter_owned_room(object ob, object from)
{
    if (!objectp(owner)) 
        return;

    if (owner == ob)
        return;

    if (!interactive(ob)) 
        return;

    if (!objectp(present(owner, this_object())))
        return;

    owner->owner_hook_enter_room(ob, from);  
}


/* Someone left the inventory of a room owned by an npc 
   and in which the npc is present. */ 
void
leave_owned_room(object ob, object to)
{
    if (!objectp(owner)) 
        return;

    if (owner == ob)
        return;

    if (!interactive(ob)) 
        return;

    if (!objectp(present(owner, this_object())))
        return;

    owner->owner_hook_leave_room(ob, to);  
}


/* An object owned by an npc enters the inventory of a player */ 
void
owned_object_enter(object dest, object old)
{
    int di, oi; 

    if (!objectp(owner)) 
        return;

    if (owner == dest)
        return;

    if (!objectp(old)) 
        return;

    di = interactive(dest); 
    oi = interactive(old); 

    if (!oi && !di) 
        return;

    if ((di && !objectp(present(owner, environment(dest)))) || 
        (oi && !objectp(present(owner, environment(old))))) 
        return;

    owner->owner_hook_transfer(this_object(), old, dest);  
}


/* An object owned by an npc has an action carried out */ 
void
owned_object_action(object player, string act)
{
    if (!objectp(owner)) 
        return;

    if (!objectp(player)) 
        return;

    if (owner == player)
        return;

    if (!objectp(present(owner, environment(player)))) 
         return;

    owner->owner_hook_action(this_object(), player, act);  
}

