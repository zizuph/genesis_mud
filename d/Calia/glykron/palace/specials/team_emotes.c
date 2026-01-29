/*  
    This is set of team emotes for the Calian warrior's guild.
    It is included into the Calian cmdsoul.
    Ideas by Strider and Uhclem.

    coder(s):   Maniac
    history:
               2/4/96     pledge moved in from other file Maniac 
                1/4/96    under water block               Maniac
               17/11/95   Corrections and new team emotes Maniac
               31/8/95     first team emotes created      Maniac
*/

#define AP_WEAPON "weapon"
#define AP_ARMOUR "armour"
#define AP_BATTLE "battle"

string *laugh_adv = ({"madly", "exuberantly", "amusedly", "hysterically",
                      "wildly", "merrily", "uncontrollably"});

mixed team_war_cries = ({ ({ "To Victory! For Caliana!", 
                             "TO VICTORY!!", 
                             "FOR CALIANA!!" }),
                          ({ "For Calia! Freedom or death!", 
                             "FOR CALIA!!",
                             "FREEDOM OR DEATH!!" }),
                          ({ "The free shall arise! To battle!",
                             "THE FREE SHALL ARISE!!",
                             "TO BATTLE!!" }),
                          ({ "Arise warriors! Victory is ours!",
                             "ARISE WARRIORS!!", 
                             "VICTORY IS OURS!!" }), 
                          ({ "For Caliana! Lead us to victory!",
                             "FOR CALIANA!!",
                             "LEAD US TO VICTORY!!" }),
                          ({ "For Calia! Ever our home!",
                             "FOR CALIA!!",
                             "EVER OUR HOME!!" }),
                          ({ "For the fallen! They died free!",
                             "FOR THE FALLEN!!",
                             "THEY DIED FREE!!" }),
                          ({ "Weapons clash! Let freedom ring!",
                             "WEAPONS CLASH!!",
                             "LET FREEDOM RING!!" }),
                          ({ "For the fallen! Blood calls for blood!",
                             "FOR THE FALLEN!!",
                             "BLOOD CALLS FOR BLOOD!!" }),
                          ({ "I'm gonna kick your butt! Me too!",
                             "I'M GONNA KICK YOUR BUTT!!",
                             "ME TOO!!" }),
                          ({ "Eat this! And have this for afters!", 
                             "EAT THIS!!",
                             "AND HAVE THIS FOR AFTERS!!" }) });


string
my_desc_vbfc(object ob)
{
    return QTNAME(ob);
}


/* Description of the team using vbfc, and allowing things like:
   "You, the olive-skinned slender dwarf and Strider."
*/
string
team_desc(object looking, object *team, int cap)
{
    string *qdesc, qd;

    if (member_array(looking, team) > -1) { 
        team -= ({looking});
        if (cap)
            qdesc = ({"You"});
        else
            qdesc = ({"you"});
        if (sizeof(team))
            qdesc += map(team, "my_desc_vbfc", this_object());
    }
    else { 
        if (cap)
            qdesc = ({QCTNAME(team[0])});
        else 
            qdesc = ({QTNAME(team[0])});
        team -= ({team[0]});
        if (sizeof(team))
            qdesc += map(team, "my_desc_vbfc", this_object());
    }

    if (sizeof(qdesc) == 1)
        qd = qdesc[0];
    else if (sizeof(qdesc) == 2)
        qd = qdesc[0] + " and " + qdesc[1];
    else
        qd = implode(qdesc[0 .. sizeof(qdesc) - 2], ", ") +
            " and " + qdesc[sizeof(qdesc) - 1];

    return qd;
}


/* Group defensive posture */
int
calian_team_posture()
{
    object *team; 
    object *people;
    object tp = this_player();
    int i;
  
    team = tp->query_team();

    if (!sizeof(team)) {
        notify_fail("You're not leading a team!\n");
        return 0;
    } 

    team = FILTER_PRESENT_LIVE(team);
    if (!sizeof(team)) {
        notify_fail("You can't seem to find any of your team members.\n");
        return 0;
    }

    team += ({tp});

    people = FILTER_PLAYERS(all_inventory(environment(tp)));

    for (i = 0; i < sizeof(people); i++) {
        people[i]->catch_msg(team_desc(people[i], team, 1) + " assume a " +
                        "defensive posture, alert to danger from " +
                        "any direction.\n"); 
    }
    return 1;
}


/* Group preparation for battle message */
int
calian_team_prepare()
{
    object *team; 
    object *people;
    object tp = this_player();
    int i;
  
    team = tp->query_team();

    if (!sizeof(team)) {
        notify_fail("You're not leading a team!\n");
        return 0;
    } 

    team = FILTER_PRESENT_LIVE(team);
    if (!sizeof(team)) {
        notify_fail("You can't seem to find any of your team members.\n");
        return 0;
    }

    team += ({tp});

    people = FILTER_PLAYERS(all_inventory(environment(tp)));

    for (i = 0; i < sizeof(people); i++) {
        people[i]->catch_msg(team_desc(people[i], team, 1) + " assemble " +
                      "into attack formation and prepare for " +
                      "battle.\n"); 
    }
    return 1;
}


/* A team huddle together to discuss something */
int
calian_team_huddle(string str)
{
    object *team; 
    object *people;
    object tp = this_player();
    int i;
  
    team = tp->query_team();

    if (!sizeof(team)) {
        notify_fail("You're not leading a team!\n");
        return 0;
    } 

    if (strlen(str) > 160) {
        notify_fail("Don't try to discuss too much!\n"); 
        return 0;
    }

    team = FILTER_PRESENT_LIVE(team);
    if (!sizeof(team)) {
        notify_fail("You can't seem to find any of your team members.\n");
        return 0;
    }

    team += ({tp});

    people = FILTER_PLAYERS(all_inventory(environment(tp)));

    for (i = 0; i < sizeof(people); i++) { 
        if (!str) 
            people[i]->catch_msg(team_desc(people[i], team, 1) + " huddle " +
                          "together for a private discussion.\n"); 
        else 
            people[i]->catch_msg(team_desc(people[i], team, 1) + " huddle " +
                          "together to discuss " + str + ".\n");
    }
    return 1;
}


/* The team crowds around something to intimidate it */
int
calian_team_crowd(string str)
{
    object *team; 
    object *people;
    object tp = this_player();
    object *it;
    int i;
  
    team = tp->query_team();

    if (!sizeof(team)) {
        notify_fail("You're not leading a team!\n");
        return 0;
    } 

    team = FILTER_PRESENT_LIVE(team);
    if (!sizeof(team)) {
        notify_fail("You can't seem to find any of your team members.\n");
        return 0;
    }

    team += ({tp});

    if (!str) {
        notify_fail("Crowd around whom?\n");
        return 0;
    }

    it = parse_this(str, "%l");

    if (!sizeof(it)) {
        notify_fail("Crowd around whom?\n");
        return 0;
    }

    if (sizeof(it) > 1) {
        notify_fail("You can only crowd around one person at a time!\n");
        return 0;
    }

    if (member_array(it[0], team) > -1) {
        notify_fail("Har har, joker.\n");
        return 0;
    }

    people = FILTER_PLAYERS(all_inventory(environment(tp)));

    for (i = 0; i < sizeof(people); i++) { 
        if (it[0] == people[i])
            people[i]->catch_msg(team_desc(people[i], team, 1) + " crowd " +
                    "around you intimidatingly.\n"); 
        else
            people[i]->catch_msg(team_desc(people[i], team, 1) + " crowd " +
                        "around " + QTNAME(it[0]) + " intimidatingly.\n"); 
    }
    return 1;
}


/* Team leap into the air and clash weapons */
int
calian_team_leap()
{
    object *team; 
    object *people;
    object tp = this_player();
    int i;
    string clash_str;

    UNDER_WATER_BLOCK;

    team = tp->query_team();

    if (!sizeof(team)) {
        notify_fail("You're not leading a team!\n");
        return 0;
    } 

    team = FILTER_PRESENT_LIVE(team);
    if (!sizeof(team)) {
        notify_fail("You can't seem to find any of your team members.\n");
        return 0;
    }

    clash_str = "weapons";
    team += ({tp});

    for (i = 0; i < sizeof(team); i++) 
        if (!objectp(query_main_weapon(team[i], "")))
             clash_str = "fists";
    

    people = FILTER_PLAYERS(all_inventory(environment(tp)));

    for (i = 0; i < sizeof(people); i++) 
        people[i]->catch_msg(team_desc(people[i], team, 1) + " leap " +
                        "into the air and clash " + clash_str + "!\n");
    return 1;
}


/* Return the possible main bodies of a selected random laugh desc. */
mixed
random_laugh_desc()
{
     string a, *v, p;

     a = laugh_adv[random(sizeof(laugh_adv))];

     switch (random(5))  {
          case 0 : v =    ({("snicker " + a), 
                            ("snickers " + a), 
                            ("snickering " + a)});
                   break;
          case 1 : v =    ({("laugh " + a), 
                            ("laughs " + a), 
                            ("laughing " + a)});
                   break;
          case 2 : v =    ({("cackle " + a), 
                            ("cackles " + a), 
                            ("cackling " + a)});
                   break;
          case 3 : v =    ({("chortle " + a), 
                            ("chortles " + a),
                            ("chortling " + a)}); 
                   break;
          default : v =   ({("giggle " + a), 
                            ("giggles " + a),
                            ("giggling " + a)}); 
                   break;
     }

     return ({ ({v[0], v[1]}),
               ({"start to " + v[0], "starts to " + v[0]}),
               ({"begin " + v[2], "begins " + v[2]}) });
}


/* get the right laugh_desc given the seeing player and laughing player(s) */
string
right_laugh_desc(object s_ob, mixed l_ob, string *sel)
{

     if (pointerp(l_ob) &&  (sizeof(l_ob) == 1))
         l_ob = l_ob[0];

     if (pointerp(l_ob) &&  (sizeof(l_ob) > 1))
         return sel[0]; 
     else  {
        if (s_ob == l_ob) 
            return sel[0];
        else
            return sel[1]; 
    }
}



/* A team laugh, either a general one or at another player. */
int
calian_team_laugh(string str)
{
    object *team, *people, *it, laughing_at; 
    object tp = this_player();
    int i, j;
    mixed leader_laugh, team_laugh;
    string ld;

    UNDER_WATER_BLOCK;

    /* Allow any Calian in the team to use it, not just team members. */
    team = tp->query_team_others(); 

    if (!sizeof(team)) {
        notify_fail("You're not in a team!\n");
        return 0;
    } 

    team = FILTER_PRESENT_LIVE(team);
    if (!sizeof(team)) {
        notify_fail("You can't seem to find any of your team members.\n");
        return 0;
    }

    if (stringp(str)) {
        it = parse_this(str, "%l");

        if (!sizeof(it)) {
            notify_fail("Team laugh at whom?\n");
            return 0;
        }

        if (sizeof(it) > 1) {
            notify_fail("You can only team laugh at one person at a time!\n");
            return 0;
        }

        if (member_array(it[0], team) > -1) {
            notify_fail("Har har, joker.\n");
            return 0;
        }
      
        laughing_at = it[0]; 
    }

    leader_laugh = random_laugh_desc()[random(3)];
    team_laugh = random_laugh_desc()[random(3)];

    people = FILTER_PLAYERS(all_inventory(environment(tp)));

    for (i = 0; i < sizeof(people); i++) {
        ld = team_desc(people[i], ({tp}), 1); 
        if (objectp(laughing_at)) { 
            if (people[i] == tp)
                ld += " point ";
            else
                ld += " points ";
            ld += ("a finger at " + 
                   team_desc(people[i], ({laughing_at}), 0) + " and "); 
        }
        else
            ld += " ";
        ld += right_laugh_desc(people[i], tp, leader_laugh);
        ld += ", and soon afterwards ";
        ld += team_desc(people[i], team, 0);
        if ((sizeof(team) > 1) || (member_array(people[i], team) > -1)) 
            ld += " join ";
        else 
            ld += " joins ";
        ld += ("in and " + 
               right_laugh_desc(people[i], team, team_laugh));
        people[i]->catch_msg(ld + ".\n"); 
    }
    return 1;
}


/* A team war cry. Leader gives a warcry then other Calians in the team
   give one, selected from a range of presets. Option also to auto-attack
   a selected living after giving the cry.
*/ 
int
calian_team_warcry(string str)
{
   object tp = this_player();
   string msg;
   int i, num;
   string liv;
   object to_attack, *team, *it;

   UNDER_WATER_BLOCK;

   if (!stringp(str)) {
        msg = "Here are the possible team war cries:\n";
        for (i = 0; i < sizeof(team_war_cries); i++) 
            msg += ((i+1) + ": " + team_war_cries[i][0] + "\n");
        tp->catch_msg(msg);
        return 1;
   }

   team = tp->query_team();

   if (!sizeof(team)) {
       notify_fail("You're not leading a team!\n");
       return 0;
   } 

   team = FILTER_PRESENT_LIVE(filter(team, is_calian));
   if (!sizeof(team)) {
       notify_fail("You can't seem to find any Calian team members!\n");
       return 0;
   }

   if (sscanf(str, "%d %s", num, liv) == 2) {
       if ((num < 1) || (num > sizeof(team_war_cries))) {
           notify_fail("No team war cry with that number.\n");
           return 0; 
       }
        it = parse_this(liv, "%l");

        if (!sizeof(it)) {
            notify_fail("War cry and attack whom?\n");
            return 0;
        }

        if (sizeof(it) > 1) {
            notify_fail("You can only attack one person at a time!\n");
            return 0;
        }

        if (member_array(it[0], team) > -1) {
            notify_fail("Har har, joker.\n");
            return 0;
        }
      
        to_attack = it[0]; 
   }


   if (!objectp(to_attack))  {
       /* Maybe they just wanted a war cry */
       if (sscanf(str, "%d", num) == 1) {
           if ((num < 1) || (num > sizeof(team_war_cries))) {
               notify_fail("No team war cry with that number.\n");
               return 0; 
           }
       }
       /* Or maybe they tried to attack something and want a random war cry */
       else {
           it = parse_this(str, "%l");

           if (!sizeof(it)) {
              notify_fail("War cry and attack whom?\n");
              return 0;
           }

          if (sizeof(it) > 1) {
              notify_fail("You can only attack one person at a time!\n");
              return 0;
          }

          if (member_array(it[0], team) > -1) {
              notify_fail("Har har, joker.\n");
              return 0;
          }
      
          to_attack = it[0]; 
          num = random(sizeof(team_war_cries)) + 1; 
      }
   }

   tp->command("cwar " + team_war_cries[num-1][1]); 
   if (objectp(to_attack)) 
       tp->command("kill " + OB_NAME(to_attack));

   for (i = 0; i < sizeof(team); i++) 
       team[i]->command("cwar " + team_war_cries[num-1][2]); 
   
   if (objectp(to_attack))
       for (i = 0; i < sizeof(team); i++) 
            team[i]->command("kill " + OB_NAME(to_attack)); 

   return 1;
}



/* Describe an armour wielded by a team member, only giving condition if 
   skill is high enough */
string
my_armour_des(int sk, object armour)
{
    if (sk < 20)
        return ("    " + armour->short() + ".\n");
    else 
        return ("    " +armour->short() + ": " + 
                armour->arm_condition_desc());
}


/* Describe a weapon wielded by a team member, only giving condition if 
   skill is high enough */
string
my_weapon_des(int sk, object weapon)
{
    if (sk < 30)
        return ("    " + weapon->short() + ".\n");
    else 
        return ("    " + weapon->short() + ": " +
                weapon->wep_condition_desc());
}


/* Used in a filter of livings currently attacking an object ob */
int
attacking_object(object ob, object at)
{
    if (at->query_attack() == ob)
        return 1;
    else
        return 0;
}


/* Team appraisal, a Calian tries to appraise a team member for a particular
   thing like weapons, armour etc.
   Success for some of these depends on the appraise object skill. */
string
cal_appraisal(object looking, object appraised, string thing, int sk)
{
    string str, *wep_des, *arm_des, hs;
    object att, *atb, *wep, *arm;
    int hp, maxhp, i;

    if (!objectp(looking) || !objectp(appraised))
        return "";

    if (looking == appraised)
        sk = 40; /* Easy to appraise one's own stuff */

    str = "";

    switch (thing) { 
        case AP_BATTLE : 
                        str += "  Attacking: "; 
                        att = appraised->query_attack();
                        if (objectp(att)) 
                            str += (QNAME(att) + ".\n");
                        else
                            str += ("No-one.\n");
                        atb = filter(
                                 FILTER_LIVE(all_inventory(
                                                 environment(appraised))),
                                 &attacking_object(appraised));
                        str += "  Currently attacked by: ";
                        if (!sizeof(atb))
                            str += "No-one.\n";
                        else
                            str += (COMPOSITE_LIVE(atb) + ".\n");
                        return str;
                        break;
        case AP_WEAPON : 
                        wep = appraised->query_weapon(-1);
                        wep_des = map(wep, &my_weapon_des(sk));
                        str += "  Wielded weapons:\n";
                        if (!sizeof(wep_des))
                           str += "    None.\n";
                        else
                            for (i = 0; i < sizeof(wep_des); i++)
                                str += wep_des[i];
                        return str;
                        break;
        case AP_ARMOUR : 
                        arm = appraised->query_armour(-1);
                        arm_des = map(arm, &my_armour_des(sk));
                        str += "  Worn armours:\n";
                        if (!sizeof(arm_des))
                            str += "    None.\n";
                        else
                             for (i = 0; i < sizeof(arm_des); i++)
                                 str += arm_des[i];
                        return str;
                        break;
         default :   return "";
                     break;
    }
}


/* Appraisal of a team. */
int
calian_team_appraise(string str)
{
    object *team; 
    object *people;
    object tp = this_player();
    int i, sk;
    string msg;
  
    team = tp->query_team_others();

/*
    if (!sizeof(team)) {
        notify_fail("You're not in a team!\n");
        return 0;
    } 
 */ 

    team = FILTER_PRESENT_LIVE(team);

/*
    if (!sizeof(team)) {
        notify_fail("You can't seem to find any of your team members.\n");
        return 0;
    }
 */

    /*
     * It is dark.
     */
    if (!CAN_SEE_IN_ROOM(tp))
    {
        notify_fail("You can't currently see any of your team mates.\n");
        return 0;
    }

    if ((str != AP_WEAPON) && (str != AP_ARMOUR) && 
        (str != AP_BATTLE)) {
        notify_fail("Appraise team members for what?\n");
        return 0;
    }

    if (sizeof(team)) { 
        write("You do a careful appraisal of your team's " + 
              str + " status.\n");
        allbb(" does a careful appraisal of " + tp->query_possessive() + 
              " team's " + str + " status."); 
    }

    sk = tp->query_skill(SS_APPR_OBJ);
    msg = "You:\n";
    msg += cal_appraisal(tp, tp, str, sk); 

    for (i = 0; i < sizeof(team); i++) {
         if (!CAN_SEE(tp, team[i])) 
             continue;
         msg += (QCTNAME(team[i]) + ":\n");
         msg += cal_appraisal(tp, team[i], str, sk);
    }
    tp->catch_msg(msg);
    return 1;
}


int
calian_pledge()
{
    object *team, *team_others, leader, *l, tp;
    int teamed;
    mixed team_title;

    tp = this_player();
    team_others = tp->query_team_others();
    team = tp->query_team();

    if (!sizeof(team_others)) {
        notify_fail("You're not currently teamed!\n");
        return 0;
    }

    team_others = FILTER_PRESENT_LIVE(team_others);
    if (!sizeof(team_others)) {
        notify_fail("You can't seem to find any of your team.\n");
        return 0;
    }

    if (sizeof(team)) {
        leader = tp;
        team_title = leader->query_prop(CALIAN_S_TEAM_TITLE);
        write("You pledge to lead your team" +
               (team_title ? (", known as " + team_title+",") : "") +
               " to victory!\n");
        allbb(" pledges to lead " + tp->query_possessive() + " team" +
               (team_title ? (", known as " + team_title+",") : "") +
               " to victory!");
        return 1;
    }
    else {
        leader = tp->query_leader();
        l = ({leader});
        actor("You pledge loyalty to your team leader", l);
        targetbb(" pledges loyalty to you as " + tp->query_possessive() +
                " team leader.", l);
        all2actbb(" pledges loyalty to " + tp->query_possessive() +
                  " team leader", l);
        return 1;
    }
}

