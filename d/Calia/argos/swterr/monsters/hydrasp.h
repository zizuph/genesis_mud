int special_attack(object enemy) {
    int attacktype;
    int i,res_prop;
    mixed* hitresult;
    object me, *ob;
    int penet=1000;
    me = this_object();
 
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
 
    for (i = 0; i < sizeof(ob); i++) {
       penet -= penet * ob[i]->query_magic_res(res_prop) /100;
       hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);
 
       ob[i]->catch_msg("You are devestated by the hydras breath!\n");
       tell_watcher(QCTNAME(ob[i]) + " is devasted by the hydra's "+
         "breath!\n", ob[i]);
 
       if (ob[i]->query_hp() <= 0)
           ob[i]->do_die(me);
   }
   return 1;
}
