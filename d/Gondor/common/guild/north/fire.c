#pragma save_binary

light_tick()
{
  burn_time--;
  if (!random(10)) {
    switch(random(8)) {
      case 0:
      tell_room(ENV(TO),"A loud pop erupts from the burning campfire.\n");
      break;
      case 1:
      tell_room(ENV(TO),"Flames dance across the burning firewood.\n");
      break;
      case 2:
      tell_room(ENV(TO),"A wet piece of wood in the campfire spits and hisses as it burns.\n");
      break;
      case 3:
      tell_room(ENV(TO),"The heat from the burning campfire warms your body comfortably.\n");
      break;
      case 4:
      tell_room(ENV(TO),"Shadows created by the flames of the campfire dance around the area.\n");
      break;
      case 5:
      tell_room(ENV(TO),"The burning firewood emits some crackling noises.\n");
      break;
      default:
      tell_room(ENV(TO),"The flames of the campfire flicker in the breeze.\n");
      break;
      }
    }
  if (burn_time == 60) tell_room(ENV(TO),"The campfire slumps down a little as it begins to burn down.\n");
  if (burn_time == 45) tell_room(environment(this_object()),"The campfire flickers and the heat grows less intense.\n");
  if (burn_time == 30)
    tell_room(environment(this_object()),"The campfire looks like it will burn out soon.\n");
  if (burn_time == 15) tell_room(environment(this_object()),"The campfire grows smaller; it's about to go out.\n");
  if (burn_time == 0) go_out(1);
  if (burn_time)
    set_alarm(1.0, 0.0, light_tick);
  update_fire();
  return 1;
}
