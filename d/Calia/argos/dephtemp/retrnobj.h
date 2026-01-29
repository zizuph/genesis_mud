/* Return object home
**
** This file can be included so that when an object disappears from the
** game, it's home room is signaled that the object has been returned.
**
** Assumptions: string HOME_ROOM has been defined in including object
**              int    OBJ_NUM   has been defined in including object
**              void   return_object(int ObjNum); is declared in HOME_ROOM
** Suggestion:  add_prop(OBJ_M_NO_SELL,1); added to including object
**
** History
** Date       Coder        Action
** -------- -------------  ---------------------------------
** 3/6/95   Maniac         Modified 
** 1/15/95  Zima           Created
**
**/
 
void
remove_object() 
{
    seteuid(getuid());
    (HOME_ROOM)->return_object(OBJ_NUM);
    ::remove_object();
}
 
void leave_env(object from, object to) {
   ::leave_env(from, to);

   /* Robe may be reset if it's no longer in the living's deep
      inventory */
   if (living(from) && 
       (member_array(this_object(), deep_inventory(from)) == -1))
      set_alarm(12.0,0.0,"remove_check");
}
 
void remove_check() {
   object ThisObj=this_object();
   object Env=environment(ThisObj);
 
    if (!interactive(Env)) {
        if (Env->query_prop(ROOM_I_IS))
        {
          tell_room(Env,"The " + (ThisObj->query_name()) +
                     " explodes in a ball of black light!\n");
        }
        remove_object();
    }
}
