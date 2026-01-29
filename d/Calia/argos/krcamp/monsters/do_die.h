#define NUM_DEATHS 6
void say_death(object dead_kretan) {
   object TR=environment(dead_kretan);
   string msg;
   string short=(dead_kretan->query_short());
   int ok;
 
   /* hand off banner, if he has it */
   if (present("banner",this_object())) {
      /* check & see if there is another kretan in the room */
      /* "health kretan" returns 0 if none, >0 if there is one */
      ok=(dead_kretan->command("health kretan"));
      if (ok) {
         dead_kretan->command("say Save the standard, comrade!");
         dead_kretan->command("give standard to kretan");
      }
   }
 
   switch (random(NUM_DEATHS)) {
        case 0:
             tell_room(TR,"The "+short+" gasps: For the honor of Kretos!\n");
             break;
        case 1:
             tell_room(TR,"Blood gushes from the mouth of the "+short+
                          " as he falls to the ground!\n");
             break;
        case 2:
             tell_room(TR,"The eyes of the "+short+" bulge out in terror!\n");
             break;
        case 3:
             tell_room(TR,"The "+short+" lets out a blood-curdling scream "+
                          "as he falls to the ground!\n");
             break;
        case 4:
             tell_room(TR,"The "+short+" gasps with a dying breath: You "+
                          "shall lose in the end, infidel!\n");
             break;
        case 5:
             tell_room(TR,"The "+short+" gasps with a dying breath: May "+
                          "you rot in Hades, infidel!\n");
             break;
        default :
             tell_room(TR,"The "+short+" stumbles back and crashes to the "+
                          "ground.\n");
   }
}
void do_die(object enemy) {
   say_death(this_object());
   ::do_die(enemy);
}
