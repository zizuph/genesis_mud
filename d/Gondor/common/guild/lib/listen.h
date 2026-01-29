/*
 *  Listen.h - the command for the Gondorian Rangers, which makes them able
 *  to hear if any livings are present in the adjacent rooms.
 *  Elessar of Gondor, May 1992.
 *
 *  Revision history:
 *  Mercade, 22 September 1993 removed bug if you listen to a non-existant room
 */
#define COST   4              /* Mana-cost for listening. */
#define RANDOM_FACTOR    20   /* Chance of wrong info */
#define LISTEN_PUNISH_MOD     1
#define LISTEN_PUNISHED(o)  \
    ((o->query_skill(SS_PUNISHMENT)==NOSKILLS) \
    || (o->query_skill(SS_PUNISHMENT)==NOABILITIES))
#define LISTEN_SKILL(o)  \
    ((o)->query_skill(SS_HEARING) / (LISTEN_PUNISH_MOD+LISTEN_PUNISHED(o)))

/* 
 * Function name: test_if_detect(obj creature,int dirfatigue)
 * Description:   Tests if the player hears the creature, by calculating
 *      the players listen-skill along with the weight of the creature
 *      (heavier is easier to hear) and the fatigue of that direction
 *      (the fatigue is used to indicate distances in this calculation).
 * Returns: 0 if not detected, >0 if detected.
 */
int
test_if_detect(object creature, int dirfatigue)
{
  int result;
  if (creature->query_wiz_level() && creature->query_invis())
    return 0;
  result = (((creature->query_prop(CONT_I_WEIGHT)/1000) +
    LISTEN_SKILL(this_player())) - (random(RANDOM_FACTOR) + 100 + (dirfatigue * 100)))/10;
  return result;
}

/* Function name: test_for_info(obj creature, int detfactor)
 * Description:   Decides how much info the listening player aquires about
 *      the creature. Factors that count are the players skills in listen
 *      and in appraise monster, along with how well the creature was
 *      detected by the player in the test_if_detect() function.
 * Returns:       A string with the info the player gets about the creature.
 */
string
test_for_info(object creature, int detfactor)
{
    int     livsize,
            apprmon,
            listen,
            lvl;
    string  livinfo,
            sizestr,
            racestr;

    if (!objectp(creature))
	return "You think you hear something.\n";
    livsize = (creature->query_prop(OBJ_I_WEIGHT) +
	       creature->query_prop(OBJ_I_VOLUME)) / 1900;
    apprmon = TP->query_skill(SS_APPR_MON);
    listen = LISTEN_SKILL(TP);
    lvl = (listen + apprmon) / 2;
    switch (livsize)
    {
    case 0..50:
	sizestr = "tiny";
	break;
    case 51..75:
	sizestr = "small";
	break;
    case 76..100:
	sizestr = "medium sized";
	break;
    case 101..150:
	sizestr = "normal sized";
	break;
    case 151..300:
	sizestr = "large";
	break;
    case 301..500:
	sizestr = "huge";
	break;
    default:
	sizestr = "gigantic";
	break;
    }
    racestr = creature->query_race_name();

    if (detfactor < 2) 
	return "You think you hear something.\n";
    if (detfactor == 2) 
	return "You hear something moving.\n";
    if ((detfactor == 3) || (lvl <= (livsize / 75)))
	return "You hear something " + sizestr + " moving.\n";
    if ((detfactor == 4) && (lvl > (livsize / 75)))
	return "You hear something, probably a "+racestr+" moving.\n";
    if ((detfactor == 5) && (lvl > (livsize / 75)))
	return "You hear something, probably a "+sizestr+" "+racestr+".\n";
    if ((detfactor > 5) && (lvl > (livsize / 75)))
	return "You hear a "+sizestr+" "+racestr+".\n";
    return "You hear something moving.\n";
}

/* Function name: check_living_present(string roomstr,str dir)
 * Description: For each object in the room, tests if it is living,
 *     and if it is, calls the function test_if_detect() to see if is
 *     detected by the player. In that case it calls the function
 *     test_for_info() to see what info the player gains about the living.
 * Returns: The number of detected livings in the direction dir.
 */
int
check_living_present(string roomstr, string dir, int dirfatigue)
{
  object *inv_arr,room;
  int fight_flag, n, heard, dfactor;

  catch(roomstr->teleledingsanka());
  room = find_object(roomstr);
  if (!objectp(room))
    return 0;
  /*  Initialize the room, to make sure we get an inventory. */
  room->short();
  inv_arr = all_inventory(room);
  while ((n < sizeof(inv_arr)) && !fight_flag)
  {
    if (living(inv_arr[n]))
    {
      dfactor = test_if_detect(inv_arr[n],dirfatigue);
      if (inv_arr[n] == this_player()) dfactor = 0;
      if (dfactor && !inv_arr[n]->query_attack())
      {
        write(test_for_info(inv_arr[n],dfactor));
        heard++;
      }
      else if (inv_arr[n]->query_attack()) fight_flag = 1;
    }
    n++;
  }
  if (fight_flag) return -1;
  return heard;
}

int
do_listen(string sdir)
{
  mixed  *exit_arr;
  object room;
  string  dir;
  int n,heard, fight_flag,dheard,*dirfatigue;

  if (this_player()->query_attack())
  {
    write("You are too busy fighting!\n");
    return 1;
  }
  switch(sdir)
  {
    case "n": dir = "north"; break;
    case "s": dir = "south"; break;
    case "e": dir = "east";  break;
    case "w": dir = "west";  break;
    case "nw": dir = "northwest"; break;
    case "sw": dir = "southwest"; break;
    case "se": dir = "southeast"; break;
    case "ne": dir = "northeast"; break;
    case "u": dir = "up"; break;
    case "d": dir = "down"; break;
    default:  dir = sdir; break;
  }
  setuid();
  seteuid(getuid());
  room = environment(this_player());
  if (!strlen(dir))
  {
    if (LISTEN_SKILL(this_player()) < 60)
    {
      notify_fail("You must specify the direction you are concentrating to listen in.\n");
      return 0;
    }
    if (room->query_prop(ROOM_I_INSIDE))
    {
      notify_fail("You must specify the direction to listen when inside a room.\n");
      return 0;
    }
    /*  Testing all directions. */
    write(BSN("You stretch yourself upon the ground, " +
        "with your ear pressed against the turf. There you lie " +
        "motionless for a while."));
    this_player()->add_mana(-COST);
    say(QCTNAME(TP)+" stretches "+OBJECTIVE(TP)+"self upon "+
        "the ground, pressing "+POSSESSIVE(TP)+" ear to the turf. There "+
        PRONOUN(TP)+" lies motionless for some time.\n", TP);
    exit_arr = room->query_exit();
    if(sizeof(exit_arr))
      dirfatigue = room->query_tired_exits();
  while ((n < sizeof(exit_arr)/3) && !fight_flag)
    {
    if (objectp(exit_arr[n*3]))
        exit_arr[n*3] = file_name(exit_arr[n*3]);
      dheard = check_living_present(exit_arr[n*3], exit_arr[n*3+1],
        dirfatigue[n]);
    if (dheard == -1) fight_flag = 1;
      heard = heard + dheard;
      n++;
    }
    if (!heard)
      write(BSN("You hear only the sound of the grass growing and the "+
          "wind blowing."));
  if (fight_flag)
    write("You hear the sound of fighting!\n");
    return 1;
  }
  /* Only listen in this room. */
  if (dir == "here") {
  write("You concentrate, and listen for sounds here.\n");
  this_player()->add_mana(-COST/2);
  say(QCTNAME(this_player()) + " seems to concentrate for a moment.\n",
    this_player());
  heard = check_living_present(file_name(environment(this_player())),"here",0);
  if (!heard) write("You hear nothing here, except your own breath.\n");
  if (heard == -1) write("Nothing can be heard above the clamour of the battle!\n");
  return 1;
  }
  /*  Only listen in one direction. */
  write(BSN("You stretch yourself upon the ground, pressing your "+
      "ear to the turf, to try to listen for sounds from the "+
      dir+"."));
  this_player()->add_mana(-COST/2);
  say(QCTNAME(TP) + " stretches "+OBJECTIVE(TP)+"self upon the ground, "+
      "pressing "+POSSESSIVE(TP)+" ear against the turf. "+
      "There "+PRONOUN(TP)+" lies motionless for some time.\n", TP);
  exit_arr = room->query_exit();
  if(sizeof(exit_arr)) dirfatigue = room->query_tired_exits();
  while (n < sizeof(exit_arr)/3)
  {
    if (dir == exit_arr[n*3 +1])
    {
        if (objectp(exit_arr[n*3]))
            exit_arr[n*3] = file_name(exit_arr[n*3]);
      heard = check_living_present(exit_arr[n*3], exit_arr[n*3+1],
        dirfatigue[n]);
    }
    n++;
  }
  if (heard == 0)
    write("You heard nothing there.\n");
  if (heard == -1) write("You hear the sounds of fighting!\n");
  return 1;
}
