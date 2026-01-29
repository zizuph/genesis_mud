/* 
   Utility for combat simulations, allows one to get statistics for
   the chance of hitting, given the various details of the attacker 
   and defender.
 
   Coded by Maniac, October 1995. 
*/

inherit "/std/object";

/* Test details */
/* Entered */
int max_num_trials;

/* Calculated */
int num_trials;
int running_test;
int input_stage;
int num_hits;

object caller;

/* Defender's details */
/* Entered */
int defender_str;
int defender_dex;
int defender_defence;
int defender_parry;
int defender_unarmed_combat;
int defender_has_weapon;
int defender_blind_combat;
int defender_can_see;
int defender_weight;
int defender_volume;
int defender_carrying_weight;
int defender_carrying_volume;

/* Calculated */
/* Encumbrance percentages for weight and volume */
int e_w_defender;
int e_v_defender;

/* Attacker's details */
/* Entered */
int attacker_str;
int attacker_dex;
int attacker_wchit;
int attacker_blind_combat;
int attacker_can_see;
int attacker_weight;
int attacker_volume;
int attacker_carrying_weight;
int attacker_carrying_volume;

/* Calculated */
/* Encumbrance percentages for weight and volume */
int e_w_attacker;
int e_v_attacker;


/* To hit value */
int tohit_val;


mixed get_input_message = 
  ({ ({"Enter defender STR (1-500):", 1, 500}),
     ({"Enter defender DEX (1-500):", 1, 500}),
     ({"Enter defender defence skill (0-100):", 0, 100}), 
     ({"Enter defender parry skill (0-100):", 0, 100}),
     ({"Enter defender unarmed combat skill (0-100):", 0, 100}),
     ({"Defender has weapon (0/1)?", 0, 1}),
     ({"Enter defender blind combat skill (0-100):", 0, 100}),
     ({"Defender can see attacker (0/1)?", 0, 1}),
     ({"Enter defender weight with no burdens (grams, 20000-200000):", 
                                                      20000, 200000}),
     ({"Enter defender volume with no burdens (ml, 20000-200000):", 
                                                      20000, 200000}),
     ({"Enter weight being carried by defender (grams, 0-500000):",0,500000}),
     ({"Enter volume being carried by defender (ml, 0-500000):",0,500000}),
     ({"Enter attacker STR (1-500):", 1, 500}), 
     ({"Enter attacker DEX (1-500):", 1, 500}), 
     ({"Enter wchit of attacker:", 1, 100}),
     ({"Enter attacker blind combat skill (0-100):", 0, 100}),
     ({"Attacker can see defender (0/1)?", 0, 1}),
     ({"Enter attacker weight with no burdens (grams, 20000-200000):", 
                                                      20000, 200000}),
     ({"Enter attacker volume with no burdens (ml, 20000-200000):", 
                                                      20000, 200000}),
     ({"Enter weight being carried by attacker (grams, 0-500000):",0,500000}),
     ({"Enter volume being carried by attacker (ml, 0-500000):",0,500000}), 
     ({"Enter total number of trials/50 (1-5000):", 1, 5000}),
    });


void
reset_vars()
{
    max_num_trials = 0;

    num_trials = 0;
    running_test = 0;
    input_stage = 0;
    num_hits = 0;

    caller = 0;

    defender_str = 0;
    defender_dex = 0;
    defender_defence = 0;
    defender_parry = 0;
    defender_unarmed_combat = 0;
    defender_has_weapon = 0;
    defender_blind_combat = 0;
    defender_can_see = 0;
    defender_weight = 0;
    defender_volume = 0;
    defender_carrying_weight = 0;
    defender_carrying_volume = 0;

    e_w_defender = 0;
    e_v_defender = 0;

    attacker_str = 0;
    attacker_dex = 0;
    attacker_wchit = 0;
    attacker_blind_combat = 0;
    attacker_can_see = 0;
    attacker_weight = 0;
    attacker_volume = 0;
    attacker_carrying_weight = 0;
    attacker_carrying_volume = 0;

    e_w_attacker = 0;
    e_v_attacker = 0;

    tohit_val = 0;
}


/*
 * Normalize offensive / defensive values
 */
static nomask int
fixnorm(int offence, int defence)
{
   if (offence + defence == 0)
       return 0;

   return ((100 * offence) / (offence + defence)) - 50;
}


int
max_weight_attacker()
{
    return attacker_weight + (attacker_str + 10) * 1000;
}

int
max_volume_attacker()
{
    return attacker_volume + (attacker_str + 10) * 1000;
}

int
max_weight_defender()
{
    return defender_weight + (defender_str + 10) * 1000;
}

int
max_volume_defender()
{
    return defender_volume + (defender_str + 10) * 1000;
}


/* Calculate encumbrance percentage volume for attacker */
int
calc_e_v_attacker()
{
    return ((100 * attacker_carrying_volume) /
            (max_volume_attacker() - attacker_volume));
}

/* Calculate encumbrance percentage weight for attacker */
int
calc_e_w_attacker()
{
    return ((100 * attacker_carrying_weight) /
            (max_weight_attacker() - attacker_weight));
}

/* Calculate encumbrance percentage volume for defender */
int
calc_e_v_defender()
{
    return ((100 * defender_carrying_volume) /
            (max_volume_defender() - defender_volume));
}

/* Calculate encumbrance percentage weight for defender */
int
calc_e_w_defender()
{
    return ((100 * defender_carrying_weight) /
            (max_weight_defender() - defender_weight));
}


/*
 * Function name: calc_tohit_val
 * Description:   Calculate the tohit value for the attacker. 
 */
void
calc_tohit_val()
{
    e_v_attacker = calc_e_v_attacker();
    e_w_attacker = calc_e_w_attacker();
    e_v_defender = calc_e_v_defender();
    e_w_defender = calc_e_w_defender();

    tohit_val = 
        2 * fixnorm(attacker_dex, defender_dex) -
        fixnorm(attacker_volume, defender_volume) -
        fixnorm(e_w_attacker + e_v_attacker,
                e_w_defender + e_v_defender);
}



void
get_input(string str)
{
      object tp = this_player();
      int v, fail;

      if (tp != caller)
          remove_object();

      fail = 0;
      if (!stringp(str)) 
          str = "";

      if (sscanf(str, "%d", v) != 1) {
          caller->catch_msg("You must enter an integer.\n"); 
          fail = 1;
      }

      if (!fail) {
          if ((v < get_input_message[input_stage][1]) ||
              (v > get_input_message[input_stage][2])) {
          caller->catch_msg("That integer is not in the correct range.\n");
          fail = 1;
          }
      }

      if (fail) {
          caller->catch_msg(get_input_message[input_stage][0]);
          input_to("get_input");
          return;
      }

      switch (input_stage) {
          case 0 : defender_str = v; break;
          case 1 : defender_dex = v; break;
          case 2 : defender_defence = v; break;
          case 3 : defender_parry = v; break;
          case 4 : defender_unarmed_combat = v; break;
          case 5 : defender_has_weapon = v; break;
          case 6 : defender_blind_combat = v; break;
          case 7 : defender_can_see = v; break;
          case 8 : defender_weight = v; break;
          case 9 : defender_volume = v; break;
          case 10: defender_carrying_weight = v; break;
          case 11: defender_carrying_volume = v; break;
          case 12: attacker_str = v; break;
          case 13: attacker_dex = v; break;
          case 14: attacker_wchit = v; break;
          case 15: attacker_blind_combat = v; break;
          case 16: attacker_can_see = v; break;
          case 17: attacker_weight = v; break;
          case 18: attacker_volume = v; break;
          case 19: attacker_carrying_weight = v; break;
          case 20: attacker_carrying_volume = v; break;
          case 21: max_num_trials = v*50; break;
          default: caller->catch_msg("Stage error.\n"); 
                   remove_object(); 
                   break; 
    }

    input_stage++;
    if (input_stage == sizeof(get_input_message)) {
        calc_tohit_val();
        caller->catch_msg("Result expected in " + (max_num_trials/50) + 
                          " second(s).\n");
        set_alarm(1.0, 0.0, "do_fifty_trials");
        running_test = 1;
        return;
    }

    caller->catch_msg(get_input_message[input_stage][0]);
    input_to("get_input");
}


void
create_object()
{

    set_name("tester");
    set_adj("combat");
    set_short("combat tester");
    set_pshort("combat testers");
    set_long("A combat test object, can give statistics for the chance " +
             "of hitting in combat over a large number of trials, given " +
             "the necessary data of the two combatants. Use `ctest' to " +
             "begin data entry.\n");
    reset_vars();
}



/* Decide if attacker hits defender or not on a given trial */
int
cb_tohit()
{
   int tmp, whit, wchit;

    wchit = attacker_wchit;

    if (defender_has_weapon) 
        tmp = defender_parry;
    else
        tmp = (defender_unarmed_combat / 2);

    tmp += defender_defence;

    /*
     * Is it dark or opponent invis? Then how well do we fight?
     */
    if (!attacker_can_see)
       wchit = (attacker_blind_combat * wchit) / 100;

    if (!defender_can_see) 
        tmp = (defender_blind_combat * tmp) / 100;

    whit = 4 * fixnorm(random(wchit) + random(wchit) +
                       random(wchit) + random(wchit), random(tmp));

    whit += tohit_val;

    if (whit > 0)
        return 1;
    else
        return (whit - 1);
}


int
show_results()
{
    if (running_test)
         return 0;  

    if (!interactive(caller)) {
         reset_vars();
         return 0;
    }

    caller->catch_msg("Over " + max_num_trials + " trials, the " +
                      "probability of attacker hitting defender was: " + 
                      ((num_hits*100) / num_trials) + "/100.\n");
}


void
do_fifty_trials()
{
    int j;

    if (objectp(calling_object())) /* Should be called from alarm */
        return;

    for (j = 0; j < 50; j++) 
       if (cb_tohit() > 0)
           num_hits++;

    num_trials += 50;

    if (num_trials >= max_num_trials) {
        running_test = 0;
        show_results();
        return;
    }
   
    set_alarm(1.0, 0.0, "do_fifty_trials");
}




int 
ctest()
{
    object c;

    if (running_test) {
        notify_fail("You are currently running a test with " + 
                    file_name(this_object()) + ".\n"); 
        return 0;
    }
   
    reset_vars();

    c = this_player();

    if (!(c->query_wiz_level())) {
        notify_fail("You are not a wizard.\n");
        return 0;
    }

    caller = c;
     
    caller->catch_msg(get_input_message[0][0]);
    input_to("get_input");
    return 1;
}


void 
enter_env(object dest, object old)
{
   ::enter_env(dest, old);
    
   if (!dest->query_wiz_level())
      set_alarm(1.0, 0.0, "remove_object");
}


void
init()
{
    ::init();
    add_action("ctest", "ctest");
    add_action("clear", "clear");
}
