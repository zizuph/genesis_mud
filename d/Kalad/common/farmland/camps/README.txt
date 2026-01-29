PLEASE NOTE, do not Update rf_war_room before reading 
this.


The room that keeps track of all that happens in the camp is
/d/Kalad/common/farmland/camps/rooms/rf_war_room

This room keeps track of which rooms that are subscribed to
get notifications ( the state changes when the camp burns),
the number of goblins alive etc.

In order to burn the camp the Goblin_warrior_counter has to
be 0 or less ( negative values works too). Everytime a room
resets the number of spawned monsters there will be added
to the counter.

I made a few functions to keep track of this and manage it if
needed, simply use these three functions to adjust the numbers
in the camp if something goes wrong.

To show the number of current goblins in the camp, go to the
rf_war_room
Call here get_goblin_warrior_counter

To add or remove goblins to the counter use these two
functions.
Call here add_goblin_warriors
Call here remove_goblin_warriors


Note do NOT update/load this room, because it will ruin the logic
of the whole camp. But if you have to do it for some reason do
it in the following order.

Update the rf_war_room make sure the goblin counter is 0.
Then load all the redfang_camp rooms 1-18, this will register 
to the subscriber and add their npcs to the counter.


Zignur
