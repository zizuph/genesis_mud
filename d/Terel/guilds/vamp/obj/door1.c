inherit "/std/door";

void
create_door() {
   
    ::create_door();
   
    set_door_id("_rusted_gate");
   
    set_pass_command(({"n", "north", "enter", "in"}));
   
    set_door_desc("A large rusted gate that blocks the way inside "+
        "the area enclosed by the stone wall.\n");
  
    set_closed_desc("A rusted old gate that blocks the way inside the stone "+
       "wall.\n");
   
    set_door_name(({"rusted gate", "gate"}));
   
    set_other_room("/d/Terel/guilds/vamp/room/gate_inside.c");
   
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_no_show_composite(1);
    
    set_no_pick();
    set_open(1);
    set_locked(0);

    set_key(6661666);

    reset_object();
 }
