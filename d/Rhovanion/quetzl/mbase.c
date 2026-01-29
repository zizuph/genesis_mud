object *
possible_targets(object for_ob)
{
   mixed *v_targets;
   if(!for_ob)
      return ({ });
   
   v_targets = environment(for_ob)->query_valid_targets(for_ob);
   if (!pointerp(v_targets))
         v_targets = ({ v_targets });
   return all_inventory(environment(for_ob)) +
     v_targets;
}
