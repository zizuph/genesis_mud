#define NUM_DEATHS 6
void say_death(object dead_npc) {
   object TR=environment(dead_npc);
   string msg;
   string short=(dead_npc->query_short());
 
   switch (random(NUM_DEATHS)) {
        case 0:
             tell_room(TR,"The "+short+" gasps: For the honor of the King!\n");
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
             tell_room(TR,"The "+short+" gasps with a dieing breath: May "+
                          "the Tritheon curse you, infidel!\n");
             break;
        case 5:
             tell_room(TR,"The "+short+" gasps with a dieing breath: May "+
                          "you rot in Hades, infidel!\n");
             break;
        default :
             tell_room(TR,"The "+short+" stumbles back and crashes to the "+
                          "ground.\n");
   }
